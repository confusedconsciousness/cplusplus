#include <iostream>
#include <vector>
using namespace std;

struct Node{
    int value;
    vector<struct Node*> neighbour;
    vector<int> weights;
    bool visited;
    // value uniquely identifies this node
    // weights are not necessary but let's take it too
    // for making things easy we'll also have certain auxilary things
    // visited will take into account whether the node has already been visited
};


// function to create a node
struct Node* createNode(int value){
    struct Node* newNode = new Node();
    newNode->visited = false;
    newNode->value = value;
    return newNode;
}

void buildLinks(int n1, int n2, int w12, struct Node** arrayOfNodes){
    // get the node1
    struct Node* node1 = arrayOfNodes[n1];
    struct Node* node2 = arrayOfNodes[n2];
    // now append node2 in the neighbour section of node1
    node1->neighbour.push_back(node2);
    node1->weights.push_back(w12);
}

void showGraph(struct Node** arrayOfNodes, int n){
    for(int i = 0; i < n; ++i){
        // first get the node
        struct Node* node = arrayOfNodes[i];
        int total_neighbours = static_cast<int>(node->neighbour.size());
        // now traverse its neighbours
        cout<<node->value<<"->";
        for(int j = 0; j < total_neighbours; ++j){
            cout<<node->neighbour[j]->value<<"->";
        }
        cout<<"NULL\n";
    }
}

void DFS_VISIT(struct Node* current){
    // first task is to mark this node as visited
    current->visited = true;
    // print the node first
    cout<<current->value<<" ";
    // we'll look at its neighbors
    for(int i = 0; i < current->neighbour.size(); ++i){
        // check if they are visited
        if(!current->neighbour[i]->visited){
            // if it is not visited then visit it
            // set the visited to true
            current->neighbour[i]->visited = true;
            DFS_VISIT(current->neighbour[i]);
        }
    }
}

void DFS_main(struct Node** arrayOfNodes, int n){
    // initially all our nodes are not visited
    for(int i = 0; i < n; ++i){
        struct Node* current_node = arrayOfNodes[i];
        if(!current_node->visited) {
            DFS_VISIT(current_node);
        }
    }
}



int main() {
    // input follows
    // n -> total nodes
    // e -> total edges
    // n1 n2 w12 -> n1 and n2 are the weights whereas w12 represents the weight of the edge
    int n, e;
    cin >> n >> e;
    // we'll create a array of pointers to these nodes
    // 0th node will be present at the 0th index of the array
    struct Node* arrayOfNodes[n];
    // link each node to the array
    for(int i  = 0; i < n; ++i){
        arrayOfNodes[i] = createNode(i);
    }

    // take the input from the user about the edges
    int INPUT[e][3];
    for(int i = 0; i < e; ++i){
        for(int j = 0; j < 3; ++j){
            cin >> INPUT[i][j];
        }
    }

    // now build links
    for(int i = 0; i < e; ++i){
        int n1 = INPUT[i][0];
        int n2 = INPUT[i][1];
        int w12 = INPUT[i][2];
        buildLinks(n1, n2, w12, arrayOfNodes);
    }

    showGraph(arrayOfNodes, n);

    DFS_main(arrayOfNodes, n);

    return 0;
}