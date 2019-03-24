#include "GenStack.cpp"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
char getOther(char c);
int main(int argc, char** argv)
{
  if(argc >= 2)
  {
    string fileName = argv[1];                                                  //get the file name from command line argument
    ifstream file;
    file.open(fileName, ifstream::in);                                          //open the file
    GenStack<char> stack;                                                       //create a stack of chars
    int lineCount = 0;                                                          //keep track of line numbers (for errors)
    string line;
    while(!file.eof())
    {
      getline(file, line);
      lineCount++;
      for(int i = 0; i < line.size(); ++i)                                      //loop thru every char in the line
      {
        if(line[i] == '{' || line[i] == '(' || line[i] == '[')                  //push opening delimeters onto stack
          stack.push(line[i]);
        else if (line[i] == '}' || line[i] == ')' || line[i] == ']')
        {
          if(!stack.isEmpty() && getOther(line[i]) == stack.peek())             //if matching delimeters, pop opening delim off stack
            stack.pop();
          else if(stack.isEmpty())                                              //if closing delim without opening (stack empty), error
          {
            cout << "error on line " << lineCount << ", missing " << getOther(line[i]) << endl;
            return 1;
          }
          else                                                                  //if closing delim without opening, error
          {
            cout << "error on line " << lineCount << ", missing " << stack.peek() << endl;
            return 1;
          }
        }
      }
    }
    if(stack.isEmpty())                                                         //all delimemters correct
      cout << "ok!" << endl;
    else                                                                        //reach the end with a non empty stack
    {
      char miss;
      while(!stack.isEmpty())                                                   //get the first occurence of an error, in caase stack size > 1
        miss = stack.pop();
      cout << "error on line " << --lineCount << ", missing " << getOther(miss) << endl;
      return 1;
    }
    file.close();
    return 0;
  }
}
char getOther(char c)                                                           //get the opposite delimeter
{
  if(c == '(')
    return ')';
  else if(c == '{')
    return '}';
  else if(c == '[')
    return ']';
  else if(c == ')')
    return '(';
  else if(c == '}')
    return '{';
  else if(c == ']')
    return '[';
}
