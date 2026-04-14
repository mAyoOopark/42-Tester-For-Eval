#include <iostream>
#include "Fixed.hpp"

int main( void ) 
{
    std::cout << "=== TEST 1: Basic functionality ===" << std::endl;
    Fixed a;
    Fixed b( a );
    Fixed c;
    c = b;
    
    std::cout << "a: " << a.getRawBits() << std::endl;
    std::cout << "b: " << b.getRawBits() << std::endl;
    std::cout << "c: " << c.getRawBits() << std::endl;

    std::cout << "\n=== TEST 2: setRawBits functionality ===" << std::endl;
    Fixed d;
    d.setRawBits(42);
    std::cout << "After setRawBits(42): " << d.getRawBits() << std::endl;
    
    Fixed e(d);
    std::cout << "Copy of d: " << e.getRawBits() << std::endl;

    std::cout << "\n=== TEST 3: Assignment chain ===" << std::endl;
    Fixed f;
    Fixed g;
    Fixed h;
    f.setRawBits(100);
    g = f;
    h = g;
    std::cout << "f: " << f.getRawBits() << ", g: " << g.getRawBits() << ", h: " << h.getRawBits() << std::endl;

    std::cout << "\n=== TEST 4: Self assignment ===" << std::endl;
    Fixed i;
    i.setRawBits(256);
    i = i;
    std::cout << "After self assignment: " << i.getRawBits() << std::endl;

    std::cout << "\n=== TEST 5: Multiple copies ===" << std::endl;
    Fixed j;
    j.setRawBits(1024);
    Fixed k(j);
    Fixed l(k);
    Fixed m(l);
    std::cout << "j: " << j.getRawBits() << ", k: " << k.getRawBits() 
              << ", l: " << l.getRawBits() << ", m: " << m.getRawBits() << std::endl;

    return 0;
}
