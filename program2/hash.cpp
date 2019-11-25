#include "hash.h"
using namespace std;


hashTable::hashTable(int size){
	data.resize(size);
	capacity = size;
	filled = 0;
}

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

string toLower(string key){
	auto it = key.begin();
	for (auto it = key.begin(); it != key.end(); it++){
		if (*it >= 65 && *it <= 90){
			(*it)+=32;
		}
	}
	return key;
}

int hashTable::insert(const std::string &key, void *pv){
	if (capacity == filled){
		rehash();
	}
	int index = hash(key);
	while(data[index].isOccupied){
		index = (++index)%capacity;
	}
	data[index].isOccupied = true;
	data[index].key = key;
	filled++;
}

int hashTable::findPos(const std::string &key){
	int index = hash(key);
	while(data[index].isOccupied){
		while(data[index].key != key){
			index = (++index)%capacity;
			if (!data[index].isOccupied){
				return -1;
			}
		}
		return index;
	}
	return -1;
}

bool hashTable::contains(const std::string &key){
	if (findPos(key) != -1){
		return true;
	}
	else{
		return false;
	}
}

bool hashTable::rehash(){
	int newSize = getPrime(capacity);
	string temp[capacity];
	for (int i = 0; i < capacity; i++){
		temp[i] = data[i].key;	
	}
	for (int i = 0; i < capacity; i++){
		data[i].key = "";
		data[i].isOccupied = false;
	}
	filled = 0;
	data.resize(newSize);
	capacity = newSize;
	for (int i = 0; i < sizeof(temp)/sizeof(temp[0]); i++){
		insert(temp[i]);
	}
}

unsigned int hashTable::getPrime(int size){
	int primes[10] = {24593,49157,98317,196613,393241,786433,1572869, 3145739, 6291469, 12582917};
	int i = 0;
	while (size >=  primes[i]){
		i++;
	}
	return primes[i];
}	
