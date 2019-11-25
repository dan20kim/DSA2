#include "hash.h"
#include <string.h>
#include <fstream>
#include <cstring>
using namespace std;
void loadDictionary(string &input, hashTable &table){
	ifstream inputfile (input);
	if (!inputfile){
		cerr << "Error: could not open " << input << "\n";
		exit(1);
	}
	string nextLine;
	while(getline(inputfile, nextLine)){
		if(!nextLine.empty()){
			table.insert(toLower(nextLine));
		}
	}
}

bool isValid(char c){
	if ((c >= 97 && c <= 122) || c == 39 || (c >= 48 && c <= 57) || c == 45 || (c >= 65 && c <= 90)){
		return true;
	}
	else{
		return false;
	}
}

void spellCheck(string &input, hashTable &table){
	string output;
	ifstream inputfile (input);
	if (!inputfile){
		cerr << "Error: could not open " << input << "\n";
		exit(1);
	}
	cout << "Enter name to output file: ";
	cin >> output;
	ofstream outputfile (output);
	string nextLine;
	string word = "";
	int lineNumber = 1;
	bool tooLong;
	while(getline(inputfile, nextLine)){
		if(!nextLine.empty()){
			auto it = nextLine.begin();
			while (!(*it == '\0')){
				int i;
				for(i = 20; i > 0; i--){
					if (isValid(*it)){
						word += *(it++);		
					}
					else{
						break;
					}
				}
				if (i == 0 && isValid(*(it))){
					outputfile << "Long word at line " << lineNumber << ", starts: " << toLower(word) << endl;
				}
				else{
					if (i < 20 && i >= 0){
						if (!table.contains(toLower(word))){
							outputfile << "Unknown word at line " << lineNumber << ": " << toLower(word) << endl;
						}
					}
				}
				while (isValid(*it)){
					it++;
				}
				if (*it != '\0'){
					it++;
				}
				word = "";
			}
		}
		lineNumber++;
	}
}


int main(){
	string input;
	cout << "Enter name of Dictionary: ";
	cin >> input;
	clock_t t1 = clock();
	hashTable table = hashTable(24593);
	//Insert into the hash Table;
	loadDictionary(input, table);
	clock_t t2 = clock();
	double timeDiff = ((double) (t2 - t1))/ CLOCKS_PER_SEC;
	cout << "Total time (in seconds) to load dictionary: " << timeDiff << endl;
	cout << "Enter name of input file: ";
	cin >> input;
	clock_t t3 = clock();
	spellCheck(input, table);
	clock_t t4 = clock();
	double timeDiff2 = ((double) (t2-t1))/ CLOCKS_PER_SEC;
	cout << "Total time (in seconds) to check document: " << timeDiff2 << endl;
	
	return 1;
}
