#ifndef HUFFMANTREE
#define HUFFMANTREE

#include <vector>
#include <map>

#include "Node.hpp"
#include "Exception.hpp"

using namespace std;

class HuffmanTree{
    private:
        Node* root;
        vector<Node*> *innerVector;
        void iNsert(Node *);
        void setCodes(Node *, int32_t, int);
        vector<Node*> *leaves;
    
    public:
        ~HuffmanTree();
        void generateTree(vector<Node*> *);
        map<unsigned char, pair<int32_t, int>> * genereateCode();
};
#endif