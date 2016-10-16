#include <cstdlib>
#include <cstdio>
#include <utility>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void split(const string& s, char delim,vector<string>& v) {
    auto i = 0;
    auto pos = s.find(delim);
    while (pos != string::npos) {
      v.push_back(s.substr(i, pos-i));
      i = ++pos;
      pos = s.find(delim, pos);

      if (pos == string::npos)
         v.push_back(s.substr(i, s.length()));
    }
}

int main(){
	// variables
	string type;
	string probabilitie = " ";
	string node;
	string querie = " ";
	vector<string> v_nodes;
	vector<string> v_probabilities;
	vector<string> v_queries;
	float p;

while(getline(cin, type)){
	if (type == "[Nodes]")
	{
		getline(cin, node);
		cout << node << "\n";
		split(node,'=',v_nodes);
	}

	if (type == "[Probabilities]")
	{
		while(getline(cin, probabilitie) && !probabilitie.empty()){
			cout << probabilitie << "\n";
			split(probabilitie,'=',v_probabilities);
			p = stof(v_probabilities[v_probabilities.size()-1]);
			cout << p << "\n";
		}
	}

	if (type == "[Queries]")
	{
		while(getline(cin, querie) && !querie.empty()){
			cout << querie << "\n";
			split(querie,'=',v_queries);
		}
	}
}
	return 0;
}