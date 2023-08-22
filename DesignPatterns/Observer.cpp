#include <iostream>
#include <list>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <memory>
using namespace std;

/*
观察者模式：定义对象间的一种一对多的依赖关系，以便当一个对象的状态发生改变时，所有依赖于它的对象都得到通知并自动刷新。
主要关注的是对象之间的通信
*/

// 定义监听者基类
class Listener
{
public:
	// 基类构造函数
	Listener(string name) :_name(name) {}
	// 监听者处理消息事件的纯虚函数接口
	virtual void handleMessage(int msgid) = 0;
protected:
	string _name;
};
// 一个具体的监听者类Listener1
class Listener1 : public Listener
{
public:
	Listener1(string name) :Listener(name) {}
	// Listener1处理自己感兴趣的事件
	void handleMessage(int msgid)
	{
		cout << "listener:" << _name << " recv:" << msgid
			<< " msg, handle it now!" << endl;
	}
};
// 一个具体的监听者类Listener2
class Listener2 : public Listener
{
public:
	Listener2(string name) :Listener(name) {}
	// Listener2处理自己感兴趣的事件
	void handleMessage(int msgid)
	{
		cout << "listener:" << _name << " recv:" << msgid
			<< " msg, handle it now!" << endl;
	}
};
// 实现观察者用强弱智能指针，解决多线程访问共享对象的线程安全问题
class Observer
{
public:
	/*
	params:
	1. Listener *pListener: 具体的监听者
	2. int msgid： 监听者感兴趣的事件
	该函数接口主要用于监听者向观察者注册感兴趣的事件
	*/
	void registerListener(weak_ptr<Listener> pwListener, int msgid)
	{
		auto it = listenerMap.find(msgid);
		if (it == listenerMap.end())
		{
			// 没人对msgid事件感兴趣过，第一次注册
			listenerMap[msgid].push_front(pwListener);
		}
		else
		{
			// 直接把当前pListener添加到对msgid事件感兴趣的list列表中
			it->second.push_front(pwListener);
		}
	}
	/*
	params:
	1. int msgid：观察到发生的事件id
	该函数接口主要用于观察者观察到事件发生，并转发到对该事件感兴趣
	的监听者
	*/
	void dispatchMessage(int msgid)
	{
		auto it = listenerMap.find(msgid);
		if (it != listenerMap.end())
		{
			for (auto it1 = it->second.begin();
				it1 != it->second.end();
				++it1)
			{
				// 智能指针的提升操作，用来判断监听者对象是否存活
				shared_ptr<Listener> ps = it1->lock();
				// 监听者对象如果存活，才通知处理事件
				if (ps != nullptr)
				{
					ps->handleMessage(msgid);
				}
				else
				{
					// 监听者对象已经析构，从map中删除这样的监听者对象
					it1 = it->second.erase(it1);
				}
			}
		}
	}
private:
	// 存储监听者注册的感兴趣的事件
	unordered_map<int, list<weak_ptr<Listener>>> listenerMap;
};
int main()
{
	shared_ptr<Listener> p1(new Listener1("高海山"));
	shared_ptr<Listener> p2(new Listener2("冯丽婷"));

	Observer obser;
	// 监听者p1注册1，2，3号事件
	obser.registerListener(p1, 1);
	obser.registerListener(p1, 2);
	obser.registerListener(p1, 3);
	// 监听者p2注册1，3号事件
	obser.registerListener(p2, 1);
	obser.registerListener(p2, 3);

	// 模拟事件的发生
	int msgid;
	for (;;)
	{
		cout << "输入事件id:";
		cin >> msgid;
		if (-1 == msgid)
			break;
		// 通过用户手动输入msgid模拟事件发生，此处观察者派发事件
		obser.dispatchMessage(msgid);
	}

	return 0;
}
