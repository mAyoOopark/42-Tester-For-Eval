#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
    std::cout << "--- Basic polymorphism test ---" << std::endl;
    const Animal* a = new Animal();
    const Animal* d = new Dog();
    const Animal* c = new Cat();
    std::cout << std::endl;

    std::cout << d->getType() << std::endl;
    std::cout << c->getType() << std::endl;
    std::cout << std::endl;

    d->makeSound();
    c->makeSound();
    a->makeSound();
    std::cout << std::endl;

    delete a;
    delete d;
    delete c;

    std::cout << std::endl << "--- Copy / assignment tests ---" << std::endl;
    {
        Dog origDog;
        Dog copyDog(origDog);
        Dog assignDog;
        assignDog = origDog;

        Cat origCat;
        Cat copyCat(origCat);
        Cat assignCat;
        assignCat = origCat;
    }

    std::cout << std::endl << "--- Slicing test ---" << std::endl;
    {
        Animal sliced = Cat();
        sliced.makeSound(); // should call Animal::makeSound due to slicing
    }

    std::cout << std::endl << "--- WrongAnimal (non-virtual makeSound) test ---" << std::endl;
    {
        const WrongAnimal* wa = new WrongAnimal();
        const WrongAnimal* wc = new WrongCat();
        std::cout << std::endl;
        std::cout << wc->getType() << std::endl;
        wc->makeSound(); // should call WrongAnimal::makeSound (non-virtual behavior)
        wa->makeSound();
        delete wa;
        delete wc;
    }

    std::cout << std::endl << "All tests completed." << std::endl;
    return 0;
}
