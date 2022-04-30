#ifndef CODERDECODER
#define CODERDECODER

#include <map>

#include "Node.hpp"


using namespace std;

class Codder{
private:
    map<unsigned char, pair<int32_t, int>> *codeTable;
public:
    Codder(map<unsigned char, pair<int32_t, int>> *);
    pair<int32_t, int> code(unsigned char);
};

class Decoder
{
private:
    map<pair<int32_t, int>, unsigned char> *codeTable;
public:
    Decoder(map<pair<int32_t, int>, unsigned char> *);
    pair<unsigned char, pair<unsigned char*, pair<int32_t,int>>> decode(unsigned char *, int, int);
};
#endif
