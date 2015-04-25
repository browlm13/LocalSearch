
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
//		convert case	
//			--------------------------

/*
*converts the case of the string argument
*mod(0 for lower case, 1 for uper case)
*/
string FormatText::lower_case( const string raw_word ) {

	//declare tmp char[] and lowerCasestring to return
	string lowerCase_word;
	char *tmp = new char[raw_word.length()];

	//for each character in string if upper case, add ascii value offset
	for(int i = 0; i< raw_word.length(); i++) {
		tmp[i] = raw_word.at(i);
		if( ((int)tmp[i] >= 65) && ((int)tmp[i] <= 90) )
			tmp[i] += 32;
	}

	//transfer and return
	lowerCase_word = tmp;
	return lowerCase_word;
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