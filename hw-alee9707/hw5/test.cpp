#include <iostream>
#include <string>
using namespace std;

int main(){
    int n = 195;
    int sizes[17] = {11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437, 102877, 205759, 411527, 823117};

    int newSize;
    int i = 0;
    while(n>sizes[i] && i<17){
        i++;
    }
    newSize = sizes[i];
    cout << n << endl;
    cout << newSize << endl;
}