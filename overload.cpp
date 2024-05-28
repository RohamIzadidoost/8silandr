#include <iostream>
using namespace std;

struct MyInt {
    int value;
    MyInt(int v = 0) : value(v) {}

    MyInt operator+(const MyInt& rhs) const { return MyInt(value + rhs.value); }
    // Same as - * / 

    MyInt& operator++() { ++value; return *this; } // Prefix increment
    MyInt& operator--() { --value; return *this; } // Prefix decrement

    MyInt& operator+=(const MyInt& rhs) { value += rhs.value; return *this; }
    // same as -= *= /= %=

    bool operator==(const MyInt& rhs) const { return value == rhs.value; }
    // Same as != < <= > >=

    MyInt operator&(const MyInt& rhs) const { return MyInt(value & rhs.value); }
    // Same as | ^ ~
    
    MyInt& operator&=(const MyInt& rhs) { value &= rhs.value; return *this; }
    // Same as |= ^= <<= >>=
    
    MyInt operator<<(const int shift) const { return MyInt(value << shift); }
    MyInt operator>>(const int shift) const { return MyInt(value >> shift); }

    // Address-of operators
    MyInt* operator&() { return this; }
    const MyInt* operator&() const { return this; }
};

int main() {
    return 0;
}
