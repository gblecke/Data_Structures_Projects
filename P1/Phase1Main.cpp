#include <iostream>
using namespace std;
#include "CDA.cpp"

void foo(CDA<int> x) {
	for (int i=0; i<x.Length()/2; i++)
		x[i] = x[x.Length()/2+i];
	// X => "6 7 8 9 10 15 19 6 7 8 9 10 15 19 11"	
	for (int i=0; i< x.Length();i++) cout << x[i] << " ";  cout << endl;
}

int main(){
	CDA<float> C(10);
	for (int i=0; i< C.Length();i++) C[i] = i;
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
	// C => "0 1 2 3 4 5 6 7 8 9"
	C.DelFront();
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
	// C => "1 2 3 4 5 6 7 8 9"
	C.DelEnd();
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
	// C => "1 2 3 4 5 6 7 8"
	C.AddEnd(100.0);
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
	// C => "1 2 3 4 5 6 7 8 100"
	C.AddEnd(101.0);	
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
	// C => "1 2 3 4 5 6 7 8 100 101"
	C.DelEnd(); C.DelFront();
	C.AddFront(-100.0); C.AddFront(-200.0);
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
	// C => "-200 -100 2 3 4 5 6 7 8 100"

	CDA<int> A,B;
	for(int i=0; i<10;i++) A.AddEnd(i);
	B = A;   //Testing the copy assignment operator
	A.AddEnd(15); A.AddEnd(19);
	// A => "0 1 2 3 4 5 6 7 8 9 15 19" 
	cout << "Search is " << A.Search(5) << endl;
	// A => "0 1 2 3 4 5 6 7 8 9 15 19" Search => 5
	cout << "BinSearch is " << A.BinSearch(12) << endl;
	// A => "0 1 2 3 4 5 6 7 8 9 15 19" BinSearch => -11
	cout << "Select is " << A.Select(3) << endl;
	// A => "0 1 2 3 4 5 6 7 8 9 15 19" Select => 2
	
	A.Sort();
	
	A.AddFront(10);
	// A => "10 0 1 2 3 4 5 6 7 8 9 15 19"
	cout << "Search is " << A.Search(5) << endl;
	// A => "10 0 1 2 3 4 5 6 7 8 9 15 19" Search => 6
	cout << "Select is " << A.Select(3) << endl;
	// A => "10 0 1 2 3 4 5 6 7 8 9 15 19" Select => 2
	A.Sort();
	// A => "0 1 2 3 4 5 6 7 8 9 10 15 19"
	A.AddEnd(11); A.AddFront(1); A.AddFront(2); A.AddFront(3);
	cout << "Capacity is " << A.Capacity() << endl;
	// A => "3 2 1 0 1 2 3 4 5 6 7 8 9 10 15 19 11"	  Capacity => 32
	A.DelFront(); A.DelFront();
	// A => "1 0 1 2 3 4 5 6 7 8 9 10 15 19 11"	  Capacity => 32
	for (int i=0; i< A.Length();i++) cout << A[i] << " ";  cout << endl;

	foo(A);  //Testing the copy constructor;

	for (int i=0; i< A.Length();i++) cout << A[i] << " ";  cout << endl;
	// A => "1 0 1 2 3 4 5 6 7 8 9 10 15 19 11"	  Capacity => 32

	for (int i=0; i< B.Length();i++) cout << B[i] << " ";  cout << endl;
	// B => "0 1 2 3 4 5 6 7 8 9"
	
	for(int i=1; i<200; i++) {
		CDA<double> D(100000,-1.0);
		for(int j=1; j<100; j++)
			D[i*j] = i*j;
		for(int j=50*i; j<51*i; j++)
			if(D[j] != -1.0) cout << "D["<<j<<"] is : "<<D[j] << endl;  //should output where D[j] is : j once per value of i
	}
	CDA<char> E(10,'X');
	E[5] = 'A';
	cout << E.Select(1) << endl;   //should output A
}