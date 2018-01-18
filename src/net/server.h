#ifndef _SERVER_H_
#define _SERVER_H_

#include <map>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "session.h"

#define MAX_EVENTS 10000
#define LISTENQ 20

class GServer {

public:
    GServer();
    ~GServer();

    startService();


private:
    int m_port; //listen port
    int m_epfd; 
    int m_listenfd; 
    struct epoll_event m_events[MAX_EVENTS];
    std::map<long, GSession*> m_sessions;    

};


#endif //_SERVER_H_
