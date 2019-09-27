


#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include "calculate.hpp"
#include "firstAlgorithm.hpp"

using namespace std;

int main() {

    int left[] = {2,1,2};
    int diagonal[] = {1,2,2};
    int top[] = {3};

    char x[] = " ananas";
    char y[] = " banana";

    int jj = 6;
    int ii = 5;

    int* r = new int[3];
    r = calculate_limit_block(3,left,top,diagonal,7,x,y,ii,jj);

    cout << r[0];

    return 0;
}