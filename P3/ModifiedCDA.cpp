using namespace std;

template <typename cdArray>
class CDA {
    private:
        int size;       //this is the size equivalent to all initialized data
        int capacity;   //this is the total capacity of the CDA, including uninitialized data
        int Front;      //this is the index of the front of the array
        int Back;       //this is the index of the back of the array
        cdArray *dynamicArray;
    public:
        CDA() {         //default constructor
            size = 0;
            capacity = 1;
            Front = 0;
            Back = 0;
            dynamicArray = new cdArray[1];
        }
        CDA(int s) {    //constructor for a CDA of specified size
            this->size = s;
            this->capacity = s;
            Front = 0;
            Back = size - 1;
            dynamicArray = new cdArray[s];
        }
        CDA &operator=(const CDA &init){
            size = init.size;
            capacity = init.capacity;
            Front = init.Front;
            Back = init.Back;
            dynamicArray = new cdArray[capacity];
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
            return dynamicArray[(Front + i) % capacity];
        }
        int Length() {return this->size;}
        int Capacity() {return this->capacity;}
        int frontIndex() {return this->Front;}
        int backIndex() {return this->Back;}
        void AddEnd(cdArray n) {
            if(size == capacity) {
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
                int oldCap = capacity;
                capacity = capacity / 2;
                cdArray *temp = new cdArray[capacity];
                for(int i = 0; i < size; i++) temp[i] = dynamicArray[(Front + i) % oldCap];
                delete[] dynamicArray; dynamicArray = new cdArray[capacity];
                for(int i = 0; i < size; i++) dynamicArray[i] = temp[i];
            }
        }
};