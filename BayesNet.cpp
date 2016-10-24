#include <cstdlib>
#include <cstdio>
#include <utility>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <algorithm>  
#include <iterator> 

using namespace std;

struct Node
{
	string name;
	set<string> parents;
	map< string, double> probTable;
	double probability;
};

struct compareHidden
{
	bool operator()(const string& s1, const string& s2)
    {
        int i = 0, j = 0;
        if(s1.front() == '+' || s1.front() == '-')
        {    
            i = 1;
        }
        if(s2.front() == '+' || s2.front() == '-')
        {
            j = 1;
        }
        return (s1.substr(i, s1.length()) < s2.substr(j, s2.length()));;
	}
};

	map< string, struct Node *> nodes;
	map< string, struct Node *>:: iterator node_it;
    map< string, struct Node *>:: iterator parent_it;
    map< string, struct Node *>:: iterator hidden_it;

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
    for(auto &x: given)
    {
        if( x[0] == '+' || x[0] == '-')
        {
            hidden_it = nodes.find( x.substr(1, x.length())) ;  
        }
        else
        {
            hidden_it = nodes.find(x);   
        }

        if( hidden_it != nodes.end() )
        {
            for(auto &y: hidden_it->second->parents)              
            {
                given.insert(y);
            }
        }
    }

   for(auto&x: given)
    {
        cout << x << endl;
    }
}

vector<string> completeExpression(string s)
{
    int i=0, j;
    vector<string> exp;
    vector<string> aux;

    exp.push_back("");
    while(i < s.size())
    {
        if(s[i] == '+' || s[i] == '-')
        {
            for(j = 0; j < exp.size(); j++)
            {
                exp[j] += s[i];
                exp[j] += s[i+1];
            }
            i+=2;
        }
        else
        {
            aux = exp;
            copy(aux.begin(), aux.end(), back_inserter(exp));

            for(j = 0; j < exp.size()/2; j++)
            {
                exp[j] += '+';
                exp[j] += s[i];
            }

            for(; j < exp.size(); j++)
            {
                exp[j] += '-';
                exp[j] += s[i];
            }
            i++;
        }
    }    
    return exp;
}

double chainRule(string s)
{
    int i = 1, j=1;
    vector<string> match;
    vector<string> aux;
    vector<string> intersect;

    double result = 1.0;

    cout << s << endl;
    while(i < s.size())
    {      
        node_it = nodes.lower_bound(s.substr(i, i));
        if(node_it != nodes.end())
        {
            j = 1;       
            while(j < s.size() )
            {  
                for(auto&k: node_it->second->probTable)                
                {
                    auto pos = k.first.find(s.substr(j-1, 2));
                    if(pos < k.first.size())
                    {
                        //cout << s.substr(j-1, 2) << " esta en " << k.first << endl;
                        aux.push_back(k.first);
                    }
                }

                if(aux.size() > 0 && match.size() == 0)
                {
                    match = aux;
                    aux.clear();
                } 
                else if(aux.size() > 0 && match.size() > 0)
                {
                    sort(aux.begin(), aux.end());
                    sort(match.begin(), match.end());
                    set_intersection(aux.begin(), aux.end(), match.begin(), match.end(), back_inserter(intersect));
                    match.clear();
                    match = intersect;
                    aux.clear();
                    intersect.clear();
                }               
                j+=2;
            }
            
            cout << "factor = " << match[0] << " = ";
            double p = node_it->second->probTable[match[0]];   
            cout << p; 
            result *= p;
            match.clear();
        }
        cout << endl;
        i+=2;
    }
    return result;
}


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

    vector<string> exp;

    set<string, compareHidden> num;
    set<string, compareHidden> den;
	double p;
    int i, j;
    size_t a;

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
			    p = stod(v_probabilities[v_probabilities.size()-1]);

			    if ( verify_independance(v_probabilities[i], '|') )
                {
				    split(v_probabilities[i], '|', v_cases);

                    node_it = nodes.find(v_cases[0].substr(1, v_cases[0].length() ));
                    if( node_it != nodes.end() )
                     {
                        keyT.insert(0, v_cases[0].substr(0, 2));

                        if ( verify_independance(v_cases[1], ',') )
                        {
                            //Tiene mas de un padre
                           split(v_cases[1], ',', v_parents);

                            for(j = 0; j < v_parents.size(); j++)
                            {
                                parent_it = nodes.find( v_parents[j].substr( 1, v_parents[j].length() ) );
                                if(parent_it != nodes.end())
                                {
                                    keyT += v_parents[j].substr(0, 2);
                                    node_it->second->parents.insert(v_parents[j].substr( 1, v_parents[j].length() ) );
                                }
                                else
                                {
                                    cout << "Nodo padre no existe" << endl;
                                }
                            }
                        }
                        else
                        {
                            parent_it = nodes.find( v_cases[1].substr(1, v_cases[1].length() ));
                            if(parent_it != nodes.end())
                            {
                                keyT += v_cases[1].substr(0, 2);
                                node_it->second->parents.insert( v_cases[1].substr(1, v_cases[1].length() ) );
                            }
                            else
                            {
                                cout << "Nodo padre no existe" << endl;
                            }
                        }

                        v_parents.clear();
                        node_it->second->probTable.emplace(keyT, static_cast<double>(p));

                        keyT[0] = '-';
                        node_it->second->probTable.emplace(keyT, static_cast<double>(1-p));
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
                        node_it->second->probTable.emplace(keyT, static_cast<double>(p));     

                        keyT.clear();
                        keyT.insert(0, '-' + v_probabilities[i].substr(1, 1));
                        node_it->second->probTable.emplace(keyT, static_cast<double>(1-p)); 

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
                cout << x.second->name << endl;

                for(auto&y: x.second->parents)
                {
                    cout << " p  " << y << endl;
                }
                for(auto&z: x.second->probTable)
                {
                    cout << "     " << z.first<< " " << z.second << endl;
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

                if ( verify_independance(query, '|') )
                {
			        split(query,'|',v_queries);
                    if ( verify_independance(v_queries[0], ',') )
                    {
                        //Tiene mas de un query
                       split(v_queries[0], ',', v_cases);

                        for(j = 0; j < v_cases.size(); j++)
                        {
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
/*
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
*/
                
                
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


    /*exp = completeExpression("-B+JAE");    
    sort(exp.begin(), exp.end());
    for(j = 0; j < exp.size(); j++)
    {
        cout << exp[j] << " = " << chainRule(exp[j]) << endl;
        p_num += chainRule(exp[j]);
    }
    chainRule(exp[0]);*/


    double p_num = 0.0;
    double p_den = 0.0;
    exp = completeExpression("+B+JAE");    
    sort(exp.begin(), exp.end());
    for(j = 0; j < exp.size(); j++)
    {
        //cout << exp[j] << " = " << chainRule(exp[j]) << endl;
        p_num += chainRule(exp[j]);
    }
    cout << "num " << p_num <<  endl;



    cout << "\n\n\n";
    exp.clear();
    exp = completeExpression("B+JAE");    
    sort(exp.begin(), exp.end());
    for(j = 0; j < exp.size(); j++)
    {
        //cout << j << " " << exp[j] << " = " << chainRule(exp[j]) << endl << endl;;
        p_den += chainRule(exp[j]);
        cout << endl;
    }
    cout << "den " << p_den <<  endl;

    cout << p_num/p_den << endl;
    return 0;
    
}
