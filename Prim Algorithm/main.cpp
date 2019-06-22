// PrimAlgorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <limits>
#include <cmath>
using namespace std;

//---------------------- Graph Nodes ------------------------------
struct GraphNodes{
    // this will correspond to the graph nodes
    int key; // it will hold the current
    struct GraphNodes* parent;
    int value; // to identify two nodes

};

struct Nodes {
    // this will be the adjacency list
    struct GraphNodes* graphNodes;

    struct Nodes* next;
};



// following functions will help us in creation of nodes
struct GraphNodes* createGraphNodes(int value) {
    struct GraphNodes* newGraphNode = new GraphNodes();
    newGraphNode->key = numeric_limits<int>::max(); // set the key to INFINITY
    newGraphNode->value = value;
    newGraphNode->parent = NULL;
    return newGraphNode;

}


struct Nodes* createNodes(struct GraphNodes* graphNodes){
    struct Nodes* newNode = new Nodes();
    newNode->graphNodes = graphNodes;
    newNode->next = NULL;
    return newNode;
}

void createLinks(int node1, int node2, struct GraphNodes** arrayOfGraphNodes, struct Nodes** adjacencyList){
    // edge1 will have a particular location in the adjacency list
    // for example if we're talking about 0th node it means its location is adjacencyList[0]
    struct Nodes* temp = adjacencyList[node1];
    // now add the node corresponding to node2 in the end of node1
    // traverse the list
    while(temp->next != NULL){
        temp = temp->next;
    }

    temp->next = createNodes(arrayOfGraphNodes[node2]);
}

void showGraph(struct Nodes** adjacencyList, int n){
    cout<<"Graph: \n";
    for(int i = 0; i < n; ++i){
        struct Nodes* temp = adjacencyList[i];
        while(temp != NULL){
            cout<<temp->graphNodes->value<<" -> ";
            temp = temp->next;
        }
        cout<<"NULL\n";
    }
}

//------------------------------------------------------------------------
// store the keys in min heap
// try to sort the graph nodes

// --------------------- Min Heap ------------------------------
int findParent(float index) {
    return ceil(index / 2 - 1);
}

int findLeftChild(int index) {
    return (2 * index + 1);
}

int findRightChild(int index) {
    return (2 * index + 2);
}

void MinHeapify(struct GraphNodes** A, int i, int n) {
    // this function assumes that the left and right child are max heaps but only the parent is not following the trend
    // heap_size
    int left = findLeftChild(i);
    int right = findRightChild(i);
    int smallest = 0;

    if (left < n && A[left]->key < A[i]->key) {
        smallest = left;
    }
    else {
        smallest = i;
    }

    if (right < n && A[right]->key < A[smallest]->key) {
        smallest = right;
    }

    if (smallest != i) {
        // swap
        swap(A[smallest], A[i]);
        MinHeapify(A, smallest, n);
    }
}

void BuildMinHeap(struct GraphNodes** A, int n) {
    // an array A which is unsorted or doesn't follow max heap will be heapified
    // we want to start from the second last level
    for (int i = n / 2; i > -1; --i) {
        MinHeapify(A, i, n);
    }
}

void showHeap(struct GraphNodes** A, int n){
    for(int i = 0; i < n; ++i){
        cout<<"Node: "<<A[i]->value<<" key: "<<A[i]->key<<"     ";
    }
    cout<<"\n";
}

//---------------------------------------------------------------------------------
int main()
{
    /*
	Input will be given the following format
	n // where n corresponds to the total number or nodes
	weight12 node1 node2
	where weight12 corresponds to the edge weight between node1 and node2
	and node1 and node2 corresponds to the index or value part of nodes
	*/
    int n;
    cin>>n;
    int edges;
    cin>>edges;
    int INPUTS[edges][3]; //3 columns
    for (int i = 0; i < edges; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> INPUTS[i][j];
        }
    }

    int WEIGHT[n][n];
    // initialise the weight to -1
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            WEIGHT[i][j] = -1;
        }
    }


    for(int i = 0; i < edges; ++i){
        int pos1 = INPUTS[i][1];
        int pos2 = INPUTS[i][2];
        int weight = INPUTS[i][0];
        WEIGHT[pos1][pos2] = weight;
    }

    cout<<"\n Weights: \n";
    cout<<"------------------------------\n";
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cout<<WEIGHT[i][j]<<"   ";
        }
        cout<<"\n";
    }
    cout<<"\n------------------------------\n";

    // first create all the graph nodes from the above information
    struct GraphNodes* arrayOfGraphNodes[n];
    for(int i = 0; i < n; ++i){
        arrayOfGraphNodes[i] = createGraphNodes(i);
    }

    struct Nodes* adjacencyList[n];
    // create the default links
    // adjacencyList[0] -> nodes(arrayOfGraphNodes[0])->NULL
    // adjacencyList[1] -> nodes(arrayOfGraphNodes[1])->NULL
    //
    for(int i = 0; i < n; ++i){
        adjacencyList[i] = createNodes(arrayOfGraphNodes[i]);
    }

    // build the rest graph
    for(int i = 0; i < edges; ++i){
        createLinks(INPUTS[i][1], INPUTS[i][2], arrayOfGraphNodes, adjacencyList);
    }

    showGraph(adjacencyList, n);

    // we'll create another array of arrayOfGraphNodes for our min heap
    struct GraphNodes* temporary[n];
    for(int i = 0; i < n; ++i){
        temporary[i] = arrayOfGraphNodes[i];
    }
    // first task is we'll have a source let's take it the 0th node
    // PRIM ALGORITHM
    temporary[0]->key = 0;
    BuildMinHeap(temporary, n);

    //showHeap(temporary, n);
    int original_size = n;
    while(n > 0){
        struct GraphNodes* currentNode = temporary[0];
        n = n - 1;
        swap(temporary[0], temporary[n]);

        //showHeap(temporary, original_size);
        // look its adjacency list
        struct Nodes* temp = adjacencyList[currentNode->value];
        temp = temp->next; // so that it points to the next element and not to itself
        while(temp != NULL){
            struct GraphNodes* neighbourNode = temp->graphNodes;
            // now check if the neighbour node is present in the temporary
            int flag = 0; // it means we were not able to find the node
            for(int i = 0; i < n; ++i){
                if(neighbourNode == temporary[i]){
                    flag = 1;
                }
            }
            int edgeWeight = WEIGHT[currentNode->value][neighbourNode->value];
            if(flag == 1 && edgeWeight < neighbourNode->key){

                neighbourNode->parent = currentNode;
                neighbourNode->key = edgeWeight;

            }
            temp = temp->next;

        }
        // heapify
        BuildMinHeap(temporary, n);
        //showHeap(temporary, original_size);
    }


    // Question is How will you print the result
    int sumOfWeights = 0;
    for(int i = 0; i < original_size; ++i){
        if(arrayOfGraphNodes[i]->parent != NULL){
            struct GraphNodes* parent = arrayOfGraphNodes[i]->parent;
            struct GraphNodes* child = arrayOfGraphNodes[i];
            sumOfWeights += WEIGHT[child->value][parent->value];
        }
    }

    cout<<"\nSum of Weights of Minimum Spanning Tree: "<<sumOfWeights;

}
