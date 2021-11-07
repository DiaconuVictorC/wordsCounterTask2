
/*!
 * \file DVI_WordsCounter.h
 * \brief WordsCounter Class that give posibility to parse a textual file \n
 *        and count the number of occurrences for each word.
 * \par Platform :
 *      Windows 10 XP
 * \par Compiler :
 *      Microsoft (R) C/C++- Version 19.29.30136 für x64
 * \par IDE: VisualStudio.16.Release/16.11.5+31729.503
 *		
 * \author  Victor Diaconu
 * \date    06.11.2021
 * \version 1.0
 * 
 * Change Log:
 * - <B>1.0</B> 06.11.2021 DVI                       \n
 * - First Version of Clase
 */

#ifndef _DVI_WORDS_COUNTER_H_
#define _DVI_WORDS_COUNTER_H_

#include <iomanip>
#include <iostream>
#include <fstream>
#include <map>
#include <regex>

using namespace std;

#define DVI_WORDS_COUNTER_MAJOR_VERSION 1
#define DVI_WORDS_COUNTER_MINOR_VERSION 0

/*! @brief Words Counter return codes */
enum _dvi_words_counter_ret_code
{
	dvi_wcrc_success          = 0,		/*!< Function successful executed. */
	dvi_wcrc_file_error       = 1,		/*!< General File error happen. */
	dvi_wcrc_file_open_error  = 2,		/*!< File open not succed. */
	dvi_wcrc_execution_broken = 3,		/*!< Parsing is canceled. */

	dvi_wcrc_unknow_error    = 0xFF,	/*!< Unknown error. */
};

/*!
 * /brief The Class that implement functionality of Words Counter.
 */
class WordsCounter
{
	private:
		/*!< String that hold the Textula File Path, name and extension */
		string filePath;								
		/*!< String that hold the Regular Expression */
		string reg_str;                                 
		bool wrdCnt_is_break;

	protected:
		/*!< Map Container, that hold the Key/Value pair. 
		 * Key is Word, and value is the word's occurrence in the text. 
		 * It is protected to allow further to extend print capability. */
		map<string, int> wordsCnt;                     

	public:
		/*!
		 * brief\ Constructor of the class
		 *
		 *  param[in] reg_str   Regular Expression to split the text
		 */
		WordsCounter(string reg_str);

		/*!
		 * brief\ Constructor of the class
		 *
		 *  param[in] reg_str   Regular Expression to split the text
		 *  param[in] fPath     Path to a File for parsing.
		 */
		WordsCounter(string reg_str, string fPath);

		/*!
		 * brief\ Destructor of the class
		 */
		~WordsCounter();

		/*!
		 * brief\ Setter Function of the reg_str characteristic
		 */
		void setDelimiter(string reg_str);

		/*!
		 * brief\ Setter Function of the fPath characteristic
		 */
		void setFilePath(string fPath);

		/*!
		 * brief\ Function that perform the file parssing
		 *
		 * This function open the File. Pars the File line by line, 
		 * split every line in Words conform Regular Expression 
		 * and save the result in the wordsCnt characteristic. 
		 * If some word already exist, then it will increment the pair value.
		 * 
		 * \return return a status of function execution. For more details, see the _dvi_words_counter_ret_code Enumeration.
		 */
		uint8_t doParssing(void);

		/*!
		 * brief\ Break the file parsing Function
		 */
		void cancelParssing(void);
		
		/*!
		 * brief\ Print the result of parsing process to console
		 */
		void printList(void);
};


#endif /*_DVI_WORDS_COUNTER_H_*/