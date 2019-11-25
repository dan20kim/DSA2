#include "heap.h"
using namespace std;
heap::heap(int capacity):mapping(capacity*4){
	data.resize(capacity+1);
	currentSize = 0;
}

heap::node::node(std::string tempId, int tempKey, void *tempData){
	id = tempId;
	key = tempKey;
	pData = tempData;
}

int heap::insert(std::string &id, int key, void *pv){
	if (currentSize == data.size() - 1){
		return 1;
	}
	if (mapping.contains(id)){
		return 2;
	}
	data[currentSize + 1] = node(id, key);
	mapping.insert(id, &data[currentSize + 1]);
	percolateUp(currentSize+1);
	currentSize++;
	return 0;
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData){
	if (currentSize == 0){
		return 1;
	}
	*pId = data[1].id;
	*pKey = data[1].key;
	if(ppData != nullptr){
		*((void **)ppData) = data[1].pData;
	}
	data[1] = data[currentSize--];
	mapping.setPointer(data[1].id, &data[1]);
	percolateDown(1);
	mapping.remove(*pId);
	return 0;
}

int heap::setKey(std::string &id, int key){
	bool b;
	node *tempNode = (node*) mapping.getPointer(id, &b);
	if (b == false){
		return 1;
	}
	int curPos = getPos(tempNode);
	(*tempNode).key = key;
	if((curPos*2 <= currentSize && data[curPos<<1].key < data[curPos].key) || (curPos*2+1 <= currentSize) && (data[(curPos<<1)+1].key) < data[curPos].key){
		percolateDown(curPos);
	}
	if(curPos > 1 && data[curPos>>1].key > data[curPos].key){
		percolateUp(curPos);
	} 
	return 0;
}

int heap::remove(std::string &id, int *pKey, void *ppData){
	bool b;
	node* tempNode = (node*) mapping.getPointer(id, &b);	
	if (b == false){
		return 1;//node does not exist
	}
	*pKey = tempNode->key;
	int curPos = getPos(tempNode);
	if (ppData != nullptr){
		*((void **)ppData) = data[curPos].pData;
	}
	node swapNode; 
	swapNode = data[currentSize];
	data[currentSize--] = data[curPos];
	data[curPos] = swapNode;

	//mapping.setPointer(data[currentSize].id, &data[currentSize]);
	mapping.setPointer(data[curPos].id, &data[curPos]);
	
	//*pKey = getKey(&data[currentSize+1]);
	if ((curPos*2 <= currentSize && data[curPos<<1].key < data[curPos].key) || (curPos*2+1 <= currentSize) && (data[(curPos<<1)+1].key) < data[curPos].key){
		percolateDown(curPos);
	}
	if (curPos > 1 && data[curPos>>1].key > data[curPos].key){
		percolateUp(curPos);
	}
	mapping.remove(id);
	return 0;
}

void heap::percolateUp(int posCur){
	node tmp = data[posCur];
	for (; posCur > 1 && tmp.key < data[posCur/2].key; posCur /= 2){
		data[posCur] = data[posCur/2];
		mapping.setPointer(data[posCur].id, &data[posCur]);
	}
	data[posCur] = tmp;
	mapping.setPointer(data[posCur].id, &data[posCur]);
}

void heap::percolateDown(int posCur){
	int child;
	node tmp = data[posCur];
	for (; posCur *2 <= currentSize; posCur = child){
		child = posCur *2;
		if (child != currentSize && data[child+1].key < data[child].key	){
			child++;
		}
		if(data[child].key < tmp.key){
			data[posCur] = data[child];
			mapping.setPointer(data[posCur].id, &data[posCur]);
		}
		else{
			break;
		}
	}
	data[posCur] = tmp;
	mapping.setPointer(data[posCur].id, &data[posCur]);
}

int heap::getPos(node *pn){
	int pos = pn - &data[0];
	return (pos);
}

std::string heap::getId(node *pn){
	return (pn->id);
}

int heap::getKey(node *pn){
	return (pn->key);
}
