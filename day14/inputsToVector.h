#ifndef INPUTSTOVECTOR_H
#define INPUTSTOVECTOR_H
#include <iostream>
#include <vector>
#endif

std::pair<std::string,char> inputsToRules(std::string &inputs){
    std::string delimiter = " -> ";
    int pos = inputs.find(delimiter);
    std::string start = inputs.substr(0, inputs.find(delimiter)); 
    char end = inputs[(pos + delimiter.length())];
    std::pair<std::string,char> rules(start,end);
    return rules;
}