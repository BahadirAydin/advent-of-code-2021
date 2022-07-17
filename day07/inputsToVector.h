#include <iostream>
#include <sstream>
#include <vector>

std::vector<int> inputsToVector(std::string &inputs){
    std::vector<int> vect;
    std::stringstream ss(inputs);
    for (int i; ss >> i;) {
        vect.push_back(i);
        if (ss.peek() == ',')
            ss.ignore();
    }
    return vect;
}