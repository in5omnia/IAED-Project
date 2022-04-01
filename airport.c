/*
* File:
* Author:
* Description:
*/


/*#include "BG_102463.h"*/
#include "flight.c"


extern int g_total_of_airports;



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
	airportBank[g_total_of_airports] = new_airport;
	return;
}


int validAirportID(char airportID[MAX_AIRPORT_ID]){
	int i;
	for (i=0; airportID[i] != '\0'; i++){
		if (i >= MAX_AIRPORT_ID-1) {	/*	mais de 3 letras */
			printf(INVALID_AIRPORT_ID);
			return 0;
		}
		if (airportID[i] < 'A' || airportID[i] > 'Z') {	/* nao sao maiusculas */
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
	for (i=0; i < g_total_of_airports; i++){
		if (!strcmp(airportID, airportBank[i].ID)) {
			if (flag == 'a') {
				printf(DUPLICATE_AIRPORT);
			}
			return ++i;
		}
	}
	if (flag != 'a') {
		printf(OUT_NO_AIRPORT_ID, airportID);
	}
	return 0;
}

