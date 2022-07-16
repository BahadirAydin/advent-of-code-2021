#include "Board.h"

// This could have been done in much less code but for educative purposes I will leave it as it is since this version is much structured and also good for OOP concepts, pointers. (ie: the function "show" is only used for debugging and is not necessary but i chose not to delete it.)

int bingoGame(std::string inputFileName){
  std::string line,inputs;
  std::ifstream Input(inputFileName);
  std::vector<Board*>Boards;
  std::getline(Input,line);
  inputs = line;
  
  Board* current_board;
  while (std::getline (Input, line)) {
    if(line.size() == 0){
      Board* new_board = new Board();
      Boards.push_back(new_board);
      current_board = new_board;
    }
    else{
      current_board -> addRow(line);
    }
  }
  Input.close(); 
  int result = -1;
  int lastMark;
  std::vector<int> winners;
  std::vector<int> markList = inputsToVector(inputs);
  for(int markInt : markList){
    for(Board* board : Boards)
      board -> mark(markInt);
    int winner = winnerChecker(Boards,winners); //This overloaded winnerChecker function also checks if the Board had won the game before.
    while(winner >= 0){ //There might be more than one winners added after one mark.
      winners.push_back(winner);
      lastMark = markInt;
      winner = winnerChecker(Boards,winners);
    }
    if(winners.size() == Boards.size()) // no need to do calculation anymore if this happens.
      break;
  }
  result = Boards[winners.back()] -> sumAllExceptMarked() * lastMark; 
  for(Board* board : Boards)
    delete board;  
  return result;
}
int main(){
  std::cout << bingoGame("input.txt") << std::endl;
  return 0;
}