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

//���write��û��д��
bool GSession::writeAgain()
{

}

//Ͷ�ݵ��������
int GSession::postTask()
{

}
