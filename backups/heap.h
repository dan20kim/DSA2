#include <vector> 
#include <string>
#include <iostream>
#include "hash.h"
class heap{
	public:
		heap(int capacity = 0);
		int insert(std::string &string, int key, void *pv = nullptr);//TODO
		int deleteMin(std::string *pId = nullptr, int *pKey = nullptr, void *ppData = nullptr);//TODO
		int setKey(std::string &string, int key);//TODO
		int remove(std::string &string, int *pKey = nullptr, void *ppData = nullptr);//TODO
	private:
		class node{
			public:
				std::string id {""};
				int key {0};
				void *pData {nullptr};
				node(std::string tempId, int tempKey, void *tempData = nullptr);
				node() = default;
		};
		int getPos(node *pn);//TODO
		int getKey(node *pn);
		std::string getId(node *pn);
		void percolateUp(int posCur);//TODO
		void percolateDown(int posCur);//TODO
		int currentSize;
		std::vector<node> data;
		hashTable mapping;
		void buildHeap();
};
