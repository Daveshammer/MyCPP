#include <iostream>
#include <memory>
using namespace std;

/*
代理模式：为其他对象提供一个代理以控制对这个对象的访问。

通过代理类，来控制实际对象的访问权限
客户    助理Proxy    老板 委托类
*/
class VideoSite // 1. 抽象类
{
public:
    virtual void freeMovie() = 0;
    virtual void vipMovie() = 0;
    virtual void ticketMovie() = 0;
};

class RealVideoSite : public VideoSite // 2. 委托类（包含所有功能，不能直接使用）
{
public:
    void freeMovie() { cout << "免费电影" << endl; }
    void vipMovie() { cout << "VIP电影" << endl; }
    void ticketMovie() { cout << "用券电影" << endl; }
};

class FreeVideoSiteProxy : public VideoSite // 3.代理类（控制委托类的访问的权限问题）
{
public:
    FreeVideoSiteProxy() { pVideoSite = new RealVideoSite(); }
    ~FreeVideoSiteProxy() { delete pVideoSite; }
    virtual void freeMovie() { pVideoSite->freeMovie(); }
    virtual void vipMovie() { cout << "VIP电影，需要付费" << endl; }
    virtual void ticketMovie() { cout << "用券电影，需要付费" << endl; }
private:
    VideoSite *pVideoSite;
};
class VipVideoSiteProxy : public VideoSite // 3.代理类（控制委托类的访问的权限问题）
{
public:
    VipVideoSiteProxy() { pVideoSite = new RealVideoSite(); }
    ~VipVideoSiteProxy() { delete pVideoSite; }
    virtual void freeMovie() { pVideoSite->freeMovie(); }
    virtual void vipMovie() { pVideoSite->vipMovie(); }
    virtual void ticketMovie() { cout << "用券电影，需要付费" << endl; }
private:
    VideoSite *pVideoSite;
};

void watchMovie(unique_ptr<VideoSite> &ptr)
{
    ptr->freeMovie();
    ptr->vipMovie();
    ptr->ticketMovie();
    cout << "--------" << endl;
}

int main()
{
    unique_ptr<VideoSite> p1(new FreeVideoSiteProxy());
    unique_ptr<VideoSite> p2(new VipVideoSiteProxy());

    watchMovie(p1);
    watchMovie(p2);


    return 0;
}