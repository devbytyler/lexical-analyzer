#include <string>

using namespace std;

enum TokenType{
  COMMA, 
  PERIOD, 
  Q_MARK, 
  LEFT_PAREN, 
  RIGHT_PAREN, 
  COLON, 
  COLON_DASH, 
  MULTIPLY, 
  ADD, 
  SCHEMES, 
  FACTS, 
  RULES, 
  QUERIES, 
  ID, 
  STRING, 
  COMMENT, 
  WHITESPACE, 
  UNDEFINED, 
  ENDFILE,
};

class Token
{
  public:
    Token(TokenType token_type, string value, int line_number);
    ~Token();
    string toString();

  private:
    string value;
    TokenType token_type;
    int line_number;
    string enumToString(TokenType tt);
};
