#include <iostream>
#include <pthread.h>
using namespace std;

// 对互斥锁操作的封装
class CMutex
{
public:
	CMutex(){pthread_mutex_init(&mutex, NULL);}  // 初始化锁
	~CMutex(){pthread_mutex_destroy(&mutex);}  // 销毁锁 
	void lock(){pthread_mutex_lock(&mutex);}  // 获取锁
	void unlock(){pthread_mutex_unlock(&mutex);}  // 释放锁
private:
	pthread_mutex_t mutex;
};

class Singleton
{
public:
	static Singleton* getInstance()
	{
		if (nullptr == single)
		{
			// 获取互斥锁
			mutex.lock();
			/* 
			这里需要再添加一个if判断，否则当两个
			线程都进入这里，又会多次new对象，不符合
			单例模式的涉及
			*/
			if(nullptr == single)
			{
				single = new Singleton();
			}
			// 释放互斥锁
			mutex.unlock();
		}
		
		return single;
	}
private:
	static Singleton *single;
	Singleton() { cout << "Singleton()" << endl; }
	~Singleton() { cout << "~Singleton()" << endl;}
	Singleton(const Singleton&);

	class CRelease //资源释放类，利用static静态对象在程序结束时自动析构
	{
	public:
		~CRelease() { delete single; }
	};
	static CRelease release;
	
	//线程间的静态互斥锁
	static CMutex mutex;
};
Singleton* Singleton::single = nullptr;
Singleton::CRelease Singleton::release;
// 定义互斥锁静态对象
CMutex Singleton::mutex;

int main()
{
	Singleton *p1 = Singleton::getInstance();
	Singleton *p2 = Singleton::getInstance();
	Singleton *p3 = Singleton::getInstance();
	cout << p1 << " " << p2 << " " << p3 << endl;

	switch (1)
	{
	case 1:
		cout << "case 1" << endl;
		break;
	
	default:
		cout << "default" << endl;
		break;
	}

	return 0;
}
