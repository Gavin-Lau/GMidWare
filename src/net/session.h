#ifndef _SESSION_H_
#define _SESSION_H_

#include "netcommon.h"

class GSession {
	friend class GServer;
public:
    GSession(int sockfd, const char* addr);
    ~GSession();

	int readAll();
	int writeAll();

	//write没有写完返回true
	bool writeAgain();
	//投递到任务队列
	int postTask();

private:
    //receive queue
	//write queue
	int m_sockfd;
	std::string m_addr;
	GServer* m_serverSink;
};

#endif //_SESSION_H_


