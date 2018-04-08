//
// Created by dat on 08/04/2018.
//

#ifndef INTOUCH_TEST_V1_CSTRINGCALCULATOR_H
#define INTOUCH_TEST_V1_CSTRINGCALCULATOR_H

#include <memory>

typedef struct DELIMITER_DETAIL{
    std::string delimiter;
    size_t pos;
};

class CStringCalculator {
public:
    static std::shared_ptr<CStringCalculator> getInstance();
    int add(std::string& s);
    bool isNumber(std::string& s);
private:
    static std::shared_ptr<CStringCalculator> instance;

    CStringCalculator() { instance = nullptr; }
};


#endif //INTOUCH_TEST_V1_CSTRINGCALCULATOR_H
