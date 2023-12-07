#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <list>
#include <semaphore.h>
#include <iostream>

/*
    创建1个生产者线程和5个消费者线程，初始信号量计数为0代表开始没有可执行任务，
    所以5个消费线程均阻塞在sem_wait调用处，接着生产者每隔1秒产生一个任务，
    然后通过调用sem_post将信号量资源计数增加1，此时其中一个线程会被唤醒，
    然后我们从任务队列中取出任务，执行任务
*/

class Task
{
public:
	Task(int taskID)
	{
		this->taskID = taskID;
	}
	
	void doTask()
	{
		std::cout << "handle a task, taskID: " << taskID << ", threadID: " << pthread_self() << std::endl; 
	}
	
private:
	int taskID;
};

pthread_mutex_t  mymutex; // 保护队列tasks的
std::list<Task*> tasks;
sem_t            mysemaphore;


void* consumer_thread(void* param)
{	
	Task* pTask = NULL;
	while (true)
	{
		if (sem_wait(&mysemaphore) != 0)
			continue;
		
		if (tasks.empty())
			continue;
		
		pthread_mutex_lock(&mymutex);	
		pTask = tasks.front();
		tasks.pop_front();
		pthread_mutex_unlock(&mymutex);
		
		pTask->doTask();
		delete pTask;
	}
	
	return NULL;
}

void* producer_thread(void* param)
{
	int taskID = 0;
	Task* pTask = NULL;
	
	while (true)
	{
		pTask = new Task(taskID);
			
		pthread_mutex_lock(&mymutex);
		tasks.push_back(pTask);
		std::cout << "produce a task, taskID: " << taskID << ", threadID: " << pthread_self() << std::endl; 
		
		pthread_mutex_unlock(&mymutex);
		
		//释放信号量，通知消费者线程
		sem_post(&mysemaphore);
		
		taskID ++;

		//休眠1秒
		sleep(1);
	}
	
	return NULL;
}

int main()
{
	pthread_mutex_init(&mymutex, NULL);
	//初始信号量资源计数为0
	sem_init(&mysemaphore, 0, 0);

	//创建5个消费者线程
	pthread_t consumerThreadID[5];
	for (int i = 0; i < 5; ++i)
	{
		pthread_create(&consumerThreadID[i], NULL, consumer_thread, NULL);
	}
	
	//创建一个生产者线程
	pthread_t producerThreadID;
	pthread_create(&producerThreadID, NULL, producer_thread, NULL);

	pthread_join(producerThreadID, NULL);
	
	for (int i = 0; i < 5; ++i)
	{
		pthread_join(consumerThreadID[i], NULL);
	}
	
	sem_destroy(&mysemaphore);
	pthread_mutex_destroy(&mymutex);

	return 0;
}