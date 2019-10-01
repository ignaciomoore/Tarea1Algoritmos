


#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <fstream>
#include "calculate.hpp"
#include "firstAlgorithm.hpp"

using namespace std;



int main() {

    string x_filename = "ananas.txt";
    string y_filename = "banana.txt";

    int block_size = 4;

    algorithm(block_size, x_filename, y_filename);


    return 0;
}