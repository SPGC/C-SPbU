#include <iostream>
#include <cassert>

#include "my_array.h"


using lab_13::my_array;

class TestClass{
public:
    TestClass(std::string s){
        data = s;
    }
    TestClass(){
        data = "Default String";
    }
    std::string toString(){
        return data;
    }
    bool operator==(TestClass &other){
        return this->data == other.data;
    }
    bool operator!=(TestClass &other){
        return !(*this == other);
    }
private:
    std::string data;
};

template<typename T, std::size_t N>
bool testSizes(){
    my_array<T, N> array;
    return array.size() == N && sizeof(array) == N * sizeof(T);
}

template<typename T, std::size_t N>
bool testFillAndIndexing(T element){
    my_array<T, N> array;
    array.fill(element);
    bool flag = true;
    for(std::size_t i; i < array.size(); i++){
        if(array[i] != element){
            flag = false;
            break;
        }
    }
    return flag;
}

template<typename T, std::size_t N>
bool testAtAndIndexing(T elementForFill, T element, std::size_t indexToReplace){
    my_array<T, N> array;
    array.fill(elementForFill);
    if(indexToReplace >= array.size()){
        try{
            array.at(indexToReplace);
            return false;
        } catch(std::out_of_range &e){
            return true;
        }
    }
    array[indexToReplace] = element;
    return array.at(indexToReplace) == element;
}

int main(){

    // Тесты на память
    bool buffer = testSizes<int, 239>();
    assert(buffer);
    buffer = testSizes<char, 12>();
    assert(buffer);
    buffer = testSizes<long, 15>();
    assert(buffer);
    buffer = testSizes<TestClass, 18>();
    assert(buffer);
    buffer = testSizes<float, 13>();
    assert(buffer);

    // Тесты на fill 
    buffer = testFillAndIndexing<int, 239>(239);
    assert(buffer);
    buffer = testFillAndIndexing<char, 12>('a');
    assert(buffer);
    buffer = testFillAndIndexing<long, 15>(239l);
    assert(buffer);
    buffer = testFillAndIndexing<TestClass, 18>(TestClass(std::string("239 однажды - 239 навсегда")));
    assert(buffer);
    buffer = testFillAndIndexing<float, 13>(239.0);
    assert(buffer);

    // Тесты на at и indexing
    buffer = testAtAndIndexing<int, 239>(239, 533, 30);
    assert(buffer);
    buffer = testAtAndIndexing<char, 12>('a', 'b', 13);
    assert(buffer);
    buffer = testAtAndIndexing<long, 15>(239l, 30l, 533);
    assert(buffer);
    buffer = testAtAndIndexing<TestClass, 18>(TestClass(std::string("239 однажды - 239 навсегда")), TestClass(std::string("Mafia 239")), 10);
    assert(buffer);
    buffer = testAtAndIndexing<float, 13>(239.0, 366, 10);
    assert(buffer);
}   