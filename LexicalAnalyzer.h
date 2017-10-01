#include <iostream>
#include <vector>
#include <string>
#include <ctype.h>
#include "Token.h"
#include "InputStream.h"

using namespace std;

class LexicalAnalyzer
{
  private:
    vector<Token> tokens_list;
    InputStream input;
    string temp_string;
    string best_string;
    TokenType best_type;
    TokenType temp_token_type;

  public:
    LexicalAnalyzer(string file_name);
    ~LexicalAnalyzer();
    void tokenize();
    void readSingleChar(char c);
    void readColonDash();
    void readKeyword(char c);
    void readId(char c);
    void readString(char c);
    void readComment(char c);
    void readWhitespace(char c);
    void readNone(char c);
    void pushOn(TokenType tt, string v, int ln);
    void setIfBetter(string s, TokenType t);
    void printV();
};
