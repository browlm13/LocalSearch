#ifndef INDEXLOADER_INTERFACE_H
#define INDEXLOADER_INTERFACE_H

#include <string>
#include <iostream>
#include <vector>
#include "data-packets/Data_Packets.h"

class IndexLoader_Interface {
protected:
		int result_amount;
public:
	virtual void addWord(word_packet &wp)		 										  {std::cout << "ADDWORD DEFUALT IMPLIMENTATION." << std::endl;}
	virtual void search(std::string query, std::vector<word_packet> &top_results)		  {std::cout << "SEARCH DEFUALT IMPLIMENTATION." << std::endl;}
	virtual void clear()												  				  {std::cout << "CLEAR DEFUALT IMPLIMENTATION." << std::endl;}
	virtual void save(std::string path) 										  		  {std::cout << "SAVE DEFUALT IMPLIMENTATION." << std::endl;}

	void set_result_amount(int result_amount_arg)										{result_amount = result_amount_arg;}
};

#endif //INDEXLOADER_INTERFACE_H
