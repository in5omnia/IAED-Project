/*
 * File: BG_102463.h
 * Author: Beatriz Gavilan - 102463
 * Description: header file with definitions and prototypes useful to the
 * 				project functions
*/


#ifndef BG_102463_H
#define BG_102463_H


#include <stdio.h>
#include <string.h>


#define MAX_CITY 51
#define MAX_COUNTRY 31
#define MAX_AIRPORT_ID 4
#define MAX_AIRPORTS 40
#define MAX_FLIGHTS 30000
#define MAX_FLIGHT_ID_STR 3

#define END_PROGRAM 'q'

#define CASE_P flag == 'p'
#define CASE_C flag == 'c'
#define CASE_A (flag == 'a')
#define CASE_V 'v'

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
#define FIRST_TODAY {1,1,2022}

#define IN_DATE "%d-%d-%d"
#define IN_TIME "%d:%d"

#define OUT_P_C_FLIGHT_VARIABLES f.ID.letters, f.ID.num, airportInOutput,\
f_date.day, f_date.month, f_date.year, f_time.hour, f_time.min





#define less(A, B) (A < B)



typedef struct {
	char ID[MAX_AIRPORT_ID];
	char country[MAX_COUNTRY];
	char city[MAX_CITY];
	int n_Departure_Flights;
	int n_Arrival_Flights;
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


typedef struct {
	Date date;
	Time time;
} DateTime;



typedef struct {

	char letters[MAX_FLIGHT_ID_STR];
	int num;

} FlightID;


typedef struct {

	FlightID ID;
	char departureAirport[MAX_AIRPORT_ID];
	char arrivalAirport[MAX_AIRPORT_ID];
	DateTime departureDateTime;
	DateTime arrivalDateTime;
	Time duration;
	int capacity;

} Flight;


/*	flight.c functions	*/

Flight createFlight(FlightID flightID, char departureAirportID[MAX_AIRPORT_ID],
					char arrivalAirportID[MAX_AIRPORT_ID],
					DateTime departureDateTime, DateTime arrivalDateTime,
					Time duration, int capacity);

int validFlightID(FlightID flightID);

int validCapacity(int capacity);

int notDuplicateFlight(FlightID flightID, Date departureDate,
					   Flight flightBank[MAX_FLIGHTS]);

int tooManyFlights();

void addFlight(Date departure_date, Time departureTime, Time duration,
				  int capacity, FlightID flightID,
				  char depAirportID[MAX_AIRPORT_ID],
				  char arrAirportID[MAX_AIRPORT_ID],
				  Flight flightBank[MAX_FLIGHTS]);

void findFlights(char airportID[MAX_AIRPORT_ID], Flight flightBank[MAX_FLIGHTS],
				Airport airportBank[MAX_AIRPORTS], char flag);

void sortFlights( Flight desiredFlights[MAX_FLIGHTS], int left, int right,
				 char flag);

void listAllFlights(Flight flightBank[MAX_FLIGHTS]);

void outputFlights_P_C(Flight wantedFlights[MAX_FLIGHTS], int num_flights,
					   char flag);


/*	date_time.c functions	*/

Date createDate(int day, int month, int year);

DateTime createDateTime(Date date, Time time);

Date newDate(Date possibleDate, Date today);

DateTime sumDuration(DateTime departure, Time duration);

int pastDate(int day, int month, int year, Date today);

int afterOneYear(int day, int month, int year, Date today);

void outputDate(Date date);

int check_date(Date date, Date today);

int validDuration(Time duration);

int sameDate(Date date1, Date date2);

int beforeTime(Time time1, Time time2);

int beforeDateTime(DateTime dateTime1, DateTime dateTime2);

/*	airport.c functions	*/

Airport createAirport(char airportID[MAX_AIRPORT_ID],
					  char country[MAX_COUNTRY], char city[MAX_CITY]);

void addAirport(Airport new_airport, Airport airportBank[MAX_AIRPORTS]);

int validAirportID(char airportID[MAX_AIRPORT_ID]);

int airportExist(char airportID[MAX_AIRPORT_ID],
				 Airport airportBank[MAX_AIRPORTS], char flag);

int beforeLetters(char beforeWord[MAX_AIRPORT_ID],
				  char afterWord[MAX_AIRPORT_ID]);

void exch(Airport airportBank[MAX_AIRPORTS], int i, int right, char flag);

int partition(Airport airportBank[MAX_AIRPORTS], int left, int right,
			  char flag);

void sortAirports(Airport airportBank[MAX_AIRPORTS], int left, int right,
				  char flag);

void listAirports(Airport airportBank[MAX_AIRPORTS], int num);

int findAirports(int num_IDs, int existingID[MAX_AIRPORTS],
				 Airport airportBank[MAX_AIRPORTS],
				 Airport requestedAirports[MAX_AIRPORTS],
				 char requested_IDs[MAX_AIRPORTS][MAX_AIRPORT_ID]);

void listRequestedAirports(Airport airportBank[MAX_AIRPORTS],
						   char requested_IDs[MAX_AIRPORTS][MAX_AIRPORT_ID],
						   int num_IDs);


/*	main file functions	*/

Date readCommand(char cmd, Airport airportBank[MAX_AIRPORTS],
				 Flight flightBank[MAX_FLIGHTS], Date today);

/*	aux file functions	*/

int validate_case_a(char airportID[], Airport airportBank[MAX_AIRPORTS]);

int valid_case_v(FlightID flightID, char arrivalAirportID[MAX_AIRPORT_ID],
				 char departureAirportID[MAX_AIRPORT_ID], Date departureDate,
				 Time duration, int capacity, Airport airportBank[MAX_AIRPORTS],
				 Flight flightBank[MAX_FLIGHTS], Date today);


void commandA(Airport airportBank[MAX_AIRPORTS]);

void commandL(Airport airportBank[MAX_AIRPORTS]);

void commandV(Airport airportBank[MAX_AIRPORTS], Flight flightBank[MAX_FLIGHTS],
			  Date today);

void command_P_C(char flag, Airport airportBank[MAX_AIRPORTS],
				 Flight flightBank[MAX_FLIGHTS]);

Date command_T(Date today);



#endif
