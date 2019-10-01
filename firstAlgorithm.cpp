//
// Created by Ignacio Moore on 26/09/2019.
//

#include <cstdio>
#include <fstream>
#include <string>
#include <cmath>
#include <iostream>
#include <chrono>
#include "calculate.hpp"
#include "firstAlgorithm.hpp"
#include <bitset>
#include <cstring>

using namespace std;
/**
 * Writes a block on an output file
 *
 * @param block
 *      The block to be written
 * @param block_size
 * @param step
 *      The step in which the block was calculated
 */
void write_block(int* block, int block_size, int step) {
    string filename = "calculated_block_" + to_string(step) + ".txt";
    ofstream outfile (filename);
    string binary_value;

    for (int i = 0; i < block_size; i++) {
        binary_value = bitset<32> (block[i]).to_string();
        outfile << binary_value;
    }

    outfile.close();
    /**
    string filename = "calculated_block_" + to_string(step) + ".txt";
    ofstream outfile (filename);
    string out_block = "";

    for (int i = 0; i < block_size; i++)
        out_block = out_block + to_string(block[i]);

    outfile << out_block;
    outfile.close();
     */
}

/**
 * Reads a block from a text file and returns the block as an int array
 *
 * @param step
 *      The step in which the block was written
 * @param block_size
 * @return
 *      The block as an int array
 */
int* read_block(int step, int block_size) {

    ifstream infile;
    string filename = "calculated_block_" + to_string(step) + ".txt";
    infile.open(filename);
    string string_cell;
    char* cell = new char[32];
    int * block = new int[block_size];

    for (int i = 0; i < block_size; i++) {
        infile.read(cell, 32);
        string_cell = string(cell);
        int int_cell = stoi(string_cell, 0, 2);
        block[i] = int_cell;
    }
    infile.close();
    return block;
    /**
    ifstream infile;
    string filename = "calculated_block_" + to_string(step) + ".txt";
    infile.open(filename);
    string cell;
    int* block = new int[block_size];

    infile >> cell;
    for (int i = 0; i < block_size; i++) {
        block[i] = stoi(cell.substr(i,1));
    }

    infile.close();
    return block;
     */
}

/**
 * Calculates the X coordinate of the matrix where a block begins.
 *
 * @param step
 *      The step where the block is calculated
 * @param block_size
 * @param string_length
 *      The length of the string on top of the matrix
 * @return
 *      The X coordinate where the block begins in the matrix
 */
int calculate_X_coordinate(int step, int block_size, int string_length) {
    int blocks_per_line = ceil((double) string_length/block_size);
    return ((step - 1) % blocks_per_line) * block_size;


    //(step % blocks_per_line - 1) * block_size;    ORIGINAL
    //((step - 1) % blocks_per_line) * block_size;
}

/**
 * Calculates the Y coordinate of the matrix where a block begins.
 *
 * @param step
 *      The step where the block is calculated
 * @param block_size
 * @param string_length
 *      The length of the string on the side of the matrix
 * @return
 *      The Y coordinate where the block begins in the matrix
 */
int calculate_Y_coordinate(int step, int block_size, int string_length) {
    int blocks_per_line = ceil((double) string_length/block_size);
    return (step - 1) / blocks_per_line;
}

/**
 * Returns the two strings in the text file, one string is on top of the other.
 *
 * @param x_filename
 *      Name of the file that contains the strings
 * @return
 *      Pair of strings
 */
pair<string, char* > get_strings(string x_filename, string y_filename, int step, int string_length, int block_size) {

    string X_string;
    //char* Y_string;
    char* Y_string = new char[1];

    int x = calculate_X_coordinate(step,block_size, string_length);
    int y = calculate_Y_coordinate(step,block_size, string_length);

    ifstream x_file;
    x_file.open(x_filename, ios::binary);

    char* xxx = new char [block_size];
    x_file.seekg (x, ios::beg);
    x_file.read (xxx, block_size);
    x_file.close();

    X_string = string(xxx);

    ifstream y_file;
    y_file.open(y_filename, ios::binary);

    y_file.seekg (y, ios::beg);
    y_file.read (Y_string, 1);
    y_file.close();



    return make_pair(X_string, Y_string);
}

