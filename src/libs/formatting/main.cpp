#include <iostream>
#include <string>
#include <vector>

#include "StopWords_Hash.h"

using namespace std;

int main(){

	StopWords_Hash swh;

	string a("lj");
	string b("trex");
	string c("is");
	string d("around");
	string e("batman");
	string f("and");
	string g("kiss");
	string h("are");

	vector<string> words;
	words.push_back(a);
	words.push_back(b);
	words.push_back(c);
	words.push_back(d);
	words.push_back(e);
	words.push_back(f);
	words.push_back(g);
	words.push_back(h);

	for(int i=0; i<words.size(); i++){
		if(swh.is_stop_word(words[i]))
			cout << words[i] << endl;
	}

	return 0;
}