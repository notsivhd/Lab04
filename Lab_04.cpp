#include <cstdlib>
#include <cstdio>
#include <utility>
#include <iostream>

using namespace std;

int main(){
	
	// variables
	string parameters;
	string nodes;
	
	getline(cin, parameters);
	cout << parameters <<"\n";
	getline(cin, nodes);
	cout << nodes << "\n";	
	getline(cin, parameters);
	cout << parameters << "\n";
	return 0;
}