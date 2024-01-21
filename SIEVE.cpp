#include <iostream>
#include <gmpxx.h>

using std::cin;
using std::cout;
using std::endl;

int main(void)
{
    mpz_class a, b, c;

    a = 1234;
    b = "-5678";
    c = a + b;
    cout << "sum is " << c << endl;
    cout << "absolute value is " << abs(c) << endl;

    return 0;
}
