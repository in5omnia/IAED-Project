/*
* File: flight.c
* Author: Beatriz Gavilan - 102463
* Description:
*/


#include "BG_102463.h"


/*	includes global variable */
extern int g_TotalOfFlights;


Flight createFlight(FlightID flightID, char departureAirportID[MAX_AIRPORT_ID],
					char arrivalAirportID[MAX_AIRPORT_ID],
					DateTime departureDateTime, DateTime arrivalDateTime,
					Time duration, int capacity) {

	Flight newFlight;

	newFlight.ID = flightID;
	strcpy(newFlight.departureAirport, departureAirportID);
	strcpy(newFlight.arrivalAirport, arrivalAirportID);

	newFlight.departureDateTime = departureDateTime;
	newFlight.arrivalDateTime = arrivalDateTime;

	newFlight.duration = duration;
	newFlight.capacity = capacity;

	return newFlight;
}


int validFlightID(FlightID flightID){
	int i;

	for (i=0; flightID.letters[i] != '\0' && i < MAX_FLIGHT_ID_STR; i++) {

		if (flightID.letters[i] < 'A' || flightID.letters[i] > 'Z') {

			printf(INVALID_FLIGHT_ID);
			return 0;
		}
	}
	return (flightID.num > 0 && flightID.num <= 9999);
}

int validCapacity(int capacity){

	if (capacity < 10 || capacity > 100) {

		printf(INVALID_CAPACITY);
		return 0;
	}
	return 1;
}


int notDuplicateFlight(FlightID flightID, Date departureDate,
					   Flight flightBank[MAX_FLIGHTS]) {
	int i;

	for (i=0; i < g_TotalOfFlights; i++) {

		if (flightID.num == flightBank[i].ID.num &&
			!strcmp(flightID.letters, flightBank[i].ID.letters)
			&& sameDate(departureDate,
						flightBank[i].departureDateTime.date))
										/* same code for same day*/
		{
			printf(DUPLICATE_FLIGHT);
			return 0;
		}
	}
	return 1;
}


int tooManyFlights(){

	int num_flights = g_TotalOfFlights;

	if (num_flights++ > MAX_FLIGHTS) {
		printf(TOO_MANY_FLIGHTS);
		return 1;
	}
	return 0;
}


/*	creates and adds new flight */
void addFlight(Date departure_date, Time departureTime, Time duration,
			   int capacity, FlightID flightID,
			   char depAirportID[MAX_AIRPORT_ID],
			   char arrAirportID[MAX_AIRPORT_ID],
			   Flight flightBank[MAX_FLIGHTS]){

	DateTime departureDateTime;
	DateTime arrivalDateTime;
	Flight newFlight;

	departureDateTime = createDateTime(departure_date,departureTime);
	arrivalDateTime = sumDuration(departureDateTime, duration);

	newFlight = createFlight(flightID,depAirportID, arrAirportID,
							 departureDateTime, arrivalDateTime, duration,
							 capacity);

	/* adds new flight to flightBank*/
	flightBank[g_TotalOfFlights] = newFlight;

	g_TotalOfFlights++;

}


/*	function that checks if the airport exists and if so, finds them in
 * flightBank, sorts and presents them in standard output	*/
void findFlights(char airportID[MAX_AIRPORT_ID], Flight flightBank[MAX_FLIGHTS],
				 Airport airportBank[MAX_AIRPORTS], char flag){

	Flight wantedFlights[MAX_FLIGHTS];
	int i, number_flights, num_flights_found =0;
	int airportIndexPlus1 = airportExist(airportID, airportBank, CASE_V);

	if (!airportIndexPlus1) 	/*	if airport doesn't exist	*/
		return;


	if (CASE_P)		/*	gets airport's number of departure flights */
		number_flights = airportBank[airportIndexPlus1-1].n_Departure_Flights;

	else 	/* (case C)  gets airport's number of arrival flights */
		number_flights = airportBank[airportIndexPlus1-1].n_Arrival_Flights;


	for (i=0; i < g_TotalOfFlights; i++) {

		if (num_flights_found == number_flights)	/* all flights were found*/
			break;

		if ((CASE_P && !strcmp(flightBank[i].departureAirport, airportID))
			|| (CASE_C && !strcmp(flightBank[i].arrivalAirport, airportID))){

			/*	adds flight to wantedFlights	*/
			wantedFlights[num_flights_found] = flightBank[i];
			num_flights_found++;
		}
	}
	sortFlights(wantedFlights, 0, num_flights_found -1, flag);
	outputFlights_P_C(wantedFlights, num_flights_found, flag);
}


void sortFlights( Flight desiredFlights[MAX_FLIGHTS], int left, int right,
				 char flag) {
	int i,j;
	Flight v;

	for (i = left+1; i <= right; i++) {

		v = desiredFlights[i];
		j = i-1;

		if (CASE_P) {
			while ( j >= left && pastDateTime( v.departureDateTime,
									 desiredFlights[j].departureDateTime))
			{
				desiredFlights[j + 1] = desiredFlights[j];
				j--;
			}
		}
		else {	/*	flag == 'c'	*/
			while ( j >= left && pastDateTime(v.arrivalDateTime,
										 desiredFlights[j].arrivalDateTime))
			{
				desiredFlights[j + 1] = desiredFlights[j];
				j--;
			}
		}
		desiredFlights[j+1] = v;
	}
}


void listAllFlights(Flight flightBank[MAX_FLIGHTS]) {
	int i;
	Date f_date;
	Time f_time;
	Flight f;

	for (i=0; i < g_TotalOfFlights; i++) {

		f = flightBank[i];
		f_date = f.departureDateTime.date;
		f_time = f.departureDateTime.time;

		printf(OUT_FLIGHT, f.ID.letters, f.ID.num, f.departureAirport,
			   f.arrivalAirport, f_date.day, f_date.month, f_date.year,
			   f_time.hour, f_time.min);
	}
}


void outputFlights_P_C(Flight wantedFlights[MAX_FLIGHTS], int num_flights,
				   char flag){
	int i=0;
	Date f_date;
	Time f_time;
	Flight f;
	char airportInOutput[MAX_AIRPORT_ID];

	if (CASE_P){
		for (i=0; i < num_flights; i++) {

			f = wantedFlights[i];
			f_date = f.departureDateTime.date;
			f_time = f.departureDateTime.time;
			strcpy(airportInOutput, f.arrivalAirport);

			printf(OUT_P_C_FLIGHT, OUT_P_C_FLIGHT_VARIABLES);
		}
	}
	else {	/*	flag == 'c'*/
		for (i=0; i < num_flights; i++) {

			f = wantedFlights[i];
			f_date = f.arrivalDateTime.date;
			f_time = f.arrivalDateTime.time;
			strcpy(airportInOutput, f.departureAirport);

			printf(OUT_P_C_FLIGHT, OUT_P_C_FLIGHT_VARIABLES);
		}
	}
}


