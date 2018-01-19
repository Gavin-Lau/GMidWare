#include "session.h"

GSession::GSession(int sockfd, const char* addr)
	:m_sockfd(sockfd), m_addr(addr)
{

}

GSession::~GSession()
{

}

int GSession::readAll()
{

}

int GSession::writeAll()
{

}

//检测write有没有写完
bool GSession::writeAgain()
{

}

//投递到任务队列
int GSession::postTask()
{

}
