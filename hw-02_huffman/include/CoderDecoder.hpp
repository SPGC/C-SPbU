#include <map>

#include "Node.hpp"

#ifndef CODERDECODER
#define CODERDECODER

using namespace std;

class Codder{
private:
    map<unsigned char, pair<int, int>> *codeTable;
public:
    Codder(map<unsigned char, pair<int, int>> *);
    pair<int, int> code(unsigned char);
};

class Decoder
{
private:
    map<pair<int, int>, unsigned char> *codeTable;
public:
    Decoder(map<pair<int, int>, unsigned char> *);
    pair<unsigned char, pair<unsigned char*, pair<int,int>>> decode(unsigned char *, int, int);
};
#endif
