/*
* File:
* Author: Beatriz Gavilan - 102463
* Description:
 */

#include "BG_102463.h"
#include "reservations.h"

/* includes global variable */
extern int g_TotalOfFlights;
extern Flight* flightBank_Tail;
extern Flight* flightBank_Head;
extern ResNode* g_allRes_Head;
/*extern ResNode g_allRes_Head;*/

int resListIsEmpty(){
	return (g_allRes_Head == NULL);
}

/* initializes doubly linked list of all reservations */
ResNode* resListInit(Reservation* newRes){
	/*ResNode *head = &g_allRes_Head;*/
	ResNode *head = (ResNode*)malloc(sizeof(ResNode));
	head->reservation = newRes;
	head->AllRes_next = NULL;
	head->AllRes_prev = NULL;
	g_allRes_Head = head;
	return g_allRes_Head;
}


/* links new reservation to the doubly linked list of all reservations */
ResNode* insertAtBeginning(Reservation *newRes){
	ResNode *newNode = (ResNode*)malloc(sizeof(ResNode));
	newNode->reservation = newRes;
	newNode->AllRes_next = NULL;
	newNode->AllRes_prev = NULL;

	newNode->AllRes_next = g_allRes_Head; /* new.next points to head */
	g_allRes_Head->AllRes_prev = newNode; /* old_head.before  points to new */
	g_allRes_Head = newNode; /* new becomes new head */
	return newNode;
}


int validReservationCode(char* reservationCode){
	int i;
	/* the code can't be less than 10 characters long */

	if (strlen(reservationCode) < 10)
		return 0;

	for (i = 0; reservationCode[i] != '\0'; i++){
		/* invalid if a string character isn't a digit or a capital letter */
		if (!( (reservationCode[i] >= 'A' && reservationCode[i] <= 'Z') ||
			  (reservationCode[i] >= '0' && reservationCode[i] <= '9') )){

			printf(OUT_INVALID_RES_CODE);
			return 0;
		}
	}
	return 1;
}


int duplicateReservation(char* reservation_code){

	ResNode *aux=NULL;

	for (aux = g_allRes_Head; aux != NULL; aux = aux->AllRes_next) {
		if (aux->reservation->reservationCode!= NULL && !strcmp(aux->reservation->reservationCode, reservation_code))
		{
			printf(DUPLICATE_RESERVATION, reservation_code);
			return 1;
		}
	}
	/*free(aux);*/	/*NECESSARY????*/
	return 0;
}


int tooManyReservations(int reservationPassengers, Flight *flight_ptr){
	if ((flight_ptr->numPassengers + reservationPassengers) >
		flight_ptr->capacity){
		printf(TOO_MANY_RESERVATIONS);
		return 1;
	}
	return 0;
}


Flight* validReservation(char flightId[], Date flightDate, char* reservationCode,
						 int passengerNum, Date today){

	Flight * flight_ptr;
	if (!validReservationCode(reservationCode)){
		return NULL;
	}
	flight_ptr = duplicateFlight(flightId, flightDate, 'r');

	/* if the flight exists */
	if (flight_ptr != NULL){

		if (duplicateReservation(reservationCode) ||
			tooManyReservations(passengerNum, flight_ptr) ||
			!check_date(flightDate, today))
			return NULL;

		if (!VALID_PASSENGER_NUM) {
			printf(OUT_INVALID_PASSENGER_NUM);
			return NULL;
		}
	}
	return flight_ptr;
}


