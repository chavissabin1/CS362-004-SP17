/*
 * sabinc
 * CS 362 SW Eng II
 * Spring 2017
 *
 * Week 4 Quiz
 * unittest4.c
 */
 /*
 For random tester to work properly two functions were modified:
 
 1.	inputChar()
	
	inputChar() works by selecting an ascii character using the rand() function.
	Random function is set to return a number between 32 and 126 which should limit
	random function to returning characters within the range boundary. The boundary
	was selected because all characters needed to advance the state lie between 32 
	and 126. This should shorten the time it takes for the test to fail.
 
 2.	inputString()
 
	inputString() works in a similar way as inputChar(). An array of characters of 
	length 6 is created. A for loop is set to populate the char array between index
	0 and 5. Index 6 is puposely left out so it can remain '\0'. Within for loop the
	characters are populated by random within a given range, similarly to the rand
	function in inputChar(). The range was modified to only look at numbers that
	represent ascii characters 'e' - 't'. This will shorten test significantly since
	all letters needed for exit message are within range. There could be a shorter way 
	to force an error by fixing some characters and only using rand on a few or just give 
	the expected return statement.
	
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 */