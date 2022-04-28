#include <iterator>
#include <iostream>

#include "HuffmanTree.hpp"


//Destructor
HuffmanTree::~HuffmanTree(){
    delete root;
    delete innerVector;
}

//Private methods
void HuffmanTree::insert(Node *item){
    innerVector->push_back(item);
    int i = innerVector->size() - 2;
    while ((i >= 0) && (*((*innerVector)[i]) < *item)){
        (*innerVector)[i + 1] = (*innerVector)[i];
        (*innerVector)[i] = item;
        i--;
    }
}

void HuffmanTree::setCodes(Node *root, int code, int depth){
    if(depth > (int)sizeof(int) * 8){
        throw IntegerOverflow();
    }
    if(root->getIsLeaf()){
        root->setCode(code);
        root->setCodeLength(depth);
        return;
    }
    if(root->getChild0() != nullptr){
        setCodes(root->getChild0(), code << 1, depth + 1);
    }
    if(root->getChild1() != nullptr){
        setCodes(root->getChild1(), ((code << 1) | 1), depth + 1);
    }
}

//Public methods
void HuffmanTree::generateTree(vector<Node*> *v){
    innerVector = v;
    Node *child0;
    Node *child1;
    int counter = 0;
    leaves = new vector<Node *>();
    while(innerVector->size() != 1){
        counter++;
        child0 = innerVector->back();
        innerVector->pop_back();
        child1 = innerVector->back();
        innerVector->pop_back();
        if(child0->getIsLeaf()){
            leaves->push_back(child0);
        }
        if(child1->getIsLeaf()){
            leaves->push_back(child1);
        }
        insert(new Node(child0, child1));
    }
    root = innerVector->front();
    innerVector->pop_back();
}

map<unsigned char, pair<int, int>> * HuffmanTree::genereateCode(){
    if (root == nullptr){
        return nullptr;
    }
    setCodes(root, 0, 0);
    map<unsigned char, pair<int, int>> *result = new map<unsigned char, pair<int, int>>;
    for (size_t i = 0; i < leaves->size(); i++){
        result->insert(make_pair((*leaves)[i]->getValue(), make_pair((*leaves)[i]->getCode(), (*leaves)[i]->getCodeLength())));
    }
    return result;
}