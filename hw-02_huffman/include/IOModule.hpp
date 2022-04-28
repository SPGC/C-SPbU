#include <string>
#include <vector>
#include <map>

#include "Node.hpp"
#include "CoderDecoder.hpp"
#include "Exception.hpp"

#ifndef IO
#define IO

using namespace std;

class IOModule{
private:
    map<pair<int, int>, unsigned char> * readCodeFromFile(ifstream *);
    void writeCodeToFile(map<unsigned char, pair<int, int>> *, ofstream *);
    void writeInteger(ofstream *, int);
    int readInteger(ifstream *);
    int fileSize;
    int archiveSize;
    int tableSize;
public:
    IOModule(/* args */);
    ~IOModule();
    void decodedInCodedOut(string, string, map<unsigned char, pair<int, int>> *);
    void codedInDecodedOut(string, string);
    vector<Node*> * constructNodes(string);
    int getFileSize() const;
    int getArchiveSize() const;
    int getTableSize() const;
};
#endif