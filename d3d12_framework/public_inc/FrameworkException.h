#ifndef FRAMEWORK_EXCEPTION_H
#define FRAMEWORK_EXCEPTION_H

#include <exception>
#include <string>

class FrameworkException : public std::exception
{
  public:
    FrameworkException(const std::string& explaination);

    const char* what() const throw();

  private:
    std::string m_explaination;
};

#endif /* FRAMEWORK_EXCEPTION_H */