#include <iostream>
#include <sstream>
#include <vector>

std::vector<std::string> inputsToVector_signals(std::string &inputs){
    std::string delimiter = "|";
    std::string start_coordinates = inputs.substr(0, inputs.find(delimiter)); 
    std::vector<std::string> vect;
    std::stringstream ss;
    ss << start_coordinates;
    for (std::string i; ss >> i;) {
        vect.push_back(i);
        if (ss.peek() == ',')
            ss.ignore();
    }
    return vect;
}

std::vector<std::string> inputsToVector_output(std::string &inputs){ //only take the second part of the signals
    std::string delimiter = "|";
    int pos = inputs.find(delimiter);
    std::string start_coordinates = inputs.substr(0, inputs.find(delimiter)); 
    std::string end_coordinates = inputs.substr(pos + delimiter.length());
    std::vector<std::string> vect;
    std::stringstream ss;
    ss << end_coordinates;
    for (std::string i; ss >> i;) {
        vect.push_back(i);
        if (ss.peek() == ',')
            ss.ignore();
    }
    return vect;
}