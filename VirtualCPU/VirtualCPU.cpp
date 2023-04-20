#include <iostream>
#include <vector>
#include "Source/instructions.hpp"
#include "Source/CPU.cpp"

std::vector<int> fabricate_instructions()
{
    //read file or throw an exception;
    return {
        IPUSH, 10,
        IPUSH, 20,
        STORE, 1,
        LOAD, 1,
        PRINT,
        POP,
        PRINT,
        POP,
        PRINT,
        PRINT,
        HALT
    };
}

int main(int argc, char* argv[])
{
    
    std::vector<int> program;
    //read file and get instructions!
    try{
        
        program=fabricate_instructions();

        CPU vm(std::move(program),0,120,300);
        vm.run();
        // std::cout<<"starting cpu!"<<program[0]<<program[1];
    }
    catch(char* msg)
    
    {
        std::cout << "Error!";
        std::cout << msg;
    }
    return 0;
}
