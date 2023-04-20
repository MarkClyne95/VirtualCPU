// #pragma once
// #include <iostream>
// #include <ostream>
// #include <vector>
//
// class CPU
// {
//     //CPU Registers
//     int ip, sp, bp;
//
//     int flag = 0;
//
//     //memory regions
//     std::vector<int> stack;
//     std::vector<int> code;
//     std::vector<int> data;
//
// public:
//     CPU(std::vector<int>&& instructions, int main_address, int datasize=100, int stacksize = 200): ip(main_address),
//         sp(-1), bp(0),stack(stacksize), code(instructions), data(datasize)
//     {
//         
//     }
//
// private:
//     int fetch();
//
//     void run();
// };
