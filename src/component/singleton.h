#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <assert.h>
#include <pthread.h>


template<typename T>
class Singleton 
{
public:
	static T& getInstance()
	{
		pthread_once(&ponce_, &Singleton::init);
		assert(value_ != NULL);
		return *value_;
	}

private:
	Singleton();
	~Singleton();

	static void init()
	{
		value_ = new T();
	}

private:
	static pthread_once_t ponce_;
	static T*             value_;
  
};

template<typename T>
pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;

template<typename T>
T* Singleton<T>::value_ = NULL;

}

#endif //_SINGLETON_H_

