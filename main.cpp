#include <iostream>

#include "CStringCalculator.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::string test_1="1,2,3";
    std::cout<<CStringCalculator::getInstance()->add(test_1)<<std::endl;
    std::string test_2="//[,][;]\n1,2;3\n4";
    std::cout<<CStringCalculator::getInstance()->add(test_2)<<std::endl;
    std::string test_3="//[,][;]\n1,-2;3\n-4";
    std::cout<<CStringCalculator::getInstance()->add(test_3)<<std::endl;
    return 0;
}