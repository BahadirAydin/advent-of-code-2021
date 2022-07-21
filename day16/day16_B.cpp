#include <fstream> 
#include <vector>
#include <iostream>
#include <bitset> 
#include <algorithm>
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
unsigned long long int decodeHelper(std::string binaryForm, long unsigned int &currentPos){
  std::string packetType = binaryForm.substr(currentPos+3,3);
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
    for(unsigned int i=0;i<groups.size();i++)
      resultStr+= groups[i];
    long long int value = std::bitset<64>(resultStr).to_ullong(); // I have lost about 2 hours because I set the bitset<32>. Lesson learned.
    return value;
  }
  else{
    char lengthTypeId = binaryForm[currentPos];
    currentPos++;
    std::vector<long long int> values;
    if(lengthTypeId == '0'){
      unsigned long long length = std::bitset<32>(binaryForm.substr(currentPos,15)).to_ullong();
      currentPos+=15;
      long unsigned int tmp = currentPos+length;
      while(currentPos < tmp)
        values.push_back(decodeHelper(binaryForm,currentPos));
    }
    else if(lengthTypeId == '1'){
      unsigned long long count = std::bitset<32>(binaryForm.substr(currentPos,11)).to_ullong();
      currentPos+=11;
      for(long long unsigned int i=0;i<count;i++)
        values.push_back(decodeHelper(binaryForm,currentPos));
    }

    if(packetType == "000"){
      long long int sum=0;
      for(long long int x : values) sum+=x;
      return sum;
    }
    else if(packetType == "001"){
      long long int product=1;
      for(long long int x : values) product*=x;
      return product;
    }
    else if(packetType == "010")
      return *std::min_element(values.begin(),values.end());
    else if(packetType == "011")
      return *std::max_element(values.begin(),values.end());
    else if(packetType == "101")
      return  values[0] > values[1];
    else if(packetType == "110")
      return values[0] < values[1];
    else if(packetType == "111")
      return  values[0] == values[1];
  }
  return 0;
}
unsigned long long int decoder(std::string inputFileName){
  std::string line;
  std::ifstream Input(inputFileName);
  std::getline(Input,line);
  std::string binaryForm;
  for(char c : line){
    binaryForm += hex_char_to_bin(c);
  }
  long unsigned int currentPos=0;
  return decodeHelper(binaryForm,currentPos);
}
int main(){
  std::cout << decoder("input.txt") << std::endl;
  return 0;
}