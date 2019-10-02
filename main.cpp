

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
    string x_filename = "zx_2^7.txt";
    string y_filename = "zy_2^7.txt";

    int block_size = pow(2, 7);
    //int block_size = 6;

    run_test(block_size, x_filename, y_filename, "ztest.txt");

    //generate_string(pow(2, 7), "zx_2^7.txt");
    //generate_string(pow(2, 7), "zy_2^7.txt");
/**
    int * a = new int [block_size];
    for (int i = 0; i < get_string_size(y_filename); i++) {
        a = read_block(i+1, block_size);
        for (int j = 0; j < block_size; j++) {
            cout << a[j] << " ";
        }
        cout << endl;
    }
*/
    cout << "Block size: " << block_size << endl;

    return 0;
}