#include <iostream>
#include <stdexcept>
using namespace std;
template <class E>
class GenStack
{
  public:
    GenStack();
    GenStack(int mySize);
    ~GenStack();
    void push(E elem);
    E pop();
    E peek();
    int getSize();
    bool isFull();
    bool isEmpty();
    int size;
    int top;
    E* myArray;
};
class StackEmptyException: public runtime_error
{
public:
  StackEmptyException(const string& err) : runtime_error(err) {};
};
template <class E>
GenStack<E>::GenStack()
{
  myArray = new E[128];
  size = 128;
  top = -1;
}
template <class E>
GenStack<E>::GenStack(int mySize)
{
  myArray = new E[mySize];
  size = mySize;
  top = -1;
}
template <class E>
GenStack<E>::~GenStack()
{
  delete[] myArray;
}
template <class E>
void GenStack<E>::push(E elem) //adjust size if full
{
  if(!isFull())
    myArray[++top] = elem;
  else
  {
    size *= 2;
    E* temp = new E[size];
    for(int i = 0; i < size/2; ++i)
      temp[i] = myArray[i];
    myArray = temp;
    delete[] temp;
  }
}
template <class E>
E GenStack<E>::pop() //throw an exception if empty
{
  if(!isEmpty())
    return myArray[top--];
  else
    throw StackEmptyException("popping from empty stack!");
}
template <class E>
E GenStack<E>::peek() //throw excception if empty
{
  if(!isEmpty())
    return myArray[top];
  else
    throw StackEmptyException("peeking from empty stack!");
}
template <class E>
int GenStack<E>::getSize()
{
  return top;
}
template <class E>
bool GenStack<E>::isFull()
{
  return top == size-1;
}
template <class E>
bool GenStack<E>::isEmpty()
{
  return top == -1;
}
