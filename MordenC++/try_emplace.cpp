#include <iostream>
#include <map>
#include <memory>

class ChatDialog
{
public:
    ChatDialog()
    {
        std::cout << "ChatDialog constructor" << std::endl;
    }

    ~ChatDialog()
    {
        std::cout << "ChatDialog destructor" << std::endl;
    }
    void activate()
    {
        //实现省略
    }
};

//用于管理所有聊天对话框的map，key是好友id，ChatDialog是聊天对话框指针
std::map<int64_t, ChatDialog*> m_ChatDialogs;
std::map<int64_t, std::unique_ptr<ChatDialog>> m_ChatDialogs2; //使用智能指针重构

//普通版本
void onDoubleClickFriendItem(int64_t userid)
{
    auto targetChatDialog = m_ChatDialogs.find(userid);
    //好友对话框不存在，则创建之，并激活
    if (targetChatDialog == m_ChatDialogs.end())
    {
        ChatDialog* pChatDialog = new ChatDialog();
        m_ChatDialogs.insert(std::pair<int64_t, ChatDialog*>(userid, pChatDialog));
        pChatDialog->activate();
    }
    //好友对话框存在，直接激活
    else
    {
        targetChatDialog->second->activate();
    }
}

//C++17版本1
/*
    try_emplace的返回值是一个std::pair<T1, T2>类型，其中T2是一个bool类型表示元素是否成功插入map中，
    T1是一个map的迭代器，如果插入成功，则返回指向插入位置的元素的迭代器，如果插入失败，则返回map中已存在的相同key元素的迭代器。
*/
void onDoubleClickFriendItem2(int64_t userid)
{   
    //结构化绑定和try_emplace都是 C++17语法
    auto [iter, inserted] = m_ChatDialogs.try_emplace(userid);
    if (inserted)
        iter->second = new ChatDialog();   

    iter->second->activate();
}

//C++ 17版本3 使用智能指针重构
void onDoubleClickFriendItem3(int64_t userid)
{   
    //结构化绑定和try_emplace都是 C++17语法    
    auto [iter, inserted] = m_ChatDialogs2.try_emplace(userid, nullptr);
    if (inserted)
    {
        auto spChatDialog = std::make_unique<ChatDialog>();
        iter->second = std::move(spChatDialog);
    }

    iter->second->activate();
}

int main()
{
    //测试用例

    // //906106643 是userid
    // onDoubleClickFriendItem2(906106643L);
    // //906106644 是userid
    // onDoubleClickFriendItem2(906106644L);
    // //906106643 是userid
    // onDoubleClickFriendItem2(906106643L);

    //906106643 是userid
    onDoubleClickFriendItem3(906106643L);
    //906106644 是userid
    onDoubleClickFriendItem3(906106644L);
    //906106643 是userid
    onDoubleClickFriendItem3(906106643L);

    return 0;
}
