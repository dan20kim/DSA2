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
		//cout << "CASE 1" << endl;
	}
	else{
		listOfVertices.push_back(Vertex(id));
		TableOfVertices.insert(id, &listOfVertices.back());
		//cout << "CASE 2" << endl;
		tempVertex = &listOfVertices.back();
		filled++;
	}
	if (TableOfVertices.contains(id2)){
		tempVertex2 = (Vertex*)TableOfVertices.getPointer(id2, &b);
		//cout << "CASE 3" << endl;
	}
	else{
		listOfVertices.push_back(Vertex(id2));
		TableOfVertices.insert(id2, &listOfVertices.back());
		tempVertex2 = &listOfVertices.back();
		filled++;
		//cout << "CASE 4" << endl;
	}
	Edge tempEdge = Edge(tempVertex2, weight);
	(*tempVertex).adj.push_back(tempEdge);
	cout << "WEIGHT: " << weight << endl;
	cout << "EDGE LIST SIZE: " << (*tempVertex).adj.size() << endl;
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
	/*for (int i = 0; i < filled; i++){
		listOfVertices[i].dist = 1000001;
		listOfVertices[i].known = false;
		//cout << listOfVertices[i].id << endl;
		cerr << "inserting " << &listOfVertices[i] << endl;
		Heap.insert(listOfVertices[i].id, listOfVertices[i].dist, &listOfVertices[i]);
	}*/
	//set input as 0 distance
	//cout << "test" << endl;
	Vertex* tempVertex = (Vertex*) TableOfVertices.getPointer(vertexID, &b);
	(*tempVertex).dist = 0;
	Heap.setKey(vertexID, 0);

	for(int i = 0; i < filled; i++){
		string pId;
		int pKey;
		Vertex *tempV;
		Heap.deleteMin(&pId, &pKey, &tempV);
		
		cerr << "removing " << tempV << endl;

		bool c;
		tempV->known = true;
		cout << "hi" << endl;
		for(auto it = (*tempV).adj.begin(); it != (*tempV).adj.end(); it++){
			if (!(it->v->known)){
				cout << tempV->id << " " << it->v->id << endl;
				int cvw = (*it).cost;
				cout <<"xdxd" << endl;
				if(((*tempV).dist + cvw) < (*it).v->dist){
					(*it).v->dist = tempV->dist + cvw;
					(*it).v->path = tempV;
					Heap.setKey(it->v->id, (tempV->dist + cvw));
				}
			}
		}
	}
}

void Graph::printGraph(string &startString){
	for(auto it = listOfVertices.begin(); it != listOfVertices.end(); it++) {
		cout << printPath(it->id, startString) << endl;
	}
}

string Graph::printPath(string &id, string &startString){
	bool b;
	Vertex* v = (Vertex*)(TableOfVertices.getPointer(id, &b));
	string output = "";
	if (v->path != nullptr){
		output += printPath((*((*v).path)).id, startString) + " ";
	}
	output +=(*v).id;
	if (v->id != startString && v->path == nullptr){
		output += ": NO PATH";
	}
	return output;
}
