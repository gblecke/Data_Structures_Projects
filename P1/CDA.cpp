#include <cstdlib>
#include <iostream>
using namespace std;
template <typename cdArray>
void Reorder(cdArray arr[], int capacity, int Front, int Back, int size);
template <typename cdArray>
void mergeSort(cdArray arr[], int front, int back);
template <typename cdArray>
void merge(cdArray arr[], int front, int mid, int back);

template <typename cdArray>
class CDA {
    private:
        int size;       //this is the size equivalent to all initialized data
        int capacity;   //this is the total capacity of the CDA, including uninitialized data
        int Front;      //this is the index of the front of the array
        int Back;       //this is the index of the back of the array
        cdArray *dynamicArray;
        cdArray initVal;
    public:
        bool Initialized;
        int *Shadow1, *Shadow2;
        CDA() {         //default constructor
            size = 0;
            capacity = 1;
            Front = 0;
            Back = 0;
            dynamicArray = new cdArray[1];
            Initialized = false;
        }
        CDA(int s) {    //constructor for a CDA of specified size
            this->size = s;
            this->capacity = s;
            Front = 0;
            Back = size - 1;
            dynamicArray = new cdArray[s];
            Initialized = false;
        }
        CDA(int s, cdArray init) {      //constructor for a CDA that initializes data to the init value using O(1) running time
            size = s;
            capacity = s;
            Front = 0;
            Back = s - 1;
            dynamicArray = new cdArray[s];
            Shadow1 = new int[s]; Shadow2 = new int[s];
            initVal = init; Initialized = true;
        }
        CDA &operator=(const CDA &init){
            size = init.size;
            capacity = init.capacity;
            Front = init.Front;
            Back = init.Back;
            dynamicArray = new cdArray[capacity];
            Initialized = init.Initialized;
            for(int i = 0; i < size; i++) {
                dynamicArray[(Front + i) % capacity] = init.dynamicArray[(Front + i) % capacity];
            }
            return *this;
        }
        CDA(const CDA &init) {
            size = init.size;
            capacity = init.capacity;
            Front = init.Front;
            Back = init.Back;
            Initialized = init.Initialized;
            dynamicArray = new cdArray[capacity];
            for(int i = 0; i < size; i++) {
                dynamicArray[(Front + i) % capacity] = init.dynamicArray[(Front + i) % capacity];
            }
        }
        ~CDA() {
            delete[] dynamicArray;
        }
        cdArray &operator[](int i) {
            if(i > size - 1 || i < 0) {
                cout << "Given input is out of bounds." << endl;
                return dynamicArray[i % size];
            }
            if(Initialized == true) {
                if(Shadow1[Shadow2[i]] == i) return dynamicArray[(Front + i) % capacity];
                else {
                    dynamicArray[(Front + i) % capacity] = initVal;
                    Shadow2[i] = (Front + i) % capacity;
                    Shadow1[(Front + i) % capacity] = i;
                    return dynamicArray[(Front + i) % capacity];
                }
            }
            return dynamicArray[(Front + i) % capacity];
        }
        void AddEnd(cdArray n) {
            if(size == capacity) {
                if(Front > Back) {
                    Reorder(dynamicArray, capacity, Front, Back, size);
                    Front = 0; Back = size - 1;
                }
                int oldCap = capacity;
                capacity *= 2;
                cdArray *temp = new cdArray[capacity];
                for(int i = 0; i < oldCap; i++) temp[i] = dynamicArray[(Front + i) % oldCap];
                delete[] dynamicArray; dynamicArray = new cdArray[capacity];
                for(int i = 0; i < oldCap; i++) dynamicArray[i] = temp[i];
                Front = 0;
                Back = size - 1;
            }
            size++;
            Back = (Back + 1) % capacity;
            dynamicArray[Back] = n;
        }
        void AddFront(cdArray n) {
            if(size == capacity) {
                if(Front > Back) {
                    Reorder(dynamicArray, capacity, Front, Back, size);
                    Front = 0; Back = size - 1;
                }
                int oldCap = capacity;
                capacity *= 2;
                cdArray *temp = new cdArray[capacity];
                for(int i = 0; i < oldCap; i++) temp[i] = dynamicArray[(Front + i) % oldCap];
                delete[] dynamicArray; dynamicArray = new cdArray[capacity];
                for(int i = 0; i < oldCap; i++) dynamicArray[i] = temp[i];
                Front = 0;
                Back = size - 1;
            }
            size++;
            Front  = (Front - 1 + capacity) % capacity;
            dynamicArray[Front] = n;
        }
        void DelEnd() {
            size--;
            Back = (Back - 1 + capacity) % capacity;
            if(size <= (capacity / 4)) {
                if(Front > Back) {
                    Reorder(dynamicArray, capacity, Front, Back, size); Front = 0; Back = size - 1;
                }
                int oldCap = capacity;
                capacity = capacity / 2;
                cdArray *temp = new cdArray[capacity];
                for(int i = 0; i < size; i++) temp[i] = dynamicArray[(Front + i) % oldCap];
                delete[] dynamicArray; dynamicArray = new cdArray[capacity];
                for(int i = 0; i < size; i++) dynamicArray[i] = temp[i];
            }
        }
        void DelFront() {
            size--;
            Front = (Front + 1) % capacity;
            if(size <= (capacity / 4)) {
                if(Front > Back) {
                    Reorder(dynamicArray, capacity, Front, Back, size); Front = 0; Back = size - 1;
                }
                int oldCap = capacity;
                capacity = capacity / 2;
                cdArray *temp = new cdArray[capacity];
                for(int i = 0; i < size; i++) temp[i] = dynamicArray[(Front + i) % oldCap];
                delete[] dynamicArray; dynamicArray = new cdArray[capacity];
                for(int i = 0; i < size; i++) dynamicArray[i] = temp[i];
            }
        }
        int Length() {return this->size;}
        int Capacity() {return this->capacity;}
        int frontIndex() {return this->Front;}
        int backIndex() {return this->Back;}
        cdArray Select(int k) {
            if(Initialized == true) {
                for(int i = 0; i < size; i++) {
                    if(Shadow1[Shadow2[i]] != i) { 
                        Shadow2[i] = (Front + i) % capacity;
                        Shadow1[Shadow2[i]] = i;
                        dynamicArray[Shadow2[i]] = initVal;
                    }
                }
            }
            Reorder(dynamicArray, capacity, Front, Back, size);
            Front = 0; Back = size - 1;
            cdArray pivot = dynamicArray[rand() % size];
            cdArray *L = new cdArray[size], *E = new cdArray[size], *G = new cdArray[size]; cdArray *temp = new cdArray[size]; 
            for(int i = 0; i < size; i++) temp[i] = dynamicArray[i];
            int Lc = 0, Ec = 0, Gc = 0, currsize = size; int tempFront = Front, tempBack = Back;
            while(tempFront <= tempBack) {
                for(int i = 0; i < currsize; i++) {
                    if(temp[i] < pivot) {
                        L[Lc] = temp[i]; Lc++;
                    } else if(temp[i] == pivot) {
                        E[Ec] = temp[i]; Ec++;
                    } else {
                        G[Gc] = temp[i]; Gc++;
                    }
                }
                if(k <= Lc) {
                    currsize = Lc; delete[] temp; temp = new cdArray[currsize];
                    for(int i = 0; i < currsize; i++) temp[i] = L[i];
                } else if(k <= Lc+Ec) {
                    return pivot;
                } else {
                    currsize = Gc; delete[] temp; temp = new cdArray[currsize];
                    for(int i = 0; i < currsize; i++) temp[i] = G[i];
                    k = k - (Lc + Ec);
                }
                Lc = 0; Ec = 0; Gc = 0; delete[] L; delete[] E; delete[] G;
                L = new cdArray[currsize]; E = new cdArray[currsize]; G = new cdArray[currsize];
                pivot = temp[rand() % currsize];
                tempBack = currsize - 1;
            }
            return pivot;
        }
        void Sort() {
            Reorder(dynamicArray, capacity, Front, Back, size);
            Front = 0; Back = size - 1;
            mergeSort(dynamicArray, Front, Back);
        }
        int Search(cdArray e) {
            for(int i = 0; i < size; i++) {
                if(e == dynamicArray[(Front + i) % capacity]) {return i; }
            }
            return -1;
        }
        int BinSearch(cdArray e) {
            int left = Front; int right = Back; int mid = 0;
            while(left < right) {
                mid = (left + right) / 2;
                if(e > dynamicArray[mid]) {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }
            if(e == dynamicArray[left]) {
                return left;
            } else if(left == Back || right == Back) {
                return -size;
            } else {
                return -(left + 1);
            }
        }
};
template <typename cdArray>
void Reorder(cdArray arr[], int capacity, int Front, int Back, int size) {
    cdArray *temp = new cdArray[capacity];
    for(int i = 0; i < size; i++) {
        temp[i] = arr[(Front + i) % capacity];
    }
    for(int i = 0; i < size; i++) {
        arr[i] = temp[i];
    }
}
template <typename cdArray>
void mergeSort(cdArray arr[], int front, int back) {
    if(front >= back) { return; }
    int mid = front + ((back - front) / 2);
    mergeSort(arr, front, mid);
    mergeSort(arr, mid + 1, back);
    merge(arr, front, mid, back);
}
template <typename cdArray>
void merge(cdArray arr[], int front, int mid, int back) {
    int leftsize = mid - front + 1;
    int rightsize = back - mid;
    cdArray *left = new cdArray[leftsize];
    cdArray *right = new cdArray[rightsize];
    for(int i = 0; i < leftsize; i++) {
        left[i] = arr[front + i];
    }
    for(int j = 0; j < rightsize; j++) {
        right[j] = arr[mid + j + 1];
    }
    int leftindex = 0; int rightindex = 0; int mergeindex = front;
    while(leftindex < leftsize && rightindex < rightsize) {
        if(left[leftindex] <= right[rightindex]) {
            arr[mergeindex] = left[leftindex];
            leftindex++; mergeindex++;
        } else {
            arr[mergeindex] = right[rightindex];
            rightindex++; mergeindex++;
        }
    }
    while(leftindex < leftsize) {
        arr[mergeindex] = left[leftindex];
        leftindex++; mergeindex++;
    }
    while(rightindex < rightsize) {
        arr[mergeindex] = right[rightindex];
        rightindex++; mergeindex++;
    }
}