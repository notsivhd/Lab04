#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <utility>
#include <set>

using namespace std;

typedef pair<string, bool> State;
typedef vector<State> Keys;
struct hash_fn
{
	size_t operator()(const Keys &key)
	{
		size_t num = 0;
		for(int i = 0; i < key.size(); i++)
		{
			num += ( (hash<string>()(key[i].first) ^ hash<bool>()(key[i].second)) << i );
		}		
		return num;
	}
};

bool operator==(const Keys &key1, const Keys &key2)
	{
		if(key1.size() != key2.size())		
		{
			for(int i = 0; i < key1.size(); i++)
			{
				if(key1[i].second != key2[i].second)
				{
					return false;
				}

				/*for(int j = 0; j < key[i].first.size())
				{
					if( key1[i][j] != key2[i][j] )
					{
						return false;
					}
				}*/
			}		
			return true;
	}
}


typedef unordered_map< Keys, double, hash_fn > pTable;
struct VariableAssignment
{
	string VariableName;
	vector< struct VariableAssignment *> parents;
	pTable probTable;
	double probability;
};

int main()
{
	int  i, num;
	bool boolValue;
	string name;
	double probability;

	vector< pair<string, bool> > aux;
	unordered_map< string, struct VariableAssignment *> nodes;
	unordered_map< string, struct VariableAssignment *>:: iterator node_it;
	unordered_map< string, struct VariableAssignment *>:: iterator parent_it;

	//Read input file

	//Name of all existing nodes
	cin >> num;

	for(i = 0; i < num; i++)
	{
		struct VariableAssignment *node = new VariableAssignment;
		cout << i <<  " " << node;

		cout << "Name ";
		cin >> name;
		node->VariableName = name;
		nodes.insert( make_pair(name, node) );
		cout << endl;
	}


	//Probabilities

	//+Ill = 0.001
	cout << "bool ";
	cin >> boolValue;
	cout << "name ";
	cin >> name;
	cout << "prob ";
	cin >> probability;

	node_it = nodes.find(name);
	cout << node_it->second << endl;
	if(node_it != nodes.end())
	{	
		//node_it->second->parents = NULL;		
		node_it->second->probability = probability;
	}

	//+Test | +Ill = 0.9
	//+Test | -Ill = 0.05

	for(i = 0; i < 2; i++)
	{
		cout << "bool ";
		cin >> boolValue;
		cout << endl;
		cout << "name ";
		cin >> name;

		node_it = nodes.find(name);
		if(node_it != nodes.end())
		{	
			cout << "par bool ";
			cin >> boolValue;	
			cout << "par name ";
			cin >> name;
			cout << "par prob ";
			cin >> probability;

			parent_it = nodes.find(name);
			if(parent_it != nodes.end())
			{	
				if(node_it->second->parents.size() == 0)		
				{	
					cout << parent_it->second << endl;
					node_it->second->parents.push_back(parent_it->second);		
					aux.push_back( make_pair(name, boolValue) );
					node_it->second->probTable.insert(aux, probability);
				}
			}
		}
	}
}













