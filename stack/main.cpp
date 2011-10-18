#include <iostream>
#include "stack.cpp"

int main()
{
    Stack<int> stack;
    stack.push(365);
    std::cout << "min" << stack.minimum() << std::endl;
    std::cout << "max" << stack.maximum() << std::endl;
    stack.push(35);
    std::cout << "min" << stack.minimum() << std::endl;
    std::cout << "max" << stack.maximum() << std::endl;
    std::cout << stack.pop() << std::endl;
    stack.push(55);
    std::cout << "min" << stack.minimum() << std::endl;
    std::cout << "max" << stack.maximum() << std::endl;
    stack.push(5);
    std::cout << "min" << stack.minimum() << std::endl;
    std::cout << "max" << stack.maximum() << std::endl;
    stack.push(387);
    std::cout << "min" << stack.minimum() << std::endl;
    std::cout << "max" << stack.maximum() << std::endl;
    
    return 0;
}
