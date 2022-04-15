/*
* File:
* Author: Beatriz Gavilan - 102463
* Description:
 */

#include "BG_102463.h"
#include "reservations.h"

/* includes global variable */
extern int g_TotalOfFlights;


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


int duplicateReservation(char* reservation_code, int index,
							Flight flightBank[MAX_FLIGHTS]){
	Reservation *temp;
	for (temp = flightBank[index].reservationHead; temp != NULL;
		 temp = temp->next)
	{
		if (!strcmp(temp->reservationCode, reservation_code)){

			printf(DUPLICATE_RESERVATION);
			return 1;
		}
	}
	return 0;
}


int tooManyReservations(int reservationPassengers, int index,
						Flight flightBank[MAX_FLIGHTS]){
	if ((flightBank[index].numPassengers + reservationPassengers) >
		flightBank[index].capacity){
		printf(TOO_MANY_RESERVATIONS);
		return 1;
	}
	return 0;
}



int validReservation(Flight flightBank[MAX_FLIGHTS], FlightID flightId,
					  Date flightDate, char* reservationCode,
					  int passengerNum, Date today){
	int index;
	if (!validReservationCode(reservationCode)){
		return 0;
	}
	index = duplicateFlight(flightId, flightDate, flightBank, 'r');
	/* if the flight exists */
	if (index){
		index -= 1;

		if (duplicateReservation(reservationCode, index, flightBank) ||
			tooManyReservations(passengerNum, index, flightBank) ||
			!check_date(flightDate, today))
			return 0;

		if (!VALID_PASSENGER_NUM) {
			printf(OUT_INVALID_PASSENGER_NUM);
			return 0;
		}
	}
	return index+1;
}


void add_Reservation(Flight flightBank[MAX_FLIGHTS], FlightID flightId,
				Date flightDate, char* reservationCode,
				int passengerNum, Date today)
{
	Reservation new;
	/* validReservation returns flight's index in flightBank plus 1 */
	int index = validReservation(flightBank, flightId, flightDate, reservationCode,
								 passengerNum, today);
	if (!index)
		return;

	/* defining the new reservation's info */
	new.reservationCode = reservationCode;
	new.passengerNum = passengerNum;

	/* new reservation will point to reservationHead */
	new.next = flightBank[--index].reservationHead;
	/* reservationHead will point to the new reservation */
	flightBank[index].reservationHead = &new;
}



void listReservations(Flight flightBank[MAX_FLIGHTS], FlightID flightId,
				 Date flightDate){

}


void commandR(Flight flightBank[MAX_FLIGHTS], Date today)
{
	char *reservationCode;
	int passengerNum;
	FlightID flightId;
	Date flightDate;

	scanf(IN_FLIGHT_ID, flightId.letters, &flightId.num);
	scanf(IN_DATE, &flightDate.day, &flightDate.month, &flightDate.year);

	if (getchar()!='\n'){

		reservationCode = malloc(sizeof (char)*MAX_CMD);
		scanf(IN_RES_CODE_AND_PASS, reservationCode, &passengerNum);

		reservationCode = realloc(reservationCode,
								  sizeof(char)*strlen(reservationCode));

		add_Reservation(flightBank, flightId, flightDate, reservationCode,
						passengerNum, today);
	}
	else{
		listReservations(flightBank, flightId, flightDate);
	}

}



void commandE(Airport airportBank[MAX_AIRPORTS],
			  Flight flightBank[MAX_FLIGHTS]){}