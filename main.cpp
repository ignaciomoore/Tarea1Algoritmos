


#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <fstream>
#include "calculate.hpp"
#include "firstAlgorithm.hpp"

using namespace std;



int main() {

    string x_filename = "x_2^13.txt";
    string y_filename = "y_2^13.txt";
    //string x_filename = "x100test.txt";
    //string y_filename = "y100test.txt";

    int x_string_length = get_string_size(x_filename);
    int y_string_length = get_string_size(y_filename);

    cout << y_string_length << endl;
    cout << x_string_length << endl;
    return 0;
}