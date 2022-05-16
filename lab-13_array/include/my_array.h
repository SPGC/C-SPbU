#ifndef MY_ARRAY_H_
#define MY_ARRAY_H_

#include <cstddef>
#include <stdexcept>


namespace lab_13 {

template<typename T, std::size_t N>
class my_array {
public:
    my_array() = default;

    T &at(std::size_t index){
        if (index >= N){
            throw std::out_of_range("Array index out of range.");
        }
        return data[index];
    }
    const T &at(std::size_t index) const{
        if (index >= N){
            throw std::out_of_range("Array index out of range.");
        }
        return data[index];
    }

    T &operator[](std::size_t index){
        return data[index];
    }
    const T &operator[](std::size_t index) const{
        return data[index];
    }

    bool empty() const{
        return N == 0;
    }
    std::size_t size() const{
        return N;
    }

    void fill(const T &val){
        for (std::size_t i = 0u; i < N; ++i){
            data[i] = val;
        }
    }
private:
    T data[N];
};

}  // namespace lab_13

#endif  // MY_ARRAY_H_
