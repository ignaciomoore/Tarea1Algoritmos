


#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include "calculate.hpp"
#include "firstAlgorithm.hpp"

using namespace std;

int main() {

    int step = 1;
    int block_size = 3;    //  JUST FOR TESTING
    int* top_block;
    int* left_block;
    int* diagonal_block;
    int* current_block;
    string X;
    string Y;

    string filename = "two_strings.txt";    //  JUST FOR TESTING

    pair<string, string> XeY = get_strings(filename);
    X = XeY.first;
    Y = XeY.second;

    int string_length = X.length();
    int blocks_per_line = ceil((double) string_length/block_size);
    int total_steps = string_length * blocks_per_line;

    for (int i = 0; i < string_length; i++) {
        for (int j = 0; j < blocks_per_line; j++) {
            if (i == 0) {
                for (int k = 0; k < block_size; k++) {
                    current_block[k + j] = k + j;
                }
                write_block(current_block, block_size, step);
                step++;
            }
            else if (j == 0) {
                top_block = read_block(get_top_step(step, blocks_per_line), block_size);
                for (int k = 0; k < block_size; k++) {
                    if (k == 0)
                        current_block[k] = calculate_Y_coordinate(step, block_size, string_length);
                    else {
                        int x_index = calculate_X_coordinate(step, block_size, string_length);
                        int y_index = calculate_Y_coordinate(step, block_size, string_length);
                        if (X[x_index] == Y[y_index])
                            current_block[k] = top_block[k - 1];
                        else {
                            int minimum = min(top_block[k] + 1, current_block[k - 1] + 1);
                            minimum = min(minimum, top_block[k - 1] + 1);
                            current_block[k] = minimum;
                        }
                    }
                }
                step++;
            }
            //  DO STUFF HERE
        }
    }

    return 0;
}