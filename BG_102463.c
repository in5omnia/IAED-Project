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
Date today = FIRST_TODAY;

/*	initializes array of all airports currently in the system	*/
Airport *airportBank = NULL;
/*	initializes doubly linked list of flights currently in the system	*/
Flight* flightBank_Tail = NULL;
Flight* flightBank_Head = NULL;
/* initializes linked list of reservations */
/*ResNode *g_allRes_Head_ptr = NULL;*/
/*ResNode g_allRes_Head;*/

/*	identifies command and redirects to associated function	*/
ResNode* readCommand(char cmd, ResNode* g_allRes_Head_ptr) {

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

		case 'r': g_allRes_Head_ptr = commandR(today, g_allRes_Head_ptr);
			break;

		case 'e': g_allRes_Head_ptr = commandE(g_allRes_Head_ptr);
			break;
	}
	return g_allRes_Head_ptr;
}


void freeFlight(){
	Flight *temp = flightBank_Head;
	int i;
	if (temp->reservationList != NULL){
		for (i = 0; i < temp->numReservations; i++){
			free(temp->reservationList[i].reservationCode);
		}
		free(temp->reservationList);
	}
	flightBank_Head = flightBank_Head->next;
	free(temp);
	temp=NULL;
	flightBank_Head->prev = NULL;
}

void freeAll(){
	while (flightBank_Head != flightBank_Tail){
		/*free(temp->ID.letters);*/
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

	ResNode *g_allRes_Head_ptr = NULL;
	char cmd;
	/*	gets commands from standard input	*/
	while ((cmd = getchar()) != EOF && cmd != END_PROGRAM){
		g_allRes_Head_ptr = readCommand(cmd, g_allRes_Head_ptr);
	}

	freeAll();
	return 0;
}



