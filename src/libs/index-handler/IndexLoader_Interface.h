#ifndef INDEXLOADER_INTERFACE_H
#define INDEXLOADER_INTERFACE_H

#include <string>
#include <vector>
#include "data-packets/Data_Packets.h"

class IndexLoader_Interface {
public:
		//private caller
	virtual void addWord(word_packet wp) {}
	virtual void search(std::string query, std::vector<word_packet> &top_results) {}
	virtual void clear() {}
};

#endif //INDEXLOADER_INTERFACE_H
