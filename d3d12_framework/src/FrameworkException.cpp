#include "FrameworkException.h"
using namespace std;

FrameworkException::FrameworkException(const string& explaination)
:m_explaination(explaination)
{
}

const char* FrameworkException::what() const throw()
{
  return m_explaination.c_str();
}
