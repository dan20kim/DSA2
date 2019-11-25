#include "graph.h"
using namespace std;

Graph::Vertex::Vertex(string &tempId){
	id = tempId;
	known = false;
	dist = 0;
	Vertex* path = nullptr;
}

Graph::Edge::Edge(Vertex *vTemp, int tempCost){
	v = vTemp;
	cost = tempCost;
}

Graph::Graph():TableOfVertices(100000){
	filled = 0;	
}

void Graph::insertVertex(string &id, string &id2, int weight){
	bool a;
	bool b;
	Vertex *tempVertex;
	Vertex *tempVertex2;
	if (TableOfVertices.contains(id)){
		tempVertex = (Vertex*)TableOfVertices.getPointer(id, &a);
	}
	else{
		listOfVertices.push_back(Vertex(id));
		TableOfVertices.insert(id, &listOfVertices.back());
		tempVertex = &listOfVertices.back();
		filled++;
	}
	if (TableOfVertices.contains(id2)){
		tempVertex2 = (Vertex*)TableOfVertices.getPointer(id2, &b);
	}
	else{
		listOfVertices.push_back(Vertex(id2));
		TableOfVertices.insert(id2, &listOfVertices.back());
		tempVertex2 = &listOfVertices.back();
		filled++;
	}
	Edge tempEdge = Edge(tempVertex2, weight);
	(*tempVertex).adj.push_back(tempEdge);
	return;
}

void Graph::Dijkstra(string &vertexID){	
	bool b;
	heap Heap(listOfVertices.size());
	for(Vertex &v : listOfVertices) {
		v.dist = 1000001;
		v.known = false;
		Heap.insert(v.id, v.dist, &v);
	}
	Vertex* tempVertex = (Vertex*) TableOfVertices.getPointer(vertexID, &b);
	(*tempVertex).dist = 0;
	Heap.setKey(vertexID, 0);

	for(int i = 0; i < filled; i++){
		string pId;
		int pKey;
		Vertex *tempV;
		Heap.deleteMin(&pId, &pKey, &tempV);

		bool c;
		tempV->known = true;
		for(auto it = (*tempV).adj.begin(); it != (*tempV).adj.end(); it++){
			if (!(it->v->known)){
				int cvw = (*it).cost;
				if(((*tempV).dist + cvw) < (*it).v->dist){
					(*it).v->dist = tempV->dist + cvw;
					(*it).v->path = tempV;
					Heap.setKey(it->v->id, (tempV->dist + cvw));
				}
			}
		}
	}
}

void Graph::printGraph(string &startString, string &outString){
	ofstream output(outString);
	for(auto it = listOfVertices.begin(); it != listOfVertices.end(); it++) {
		output << it->id << ": ";
		output << printPath(it->id, startString, 0) << endl;
	}
}

string Graph::printPath(string &id, string &startString, int depth){
	bool b;
	Vertex* v = (Vertex*)(TableOfVertices.getPointer(id, &b));
	string output = "";
	if (v->id != startString && v->path == nullptr){
		return ("NO PATH");
	}
	if (depth == 0){
		output += to_string(v->dist);
	}
	if (v->path != nullptr){
		output += printPath((*((*v).path)).id, startString, depth+1) + ", ";
	}
	else {
		output += " [";
	}
	output +=(*v).id;
	if (depth == 0){
		output += "]";
	}
	return output;
}
