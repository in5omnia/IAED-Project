/*
* File: BG_102463.c
* Author: Beatriz Gavilan - 102463
* Description:	main file with main functions and other supportive functions
 * 				to the airport management support system
*/

#include "BG_102463.h"


/*	initializes global variables */
int g_TotalOfAirports = 0;
int g_TotalOfFlights = 0;


/*	identifies command from input and redirects to associated function
 *
 * cmd: command found in input
 * airportBank: array of all airports currently in the system
 * flightBank: array of all flights currently in the system
 * today: today's date
 */

Date readCommand(char cmd, Airport airportBank[MAX_AIRPORTS],
				 				Flight flightBank[MAX_FLIGHTS], Date today) {

	switch (cmd) {
		case 'a':
			commandA(airportBank);
			break;

		case 'l':
			commandL(airportBank);
			break;

		case 'v':
			commandV(airportBank, flightBank, today);
			break;

		case 'p':
			command_P_C('p', airportBank, flightBank);
			break;

		case 'c':
			command_P_C('c', airportBank, flightBank);
			break;

		case 't':
			today = command_T(today);
			break;
	}
	return today;
}


int main() {

	Airport airportBank[MAX_AIRPORTS] = {0};
	Flight flightBank[MAX_FLIGHTS] = {0};

	Date today = FIRST_TODAY;
	char cmd;

	while ((cmd = getchar()) != EOF && cmd != END_PROGRAM){
		today = readCommand(cmd, airportBank, flightBank, today);
	}
	return 0;
}



