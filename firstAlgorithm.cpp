//
// Created by Ignacio Moore on 26/09/2019.
//

#include <cstdio>
#include <fstream>
#include <string>
#include <cmath>
#include <iostream>

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
    string out_block = "";

    for (int i = 0; i < block_size; i++)
        out_block = out_block + to_string(block[i]);

    outfile << out_block;
    outfile.close();
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
    string cell;
    int* block = new int[block_size];

    infile >> cell;
    for (int i = 0; i < block_size; i++) {
        block[i] = stoi(cell.substr(i,1));
    }

    infile.close();
    return block;
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
    char* Y_string;

    char Y_char;
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

    string line;
    ifstream infile;
    infile.open(filename);
    getline(infile, line);
    infile.close();
    return line.length();
}

void generate_string(int size, string filename) {

    ofstream string_file;
    string_file.open(filename);

    string x;

    for (int i = 0; i < pow(2,size); i++) {
        int c = rand() % 26 + 65;
        x += char(c);
    }

    string_file << x;
    string_file.close();
}
