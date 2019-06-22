#include <iostream>
using namespace std;

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



int main() {

    // we need to tell if two friends are somehow connected
    // inputs
    // 5 // 5 represents total nodes
    // 4 // 4 represents total relations
    // 0 1
    // 1 2
    // 3 4
    // 4 5
    // it means 0 knows 1, 1 knows 2
    // output should be
    // 0 -> 1 -> 2
    // 3 -> 4 -> 5
    int n;
    cin>>n;
    // create n nodes
    struct Node* arrayOfNodes[n];
    for(int i = 0; i < n; ++i){
        arrayOfNodes[i] = createNode(i);
    }

    int relations;
    cin>>relations;

    int INPUTS[relations][2];
    for(int i = 0; i < relations; ++i){
        for(int j = 0; j < 2; ++j){
            cin >> INPUTS[i][j];
        }
    }
    // first we'll call make_sets operation
    // for that we need an array that will store all the containers
    // MAKE SET
    struct Container* arrayOfContainers[n];
    for(int i = 0; i < n; ++i){
        arrayOfContainers[i] = make_set(arrayOfNodes, i);
    }

    // now start the union process
    // UNION
    for(int i = 0; i < relations; ++i){
        int indexOfNode1 = INPUTS[i][0];
        int indexOfNode2 = INPUTS[i][1];

        union_set(indexOfNode1, indexOfNode2, arrayOfNodes, arrayOfContainers);

    }
    // print the groups
    int counter = 1;
    for(int i = 0; i < n; ++i){

        if(arrayOfContainers[i] != NULL){
            // print the links
            struct Node* temp = arrayOfContainers[i]->head;
            cout<<"Group "<<counter<<": ";
            while(temp != NULL){
                cout<<temp->value<<" ";
                temp = temp->next;
            }
            cout<<"\n";
            counter += 1;
        }
    }


    return 0;
}