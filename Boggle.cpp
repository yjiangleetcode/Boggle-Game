// Boggle Solver.cpp : Defines the entry point for the console application.
//
/*
A program to output the number of valid word in a dictionary that can build by a set of given letters
1. preprocess the dictionary (case sensitive and length of words)
2. Traversal the dictionary and output the number of valid word

Complexity: O(length of the dictionary)
*/
///#include "stdafx.h" for Visual Studio
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <algorithm>

using namespace std;

///Function to check if a word from the dictionary can be built by the input strings
bool checkWord(string input, string &dict){
	vector<bool> used(input.length(),false); ///vector of bool as the flag of whether the letter has been used
	bool found = true;
	int i = 0;
	while (found && i<dict.length()){ ///iterate each string in the word from dictionary
		found = false;
		for (int j=0;j<input.length();j++){
			if (used[j]==false && dict[i]==input[j]){ ///if the letter is found and can be used, break the inner loop 
				used[j]=true;						///and go to the next string in the word
				found = true;
				break;
			}
		}
		++i;
	}
	return found; ///return whether a word from dictionary can be built by the given letters
}
///Function to iterate each word in the dictionary and find the number of valid word that can be built by the input letters
int countWord(string input, unordered_set<string> &dictionary){
	int count = 0;
	for (auto it = dictionary.begin(); it != dictionary.end(); ++it ){
		string str = *it;
		if (checkWord(input,str)) count++;
	}
	return count;
}


int main(int argc, char* argv[])
{
	unordered_set<string> dictionary; ///Initialize the dictionary as unordered set
	string str;///string to hold lines from the dictionary file
	ifstream dict(argv[1]);
	/*Preprocess the dictionary file:
		read each line and store the words into the set
		transform all words to lowercase since the matches are not case sensitive
		only store the words with length larger than or equal to 3
	*/
	if (dict.is_open()){
		while (dict){
			getline(dict,str);
			transform(str.begin(), str.end(), str.begin(), ::tolower);
			if (str.length()>2) dictionary.insert(str);
		}
		dict.close();
	}
	else{
		cout<<"Can not open the dictionary file"<< endl;
	}
	cout << "Dictionary loaded"<<endl;
	/*Processing input data
		read each line in input file and find the number of valid words
	*/
	string inputstr;
	ifstream input(argv[2]); ///parsing the first argument as input path
	ofstream output("output.txt"); ///parsing the second one as output path
	if (input.is_open()){
		while (input){
			getline(input, inputstr);
			output<<inputstr<<" "<<countWord(inputstr,dictionary)<<endl;
		}
	}
	else cout<<"Can not open the input file"<<endl;
	input.close();
	output.close();
	return 0;
}

