


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

    string x_filename;
    string y_filename;

    int block_size;

    //  TEST #1

    x_filename = "x_2^10.txt";
    y_filename = "y_2^10.txt";

    block_size = pow(2, 10);

    run_test(block_size, x_filename, y_filename, "A1_B2^10_S2^10_experiment.txt");

    //  TEST #2

    x_filename = "x_2^11.txt";
    y_filename = "y_2^11.txt";

    block_size = pow(2, 10);

    run_test(block_size, x_filename, y_filename, "A1_B2^10_S2^11_experiment.txt");

    //  TEST #3

    x_filename = "x_2^12.txt";
    y_filename = "y_2^12.txt";

    block_size = pow(2, 10);

    run_test(block_size, x_filename, y_filename, "A1_B2^10_S2^12_experiment.txt");

    //  TEST #4

    x_filename = "x_2^13.txt";
    y_filename = "y_2^13.txt";

    block_size = pow(2, 10);

    run_test(block_size, x_filename, y_filename, "A1_B2^10_S2^13_experiment.txt");

    return 0;
}