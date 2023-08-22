#include <iostream>
using namespace std;

template <typename T>
class Queue
{
public:
    Queue()
    {
        _front = _rear = new QueueItem();
    }
    ~Queue()
    {
        while (_front)
        {
            _rear = _front->_next;
            delete _front;
            _front = _rear;
        }
    }
    void push(const T &val)
    {
        QueueItem *item = new QueueItem(val);
        _rear->_next = item;
        _rear = item;
    }
    void pop()
    {
        if (empty())
        {
            return;
        }
        QueueItem *p = _front->_next; // p指向队头元素
        _front->_next = p->_next;     // 队头元素出队
        if (_front->_next == nullptr) // 如果队列中只有一个元素，出队后队列为空
        {
            _rear = _front;
        }
        delete p;
    }
    T front() const
    {
        return _front->_next->_data;
    }
    T back() const
    {
        return _rear->_data;
    }
    bool empty() const
    {
        return _front == _rear;
    }

private:
    // 产生一个QueueItem的对象池（10000个QueueItem节点）
    struct QueueItem // 队列中的节点
    {
        QueueItem(T data = T()) : _data(data), _next(nullptr) {}
        // 给QueueItem提供自定义内存管理
        void *operator new(size_t size)
        {
            if (_itemPool == nullptr)
            {
                _itemPool = (QueueItem *)new char[POOL_ITEM_SIZE * sizeof(QueueItem)];
                QueueItem *p = _itemPool;
                for (int i = 0; i < POOL_ITEM_SIZE - 1; i++)
                {
                    p->_next = (QueueItem *)((char *)p + sizeof(QueueItem));
                    p = p->_next;
                }
                p->_next = nullptr;
            }

            QueueItem *p = _itemPool; // 从对象池中取出一个节点
            _itemPool = _itemPool->_next; // 对象池中的可用节点数减1，指向下一个可用节点
            return p; // 返回取出的节点
        }
        void operator delete(void *ptr)
        {
            QueueItem *p = (QueueItem *)ptr;
            p->_next = _itemPool; // 把释放的节点放回对象池中
            _itemPool = p;
        }
        T _data;
        QueueItem *_next;
        static QueueItem *_itemPool;
        static const int POOL_ITEM_SIZE = 10000;
    };

    QueueItem *_front; // 队头的前一个节点，头节点
    QueueItem *_rear;  // 队尾
};

template <typename T>
typename Queue<T>::QueueItem *Queue<T>::QueueItem::_itemPool = nullptr;

int main()
{
    Queue<int> que;
    for (int i = 0; i < 1000000; i++)
    {
        que.push(i);
        que.pop();
    }
    cout << que.empty() << endl;

    return 0;
}