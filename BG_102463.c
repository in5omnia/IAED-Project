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
/*	initializes array of all airports currently in the system	*/
Airport *airportBank = NULL;
/*	initializes doubly linked list of flights currently in the system	*/
Flight* flightBank_Tail = NULL;
Flight* flightBank_Head = NULL;
/* initializes linked list of reservations */
ResNode *g_allRes_Head = NULL;


/*	identifies command and redirects to associated function	*/
Date readCommand(char cmd, Date today) {

	switch (cmd) {
		case 'a': commandA();
			break;

		case 'l': commandL();
			break;

		case 'v': commandV(today);
			break;

		case 'p': command_P_C('p');
			break;

		case 'c': command_P_C('c');
			break;

		case 't': today = command_T(today);
			break;

		case 'r': commandR(today);
			break;

		case 'e': commandE();
			break;
	}
	return today;
}


void noMemory(){
	printf(NO_MEMORY);
	freeAll();
	exit(1);
}


/* frees memory associated with each flight and its reservations */
void freeFlight(){
	Flight *temp = flightBank_Head;
	int i;
	if (temp->reservationList != NULL){
		for (i = 0; i < temp->numReservations; i++){
			free(temp->reservationList[i]->reservationCode);
			free(temp->reservationList[i]->resNode_ptr->reservation);
		}
		free(temp->reservationList);
	}
	flightBank_Head = flightBank_Head->next;
	free(temp);
	temp=NULL;
	flightBank_Head->prev = NULL;
}


/* frees all memory allocated manually */
void freeAll(){
	while (flightBank_Head != flightBank_Tail){
		freeFlight();
	}
	if (flightBank_Tail != NULL) {
		if(flightBank_Tail->reservationList != NULL){
			free(flightBank_Tail->reservationList);
		}
		free(flightBank_Tail);
	}
	if (airportBank != NULL) {
		free(airportBank);
	}
}


int main() {
	Date today = FIRST_TODAY;
	char cmd;
	while ((cmd = getchar()) != EOF && cmd != END_PROGRAM){
		today = readCommand(cmd, today);
	}

	freeAll();
	return 0;
}



