#include "server.h"
#include "netcommon.h"


GServer::GServer()
{
    m_listenfd = socket(AF_INET, SOCK_STREAM, 0);
    NetTool::setnonblocking(m_listenfd);

    m_epfd = epoll_create();
}

GServer::~GServer()
{

}

int GServer::startService()
{
    struct epoll_event ev;
    ev.data.fd = m_listenfd;
    ev.events = EPOLLIN | EPOLLET;

    epoll_ctl(m_epfd, EPOLL_CTL_ADD, m_listenfd, &ev);

    struct sockaddr_in serveraddr;

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(m_port);
    
    bind(m_listenfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    
    listen(m_listenfd, LISTENQ);
    
    for (;;)
    {
		int nfds = epoll_wait(m_epfd, m_events, 10000, -1);

        for(i = 0 ; i < nfds ; ++i)
        {
			if (m_events[i].data.fd == m_listenfd)
            {
                struct sockaddr_in clientaddr;
                socklen_t clilen;

                int connfd = accept(m_listenfd, (struct sockaddr*)&clientaddr, &clilen);
                
                NetTool::setnonblocking(connfd);
                                
                GSession* session = new GSession(connfd, inet_ntoa(clientaddr.sin_addr));
				session->m_serverSink = this;
                m_sessions.insert(std::pair<long, GSession*>(connfd, session));
                
                ev.data.fd = connfd;
                ev.events = EPOLLIN | EPOLLET;
                epoll_ctl(m_epfd,EPOLL_CTL_ADD, connfd, &ev);

            } else if (m_events[i].events & EPOLLIN) {
                int sockfd = -1;
                GSession* session = NULL;
                if ((sockfd = m_events[i].data.fd) < 0) continue;
                if ((session = m_sessions[sockfd]) == NULL) continue;
                if (session.readAll() <= 0)
                {
                    close(sockfd);
                    m_events[i].data.fd = -1;
                    m_session.erase(sockfd);
                    delete session;
                }
                //do not add EPOLLOUT event here, only write return EAGAIN
            } else if(m_events[i].events & EPOLLOUT) {
                int sockfd = -1;
                GSession* session = NULL;
                if ((sockfd = m_events[i].data.fd) < 0) continue;
                if ((session = m_sessions[sockfd]) == NULL) continue;

                if (session.writeAgain() == true)
                {
                    ev.data.fd = sockfd;
                    ev.events = EPOLLOUT | EPOLLET;
                    epoll_ctl(m_epfd, EPOLL_CTL_MOD, sockfd, &ev);
                } else {
                    ev.data.fd = sockfd;
                    ev.events = EPOLLIN | EPOLLET;
                    epoll_ctl(m_epfd, EPOLL_CTL_MOD, sockfd, &ev);
                }
            }
        }
    }
}

int GServer::addOutEvent(int sockfd)
{
	GSession* session = NULL;

	struct epoll_event ev;
	ev.data.fd = sockfd;
	ev.events = EPOLLOUT | EPOLLET;

	if ((session = m_sessions[sockfd]) == NULL) return -1;
	epoll_ctl(m_epfd, EPOLL_CTL_MOD, sockfd, &ev);
}

