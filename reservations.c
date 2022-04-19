/*
 * File:
 * Author: Beatriz Gavilan - 102463
 * Description:
 */

#include "reservations.h"

#include "BG_102463.h"

/* includes global variable */
extern int g_TotalOfFlights;
extern Flight* flightBank_Tail;
extern Flight* flightBank_Head;
/*extern ResNode* g_allRes_Head;*/
extern ResNode* hashTable[HASH_TABLE_SIZE];
/*extern ResNode g_allRes_Head;*/



int validReservationCode(char* reservationCode) {
	int i;
	/* the code can't be less than 10 characters long */

	if (strlen(reservationCode) < 10) return 0;

	for (i = 0; reservationCode[i] != '\0'; i++) {
		/* invalid if a string character isn't a digit or a capital letter */
		if (!((reservationCode[i] >= 'A' && reservationCode[i] <= 'Z') ||
			  (reservationCode[i] >= '0' && reservationCode[i] <= '9'))) {
			printf(OUT_INVALID_RES_CODE);
			return 0;
		}
	}
	return 1;
}


int duplicateReservation(char* reservation_code) {
	/*aux->reservation->reservationCode!= NULL*/

	int hashValue = hash(reservation_code);

	if (STsearch(reservation_code, hashValue) != NULL) {
		printf(DUPLICATE_RESERVATION, reservation_code);
		return 1;
	}

	return 0;
}


int tooManyReservations(int reservationPassengers, Flight* flight_ptr) {
	if ((flight_ptr->numPassengers + reservationPassengers) >
		flight_ptr->capacity) {
		printf(TOO_MANY_RESERVATIONS);
		return 1;
	}
	return 0;
}


Flight* validReservation(char flightId[], Date flightDate,
						 char* reservationCode, int passengerNum, Date today) {
	Flight* flight_ptr;
	if (!validFlightID(flightId)) {
		return NULL;
	}

	if (!validReservationCode(reservationCode)) {
		return NULL;
	}

	flight_ptr = duplicateFlight(flightId, flightDate, 'r');
	if (flight_ptr == NULL) {
		return NULL;
	}

	if (duplicateReservation(reservationCode) ||
		tooManyReservations(passengerNum, flight_ptr) ||
		!check_date(flightDate, today)) {
		return NULL;
	}

	if (!VALID_PASSENGER_NUM) {
		printf(OUT_INVALID_PASSENGER_NUM);
		return NULL;
	}

	return flight_ptr;
}


void listReservations(char flightId[], Date flightDate, Date today) {
	Reservation* res;
	Flight* flight_ptr;

	if (!validFlightID(flightId)) {
		return;
	}

	flight_ptr = duplicateFlight(flightId, flightDate, 'r');

	if (flight_ptr == NULL || !check_date(flightDate, today)) return;

	for (res = flight_ptr->flightResHead; res != NULL; res = res->next) {
		printf("%s %d\n", res->reservationCode, res->passengerNum);
	}
}

/*		LIST FLIGHTS RESERVATIONS	*/

/*START OF NEW CODE*/

void flightResList_Init(Flight* flight_ptr, Reservation* new) {
	flight_ptr->flightResHead = new;
	new->next = NULL;
	new->prev = NULL;
}


int beforeRes(Reservation* res1, Reservation* res2) {
	return (strlen(res1->reservationCode) < strlen(res2->reservationCode) ||
			(strcmp(res1->reservationCode, res2->reservationCode) < 0));
}


void insertBetween(Reservation* prev, Reservation* next, Reservation* new, Flight* flight_ptr) {
	if (prev == NULL){
		new->prev = NULL;
		flight_ptr->flightResHead = new;
	}
	else
		new->prev = prev;

	if (next == NULL)
		new->next = NULL;
	else
		new->next = next;

	if (prev != NULL) prev->next = new;

	if (next != NULL) next->prev = new;
}


void addFlightRes_InOrder(Flight* flight_ptr, Reservation* new) {
	Reservation *head = flight_ptr->flightResHead, *aux = head, *prev = NULL;

	while (aux != NULL && beforeRes(aux, new)) {
		prev = aux;
		aux = aux->next;
	}
	insertBetween(prev, aux, new, flight_ptr);
}


int add_Reservation(char flightId[], Date flightDate, char* reservationCode,
					int passengerNum, Date today) {

	Reservation* new = (Reservation*)malloc(sizeof(Reservation));
	Flight* flight_ptr = validReservation(flightId, flightDate, reservationCode,
										  passengerNum, today);
	int hashValue;

	if (new == NULL) {
		noMemory();
	}

	if (flight_ptr == NULL) return 0;

	new->reservationCode = reservationCode;
	new->passengerNum = passengerNum;
	new->flight_ptr = flight_ptr;
	new->next = NULL;
	new->prev = NULL;

	/* add to flight */
	if (flight_ptr->flightResHead == NULL) {
		flightResList_Init(flight_ptr, new);
	} else {
		addFlightRes_InOrder(flight_ptr, new);
	}

	/* ADD TO HASTABLE*/
	hashValue = hash(reservationCode);
	insertInHashTable(new, hashValue);

	flight_ptr->numPassengers += passengerNum;

	return 1;
}


void deleteResFromFlight(Reservation* res) {
	res->flight_ptr->numPassengers -= res->passengerNum;
	if (res->next != NULL) res->next->prev = res->prev;
	if (res->prev != NULL)
		res->prev->next = res->next;
	else
		res->flight_ptr->flightResHead = res->next;
}


void deleteFlightReservations(Flight* flight_ptr) {
	Reservation *res, *next;

	for (res = flight_ptr->flightResHead; res != NULL; res = next) {
		next = res->next;
		deleteReservation(res->reservationCode, 0);
	}

}


int deleteFlight(char flightID[]) {
	Flight *aux, *next;
	int flag = 0;
	for (aux = flightBank_Head; aux != NULL; aux = next) {

		if (!strcmp(flightID, aux->ID)) {
			deleteFlightReservations(aux);

			if (aux == flightBank_Head)
				flightBank_Head = aux->next;
			else
				aux->prev->next = aux->next;

			if (aux == flightBank_Tail)
				flightBank_Tail = aux->prev;
			else
				aux->next->prev = aux->prev;

			next = aux->next;
			free(aux);
			flag = 1;

		} else {
			next = aux->next;
		}
	}
	return flag;
}
