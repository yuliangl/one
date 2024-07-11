#ifndef __LIST__
#define __LIST__

#include <>


class node {
public:
    node();
    ~node();
private:
    int value;
    node* prev;
    node* next;
};


class DuLinkList {
public:
    DuLinkList();
    ~DuLinkList();

    void push_back(node* node);
    void push_front(node* node);
    void pop_back(node* node);
    void pop_front(node* node);
    

private:
    node* m_head;
};

#endif
