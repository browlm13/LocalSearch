#include <algorithm>

#include "FormatText.h"
#include "porter2-stemmer/porter2_stemmer.h"

//---------------------------------------------------------------------------------------------------//
/*
*		FormatText	(Deffinitions)
*/
//---------------------------------------------------------------------------------------------------//

//--------------------------
//		format word: case, stop words, stemming	
//			--------------------------

string FormatText::format_word( const string raw_word ){
	string formatted_word;

	//convert to lower case
	formatted_word = lower_case( raw_word );

/*
	if (swt.on_list(formatted_word))
		formatted_word = "0";
	else
		//continue with stemmer
*/
/*
	if ( !stop_word(word))		//will use stopWordsTable class not this method call	
		stem(word);
	else
		word = '0';
*/

	return formatted_word;

}

//--------------------------
//		format query: break apart, case, stop words, stemming
//			--------------------------
vector<string> FormatText::format_query( const string raw_query ){
	vector<string> formatted_query;

	//break apart
	formatted_query = break_apart(raw_query);

	//convert case, convert operands
	for(int i = 0; i < formatted_query.size(); i++){
		transform(formatted_query[i].begin(), formatted_query[i].end(), formatted_query[i].begin(), ::tolower);
		conv_operands(formatted_query[i]);

		//remove stop words
		//stem
		Porter2Stemmer::stem(formatted_query[i]);
	}

	return formatted_query;
}

//--------------------------
//		convert operands	
//			--------------------------
void FormatText::conv_operands(string &unkown){
	if(unkown.compare("and") == 0)
		unkown = "&&";

	if(unkown.compare("or") == 0)
		unkown = "||";
	
	if(unkown.compare("not") == 0)
		unkown = "!!";
}

//--------------------------
//		convert case	
//			--------------------------

string FormatText::lower_case( const string raw_word ) {
	string lowerCase_word = raw_word;

	transform(lowerCase_word.begin(), lowerCase_word.end(), lowerCase_word.begin(), ::tolower);

	return lowerCase_word;
}

//conv_case: 1 for upper, 0 for lower
string FormatText::conv_case( const string &raw_word, int type ){
	string formatted_word = raw_word;

	if(type == 1)
		transform(formatted_word.begin(), formatted_word.end(), formatted_word.begin(), ::toupper);
	else
		formatted_word = lower_case(formatted_word);

	return formatted_word;
}

bool stop_word( const string unkown ){}

//--------------------------
//		break apart line
//			--------------------------

/*
*breaks apart string with white space
*into seperate strings. returns vector.
*/
vector<string> FormatText::break_apart( const string raw_line ){
	string cur;
	vector<string> strings;

	for(int i=0; i<raw_line.size(); i++){
		if(raw_line.at(i) == ' ' || raw_line.at(i) == '\n'|| raw_line.at(i) == '\t' || raw_line.at(i) == '\r' || raw_line.at(i) == '.' || raw_line.at(i) == ','){
			//if(i != 0)
				//{strings.push_back(cur);}
			if(cur.size() > 0)
				{strings.push_back(cur);}

			cur.clear();
		}
		else 
			{cur += raw_line.at(i);}
	}
	if(cur.size() > 0)
			strings.push_back(cur);

	return strings;
}