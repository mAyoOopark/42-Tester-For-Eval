#include <iostream>
#include "Fixed.hpp"

int main( void ) 
{
    std::cout << "=== TEST 1: Int conversion ===" << std::endl;
    Fixed a(0);
    Fixed b(1);
    Fixed c(42);
    Fixed d(-5);
    Fixed e(1000);
    
    std::cout << "Fixed(0): " << a << " -> toInt: " << a.toInt() << std::endl;
    std::cout << "Fixed(1): " << b << " -> toInt: " << b.toInt() << std::endl;
    std::cout << "Fixed(42): " << c << " -> toInt: " << c.toInt() << std::endl;
    std::cout << "Fixed(-5): " << d << " -> toInt: " << d.toInt() << std::endl;
    std::cout << "Fixed(1000): " << e << " -> toInt: " << e.toInt() << std::endl;

    std::cout << "\n=== TEST 2: Float conversion ===" << std::endl;
    Fixed f(0.0f);
    Fixed g(1.5f);
    Fixed h(42.42f);
    Fixed i(-3.14f);
    Fixed j(0.5f);
    Fixed k(0.001f);
    
    std::cout << "Fixed(0.0f): " << f << std::endl;
    std::cout << "Fixed(1.5f): " << g << " -> toInt: " << g.toInt() << std::endl;
    std::cout << "Fixed(42.42f): " << h << " -> toInt: " << h.toInt() << std::endl;
    std::cout << "Fixed(-3.14f): " << i << " -> toInt: " << i.toInt() << std::endl;
    std::cout << "Fixed(0.5f): " << j << std::endl;
    std::cout << "Fixed(0.001f): " << k << std::endl;

    std::cout << "\n=== TEST 3: Precision test ===" << std::endl;
    Fixed l(2.5f);
    Fixed m(-2.5f);
    Fixed n(9.99f);
    
    std::cout << "Fixed(2.5f): " << l << " -> toInt: " << l.toInt() << std::endl;
    std::cout << "Fixed(-2.5f): " << m << " -> toInt: " << m.toInt() << std::endl;
    std::cout << "Fixed(9.99f): " << n << " -> toInt: " << n.toInt() << std::endl;

    std::cout << "\n=== TEST 4: Copy and convert ===" << std::endl;
    Fixed o(5.5f);
    Fixed p(o);
    std::cout << "Original: " << o << ", Copy: " << p << std::endl;
    std::cout << "Original toInt: " << o.toInt() << ", Copy toInt: " << p.toInt() << std::endl;

    std::cout << "\n=== TEST 5: Assignment and convert ===" << std::endl;
    Fixed q;
    q = Fixed(7.25f);
    std::cout << "After assignment of Fixed(7.25f): " << q << " -> toInt: " << q.toInt() << std::endl;

    std::cout << "\n=== TEST 6: Large numbers ===" << std::endl;
    Fixed r(10000);
    Fixed s(10000.5f);
    std::cout << "Fixed(10000): " << r << std::endl;
    std::cout << "Fixed(10000.5f): " << s << std::endl;

    return 0;
}
