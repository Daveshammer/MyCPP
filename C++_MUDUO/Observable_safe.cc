#include <iostream>
#include <algorithm>
#include <vector>
#include <mutex>
#include <memory>

class Observable;

class Observer : public std::enable_shared_from_this<Observer>
{
 public:
  virtual ~Observer();
  virtual void update() = 0;

  void observe(Observable* s);

 protected:
  Observable* subject_;
};

class Observable
{
 public:
  void register_(std::weak_ptr<Observer> x);
  // void unregister(boost::weak_ptr<Observer> x);

  void notifyObservers()
  {
    std::lock_guard<std::mutex> lock(mutex_);

    Iterator it = observers_.begin();
    while (it != observers_.end())
    {
      std::shared_ptr<Observer> obj(it->lock());
      if (obj)
      {
        obj->update();
        ++it;
      }
      else
      {
        printf("notifyObservers() erase\n");
        it = observers_.erase(it);
      }
    }
  }

 private:
  std::mutex mutex_;
  std::vector<std::weak_ptr<Observer> > observers_; //如果使用shared_ ptr，那么除非手动调用unregister()，否则Observer对象永远不会析构
  typedef std::vector<std::weak_ptr<Observer> >::iterator Iterator;
};

Observer::~Observer()
{
  // subject_->unregister(this);
}

void Observer::observe(Observable* s)
{
  s->register_(shared_from_this());
  subject_ = s;
}

void Observable::register_(std::weak_ptr<Observer> x)
{
  observers_.push_back(x);
}

//void Observable::unregister(boost::weak_ptr<Observer> x)
//{
//  Iterator it = std::find(observers_.begin(), observers_.end(), x);
//  observers_.erase(it);
//}

// ---------------------

class Foo : public Observer
{
  virtual void update()
  {
    printf("Foo::update() %p\n", this);
  }
};

int main()
{
  Observable subject;
  {
    std::shared_ptr<Foo> p(new Foo);
    p->observe(&subject);
    subject.notifyObservers();
  }
  subject.notifyObservers();
}
