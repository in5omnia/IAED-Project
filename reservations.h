/*
* File: reservations.h
* Author: Beatriz Gavilan - 102463
* Description: header file for reservations
 */

#ifndef RESERVATIONS_H
#define RESERVATIONS_H


#define FLIGHT_DOESNT_EXIST "flight does not exist\n"
#define OUT_INVALID_PASSENGER_NUM "invalid passenger number\n"
#define OUT_INVALID_RES_CODE "invalid reservation code\n"
#define DUPLICATE_RESERVATION "flight reservation already used\n"
#define TOO_MANY_RESERVATIONS "too many reservations\n"
#define NO_MEMORY "No memory\n"
#define NOT_FOUND "not found\n"

#define IN_RES_CODE_AND_PASS "%s %d"


typedef struct reservation {
	/*Flight resFlight;        obtido atraves de flightid e date */
	char* reservationCode;
	int passengerNum;
	int flightBankIndex;
	int flightResListIndex;
	/*struct reservation *flightRes_Before, *flightRes_Next;*/
	struct reservation *allRes_Next, *allRes_Prev;
} Reservation;




#endif
