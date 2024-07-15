#include <iostream>
#include "list.h"

namespace sylar {


Node::Node()
    :value(0)
    ,prev(nullptr)
    ,next(nullptr){
}

Node::Node(int val)
    :value(val)
    ,prev(nullptr)
    ,next(nullptr){
}

Node::Node(int val, Node* p, Node* n)
    :value(val)
    ,prev(p)
    ,next(n){
    
}


Node::~Node(){
    if(prev)
        delete prev;
    if(next)
        delete next;
}


DuLinkList::DuLinkList()
    :m_head(new Node())
{
}

DuLinkList::DuLinkList(const DuLinkList& list){
    Node* node = list.getHead();
    m_head = new Node(*(list.getHead()));
    Node* self = m_head;        

    while(node->next){
        node = node->next;
        self->next = new Node(*node);
        Node* tmp = self;
        self = self->next;
        self->prev = tmp;

        if(node->next == list.getHead()){
            m_head->prev = self;
            break;
        }
    }
}

DuLinkList::~DuLinkList(){
}

DuLinkList& DuLinkList::operator=(const DuLinkList& list){
    return *this;
}

void DuLinkList::push_back(Node* node){
    if(m_head->prev == nullptr){
        m_head->next = node;
        m_head->prev = node;
        node->prev = m_head;
        node->next = m_head;
        return;
    }

    Node* end = m_head->prev;
    end->next = node;
    node->prev = end;
    node->next = m_head;
    m_head->prev = node;

}

void DuLinkList::push_front(Node* node){
    if(m_head->next == nullptr){
        m_head->next = node;
        m_head->prev = node;
        node->prev = m_head;
        node->next = m_head;
        return;
    }

    Node* front = m_head->next;
    front->prev = node;
    node->next = front;
    node->prev = m_head;
    m_head->next = node;
}

Node* DuLinkList::pop_back(){
    Node* back = m_head->prev;
    Node* end = back->prev;

    end->next = m_head;
    m_head->prev = end;

    return back;
}
Node* DuLinkList::pop_front(){
    Node* front = m_head->next;
    Node* first = front->next;

    m_head->next = first;
    first->prev = m_head;

    return front;
}




















} // end namespace
