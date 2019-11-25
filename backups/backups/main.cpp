#include "graph.h"
#include <fstream>
using namespace std;
void loadGraph(string &graphFile, Graph &graph){
	ifstream inputfile(graphFile);
	if (!inputfile){
		cerr << "Error: could not open " << graphFile << "\n";
		exit(1);
	}
	string nextLine;
	string id, id2, weightString;
	int weight;
	while(inputfile >> id >> id2 >> weight) {
	/*while(getline(inputfile, nextLine)){
		if(!nextLine.empty()){
			auto it = nextLine.begin();
			for (; (*it) != ' '; it++){
				id += *it;
			}
			it++;
			for(; (*it) != ' '; it++){
				id2 += *it;
			}
			for(; it != nextLine.end(); it++){
				weightString += *it;
			}
			weight = stoi(weightString);*/
			cout << endl;
			cout << "id1: " << id << endl;
			cout << "id2: " << id2 << endl;
			cout << "weight: " << weight << endl;
			graph.insertVertex(id, id2, weight);
	}
}


int main(){
	string graphFile, outString;
	string vertexID;
	Graph graph;
	cout << "Enter name of graph file: ";
	cin >> graphFile;
	cout <<"Enter a valid vertex id for the starting vertex: ";
	cin >> vertexID;
	cout << "hi" << endl;
	loadGraph(graphFile, graph);
	clock_t t1 = clock();
	cout << "hi" << endl;
	graph.Dijkstra(vertexID);
	clock_t t2 = clock();
	cout << "hi" << endl;
	double timeDiff = ((double) (t2-t1))/CLOCKS_PER_SEC;
	cout <<"Total time (in seconds) to apply Dijkstra's algorithm: " << timeDiff << endl;
	graph.printGraph(vertexID);
/*	cout << "Enter name of	output file: ";
	cin >> outString;*/
}
