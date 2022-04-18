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
/*extern ResNode* g_allRes_Head_ptr;*/
/*extern ResNode g_allRes_Head;*/

int resListIsEmpty(ResNode* g_allRes_Head_ptr){
	return (g_allRes_Head_ptr == NULL);
}


ResNode* resListInit(Reservation* newRes, ResNode* g_allRes_Head_ptr){
	/*ResNode *head = &g_allRes_Head;*/
	g_allRes_Head_ptr = (ResNode*)malloc(sizeof(ResNode));
	g_allRes_Head_ptr->reservation = newRes;
	/*g_allRes_Head_ptr->reservation->reservationCode = newRes->reservationCode;*/
	g_allRes_Head_ptr->AllRes_next = NULL;
	g_allRes_Head_ptr->AllRes_prev = NULL;
	/*g_allRes_Head_ptr = head;*/
	return g_allRes_Head_ptr;
}

ResNode* insertAtBeginning(Reservation *newRes, ResNode* g_allRes_Head_ptr){
	ResNode *newNode = (ResNode*)malloc(sizeof(ResNode));
	newNode->reservation = newRes;
	newNode->AllRes_next = NULL;
	newNode->AllRes_prev = NULL;
	/*newNode->reservation->reservationCode = newRes->reservationCode;*/
	newNode->AllRes_next = g_allRes_Head_ptr; /* new.next points to head */
	g_allRes_Head_ptr->AllRes_prev = newNode; /* old_head.before  points to new */
	g_allRes_Head_ptr = newNode; /* new becomes new head */
	return g_allRes_Head_ptr;
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


int duplicateReservation(char* reservation_code, ResNode* g_allRes_Head_ptr){

	ResNode *aux=NULL;

	for (aux = g_allRes_Head_ptr; aux != NULL; aux = aux->AllRes_next) {
		if (aux->reservation->reservationCode!= NULL &&
			!strcmp(aux->reservation->reservationCode, reservation_code))
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


Flight* validReservation(FlightID flightId, Date flightDate, char* reservationCode,
					 int passengerNum, Date today, ResNode* g_allRes_Head_ptr){

	Flight * flight_ptr;
	if (!validReservationCode(reservationCode)){
		return NULL;
	}
	flight_ptr = duplicateFlight(flightId, flightDate, 'r');

	/* if the flight exists */
	if (flight_ptr != NULL){

		if (duplicateReservation(reservationCode, g_allRes_Head_ptr) ||
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


ResNode* add_Reservation(FlightID flightId, Date flightDate,
					 char* reservationCode, int passengerNum, Date today,
						 ResNode* g_allRes_Head_ptr) {
	Reservation new;
	int numRes;

	/* validReservation returns pointer to flight */
	Flight *flight_ptr = validReservation(flightId, flightDate,
								 reservationCode, passengerNum, today, g_allRes_Head_ptr);
	if (flight_ptr == NULL)
		return g_allRes_Head_ptr;

	/* adds new reservation to the flight's list of reservations */
	numRes = flight_ptr->numReservations;

	flight_ptr->reservationList = (Reservation*)realloc(
		flight_ptr->reservationList,sizeof(Reservation)*(numRes + 1));

	if (flight_ptr->reservationList == NULL){
		printf(NO_MEMORY);
		freeAll();
		exit(1);
	}

	/* defining the new reservation's info */
	new.reservationCode = (char*)malloc(sizeof(char)*(strlen(reservationCode) + 1));
	strcpy(new.reservationCode, reservationCode);
	new.passengerNum = passengerNum;
	new.flight_ptr = flight_ptr;
	new.flightResListIndex = numRes;
	new.resNode_ptr = NULL;

	flight_ptr->reservationList[numRes] = new;

	/* updates flight info */
	++(flight_ptr->numReservations);
	flight_ptr->numPassengers += passengerNum;

	/* links new reservation to the list of all reservations */
	if (resListIsEmpty(g_allRes_Head_ptr)) {
		g_allRes_Head_ptr = resListInit(&new, g_allRes_Head_ptr);
		flight_ptr->reservationList[numRes].resNode_ptr = g_allRes_Head_ptr;

	} else {
		g_allRes_Head_ptr = insertAtBeginning(&new, g_allRes_Head_ptr);
		flight_ptr->reservationList[numRes].resNode_ptr = g_allRes_Head_ptr;
	}
	/*free(reservationCode);*/
	return g_allRes_Head_ptr;
}


void sortReservations(Reservation *reservationList, int numRes){
	/*very slow basic selection sort*/
	Reservation temp;
	int i,j;
	for (i=0; i < numRes; i++){
		for(j=i+1; j < numRes; j++){
			if (strlen(reservationList[i].reservationCode) >
					strlen(reservationList[j].reservationCode) ||
				(strcmp(reservationList[i].reservationCode,
						reservationList[j].reservationCode) > 0))
			{
				temp = reservationList[i];
				reservationList[i] = reservationList[j];
				reservationList[j] = temp;
			}
		}
	}

}


void listReservations(FlightID flightId, Date flightDate, Date today){

	int i, numRes;
	Reservation res;
	Flight *flight_ptr = duplicateFlight(flightId, flightDate, 'r');

	if (flight_ptr == NULL || !check_date(flightDate, today))
		return;

	numRes = flight_ptr->numReservations;
	sortReservations(flight_ptr->reservationList,
					 flight_ptr->numReservations);

	for (i=0; i < numRes; i++){
		res = flight_ptr->reservationList[i];
		printf("%s %d\n", res.reservationCode, res.passengerNum);
	}

}


/* removes reservatiuon node from all reservations linked list */
ResNode* deleteResNode(ResNode *current, ResNode* g_allRes_Head_ptr){
	ResNode *prev = current->AllRes_prev, *next = current->AllRes_next;

	if (current == g_allRes_Head_ptr){
		g_allRes_Head_ptr = next;
	}
	else {
		prev->AllRes_next = next;
	}
	if (next != NULL)
		next->AllRes_prev = prev;

	return g_allRes_Head_ptr;
}


ResNode* deleteReservation(char* code, ResNode* g_allRes_Head_ptr){

	ResNode *aux=NULL;
	int i, numRes, resIndex;
	Flight *flightPtr;
	for (aux = g_allRes_Head_ptr; aux != NULL; aux = aux->AllRes_next){

		if (!strcmp(aux->reservation->reservationCode, code)){
			/* remove from all reservations list */
			deleteResNode(aux, g_allRes_Head_ptr);

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

			/* deletes aux reservation's memory block */
			/*free(aux);*/	/* NECESSARY??????*/

			return g_allRes_Head_ptr;
		}
	}
	printf(NOT_FOUND);
	/* if the reservation wasn't found */
	return g_allRes_Head_ptr;
}



ResNode* deleteFlightReservations(Flight* flight_ptr, ResNode* g_allRes_Head_ptr){

	ResNode *current;
	int i, numRes = flight_ptr->numReservations;
	for (i=0; i<numRes; i++){

		current = flight_ptr->reservationList[i].resNode_ptr;
		g_allRes_Head_ptr = deleteResNode(current, g_allRes_Head_ptr);
	}
	/* frees the memory of all this flight's reservations */
	if (flight_ptr->reservationList != NULL)
		free(flight_ptr->reservationList);

	return g_allRes_Head_ptr;
}


