
using namespace std;

void write_block(int* block, int block_size, int step);

int* read_block(int step, int block_size);

int calculate_X_coordinate(int step, int block_size, int string_length);

int calculate_Y_coordinate(int step, int block_size, int string_length);

pair<string, string> get_strings(string filename);

int get_top_step(int step, int blocks_per_line);