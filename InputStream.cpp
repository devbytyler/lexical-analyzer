#include "InputStream.h"



InputStream::InputStream(string file_name)
{
  currentLoc = 0;
  currentLine = 0;
  atEnd = false;
  buildString(file_name);
}

InputStream::~InputStream()
{

}

char InputStream::now()
{
  if (currentLoc >= str.length()){
    return '\0';
  }
  else{
    return str[currentLoc];
  }
}

void InputStream::buildString(string file_name)
{
  ifstream infile;
  stringstream ss;
  string line;
  infile.open(file_name);
  while (getline(infile, line)) {
    ss << line << endl;
  }
  str = ss.str();
  // str.pop_back();
  infile.close();
  if (str.length() > 0) currentLine++;
}

void InputStream::print()
{
  cout << str;
}

int InputStream::getCurrentLoc()
{
 return currentLoc;
}

int InputStream::getCurrentLine()
{
 return currentLine;
}

bool InputStream::isAtEnd(){
  return atEnd;
}

void InputStream::advanceBy(int t)
{
  for (int i = 0; i < t ; i++){
    // cout << now() << endl;
    if (now() == '\n')
    {
      // cout << "INCREMENTING LINE" << endl;
      currentLine++;
    }
    currentLoc++;
  }
}

char InputStream::lookAhead(int i)
{
  if (currentLoc + i < str.length()) {
    return str[currentLoc + i];
  }
  else {
    return '\0';
  }
}