#include <iostream>
#include <vector>
using namespace std;
// this program only determines the shortest path
struct Node{
    bool isRoad; // will determine if there is a way
    bool isVisited; // will determine if we've already visited this node
    int distance; // will take a track of the distance of the node from the source
    int i;
    int j;
};

// we'll be needing a queue to store our nodes
// this queue will be storing the nodes
const int MAX_SIZE = 100;
class Queue{
    struct Node arrayOfNodes[MAX_SIZE];
    int front;
    int rear;
public:
    Queue(){
        // constructor
        front = -1;
        rear = -1;
    }
    void enqueue(struct Node node);
    struct Node dequeue();
    bool isEmpty();
};

void Queue::enqueue(struct Node node){
    if(front == -1 && rear == -1){
        // we've an empty queue
        ++front;
        ++rear;
        arrayOfNodes[rear] = node;
    }else{
        arrayOfNodes[++rear] = node;
    }
}

struct Node Queue::dequeue() {
    if(front == rear + 1){
        // empty
        cout<<"Queue is empty";
    }else{
        struct Node temp = arrayOfNodes[front];
        ++front;
        return  temp;
    }
}

bool Queue::isEmpty() {
    return front == rear + 1;
}



int findShortestPath(int i, int j, int p, int q, int n, struct Node Matrix[4][4]) {
    // (i, j) current position in the matrix
    // (p, q) destination
    // n size of the matrix
    // Matrix - containing the information about the roads

    Queue myQueue;
    myQueue.enqueue(Matrix[i][j]); // enqueue the source
    Matrix[i][j].isVisited = true;
    Matrix[i][j].distance = 0;
    // apply BFS
    while(!myQueue.isEmpty()){
        cout<<"Inside while\n";
        // dequeue the element
        struct Node current_node = myQueue.dequeue();
        // now check its all directions
        int i = current_node.i;
        int j = current_node.j;
        cout<<"current Pos: (i, j) -> ("<<i<<","<<j<<")\n";
        // first check left
        if(j - 1 > -1 && Matrix[i][j - 1].isRoad && !Matrix[i][j - 1].isVisited){
            // valid node
            myQueue.enqueue(Matrix[i][j - 1]);
            // further more set the nodes distance to
            Matrix[i][j - 1].distance = Matrix[i][j].distance + 1;
            Matrix[i][j - 1].isVisited = true;
        }
        // second check right
        if((j + 1) < n && Matrix[i][j + 1].isRoad && !Matrix[i][j + 1].isVisited){
            // valid node
            myQueue.enqueue(Matrix[i][j + 1]);
            // furthermore change the defaults
            Matrix[i][j + 1].distance = Matrix[i][j].distance + 1;
            Matrix[i][j + 1].isVisited = true;
        }
        // third check up
        if((i - 1) > -1 && Matrix[i - 1][j].isRoad && !Matrix[i - 1][j].isVisited){
            // valid node
            myQueue.enqueue(Matrix[i - 1][j]);
            // furthermore change the defaults
            Matrix[i - 1][j].distance = Matrix[i][j].distance + 1;
            Matrix[i - 1][j].isVisited = true;
        }
        // fourth check down
        if((i + 1) < n && Matrix[i + 1][j].isRoad && !Matrix[i + 1][j].isVisited){
            // valid node
            myQueue.enqueue(Matrix[i + 1][j]);
            // furthermore change the defaults
            Matrix[i + 1][j].distance = Matrix[i][j].distance + 1;
            Matrix[i + 1][j].isVisited = true;
        }


    }

    // after doing the breadth first search we'll simply print the distance
    return Matrix[p][q].distance;

}





int main() {
    int n;
    cout<<"Size of matrix (n * n): ";
    cin>>n;
    const int size = n;
    struct Node Matrix[4][4];
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            int temp;
            cin>>temp;
            Matrix[i][j].isVisited = false; // by default
            Matrix[i][j].distance = 1000; // by default
            Matrix[i][j].i = i;
            Matrix[i][j].j = j;

            if(temp == 1){
                Matrix[i][j].isRoad = true;

            }else{
                Matrix[i][j].isRoad = false;
            }

        }
    }
    int cur_i, cur_j, des_i, des_j;
    cin>>cur_i>>cur_j;
    cin>>des_i>>des_j;
    int temp = findShortestPath(cur_i, cur_j, des_i, des_j, n, Matrix);
    cout<<temp;
    return 0;
}