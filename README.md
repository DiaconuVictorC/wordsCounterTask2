Words counter Utility

Version : 1.0

A small command line utility. 
The program read a specified text file, identify the individual
words and count the number of occurrences for each word.
The result is given in the form of a simple table with two columns.
The first column contains the words found, the second column the number of occurrence.
The result will be sorted according to the number of occurrences.

Syntax:
C.\Users\yourUserName>"../wordsCounterTask.exe (path_to_file) [regular_expresion]" << endl
() - Mandatory Paramters
[] - Optional Parameters

Input Parameters:
    path_to_file - path, name and extension of the desired file to parse
    regular expression - a regular expression to delimit the words, by default "\s" (will delimit all white spaces).

Examples:
    C:\Users\abc>"wordsCounterTask.exe" text.txt "\s" 
	  C:\Users\abc>"wordsCounterTask.exe" text.txt
