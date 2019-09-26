


#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include "calculate.hpp"
#include "firstAlgorithm.hpp"

using namespace std;

int main() {

    pair<string, string> xey;

    xey = get_strings("two_strings.txt");

    string x = xey.first;
    cout << x << endl;
    cout << x.length() << endl;
    cout << xey.second << endl;

    return 0;
}