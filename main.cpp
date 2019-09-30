


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
    int* top_block = new int[block_size];
    int* left_block = new int[block_size];
    int* diagonal_block = new int[block_size];
    int* current_block = new int[block_size];
    string X;   //  MAKE STRING BLOCK
    string Y;   //  MAKE STRING BLOCK

    string filename = "two_strings.txt";    //  JUST FOR TESTING

    pair<string, string> XeY = get_strings(filename);
    X = XeY.first;
    Y = XeY.second;

    int string_length = get_string_size(filename);

    int blocks_per_line = ceil((double) string_length/block_size);
    int total_steps = string_length * blocks_per_line;
    int number_of_values = string_length % (blocks_per_line - 1);   //  NUMBER OF VALUES ON LIMIT BLOCK
    int* limit_block = new int[number_of_values];   //  TRY TO DELETE THIS MEMORY SPACE AND USE CURRENT_BLOCK

    int x_index;
    int y_index;
    int minimum;
    int top_step;

    for (int i = 0; i < string_length; i++) {
        for (int j = 0; j < blocks_per_line; j++) {
            if (i == 0) {
                if (j == (blocks_per_line - 1)) {
                    x_index = calculate_X_coordinate(step, block_size, string_length);
                    for (int k = 0; k < number_of_values; k++) {
                        limit_block[k] = x_index + k;
                    }
                    write_block(limit_block, number_of_values, step);
                    step++;
                }
                else {
                    x_index = calculate_X_coordinate(step, block_size, string_length);
                    for (int k = 0; k < block_size; k++) {
                        current_block[k] = x_index + k;
                    }
                    write_block(current_block, block_size, step);
                    step++;
                }
            }
            else if (j == 0) {
                top_block = read_block(get_top_step(step, blocks_per_line), block_size);
                for (int k = 0; k < block_size; k++) {
                    if (k == 0)
                        current_block[k] = calculate_Y_coordinate(step, block_size, string_length);
                    else {
                        x_index = calculate_X_coordinate(step, block_size, string_length) + k;
                        y_index = calculate_Y_coordinate(step, block_size, string_length);
                        if (X[x_index] == Y[y_index])
                            current_block[k] = top_block[k - 1];
                        else {
                            minimum = min(top_block[k] + 1, current_block[k - 1] + 1);
                            minimum = min(minimum, top_block[k - 1] + 1);
                            current_block[k] = minimum;
                        }
                    }
                }
                write_block(current_block, block_size, step);
                step++;
            }
            else if (j == (block_size - 1)) {
                top_step = get_top_step(step,blocks_per_line);
                top_block = read_block(top_step, number_of_values);
                left_block = read_block((step - 1), block_size);
                diagonal_block = read_block(top_step - 1, block_size);
                x_index = calculate_X_coordinate(step, block_size, string_length);
                y_index = calculate_Y_coordinate(step,block_size,string_length);
                limit_block = calculate_limit_block(block_size, left_block, top_block, diagonal_block,
                                                    string_length, X, Y, y_index, x_index);
                write_block(limit_block, number_of_values, step);
                step++;
            }
            else {
                top_step = get_top_step(step,blocks_per_line);
                top_block = read_block(top_step, block_size);
                left_block = read_block((step - 1), block_size);
                diagonal_block = read_block(top_step - 1, block_size);
                x_index = calculate_X_coordinate(step, block_size, string_length);
                y_index = calculate_Y_coordinate(step, block_size, string_length);
                current_block = calculate_block(block_size, left_block, top_block, diagonal_block, string_length,
                                                X, Y, y_index, x_index);
                write_block(current_block, block_size, step);
                step++;
            }
        }
    }

    int* last_block = new int[block_size];
    last_block = read_block(total_steps, number_of_values);

    cout << last_block[number_of_values - 1];

    return 0;
}