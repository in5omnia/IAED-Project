//
// Created by Beatriz Gavilan on 26/03/2022.
//
/*
#include <string.h>
#include <proj1.h>

Airport createAirport(char airportID[MAX_AIRPORT_ID],
					  char country[MAX_COUNTRY], char city[MAX_CITY]){
	Airport airport;
	strcpy(airport.ID, airportID);
	strcpy(airport.country, country);
	strcpy(airport.city, city);
	airport.n_flights = 0;
	return airport;
}

void addAirport(Airport new_airport, Airport airportBank[MAX_AIRPORTS]){ //[[airport, voosPartida, voosChegada], ...]
	airportBank[n_airports] = new_airport;
	return;
}


int validAirportID(*/
/*const *//*
char airportID[]){
	int i;
	for (i=0; airportID[i] != '\0'; i++){
		if (i >= MAX_AIRPORT_ID)	*/
/*	mais de 3 letras *//*

			return 0;
		if (airportID[i] < 'A' || airportID[i] > 'Z')	*/
/* nao sao maiusculas *//*

			return 0;
	}
	if (i < MAX_AIRPORT_ID-1)	*/
/* menos de 3 letras *//*

		return 0;
	return 1;
}


int notDuplicateAirport(char airportID[], Airport airportBank[MAX_AIRPORTS]){
	for (int i=0; i < n_airports; i++){
		if (!strcmp(airportID, airportBank[i].ID))
			return 0;
	}
	return 1;
}
*/
