#ifndef IO
#define IO

#include <string>
#include <vector>
#include <fstream>

#include "Node.hpp"
#include "CoderDecoder.hpp"
#include "Exception.hpp"


using namespace std;

class IOModule{
private:
    map<pair<int32_t, int>, unsigned char> * readCodeFromFile(ifstream *);
    void writeCodeToFile(map<unsigned char, pair<int32_t, int>> *, ofstream *);
    void writeInteger(ofstream *, int32_t);
    int32_t readInteger(ifstream *);
    int fileSize;
    int archiveSize;
    int tableSize;
public:
    void decodedInCodedOut(string, string, map<unsigned char, pair<int32_t, int>> *);
    void codedInDecodedOut(string, string);
    vector<Node*> * constructNodes(string);
    int getFileSize() const;
    int getArchiveSize() const;
    int getTableSize() const;
};
#endif