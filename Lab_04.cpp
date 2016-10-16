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

bool verify_independance(string s, char c){

	for(int  i = 0;i < s.length();i++)
	{
    	if(s[i] == c)
    	{
        	return true;
    	}
	}
	return false;
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
		cout<<"[Probabilities]" << "\n";
		int i = 0;
		while(getline(cin, probabilitie) && !probabilitie.empty()){
			split(probabilitie,'=',v_probabilities);
			p = stof(v_probabilities[v_probabilities.size()-1]);
			if (verify_independance(v_probabilities[i],'|')){
				split(v_probabilities[i],'|',cases);
				p_cases = {cases,p};
				probabilities.push_back(p_cases);
			}
			p_cases = {v_probabilities,p};
			probabilities.push_back(p_cases);
			cout << v_probabilities[i] << '=' << p <<"\n";
			cout << v_probabilities[i] <<"\n";
			i += 2;
		}
	}

	if (type == "[Queries]")
	{
		cout << "[Queries]"<< "\n";
		while(getline(cin, querie) && !querie.empty()){
			cout << querie << "\n";
			split(querie,'=',v_queries);
		}
	}
}
	return 0;
}