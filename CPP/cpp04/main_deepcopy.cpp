#include "Dog.hpp"
#include "Cat.hpp"
#include <iostream>

int main()
{
    std::cout << "--- Dog deep copy test ---" << std::endl;
    Dog d1;
    d1.setIdea(0, "Dog1 idea A");
    Dog d2 = d1; // copy constructor

    std::cout << "d1[0]: " << d1.getIdea(0) << std::endl;
    std::cout << "d2[0]: " << d2.getIdea(0) << std::endl;

    d1.setIdea(0, "Dog1 idea B");
    std::cout << "after modify d1" << std::endl;
    std::cout << "d1[0]: " << d1.getIdea(0) << std::endl;
    std::cout << "d2[0]: " << d2.getIdea(0) << std::endl;

    std::cout << "--- Dog assignment operator test ---" << std::endl;
    Dog d3;
    d3.setIdea(0, "d3 original");
    d3 = d1; // assignment
    std::cout << "d3[0]: " << d3.getIdea(0) << std::endl;

    std::cout << "--- Cat deep copy test ---" << std::endl;
    Cat c1;
    c1.setIdea(0, "Cat1 idea A");
    Cat c2 = c1;
    c1.setIdea(0, "Cat1 idea B");
    std::cout << "c1[0]: " << c1.getIdea(0) << std::endl;
    std::cout << "c2[0]: " << c2.getIdea(0) << std::endl;

    return 0;
}
