/*!
 * \file MainWordsCounter.c This is main File. Here happens all the logic.
 * */
#include <iostream>
#include <thread>
#include <process.h>
#include <windows.h>

#include "DVI_WordsCounter.h"

using namespace std;

WordsCounter loc_words("\\s");  // Create and Init the Text Parsser wiht default RegExpression

static uint8_t ret_code;
HANDLE inputKeyThread;

/*!
* \brief Help Text for user
*/
void show_help_info(void)
{
	cout << "Words counter Utility" << endl << "Version : 1.0" << endl << endl;
	cout << "This utility parse a text and count the number of occurrences for each word." << endl;
	cout << "The result will be printed in two columns, first column will contain the special word and second the occurrences of the corresponding word." << endl;

	cout << "Syntax:" << endl;
	cout << "../wordsCounterTask.exe (path_to_file) [regular_expresion]" << endl
		<< "() - Mandatory Paramters" << endl
		<< "[] - Optional Parameters" << endl;
	cout << "Input Parameters: " << endl
		<< "    path_to_file - path, name and extension of the desired file to parse" << endl;
	cout << "    regular expression - a regular expression to delimit the words, by default \"\\s\" (will delimit all white spaces)." << endl;

	cout << "Examples:" << endl;
	cout << "C:\\Users\\abc>\"wordsCounterTask.exe\" text.txt \"\\s\"" << endl;
	cout << "C:\\Users\\abc>\"wordsCounterTask.exe\" text.txt " << endl;
}

/*!
* \brief Help Function for threading the parssing
*/
void startParsing (void* param)
{
	cout << "Start parssing!" << endl;

	ret_code = loc_words.doParssing();

	_endthread();
}

/*!
* \brief Help Function for Read key form Tastatur in nonblocking mode.
*/
void readKeyboardKeyPres(void* param)
{
	cout << "Pleas type \"B\" and press \"Enter\" to break the process." << endl << endl;
	char loc_key;

	while (true)
	{
		cin >> loc_key;

		if ('B' == loc_key)
		{
			loc_words.cancelParssing();
			break;
		}
	}
	_endthread();
}

/* MAIN FUNCTION */
int main(int argc, char** argv)
{
	ret_code = dvi_wcrc_unknow_error;	/*Init return code*/

	//argc = 2;
	//string debug_str = "C:\\Users\\dvi\\Desktop\\Job Interview Task\\templay.txt";

	switch (argc)
	{
	default:
	{
		cout << "ERROR: Too many arguments" << endl << endl << endl;
		/*break; without break go ahead*/
	}
	case 1 : /*If user introduces just wordsCounterTask.exe, then*/
	{
		show_help_info();   // Show the helpful Info
		return 0;
	}

	case 2 : /*User introduces the Task.exe and first argument (file Path and name)*/
	{
		loc_words.setFilePath(argv[1]);
		//loc_words.setFilePath(debug_str);	/*set path*/
		break;
	}

	case 3 : /*User introduces the Task.exe, first argument (file Path and name) and a new Regular Expression*/
	{
		loc_words.setDelimiter(argv[2]);	/*set regular expresion*/
		loc_words.setFilePath(argv[1]);     /*set path*/
		break;
	}
	} /*end switch (argc)*/

	
	_beginthread(startParsing, 0, NULL);									/*Start parsing in concurrent mode*/
	std::this_thread::sleep_for(std::chrono::milliseconds(100));            /*Sleep for 100 millisecond to start the Parssing proccess first*/
	inputKeyThread = (HANDLE)_beginthread(&readKeyboardKeyPres, 0, NULL);   /*Start waiting a key press event from keyboard*/
	std::this_thread::sleep_for(std::chrono::milliseconds(100));            /*Sleep for 100 millisecond to start the Keyboard Event Listener first*/

	uint32_t counter = 0;
	while (dvi_wcrc_unknow_error == ret_code)	/*Wait until ret_code not change his value*/
	{
		counter++;
		cout << "\t\r" << "Parsing.... " << counter << " Seconds"  << std::flush;

		std::this_thread::sleep_for(std::chrono::seconds(1)); /*Sleep for one second to save CPU resources*/
	}	

	if ((dvi_wcrc_execution_broken != ret_code) && (NULL != inputKeyThread))
		CloseHandle(inputKeyThread);

	cout << endl << endl;

	/*Handling the Return Code*/
	switch (ret_code)
	{
	case dvi_wcrc_file_error :
		cout << "Error: to manage file" << endl;
		break;
		
	case dvi_wcrc_file_open_error :
		cout << "Error: to open file" << endl;
		break;

	case dvi_wcrc_execution_broken :
		cout << "Parsing is broken" << endl;
		break;

	case dvi_wcrc_success :
		loc_words.printList();
		break;

	default:
		break;
	} /*switch (ret_code)*/

	return 0;
}


