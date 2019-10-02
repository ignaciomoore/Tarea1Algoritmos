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
    ofstream outfile (filename, ios::binary);
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
        out_block = out_block + to_string(bitset<32> (block[i]));

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
    int int_cell;

    for (int i = 0; i < block_size; i++) {
        infile.read(cell, 32);
        string_cell = string(cell);
        int_cell = stoi(string_cell, 0, 2);
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

int findMin(int x, int y, int z){
    if(x <= y && x <= z)
        return x;
    else if(y <=x && y <= z)
        return y;
    else
        return z;
}

void algorithm(int block_size, string x_filename, string y_filename, string out_filename) {

    auto start = chrono::high_resolution_clock::now();

    int step = 1;

    int write_block_count = 0;
    int read_block_count = 0;

    int* top_block = new int[block_size];
    int* left_block = new int[block_size];
    int* diagonal_block = new int[block_size];
    int* current_block = new int[block_size];

    int left_value;
    int diagonal_value;

    int string_length = get_string_size(x_filename);
    cout << "string length: " << string_length << endl;

    pair<string, char*> XeY;

    int blocks_per_line = ceil((double) string_length/block_size);
    cout << "blocks per line: " << blocks_per_line << endl;
    int total_steps = string_length * blocks_per_line;
    cout << "total steps: " << total_steps << endl;

    int x_string_index;
    int y_string_index;
    int top_step;

    string X_string;
    char Y_char;

    for (int i = 0; i < string_length; i++) {
        for (int j = 0; j < blocks_per_line; j++) {
            if (i == 0) {
                if (j == 0) {
                    left_value = 1;
                    diagonal_value = 0;
                    for (int k = 0; k < block_size; k++) {
                        top_block[k] = k + 1;
                    }
                    XeY = get_strings(x_filename, y_filename, step, string_length, block_size);
                    X_string = XeY.first;
                    X_string = X_string.substr(0, block_size);
                    Y_char = *(XeY.second);
                    current_block = calculate_block(block_size, left_value, top_block,
                                                    diagonal_value, string_length, X_string, Y_char);
                }
                else {
                    x_string_index = calculate_X_coordinate(step, block_size, string_length);
                    for (int k = 0; k < block_size; k++) {
                        top_block[k] = x_string_index + 1 + k;
                    }
                    left_block = read_block(step - 1, block_size);
                    read_block_count++;
                    left_value = left_block[block_size - 1];
                    diagonal_value = x_string_index;
                    XeY = get_strings(x_filename, y_filename, step, string_length, block_size);
                    X_string = XeY.first;
                    X_string = X_string.substr(0, block_size);
                    Y_char = *(XeY.second);
                    current_block = calculate_block(block_size, left_value, top_block,
                                                    diagonal_value, string_length, X_string, Y_char);
                }
            }
            else if (j == 0) {
                top_step = get_top_step(step, blocks_per_line);
                top_block = read_block(top_step, block_size);
                read_block_count++;
                y_string_index = calculate_Y_coordinate(step, block_size, string_length);
                left_value = y_string_index + 1;
                diagonal_value = y_string_index;
                XeY = get_strings(x_filename, y_filename, step, string_length, block_size);
                X_string = XeY.first;
                X_string = X_string.substr(0, block_size);
                Y_char = *(XeY.second);
                current_block = calculate_block(block_size, left_value, top_block, diagonal_value,
                                                string_length, X_string, Y_char);
            }
            else {
                top_step = get_top_step(step,blocks_per_line);
                top_block = read_block(top_step, block_size);
                read_block_count++;
                left_block = read_block(step - 1, block_size);
                read_block_count++;
                left_value = left_block[block_size - 1];
                diagonal_block = read_block(top_step - 1, block_size);
                read_block_count++;
                diagonal_value = diagonal_block[block_size - 1];
                XeY = get_strings(x_filename, y_filename, step, string_length, block_size);
                X_string = XeY.first;
                X_string = X_string.substr(0, block_size);
                Y_char = *(XeY.second);
                current_block = calculate_block(block_size, left_value, top_block,
                                                diagonal_value, string_length, X_string, Y_char);
            }
            write_block(current_block, block_size, step);
            write_block_count++;
            step++;
        }
    }
    current_block = read_block(total_steps, block_size);
    read_block_count++;

    int distance = current_block[block_size - 1];

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<float > duration = end - start;

    ofstream outfile(out_filename);
    outfile << "Test for block size " << block_size << " and string size " << string_length << endl;
    outfile << "Execution time: " << duration.count() << " seconds" <<endl;
    outfile << "Distance: " << distance << endl;
    outfile << "Blocks read: " << read_block_count << endl;
    outfile << "Blocks written: " << write_block_count << endl;
    outfile.close();
}