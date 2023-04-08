#include <iostream>
#include <cstdlib>
using namespace std;

template <typename keytype>
class Treap {
    private:
        struct Node {
            Node *left;
            Node *right;
            Node *parent;
            keytype key;
            int leftsize;
            float priority;
        };
    public:
        Node *Root;
        Node *Tnull;
        int numNodes;
        Treap() {
            Root = new Node; Tnull = new Node;
            Tnull = NULL;
            Root = Tnull;
            numNodes = 0;
        }
        Treap(keytype k[], float p[], int s) {
            Root = new Node; Tnull = new Node;
            Tnull = NULL;
            Root = Tnull;
            numNodes = 0;
            for(int i = 0; i < s; i++) {
                insert(k[i], p[i]);
            }
        }
        ~Treap() {
            deleteTree(Root);
            delete Tnull;
        }
        Treap &operator=(const Treap &init) {
            this->Root = new Node; this->Tnull = new Node;
            this->Tnull = NULL;
            this->Root->key = init.Root->key;
            this->Root->priority = init.Root->priority;
            this->Root->leftsize = init.Root->leftsize;
            this->Root = BuildCopy(this->Root, this->Root, init.Root);
            this->numNodes = init.numNodes;
            return *this;
        }
        Treap(const Treap &init) {
            this->Root = new Node; this->Tnull = new Node;
            this->Tnull = NULL;
            this->Root->key = init.Root->key;
            this->Root->priority = init.Root->priority;
            this->Root->leftsize = init.Root->leftsize;
            this->Root = BuildCopy(this->Root, this->Root, init.Root);
            this->numNodes = init.numNodes;
        }
        float search(keytype k) {   //search for the k, return the priority, If not found, return -1
            Node* temp = Root;
            while(temp != Tnull) {
                if(k == temp->key) return temp->priority;
                else if(k > temp->key) temp = temp->right;
                else temp = temp->left;
            }
            return -1;
        }
        void insert(keytype k, float p) {
            numNodes++;
            Root = recursiveInsert(Root, Root, k, p);
        }
        void insert(keytype k) {    //insert the key with a randomly generated priority
            float p = rand() / (1.0 * RAND_MAX);
            Root = recursiveInsert(Root, Root, k, p);
            numNodes++;
        }
        int remove(keytype k) { //remove the key and replace with the predecessor, return 1 if removed and 0 is not found
            int Flag[1];
            Flag[0] = 0;
            Root = recursiveRemove(Root, Root, k, Flag);
            if(Flag[0] == 1) {
                numNodes--;
                return 1;
            } else {
                return 0;
            }
        }
        int rank(keytype k) {   //return the rank of k, 1 is the lowest rank, return 0 if not in tree
            Node* curr = Root;
            int Rank = 1;
            while(curr != Tnull) {
                if(k > curr->key) {
                    Rank = Rank + curr->leftsize + 1;
                    curr = curr->right;
                } else if(k == curr->key) {
                    return Rank + curr->leftsize;
                } else {
                    curr = curr->left;
                }
            }
            return 0;
        }
        keytype select(int pos) {   //return the key at the given rank
            Node* curr = Root;
            while(curr != Tnull) {
                if(pos == curr->leftsize + 1) {
                    return curr->key;
                } else if(pos <= curr->leftsize) {
                    curr = curr->left;
                } else {
                    pos = pos - (curr->leftsize + 1);
                    curr = curr->right;
                }
            }
            return Root->key;
        }
        keytype successor(keytype k) {   //return the succesor of k, If it has none, return k
            int temp = rank(k) + 1;
            if(temp != 1) return select(temp);
            return k;
        }
        keytype predecessor(keytype k) {    //return the predecessor of k, If it has none, return k
            int temp = rank(k) - 1;
            if(temp >= 1) return select(temp);
            return k;
        }
        int size() {    //return the number of nodes in the tree
            return numNodes;
        }
        void preorder() {   //prints the keys in preorder traversal
            preprint(Root);
            cout << endl;
        }
        void inorder() {    //prints the keys in inorder traversal
            inprint(Root);
            cout << endl;
        }
        void postorder() {  //prints the keys in postorder traversal
            postprint(Root);
            cout << endl;
        }
        void preprint(Node* curr) {
            if(curr == Tnull) return;
            cout << curr->key << " ";
            preprint(curr->left);
            preprint(curr->right);
        }
        void inprint(Node* curr) {
            if(curr == Tnull) return;
            inprint(curr->left);
            cout<< curr->key << " ";
            inprint(curr->right);
        }
        void postprint(Node* curr) {
            if(curr == Tnull) return;
            postprint(curr->left);
            postprint(curr->right);
            cout << curr->key << " ";
        }
        Node* recursiveInsert(Node* current, Node* prev, keytype k, float p) {
            if(current == Tnull) {
                Node* temp = new Node;
                temp->key = k; temp->priority = p;
                temp->left = Tnull; temp->right = Tnull; temp->parent = prev;
                temp->leftsize = 0;
                return temp;
            } else if(current->key > k) {
                current->leftsize = current->leftsize + 1;
                current->left = recursiveInsert(current->left, current, k, p);
                if(current->left->priority < current->priority) {
                    current = rightRotate(current, current->left);
                }
            } else {
                current->right = recursiveInsert(current->right, current, k, p);
                if(current->right->priority < current->priority) {
                    current = leftRotate(current, current->right);
                }
            }
            return current;
        }
        Node* recursiveRemove(Node* current, Node* prev, keytype k, int Flag[]) {
            if(current == Tnull) {
                return current;
            } else if(k < current->key) {
                current->left = recursiveRemove(current->left, current, k, Flag);
            } else if(k > current->key) {
                current->right = recursiveRemove(current->right, current, k, Flag);
            } else {
                Flag[0] = 1;
                if(current->left == Tnull) {
                    if(current->right != Tnull) {
                        current->right->parent = current->parent;
                    }
                    current = current->right;
                } else if(current->right == Tnull) {
                    if(current->left != Tnull) {
                        current->left->parent = current->parent;
                    }
                    current = current->left;
                } else if(current->left->priority < current->right->priority) {
                    current = rightRotate(current, current->left);
                    current->right = recursiveRemove(current->right, current, k, Flag);
                } else {
                    current = leftRotate(current, current->right);
                    current->left = recursiveRemove(current->left, current, k, Flag);
                }
                return current;
            }
            return current;
        }
        Node* leftRotate(Node* current, Node* R) {
            current->right = R->left;
            if(R->left != Tnull) {
                R->left->parent = current;
            }
            R->parent = current->parent;
            if(current == Root) {
                Root = R;
            } else if(current->parent->left == current) {
                current->parent->left = R;
            } else {
                current->parent->right = R;
            }
            R->leftsize = current->leftsize + R->leftsize + 1;
            R->left = current;
            current->parent = R;
            return R;
        }
        Node* rightRotate(Node* current, Node* L) {
            current->left = L->right;
            if(L->right != Tnull) {
                L->right->parent = current;
            }
            L->parent = current->parent;
            if(current == Root) {
                Root = L;
            } else if(current->parent->right == current) {
                current->parent->right = L;
            } else {
                current->parent->left = L;
            }
            current->leftsize = current->leftsize - L->leftsize - 1;
            L->right = current;
            current->parent = L;
            return L;
        }
        void deleteTree(Node* current) {
            if(current == Tnull) {
                return;
            }
            deleteTree(current->left);
            deleteTree(current->right);
            remove(current->key);
        }
        Node* BuildCopy(Node* current, Node* prev, const Node* initcurrent) {
            if(initcurrent == NULL) {
                return NULL;
            }
            current->key = initcurrent->key;
            current->priority = initcurrent->priority;
            current->leftsize = initcurrent->leftsize;
            current->left = new Node; current->right = new Node;
            current->left = BuildCopy(current->left, current, initcurrent->left);
            current->right = BuildCopy(current->right, current, initcurrent->right);
            current->parent = prev;
            return current;
        }
};