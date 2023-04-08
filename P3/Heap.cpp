#include <cstdlib>
#include <iostream>
#include "ModifiedCDA.cpp"

using namespace std;

template <typename keytype>
class Heap {
    private:
        CDA<keytype> heapArray;     //this is the heap
        int size;                   //this is the size of the heap for easy, accurate access
    public:
        Heap() {        //default constructor
            size = 0;       //build an empty CDA class array
            CDA<keytype> temp; heapArray = temp;
        }
        Heap(keytype k[], int s) {      //this is the constructor given an array and size
            size = s;
            CDA<keytype> array(size); heapArray = array;    //initialize heaparray to a new CDA object
            //keytype* temp = new keytype(size);
            //for(int i = 0; i < size; i++) temp[i] = k[i];   //build a copy of array k
            for(int i = 0; i < size; i++) heapArray[i] = k[i];   //copy temp over to the heaparray
            BottomUpBuild();                //sort the values in temp into heap order
        }
        ~Heap() {}                      //this is the destructor, deafults to the CDA desctructor as that's the only necessary memory to free
        Heap &operator=(const Heap &init) {
            size = init.size;
            for(int i = 0; i < size; i++) heapArray[i] = init.heapArray[i];
        }
        Heap(const Heap &init) {
            size = init.size;
            for(int i = 0; i < size; i++) heapArray[i] = init.heapArray[i];
        }
        keytype peekKey() {             //this returns the minimum value of the tree without making edits
            return heapArray[0];
        }
        keytype extractMin() {          //this returns the minimum value of the tree after it has been removed
            keytype Min = heapArray[0];
            heapArray[0] = heapArray[size - 1]; size--;
            BubbleDown(0, heapArray[0]);
            return Min;
        }
        void insert(keytype k) {        //adds the key to the last spot in the tree then checks to fix heap order
            int kIndex = size;
            size++; heapArray.AddEnd(k);    //simple addend to the dynamic array heap
            bool Right = true;
            if(kIndex % 2 == 1) Right = false;  //check if we put it in the left or right child of its parent
            BubbleUp(kIndex, k, Right);         //bubble up the data
        }
        void printKey() {               //prints all the keys in index order of the heap array
            for(int i = 0; i < size; i++) cout << heapArray[i] << " ";
            cout << endl;
        }
        void BottomUpBuild() {       //helper function used for the constructor with input to fix the array and keep the constructor short
            bool isLeftData, isRightData;       //boolean values to check if left and right children have any data
            for(int i = size - 1; i >= 0; i--) {
                if((i*2 + 1) >= size) isLeftData = false; else isLeftData = true;   //check both children to see if we have any data
                if((i*2 + 2) >= size) isRightData = false; else isRightData = true;
                if(isLeftData) {            //if we have left children, continue
                    if(isRightData) {       //if both leaves had children, check if left is smaller than right
                        if(heapArray[i*2 + 1] < heapArray[i*2 + 2] && heapArray[i*2 + 1] < heapArray[i]) {  //if left is smaller than right and should be swapped up, swap it
                            keytype temp = heapArray[i]; heapArray[i] = heapArray[i*2 + 1]; heapArray[i*2 + 1] = temp;
                            BubbleDown(i*2 + 1, temp);
                        } else if(heapArray[i*2 + 2] < heapArray[i*2 + 1] && heapArray[i*2 + 2] < heapArray[i]) {
                            keytype temp = heapArray[i]; heapArray[i] = heapArray[i*2 + 2]; heapArray[i*2 + 2] = temp;
                            BubbleDown(i*2 + 2, temp);
                        }
                    } else {                //else if there is no right data, check if left should be swapped up
                        if(heapArray[i*2 + 1] < heapArray[i]) {     //if it should be swapped, swap it
                            keytype temp = heapArray[i]; heapArray[i] = heapArray[i*2 + 1]; heapArray[i*2 + 1] = temp;
                            BubbleDown(i*2 + 1, temp);
                        }
                    }
                }                       //check if right is there regardless, if left was swapped up this will fail. If not, it will check if right should be swapped up
                if(isRightData) {       //if we have right data, check it it should be swapped up
                    if(heapArray[i*2 + 2] < heapArray[i]) {         //if right should be swapped up, swap it
                        keytype temp = heapArray[i]; heapArray[i] = heapArray[i*2 + 2]; heapArray[i*2 + 2] = temp;
                        BubbleDown(i*2 + 2, temp);
                    }
                }
            }
        }
        void BubbleUp(int index, keytype k, bool Right) {       //recursive helper function to bubble a new value to the point it needs to be
            if(index == 0) return;                              //check if we reached the top
            int parentindex;
            if(Right) parentindex = (index - 2) / 2;            //set the parentindex for either case
            else parentindex = (index - 1) / 2;
            if(k < heapArray[parentindex]) {                    //check if the key is smaller for both cases
                heapArray[index] = heapArray[parentindex]; heapArray[parentindex] = k;  //if it is, swap current with the parent and prep the next bubble
                if(parentindex % 2 == 1) Right = false; else Right = true;
                BubbleUp(parentindex, k, Right);                                        //perform the next bubble
            }
            return;
        }
        void BubbleDown(int index, keytype k) {
            if(index >= size) return;   //make sure we're in the bounds
            if((index*2 + 1) < size && (index*2 + 2) < size) {
                if(heapArray[index*2 + 1] < heapArray[index*2 + 2] && heapArray[index*2 + 1] < k) {
                    heapArray[index] = heapArray[index*2 + 1]; heapArray[index*2 + 1] = k;  //if both are true, swap down to the left and try the next children
                    BubbleDown(index*2 + 1, k);
                } else if(heapArray[index*2 + 2] < heapArray[index*2 + 1] && heapArray[index*2 + 2] < k) {
                    heapArray[index] = heapArray[index*2 + 2]; heapArray[index*2 + 2] = k;  //if both are true, swap down to the right and try the next children
                    BubbleDown(index*2 + 2, k);
                }
            } else if((index*2 + 1) < size && heapArray[index*2 + 1] < k) {    //check if the left child exists and then if it's smaller
                heapArray[index] = heapArray[index*2 + 1]; heapArray[index*2 + 1] = k;  //if both are true, swap down to the left and try the next children
                BubbleDown(index*2 + 1, k);
            } else if((index*2 + 2) < size && heapArray[index*2 + 2] < k) {  //check if the right child exists and then if it's smaller
                heapArray[index] = heapArray[index*2 + 2]; heapArray[index*2 + 2] = k;  //if both are true, swap down to the right and try the next children
                BubbleDown(index*2 + 2, k);
            }
            return;
        }
};