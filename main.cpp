#include <iostream>
#include "dough/core.hpp"


int main() {
    dough::Vector3 vec1{4,5,6};
    dough::Vector3 vec2{1,2,3};
    vec1 += vec2;
    std::cout << vec1.x << std::endl;
}