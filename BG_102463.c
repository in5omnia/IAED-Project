/*
* File: BG_102463.c
* Author: Beatriz Gavilan - 102463
* Description: main file with main function and the function that identifies
 * commands.
*/

#include "BG_102463.h"


/*	initializes global variables */
int g_TotalOfAirports = 0;
int g_TotalOfFlights = 0;


/*	identifies command and redirects to associated function	*/
Date readCommand(char cmd, Airport airportBank[MAX_AIRPORTS],
				 				Flight flightBank[MAX_FLIGHTS], Date today) {

	switch (cmd) {
		case 'a': commandA(airportBank);
			break;

		case 'l': commandL(airportBank);
			break;

		case 'v': commandV(airportBank, flightBank, today);
			break;

		case 'p': command_P_C('p', airportBank, flightBank);
			break;

		case 'c': command_P_C('c', airportBank, flightBank);
			break;

		case 't': today = command_T(today);
			break;

		case 'r': commandR(flightBank, today);
			break;

		/*case 'e': commandE(flightBank);
			break;*/
	}
	return today;
}


int main() {

	/*	initializes array of all airports currently in the system	*/
	Airport airportBank[MAX_AIRPORTS] = {0};
	/*	initializes array of all flights currently in the system	*/
	Flight flightBank[MAX_FLIGHTS] = {0};

	Date today = FIRST_TODAY;
	char cmd;

	/*	gets commands from standard input	*/
	while ((cmd = getchar()) != EOF && cmd != END_PROGRAM){
		today = readCommand(cmd, airportBank, flightBank, today);
	}
	return 0;
}



