//
// Created by dat on 08/04/2018.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include <set>

#include "CStringCalculator.h"

std::shared_ptr<CStringCalculator> CStringCalculator::instance= nullptr;

std::shared_ptr<CStringCalculator> CStringCalculator::getInstance(){
    if(instance== nullptr){
        instance=std::shared_ptr<CStringCalculator>(new CStringCalculator());
    }
    return instance;
}

int CStringCalculator::add(std::string &s) {
    if(s.length()<=0){
        return 0;
    }else if(s.length()==1){
        return std::atoi(s.c_str());
    }

    std::vector<std::string> delimiters;
    delimiters.push_back("\n");

    std::vector<DELIMITER_DETAIL> delimiterDetails;

    auto parseDelimiterString=[](std::string& s, std::vector<std::string>& delimiters){
        size_t open_pos=0;
        size_t close_pos=0;
        while(true) {
            open_pos = s.find("[", open_pos);
            close_pos= s.find("]", close_pos);
            if(open_pos==std::string::npos || close_pos==std::string::npos){
                break;
            }
            auto length = close_pos - open_pos-1;
            if(length==0){
                break;
            }else{
                //std::cout<<s.substr(open_pos+1, length)<<std::endl;
                delimiters.push_back(s.substr(open_pos+1, length));
                close_pos++;
                open_pos=close_pos;
            }
        }
    };

    // "//[abc][def]\n...."
    if(s.substr(0,2)=="//"){
        auto first_of_n=s.find_first_of("\n");
        std::string delimiterString=s.substr(2, first_of_n-2);
//        std::cout<<delimiterString<<std::endl;
        s=s.substr(first_of_n+1);
        parseDelimiterString(delimiterString, delimiters);
    }else{
        delimiters.push_back(",");
    }

    //Remove duplication
    std::set<std::string> set;
    std::for_each(delimiters.begin(), delimiters.end(), [&set](const std::string& s){
        set.insert(s);
    });
    delimiters.clear();
    delimiters.assign(set.begin(), set.end());

    auto find_all_appearance=[](std::string& s, std::vector<DELIMITER_DETAIL>& details, const std::string& delimiter){
        size_t position=0;
        while(position<s.length()){
            position=s.find(delimiter,position);
            if(position==std::string::npos){
                break;
            }else{
                DELIMITER_DETAIL delimiterDetail;
                delimiterDetail.pos=position;
                delimiterDetail.delimiter=delimiter;
                details.push_back(delimiterDetail);
                position++;
            }
        }
    };

    std::for_each(delimiters.begin(), delimiters.end(), [&find_all_appearance, &delimiterDetails, &s](const std::string& delimiter){
       find_all_appearance(s, delimiterDetails, delimiter);
    });

    std::sort(delimiterDetails.begin(), delimiterDetails.end(), [](const DELIMITER_DETAIL& a, const DELIMITER_DETAIL& b)->bool{
        return a.pos<b.pos;
    });

    std::string negativeString="";

    size_t position=0;
    std::vector<int> values;
    auto size=delimiterDetails.size();
    for(int i=0; i<size; i++){
        auto length=delimiterDetails.at(i).pos-position;
//        std::cout<<s.substr(position, length)<<std::endl;
        std::string temp=s.substr(position, length);
        if(isNumber(temp)) {
            auto value=std::atoi(temp.c_str());
            if(value>=0) {
                values.push_back(value);
            }else{
                negativeString+=","+temp;
            }
        }
        position=delimiterDetails.at(i).pos+delimiterDetails.at(i).delimiter.length();
    }
//    std::cout<<s.substr(delimiterDetails.at(size-1).pos+1)<<std::endl;
    if(size>0){
        std::string temp=s.substr(delimiterDetails.at(size-1).pos+1);
        if(isNumber(temp)) {
            auto value=std::atoi(temp.c_str());
            if(value>=0) {
                values.push_back(value);
            }else{
                negativeString+=","+temp;
            }
        }
    }

    if(negativeString.length()>0){
        negativeString=negativeString.substr(1);
    }

    try{
        if(negativeString.length()>0){
            throw std::runtime_error(negativeString);
        }
    }catch(std::exception& ex){
        std::cout<<"negatives not allowed "<<ex.what()<<std::endl;
        return 0;
    }

    int sum=0;
    std::for_each(values.begin(), values.end(), [&sum](const int& a){
        sum+=a;
    });

    return sum;
}

bool CStringCalculator::isNumber(std::string &s) {
    if(s.find_first_not_of("-0123456789")!=std::string::npos){
        return false;
    }

    size_t minus=0;
    int count=0;
    while(true){
        minus=s.find("-",minus);
        if(minus!=std::string::npos){
            count++;
        }else{
            break;
        }
        if(count >1){
            return false;
        }
        minus++;
    }

    return true;
}