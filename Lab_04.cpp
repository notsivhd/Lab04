#include <cstdlib>
#include <cstdio>
#include <utility>
#include <iostream>

using namespace std;

int main(){
	
	// variables
	string type;
	string probabilities = " ";
	string nodes;
	string queries = " ";

while(getline(cin, type)){
	if (type == "[Nodes]")
	{
		getline(cin, nodes);
		cout << nodes << "\n";
	}

	if (type == "[Probabilities]")
	{
		while(getline(cin, probabilities) && !probabilities.empty()){
			cout << probabilities << "\n";
		}
	}

	if (type == "[Queries]")
	{
		while(getline(cin, queries) && !queries.empty()){
			cout << queries << "\n";
		}
	}
}
	return 0;
}