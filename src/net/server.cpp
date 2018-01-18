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

GServer::startService()
{
    struct epoll_event ev;
    ev.data.fd = m_listenfd;
    ev.events = EPOLLIN | EPOLLET;

    epoll_ctl(m_epfd, EPOLL_CTL_ADD, listenfd, &ev);

    struct sockaddr_in serveraddr;

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(m_port);
    
    bind(m_listenfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    
    listen(m_listenfd, LISTENQ);
    
    for (;;)
    {
        int nfds = epoll_wait(m_epfd, events, 10000, -1);

        for(i = 0 ; i < nfds ; ++i)
        {
            if (events[i].data.fd == listenfd)
            {
                struct sockaddr_in clientaddr;
                socklen_t clilen;

                connfd = accept(listenfd, (struct sockaddr*)&clientaddr, &clilen);
                
                NetTool::setnonblocking(connfd);
                                
                GSession* session = new GSession(connfd, inet_ntoa(clientaddr.sin_addr));
                m_sessions.insert(std::pair<long, GSession*>(connfd, session));
                
                ev.data.fd = connfd;
                ev.events = EPOLLIN | EPOLLET;
                epoll_ctl(m_epfd,EPOLL_CTL_ADD, connfd, &ev);

            } else if (events[i].events & EPOLLIN) {
                int sockfd = -1;
                GSession* session = NULL;
                if ((sockfd = events[i].data.fd) < 0) continue;
                if ((session = m_sessions[sockfd]) == NULL) continue;
                if (session.readAll() <= 0)
                {
                    close(sockfd);
                    events[i].data.fd = -1;
                    m_session.erase(sockfd);
                    delete session;
                }
                //do not add EPOLLOUT event here, only write return EAGAIN
            } else if(events[i].events & EPOLLOUT) {
                int sockfd = -1;
                GSession* session = NULL;
                if ((sockfd = events[i].data.fd) < 0) continue;
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


