#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
std::tuple<int,int,int>  inputsToVector(std::string &inputs){
    std::vector<int> vect;
    std::stringstream ss(inputs);
    for (int i; ss >> i;) {
        vect.push_back(i);
        if (ss.peek() == ',')
            ss.ignore();
    }
    return std::make_tuple(vect[0],vect[1],vect[2]);
}