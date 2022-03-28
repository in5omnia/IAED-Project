/*
	Created by Beatriz Gavilan on 26/03/2022.
*/

#ifndef IAED_PROJECT1_PROJ1_H

#define MAX_CITY 51
#define MAX_COUNTRY 31
#define MAX_AIRPORT_ID 4
#define MAX_AIRPORTS 40
#define MAX_FLIGHTS 30000
#define MAX_LETTERS_FLIGHT_ID 3

#define OUT_AIRPORT_ID "airport %s\n"
#define OUT_AIRPORT "%s %s %s %d\n"
#define OUT_FLIGHT "%s%d %s %s %02d-%02d-%d %02d:%02d\n"
#define OUT_NO_AIRPORT_ID "%s: no such airport ID\n"
#define DUPLICATE_AIRPORT "duplicate airport\n"
#define INVALID_AIRPORT_ID "invalid airport ID\n"
#define TOO_MANY_AIRPORTS "too many airports\n"
#define INVALID_DURATION "invalid duration\n"
#define INVALID_CAPACITY "invalid capacity\n"
#define TOO_MANY_FLIGHTS "too many flights\n"
#define DUPLICATE_FLIGHT "flight already exists\n"
#define INVALID_DATE "invalid date\n"
#define INVALID_FLIGHT_ID "invalid flight code\n"

#define END_PROGRAM 'q'


typedef struct {
	int day;
	int month;
	int year;
} Date;


typedef struct {
	int hour;
	int min;
} Time;


typedef struct {
	Date date;
	Time time;
} dateTime;


typedef struct {
	char letters[MAX_LETTERS_FLIGHT_ID];
	int num;
} FlightID;


typedef struct {
	FlightID ID;
	char departureAirport[MAX_AIRPORT_ID];
	char arrivalAirport[MAX_AIRPORT_ID];
	dateTime departureDateTime;
	Time duration;
	int capacity;
} Flight;




Flight createFlight(FlightID flightID, char departureAirportID[MAX_AIRPORT_ID],
				 char arrivalAirportID[MAX_AIRPORT_ID], dateTime departureDateTime,
				 Time duration, int capacity) {
	Flight newFlight;
	newFlight.ID = flightID;
	strcpy(newFlight.departureAirport, departureAirportID);
	strcpy(newFlight.arrivalAirport, arrivalAirportID);
	newFlight.departureDateTime = departureDateTime;
	newFlight.duration = duration;
	newFlight.capacity = capacity;
	return newFlight;
}



#include "airport.h"





#endif	/* IAED_PROJECT1_PROJ1_H*/
