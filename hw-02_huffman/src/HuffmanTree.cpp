#include <iterator>
#include <iostream>

#include "HuffmanTree.hpp"


//Destructor
HuffmanTree::~HuffmanTree(){
    delete root;
    delete innerVector;
    delete leaves;
}

//Private methods
void HuffmanTree::iNsert(Node *item){
    innerVector->push_back(item);
    int i = innerVector->size() - 2;
    while ((i >= 0) && (*((*innerVector)[i]) < *item)){
        (*innerVector)[i + 1] = (*innerVector)[i];
        (*innerVector)[i] = item;
        i--;
    }
}

void HuffmanTree::setCodes(Node *current, int code, int depth){
    if(depth > (int)sizeof(int) * 8){
        throw IntegerOverflow();
    }
    if(current->getIsLeaf()){
        current->setCode(code);
        current->setCodeLength(depth);
        return;
    }
    if(current->getChild0() != nullptr){
        setCodes(current->getChild0(), code << 1, depth + 1);
    }
    if(current->getChild1() != nullptr){
        setCodes(current->getChild1(), ((code << 1) | 1), depth + 1);
    }
}

//Public methods
void HuffmanTree::generateTree(vector<Node*> *v){
    innerVector = v;
    leaves = new vector<Node *>();
    if(innerVector->size() == 1){
        Node *bufferNode = new Node(1,1);
        bufferNode->setIsLeaf(false);
        innerVector->push_back(bufferNode);
    }
        Node *child0;
        Node *child1;
        int flag = 0;
        while(innerVector->size() != 1 ){
            flag++;
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
            iNsert(new Node(child0, child1));
        }
        root = innerVector->front();
        innerVector->pop_back();
    // } else {
    //     Node *child1 = v->front();
    //     innerVector->pop_back();
    //     leaves->push_back(child1);
    //     root = new Node(child1);
    //     //leaves->push_back(root);
    //     cout << "I'm here!\n";
    // }
}

map<unsigned char, pair<int, int>> * HuffmanTree::genereateCode(){
    if (root == nullptr){
        return nullptr;
    }
    setCodes(root, 0, 0);
    map<unsigned char, pair<int, int>> *result = new map<unsigned char, pair<int, int>>();
    for (size_t i = 0; i < leaves->size(); i++){
        result->insert(make_pair((*leaves)[i]->getValue(), make_pair((*leaves)[i]->getCode(), (*leaves)[i]->getCodeLength())));
    }
    return result;
}