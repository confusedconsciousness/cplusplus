#include <iostream>
using namespace std;
// we'll be using dynamic programming

int main() {
    int W;
    cin >> W; // input the capacity of your bag
    int n;
    cin >> n;// total number of items

    int info[n][2]; // array containing the value and weight of each item
    // input is taken in the following format
    // value, weight
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < 2; ++j){
            cin >> info[i][j];
        }
    }
    // we're going to maintain an array having the n * W dimension
    int matrix[n + 1][W + 1];
    // we need to first initialise the array
    // matrix[0][W] = 0
    for(int i = 0; i < n + 1; ++i){
        for(int j = 0; j < W + 1; ++j){
            matrix[i][j] = 0;
        }
    }
    // now apply dynamic programming approach
    for(int i = 1; i < n + 1; ++i){
        for(int w = 0; w < W + 1; ++w){
            int weightOfItem = info[i - 1][1];
            int valueOfItem = info[i - 1][0];
            if((w - weightOfItem) > 0){
                matrix[i][w] = max(matrix[i - 1][w], matrix[i - 1][w - weightOfItem] + valueOfItem);
            }else{
                matrix[i][w] = matrix[i - 1][w];
            }

        }
    }
    // final output
    cout<<matrix[n][W];
    return 0;
}