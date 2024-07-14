#ifndef __LIST__
#define __LIST__

//#include <>

namespace sylar{

class Node {
public:
    Node();
    Node(int val);
    Node(int val, Node* p, Node* n);
    Node(const Node& node);
    ~Node();

    Node& operator=(const Node& node);

    int value;
    Node* prev;
    Node* next;
};


class DuLinkList {
public:
    DuLinkList();
    ~DuLinkList();

    void push_back(Node* node);
    void push_front(Node* node);
    void pop_back();
    void pop_front();
    

private:
    Node* m_head;
};

} // end namespace
#endif
