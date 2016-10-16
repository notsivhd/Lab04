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

	vector<string> nodes;
	vector<string> cases;
	pair<vector<string>,float> p_cases;
	vector<pair<vector<string>,float>> probabilities;
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
		int i = 0;
		while(getline(cin, probabilitie) && !probabilitie.empty()){
			
			cout << probabilitie << "\n";
			split(probabilitie,'=',v_probabilities);
			split(v_probabilities[i],'|',cases);
			
			if (v_probabilities[i]){
				
			}

			p_cases = {cases,v_probabilities.size()-1};
			cout << "probabilitie: " << v_probabilities[i]<< " ";
			cout << cases[1] << "\n";
			probabilities.push_back(p_cases);

			p = stof(v_probabilities[v_probabilities.size()-1]);
			cout << p << "\n";
			i += 2;
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