/**
 * Calculates the step in which the top block was calculated
 *
 * @param step
 *      The step of the current block
 * @param blocks_per_line
 *      The amount of blocks per line of the matrix
 * @return
 *      The step in which the top block was calculated
 */
int get_top_step(int step, int blocks_per_line) {
    return step - blocks_per_line;
}

/**
 * Returns the length of the line in the file
 *
 * @param filename
 *      Name of the file
 * @return
 *      Line length
 */
int get_string_size(string filename) {
    ifstream infile(filename, ios::binary);
    const auto begin = infile.tellg();
    infile.seekg(0, ios::end);
    const auto end = infile.tellg();
    return end - begin;
}

void generate_string(int size, string filename) {

    ofstream string_file;
    string_file.open(filename);

    for (int i = 0; i < size; i++) {
        int c = rand() % 26 + 65;
        string_file << char(c);
    }

    string_file.close();
}

int algorithm(int block_size, string x_filename, string y_filename) {

    int step = 1;

    int* top_block = new int[block_size];
    int* left_block = new int[block_size];
    int* diagonal_block = new int[block_size];
    int* current_block = new int[block_size];

    int string_length = get_string_size(x_filename);
    cout << "string length: " << string_length << endl;

    pair<string, char*> XeY;

    int blocks_per_line = ceil((double) string_length/block_size);
    cout << "blocks per line: " << blocks_per_line << endl;
    int total_steps = string_length * blocks_per_line;
    cout << "total steps: " << total_steps << endl;
    int number_of_values = string_length % block_size;   //  NUMBER OF VALUES ON LIMIT BLOCK
    cout << "number of values on limit blocks: " << number_of_values << endl;

    int* limit_block = new int[number_of_values];   //  TRY TO DELETE THIS MEMORY SPACE AND USE CURRENT_BLOCK

    int x_index;
    int y_index;
    int minimum;
    int top_step;

    string X_string;
    char Y_char;

    for (int i = 0; i < string_length; i++) {
        for (int j = 0; j < blocks_per_line; j++) {
            if (i == 0) {
                if (j == 0) {
                    for (int k = 0; k < block_size; k++) {
                        top_block[k] = k + 1;
                    }
                    XeY = get_strings(x_filename, y_filename, step, string_length, block_size);
                    X_string = XeY.first;
                    X_string = X_string.substr(0, block_size);
                    Y_char = *(XeY.second);
                    current_block = calculate_block(block_size, 1, top_block,
                                                    0, string_length, X_string, Y_char);
                    write_block(current_block, block_size, step);
                    step++;
                }
                else if (j == (blocks_per_line - 1) && (number_of_values != 0)) {
                    x_index = calculate_X_coordinate(step, block_size, string_length);
                    for (int k = 0; k < number_of_values; k++)
                        top_block[k] = x_index + 1 + k;
                    left_block = read_block(step - 1, block_size);
                    XeY = get_strings(x_filename, y_filename, step, string_length, number_of_values);
                    X_string = XeY.first;
                    X_string = X_string.substr(0, number_of_values);
                    Y_char = *(XeY.second);
                    limit_block = calculate_limit_block(block_size, left_block[block_size - 1], top_block,
                            x_index + 1, string_length, X_string, Y_char);
                    write_block(limit_block, number_of_values, step);
                    step++;
                }
                else {
                    x_index = calculate_X_coordinate(step, block_size, string_length);
                    for (int k = 0; k < block_size; k++) {
                        top_block[k] = x_index + 1 + k;
                    }
                    left_block = read_block(step - 1, block_size);
                    XeY = get_strings(x_filename, y_filename, step, string_length, block_size);
                    X_string = XeY.first;
                    X_string = X_string.substr(0, block_size);
                    Y_char = *(XeY.second);
                    current_block = calculate_block(block_size, left_block[block_size - 1], top_block,
                                                    x_index, string_length, X_string, Y_char);
                    write_block(current_block, block_size, step);
                    step++;
                }
            }
            else if (j == 0) {
                top_block = read_block(get_top_step(step, blocks_per_line), block_size);
                y_index = calculate_Y_coordinate(step, block_size, string_length);
                XeY = get_strings(x_filename, y_filename, step, string_length, block_size);
                X_string = XeY.first;
                X_string = X_string.substr(0, block_size);
                Y_char = *(XeY.second);
                current_block = calculate_block(block_size, y_index + 1, top_block, y_index,
                                                string_length, X_string, Y_char);
                write_block(current_block, block_size, step);
                step++;
            }
            else if (j == (blocks_per_line - 1) && (number_of_values != 0)) {
                top_step = get_top_step(step,blocks_per_line);
                top_block = read_block(top_step, number_of_values);
                left_block = read_block((step - 1), block_size);
                diagonal_block = read_block(top_step - 1, block_size);
                XeY = get_strings(x_filename, y_filename, step, string_length, number_of_values);
                X_string = XeY.first;
                X_string = X_string.substr(0, number_of_values);
                Y_char = *(XeY.second);
                limit_block = calculate_limit_block(block_size, left_block[block_size - 1],
                        top_block,diagonal_block[block_size - 1], string_length, X_string, Y_char);
                write_block(limit_block, number_of_values, step);
                step++;
            }
            else {
                top_step = get_top_step(step,blocks_per_line);
                top_block = read_block(top_step, block_size);
                left_block = read_block((step - 1), block_size);
                diagonal_block = read_block(top_step - 1, block_size);
                XeY = get_strings(x_filename, y_filename, step, string_length, block_size);
                X_string = XeY.first;
                X_string = X_string.substr(0, block_size);
                Y_char = *(XeY.second);
                current_block = calculate_block(block_size, left_block[block_size - 1], top_block,
                                                diagonal_block[block_size - 1], string_length, X_string, Y_char);
                write_block(current_block, block_size, step);
                step++;
            }


            cout << "Step: " << step << " ";
            for (int l = 0; l < block_size; l++) {
                cout << current_block[l];
            }
            cout << endl;

            cout << "limit block: ";
            for (int l = 0; l < number_of_values; l++) {
                cout << limit_block[l];
            }
            cout << endl;
        }
    }

    if (number_of_values != 0) {
        limit_block = read_block(total_steps, number_of_values);
        cout << "Distance: ";
        cout << limit_block[number_of_values - 1] << endl;
        return limit_block[number_of_values - 1];
    }
    else {
        current_block = read_block(total_steps, block_size);
        cout << "Distance: ";
        cout << current_block[block_size - 1] << endl;
        return current_block[block_size - 1];
    }
}

