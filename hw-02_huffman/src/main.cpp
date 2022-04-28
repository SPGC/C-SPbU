#include <iostream>
#include <fstream>

#include "IOModule.hpp"
#include "HuffmanTree.hpp"
#include "Exception.hpp"


pair<int, pair<int, int>> code(string in, string out){
    IOModule io;
    vector<Node *> *v = io.constructNodes(in);
    HuffmanTree tree;
    tree.generateTree(v);
    map<unsigned char, pair<int, int>> * dict = tree.genereateCode();
    io.decodedInCodedOut(in, out, dict);
    return make_pair(io.getFileSize(), make_pair(io.getArchiveSize(), io.getTableSize()));
}

pair<int, pair<int, int>> decode(string in, string out){
    IOModule io;
    io.codedInDecodedOut(in, out);
    return make_pair(io.getFileSize(), make_pair(io.getArchiveSize(), io.getTableSize()));
}

int main(int argn, char **argv){
    if(argn != 6){
        throw WrongAmountOFArguments();
    }
    string in;
    string out;
    char mode;
    string s;
    int i = 1;
    while(i < argn){     
        string s(argv[i]);
        if(s.compare("-c") == 0){
            mode = 'c';
            i++;
        } else if(s.compare("-u") == 0){
            mode = 'u';
            i++;
        } else if((s.compare("-f")) == 0 || (s.compare("--file") == 0)){
            in = string(argv[i + 1]);
            i += 2;
        } else if((s.compare("-o") == 0) || (s.compare("--output") == 0)){
            out = string(argv[i + 1]);
            i += 2;
        } else {
            throw WrongArgument();
        }
    }
    pair<int, pair<int, int>> result;
    ifstream inStream(in);
    char *forFlag = (char *)malloc(1);
    inStream.read(forFlag,1);
    if(inStream.eof()){
        cout<< 0 << "\n" << 0 << "\n" << 0 << "\n";
        inStream.close();
        ofstream outStream(out);
        outStream.close();
        free(forFlag);
        return 0;
    }
    inStream.close();
    free(forFlag);
    if(mode == 'c'){
        result = code(in, out);
        cout << result.first << "\n" << result.second.first << "\n" << result.second.second << "\n";
    } else {
        result = decode(in, out);
        cout << result.second.first << "\n" << result.first << "\n" << result.second.second << "\n";
    }
}