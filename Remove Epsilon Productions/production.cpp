
/* 

Name : Prasad Kshirsagar
Entry No : 2016csb1041
Course : Compiler Design (CS315)

Topic : Removing epsilon productions from a grammar

For Grammar : Refer to 'Grammar_productions.txt'

NOTE : Here, epsilon denotes '$' and '@' is special symbol
       used which should not be a part of grammar.

*/

#include <bits/stdc++.h>

using namespace std;


/* Function to get another combination of string */
string get_string_combination(string str, int k)
{
	int len = str.length();
	string out = "";
	for(int i=0;i<len;i++)
	{
		if(i == k)
		{
			// Special symbol '@' used as part of algorithm design which should not be a part of grammar.
			out += '@';                
		}
		else
		{
			out += str[i];
		}

	}

	return out;

}


/* Function to remove extra @ symbol which was inserted to keep length constant */
vector<string> get_simplified_strings(vector<string> Vec)
{
	int lent = Vec.size();
	vector<string> out_vector;
	for(int i=0;i<lent;i++)
	{
		int d = Vec[i].length();
		string s1 = "";
		for(int j=0;j<d; j++)
		{
			if(Vec[i][j] == '@')
			{
				continue;
			}
			else
			{
				s1 += Vec[i][j];
			}

		}
		if(s1 != "" && s1 != "$")
		{
			out_vector.push_back(s1);
		}

	}
	return out_vector;

}






int main()
{


/* File reading to get LHS & RHS of a production separated : */

string line;
ifstream file("Grammar_productions.txt");

// vector for storing LHS of productions 
vector<string> vector_for_lhs; 

// vector for storing RHS of productions
vector<string> vector_for_rhs;

while (getline(file, line)) 
{
	stringstream check1(line);       
	string intermediate;
	vector<string> wordVector;
	
	
	while(getline(check1, intermediate)) 
	{ 
		std::size_t prev = 0, pos;
    	while ((pos = line.find_first_of(" |=", prev)) != std::string::npos)
    	{
        	if (pos > prev)
           		wordVector.push_back(line.substr(prev, pos-prev));
        	prev = pos+1;
    	}

    	if (prev < line.length())
       	wordVector.push_back(line.substr(prev, std::string::npos)); 
	}

	for(int i = 1; i < wordVector.size(); i++)
	{
		vector_for_lhs.push_back(wordVector[0]);
		vector_for_rhs.push_back(wordVector[i]);	
	}

}


/* ---------------- For Finding Nullable set : -----------------------------------------------*/

unordered_set <string> Nullable_Set;
Nullable_Set.insert("$");

int n = vector_for_lhs.size();

// Using taught algorithm to find nullables in the grammar :
while(true)
{

	// New vector for new nullables in each iteration : 
	vector<string> new_nullables;

	// For each production :
	for(int i = 0; i < n;i++)
	{
		int flag = 0;
		for(int j=0;j<vector_for_rhs[i].length(); j++)
		{
			string temp(1, vector_for_rhs[i][j]);

			// if RHS symbol is not nullable :
			if(Nullable_Set.find(temp) == Nullable_Set.end())
			{
				flag = 1;
			}

		}

		// Put LHS Symbol in nullable :
		if(flag == 0 && (Nullable_Set.find(vector_for_lhs[i]) == Nullable_Set.end()))
		{
			new_nullables.push_back(vector_for_lhs[i]);
			Nullable_Set.insert(vector_for_lhs[i]);
		}

	}

	// if no new nullables are added, break the loop :
	if(new_nullables.size() == 0)
	{
		break;
	}

}


/* -----------------------getting all possible combinations by placing epsilon at nullables--------------------------------*/


// double vector to store all the multiple outputs of each production : 
vector<vector<string> > vec(n);

// For each production :
for(int i=0;i<n;i++)
{
	int leng = vector_for_rhs[i].length();

	// vetcor to store all output combinations of i'th production :
	vector<string> temp_vector;
	temp_vector.push_back(vector_for_rhs[i]);

	// iterate over length & put nullables as epsilon :
	for(int j=0;j<leng; j++)
	{
		string temp_str(1, vector_for_rhs[i][j]);

		// check if its a nullable or not :
		if(Nullable_Set.find(temp_str) != Nullable_Set.end())
		{
			int tt = temp_vector.size();
			for(int k=0;k<tt;k++)
			{
				string temp1 = get_string_combination(temp_vector[k],j);
				temp_vector.push_back(temp1);
			}

		}
		
	}

	// Assign final set of outputs of a production to storage vector :
	vec[i] = get_simplified_strings(temp_vector);

}


// printing all the productions without epsilon :
for(int i=0;i<n;i++)
{
	int p = vec[i].size();
	for(int j=0;j<p;j++)
	{
		cout << vector_for_lhs[i] << " = "<< vec[i][j] <<endl;
	}

}

return 0;
}
