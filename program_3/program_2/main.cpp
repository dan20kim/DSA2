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
	loadGraph(graphFile, graph);
	clock_t t1 = clock();
	graph.Dijkstra(vertexID);
	clock_t t2 = clock();
	double timeDiff = ((double) (t2-t1))/CLOCKS_PER_SEC;
	cout <<"Total time (in seconds) to apply Dijkstra's algorithm: " << timeDiff << endl;
	cout <<"Enter name of output file: ";
	cin >> outString;
	graph.printGraph(vertexID, outString);
}
