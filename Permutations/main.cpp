#include <iostream>
#include <vector>
// this program basically computes all the permutations
using namespace std;

void sortTheArray(int *A, int i, int n){
    // A -> is the array
    // i -> is the current index from where we need to sort
    // n -> is the size of the array
    // since the array is in descending order we need to swap it
    int k = 0;
    for(int j = i; j < n ; ++j){
        if(j < (n - 1 - k)){
            swap(A[j], A[n - 1 - k]);
            ++k;
        }else{
            break;
        }
    }
}

void generateNextPermutation(int *A, int n){
    // A is the current state
    // n is the size of the array
    int flag = 0;
    vector<int> auxiliary;
    for(int i = n - 2; i > -1 ; --i){
        if(A[i] > A[i + 1]){
            auxiliary.push_back(A[i + 1]);
        }else{
            // find the element which is just greater than A[i] from auxiliary array
            auxiliary.push_back(A[i + 1]);

            for(int j = 0; j < auxiliary.size(); ++j){
                if(auxiliary[j] > A[i]){
                    // we got our element now we need to swap
                    swap(A[i], A[n - j - 1]);
                    // now we need to sort the A after the ith index
                    sortTheArray(A, i + 1, n);
                    flag = 1;
                    break;
                }
            }

        }
        if (flag == 1){
            break;
        }

    }
}

void showThePermutation(int *A, int n){
    for(int i = 0; i < n; ++i){
        cout<<A[i]<<" ";
    }
    cout<<"\n";
}

int main() {
    // you can take your own input, here i'm using a predefined input
    int A[] = {6, 2, 1, 5, 4, 3, 0};
    int n = sizeof(A) / sizeof(int);

    // we'll start from the end and search a first non-increasing number
    // here 0 -> 3 -> 4 -> 5 -> [1], 1 is non increasing
    // the next phase is to find a number from that increasing phase such that it is greater than 1 which is 3
    // then swap it so that our new A = {6, 2, 3, 5, 4, 1, 0}
    // now sort the element after 3
    // A = {6, 2, 3, 0, 1, 4, 5
    // the question is from this state how many next permutations will be possible
    // we need to find the next permutations till we reach 6, 5, 4, 3, 2, 1, 0

    // first we'll create a function that just give us the next permutations
    // generate 10 next permutations
    showThePermutation(A, n);
    for(int i = 0; i < 100; ++i){
        generateNextPermutation(A, n);
        showThePermutation(A, n);
    }
    
    return 0;
}