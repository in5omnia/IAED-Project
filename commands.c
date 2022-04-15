/*
* File: commands.c
* Author: Beatriz Gavilan - 102463
* Description: file with functions that execute or validate commands.
*/

#include "BG_102463.h"


/*	Includes global variables */
extern int g_TotalOfAirports;
extern int g_TotalOfFlights;


/*	Checks validity for "case a" : returns 1 if the airportID is valid and if
 * the limit of airports won't be exceeded when adding one */
int validate_case_a(char airportID[], Airport airportBank[MAX_AIRPORTS]){
	int num_airports = g_TotalOfAirports;
	if (!validAirportID(airportID))
		return 0;

	if ((++num_airports) > MAX_AIRPORTS) {
		printf(TOO_MANY_AIRPORTS);
		return 0;
	}
	return (!airportExist(airportID, airportBank, 'a'));
}


/*	Checks validity for case v: checks if flightID and its airports' IDs
 * are valid; if the flight is duplicate and if the airports exist;
 * if adding a flight will exceed the limit of flights; if the flight date,
 * duration and capacity are valid	*/

int valid_case_v(FlightID flightID, char arrivalAirportID[MAX_AIRPORT_ID],
				 char departureAirportID[MAX_AIRPORT_ID], Date departureDate,
				 Time duration, int capacity, Airport airportBank[MAX_AIRPORTS],
				 Flight flightBank[MAX_FLIGHTS], Date today) {

	int departureIndexPlus1, arrivalIndexPlus1;

	if (validFlightID(flightID) &&
		!duplicateFlight(flightID, departureDate, flightBank, 'v') &&
		validAirportID(departureAirportID) &&
		validAirportID(arrivalAirportID)) {

		/* airportExist returns 0 or (airport index in airportBank + 1)
		 * if it exists*/
		departureIndexPlus1 = airportExist(departureAirportID,
										   airportBank, CASE_V);

		arrivalIndexPlus1 = airportExist(arrivalAirportID,
										 airportBank, CASE_V);

		if (!(!departureIndexPlus1 || !arrivalIndexPlus1) &&
			!tooManyFlights() &&
			check_date(departureDate, today) &&
			validDuration(duration) && validCapacity(capacity))
		{
			airportBank[departureIndexPlus1-1].n_Departure_Flights++;
			airportBank[arrivalIndexPlus1-1].n_Arrival_Flights++;
			return 1;
		}
	}
	return 0;
}


/*	Receives input for command "a" and, if it's valid, creates and adds a
 * new airport, presenting the corresponding message in standard output.	*/
void commandA(Airport airportBank[MAX_AIRPORTS]){

	char airportID[MAX_AIRPORT_ID], country[MAX_COUNTRY], city[MAX_CITY];
	scanf(IN_AIRPORT_ID_OR_COUNTRY, airportID);
	scanf(IN_AIRPORT_ID_OR_COUNTRY, country);
	scanf(IN_CITY, city);

	if (validate_case_a(airportID, airportBank)) {

		Airport new_airport = createAirport(airportID, country, city);
		addAirport(new_airport, airportBank);

		printf(OUT_AIRPORT_ID, airportID);
		/*	increases global variable (total of airports in the system)	*/
		g_TotalOfAirports++;

	}
}


/*	Receives remaining input for command "l" and: if there isn't any, presents
 * sorted airports; if there is, stores the airports asked for and presents the
 * valid ones */
void commandL(Airport airportBank[MAX_AIRPORTS]){
	char airportID[MAX_AIRPORT_ID];
	if (getchar() == '\n') {
		sortAirports(airportBank, 0, g_TotalOfAirports - 1);
		listAirports(airportBank, 0);
	}
	else {
		char requested_IDs[MAX_AIRPORTS][MAX_AIRPORT_ID];
		int num_IDs = 0;
		do {
			scanf(IN_AIRPORT_ID_OR_COUNTRY, airportID);
			strcpy(requested_IDs[num_IDs], airportID);
			num_IDs++;

		} while (getchar() != '\n');

		listRequestedAirports(airportBank, requested_IDs, num_IDs);
	}
}


/*	Receives remaining input for command "v" and: if there isn't any, presents
* all flights; if there is, checks if it's valid and, if so, adds new flight to
 * FlightBank	*/
void commandV(Airport airportBank[MAX_AIRPORTS], Flight flightBank[MAX_FLIGHTS],
			  Date today){

	if (getchar() == '\n') {
		listAllFlights(flightBank);

	} else {

		int capacity;
		char depAirportID[MAX_AIRPORT_ID], arrAirportID[MAX_AIRPORT_ID];
		FlightID flightID;
		Date departure_date;
		Time duration, departureTime;

		scanf(IN_FLIGHT_ID, flightID.letters, &flightID.num);
		scanf(IN_AIRPORT_ID_OR_COUNTRY, depAirportID);
	  	scanf(IN_AIRPORT_ID_OR_COUNTRY, arrAirportID);

		scanf(IN_DATE, &departure_date.day, &departure_date.month,
			  &departure_date.year);

		scanf(IN_TIME, &departureTime.hour, &departureTime.min);
		scanf(IN_TIME, &duration.hour, &duration.min);
		scanf(IN_CAPACITY, &capacity);

		if (!valid_case_v(flightID, arrAirportID,depAirportID, departure_date,
						  duration, capacity, airportBank, flightBank, today))
			return;

		addFlight(departure_date, departureTime, duration, capacity, flightID,
				  depAirportID, arrAirportID, flightBank);

	}
}


/*	Receives airportID for P and C commands and finds associated flights	*/
void command_P_C(char flag, Airport airportBank[MAX_AIRPORTS],
				 Flight flightBank[MAX_FLIGHTS]){

	char airportID[MAX_AIRPORT_ID];
	scanf(IN_AIRPORT_ID_OR_COUNTRY, airportID);
	findFlights(airportID, flightBank, airportBank, flag);
}


/*	Gets a date from input and if it's valid, updates "today"	*/
Date command_T(Date today){

	int day, month, year;
	Date possibleDate;

	scanf(IN_DATE, &day, &month, &year);
	possibleDate = createDate(day, month, year);

	if (check_date(possibleDate, today))	/*	checks date's validity	*/
	{
		today = newDate(possibleDate, today);
		outputDate(today);
	}
	return today;
}
