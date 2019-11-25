#include "graph.h"
using namespace std;

Graph::Vertex::Vertex(string &tempId){
	id = tempId;
	known = false;
	dist = 0;
	Vertex* path = nullptr;
	adj.resize(100000);
}

Graph::Edge::Edge(Vertex *vTemp, int tempCost){
	v = vTemp;
	cost = tempCost;
}

Graph::Graph():TableOfVertices(10000){
	listOfVertices.resize(10000);
	filled = 0;	
}

void Graph::insertVertex(string &id, string &id2, int weight){
	cout << "jakdsjf;akdlj " << endl;
/*
	if(TableOfVertices.contains(id)){
		if (TableOfVertices.contains(id2)){
			//Edge(*((Vertex*)(TableOfVertices.getPointer(id2))), weight);


			Vertex *tempVertex = ((Vertex*)TableOfVertices.getPointer(id, &a));
			cout << "hi" << endl;
			Vertex *tempVertex2 = ((Vertex*)TableOfVertices.getPointer(id2, &b));
			cout << "hi" << endl;
			Edge tempEdge = Edge(tempVertex2, weight);
			cout << "hi" << endl;
			(*tempVertex).adj.push_back(tempEdge);

			cout << "hm" << endl;
			Edge tempEdge = Edge(*((Vertex*)(TableOfVertices.getPointer(id2))),weight);
			(*((Vertex*)TableOfVertices.getPointer(id, &b))).adj.push_back(tempEdge);
			cout << "hm" << endl;



			//((Vertex*)(TableOfVertices.getPointer(id)))->adj.push_back(tempEdge);
		}
		else{//DONE
			Vertex tempVertex2 = Vertex(id2);
			listOfVertices.push_back(tempVertex2);
			TableOfVertices.insert(id2, &tempVertex2);
			Vertex *tempVertex = ((Vertex*)TableOfVertices.getPointer(id, &b));
			cout << "hm" << endl;
			Edge tempEdge = Edge(&tempVertex2, weight);
			(*tempVertex).adj.push_back(tempEdge);
			cout << "hm" << endl;
		}
		//TableOfVeddrtices.insert(id);
		//Vertex tempVertex = Vertex(id);
	}
	else{//
		if (TableOfVertices.contains(id2)){
			Vertex tempVertex = Vertex(id);
			TableOfVertices.insert(id, &tempVertex);
			Edge tempEdge = Edge(((Vertex*)(TableOfVertices.getPointer(id2, &b))), weight);
			tempVertex.adj.push_back(tempEdge);
		}
		else{//DONE
			cout <<" here" << endl;
			//Vertex 1
			listOfVertices.push_back(Vertex(id));
			TableOfVertices.insert(id, &listOfVertices.back());
			//Vertex 2
			listOfVertices.push_back(Vertex(id2));
			TableOfVertices.insert(id2, &listOfVertices.back());
			Edge tempEdge = Edge(&listOfVertices.back(), weight);
			((Vertex*)TableOfVertices.getPointer(id))->adj.push_back(tempEdge);
		}
	}
*/
	int x = 0;
	int y = 0;
	bool a;
	bool b;
	Vertex *tempVertex;
	Vertex *tempVertex2;
		listOfVertices[filled] = Vertex(id);
		TableOfVertices.insert(id, &listOfVertices[filled]);
		tempVertex = &listOfVertices[filled];
		filled++;
		listOfVertices[filled] = Vertex(id2);
		TableOfVertices.insert(id2, &listOfVertices[filled]);
		tempVertex = &listOfVertices[filled];
		filled++;
	}
	Edge tempEdge = Edge(tempVertex2, weight);
	return;
}

void Graph::Dijkstra(string &vertexID){	
	bool b;
	heap Heap(listOfVertices.size());
	for (auto it = (listOfVertices).begin(); it != (listOfVertices).end(); it++){
		(*it).dist = 1000000;
		(*it).known = false;
		Heap.insert((*it).id, (*it).dist, &(*it));
	}
	cout << "test" << endl;
	Vertex* tempVertex = (Vertex*) TableOfVertices.getPointer(vertexID, &b);
	if (b == false){
		cout << "really" << endl;
		//should not happen as vertexID is guaranteed to be in list
		return;
	}
	(*tempVertex).dist = 0;
	cout << "test" << endl;
	//cout << tempVertex ->dist << endl;
	cout << "test" << endl;
	Heap.setKey(vertexID, 0);
	cout << "test" << endl;
	cout << listOfVertices.size() << endl;
	for(int i = 0; i < listOfVertices.size(); i++){
		cout << "xd" << endl;
		string *pId;
		int *pKey;
		Heap.deleteMin(pId, pKey);
		Vertex v = *pId;
		int tempDist = *pKey;
		for(auto it = v.adj.begin(); it != v.adj.end(); it++){
			if (!(*it).v->known){
				int cvw = (*it).cost;
				if(v.dist + cvw < (*it).v->dist){
					cout << "something happened" << endl;
					(*it).v->dist = v.dist + cvw;
					(*it).v->path = &v;
				}
			}
		}
	}
}

void Graph::printGraph(){
	for (int i = 0; i < filled; i++){
		cout << printPath(listOfVertices[i].id) << endl;
	}
}

string Graph::printPath(string &id){
	Vertex *v = (Vertex*)(TableOfVertices.getPointer(id));
	string output;
	if ((*v).path != nullptr){
		output += printPath((*(*v).path).id);
	}
	output +=(*v).id;
	cout << output << endl;
	return output;
}
