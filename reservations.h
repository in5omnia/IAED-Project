//
// Created by Beatriz Gavilan on 15/04/2022.
//

#ifndef RESERVATIONS_H
#define RESERVATIONS_H


#define FLIGHT_DOESNT_EXIST "flight does not exist"
#define OUT_INVALID_PASSENGER_NUM "invalid passenger number"
#define OUT_INVALID_RES_CODE "invalid reservation code"
#define DUPLICATE_RESERVATION "flight reservation already used"
#define TOO_MANY_RESERVATIONS "too many reservations"

#define IN_RES_CODE_AND_PASS "%s %d"


typedef struct reservation {
	/*Flight resFlight;		obtido atraves de flightid e date */
	char* reservationCode;
	int passengerNum;
	struct reservation *next;
	struct reservation *resListNext;
} Reservation;



#endif
