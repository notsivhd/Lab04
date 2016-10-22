#include <cstdlib>
#include <cstdio>
#include <utility>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <unordered_map>

using namespace std;

struct Node
{
	string name;
	vector< struct Node *> parents;
	unordered_map< string, float > probTable;
	float probability;
};

void split(string& s, char delim, vector<string>& v)
{
    int i = 0;
    char pos = s.find(delim);

    if(s.back() == ' ')
    {
        s.pop_back();
    }

    while (pos != string::npos) 
    {
        v.push_back(s.substr(i, pos-i));
        i = ++pos; 

        if(s[i] == ' '){
            i++;
        }
        pos = s.find(delim, pos);

        if (pos == string::npos)
        {
            v.push_back(s.substr(i, s.length()));
        }
    }
}

bool verify_independance(string s, char c)
{
	for(int  i = 0; i < s.length(); i++)
	{
    	if(s[i] == c)
    	{
        	return true;
    	}
	}
	return false;
}

int main()
{	
    // Variable definition
	string type;
	string probability = " ";
	string node;
	string query = " ";

     string keyT;

	vector<string> v_nodes;
	vector<string> v_probabilities;
	vector<string> v_queries;
    vector<string> v_cases;
	vector<string> v_parents;

	float p;
    int i, j;

	unordered_map< string, struct Node *> nodes;
	unordered_map< string, struct Node *>:: iterator node_it;
    unordered_map< string, struct Node *>:: iterator parent_it;

    // Read input file

    // Get names of the nodes
    while(getline(cin, type))
    {
	    if (type == "[Nodes]")
	    {
		    getline(cin, node);
		    //cout << node << "\n";

            v_nodes.clear();
		    split(node, ',', v_nodes);

		    for(int nodes_index = 0;  nodes_index < v_nodes.size(); nodes_index++)
		    {
                cout << "-" << v_nodes[nodes_index] << "-" << endl;
			    struct Node *element = new Node;
			    element->name = v_nodes[nodes_index];
			    nodes.emplace( v_nodes[nodes_index], element );
		    }
        }

        // Get the probabilities to generate probability table
	    if (type == "[Probabilities]")
	    {
		    cout<<"[Probabilities]" << "\n";
		    i = 0;
            keyT = "";

		    while( getline(cin, probability) && !probability.empty() )
            {
                // Get probability value
			    split(probability, '=', v_probabilities);
			    p = stof(v_probabilities[v_probabilities.size()-1]);

			    if ( verify_independance(v_probabilities[i], '|') )
                {
                    // Get parents
				    split(v_probabilities[i], '|', v_cases);
                    cout << "//" << v_cases[0] << "//" << endl;

                    node_it = nodes.find(v_cases[0].substr(1, v_cases[0].length() ));
                    if( node_it != nodes.end() )
                     {
                        //cout << "sub " << v_cases[0].substr(0, 2)  << endl;
                        keyT.insert(0, v_cases[0].substr(0, 2));

                        if ( verify_independance(v_cases[1], ',') )
                        {
                            //Tiene mas de un padre
                           split(v_cases[1], ',', v_parents);

                            for(j = 0; j < v_parents.size(); j++)
                            {
                                cout << "==" << v_parents[j] << "==" << endl;
                                parent_it = nodes.find( v_parents[j].substr( 1, v_parents[j].length() ) );
                         
                                if(parent_it != nodes.end())
                                {
                                    //cout << "sub " << v_parents[j].substr(0, 2) << endl;
                                    keyT += v_parents[j].substr(0, 2);
                                    node_it->second->parents.push_back(parent_it->second);
                                }
                                else
                                {
                                    cout << "Nodo padre no existe" << endl;
                                }
                            }
                        }
                        else
                        {        
                            cout << "@" << v_cases[1].substr(1, v_cases[1].length() ) << "@" << endl;
                            parent_it = nodes.find( v_cases[1].substr(1, v_cases[1].length() ));

                            if(parent_it != nodes.end())
                            {
                                //cout << "sub " << v_cases[1].substr(0, 2) << endl;
                                keyT += v_cases[1].substr(0, 2);
                                node_it->second->parents.push_back(parent_it->second);
                            }
                            else
                            {
                                cout << "Nodo padre no existe" << endl;
                            }
                        }

                        v_parents.clear();
                        node_it->second->probTable.emplace(keyT, static_cast<float>(p));
                    }
                    else{
                        cout << "Nodo no existe" << endl;
                    }

			    }	
			    else
                {
				    // Node is a root element
                    cout << "No parents " << v_probabilities[i] << " " << i <<endl;
                    if(v_probabilities[i].back() == ' ')
                    {
                        node_it = nodes.find(v_probabilities[i].substr(1, v_probabilities[i].length() - 2));
                    }
                    else
                    {
                        node_it = nodes.find(v_probabilities[i].substr(1, v_probabilities[i].length() ));
                    }
                    
                    if( node_it != nodes.end() )
                     {
                        keyT.insert(0, v_probabilities[i].substr(0, 2));
                        node_it->second->probTable.emplace(keyT, static_cast<float>(p));     
                    }
                    else{
                        cout << "Not found" << endl;
                    }          
			    }

                v_cases.clear();    
                keyT.clear(); 
			    i += 2;                 
		    }
            
            v_probabilities.clear();
            /*for(auto&x: nodes)
            {
                for(auto&y: x.second->probTable)
                {
                    cout << y.first<< " " << y.second << endl;
                }
            }*/
	    }

	    if (type == "[Queries]")
	    {
		    cout << "[Queries]"<< "\n";
		    while(getline(cin, query) && !query.empty())
            {
			    cout << query << "\n";
			    split(query,'=',v_queries);

			    //for each element in v_queries look for the parents and construc numerator
			    //denominator = nodes and parents after |
			
			    //completar las tablas

			    //calcular probabilidad preguntando a la tabla de cada nodo si conoce los elementos (Ruben)

     
		    }

            v_queries.clear();
	    }        
    }
	return 0;
}
