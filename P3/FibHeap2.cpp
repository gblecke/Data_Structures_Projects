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

        }
        FibHeap(const FibHeap &init) {          //copy constructor for the class

        }
        keytype peekKey() {         //returns the minimum key, nothing else
            return minimum->key;
        }
        keytype extractMin() {      //deletes the node with the minimum key then returns the minimum
            keytype min = minimum->key;
            FibNode<keytype>* currchild; FibNode<keytype>* nextchild;
            FibNode<keytype>* temp;
            if(minimum->child != NULL) {
                currchild = minimum->child;
            } else {
                currchild = NULL;
            }
            if(currchild != NULL) {
                temp = currchild;
                while(nextchild != temp) {
                    nextchild = currchild->right;
                    minimum->left->right = currchild;       //pop child up into the list without removing min from the list yet
                    currchild->right = minimum;             //previous: tried popping min out then putting children up, caused segfaults
                    currchild->left = minimum->left;
                    minimum->left = currchild;
                    currchild->parent = NULL;
                    currchild = nextchild;
                }
            }
            minimum->left->right = minimum->right;
            minimum->right->left = minimum->left;
            minimum = minimum->right;
            consolidate();      //consolidate
            temp = Head->right;
            if(Head->key < minimum->key) minimum = Head;
            while(temp != Head) {
                if(temp->key < minimum->key) minimum = temp;
                temp = temp->right;
            }
            return min;
        }
        void insert(keytype k) {    //inserts a new rank 0 node with the given key
            FibNode<keytype>* temp = newNode(k);
            if(Head == NULL) {
                Head = temp; minimum = temp;
                Head->left = Head; Head->right = Head;
            } else {
                FibNode<keytype>* current = Head->left;
                temp->left = current; temp->right = Head;
                Head->left = temp; current->right = temp;
            }
            if(temp->key < minimum->key) {
                minimum = temp;
            }
        }
        void merge(FibHeap<keytype> &H2) {      //combines H2 into the current heap
            FibNode<keytype>* newtail = H2.Head->left;        //pointers to make the operation easier
            FibNode<keytype>* origtail = Head->left;
            origtail->right = H2.Head; H2.Head->left = origtail;        //make the merge circular on the ends
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
            if(current == NULL) return;
            cout << current->key << " ";
            RecursivePrint(current->child);
            FibNode<keytype>* temp = current;
            FibNode<keytype>* cycle = current->right;
            while(cycle != temp) {
                cout << cycle->key << " ";
                RecursivePrint(cycle->child);
                cycle = cycle->right;
            }
        }
        void consolidate() {
            int ranktemp;
            FibNode<keytype>* current = Head;           //declare variables from updating in while loops
            FibNode<keytype>* fromArray;
            RankArray[current->rank] = current;         //declare members of the rank array. only starts with head to help while loop condition
            current = current->right;                   //after the head is put in the rank array, continue to the loop.
            while(current != Head) {                    
                ranktemp = current->rank;               //get the rank of the current tree
                while(RankArray[ranktemp] != NULL) {        //second loop if that rank array slot is already occupied
                    fromArray = RankArray[ranktemp];        //set a temp pointer
                    if(current->key < fromArray->key) {
                        fromArray->left->right = fromArray->right;      //pop fromarray out of the top layer
                        fromArray->right->left = fromArray->left;
                        fromArray->left = fromArray; fromArray->right = fromArray;       
                        fromArray->parent = current;                        //ensure no memory leaks
                        if(current->child != NULL) {
                            current->child->left = fromArray;               //if current already has a child, add the new child to the left of the tree branches
                            fromArray->right = current->child;              //move current child to the right
                            fromArray->left = current->child->left;         //fix circular pointers
                            current->child->left->right = fromArray;
                            current->child = fromArray;                     //make fromarray the new child at the left of the children
                            current->rank++;                                //increment rank
                        } else {
                            current->child = fromArray;                     //if current has no children, just make fromarray the child and inc rank
                            current->rank++;
                        }
                    } else {
                        current->left->right = current->right;
                        current->right->left = current->left;               //carbon copy of the original if, just flipped if current->key is larger
                        current->left = current; current->right = current;
                        current->parent = fromArray;
                        if(fromArray->child != NULL) {
                            fromArray->child->left = current;
                            current->right = fromArray->child;
                            current->left = fromArray->child->left;
                            fromArray->child->left->right = current;
                            fromArray->child = current;
                            fromArray->rank++;
                        } else {
                            fromArray->child = current;
                            fromArray->rank++;
                        }
                        current = fromArray;                //make current point to fromarray so current is always pointing at the parent
                    }
                    if(current->right == current) Head = current;    //update head pointer
                    RankArray[ranktemp] = NULL;
                    ranktemp++;
                }
                RankArray[current->rank] = current;
                current = current->right;
            }
            Head = NULL;
            for(int i = 0; i < 30; i++) {
                if(RankArray[i] != NULL) {
                    RankArray[i]->left = RankArray[i];
                    RankArray[i]->right = RankArray[i];
                    if(Head != NULL) {
                        Head->left->right = RankArray[i];
                        RankArray[i]->right = Head;
                        RankArray[i]->left = Head->left;
                        Head->left = RankArray[i];
                        Head = RankArray[i];
                    } else {
                        Head = RankArray[i];
                    }
                }
            }
        }
};