int add_Reservation(char flightId[], Date flightDate,
					char* reservationCode, int passengerNum, Date today) {
	Reservation* new=(Reservation*)malloc(sizeof(Reservation));
	int numRes;

	/* validReservation returns pointer to flight */
	Flight *flight_ptr = validReservation(flightId, flightDate,
										  reservationCode, passengerNum, today);
	if (flight_ptr == NULL)
		return 0;

	/* adds new reservation to the flight's list of reservations */
	numRes = flight_ptr->numReservations;

	flight_ptr->reservationList = (Reservation**)realloc(
		flight_ptr->reservationList,sizeof(Reservation*)*(numRes + 1));

	if (flight_ptr->reservationList == NULL){
		printf(NO_MEMORY);
		freeAll();
		exit(1);
	}

	/* defining the new reservation's info */

	new->reservationCode = reservationCode;
	new->passengerNum = passengerNum;
	new->flight_ptr = flight_ptr;
	new->flightResListIndex = numRes;
	new->resNode_ptr = NULL;

	flight_ptr->reservationList[numRes] = new;

	/* updates flight info */
	++(flight_ptr->numReservations);
	flight_ptr->numPassengers += passengerNum;

	if (resListIsEmpty()) {
		flight_ptr->reservationList[numRes]->resNode_ptr = resListInit(new);

	} else {
		flight_ptr->reservationList[numRes]->resNode_ptr =
			insertAtBeginning(new);
	}

	return 1;
}


void sortReservations(Reservation **reservationList, int numRes){
	/*very slow basic selection sort*/
	Reservation* temp;
	int i,j;
	for (i=0; i < numRes; i++){
		for(j=i+1; j < numRes; j++){
			if (strlen(reservationList[i]->reservationCode) >
					strlen(reservationList[j]->reservationCode) ||
				(strcmp(reservationList[i]->reservationCode,
						reservationList[j]->reservationCode) > 0))
			{
				temp = reservationList[i];
				reservationList[i] = reservationList[j];
				reservationList[j] = temp;
			}
		}
	}

}


void listReservations(char flightId[], Date flightDate, Date today){

	int i, numRes;
	Reservation* res;
	Flight *flight_ptr = duplicateFlight(flightId, flightDate, 'r');

	if (flight_ptr == NULL || !check_date(flightDate, today))
		return;

	numRes = flight_ptr->numReservations;
	sortReservations(flight_ptr->reservationList,
					 flight_ptr->numReservations);

	for (i=0; i < numRes; i++){
		res = flight_ptr->reservationList[i];
		printf("%s %d\n", res->reservationCode, res->passengerNum);
	}

}


/* removes reservatiuon node from all reservations linked list */
void deleteResNode(ResNode *current){
	ResNode *prev = current->AllRes_prev, *next = current->AllRes_next;

	if (current == g_allRes_Head){
		g_allRes_Head = next;
	}
	else {
		prev->AllRes_next = next;
	}
	if (next != NULL)
		next->AllRes_prev = prev;

}


int deleteReservation(char* code){

	ResNode *aux=NULL;
	int i, numRes, resIndex;
	Flight *flightPtr;
	for (aux = g_allRes_Head; aux != NULL; aux = aux->AllRes_next){

		if (!strcmp(aux->reservation->reservationCode, code)){
			/* remove from all reservations list */
			deleteResNode(aux);

			/* removes from flight's list of reservations */
			flightPtr = aux->reservation->flight_ptr;
			numRes = flightPtr->numReservations;
			resIndex = aux->reservation->flightResListIndex;
			flightPtr->numPassengers -= aux->reservation->passengerNum;

			for (i=resIndex; i < numRes-1; i++)
				/* move each reservation to the left */
				flightPtr->reservationList[resIndex] =
					flightPtr->reservationList[resIndex+1];

			/* reallocates array's memory */
			flightPtr->reservationList =
				realloc(flightPtr->reservationList,
						sizeof(Reservation)*
							(--flightPtr->numReservations));

			return 1;
		}
	}
	return 0;
}



void deleteFlightReservations(Flight* flight_ptr){

	ResNode *current;
	int i, numRes = flight_ptr->numReservations;
	for (i=0; i<numRes; i++){

		current = flight_ptr->reservationList[i]->resNode_ptr;
		deleteResNode(current);
	}
	/* frees the memory of all this flight's reservations */
	if (flight_ptr->reservationList != NULL)
		free(flight_ptr->reservationList);
}


