#include <fstream>
#include <iostream>
#include <vector>

// Credit for the idea: https://www.youtube.com/watch?v=Eswmo7Y7C4U

int type_0_constants[7] = {6, 11, 5, 6, 8, 9, 13};
int type_1_constants[7] = {1, 16, 8, 16, 13, 6, 6};
int digit_types[14] = {0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1};

std::vector<std::string> getData(std::string inputFileName) {
  std::vector<std::string> arr;
  std::string line;
  std::ifstream Input(inputFileName);
  while (std::getline(Input, line)) {
    arr.push_back(line);
  }

  return arr;
}
bool check(int digit, int *res) {
  std::string str = std::to_string(digit);
  int arr[7];
  for (int j = 0; j < 7; j++)
    arr[j] = str[j] - '0';
  int z = 0;
  int countType0 = 0;
  int countType1 = 0;
  for (int i = 0; i < 14; i++) {
    if (digit_types[i] == 0) {
      z = z * 26 + arr[countType0] + type_0_constants[countType0];
      res[i] = arr[countType0];
      if (res[i] > 9 || res[i] < 1)
        return false;
      countType0++;
    } else {
      res[i] = (z % 26) - type_1_constants[countType1];
      z = z / 26;
      countType1++;
      if (res[i] > 9 || res[i] < 1)
        return false;
    }
  }
  return true;
}

int *execute() {
  int *arr = new int[14];
  int digit = 9999999;
  while (digit > 1000000) {
    if (check(digit, arr))
      return arr;
    digit--;
  }
  return arr;
}

int main() {
  int *arr = new int[14];
  int *ptr = execute();
  for (int i = 0; i < 14; i++) {
    std::cout << ptr[i];
  }
  std::cout << std::endl;
  return 0;
}