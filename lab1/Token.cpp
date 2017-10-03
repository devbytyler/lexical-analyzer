#include "Token.h"

Token::Token(TokenType token_type, string value, int line_number)
{
  this->value = value;
  this->token_type = token_type;
  this->line_number = line_number;
}

Token::~Token()
{

}

string Token::toString()
{
  return '(' + enumToString(token_type) + ",\"" + value + "\"," + to_string(line_number) + ")";
}

string Token::enumToString(TokenType tt)
{
  switch(tt) {
    case COMMA: return "COMMA";
    case PERIOD: return "PERIOD";
    case Q_MARK: return "Q_MARK";
    case LEFT_PAREN: return "LEFT_PAREN";
    case RIGHT_PAREN: return "RIGHT_PAREN";
    case COLON: return "COLON";
    case COLON_DASH: return "COLON_DASH";
    case MULTIPLY: return "MULTIPLY";
    case ADD: return "ADD";
    case SCHEMES: return "SCHEMES";
    case FACTS: return "FACTS";
    case RULES: return "RULES";
    case QUERIES: return "QUERIES";
    case ID: return "ID";
    case STRING: return "STRING";
    case COMMENT: return "COMMENT";
    case WHITESPACE: return "WHITESPACE";
    case UNDEFINED: return "UNDEFINED";
    case ENDFILE: return "EOF";
    default: return "NONE";
  }
}