#ifndef __LIST__
#define __LIST__

//#include <>

namespace sylar{

class Node {
public:
    Node();
    explicit Node(int val);
    Node(int val, Node* p, Node* n);
    Node(const Node& node) = default;
    ~Node();

    Node& operator=(const Node& node) = default; 

    int value;
    Node* prev;
    Node* next;
};


class DuLinkList {
public:
    DuLinkList();
    DuLinkList(const DuLinkList& list);
    ~DuLinkList();

    DuLinkList& operator=(const DuLinkList& list);
    void push_back(Node* node);
    void push_front(Node* node);
    Node* pop_back();
    Node* pop_front();

    Node* getHead() const {return m_head;}
private:
    Node* m_head;
};

} // end namespace
#endif
