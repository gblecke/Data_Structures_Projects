#include <iostream>
#include <cstdlib>
#include <stdlib.h>
using namespace std;
#include "Treap.cpp"

int main(){
	string K[10] = {"A","B","C","D","E","F","G","H","I","K"};
	float P[10] = {0.2,0.95,0.7,0.4,0.5,0.3,0.8,0.1,0.9,0.6};
	
	Treap<string> T1, T2(K,P,10), T3;
	
	for(int i=0; i<10; i++) T1.insert(K[i],P[i]);
	// T1 and T2 should be identical trees
	
	cout << T2.search("C") << endl;
	// Should output 0.7
	
	cout << T1.rank("C") << endl;
	//Should output 3
	
	cout << T1.select(3) << endl;
	//Should output C 
	
	T2.preorder();
	//Should output "H A F D C B E G K I\n"
	//There should be a single 
	//newline after any of the order 
	//method calls
	
	T2.inorder();
	//Should output	A B C D E F G H I K\n
	
	cout << T2.remove("F") << endl;
	//Should output 1
	
	T2.preorder();
	//Should output H A D C B E G K I\n
	
	T2.inorder();
	//Should output	A B C D E G H I K\n
	
	cout << T2.remove("J") << endl;
	//Should output 0
	
	cout <<T2.rank("G") << endl;
	//Should output 6
	
	cout <<T1.successor("E")<<endl;
	//Should output F
	
	cout <<T1.predecessor("B")<<endl;
	//Should output A	
    T3 = T1;
    
    T3.remove("F");	

	cout <<T1.successor("E")<<endl;
	//Should output F

    Treap<int> X;
	for (int i=1;i<1001000;i++) X.insert(i,rand()/(1.0 * RAND_MAX));
	for (int i=1;i<1001000;i++) {
	    if(X.rank(i) != i) cout << "Rank error" << endl;
		if(X.select(i) != i) cout << "Select error" << endl;
	}
	//Should be no output and should take seconds, not minutes
	return 0;
}