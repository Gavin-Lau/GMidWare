#ifndef _DATA_QUEUE_H_
#define _DATA_QUEUE_H_

#include <vector>
#define CHUNK_SIZE (100)
#define CHUNK_COUNT (20)
class DataQueue {

public:
	DataQueue();
	~DataQueue();

	void insertData(char* buf, int bufLen);
	void extractData(char* buf, int *bufLen);

private:


private:
	unsigned int m_insertPos;
	unsigned int m_insertChunk;

	std::vector<char*> m_bufs;
	std::vector<int> m_bufSize;
};

#endif //_DATA_QUEUE_H_
