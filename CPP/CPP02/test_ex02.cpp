#include <iostream>
#include "Fixed.hpp"

int main( void ) 
{
    std::cout << "=== TEST 1: Comparison operators ===" << std::endl;
    Fixed a(5.05f);
    Fixed b(2.0f);
    Fixed c(5.05f);
    
    std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;
    std::cout << "a > b: " << (a > b ? "true" : "false") << std::endl;
    std::cout << "a < b: " << (a < b ? "true" : "false") << std::endl;
    std::cout << "a >= b: " << (a >= b ? "true" : "false") << std::endl;
    std::cout << "a <= b: " << (a <= b ? "true" : "false") << std::endl;
    std::cout << "a == c: " << (a == c ? "true" : "false") << std::endl;
    std::cout << "a != b: " << (a != b ? "true" : "false") << std::endl;

    std::cout << "\n=== TEST 2: Arithmetic +/- ===" << std::endl;
    Fixed d(5.0f);
    Fixed e(3.0f);
    Fixed f = d + e;
    Fixed g = d - e;
    
    std::cout << "d = " << d << ", e = " << e << std::endl;
    std::cout << "d + e = " << f << std::endl;
    std::cout << "d - e = " << g << std::endl;

    std::cout << "\n=== TEST 3: Arithmetic *// ===" << std::endl;
    Fixed h(2.5f);
    Fixed i(4.0f);
    Fixed j = h * i;
    Fixed k = h / i;
    
    std::cout << "h = " << h << ", i = " << i << std::endl;
    std::cout << "h * i = " << j << std::endl;
    std::cout << "h / i = " << k << std::endl;

    std::cout << "\n=== TEST 4: Pre-increment/decrement ===" << std::endl;
    Fixed l(0.0f);
    std::cout << "Initial: " << l << std::endl;
    std::cout << "++l: " << ++l << std::endl;
    std::cout << "++l again: " << ++l << std::endl;
    std::cout << "--l: " << --l << std::endl;
    std::cout << "Value after: " << l << std::endl;

    std::cout << "\n=== TEST 5: Post-increment/decrement ===" << std::endl;
    Fixed m(1.0f);
    std::cout << "Initial: " << m << std::endl;
    std::cout << "m++: " << m++ << std::endl;
    std::cout << "Value after m++: " << m << std::endl;
    std::cout << "m--: " << m-- << std::endl;
    std::cout << "Value after m--: " << m << std::endl;

    std::cout << "\n=== TEST 6: Mixed arithmetic ===" << std::endl;
    Fixed n(10.0f);
    Fixed o(3.0f);
    Fixed p = (n + o) - Fixed(2.0f);
    std::cout << "(10 + 3) - 2 = " << p << std::endl;

    std::cout << "\n=== TEST 7: Comparison chain ===" << std::endl;
    Fixed q(5.0f);
    Fixed r(10.0f);
    Fixed s(7.5f);
    
    std::cout << "q = " << q << ", r = " << r << ", s = " << s << std::endl;
    std::cout << "q < s < r: " << ((q < s && s < r) ? "true" : "false") << std::endl;
    std::cout << "s > q && s < r: " << ((s > q && s < r) ? "true" : "false") << std::endl;

    std::cout << "\n=== TEST 8: Min/Max with non-const ===" << std::endl;
    Fixed t(3.0f);
    Fixed u(7.0f);
    std::cout << "t = " << t << ", u = " << u << std::endl;
    std::cout << "min(t, u) = " << Fixed::min(t, u) << std::endl;
    std::cout << "max(t, u) = " << Fixed::max(t, u) << std::endl;

    std::cout << "\n=== TEST 9: Min/Max with const ===" << std::endl;
    const Fixed v(2.5f);
    const Fixed w(8.5f);
    std::cout << "v = " << v << ", w = " << w << std::endl;
    std::cout << "min(v, w) = " << Fixed::min(v, w) << std::endl;
    std::cout << "max(v, w) = " << Fixed::max(v, w) << std::endl;

    std::cout << "\n=== TEST 10: Epsilon increment ===" << std::endl;
    Fixed x(0.0f);
    std::cout << "Starting at: " << x << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << "After " << (i+1) << " increments: " << ++x << std::endl;
    }

    std::cout << "\n=== TEST 11: Negative numbers ===" << std::endl;
    Fixed y(-5.5f);
    Fixed z(-2.0f);
    std::cout << "y = " << y << ", z = " << z << std::endl;
    std::cout << "y + z = " << (y + z) << std::endl;
    std::cout << "y - z = " << (y - z) << std::endl;
    std::cout << "y * z = " << (y * z) << std::endl;

    std::cout << "\n=== TEST 12: Zero cases ===" << std::endl;
    Fixed a0(0.0f);
    Fixed b0(1.0f);
    std::cout << "0 + 1 = " << (a0 + b0) << std::endl;
    std::cout << "0 - 1 = " << (a0 - b0) << std::endl;
    std::cout << "0 * 1 = " << (a0 * b0) << std::endl;
    std::cout << "0 == 0: " << (a0 == Fixed(0.0f) ? "true" : "false") << std::endl;

    return 0;
}
