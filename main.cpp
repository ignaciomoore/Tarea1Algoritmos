


#include <iostream>
#include <algorithm>
#include <cstring>
#include "calculate.hpp"
#include "firstAlgorithm.hpp"

using namespace std;

int main() {

    int left[] = {5,4,3};
    int diagonal[] = {4,3,2};
    int top[] = {1,2,2};

    int block_size = sizeof(top)/ sizeof(*top);

    char x[] = " ananas";
    char y[] = " banana";

    int string_size = strlen(x);

    int jj = 3;
    int ii = 5;

    int* r;
    r = calculate_block(block_size,left,top,diagonal,string_size,x,y,ii,jj);

    std::cout << r[0] << " ";
    std::cout << r[1] << " ";
    std::cout << r[2] << std::endl;
    std::cout << "Expected 2 1 2" << std::endl;

    int* read;
    read = read_block(20,block_size);

    cout << read[0] << " ";
    cout << read[1] << " ";
    cout << read[2] << endl;

    return 0;
}