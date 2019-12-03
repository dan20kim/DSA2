#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string.h>
using namespace std;

char l1[1000];
char l2[1000];
char l3[2000];
char m1[1000][1000];
char m2 [1000][1000];
char m3 [2000][2000];
static int k = 0;
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
		int count = 0;
		k = 0;
		for (int i = 0; i <= count; i++){
			strcpy(l1, m1[i].c_str());
			strcpy(l2, m2[i].c_str());
			strcpy(l3, m3[i].c_str());
			int length_1 = m1[i].length();
			int length_2 = m2[i].length();
			int length_total = length_1 + length_2;
			int n = 0;
			int m = 0;
			bool flag1 = false;
			bool flag2 = false;
			bool flag3 = false;
			for (int j = 0; j < length_total; i++){
				if (n = length_1 && m = length_2){
					flag3 = true;
				}
				if (m3[i][j] == m1[i][n] && n < length_1){
					flag1 = true;
				}
				else if(m3[i][j] == m2[i][m] && m < length_2){
					flag2 = true;
				}
				if (flag1 && flag2){
					k++;
					count++;
					m1[i] = m1[i].substr(n+1);
					m2[i] = m2[i].substr(m);
					m3[i] = m3[i].substr(n+m+1);
			
					m1[i+1] = m1[i].substr(n);
					m2[i+1] = m2[i].substr(m+1);
					m3[i+1] = m3[i].substr(n+m+1);
					count++;  
					break;
				}
				else if (flag1){
					n++;
					k++;
					l3[k] += 32;
				}
				else if (flag2){
					m++;
					k++;
				}
				/*else{
					cout << "*** NOT A MERGE ***" << endl;	
					flag = false;
					break;
				}*/
			}
			if (!flag){
			}
			if (flag){
				cout << l3 << endl;
			}
		}
		if (!flag){
			outputfile << "*** NOT A MERGE ***" << endl;
		}
		if (flag{
			cout < l3 << endl;
		}
	}	
}
