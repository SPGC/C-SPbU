#include "CoderDecoder.hpp"


//Codder

// Constructor
Codder::Codder(map<unsigned char, pair<int32_t, int>> *code){
    this->codeTable = code;
}

// Code
pair<int32_t, int> Codder::code(unsigned char value){
    return (*codeTable)[value];
}


//Decoder
Decoder::Decoder(map<pair<int32_t, int>, unsigned char> *code){
    this->codeTable = code;
}

// Decode
//  returns:
//      [value, not used bytes or not fully used bytes, amount of not used not fully used bytes, amount of first byte not used bits]
pair<unsigned char, pair<unsigned char*, pair<int32_t, int>>> Decoder::decode(unsigned char * inputBytes, int firstByteNotUsedBits, int amountsOFBytes){
    int32_t buffer = (inputBytes[0] >> (firstByteNotUsedBits - 1) ) & 1;
    int i = 0;
    int counter = 1;
    while (true){
        if (counter == firstByteNotUsedBits){
            i++;
        }
        if (codeTable->find(make_pair(buffer, counter)) != codeTable->end()){
            return make_pair((*codeTable->find(make_pair(buffer, counter))).second, 
                              make_pair(inputBytes + i, 
                              make_pair(amountsOFBytes - i, (i) * 8 + firstByteNotUsedBits - counter)));
        }
        buffer = buffer << 1;
        if(i == 0){
            buffer |= (inputBytes[0] >> (firstByteNotUsedBits - counter - 1)) & 1;
            counter++;
        } else {
            buffer |= (inputBytes[i] >> ((i) * 8 + firstByteNotUsedBits - counter - 1)) & 1;
            counter++;
            if((counter - firstByteNotUsedBits) % 8 == 0){
                i++;
            }
            if(i == amountsOFBytes){
                if(codeTable->find(make_pair(buffer, counter)) != codeTable->end()){
                    return make_pair((*codeTable->find(make_pair(buffer, counter))).second, 
                                make_pair(inputBytes + i - 1, 
                                make_pair(0, 0)));
                } else {
                    return make_pair(0, 
                                make_pair(nullptr, 
                                make_pair(0, 0)));
                }
            }
        }
    }
}