void run_test(int block_size, string x_filename, string y_filename, string out_filename) {

    auto start = chrono::high_resolution_clock::now();

    int distance = algorithm(block_size,x_filename, y_filename);
    //int distance = alternate_algorithm(block_size,x_filename, y_filename);

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<float > duration = end - start;

    int string_size = get_string_size(x_filename);

    ofstream outfile(out_filename);
    outfile << "Test for block size " << block_size << " and string size " << string_size << endl;
    outfile << "Execution time: " << duration.count() << " seconds" <<endl;
    outfile << "Distance: " << distance << endl;
}

int findMin(int x, int y, int z){
    if(x <= y && x <= z)
        return x;
    else if(y <=x && y <= z)
        return y;
    else
        return z;
}

int findDistance(char a[], char b[]) {
    // Declaring a 2D array on the heap dynamically:
    int len_a = strlen(a);
    int len_b = strlen(b);
    int **d = new int *[len_a + 1];
    for (int i = 0; i < len_a + 1; i++)
        d[i] = new int[len_b + 1];

    // Initialising first column:
    for (int i = 0; i < len_a + 1; i++)
        d[i][0] = i;

    // Initialising first row:
    for (int j = 0; j < len_b + 1; j++)
        d[0][j] = j;

    // Applying the algorithm:
    int insertion, deletion, replacement;

    for (int i = 1; i < len_a + 1; i++) {
        for (int j = 1; j < len_b + 1; j++) {
            if (a[i - 1] == b[j - 1]) {
                d[i][j] = d[i - 1][j - 1];
            } else {
                // Choosing the best option:
                insertion = d[i][j - 1];
                deletion = d[i - 1][j];
                replacement = d[i - 1][j - 1];

                d[i][j] = 1 + findMin(insertion, deletion, replacement);
            }
        }
    }

    int answer = d[len_a][len_b];

    return answer;
}

