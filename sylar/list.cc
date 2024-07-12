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

Node::Node(const Node& node)
    :value(node.value)
    ,prev(new Node)
    ,next(new Node){

    *prev = *(node.prev);
    *next = *(node.next);

}

Node::~Node(){
    delete prev;
    delete next;
}

Node& Node::operator=(const Node& node){
    value = node.value;
    Node* tmpNode(node);  

    if(prev)
        delete prev;
    if(next)
        delete next;

    prev = new Node(tmpNode.prev);
    next = new Node(tmpNode.next);

    retrun *this; 
}




} // end namespace
