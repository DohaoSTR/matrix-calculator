#include <iostream>

using namespace std;

class IndexOutOfRangeException : public exception
{
public:
    explicit IndexOutOfRangeException(const char* message) : exception(message)
    {}
};