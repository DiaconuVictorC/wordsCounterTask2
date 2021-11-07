/*!
 * \file DVI_WordsCounter.c with all member functions definitions including constructor.
 * */

#include "DVI_WordsCounter.h"
#include <string>

/*******************************************
 *CONSTURCTORS AND DESTRUCTOR  
 *******************************************/
WordsCounter::WordsCounter(string reg_str)
{
	this->reg_str  = reg_str;
	this->filePath = "";

	wrdCnt_is_break = false;
}

WordsCounter::WordsCounter(string reg_str, string fPath)
{
	this->reg_str  = reg_str;
	this->filePath = fPath;

	wrdCnt_is_break = false;
}

WordsCounter::~WordsCounter(void)
{
	if (!wordsCnt.empty())
		wordsCnt.clear();
	
	filePath.clear();
	filePath.~basic_string();
	
	reg_str.clear();
	reg_str.~basic_string();
}

/*******************************************
 *SETTER FUNCTIONS
 *******************************************/
void WordsCounter::setDelimiter(string reg_str)
{
	this->reg_str = reg_str;
}

void WordsCounter::setFilePath(string fPath)
{
	this->filePath = fPath;
}

/*******************************************
 *BEHAVIOR FUNCTION OF THE CLASS, for function description look in header file.
 *******************************************/
/*Principal Function that do the parsing logic*/
uint8_t WordsCounter::doParssing(void)
{
	int help_int;                                  /*Use help variable for count the occurrence of words */
	ifstream fileBuff;                             /*Init the file buffer*/

	wrdCnt_is_break = false;                       /*Reset the break flag*/

	regex regExpres(this->reg_str);                /*Create the Regular Expression object*/

	fileBuff.open(this->filePath, ios::in);        /*Open the file with provider paht in Read Mode*/

	if (fileBuff.bad())                            /*Check the filebuffer*/
		return dvi_wcrc_file_error;		           /*Error, the file Buffer is corupted*/

	if (!fileBuff.is_open())                       /*Check if the file is properly open*/
		return dvi_wcrc_file_open_error;           /*Error, not possible to open the file*/

	for (string line; getline(fileBuff, line); )   /*Parse the file line by line*/
	{
		if (true == wrdCnt_is_break)               /* If user request break of execution*/
		{
			return dvi_wcrc_execution_broken;      /* then exit and inform the caller about execution broken*/
		}

		const vector<string> wordsVector {		   /* Now pleat the Line with text in words conform provided regular expression*/
			sregex_token_iterator(line.begin(), line.end(), regExpres, -1),
			sregex_token_iterator() };

		for (const auto& word : wordsVector)       /* Parse the words List*/
		{
			if (word == "")                        /* if it is a empty string then read the next word*/
				continue;
			
			/* Look in Map for desired word. If such a word does not exist, 
			 * then iterator will be at the end of map*/
			auto map_iter = wordsCnt.find(word);   

			if (map_iter == wordsCnt.end())        /*If iterator is at the end of Map, that mean that it is a new word*/
				help_int = 1;                      /*set the help variable to first occurence */
			else                                   /*in another case */
				help_int = map_iter->second + 1;   /*read the ocurence of word incremet it and save in help variable*/
			wordsCnt.insert_or_assign(word, help_int); /*update the pair or if it is a new word create a pair*/
		}
	}

	fileBuff.close();
	return dvi_wcrc_success;                       /*After parsing inform the caller about successful execution*/
}

/*Function that cancel the parsing of doParssing Function.*/
void WordsCounter::cancelParssing(void)
{
	wrdCnt_is_break = true;
}

/*Function that print the result on console.*/
void WordsCounter::printList(void)
{
	/*do sort the result*/
	vector <pair<string, int>> result;								/*help verctor to sort*/
	for (auto itr = wordsCnt.begin(); itr != wordsCnt.end(); ++itr)	/*Copy the Map into vector*/
		result.push_back(*itr);

	sort(															/*Sort the Vector*/
		result.begin(),												/*Set first element*/
		result.end(),                                               /*Set last element*/
		[=](pair<string, int>& p1, pair<string, int>& p2)		    /*Use lambda expression to override the compare function*/
		{
			return p1.second < p2.second;                           /*Compare Second Values of Pairs*/
		}
	);

	cout << std::setw(20) << "Word" << "  Occurrence" << endl;      /*Visualize the column*/

	for (auto& loc : result)
	{
		cout << std::setw(20) << loc.first << "  " << loc.second << endl;
	}
}