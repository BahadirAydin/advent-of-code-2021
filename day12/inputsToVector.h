#ifndef INPUTSTOVECTOR_H
#define INPUTSTOVECTOR_H
#include <iostream>
#include <sstream>
#include <vector>
#endif


std::vector<std::string> inputsToVector(std::string &inputs){
    std::string delimiter = "-";
    int pos = inputs.find(delimiter);
    std::string start = inputs.substr(0, inputs.find(delimiter)); 
    std::string end = inputs.substr(pos + delimiter.length());
    std::vector<std::string> vect;
    vect.push_back(start);
    vect.push_back(end);
    return vect;
}