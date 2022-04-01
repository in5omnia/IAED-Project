/*
* File: airport.c
* Author: Beatriz Gavilan - 102463
* Description:
*/


#include "BG_102463.h"

/*	includes global variable */
extern int g_TotalOfAirports;


Airport createAirport(char airportID[MAX_AIRPORT_ID],
					  char country[MAX_COUNTRY], char city[MAX_CITY]){
	Airport airport;

	strcpy(airport.ID, airportID);
	strcpy(airport.country, country);
	strcpy(airport.city, city);
	airport.n_Departure_Flights = 0;

	return airport;
}


void addAirport(Airport new_airport, Airport airportBank[MAX_AIRPORTS]){

	airportBank[g_TotalOfAirports] = new_airport;
}


int validAirportID(char airportID[MAX_AIRPORT_ID]){

	int i;

	for (i=0; airportID[i] != '\0'; i++){

		if (i >= MAX_AIRPORT_ID-1) {	/*	more than 3 letters */
			printf(INVALID_AIRPORT_ID);
			return 0;
		}

		if (airportID[i] < 'A' || airportID[i] > 'Z') {	/* not all upper case */
			printf(INVALID_AIRPORT_ID);
			return 0;
		}

	}

	if (i < MAX_AIRPORT_ID-1) {	/* menos de 3 letras */
		printf(INVALID_AIRPORT_ID);
		return 0;
	}

	return 1;
}


int airportExist(char airportID[MAX_AIRPORT_ID],
				 Airport airportBank[MAX_AIRPORTS], char flag){
	int i;

	for (i=0; i < g_TotalOfAirports; i++){

		if (!strcmp(airportID, airportBank[i].ID)) {
			if (CASE_A) {
				printf(DUPLICATE_AIRPORT);
			}
			return ++i;
		}
	}

	if (!CASE_A)
		printf(OUT_NO_AIRPORT_ID, airportID);

	return 0;
}



int beforeLetters(char beforeWord[MAX_AIRPORT_ID],
				  char afterWord[MAX_AIRPORT_ID]) {

	return (less(beforeWord[0], afterWord[0]) ||

			((beforeWord[0] == afterWord[0])
			 && less(beforeWord[1], afterWord[1])) ||

			((beforeWord[0] == afterWord[0])
				&& (beforeWord[1] == afterWord[1])
				&& less(beforeWord[2], afterWord[2])));
}


void exch(Airport airportBank[MAX_AIRPORTS], int i, int right, char flag){

	if (flag == 'l') {

		Airport t = airportBank[i];
		airportBank[i] = airportBank[right];
		airportBank[right] = t;
	}
}

int partition(Airport airportBank[MAX_AIRPORTS], int left, int right, char flag)
{
	int i = left-1;
	int j = right;

	if (flag == 'l') {

		char v[MAX_AIRPORT_ID];
		strcpy(v, airportBank[right].ID);

		while (i < j) {

			while (beforeLetters(airportBank[++i].ID, v));

			while (beforeLetters(v, airportBank[--j].ID)){
				if (j == left)
					break;

			}
			if (i < j)
				exch(airportBank, i, j, 'l');
		}
		exch(airportBank, i, right, 'l');
	}
	return i;
}


void sortAirports(Airport airportBank[MAX_AIRPORTS], int left, int right,
				  char flag)
{
	int i;

	if (right <= left)
		return;

	i = partition(airportBank, left, right, flag);
	sortAirports(airportBank, left, i - 1, flag);
	sortAirports(airportBank, i + 1, right, flag);
}


void listAirports(Airport airportBank[MAX_AIRPORTS], int num){
	int i;

	if (!num) {
		num = g_TotalOfAirports;
	}

	for (i=0; i < num; i++)

		printf(OUT_AIRPORT, airportBank[i].ID, airportBank[i].city,
			   airportBank[i].country, airportBank[i].n_Departure_Flights);

}



int findAirports(int num_IDs, int existingID[MAX_AIRPORTS],
				 Airport airportBank[MAX_AIRPORTS],
				 Airport requestedAirports[MAX_AIRPORTS],
				 char requested_IDs[MAX_AIRPORTS][MAX_AIRPORT_ID]){

	int i, e, c, n=0;

	for (c=0; c < num_IDs; c++){
		existingID[c] = 0;	/* initializes vector that checks IDs with 0 */
	}

	for (i=0; i < g_TotalOfAirports; i++){

		if (n == num_IDs)		/*	we have all the requested flights */
			break;

		for (e=0; e < num_IDs; e++){

			if (!strcmp(airportBank[i].ID, requested_IDs[e])){

				requestedAirports[e] = airportBank[i];
				n++;
				existingID[e] = 1;
				break;
			}
		}
	}
	return n;
}



void listRequestedAirports(Airport airportBank[MAX_AIRPORTS],
						   char requested_IDs[MAX_AIRPORTS][MAX_AIRPORT_ID],
						   int num_IDs){

	int a, n, existingID[MAX_AIRPORTS];
	Airport requestedAirports[MAX_AIRPORTS];

	n = findAirports(num_IDs, existingID, airportBank, requestedAirports,
					 requested_IDs);

	if (n != num_IDs){	/* only checks existence if not all were found */

		for (a=0; a < num_IDs; a++){	/* validates ID's existence */

			if (!existingID[a]){

				printf(OUT_NO_AIRPORT_ID, requested_IDs[a]);
			}
			else{
				printf(OUT_AIRPORT, requestedAirports[a].ID,
					   requestedAirports[a].city,
					   requestedAirports[a].country,
					   requestedAirports[a].n_Departure_Flights);
			}
		}
	}
	else {
		listAirports(requestedAirports, num_IDs);
	}

}
