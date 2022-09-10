#include <iostream>

using namespace std;

class NoneSquareMatrixException : public exception
{
public:
    explicit NoneSquareMatrixException(const char* message) : exception(message)
    {}
};