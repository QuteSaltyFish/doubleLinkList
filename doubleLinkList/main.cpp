//
//  main.cpp
//  doubleLinkList
//
//  Created by Mingke Wang on 2018/9/30.
//  Copyright © 2018年 Mingke Wang. All rights reserved.
//

#include <iostream>
#include <list>
using namespace std;

template <class elemType>
class dLinkList: public list<elemType>
{
private:
    struct node //双链表中的节点类
    {
        elemType data;
        node *prev, *next;  //存储前后地址
        
        node(const elemType &x, node *p = NULL, node *n = NULL)
        {
            data = x;
            next = n;
            prev = p;
        }
        node():next(NULL),prev(NULL){}
        ~node(){}
    };
    
    node *head, *tail;
    int currentLength;  //表长
    
    node *move(int i) const;    //返回第i个节点的地址
    
public:
    dLinkList();
    ~dLinkList()
    {
        clear();
        delete head;
        delete tail;
    }
    
    void clear();
    int length() const{return currentLength;}
    void insert(int i, const elemType &x);
    void remove(int i);
    int search(const elemType &x) const;
    elemType visit(int i) const;
    void traverse() const;
};

//双链表类构造函数的实现
template <class elemType>
dLinkList<elemType>::dLinkList()    //head和tail不保留data信息
{
    head = new node;
    head->next = tail = new node;
    tail->prev = head;
    currentLength = 0;
}

//双链表的插入删除和move函数的实现
template <class elemType>
typename dLinkList<elemType>::node *dLinkList<elemType>::move(int i) const
{
    node *p = head;
    while (i-->=0)
        p = p->next;
    return p;
}

template <class elemType>
void dLinkList<elemType>::insert(int i, const elemType &x)
{
    node *pos, *tmp;
    pos = move(i);  //找到第i个节点
    tmp = new node(x, pos->prev, pos);  //申请存在x的节点，设定前驱为节点i-1，后驱为原i节点
    pos->prev->next = tmp;  //i-1的后续为x
    pos->prev = tmp;    //原i前驱为x
    ++currentLength;
}

template <class elemType>
void dLinkList<elemType>::remove(int i)
{
    node *pos;
    
    pos = move(i);  //pos指向被删除点
    pos->prev->next = pos->next;    //设节点i-1的后继为i+1
    pos->next->prev = pos->prev;    //设节点i+1的前驱为i-1
    delete pos;
    --currentLength;
}

//双链表中visit、clear、search和traverse函数的实现
template <class elemType>
void dLinkList<elemType>::clear()
{
    node *p = head->next, *q;   //p指向被删除的节点，q指向被删除节点的后继
    head->next = tail;  //设为空表
    tail->prev = head;
    while (p!=tail)
    {
        q = p->next;
        delete p;
        p=q;
    }
    currentLength = 0;
}

template <typename elemType>
int dLinkList<elemType>::search(const elemType &x) const
{
    node *p = head->next;
    int i;
    
    for (i=0; p!=tail && p->data!=x; ++i)
        p = p->next;
    if (p==tail) return -1;
    else return i;
}

template <class elemType>
elemType dLinkList<elemType>::visit(int i) const
{
    return move(i)->data;
}

template <class elemtype>
void dLinkList<elemtype>::traverse() const
{
    node *p = head->next;
    cout<<endl;
    while (p!=tail)
    {
        cout<<p->data<<" ";
        p = p->next;
    }
    cout<<endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
