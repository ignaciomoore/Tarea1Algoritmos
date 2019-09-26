//
// Created by Ignacio Moore on 25/09/2019.
//

#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <windef.h>
#include <algorithm>

int* calculate_block(int block_size, int* left_block, int* top_block, int* diagonal_block, int string_size, char* X,
        char* Y, int Y_char_index, int X_char_index) {

    int* result_block = new int[block_size];

    for (int w = 0; w < block_size; w++) {
        if (w == 0) {
            if (X[X_char_index] == Y[Y_char_index]) {
                result_block[0] = diagonal_block[block_size - 1];
            } else {
                int top_value = top_block[0];
                int left_value = left_block[block_size - 1];
                int first_minimum_value = std::min(top_value + 1, left_value + 1);
                int diagonal_value = diagonal_block[block_size - 1];
                int second_minimum_value = std::min(first_minimum_value, diagonal_value + 1);
                result_block[0] = second_minimum_value;
            }
        } else {
            if (X[X_char_index] == Y[Y_char_index]) {
                result_block[w] = top_block[w - 1];
            } else {
                int top_value = top_block[w];
                int left_value = result_block[w - 1];
                int first_minimum_value = std::min(top_value + 1, left_value + 1);
                int diagonal_value = top_block[w - 1];
                int second_minimum_value = std::min(first_minimum_value, diagonal_value + 1);
                result_block[w] = second_minimum_value;
            }
        }
        X_char_index++;
        if (X_char_index >= string_size) {
            X_char_index = 0;
            Y_char_index++;
        }
    }
    return result_block;
}
