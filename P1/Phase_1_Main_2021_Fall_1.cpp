#include <iostream>
#include <fstream>
using namespace std;
#include "CDA.cpp"

void test1(ostream &fp);
void test2(ostream &fp);
void test3(ostream &fp);
void test4(ostream &fp);
void test5(ostream &fp);
void test6(ostream &fp);

void foo(CDA<int> x) {
	for (int i=0; i<x.Length()/2; i++){
		int temp = x[i];
		x[i] = x[x.Length()/2+i];
		x[x.Length()/2+i] = temp;
	}
}

int printWrapper = 0;

int main(int argc, char **argv){
	int testToRun = atoi(argv[1]);
	switch (testToRun){
		case 1:
			test1(cout);
			break;
		case 2:
			test2(cout);
			break;
		case 3:
			test3(cout);
			break;
		case 4:
			test4(cout);
			break;
		case 5:
			test5(cout);
			break;
		case 6:
			test6(cout);
			break;
	}
}

void test1(ostream &fp){
	if(printWrapper) fp << "Running test 1" << endl;
	//fp.open("test1.out");
	CDA<int> C(25);
	for (int i=0; i< C.Length();i++) C[i] = i*10;
	for (int i=0; i< C.Length();i++) fp << C[i] << " "; fp << endl;
	C.DelFront();
	for (int i=0; i< C.Length();i++) fp << C[i] << " ";  fp << endl;
	C.DelEnd();
	for (int i=0; i< C.Length();i++) fp << C[i] << " ";  fp << endl;
	C.AddEnd(1001);
	for (int i=0; i< C.Length();i++) fp << C[i] << " ";  fp << endl;
	C.AddEnd(1005);
	for (int i=0; i< C.Length();i++) fp << C[i] << " ";  fp << endl;
	C.DelEnd(); C.DelEnd();
	C.AddFront(-105); C.AddFront(-250);
	for (int i=0; i< C.Length();i++) fp << C[i] << " ";  fp << endl;
	fp << "Capacity is " << C.Capacity() << endl;

	CDA<int> A;
	int temp = 0;
	for(int i=0; i<25;i++){
		A.AddEnd(i*10);
		if(A.Capacity() != temp){
			temp = A.Capacity();
			fp << "Capacity is " << temp << " ";
		}
	}
    fp << endl;
	fp << "Capacity is " << A.Capacity() << endl;
	fp << "Search is " << A.Search(60) << endl;
	fp << "Select is " << A.Select(2) << endl;
	A.Sort();
	A.AddFront(12); 
	fp << "Search is " << A.Search(60) << endl;
	fp << "Select is " << A.Select(2) << endl;
	A.AddFront(-12);
	A.Sort();
	fp << "BinSearch is " << A.BinSearch(30) << endl;
	A.DelFront(); A.DelFront(); A.AddEnd(61);
	for (int i=0; i< A.Length();i++) fp << A[i] << " ";  fp << endl;
	CDA<int> B;
	B = A;
	A[0] = -1001;
	fp << B[0] << endl;
	foo(A);
	for (int i=0; i< B.Length();i++) fp << B[i] << " ";  fp << endl;
	CDA<long int> testGeneric1(10);
	CDA<short int> testGeneric2(10);
	CDA<double> testGeneric3(10);
	fp << "Passed Generics Test" << endl;
	//fp.close();
	if(printWrapper)fp << "-----------------Finished Test----------------------" << endl;
}

void test2(ostream &fp){
	if(printWrapper) fp << "Running test 2" << endl;   //testing O(nlgn) sort
	CDA<int> A;
	for(int i = 0; i < 500500; i++) A.AddFront(i);
	fp << "Select is " << A.Select(400) << endl;
	fp << "Select is " << A.Select(4000) << endl;
	fp << "Select is " << A.Select(40000) << endl;
	A.Sort();
	fp << "Search is " << A.Search(400) << endl;
	fp << "Search is " << A.Search(4000) << endl;
	fp << "Search is " << A.Search(40000) << endl;
	fp << "Select is " << A.Select(4000) << endl;
	if(printWrapper) fp << "-----------------Finished Test----------------------" << endl;
}

void test3(ostream &fp){
	if(printWrapper) fp << "Running test 3" << endl;   //testing initialization constructor
	int initCounter = 0;
	for(int i=1; i<200; i++) {
		CDA<long double> D(500500,-10.0);
		for(int j=1; j<1000; j++) D[i*j] = i*j;
		for(int j=50*i; j<51*i; j++) 
			if(D[j] != -10.0 && i % 39 == 0){
				cout << "D["<<j<<"] is : "<<D[j] << endl;  //should output where D[j] is : j once per value of i
				initCounter++;
			} 
	}
	int printNumber = 0;
	if(initCounter < 6) printNumber = 5;
	else if(initCounter < 30) printNumber = 4;
	else if(initCounter < 60) printNumber = 3;
	else if(initCounter < 100) printNumber = 2;
	else if(initCounter < 200) printNumber = 1;
	else if(initCounter < 300) printNumber = 0;
	for(int i =0; i < printNumber; i++) cout << "This print counts as a line" << endl;
	CDA<char> E(1000000,'X');
	E[490000] = 'A';
	E[500000] = 'B';
	cout << E.Search('B')<< endl;   //should output 500000
	if(printWrapper) fp << "-----------------Finished Test----------------------" << endl;
}

void test4(ostream &fp){
	if(printWrapper) fp << "Running test 4" << endl;
	CDA<int> A;
	for(int i = 0; i < 50000; i++) {A.AddFront(i);A.AddEnd(100000-i);}
	fp << "A[24999] is " << A[24999] << endl;
	fp << "A[25000] is " << A[25000] << endl;	
	for(int i = 0; i < 25000; i++) {A.DelFront();A.DelEnd();}	
	fp << "A[12499] is " << A[12499] << endl;
	fp << "A[12500] is " << A[12500] << endl;
	fp << "Search is " << A.Search(400) << endl;
	fp << "Select is " << A.Select(4000) << endl;
	A.Sort();
	fp << "BinSearch is " << A.BinSearch(4000) << endl;
	fp << "BinSearch is " << A.BinSearch(50000) << endl;	  //looking for a value not in the array	
	if(printWrapper) fp << "-----------------Finished Test----------------------" << endl;
}


void test5(ostream &fp){
	if(printWrapper) fp << "Running test 5" << endl;	
	CDA<int> A;
	for(int i = 0; i < 1000000; i++) 
	{
		A.AddEnd(i);
	}
	for(int i = 0; i < 23000; i++) 
	{
		int value = A.BinSearch(i);
		if(i % 3500 == 0) fp << "BinSearch at " << i << " is " << value << endl;
	}
	if(printWrapper) fp << "-----------------Finished Test----------------------" << endl;
}


void test6(ostream &fp){
	if(printWrapper) fp << "Running test 6" << endl;
	CDA<int> A;
	for(int i = 0; i < 500000; i++) 
	{
		A.AddFront(i);
	}
	for(int i = 0; i < 50; i++) 
	{
		int value = A.Search(i);
		if(i % 10 == 0) fp << "Search at " << i << " is " << value << endl;
	}
	for(int i = 1; i < 5; i++) 
	{
		int value = A.Select(i);
		fp << "Select at " << i << " is " << value << endl;
	}
	for(int i = 49900; i < 49905; i++) 
	{
		int value = A.Select(i);
		fp << "Select at " << i << " is " << value << endl;
	}
	if(printWrapper) fp << "-----------------Finished Test----------------------" << endl;
}


