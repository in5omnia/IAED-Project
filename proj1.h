//
// Created by Beatriz Gavilan on 26/03/2022.
//

#ifndef IAED_PROJECT1_PROJ1_H

#define MAX_CITY 51
#define MAX_COUNTRY 31
#define MAX_AIRPORT_ID 4
#define MAX_AIRPORTS 40
#define MAX_FLIGHTS 30000

#define OUT_AIRPORT_ID "airport %s"
#define OUT_AIRPORT "%s %s %s %d"

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
	char ID[MAX_AIRPORT_ID];
	char country[MAX_COUNTRY];
	char city[MAX_CITY];
	int n_flights;
} Airport;







#endif	// IAED_PROJECT1_PROJ1_H
