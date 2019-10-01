

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <fstream>
#include "calculate.hpp"
#include "firstAlgorithm.hpp"
#include <chrono>
#include <bitset>

using namespace std;

int main() {

    //string x_filename = "x_2^10.txt";
    //string y_filename = "y_2^10.txt";
    string x_filename = "ananas.txt";
    string y_filename = "banana.txt";

    //int block_size = pow(2, 7);
    int block_size = 6;

    run_test(block_size, x_filename, y_filename, "ztest.txt");

    //generate_string(pow(2, 6), "zx_2^6.txt");
    //generate_string(pow(2, 6), "zy_2^6.txt");

    cout << block_size << endl;

    int * a = new int[3];
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    for (int i = 0; i < 3; i++)
        cout << a[i];
    return 0;
}