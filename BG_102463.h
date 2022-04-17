/*
 * File: BG_102463.h
 * Author: Beatriz Gavilan - 102463
 * Description: header file with definitions and prototypes useful to the
 * 				project functions
*/


#ifndef BG_102463_H
#define BG_102463_H

#include "reservations.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CITY 51
#define MAX_COUNTRY 31
#define MAX_AIRPORT_ID 4
#define MAX_AIRPORTS 40
#define MAX_FLIGHTS 30000
#define MAX_FLIGHT_ID_STR 3
#define MAX_CMD_R 65518
#define MAX_CMD_E 65535

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


#define VALID_PASSENGER_NUM (passengerNum > 0)
#define FIRST_TODAY {1,1,2022}

#define IN_DATE "%d-%d-%d"
#define IN_TIME "%d:%d"
#define IN_FLIGHT_ID "%02s%d"
#define IN_CAPACITY "%d"
#define IN_AIRPORT_ID_OR_COUNTRY "%s"
#define IN_CITY " %[^\n]"

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
	int numPassengers;
	Reservation * reservationList;
	int numReservations;

} Flight;



/*	flight.c functions	*/

Flight createFlight(FlightID flightID, char departureAirportID[MAX_AIRPORT_ID],
					char arrivalAirportID[MAX_AIRPORT_ID],
					DateTime departureDateTime, DateTime arrivalDateTime,
					Time duration, int capacity);

int validFlightID(FlightID flightID);

int validCapacity(int capacity);

int duplicateFlight(FlightID flightID, Date departureDate,
					char flag);

int tooManyFlights();

void addFlight(Date departure_date, Time departureTime, Time duration,
				  int capacity, FlightID flightID,
				  char depAirportID[MAX_AIRPORT_ID],
				  char arrAirportID[MAX_AIRPORT_ID]);

void findFlights(char airportID[MAX_AIRPORT_ID], char flag);

void sortFlights( Flight desiredFlights[MAX_FLIGHTS], int left, int right,
				 char flag);

void listAllFlights();

void outputFlights_P_C(Flight wantedFlights[MAX_FLIGHTS], int num_flights,
					   char flag);

int deleteFlight(FlightID flightID);

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

void addAirport(Airport new_airport);

int validAirportID(char airportID[MAX_AIRPORT_ID]);

int airportExist(char airportID[MAX_AIRPORT_ID], char flag);

int beforeLetters(char beforeWord[MAX_AIRPORT_ID],
				  char afterWord[MAX_AIRPORT_ID]);

void exch(int i, int right);

int partition(int left, int right);

void sortAirports(int left, int right);

void listAirports(Airport* airportList, int num);

int findAirports(int num_IDs, int existingID[MAX_AIRPORTS],
				 Airport* requestedAirports,
				 char requested_IDs[MAX_AIRPORTS][MAX_AIRPORT_ID]);

void listRequestedAirports(char requested_IDs[MAX_AIRPORTS][MAX_AIRPORT_ID],
						   int num_IDs);


/*	main file functions	*/

Date readCommand(char cmd, Date today);

/*	aux file functions	*/

int validate_case_a(char airportID[]);

int valid_case_v(FlightID flightID, char arrivalAirportID[MAX_AIRPORT_ID],
				 char departureAirportID[MAX_AIRPORT_ID], Date departureDate,
				 Time duration, int capacity, Date today);


void commandA();

void commandL();

void commandV(Date today);

void command_P_C(char flag);

Date command_T(Date today);

void commandR(Date today);

/*void commandE(Flight flightBank[MAX_FLIGHTS]);*/


/*	reservation file functions	*/
int add_Reservation(FlightID flightId,
				Date flightDate, char* reservationCode,
				int passengerNum, Date today);

void listReservations(FlightID flightId,
				 Date flightDate, Date today);


FlightID readFlightID();

/*
int deleteReservation(char* code, Flight* flightBank);*/

#endif
