#include "dataQueue.h"

#define Min(a, b) ((a) < (b) ? (a) : (b))
#define Max(a, b) ((a) > (b) ? (a) : (b))

DataQueue::DataQueue()
{	
	for (int i = 0; i < CHUNK_COUNT; ++i)
	{
		char* buf = (char*)malloc(CHUNK_SIZE * sizeof(char));
		m_bufs.push_back(buf);
	}

	m_insertPos = 0;
	m_insertChunk = 0;
}

DataQueue::~DataQueue()
{
	int chunkCount = m_bufs.size();
	for (int i = 0; i < chunkCount; ++i)
	{
		free(m_bufs.back());
		m_bufs.pop_back();
	}
}

void DataQueue::insertData(char* buf, int bufLen)
{
	/* buf 空间足够存储此次buf */
	int copiedLen = 0;
	char* curChunk = NULL;
	while(copiedLen < bufLen)
	{
		curChunk = m_bufs[m_insertChunk];
		/* 本块足够存储此次buf */
		if (CHUNK_SIZE - m_insertPos > bufLen - copiedLen)
		{
			memcpy(curChunk + m_insertPos, buf + copiedLen, bufLen - copiedLen);
			m_insertPos += (bufLen - copiedLen);
			break;
		}
		else
		{
			memcpy(curChunk + m_insertPos, buf + copiedLen, CHUNK_SIZE - m_insertPos);
			copiedLen += CHUNK_SIZE - m_insertPos;
			m_insertPos = 0;
			if (m_insertChunk == m_bufs.size() - 1)
			{
				m_bufs.push_back((char*)malloc(CHUNK_SIZE * sizeof(char)));
			}
			m_insertChunk++;
		}
	}
	m_bufSize.push_back(bufLen);
}

void DataQueue::extractData(char* buf, int *bufLen)
{
	int lastLen = m_bufSize[m_bufSize.size() - 1];
	m_bufSize.pop_back();
	int curMsgChunk = m_insertChunk;
	int curMsgPos = m_insertPos;
	int copiedLen = 0;
	*bufLen = lastLen;

	while (copiedLen < lastLen)
	{
		if (curMsgPos > lastLen - copiedLen)
		{
			memcpy(buf + lastLen - copiedLen, m_bufs[curMsgChunk] + (curMsgPos - lastLen), lastLen - copiedLen);
			copiedLen += lastLen;
			/* 回退insert指针位置 */
			m_insertChunk = curMsgChunk;
			m_insertPos = curMsgPos - lastLen;
			break;
		}
		else
		{
			memcpy(buf + lastLen - copiedLen - curMsgPos, m_bufs[curMsgChunk], curMsgPos);
			copiedLen += curMsgPos;
			curMsgPos = CHUNK_SIZE;
			curMsgChunk--;
		}
	}
}

