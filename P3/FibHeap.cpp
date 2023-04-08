#include <iostream>
using namespace std;

template <typename keytype>
class FibNode {
    public:
        int rank;
        keytype key;
        FibNode* parent;
        FibNode* left;
        FibNode* right;
        FibNode* child;
};

template <typename keytype>
class FibHeap {
    private:
        FibNode<keytype>* minimum;       //always points to the minimum node
        FibNode<keytype>* RankArray[30];     //array of pointers that points at the first node of each rank
        FibNode<keytype>* Head;          //points at the first node in the list of tree heads
    public:
        FibHeap() {             //baseline constructor of the class
            minimum = new FibNode<keytype>; minimum = NULL;
            Head = new FibNode<keytype>; Head = NULL;
            *RankArray = new FibNode<keytype>[30];
            for(int i = 0; i < 30; i++) RankArray[i] = NULL;
        }
        FibHeap(keytype k[], int s) {       //initialized constructor of the class
            minimum = new FibNode<keytype>; Head = new FibNode<keytype>; minimum = NULL; Head = NULL;
            *RankArray = new FibNode<keytype>[30];
            for(int i = 0; i < 30; i++) RankArray[i] = NULL;
            for(int i = 0; i < s; i++) {
                insert(k[i]);
            }
            consolidate();
        }
        ~FibHeap() {            //destructor for the class
            FibNode<keytype>* current = Head->right;
            FibNode<keytype>* next = current->right;
            while(current != Head) {
                delete current;
                current = next;
                next = next->right;
            }
            delete Head;
            delete minimum;
            delete[] *RankArray;
        }
        FibHeap &operator=(const FibHeap &init) {       //copy assignment operator for the class
            return init;
        }
        FibHeap(const FibHeap &init) {          //copy constructor for the class
        }
        keytype peekKey() {         //returns the minimum key, nothing else
            return minimum->key;
        }
        keytype extractMin() {      //deletes the node with the minimum key then returns the minimum
            keytype min = minimum->key;
            FibNode<keytype>* current; 
            FibNode<keytype>* nextchild;     //declare the variables to be used
            FibNode<keytype>* tempMin = minimum;
            if(tempMin->child != NULL) {
                current = tempMin;
            } else {                        //set current if a child exists
                current = NULL;
            }
            if(current != NULL) {               //if current is not null, pop the children of the node up
                nextchild = NULL;
                while(nextchild != NULL) {    //loop through to pop all the children up 
                    nextchild = current->right;
                    tempMin->left->right = current;
                    current->right = tempMin;
                    current->left = tempMin->left;
                    tempMin->left = current;
                    current->parent = NULL;
                    current = nextchild;
                }
            }
            tempMin->left->right = tempMin->right;      //remove the minimum from the list
            tempMin->right->left = tempMin->left;
            if(Head == minimum) Head = Head->right;     //update the head
            minimum = tempMin->right;
            consolidate();                  //call to consolidate the nodes of the tree
            return min;
        }
        void insert(keytype k) {    //inserts a new rank 0 node with the given key
            FibNode<keytype>* temp = newNode(k);
            if(Head == NULL) {
                Head = temp; minimum = temp;            //if the heap is empty, make the new node the head
                Head->left = Head; Head->right = Head;
            } else {
                FibNode<keytype>* current = Head->left;     //otherwise, insert it at the back
                temp->left = current; temp->right = Head;
                Head->left = temp; current->right = temp;
            }
            if(temp->key < minimum->key) {              //update the minimum if the new key is smaller
                minimum = temp;
            }
        }
        void merge(FibHeap<keytype> &H2) {      //combines H2 into the current heap
            FibNode<keytype>* newtail = H2.Head->left;        //pointers to make the operation easier
            FibNode<keytype>* origtail = Head->left;
            FibNode<keytype>* H2Head = H2.Head;
            origtail->right = H2Head; H2Head->left = origtail;        //make the merge circular on the ends
            Head->left = newtail; newtail->right = Head;                  //connect the middle of the heaps
            if(H2.minimum->key < minimum->key) minimum = H2.minimum;      //check if we should update the minimum pointer
        }
        void printKey() {       //prints the keys in by printing its rank first, then doing a modified preorder traversal of the tree named
            FibNode<keytype>* current = Head;
            cout << "B" << current->rank << endl;   //print the head's heap regardless of how large
            cout << current->key << " ";
            RecursivePrint(current->child); cout << endl << endl; 
            current = current->right;
            while(current != Head) {            //print every node after Head and stop when we loop back to the head
                cout << "B" << current->rank << endl << current->key << " ";
                RecursivePrint(current->child);
                cout << endl << endl;
                current = current->right;
            }
        } 
        FibNode<keytype>* newNode(keytype k) {      //helper function to initialize a new node for insert. Makes insert less bulky
            FibNode<keytype>* node = new FibNode<keytype>;
            node->key = k; node->rank = 0;
            node->parent = NULL; node->child = NULL;
            node->left = NULL; node->right = NULL;
            return node;
        }
        void RecursivePrint(FibNode<keytype>* current) {    //helper function to print a heap tree from the parent node
            if(current == NULL) return;         //return on a null node
            cout << current->key << " ";        //print the key
            RecursivePrint(current->child);     //next child
            FibNode<keytype>* temp = current;
            FibNode<keytype>* cycle = current->right;
            while(cycle != NULL) {          //call to print the right children of the nodes
                cout << cycle->key << " ";
                RecursivePrint(cycle->child);
                cycle = cycle->right;
            }
        }
        void consolidate() {
            int temprank;
            FibNode<keytype>* temp;
            FibNode<keytype>* conspar;      //declare variables
            FibNode<keytype>* conschi;
            for(int i = 0; i < 30; i++) RankArray[i] = NULL;    //clear the RankArray from previous consolidates
            conspar = Head;
            RankArray[conspar->rank] = conspar;             //set first iteration so first loop works
            conspar = conspar->right;
            while(conspar != Head) {                        //first loop to cover every node in the upper list
                temprank = conspar->rank;
                while(RankArray[temprank] != NULL) {        //second loop to consolidate nodes of the same rank
                    conschi = RankArray[temprank];
                    if(conspar->key > conschi->key) {       //swap so conspar is always the less key'd node
                        temp = conspar;
                        conspar = conschi;
                        conschi = temp;
                    }
                    if(Head == conschi) Head = conspar;     //update head pointer so we don't break it
                    conschi->left->right = conschi->right;  //close links where conschi is being removed from
                    conschi->right->left = conschi->left;
                    conschi->right = NULL;                  //prevent children from being circular
                    conschi->left = conschi;
                    conschi->parent = conspar;
                    if(conspar->child != NULL) {            //if conspar has children, slot conschi in no problem
                        conschi->right = conspar->child;
                        conschi->left = conspar->child->left;
                        conspar->child->left = conschi;
                    }
                    conspar->child = conschi;               //always make conschi the direct child
                    conspar->rank++;                        //inc the rank
                    RankArray[temprank] = NULL;             //clear the rank array pointer
                    temprank++;                             //inc temp rank
                }
                RankArray[temprank] = conspar;              //set the pointer for the new sized heap
                conspar = conspar->right;                   //inc the loop condition
            }
            //next rebuild the order of the fibheap
            minimum = Head;
            Head = NULL;
            for(int i = 0; i < 30; i++) {       //loop through rankarray
                if(RankArray[i] != NULL) {
                    RankArray[i]->left = RankArray[i]; RankArray[i]->right = RankArray[i];
                    if(Head != NULL) {              //if this is not the first node found, include it
                        Head->left->right = RankArray[i];
                        RankArray[i]->right = Head; 
                        RankArray[i]->left = Head->left;
                        Head->left = RankArray[i];
                        if(RankArray[i]->key < minimum->key) { //set minimum
                            minimum = RankArray[i];
                        }
                    } else {
                        Head = RankArray[i];            //if this is the first node found, make it the head
                    }
                }
            }
        }
};