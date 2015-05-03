#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T>
class hash{

	unsigned size;	//some prime number

	//element
	struct element{
		element(std::string key, T value) : key(key), value(value){}
		std::string key;
		T value;
	};

	//std::vector< std::vector<element> > table(10, std::vector<element>(10));//, std::vector<element>(1));
	vector<element> *table;

	//array[size] of vectors(deletion not neccisarry),

	//for stop words hash
		//each element in vector contains a string

	//for index loader hash
		//each element in the vector contains a (word) and its avl tree of doc_id_packets
		//an (index loader tree child) as the value

	unsigned index(std::string key);		//returns index

public:
	void 	clear			();
	void 	add				(std::string key, T value);		//hashfunction %size for index in array of vecotrs. push_back on vector
	T* 		get				(std::string key);				///what happens if not found? return null

/*
	//for both
	bool	check			(std::string key);
	//for index loader hash
	bool	get_results	(std::string key, std::vector<word_packet> &results)	//appends top results to vector
*/
	hash() {
		size = 2027;
		table = new vector<element> [size];
	}
	~hash(){
		delete [] table;
	}
};

template<class T>
unsigned hash<T>::index(std::string key){
	//primes
	const unsigned A = 54059;
	const unsigned B = 76963;
	unsigned d = 31;

	for(int i=0; i<key.size(); i++)
		d = (d * A) ^ (key[i] * B);

	return d % size;
}

template<class T>
void hash<T>::add(std::string key, T value){
	element e(key, value);				//value must be an avl child tree
	table[index(key)].push_back(e);		//for index loader hash table[index(key)].insert
}

//index loader hash add
/*
template<class T>
void hash<T>::add(std::string key, T doc_id_packet, ){
	unsigned loc = index(key);

	if(get(key))
	{
		for(int i=0; i<table[loc].size()); i++){
			if(table[loc][i].key.compare(key) == 0)
				table[loc][i].value.insert(id);
		}
	}
	else 
	{
		index_builder_child_tree ibct;
		ibct.insert(id);
		element e(key, ibct);			//value = index_builder_child_tree
		table[loc].push_back(e);
	}
}
*/
template<class T>
T* hash<T>::get(std::string key){
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
void hash<T>::clear(){
	delete [] table;
}
#endif //HASH_H


/*
#define A 54059 // a prime
#define B 76963 // another prime
#define C 86969 // yet another prime
unsigned hash_str(const char* s)
{
   unsigned h = 31 // also prime;
   while (*s) {
     h = (h * A) ^ (s[0] * B);
     s++;
   }
   return h; // or return h % C;
}
*/