/*
	Created by Beatriz Gavilan on 26/03/2022.
*/

#ifndef IAED_PROJECT1_PROJ1_H

#define MAX_CITY 51
#define MAX_COUNTRY 31
#define MAX_AIRPORT_ID 4
#define MAX_AIRPORTS 40
#define MAX_FLIGHTS 30000
#define MAX_FLIGHT_ID_STR 3

#define END_PROGRAM 'q'

#define OUT_AIRPORT_ID "airport %s\n"
#define OUT_AIRPORT "%s %s %s %d\n"
#define OUT_FLIGHT "%s%d %s %s %02d-%02d-%d %02d:%02d\n"
#define OUT_P_C_FLIGHT "%s%d %s %02d-%02d-%d %02d:%02d\n"
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
#define OUT_P_C_FLIGHT_VARIABLES f.ID.letters, f.ID.num, airportInOutput,\
f_date.day, f_date.month, f_date.year, f_time.hour, f_time.min

#define CASE_P flag == 'p'
#define CASE_C flag == 'c'



#define less(A, B) (A < B)


#include "airport.h"
#include "date_time.h"
#include "flight.h"




#endif	/* IAED_PROJECT1_PROJ1_H*/
