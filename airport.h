/*
 Created by Beatriz Gavilan on 27/03/2022.
*/

#ifndef IAEDPROJ1_AIRPORT_H
/*#define IAEDPROJ1_AIRPORT_H*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int extern n_airports;

typedef struct {
	char ID[MAX_AIRPORT_ID];
	char country[MAX_COUNTRY];
	char city[MAX_CITY];
	int n_flights;
} Airport;


Airport createAirport(char airportID[MAX_AIRPORT_ID],
					  char country[MAX_COUNTRY], char city[MAX_CITY]){
	Airport airport;
	strcpy(airport.ID, airportID);
	strcpy(airport.country, country);
	strcpy(airport.city, city);
	airport.n_flights = 0;
	return airport;
}


void addAirport(Airport new_airport, Airport airportBank[MAX_AIRPORTS]){/*[[airport, voosPartida, voosChegada], ...]*/
	airportBank[n_airports] = new_airport;
	return;
}


int validAirportID(/*const */char airportID[MAX_AIRPORT_ID]){
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
		printf("2yo");
		return 0;
	}
	return 1;
}


int notDuplicateAirport(char airportID[], Airport airportBank[MAX_AIRPORTS]){
	int i;
	for (i=0; i < n_airports; i++){
		if (!strcmp(airportID, airportBank[i].ID)) {
			printf(DUPLICATE_AIRPORT);
			return 0;
		}
	}
	return 1;
}




#endif	/* IAEDPROJ1_AIRPORT_H */