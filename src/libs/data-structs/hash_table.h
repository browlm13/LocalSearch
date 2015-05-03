#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <string>
#include <vector>

template <class T>
class hash_table{

	unsigned size;	//some prime number

	//element
	struct element{
		element(std::string key, T value) : key(key), value(value){}
		std::string key;
		T value;
	};

	std::vector<element> *table;

	unsigned index(std::string key);		//returns index

public:
	void 	clear			();
	void 	add				(std::string key, T value);	
	T* 		get				(std::string key);

	hash_table() {
		size = 2027;
		table = new std::vector<element> [size];
	}
	~hash_table(){
		delete [] table;
	}
};

template<class T>
unsigned hash_table<T>::index(std::string key){
	//primes
	const unsigned A = 54059;
	const unsigned B = 76963;
	unsigned d = 31;

	for(int i=0; i<key.size(); i++)
		d = (d * A) ^ (key[i] * B);

	return d % size;
}

template<class T>
void hash_table<T>::add(std::string key, T value){
	element e(key, value);	
	table[index(key)].push_back(e);	
}

template<class T>
T* hash_table<T>::get(std::string key){
	T* v = 0;
	unsigned loc = index(key);

	if(table[loc].size() > 0){
		for (int i=0; i<table[loc].size(); i++){
			if(table[loc][i].key.compare(key) == 0)
				v = &table[loc][i].value;
		}
	}

	return v;
}	

template<class T>
void hash_table<T>::clear(){
	delete [] table;
}

#endif //HASH_TABLE_H