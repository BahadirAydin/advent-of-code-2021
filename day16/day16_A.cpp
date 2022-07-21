#include <fstream> 
#include <vector>
#include <iostream>
#include <bitset> 
//SOLUTION USING RECURSION

const char* hex_char_to_bin(char c){
  //this function is a copy-paste from stack overflow.
    switch(c){
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
    }
  return "NO";
}



void decodeHelper(std::string binaryForm,int &sum, int &currentPos){
  std::string packetVersion = binaryForm.substr(currentPos,3);
  std::string packetType = binaryForm.substr(currentPos+3,3);
  auto versionNumber = std::bitset<32>(packetVersion).to_ullong();
  sum+= versionNumber;   
  //std::cout << "VERSION: " << versionNumber << " " << packetVersion<< std::endl;
  currentPos += 6;   
  if(packetType == "100"){
    std::vector<std::string> groups;
    std::string resultStr; 
    while(currentPos < binaryForm.size()){
      groups.push_back(binaryForm.substr(currentPos+1,4));
      currentPos+=5;
      if(binaryForm[currentPos-5] == '0'){
        break;
      }
    }
    /*for(unsigned int i=0;i<groups.size();i++)
      resultStr+= groups[i];
    auto value = std::bitset<32>(resultStr).to_ullong();
    std::cout << value << std::endl;*/
  }
  else{
    char lengthTypeId = binaryForm[currentPos];
    currentPos++;
    if(lengthTypeId == '0'){
      auto length = std::bitset<32>(binaryForm.substr(currentPos,15)).to_ullong();
      currentPos+=15;
      int tmp = currentPos+length;
      while(currentPos < tmp)
        decodeHelper(binaryForm,sum,currentPos);
    }
    else if(lengthTypeId == '1'){
      auto count = std::bitset<32>(binaryForm.substr(currentPos,11)).to_ullong();
      currentPos+=11;
      for(int i=0;i<count;i++){
        decodeHelper(binaryForm,sum,currentPos);
      }
    }
  }
}


long int decoder(std::string inputFileName){
  std::string line;
  std::ifstream Input(inputFileName);
  std::getline(Input,line);
  std::string binaryForm;
  for(char c : line){
    binaryForm += hex_char_to_bin(c);
  }
  int sum =0,currentPos=0;
  decodeHelper(binaryForm,sum,currentPos);

  return sum;
}
int main(){
  std::cout << decoder("input.txt") << std::endl;
  return 0;
}