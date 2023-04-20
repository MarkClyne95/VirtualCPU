#include <iostream>
#include <ostream>
#include <vector>

#include "instructions.hpp"

class CPU
{
    //CPU Registers
    int ip, sp, bp;

    int flag = 0;

    //memory regions
    std::vector<int> stack;
    std::vector<int> code;
    std::vector<int> data;

public:
    CPU(std::vector<int>&& instructions, int main_address, int datasize=100, int stacksize = 200): ip(main_address),
        sp(-1), bp(0),stack(stacksize), code(instructions), data(datasize)
    {
        
    }

    int fetch()
    {
        //grabbing the next instruction from the code vector
        return code[ip++];
    }

    void run()
    {
        std::cout << "CPU Started" << std::endl;

        ip = 0;
        int value;

        while(ip < code.size())
        {
            int instruction = fetch();

            switch(instruction)
            {
                case IPUSH:
                    value = code[ip++];
                    stack[++sp] = value;
                    break;

                case POP:
                    sp--;
                    break;

                case PRINT:
                    if(sp>-1)
                    {
                        std::cout << "Stack top: "<<stack[sp] <<std::endl;
                    } 
                    else{
                        std::cout << "Stack Empty!"<<std::endl;
                    }
                    break;

                case IADD:
                    stack[++sp]=code[ip++]+code[ip++];
                    break;

                case ISUB:
                    stack[++sp]=code[ip++]-code[ip++];
                    break;

                case IMUL:
                    stack[++sp]=code[ip++]*code[ip++];
                    break;
                            
                case IADDS:// instruction for when operands are on the stack! IADDS 0 1
                    stack[++sp]=stack[bp-code[ip++]]+stack[bp-code[ip++]];
                    break;

                case ISUBS:// instruction for when operands are on the stack! ISUBS 0 1
                    stack[++sp]=stack[bp-code[ip++]]-stack[bp-code[ip++]];
                    break;

                case IMULS:// instruction for when operands are on the stack! IMULS 0 1
                    stack[sp]=stack[bp-code[ip++]]*stack[bp-code[ip++]];
                    break;

                case JUMP:
                    ip=code[ip];
                    break;

                case JEQ:
                    if(flag==0)
                    {
                        ip=code[ip];
                    }
                    else{
                        ip++;
                    }
                    break;
                        
                case JLT:
                    if(flag<0)
                    {
                        ip=code[ip];
                    }
                    else{
                        ip++;
                    }
                    break;
                        
                case JGT:
                    if(flag>0)
                    {
                        ip=code[ip];
                    }
                    else{
                        ip++;
                    }
                    break;

                case ICMP:
                    value=code[ip++];
                    if(value == code[ip])
                    {
                        flag = 0;   
                    }
                    else if(value > code[ip])
                    {
                        flag =1;
                    }
                    else{
                        flag=-1;
                    }
                    ip++;
                    break;
                
                case ICMPS: // relative to the base pointer
                    value=stack[bp-code[ip++]];
                    int i =stack[bp-code[ip]];
                    if(value == i)
                    {
                        flag = 0;   
                    }
                    else if(value > i)
                    {
                        flag =1;
                    }
                    else{
                        flag=-1;
                    }
                    ip++;
                    break;

                case STORE:
                    data[code[ip++]]=stack[sp--];
                    break;

                case LOAD:
                    stack[++sp]=data[code[ip++]];
                    break; 
            }
        }
    }
};
