//
// Created by Ignacio Moore on 26/09/2019.
//

#include <cstdio>
#include <fstream>
#include <string>

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