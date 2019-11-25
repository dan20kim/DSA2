#include "hash.h"
#include <ctype.h>
using namespace std;

// hashTable Constructor
hashTable::hashTable(int size){
	data.resize(size);
	capacity = size;
	filled = 0;
}

// hash Function - taken from text book
int hashTable::hash(const std::string &key){
	int hashVal = 0;
	for (int i = 0; i < key.length(); i++){
		hashVal = 37*hashVal + key[i];
	}
	hashVal %= capacity;
	if (hashVal < 0){
		hashVal += capacity;
	}
	return hashVal;
}

// Insert Member Function - Calls rehash when 60% of the table is filled
int hashTable::insert(const std::string &key, void *pv){
	if (filled >= (.6*capacity)){
		rehash();
	}
	int index = hash(key);
	while(data[index].isOccupied){
		index = (++index)%capacity;
	}
	data[index].isOccupied = true;
	data[index].key = key;
	data[index].pv = pv;
	data[index].isDeleted = false;
	filled++;	
}

// Find Position Member Function
int hashTable::findPos(const std::string &key){
	int index = hash(key);
	if(data[index].isOccupied){
		while(data[index].key != key || data[index].isDeleted){
			index = (++index)%capacity;
			if (!data[index].isOccupied){
				return -1;
			}
		}	
		return index;
	}
	else{
		return -1;
	}
}

// Contains Member Function
bool hashTable::contains(const std::string &key){
	if (findPos(key) != -1){
		return true;
	}
	else{
		return false;
	}
}

// Rehash Member Function
bool hashTable::rehash(){
	int newSize = getPrime(capacity);
	if (newSize == -1){
		return false;
	}
	capacity = newSize;
	vector<hashItem> temp(newSize);
	for (hashItem x: data){
		if (x.isOccupied && !x.isDeleted){
			int index = hash(x.key);
			while(temp[index].isOccupied){
					index = (++index)%capacity;
			}
			temp[index] = x;
		}
	}
	data.resize(newSize);
	data = move(temp);
	return true;
}

unsigned int hashTable::getPrime(int size){
	int primes[13] = {24593,49157,98317,196613,393241,786433,1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319};
	int i = 0;
	if (size >=  primes[i] && i < 12){
		i++;
		return primes[i];
	}
	if (i == 12){
		return -1;
	}
}

void* hashTable::getPointer(const std::string &key, bool *b){
	int index = findPos(key);
	cout << "index: " << index << endl;
	if (index == -1){
		*b = false;
		return nullptr;
	}
	//cout << "FOUNNDDDD" << endl;
	*b = true;
	return (data[index].pv);	
}

int hashTable::setPointer(const std::string &key, void *pv){
	int index = findPos(key);
	if (index == -1){
		return 1;
	}
	data[index].pv = pv;
	return 0;
}

bool hashTable::remove(const std::string &key){
	int index = findPos(key);
	if (index == -1){
		return false;
	}
	else{
		data[index].isDeleted = true;
		return true;
	}
}
