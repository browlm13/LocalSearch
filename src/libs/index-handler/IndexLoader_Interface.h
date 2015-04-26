#ifndef INDEXLOADER_INTERFACE_H
#define INDEXLOADER_INTERFACE_H

#include <string>
#include <iostream>
#include <vector>
#include "data-packets/Data_Packets.h"

class IndexLoader_Interface {
public:
	virtual void addWord(word_packet &wp)		 										  {std::cout << "ADDWORD DEFUALT IMPLIMENTATION." << std::endl;}
	virtual void search(std::string query, std::vector<word_packet> &top_results)		  {std::cout << "SEARCH DEFUALT IMPLIMENTATION." << std::endl;}
	virtual void clear()												  				  {std::cout << "CLEAR DEFUALT IMPLIMENTATION." << std::endl;}
	virtual void save(std::string path) 										  		  {std::cout << "SAVE DEFUALT IMPLIMENTATION." << std::endl;}
};

#endif //INDEXLOADER_INTERFACE_H
