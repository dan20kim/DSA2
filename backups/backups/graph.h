#include "heap.h"
#include<fstream>
#include<list>
using namespace std;
class Graph{
	public:
		class Edge;
		class Vertex{
			public:
				string id{""};
				list<Edge> adj;
				bool known;
				int dist;
				Vertex* path = nullptr;
				Vertex(string &tempId);
				Vertex() = default;
		};
		class Edge{
			public:
				Vertex* v;
				int cost;
				Edge(Vertex *vTemp, int tempCost);
				Edge() = default;
		};
		Graph();
		void insertVertex(string &id, string &id2, int weight);
		string printPath(string &id, string &startString);
		void Dijkstra(string &vertexID);
		list<Vertex> listOfVertices;
		hashTable TableOfVertices;
		int filled;
		void printGraph(string &startString);
};
