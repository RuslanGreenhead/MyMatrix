#include <iostream>

using namespace std;
class A
{
public:
    A() {cout << "I was constructed!" << endl;}
    A(int a) {cout << "I was constructed with one param!" << endl;}
    ~A() {cout << "I was destructed" << endl;}
    static void print() {cout << "PRINT" << endl;}
};

int main() {
    A (b);
    A::print();
    cout << "SHIS" << endl;
    return 0;
}
