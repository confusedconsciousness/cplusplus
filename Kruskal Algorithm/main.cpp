#include <iostream>
using namespace std;
// this program will implement Kruskal algorithm
// kruskal make use of Disjoint sets
// it also maintains a sorted array according to weights
// it's a Greedy Algorithm

// Disjoint sets implementation
// ----------------------------------------------------------------------------------------
// define two structure ahead of time
struct Node;
struct Container;

struct Node{
    int value; // uniquely identifies each nodes
    struct Node* next; // points toward the next node (acts as link)
    struct Container* representative; // points toward its representative set
};

struct Container{
    struct Node* head; // points toward the node which is directly attached to container
    struct Node* tail; // points toward the node which is present in the end
    int length; // take account of the total length
};

// define a function that will create a node
struct Node* createNode(int value){
    struct Node* newNode = new Node();
    newNode->value = value;
    newNode->next = NULL;
    newNode->representative = NULL;
    return newNode;
}

// define a function which will create create a disjoint sets
struct Container* make_set(struct Node** arrayOfNodes, int value){
    // initialise the container
    struct Container* newContainer = new Container();
    // since there is only one node attached to the container the head and tail will be same
    newContainer->head = arrayOfNodes[value];
    newContainer->tail = arrayOfNodes[value];
    newContainer->length = 1; // only 1 node is attached
    arrayOfNodes[value]->representative = newContainer;

    return newContainer; // return the container
}

void union_set(int indexOfNode1, int indexOfNode2, struct Node** arrayOfNodes, struct Container** arrayOfContainer){
    // we'll be given two nodes
    struct Container* container1 = arrayOfNodes[indexOfNode1]->representative;
    struct Container* container2 = arrayOfNodes[indexOfNode2]->representative;
    // if both containers are same the nodes provided can't be disjoint, so do nothing
    if(container1 != container2){
        // union them
        // pick the container having greater length
        int length1 = container1->length;
        int length2 = container2->length;

        if(length1 > length2){
            // union the container2 to container1, i.e change the representative element of container2 to point to container1
            // container1 tail node should point to container2 head
            container1->tail->next = container2->head;
            // container1 tail should point to the container2 tail
            container1->tail = container2->tail;
            struct Node* temp = container2->head;
            while(temp != NULL){
                // change the representative element
                temp->representative = container1;
                temp = temp->next;
            }
            // furthermore update the length of container1
            container1->length += container2->length;
            // delete the container2
            arrayOfContainer[indexOfNode2] = NULL;

            delete container2;
        }else{
            // repeat the above procedure but take container2 as main container
            container2->tail->next = container1->head;
            container2->tail = container1->tail;
            struct Node* temp = container1->head;
            while(temp != NULL){
                temp->representative = container2;
                temp = temp->next;
            }
            container2->length += container1->length;
            // delete the container1
            arrayOfContainer[indexOfNode1] = NULL;
            delete container1;
        }

    }
}
// ----------------------------------------------------------------------------------------




// Structure to take care of edges
struct Edge{
    int node1;
    int node2;
    int weight;
};

struct Edge* createEdge(int node1, int node2, int weight){
    struct Edge* newEdge = new Edge();
    newEdge->node1 = node1;
    newEdge->node2 = node2;
    newEdge->weight = weight;
    return newEdge;
}




// sorting algorithm
// we'll be using Quick Sort for this algorithm because its time complexity is O(n * log(n)) on average
int partition(struct Edge **A, int start, int end){
    int pivot = A[end]->weight;
    int i = start - 1;
    for(int j = start; j < end; ++j){
        if(A[j]->weight < pivot){
            ++i;
            swap(A[i], A[j]);
        }
    }
    ++i;
    swap(A[i], A[end]);
    return i;

}


void quickSort(struct Edge **A, int start, int end){
    if(start < end){

        int pIndex = partition(A, start, end);
        quickSort(A, start, pIndex - 1);
        quickSort(A, pIndex + 1, end);

    }

}


int main() {
    // input will be in the following format
    // n -> total nodes in graph
    // edges -> total edges
    // weight, node1, node2

    int n, total_edges;
    cin >> n;
    cin >> total_edges;
    struct Edge *arrayOfEdges[total_edges];
    for (int i = 0; i < total_edges; ++i) {
        int node1, node2, weight;
        cin >> node1 >> node2 >> weight;
        arrayOfEdges[i] = createEdge(node1, node2, weight);
    }


    // first task is to sort the arrayOfEdges  based on its weights (ascending order)
    quickSort(arrayOfEdges, 0, total_edges - 1);
    // arrayOfEdges will now be in sorted order, let's print it out to verify
    /*cout << "\n";
    for (int i = 0; i < total_edges; ++i) {
        cout << arrayOfEdges[i]->weight << " ";
    }
    cout << "\n";
     */
    // works fine

    // now starts our algorithm
    // first we need to create nodes
    struct Node* arrayOfNodes[n];
    for(int i = 0; i < n; ++i){
        arrayOfNodes[i] = createNode(i);
    }


    // MAKE SET
    struct Container* arrayOfContainers[n];
    for(int i = 0; i < n; ++i){
        arrayOfContainers[i] = make_set(arrayOfNodes, i);
    }

    // now start the union process
    // UNION
    int minimum_weight = 0;
    for(int i = 0; i < total_edges; ++i){
        struct Edge* temp = arrayOfEdges[i]; // these are in sorted order
        struct Container* container1 = arrayOfNodes[temp->node1]->representative;
        struct Container* container2 = arrayOfNodes[temp->node2]->representative;
        if(container1 != container2){
            minimum_weight += temp->weight;
            union_set(temp->node1, temp->node2, arrayOfNodes, arrayOfContainers);
        }


    }
    // print the minimum spanning weight

    cout<<"Minimum Weight: "<<minimum_weight;

    return 0;
}
