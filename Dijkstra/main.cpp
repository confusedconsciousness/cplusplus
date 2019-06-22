#include <iostream>
#include <vector>
// 2 ^ 16 = 65,536
using namespace std;

// we'll first build a graph
// edges structure will contain the meta data of the nodes to which node they are connected

struct GraphNode{
    int value; // to uniquely identify each nodes
    int total_neighbors;
    int distance;
    vector<struct GraphNode*> neighbors;
    vector<int> weights;
};

// following functions will help us in creating a new node
struct GraphNode* createGraphNode(int value){
    auto * newNode = new GraphNode();
    newNode->value = value;
    newNode->total_neighbors = 0;
    newNode->distance = 65536; // it is as if we are setting this value to infinity
    return newNode;
}

// following function will create a graph
void createGraph(struct GraphNode** arrayOfGraphNode, int node1, int node2, int weight){
    // arrayOfGraphNode -> array of graph nodes
    // weight -> the edge weight between these two nodes node1 and node2
    // using node1 we'll figure out the location of node1 in arrayOfGraphNode
    struct GraphNode* pointer2Node1 = arrayOfGraphNode[node1];
    struct GraphNode* pointer2Node2 = arrayOfGraphNode[node2];
    // we need to make a link of node2pointer in node1pointer
    pointer2Node1->neighbors.push_back(pointer2Node2);
    pointer2Node1->weights.push_back(weight);
    pointer2Node1->total_neighbors += 1;


}

void showGraph(struct GraphNode** arrayOfGraphNode, int n){
    // n -> no of nodes
    for(int i = 0; i < n; ++i){
        struct GraphNode* pointer2Node = arrayOfGraphNode[i];
        // now explore all its neighbours
        // first let's see how many neighbors are present
        int total_neighbors = pointer2Node->total_neighbors;
        cout<<pointer2Node->value<<" -> ";
        for(int j = 0; j < total_neighbors; ++j){
            cout<<pointer2Node->neighbors[j]->value<<" -> ";
        }
        cout<<"NULL\n";

    }
}

// Build min heap w.r.t distance
// min heap creation require four auxiliary function
int findLeftChild(int index){
    return 2 * index + 1;
}
int findRightChild(int index){
    return 2 * index + 2;
}
void heapify(struct GraphNode **A, int index, int n){
    // this function takes the current index and looks for its children whether they satisfy the min heap condition
    // if they don't it swaps and again call heapify to
    int left = findLeftChild(index);
    int right = findRightChild(index);
    int smallest; // index of smallest child
    if (left < n && A[left]->distance <= A[index]->distance){
        // parent is greater than the left child, violates
        smallest = left;
    }else{
        smallest = index;
    }

    if(right < n && A[right]->distance < A[smallest]->distance){
        // the right element is smallest
        smallest = right;
    }
    if(smallest != index){
        // which means if the parent is not the smallest
        swap(A[smallest], A[index]);
        // call heapify again
        heapify(A, smallest, n);
    }

}

void buildMinHeap(struct GraphNode **A, int n){
    // as we've  a constraint that heapify assumes that its children should satisfy the property of min heap
    // although it's not necessary for its parent to follow
    for(int i = n / 2; i > -1; --i){
        // when i = n / 2, it means we're at the second last level and the last level always satisfy the min heap
        heapify(A, i, n);
    }
}

void showHeap(struct GraphNode **A, int n){
    for(int i = 0; i < n; ++i){
        cout<<"Node: "<<A[i]->value<<" distance: "<<A[i]->distance<<" || ";
    }
    cout<<"\n";
}

int main() {
    int n; // no of nodes
    cin>>n;
    // input should be in the following format
    // weight, node1, node2
    // we'll have an array of nodes
    struct GraphNode* arrayOfGraphNodes[n];
    // initialise the array
    for(int i = 0; i < n; ++i){
        arrayOfGraphNodes[i] = createGraphNode(i);
    }

    int no_of_edges;
    cin>>no_of_edges;
    int INPUTS[no_of_edges][3];
    for(int i = 0; i < no_of_edges; ++i){
        for(int j = 0; j < 3; ++j){
                cin >>INPUTS[i][j];
        }
    };
    // BUILD the graph
    for(int i = 0; i < no_of_edges; ++i){
        int node1 = INPUTS[i][1];
        int node2 = INPUTS[i][2];
        int weight = INPUTS[i][0];

        createGraph(arrayOfGraphNodes, node1, node2, weight);

    }

    showGraph(arrayOfGraphNodes, n);

    // first task is to create a different copy of arrayOfGraphNodes
    struct GraphNode* temporary[n];
    for(int i = 0; i < n; ++i){
        temporary[i] = arrayOfGraphNodes[i];
    }

    // set the first element or whatever you wish to set as a source to 0
    temporary[0]->distance = 0;
    buildMinHeap(temporary, n);
    //showHeap(temporary, n);

    // Apply Dijkstra Algorithm
    int counter = n;
    while(counter > 0){
        struct GraphNode* currentNode = temporary[0];
        counter = counter - 1;
        swap(temporary[0], temporary[counter]);
        // now look all the neighbours of it
        int total_neighbor = currentNode->total_neighbors;
        for(int i = 0; i < total_neighbor; ++i){
            // now check the condition
            struct GraphNode* neighborNode = currentNode->neighbors[i];
            int edgeWeight = currentNode->weights[i];
            if(neighborNode->distance > currentNode->distance + edgeWeight){
                // edge relaxation step
                neighborNode->distance = currentNode->distance + edgeWeight;
            }
        }
        // heapify the nodes, so the changes may appear
        buildMinHeap(temporary, counter);
        //showHeap(temporary, n);
    }
    cout<<"\nMinimum Distance: \n";
    for(int i = 0; i < n; ++i){
        cout<<"Node: "<<temporary[i]->value<<", Shortest Path: "<<temporary[i]->distance<<"\n";
    }

    return 0;
}