/*
 Created by Beatriz Gavilan on 27/03/2022.
*/

#ifndef IAEDPROJ1_AIRPORT_H


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flight.h"

extern int n_airports;

typedef struct {
	char ID[MAX_AIRPORT_ID];
	char country[MAX_COUNTRY];
	char city[MAX_CITY];
	int n_Departure_Flights;
	int n_Arrival_Flights;
/*	Flight departureFlights[MAX_FLIGHTS];
	Flight arrivalFlights[MAX_FLIGHTS];*/
} Airport;


Airport createAirport(char airportID[MAX_AIRPORT_ID],
					  char country[MAX_COUNTRY], char city[MAX_CITY]){
	Airport airport;
	/*int i;*/
	strcpy(airport.ID, airportID);
	strcpy(airport.country, country);
	strcpy(airport.city, city);
	airport.n_Departure_Flights = 0;
/*	airport.n_Arrival_Flights = 0;*/
/*

	for (i=0; i < MAX_FLIGHTS; i++) {

		airport.departureFlights[i] = createFlight(
			createFlightID("$$", 0), airportID, "$$$",
			createDateTime(createDate(0,0,0), createTime(0,0)),
			createTime(0,0), 0);

		airport.arrivalFlights[i] = createFlight(
			createFlightID("$$", 0), "$$$", airportID,
			createDateTime(createDate(0,0,0), createTime(0,0)),
			createTime(0,0), 0);
	}
*/

	return airport;
}


void addAirport(Airport new_airport, Airport airportBank[MAX_AIRPORTS]){/*[[airport, voosPartida, voosChegada], ...]*/
	airportBank[n_airports] = new_airport;
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


int airportExist(char airportID[], Airport airportBank[MAX_AIRPORTS], char flag){
	int i;
	for (i=0; i < n_airports; i++){
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


/*
int airportExists(char airportID[], Airport airportBank[MAX_AIRPORTS], char flag){
	int i;
	for (i=0; i < n_airports; i++){
		if (!strcmp(airportID, airportBank[i].ID)) {
			if (flag == 'a') {
				printf(DUPLICATE_AIRPORT);
			}
			return ++i;
		}
	}
	if (flag == 'v') {
		printf(OUT_NO_AIRPORT_ID, airportID);
	}
	return 0;
}
*/



/*

int airportIDs_exist(char arrivalAirportID[MAX_AIRPORT_ID],
					 char departureAirportID[MAX_AIRPORT_ID], Airport airportBank[MAX_AIRPORTS])
{
	int i, exists=1, Arr_flag=0, Dep_flag=0;
	for (i=0; i < n_airports; i++) {
		if (!strcmp(arrivalAirportID, airportBank[i].ID))
			Arr_flag++;

		if (!strcmp(departureAirportID, airportBank[i].ID))
			Dep_flag++;
	}
	if (!Dep_flag) {
		printf(OUT_NO_AIRPORT_ID, departureAirportID);
		exists = 0;
	}
	if (!Arr_flag){
		printf(OUT_NO_AIRPORT_ID, arrivalAirportID);
		exists = 0;
	}
	return exists;
}
*/


#endif	/* IAEDPROJ1_AIRPORT_H */