int calculate_value(char x, char y, int left_value, int top_value, int diagonal_value) {
    int min;
    if (x == y)
        min = findMin(left_value + 1, diagonal_value, top_value + 1);
    else
        min = findMin(left_value + 1, diagonal_value + 1, top_value + 1);
    return min;
}

int* calculate(string x, char y, int left_value, int* top_block, int diagonal_value, int block_size) {
    int* block = new int[block_size];
    for (int i = 0; i < block_size; i++) {
        if (i == 0) {
            block[i] = calculate_value(x[i], y, left_value, top_block[i], diagonal_value);
        } else {
            block[i] = calculate_value(x[i], y, block[i-1], top_block[i], top_block[i-1]);
        }
    }
    return block;
}

int alternate_algorithm(int block_size, string x_filename, string y_filename) {

    int step = 1;

    int* top_block = new int[block_size];
    int* left_block = new int[block_size];
    int* diagonal_block = new int[block_size];
    int* current_block = new int[block_size];

    int string_length = get_string_size(x_filename);
    cout << "string length: " << string_length << endl;

    pair<string, char*> XeY;

    int blocks_per_line = ceil((double) string_length/block_size);
    cout << "blocks per line: " << blocks_per_line << endl;
    int total_steps = string_length * blocks_per_line;
    cout << "total steps: " << total_steps << endl;
    int number_of_values = string_length % block_size;   //  NUMBER OF VALUES ON LIMIT BLOCK
    cout << "number of values on limit blocks: " << number_of_values << endl;

    int* limit_block = new int[number_of_values];   //  TRY TO DELETE THIS MEMORY SPACE AND USE CURRENT_BLOCK

    int x_index;
    int y_index;
    int minimum;
    int top_step;

    string X_string;
    char Y_char;

    for (int i = 0; i < string_length; i++) {
        for (int j = 0; j < blocks_per_line; j++) {
            if (i == 0) {
                if (j == 0) {
                    for (int k = 0; k < block_size; k++) {
                        top_block[k] = k + 1;
                    }
                    XeY = get_strings(x_filename, y_filename, step, string_length, block_size);
                    X_string = XeY.first;
                    X_string = X_string.substr(0, block_size);
                    Y_char = *(XeY.second);
                    //current_block = calculate_block(block_size, 1, top_block,
                      //                              0, string_length, X_string, Y_char);
                    current_block = calculate(X_string, Y_char, 1, top_block, 0, block_size);
                    write_block(current_block, block_size, step);
                    step++;
                }
                else if (j == (blocks_per_line - 1) && (number_of_values != 0)) {
                    x_index = calculate_X_coordinate(step, block_size, string_length);
                    for (int k = 0; k < number_of_values; k++)
                        top_block[k] = x_index + 1 + k;
                    left_block = read_block(step - 1, block_size);
                    XeY = get_strings(x_filename, y_filename, step, string_length, number_of_values);
                    X_string = XeY.first;
                    X_string = X_string.substr(0, number_of_values);
                    Y_char = *(XeY.second);
                    //limit_block = calculate_limit_block(block_size, left_block[block_size - 1], top_block,
                      //                                  x_index + 1, string_length, X_string, Y_char);
                    limit_block = calculate(X_string, Y_char, left_block[block_size - 1], top_block, x_index + 1, number_of_values);
                    write_block(limit_block, number_of_values, step);
                    step++;
                }
                else {
                    x_index = calculate_X_coordinate(step, block_size, string_length);
                    for (int k = 0; k < block_size; k++) {
                        top_block[k] = x_index + 1 + k;
                    }
                    left_block = read_block(step - 1, block_size);
                    XeY = get_strings(x_filename, y_filename, step, string_length, block_size);
                    X_string = XeY.first;
                    X_string = X_string.substr(0, block_size);
                    Y_char = *(XeY.second);
                    //current_block = calculate_block(block_size, left_block[block_size - 1], top_block,
                      //                              x_index, string_length, X_string, Y_char);
                    current_block = calculate(X_string, Y_char, left_block[block_size - 1], top_block, x_index, block_size);
                    write_block(current_block, block_size, step);
                    step++;
                }
            }
            else if (j == 0) {
                top_block = read_block(get_top_step(step, blocks_per_line), block_size);
                y_index = calculate_Y_coordinate(step, block_size, string_length);
                XeY = get_strings(x_filename, y_filename, step, string_length, block_size);
                X_string = XeY.first;
                X_string = X_string.substr(0, block_size);
                Y_char = *(XeY.second);
                //current_block = calculate_block(block_size, y_index + 1, top_block, y_index,
                  //                              string_length, X_string, Y_char);
                current_block = calculate(X_string, Y_char, y_index + 1, top_block, y_index, block_size);
                write_block(current_block, block_size, step);
                step++;
            }
            else if (j == (blocks_per_line - 1) && (number_of_values != 0)) {
                top_step = get_top_step(step,blocks_per_line);
                top_block = read_block(top_step, number_of_values);
                left_block = read_block((step - 1), block_size);
                diagonal_block = read_block(top_step - 1, block_size);
                XeY = get_strings(x_filename, y_filename, step, string_length, number_of_values);
                X_string = XeY.first;
                X_string = X_string.substr(0, number_of_values);
                Y_char = *(XeY.second);
                //limit_block = calculate_limit_block(block_size, left_block[block_size - 1],
                  //                                  top_block,diagonal_block[block_size - 1], string_length, X_string, Y_char);
                limit_block = calculate(X_string, Y_char, left_block[block_size - 1], top_block, diagonal_block[block_size-1], number_of_values);
                write_block(limit_block, number_of_values, step);
                step++;
            }
            else {
                top_step = get_top_step(step,blocks_per_line);
                top_block = read_block(top_step, block_size);
                left_block = read_block((step - 1), block_size);
                diagonal_block = read_block(top_step - 1, block_size);
                XeY = get_strings(x_filename, y_filename, step, string_length, block_size);
                X_string = XeY.first;
                X_string = X_string.substr(0, block_size);
                Y_char = *(XeY.second);
                //current_block = calculate_block(block_size, left_block[block_size - 1], top_block,
                  //                              diagonal_block[block_size - 1], string_length, X_string, Y_char);
                current_block = calculate(X_string, Y_char, left_block[block_size-1], top_block, diagonal_block[block_size-1], block_size);
                write_block(current_block, block_size, step);
                step++;
            }
            cout << "Step: " << step << endl;
        }
    }

    if (number_of_values != 0) {
        limit_block = read_block(total_steps, number_of_values);
        cout << "Distance: ";
        cout << limit_block[number_of_values - 1] << endl;
        return limit_block[number_of_values - 1];
    }
    else {
        current_block = read_block(total_steps, block_size);
        cout << "Distance: ";
        cout << current_block[block_size - 1] << endl;
        return current_block[block_size - 1];
    }
}