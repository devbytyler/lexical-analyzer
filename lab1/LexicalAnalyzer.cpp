#include "LexicalAnalyzer.h"

LexicalAnalyzer::LexicalAnalyzer(string file_name) : input(file_name)
{
}

LexicalAnalyzer::~LexicalAnalyzer(){}

void LexicalAnalyzer::tokenize()
{
  // input.print();
  while (input.now() != '\0') {
    best_type = UNDEFINED;
    best_string = "";
    char c = input.now();
    readSingleChar(c);
    readColonDash();
    readKeyword(c);
    readId(c);
    readString(c);
    readComment(c);
    readWhitespace(c);
    readNone(c);
    pushOn(best_type, best_string, input.getCurrentLine());
    input.advanceBy(best_string.length());
  }
  pushOn(ENDFILE, "", input.getCurrentLine());
  // while (!input.isAtEnd()){
  //   if (input.lookAhead(0) == '\0') break;
  //   if (isspace(input.now())) {
  //     input.advanceBy(1);
  //   }
  //   readSingleChar(input.now());
  //   readColonDash();
  //   readKeyword(input.now());
  //   readId(input.now());
  //   readString(input.now());
  //   readComment(input.now());
  //   readNone(input.now());
  //   Token next_token(temp_string, temp_token_type, input.getCurrentLine());
  //   if ((!isspace(temp_string[0])) && (temp_string.length() != 0)) tokens_list.push_back(next_token);
  //   input.advanceBy(temp_string.length());
  // }
  // Token last_token("", ENDFILE, input.getCurrentLine());
  // tokens_list.push_back(last_token);

  // string thing = "Hello\n\n";
  // cout << thing << endl;
  // cout << thing.length() << endl;

}

void LexicalAnalyzer::readSingleChar(char c)
{
  temp_string = c;
  switch (c){
    case '.': temp_token_type = PERIOD;
              break;
    case ',': temp_token_type = COMMA;
              break;
    case '?': temp_token_type = Q_MARK;
              break;
    case '(': temp_token_type = LEFT_PAREN;
              break;
    case ')': temp_token_type = RIGHT_PAREN;
              break;
    case ':': temp_token_type = COLON;
              break;
    case '*': temp_token_type = MULTIPLY;
              break;
    case '+': temp_token_type = ADD;
              break;                          
    default: temp_string = "";
  }
  setIfBetter(temp_string, temp_token_type);
}

void LexicalAnalyzer::readColonDash()
{
  if (temp_string == ":")
  {
    if (input.lookAhead(1) == '-')
    {
      temp_string = ":-";
      temp_token_type = COLON_DASH;
    }
  }
  setIfBetter(temp_string, temp_token_type);
}

void LexicalAnalyzer::readKeyword(char c)
{
  string keyword = "";
  switch (c){
    case 'S': {
      keyword = "Schemes";
      temp_token_type = SCHEMES;
    }
    break;
    case 'F': {
      keyword = "Facts";
      temp_token_type = FACTS;
    }
    break;
    case 'R': {
      keyword = "Rules";
      temp_token_type = RULES;
    }
    break;
    case 'Q': {
      keyword = "Queries";
      temp_token_type = QUERIES;
    }
    break;
  }
  for (int i = 0; i < keyword.length(); i++) {
    if ((input.lookAhead(i)) == keyword[i]) temp_string += keyword[i];
    else {
      keyword = "";
      temp_string = "";
    }
  }
  setIfBetter(temp_string, temp_token_type);
}

void LexicalAnalyzer::readId(char c)
{
  if (isalpha(c)) {
    // string temp_id_string;
    // temp_id_string += c;
    temp_string = c;
    int i = 1;
    while (isalnum(input.lookAhead(i))){
      temp_string += input.lookAhead(i);
      i++;
    }
    setIfBetter(temp_string, ID);
  }
}

void LexicalAnalyzer::readString(char c){
  if (c == '\'') {
    temp_string = c;
    bool endofstring = false;
    int i = 1;
    while (!endofstring){
      if ((input.lookAhead(i) == '\'') && (input.lookAhead(i+1) != '\'')){
        temp_string += '\'';
        endofstring = true;
        temp_token_type = STRING;
      }
      else if ((input.lookAhead(i) == '\'') && (input.lookAhead(i+1) == '\''))
      {
        temp_string += '\'';
        temp_string += '\'';
        i+= 2;
      }
      else{
        if (input.lookAhead(i) != '\0'){
          temp_string += input.lookAhead(i);
          i++;
        }
        else{
          temp_token_type = UNDEFINED;
          endofstring = true;
          setIfBetter(temp_string, temp_token_type);
          return;
        }
      }
    }
  }
  setIfBetter(temp_string, STRING);
}

void LexicalAnalyzer::readComment(char c){
  if (c == '#'){
    temp_string = c;
    int i = 1;
    bool multiline = false;
    bool endofcomment = false;
    if (input.lookAhead(1) == '|') {
      multiline = true;
      temp_string += '|';
      i++;
    }
    if (!multiline) {
      while(!endofcomment){
        if ((input.lookAhead(i) == '\n') || (input.lookAhead(i) == '\0')){
          endofcomment = true;
        }
        else{
          temp_string += input.lookAhead(i);
          i++;
        }
      }
      // temp_token_type = COMMENT;
    }
    else {
      while(!endofcomment){
        if ((input.lookAhead(i) == '|')&&(input.lookAhead(i+1) == '#')) {
          endofcomment = true;
          temp_string += "|#";
        }
        else if (input.lookAhead(i) == '\0') {
          endofcomment = true;
          temp_token_type = UNDEFINED;
          setIfBetter(temp_string, temp_token_type);
          return;
        }
        else {
          temp_string += input.lookAhead(i);
          i++;
        }
      }
    }
    temp_token_type = COMMENT;
  }
  setIfBetter(temp_string, temp_token_type);
}

void LexicalAnalyzer::readWhitespace(char c){
  if (isspace(c)) {
    temp_string = c;
    setIfBetter(temp_string, WHITESPACE);
  }
}

void LexicalAnalyzer::pushOn(TokenType tt, string v, int ln)
{
  if (tt != WHITESPACE) {
    Token newToken(tt, v, ln);
    tokens_list.push_back(newToken);
  }
}

void LexicalAnalyzer::readNone(char c)
{
  temp_string = c;
  temp_token_type = UNDEFINED;
  setIfBetter(temp_string, temp_token_type);
}

void LexicalAnalyzer::setIfBetter(string temp_string, TokenType temp_token_type){
  if (temp_string.length() > best_string.length()) {
    best_string = temp_string;
    best_type = temp_token_type;    
  } 
}

void LexicalAnalyzer::printV()
{
  for (int i = 0; i<tokens_list.size(); i++)
  {
    cout << tokens_list[i].toString() << endl;
  }
  cout <<"Total Tokens = "<< tokens_list.size();
}