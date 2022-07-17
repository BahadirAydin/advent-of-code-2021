#include <iostream>
#include <sstream>
#include <vector>

std::vector<int> inputsToVector(std::string &inputs){
    std::string delimiter = "->";
    int pos = inputs.find(delimiter);
    std::string start_coordinates = inputs.substr(0, inputs.find(delimiter)); 
    std::string end_coordinates = inputs.substr(pos + delimiter.length());
    std::vector<int> vect;
    std::stringstream ss;
    ss << start_coordinates << end_coordinates;
    for (int i; ss >> i;) {
        vect.push_back(i);
        if (ss.peek() == ',')
            ss.ignore();
    }
    return vect;
}