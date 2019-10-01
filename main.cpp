


#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <fstream>
#include "calculate.hpp"
#include "firstAlgorithm.hpp"
#include <chrono>

using namespace std;



int main() {

    auto start = chrono::high_resolution_clock::now();

    string x_filename = "ananas.txt";
    string y_filename = "banana.txt";

    int block_size = 4;

    algorithm(block_size,x_filename, y_filename);

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<float > duration = end - start;

    cout << "Execution time: " << duration.count() << " s" << endl;

    return 0;
}