#include <iostream>
#include <memory>
using namespace std;

/*
适配器：将一个类的接口转换成客户希望的另一个接口。适配器使得原来不兼容的接口可以一起工作。

电脑 =》 投影到 =》 投影仪上 VGA HDMI TypeC
*/
class VGA // VGA接口类
{
public:
    virtual void play() = 0;
    string getType()const {return "VGA"; }
};
// TV01表示支持VGA接口的投影仪
class TV01 : public VGA
{
public:
    void play() { cout << "TV01:VGA" << endl; }
};

class HDMI // HDMI接口类
{
public:
    virtual void play() = 0;
    string getType()const {return "HDMI"; }
};
// TV02表示支持HDMI接口的投影仪
class TV02 : public HDMI
{
public:
    void play() { cout << "TV02:HDMI" << endl; }
};

// 电脑类(只支持VGA接口)
class Computer
{
public:
    void playVideo(VGA* vga) { vga->play(); }
};

// 由于电脑（VGA接口）和投影仪(HDMI接口)不兼容，所以需要适配器
class VGAToHDMIAdapter : public VGA
{
public:
    VGAToHDMIAdapter(HDMI* hdmi) :pHdmi(hdmi) {} 
    void play() { pHdmi->play(); }
private:
    HDMI* pHdmi;
};


int main()
{
    Computer computer;
    computer.playVideo(new TV01()); // 把电脑上的视频投影到TV01上
    computer.playVideo(new VGAToHDMIAdapter(new TV02())); // 把电脑上的视频投影到TV02上

    return 0;
}