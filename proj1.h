//
// Created by Beatriz Gavilan on 26/03/2022.
//

#ifndef IAED_PROJECT1_PROJ1_H



#define MAX_CITY 51
#define MAX_COUNTRY 31
#define MAX_AIRPORT_ID 4
#define MAX_AIRPORTS 40
#define MAX_FLIGHTS 30000

#define OUT_AIRPORT_ID "airport %s\n"
#define OUT_AIRPORT "%s %s %s %d\n"
#define OUT_NO_AIRPORT_ID "%s: no such airport ID\n"

#define DUPLICATE_AIRPORT "duplicate airport\n"
#define INVALID_AIRPORT_ID "invalid airport ID\n"
#define TOO_MANY_AIRPORTS "too many airports\n"

#define END_PROGRAM 'q'

typedef struct {
	char ID[MAX_AIRPORT_ID];
	char country[MAX_COUNTRY];
	char city[MAX_CITY];
	int n_flights;
} Airport;


typedef struct {
	int day;
	int month;
	int year;
} Date;


typedef struct {
	int hour;
	int min;
} Time;


int validate_case_a(char airportID[], Airport airportBank[MAX_AIRPORTS]);
void listAirports(Airport airportBank[MAX_AIRPORTS], int num);
void listRequestedAirports(Airport airportBank[MAX_AIRPORTS],
			   char requested_IDs[MAX_AIRPORTS][MAX_AIRPORT_ID], int num_IDs);
void readcommand(char cmd, Airport airportBank[MAX_AIRPORTS]);
Airport createAirport(char airportID[MAX_AIRPORT_ID],
					  char country[MAX_COUNTRY], char city[MAX_CITY]);
void addAirport(Airport new_airport, Airport airportBank[MAX_AIRPORTS]);
int validAirportID(/*const */char airportID[]);
int notDuplicateAirport(char airportID[], Airport airportBank[MAX_AIRPORTS]);




#endif	// IAED_PROJECT1_PROJ1_H
