#ifndef _SERVER_H_
#define _SERVER_H_

#include <map>

#include "session.h"

class GServer {

public:
    GServer();
    ~GServer();

    startService();

private:
    int m_port;
    std::map<long, GSession*> m_sessions;    

};


#endif //_SERVER_H_
