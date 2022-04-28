#include "Node.hpp"


//Constructors and destructor
Node::Node(Node *child0, Node *child1){
    this->child0 = child0;
    this->child1 = child1;
    this->amount = child1->amount + child0->amount;
    isLeaf = false;
}

Node::Node(unsigned char value, int amount){
    this->amount = amount;
    this->value = value;
    child0 = nullptr;
    child1 = nullptr;
    isLeaf = true;
}

Node::~Node(){
    if(child0 != nullptr){
        delete child0;
    }
    if(child1 != nullptr){
        delete child1;
    }
}

//Getters and setters
Node * Node::getChild0() const{
    return child0;
}

Node * Node::getChild1() const{
    return child1;
}

int Node::getAmount() const{
    return amount;
}

unsigned char Node::getValue() const{
    return value;
}

bool Node::getIsLeaf() const{
    return isLeaf;
}

int Node::getCode() const{
    return code;
}

int Node::getCodeLength() const{
    return codeLength;
}

void Node::setIsLeaf(bool flag){
    isLeaf = flag;
}

void Node::setCodeLength(int length){
    codeLength = length;
}

void Node::setCode(int code){
    this->code = code;
}

void Node::setChild1(Node * child1){
    this->child1 = child1;
}

void Node::setChild0(Node * child0){
    this->child0 = child0;
}

void Node::increaseAmount(){
    amount++;
}

//Not class methods

bool operator<(const Node& n1, const Node& n2){
    return n1.getAmount() < n2.getAmount();
}