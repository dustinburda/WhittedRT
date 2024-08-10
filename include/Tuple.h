//
// Created by Dustin on 8/10/24.
//

#ifndef TUPLE_H
#define TUPLE_H

#include <array>
#include <string>
#include <initializer_list>

template<typename T, size_t N>
class Tuple {
public:
    explicit Tuple(std::initializer_list<T>& data) {
        if(data.size() != N) {
            std::string error_msg = "Must intitialize " + std::to_string(N) +
                                    "-tuple with " + std::to_string(N) + " elements, not "
                                    + std::to_string(data.size()) + " elements";
            throw std::logic_error(error_msg);
        }

        // Update compiler
        for(size_t index = 0; T& element : data) {
            data[index] = element;
            index++;
        }
    }

private:
    std::array<T, N> data_;
};

#endif //TUPLE_H
