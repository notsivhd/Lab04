#include <cstdlib>
#include <cstdio>
#include <utility>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

struct Node
{
	string name;
	vector< struct Node *> parents;
	unordered_map< string, float > probTable;
	float probability;
};

struct compareHidden
{
	bool operator()(const string& s1, const string& s2)
    {
        int i = 0, j = 0;
        bool a;
        if(s1.front() == '+' || s1.front() == '-')
        {    
            i = 1;
        }
        if(s2.front() == '+' || s2.front() == '-')
        {
            j = 1;
        }
        a = (s1.substr(i, s1.length()) < s2.substr(j, s2.length()));
        //cout << s1.substr(i, s1.length()) << " " << s2.substr(j, s2.length()) << endl;
        return a;
	}
};

	unordered_map< string, struct Node *> nodes;
	unordered_map< string, struct Node *>:: iterator node_it;
    unordered_map< string, struct Node *>:: iterator parent_it;
    unordered_map< string, struct Node *>:: iterator hidden_it;

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

void hiddenNodes(set< string, compareHidden > given)
{
    set<string, compareHidden>::iterator given_it;

    for(auto&x: given)
    {
        if(x[0] == '+' || x[0] == '-')
        {
            hidden_it = nodes.find(x.substr(1, x.length())) ;  
        }
        else
        {
            hidden_it = nodes.find(x);   
        }
        
        if( hidden_it != nodes.end() )
        {
            if(hidden_it->second->parents.size() > 0)
            {
                for(auto&y: hidden_it->second->parents)              
                {
                    //cout << "y " << y->name << ".." << endl;
                    given_it = given.find(y->name);
                    if( given_it == given.end() )                   
                    {
                        given.insert(y->name);
                    }
                }
            }
        }
    }

    for(auto&x: given)
    {
        cout << x << endl;
    }
}

/*void chainRule()
{
    //numerador = todos + parents
    //denominador = todos despues de | + parents

    //obtener los primeros dos caracteres de cada elemento

    //for each element in numerador
        //obtener nodo
        //obtener probTble del nodo seleccionado
}

void sumOut( //vector de nodos )
{
    //for each element in vector
        //get parents

    //for each parent
        //duplicate actual expresions by adding pair of sum with +p and - p
}*/

int main()
{	
    // Variable definition
	string type;
	string probability = " ";
	string node;
	string query = " ";

    string keyT;
    string numerator;
    string denominator;

	vector<string> v_nodes;
	vector<string> v_probabilities;
	vector<string> v_queries;
    vector<string> v_cases;
	vector<string> v_parents;

    set<string, compareHidden> num;
    set<string, compareHidden> den;
	float p;
    int i, j;

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
                //cout << "-" << v_nodes[nodes_index] << "-" << endl;
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
                    //cout << "//" << v_cases[0] << "//" << endl;

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
                                //cout << "==" << v_parents[j] << "==" << endl;
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
                            //cout << "@" << v_cases[1].substr(1, v_cases[1].length() ) << "@" << endl;
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
            for(auto&x: nodes)
            {
                for(auto&y: x.second->probTable)
                {
                    cout << y.first<< " " << y.second << endl;
                }
            }
	    }

	    if (type == "[Queries]")
	    {
		    cout << "[Queries]"<< "\n";
		    while(getline(cin, query) && !query.empty())
            {
                denominator = "";
                numerator = "";

			    //cout << query << "\n";
                if ( verify_independance(query, '|') )
                {
			        split(query,'|',v_queries);
                    if ( verify_independance(v_queries[0], ',') )
                    {
                        //Tiene mas de un query
                       split(v_queries[0], ',', v_cases);

                        for(j = 0; j < v_cases.size(); j++)
                        {
                            //cout << ".." << v_cases[j] << ".." << endl;
                            numerator += v_cases[j];
                            num.insert(v_cases[j]);
                        }  
                    }
                    else
                    {
                        numerator = v_queries[0];
                        num.insert(v_queries[0]);
                    }
                    v_cases.clear();

                    if ( verify_independance(v_queries[1], ',') )
                    {
                        //Tiene mas de un query
                       split(v_queries[1], ',', v_cases);

                        for(j = 0; j < v_cases.size(); j++)
                        {
                            //cout << "==" << v_cases[j] << "==" << endl;
                            denominator += v_cases[j];
                            num.insert(v_cases[j]);
                            den.insert(v_cases[j]);
                        }                
                    }
                    else
                    {
                        denominator = v_queries[1];
                        num.insert(v_queries[1]);
                        den.insert(v_queries[1]);
                    }
                    v_cases.clear();
                }
                else
                {
                    numerator = query;
                    num.insert(query);
                }

                

                numerator += denominator;
                cout << endl << "Num y den" << endl;
                cout << numerator << " " << num.size() << endl;
                cout << denominator << " " << den.size() <<endl;

                //num

                cout << "******num******" << endl;
                hiddenNodes(num);
                cout << "************" << endl;

                //den
                cout << "******den******" << endl;
                hiddenNodes(den);
                cout << "************" << endl;
	            //for each element in v_queries look for the parents and construc numerator
	            //denominator = nodes and parents after |
	
	            //completar las tablas

	            //calcular probabilidad preguntando a la tabla de cada nodo si conoce los elementos (Ruben)

                v_queries.clear();
                num.clear();
                den.clear();
	        }
        }     
    }
    return 0;
    
}
