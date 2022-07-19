#ifndef INPUTSTOVECTOR_H
#define INPUTSTOVECTOR_H
#include <iostream>
#include <sstream>
#include <vector>
#endif



std::pair<int,int> inputsToPairXY(std::string &inputs){
    std::string delimiter = ",";
    int pos = inputs.find(delimiter);
    std::string start = inputs.substr(0, inputs.find(delimiter)); 
    std::string end = inputs.substr(pos + delimiter.length());
    std::pair<int,int>  pair;
    pair.first = (std::stoi(start));
    pair.second = (std::stoi(end));
    return pair;
}

std::pair<char,int> inputsToPair(std::string &inputs){
    std::string delimiter = "=";
    int pos = inputs.find(delimiter);
    std::string start = inputs.substr(0, inputs.find(delimiter)); 
    std::string end = inputs.substr(pos + delimiter.length());
    std::pair<char,int> pair;
    pair.first = start[start.size()-1];
    pair.second = std::stoi(end);
    return pair;
}