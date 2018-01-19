#ifndef _SERVER_H_
#define _SERVER_H_

#inclued "netcommon.h"
#include "session.h"

#include <map>

class GServer {

public:
    GServer();
    ~GServer();

    int startService();
	int addOutEvent(int sockfd);
private:


private:

    int m_port; //listen port
    int m_epfd; 
    int m_listenfd; 
    struct epoll_event m_events[MAX_EVENTS];
    std::map<long, GSession*> m_sessions;
};


#endif //_SERVER_H_
