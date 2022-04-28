#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <bitset>
#include <climits>

#include "IOModule.hpp"


//Private Methods
void IOModule::writeInteger(ofstream *out, int data){
    unsigned char c;
    char *outChar = (char *)malloc(1);
    for (size_t i = 0; i < sizeof(int); i++){
        c = (data >> ((sizeof(int) - i - 1) * 8)) % 256;
        *outChar = c;
        out->write(outChar, 1);
    }
    free(outChar);
}

void IOModule::writeCodeToFile(map<unsigned char, pair<int, int>> * dict, ofstream * out){
    int size = dict->size();
    writeInteger(out, fileSize);
    writeInteger(out, size);
    char *outChar = (char*) malloc(1);
    for (map<unsigned char, pair<int, int>>::iterator i = dict->begin(); i != dict->end(); i++){
        *outChar = (*i).first;
        out->write(outChar, 1);
        writeInteger(out, (*i).second.first);
        writeInteger(out, (*i).second.second);
    }   
    free(outChar);
    tableSize = 2 * sizeof(int) + size * (2 * sizeof(int) + 1);
}

int IOModule::readInteger(ifstream * in){
    char *inChar = (char *)malloc(1);
    int result = 0;
    for (size_t i = 0; i < sizeof(int); i++){
        in->read(inChar, 1);
        result = result << 8;
        result |= (unsigned char)(*inChar);
    }
    free(inChar);
    return result;
}

map<pair<int, int>, unsigned char> * IOModule::readCodeFromFile(ifstream * in){
    fileSize = readInteger(in);
    int size = readInteger(in);
    tableSize = 2 * sizeof(int) + size * (2 * sizeof(int) + 1);
    char *inChar = (char *)malloc(1);
    int code;
    int codeLength;
    map<pair<int, int>, unsigned char> *dict = new map<pair<int, int>, unsigned char>();
    for (int i = 0; i < size; i++){
        in->read(inChar, 1);
        code = readInteger(in);
        codeLength = readInteger(in);
        dict->insert(make_pair(make_pair(code,codeLength),(unsigned char)(*inChar)));
    }
    free(inChar);
    return dict;
}

IOModule::IOModule(/* args */){
}

IOModule::~IOModule(){
}

int IOModule::getTableSize() const{
    return tableSize;
}

int IOModule::getFileSize() const{
    return fileSize;
}

int IOModule::getArchiveSize() const{
    return archiveSize;
}

void IOModule::decodedInCodedOut(string inFile, string outFile, map<unsigned char, pair<int, int>> * dict){
    ofstream out(outFile, ios::binary);
    ifstream in(inFile, ios::binary);
    if (!(out.is_open() && in.is_open())){
        throw FileOpenException();
    }
    writeCodeToFile(dict, &out);
    char *c = (char *)malloc(1);
    char *outChar = (char *)malloc(1);
    Codder codder(dict);
    pair<int, int> result;
    unsigned char outBuffer = 0;
    int counter = 0;
    while(true){
        in.read(c, 1);
        if(in.eof()){
            break;
        }
        result = codder.code((unsigned char)*c);
        int i = result.second;
        while(i > 0){
            outBuffer = outBuffer << 1;
            outBuffer |= (result.first >> (i - 1)) & 1;
            counter++;
            if(counter == 8){
                *outChar = outBuffer;
                out.write(outChar, 1);
                outBuffer = 0;
                counter = 0;
            }
            i--;
        }
    }
    if(counter != 0){
        outBuffer = outBuffer << (8 - counter);
        *outChar = outBuffer;
        out.write(outChar, 1);
    }
    archiveSize = out.tellp();
    in.close();
    out.close();
    free(outChar);
    free(c);
    delete dict;
}

void IOModule::codedInDecodedOut(string inFile, string outFile){
    ofstream out(outFile, ios::binary);
    ifstream in(inFile, ios::binary);
    if (!(out.is_open() && in.is_open())){
        throw FileOpenException();
    }
    map<pair<int, int>, unsigned char> * codeTable = readCodeFromFile(&in);
    Decoder decoder(codeTable);
    pair<unsigned char, pair<unsigned char*, pair<int, int>>> decoded;
    int toRead = 4;
    int currentSize = 4;
    int firstByteNotUsedBits = 8;
    char *buffer = (char *)malloc(4);
    unsigned char *toDecode = (unsigned char *)malloc(5);
    char * outChar = (char *)malloc(1);
    archiveSize = in.tellg();
    for(int i = 0; i < toRead; i++){
        in.read(buffer + i, 1);
        if(!in.eof()){
            archiveSize = in.tellg();
        }
    }
    for (int i = 0; i < 4; i++){
        toDecode[i] = buffer[i];
    }
    int counter = 0;
    while(true){
        decoded = decoder.decode(toDecode, firstByteNotUsedBits, currentSize);
        *outChar = decoded.first;
        out.write(outChar, 1);
        counter++;
        currentSize = decoded.second.second.first;
        firstByteNotUsedBits = decoded.second.second.second;
        if(firstByteNotUsedBits != 0){
            for (int i = 0; i < currentSize; i++){
                toDecode[i] = decoded.second.first[i];
            }
            if(firstByteNotUsedBits != 8){
                toRead = 5 - currentSize;
            } else {
                toRead = 4 - currentSize;
            }
            if(toRead != 0){
                for(int i = 0; i < toRead; i++){
                    in.read(buffer + i, 1);
                    if(!in.eof()){
                        archiveSize = in.tellg();
                    }
                }
                if(in.eof()){
                    break;
                }
                for (int i = currentSize; i < currentSize + toRead; i++){
                    toDecode[i] = buffer[i - currentSize];
                }
                currentSize += toRead;
            } 
        } else {
            toRead = 4;
            firstByteNotUsedBits = 8;
                for(int i = 0; i < toRead; i++){
                    in.read(buffer + i, 1);
                    if(!in.eof()){
                        archiveSize = in.tellg();
                    }
                }
            if(in.eof()){
                break;
            }
            currentSize = 4;
            for (int i = 0; i < currentSize; i++){
                toDecode[i] = decoded.second.first[i];
            }
        }
    }
    while(currentSize > 0){
        decoded = decoder.decode(toDecode, firstByteNotUsedBits, currentSize);
        if(counter >= fileSize){
            break;
        }
        *outChar = decoded.first;
        out.write(outChar, 1);
        counter++;
        currentSize = decoded.second.second.first;
        firstByteNotUsedBits = decoded.second.second.second;
        for (int i = 0; i < currentSize; i++){
                toDecode[i] = decoded.second.first[i];
            }
    }
    in.close();
    out.close();
    free(outChar);
    free(toDecode);
    free(buffer);
    delete codeTable;
}

//Checked!
vector<Node*> * IOModule::constructNodes(string inFile){
    ifstream in(inFile, ios::binary);
    if (!in.is_open()){
        throw FileOpenException();
    }
    char *c = (char *)malloc(1);
    map<char, Node *> buffer;
    fileSize = 0;
    while(true){
        in.read(c, 1);
        if(in.eof()){
            break;
        }
        if(buffer.find(*c) != buffer.end()){
            buffer[*c]->increaseAmount();
        } else {
            buffer[*c] = new Node((unsigned char)(*c), 1);
        }
    }
    vector<Node *> * result = new vector<Node *>();
    for(map<char, Node *>::iterator i = buffer.begin(); i != buffer.end(); i++){
        result->push_back((*i).second);
        fileSize += (*i).second->getAmount();
    }
    sort(result->begin(), result->end(), [](Node * n1, Node * n2){return *n2 < *n1;});
    free(c);
    in.close();
    return result;
}