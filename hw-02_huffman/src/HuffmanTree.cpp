#include <iterator>

#include "HuffmanTree.hpp"


//Destructor
HuffmanTree::~HuffmanTree(){
    delete root;
    delete innerVector;
    delete leaves;
}

//Private methods

// Insert new Node to the vector of node and sort the givven vector
void HuffmanTree::iNsert(Node *item){
    innerVector->push_back(item);
    int i = innerVector->size() - 2;
    while ((i >= 0) && (*((*innerVector)[i]) < *item)){
        (*innerVector)[i + 1] = (*innerVector)[i];
        (*innerVector)[i] = item;
        i--;
    }
}

// Set codes to nodes that are leafs. 
// Node *current - first node for setting code
// Depth - depth of the current node in the Tree (for the begining it's 0)
void HuffmanTree::setCodes(Node *current, int32_t code, int depth){
    if(depth > (int)sizeof(int32_t) * 8){
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

//Generate tree from Huffman algorithm from given vector of nodes
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
}

//GenerateCode() : returns dict with key - chars, value - pair: (code of the char; length of the code)
map<unsigned char, pair<int32_t, int>> * HuffmanTree::genereateCode(){
    if (root == nullptr){
        return nullptr;
    }
    setCodes(root, 0, 0);
    map<unsigned char, pair<int32_t, int>> *result = new map<unsigned char, pair<int32_t, int>>();
    for (size_t i = 0; i < leaves->size(); i++){
        result->insert(make_pair((*leaves)[i]->getValue(), make_pair((*leaves)[i]->getCode(), (*leaves)[i]->getCodeLength())));
    }
    return result;
}