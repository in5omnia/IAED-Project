/*
* File: airport.c
* Author: Beatriz Gavilan - 102463
* Description: Contains all the functions related to the airports.
*/


#include "BG_102463.h"

/*	includes global variable */
extern int g_TotalOfAirports;


/*	Creates an airport	*/
Airport createAirport(char airportID[MAX_AIRPORT_ID],
					  char country[MAX_COUNTRY], char city[MAX_CITY]){
	Airport airport;

	strcpy(airport.ID, airportID);
	strcpy(airport.country, country);
	strcpy(airport.city, city);
	airport.n_Departure_Flights = 0;

	return airport;
}


/*	Adds an airport to the system	*/
void addAirport(Airport new_airport, Airport airportBank[MAX_AIRPORTS]){

	airportBank[g_TotalOfAirports] = new_airport;
}


/*	Checks if an airportID is valid: if it's made of 3 upper case letters.
 * Returns 1 if it's valid and 0 if not.	*/
int validAirportID(char airportID[MAX_AIRPORT_ID]){

	int i;

	for (i=0; airportID[i] != '\0'; i++){

		if (i >= MAX_AIRPORT_ID-1) {	/*	more than 3 letters */
			printf(INVALID_AIRPORT_ID);
			return 0;
		}

		/* not all upper case */
		if (airportID[i] < 'A' || airportID[i] > 'Z') {
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


/*	Checks if an airport exists in the system. Returns 1 if so and 0 if not. */
int airportExist(char airportID[MAX_AIRPORT_ID],
				 Airport airportBank[MAX_AIRPORTS], char flag){
	int i;

	for (i=0; i < g_TotalOfAirports; i++){
		/*	Compares the airportID with each system's airport' ID	*/
		if (!strcmp(airportID, airportBank[i].ID)) {	/*	same ID	*/
			if (CASE_A) {
				printf(DUPLICATE_AIRPORT);
			}
			return ++i;
		}
	}

	if (!CASE_A)	/*	Case A doesn't require this message	*/
		printf(OUT_NO_AIRPORT_ID, airportID);

	return 0;
}


/*	Compares 2 words made of 3 letters in relation to their alphabetical order.
 * Returns 1 if they're ordered and 0 if not.	*/
int beforeLetters(char beforeWord[MAX_AIRPORT_ID],
				  char afterWord[MAX_AIRPORT_ID]) {

	return (less(beforeWord[0], afterWord[0]) ||

			((beforeWord[0] == afterWord[0])
			 && less(beforeWord[1], afterWord[1])) ||

			((beforeWord[0] == afterWord[0])
				&& (beforeWord[1] == afterWord[1])
				&& less(beforeWord[2], afterWord[2])));
}


/*	Exchanges 2 airports' placement in the airportBank array. */
void exch(Airport airportBank[MAX_AIRPORTS], int i, int right, char flag){

	if (flag == 'l') {

		Airport t = airportBank[i];
		airportBank[i] = airportBank[right];
		airportBank[right] = t;
	}
}

/*	Creates partitions of airports (based on quicksort's algorithm) to
 * sort alphabetically. */
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


/*	Sorts an array of airports in alphabetical order. */
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


/*	Lists airports of an array in the standard output.	*/
void listAirports(Airport airportList[MAX_AIRPORTS], int num){
	int i;

	if (!num) {
		num = g_TotalOfAirports;
	}

	for (i=0; i < num; i++)

		printf(OUT_AIRPORT, airportList[i].ID, airportList[i].city,
			   airportList[i].country, airportList[i].n_Departure_Flights);

}


/*	Finds the airports that exist with the requested IDs and stores them in the
 * requestedAirports array for posterior access and returns the number of
 * airports found. */
int findAirports(int num_IDs, int existingID[MAX_AIRPORTS],
				 Airport airportBank[MAX_AIRPORTS],
				 Airport requestedAirports[MAX_AIRPORTS],
				 char requested_IDs[MAX_AIRPORTS][MAX_AIRPORT_ID]){

	int i, e, c, num_airports_found=0;

	for (c=0; c < num_IDs; c++){
		existingID[c] = 0;	/* initializes vector that checks IDs with 0 */
	}

	for (i=0; i < g_TotalOfAirports; i++){
		/*	we have all the requested flights */
		if (num_airports_found == num_IDs)
			break;

		for (e=0; e < num_IDs; e++){

			if (!strcmp(airportBank[i].ID, requested_IDs[e])){

				requestedAirports[e] = airportBank[i];
				num_airports_found++;
				existingID[e] = 1;
				break;
			}
		}
	}
	return num_airports_found;
}


/*	Lists in the standard output the airports associated to the requested IDs
 * if they exist, and the error messages to those that don't.   */
void listRequestedAirports(Airport airportBank[MAX_AIRPORTS],
						   char requested_IDs[MAX_AIRPORTS][MAX_AIRPORT_ID],
						   int num_IDs){

	int a, num_airports_found, existingID[MAX_AIRPORTS];
	Airport requestedAirports[MAX_AIRPORTS];

	num_airports_found = findAirports(num_IDs, existingID, airportBank,
									  requestedAirports, requested_IDs);

	/* only checks existence if not all were found */
	if (num_airports_found != num_IDs){

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
