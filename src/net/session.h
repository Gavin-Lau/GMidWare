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

	//writeû��д�귵��true
	bool writeAgain();
	//Ͷ�ݵ��������
	int postTask();

private:
    //receive queue
	//write queue
	int m_sockfd;
	std::string m_addr;
	GServer* m_serverSink;
};

#endif //_SESSION_H_


