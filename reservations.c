/*
* File:
* Author: Beatriz Gavilan - 102463
* Description:
 */

#include "BG_102463.h"
#include "reservations.h"

/* includes global variable */
extern int g_TotalOfFlights;
extern Flight* flightBank;

/* new global variables */
/* pointer to the first reservation in a list */
Reservation *g_allResHead = NULL;


int validReservationCode(char* reservationCode){
	int i;
	/* the code can't be less than 10 characters long */
	if (strlen(reservationCode) < 10)
		return 0;

	for (i = 0; reservationCode[i] != '\0'; i++){
		/* invalid if a string character isn't a digit or a capital letter */
		if (!( (reservationCode[i] > 'A' && reservationCode[i] < 'Z') ||
			  (reservationCode[i] >'0' && reservationCode[i] < '9') )){

			printf(OUT_INVALID_RES_CODE);
			return 0;
		}
	}
	return 1;
}


int duplicateReservation(char* reservation_code){

	Reservation *aux;

	for (aux = g_allResHead; aux != NULL; aux = aux->allRes_Next) {
		if (!strcmp(aux->reservationCode, reservation_code))
		{
			printf(DUPLICATE_RESERVATION);
			return 1;
		}
	}
	free(aux);	/*NECESSARY????*/
	return 0;
}


int tooManyReservations(int reservationPassengers, int index){
	if ((flightBank[index].numPassengers + reservationPassengers) >
		flightBank[index].capacity){
		printf(TOO_MANY_RESERVATIONS);
		return 1;
	}
	return 0;
}


int validReservation(FlightID flightId, Date flightDate, char* reservationCode,
					 int passengerNum, Date today){
	int indexPlus1;
	if (!validReservationCode(reservationCode)){
		return 0;
	}
	indexPlus1 = duplicateFlight(flightId, flightDate, 'r');
	/* if the flight exists */
	if (indexPlus1){

		if (duplicateReservation(reservationCode) ||
			tooManyReservations(passengerNum, indexPlus1-1) ||
			!check_date(flightDate, today))
			return 0;

		if (!VALID_PASSENGER_NUM) {
			printf(OUT_INVALID_PASSENGER_NUM);
			return 0;
		}
	}
	return indexPlus1;
}


int add_Reservation(FlightID flightId, Date flightDate,
					 char* reservationCode, int passengerNum, Date today) {
	Reservation new;
	int numRes;
	/* validReservation returns flight's index in flightBank plus 1 */
	int index = validReservation(flightId, flightDate,
								 reservationCode, passengerNum, today);
	if (!index)
		return 0;

	/*new = (Reservation*)malloc(sizeof(Reservation));*/

	/* adds new reservation to the flight's list of reservations */
	numRes = flightBank[index].numReservations;

	flightBank[index].reservationList = realloc(
		flightBank[index].reservationList,sizeof(Reservation)*(numRes + 1));

	if (flightBank[index].reservationList == NULL)
		printf(NO_MEMORY);


	/* defining the new reservation's info */
	new.reservationCode = (char*)malloc(sizeof(char*)*
										(strlen(reservationCode)+1));
	strcpy(new.reservationCode, reservationCode);
	new.passengerNum = passengerNum;
	new.flightBankIndex = --index;
	new.flightResListIndex = numRes;
	new.allRes_Prev = NULL;	/* new.before points to NULL */
	new.allRes_Next = NULL;

	flightBank[index].reservationList[numRes] = new;

	/* updates the rest of the flight info */
	++(flightBank[index].numReservations);
	flightBank[index].numPassengers += passengerNum;

	/* links new reservation to the list of all reservations */

	new.allRes_Next = g_allResHead;	/* new.next points to head */
	g_allResHead->allRes_Prev = &new;	/* old_head.before  points to new */
	g_allResHead = &new;	/* new becomes new head */
	return 1;
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

	int index = duplicateFlight(flightId, flightDate, 'r'),
		i, numRes = flightBank[index-1].numReservations;
	Reservation res;

	if (!index || !check_date(flightDate, today))
		return;
	--index;

	sortReservations(flightBank[index].reservationList,
					 flightBank[index].numReservations);

	for (i=0; i < numRes; i++){
		res = flightBank[index].reservationList[i];
		printf("%s %d\n", res.reservationCode, res.passengerNum);
	}

}


int deleteReservation(char* code){

	Reservation *aux=NULL/*, *last=NULL*/;
	int i, numRes, resIndex, flightIndex;
	for (aux = g_allResHead; aux != NULL; /*last = aux, */aux = aux->allRes_Next){

		if (!strcmp(aux->reservationCode, code)){

			/* remove from all reservations list */
			if (aux == g_allResHead)
				g_allResHead = aux->allRes_Next;

			else
				aux->allRes_Prev->allRes_Next = aux->allRes_Next;
				/*last->allRes_Next = aux->allRes_Next;*/


			/* removes from flight's list of reservations */
			flightIndex = aux->flightBankIndex;
			numRes = flightBank[flightIndex].numReservations;
			resIndex = aux->flightResListIndex;
			flightBank[flightIndex].numPassengers -= aux->passengerNum;

			for (i=resIndex; i < numRes-1; i++)
				/* move each reservation to the left */
				flightBank[flightIndex].reservationList[resIndex] =
					flightBank[flightIndex].reservationList[resIndex+1];


			/* reallocates array's memory */
			flightBank[flightIndex].reservationList =
				realloc(flightBank[flightIndex].reservationList,
						sizeof(Reservation)*
						(--flightBank[flightIndex].numReservations));

			/* deletes aux reservation's memory block */
			/*free(aux);*/	/* NECESSARY??????*/
			return 1;
		}
	}
	/* if the reservation wasn't found */
	return 0;
}





