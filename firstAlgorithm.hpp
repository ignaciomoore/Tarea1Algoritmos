
using namespace std;

void write_block(int* block, int block_size, int step);

int* read_block(int step, int block_size);

int calculate_X_coordinate(int step, int block_size, int string_length);

int calculate_Y_coordinate(int step, int block_size, int string_length);

pair<string, char* > get_strings(string x_filename, string y_filename, int step, int string_length, int block_size);

int get_top_step(int step, int blocks_per_line);

int get_string_size(string filename);

void generate_string(int size, string filename);

void algorithm(int block_size, string x_filename, string y_filename);