#include <iostream>
#include "LexicalAnalyzer.h"

#include <string>


using namespace std;

bool hasInput(int arg_count) {
  return (arg_count > 1) ? true : false;
}

int main(int argc, char* argv[]) 
{
  if (!hasInput(argc)) {
    cout << "No file name entered. Exiting...";
    return -1;
  }
  
  LexicalAnalyzer lexer(argv[1]);
  lexer.tokenize();
  lexer.printV();
}