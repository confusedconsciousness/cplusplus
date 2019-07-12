#include <iostream>
#include <vector>
using namespace std;


struct Node{
    int x, y; // coordinate of the node
    int key; // this will actually be equal to f(n) = g(n) + h(n), where h(n) is the manhattan distance and g(n) is the total distance till covered
    int distance; // it will consist of the shortest distance
    vector<struct Node*> neighbours;
    int manhattanDistance; // this will consist of the manhattan distance from the current node to the destination node
    int path; // yes means this node is visitable otherwise no road exists
};

struct Node* INPUT[20][20]; // this will our matrix of nodes (graph)
struct Node* ARRAY[400]; // this is for flattened out nodes, basically used to maintain a min heap


struct Node* createNode(int x, int y, int path){
    struct Node* newNode = new Node();
    newNode->x = x;
    newNode->y = y;
    newNode->distance = 65536; // this value means unreachable
    newNode->key = 65536; // same as distance but will contain the shortest path
    newNode->path = path;
    return newNode;
}

void createGraph(int n){
    // n is the size of the matrix which is n X n
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            // get the current node
            struct Node* currentNode = INPUT[i][j];
            // now let's check its all the four side
            // if there is a path to them we'll consider those nodes as the neighbour of the current node
            if(i - 1 > -1){
                // look up
                if(INPUT[i - 1][j]->path){
                    // there is a path
                    currentNode->neighbours.push_back(INPUT[i - 1][j]);
                }
            }
            if(i + 1 < n){
                // look down
                if(INPUT[i + 1][j]->path){
                    // there is a path
                    currentNode->neighbours.push_back(INPUT[i + 1][j]);
                }
            }
            if(j - 1 > -1){
                // look left
                if(INPUT[i][j - 1]->path){
                    // there is a path
                    currentNode->neighbours.push_back(INPUT[i][j - 1]);
                }
            }
            if(j + 1 < n){
                // look right
                if(INPUT[i][j + 1]->path){
                    // there is a path
                    currentNode->neighbours.push_back(INPUT[i][j] + 1);
                }
            }


        }
    }
}

// let's implement min heap
int findLeftChild(int i){
    return (2 * i + 1);
}
int findRightChild(int i ){
    return (2 * i + 2);
}

void heapify(int i, int n){
    // i is the index of parent
    // n is the length of the array
    int left = findLeftChild(i);
    int right = findRightChild(i);
    int smallest;
    if(left < n && ARRAY[left]->key < ARRAY[i]->key){
        smallest = left;
    }else{
        smallest = i;
    }

    if(right < n && ARRAY[right]->key < ARRAY[smallest]->key){
        smallest = right;
    }
    if(smallest != i){
        // that is it violates the min heap property
        swap(ARRAY[smallest], ARRAY[i]);
    }
}

void buildHeap(int n){
    for(int i = n / 2; i > -1; --i){
        heapify(i, n);
    }
}
void showHeap(int n){
    for(int i = 0; i < n; ++i){
        if(ARRAY[i] != nullptr){
            cout<<ARRAY[i]->key<<" ";
        }
    }
    cout<<endl;
}

// let's implement the heuristic
void applyHeuristic(int n, int x, int y){
    // x and y coordinates are the destination coordinates, notice the coordinates start from (0, 0) to (n-1, n-1)
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            INPUT[i][j]->manhattanDistance = abs(i - x) + abs(j - y);
        }
    }
}


// let's implement the searching algorithm
void searchAlgorithm(struct Node* source, int n){
    // n is the flattened size of the array for the maintenance of min heap
    source->key = source->manhattanDistance; // initialise the key to manhattan distance
    source->distance = 0; // because it will tell the shortest path
    int counter = n;
    buildHeap(n);
    //showHeap(counter);
    while(n > -1){
        struct Node* current = ARRAY[0]; // extract smallest key
        n = n - 1;
        swap(ARRAY[0], ARRAY[n]); // put that outside of our context
        // look at the neighbours of it
        for(int i = 0; i < current->neighbours.size(); ++i){
            if(current->neighbours[i]->key >= current->key + current->neighbours[i]->manhattanDistance + 1){
                current->neighbours[i]->key = current->key + current->neighbours[i]->manhattanDistance + 1;
                current->neighbours[i]->distance = current->distance + 1;
            }
        }
        // now again build the heap to update the heap
        buildHeap(n);
        //showHeap(counter);
    }

}

int main() {
    int n;
    cin>>n;
    int temp, count = 0;
    int start_x, start_y, dest_x, dest_y; // give the coordinates of the current position and the destined position
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cin>>temp;
            INPUT[i][j] = createNode(i, j, temp);
            ARRAY[count] = INPUT[i][j];
            ++count;
        }
    }
    cin>>start_x>>start_y>>dest_x>>dest_y;
    // let's build the graph
    createGraph(n);
    applyHeuristic(n, dest_x, dest_y);
    searchAlgorithm(INPUT[start_x][start_y], count);
    // now output the minimum distance
    cout<<"\nMinimum Distance: "<<INPUT[dest_x][dest_y]->distance;
    return 0;
    // try this input or one of ur own
    /*
    8
    1 1 0 1 0 1 0 0
    1 1 1 1 1 0 0 1
    0 0 1 1 1 1 1 0
    1 0 0 1 1 1 1 1
    0 1 1 1 1 1 0 0
    1 1 1 1 1 0 1 1
    1 0 1 0 1 1 1 1
    1 1 1 1 1 0 0 1
    0 0 7 7
     */
}