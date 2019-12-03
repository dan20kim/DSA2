#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string.h>
using namespace std;


char c1[1000];
char c2[1000];
char c3[1000];
int matrix[2000][2000];
int main(){
	string input, output, s1, s2, s3;
	cout << "Enter name of input file: ";
	cin >> input;
	cout << "Enter name of output file: ";
	cin >> output;
	ifstream inputfile(input);
	ofstream outputfile(output);
	if (!inputfile){
		cerr << "Error: could not open " << input << "\n";
		exit(1);
	}
	while(inputfile >> s1 >> s2 >> s3){	
		strcpy(c1, s1.c_str());
		strcpy(c2, s2.c_str());
		strcpy(c3, s3.c_str());
		int n = 1;
		int m = 1;
		int depth = 0;
		for (int depth = 0; depth <= s3.length(); depth++){
			for (int x = 0; x <= depth; x++){
				int y = depth - x;
				if (x == 0 && y == 0){
					matrix[y][x] = 1;
				}

				if (matrix[y][x] == 1){
				
					if (c1[x] == c3[depth]){
						matrix[y][x+1] = 1;
					}
					else{
						matrix[y][x+1] = 0;
					}

					if (c2[y] == c3[depth]){
						matrix[y+1][x] = 1;
					}
					else{
						matrix[y+1][x] = 0;
					}
				}
			}
		}
/*
			for (int k = 0; k <= s2.length(); k++){
				for (int l = 0; l <= s1.length(); l++){
					cout << matrix[k][l] << " ";
				}
				cout << "\n";
			}
*/

		depth = 0;
		int x = s1.length();
		int y = s2.length();
		for (int k = s3.length()-1; k >= 0; k--){
			if (y-1 >= 0 && matrix[y-1][x] == 1){
					y--;
			}
			else if (x >= 0 && matrix[y][x-1] == 1){
					x--;
					c3[k] -= 32;
			}
		}
		if (matrix[s2.length()][s1.length()] == 1 && s1.length() + s2.length() == s3.length()){
			//cout << "IS A MERGE" << endl;
			outputfile << c3 << endl;
		}
		else {
			outputfile << "*** NOT A MERGE ***" << endl;
		}

		memset(matrix, 0, sizeof matrix);
	}
}
