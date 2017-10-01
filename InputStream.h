#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class InputStream 
{
  private:
    string str;
    int currentLoc;
    int currentLine;
    bool atEnd;

  public:
    InputStream(string file_name);
    ~InputStream();

    void buildString(string file_name);
    void advanceBy(int i);
    char now();
    char lookAhead(int i);
    bool isAtEnd();




    void print();
    int getCurrentLoc();
    int getCurrentLine();
};