#include <vector>
#include <map>

#include "Node.hpp"
#include "Exception.hpp"

#ifndef HUFFMANTREE
#define HUFFMANTREE

using namespace std;

class HuffmanTree{
    private:
        Node* root;
        vector<Node*> *innerVector;
        void insert(Node *);
        void setCodes(Node *, int, int);
        vector<Node*> *leaves;
    
    public:
        ~HuffmanTree();
        void generateTree(vector<Node*> *);
        map<unsigned char, pair<int, int>> * genereateCode();
};
#endif