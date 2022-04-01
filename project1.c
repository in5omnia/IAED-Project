/*
 * Author: Beatriz Gavilan -102463
 * */

#include <stdio.h>
#include <string.h>
#include "proj1.h"



int n_airports = 0;
int n_flights = 0;



int beforeLetters(char beforeWord[MAX_AIRPORT_ID],
				  char afterWord[MAX_AIRPORT_ID]) {

	return (less(beforeWord[0], afterWord[0]) ||
		((beforeWord[0] == afterWord[0]) && less(beforeWord[1], afterWord[1]))
		|| ((beforeWord[0] == afterWord[0]) && (beforeWord[1] == afterWord[1])
		&& less(beforeWord[2], afterWord[2])));
}


void exch(Airport airportBank[MAX_AIRPORTS]/*, Flight desiredFlights[MAX_FLIGHTS]*/, int i, int right, char flag){
	if (flag == 'l') {
		Airport t = airportBank[i];
		airportBank[i] = airportBank[right];
		airportBank[right] = t;
	}
	return;

}

int partition(Airport airportBank[MAX_AIRPORTS], int left, int right, char flag)
{
	int i = left-1;
	int j = right;
	if (flag == 'l') {
		char v[MAX_AIRPORT_ID];
		strcpy(v, airportBank[right].ID);
		while (i < j) {
			while (beforeLetters(airportBank[++i].ID, v));

			while (beforeLetters(v, airportBank[--j].ID)){
				if (j == left)
					break;
			}
			if (i < j)
				exch(airportBank, i, j, 'l');
		}
		exch(airportBank, i, right, 'l');
	}
	return i;
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
											 desiredFlights[j].departureDateTime)) {
				desiredFlights[j + 1] = desiredFlights[j];
				j--;
			}
		}
		else {	/*	flag == 'c'	*/
			while ( j >= left && pastDateTime(v.arrivalDateTime,
											 desiredFlights[j].arrivalDateTime)) {
				desiredFlights[j + 1] = desiredFlights[j];
				j--;
			}
		}
		desiredFlights[j+1] = v;
	}
	return;
}


void sortAirports(Airport airportBank[MAX_AIRPORTS]/*, Flight desiredFlights[MAX_FLIGHTS]*/,
			   int left, int right, char flag)
{
	int i;
	if (right <= left)
		return;
	i = partition(airportBank, /*desiredFlights,*/ left, right, flag);
	sortAirports(airportBank, /*desiredFlights,*/ left, i - 1, flag);
	sortAirports(airportBank, /*desiredFlights,*/ i + 1, right, flag);
}



int validate_case_a(char airportID[], Airport airportBank[MAX_AIRPORTS]){
	int num_airports = n_airports;
	if (!validAirportID(airportID))
		return 0;

	if ((++num_airports) > MAX_AIRPORTS) {
		printf(TOO_MANY_AIRPORTS);
		return 0;
	}
	return (!airportExist(airportID, airportBank, 'a'));
}


/* 	l	 */
void listAirports(Airport airportBank[MAX_AIRPORTS], int num){
	int i;
	if (!num) {
		num = n_airports;
	}
	for (i=0; i < num; i++)
		printf(OUT_AIRPORT, airportBank[i].ID, airportBank[i].city,
			   airportBank[i].country, airportBank[i].n_Departure_Flights);
	return;
}


void outputFlights(Flight desiredFlights[MAX_FLIGHTS], int n_wanted_flights,
				   char flag){
	int i=0;
	Date f_date;
	Time f_time;
	Flight f;
	char airportInOutput[MAX_AIRPORT_ID];
	if (CASE_P){
		for (i=0; i < n_wanted_flights; i++) {
			f = desiredFlights[i];
			f_date = f.departureDateTime.date;
			f_time = f.departureDateTime.time;
			strcpy(airportInOutput, f.arrivalAirport);
			printf(OUT_P_C_FLIGHT, OUT_P_C_FLIGHT_VARIABLES);
		}
	} else {	/*	flag == 'c'*/
		for (i=0; i < n_wanted_flights; i++) {
			f = desiredFlights[i];
			f_date = f.arrivalDateTime.date;
			f_time = f.arrivalDateTime.time;
			strcpy(airportInOutput, f.departureAirport);
			printf(OUT_P_C_FLIGHT, OUT_P_C_FLIGHT_VARIABLES);
		}
	}
	return;
}


void listFlights(Flight flightBank[MAX_FLIGHTS]) {
	int i;
	Date f_date;
	Time f_time;
	Flight f;
	for (i=0; i < n_flights; i++) {
		f = flightBank[i];
		f_date = f.departureDateTime.date;
		f_time = f.departureDateTime.time;
		printf(OUT_FLIGHT, f.ID.letters, f.ID.num, f.departureAirport,
			   f.arrivalAirport, f_date.day, f_date.month, f_date.year,
			   f_time.hour, f_time.min);
	}
	return;
}


void listRequestedAirports(Airport airportBank[MAX_AIRPORTS],
			   char requested_IDs[MAX_AIRPORTS][MAX_AIRPORT_ID], int num_IDs){
	int i, e, a, c, n=0, initialized = 0, existingID[MAX_AIRPORTS];
	Airport requestedAirports[MAX_AIRPORTS];

	for (c=0; c < num_IDs; c++){
		existingID[c] = 0;
	}
	for (i=0; i < n_airports; i++){
		if (n == num_IDs)		/*	we have all the requested flights */
			break;
		for (e=0; e < num_IDs; e++){
			if (!initialized) {	 /* initializes vector that checks IDs with 0 */
				existingID[e] = 0;
			}
			if (!strcmp(airportBank[i].ID, requested_IDs[e])){
				requestedAirports[e] = airportBank[i];
				n++;
				existingID[e] = 1;
				break;
			}
		}
		initialized = 1;
	}

	if (n != num_IDs){	/* only checks existence if not all were found */
		for (a=0; a < num_IDs; a++){	/* validates ID's existence */
			if (!existingID[a]){
				printf(OUT_NO_AIRPORT_ID, requested_IDs[a]);
			}
			else{
				printf(OUT_AIRPORT, requestedAirports[a].ID,
					   requestedAirports[a].city,
					   requestedAirports[a].country,
					   requestedAirports[a].n_Departure_Flights);
			}
		}
	}
	else {
		listAirports(requestedAirports, num_IDs);
	}
	return;
}



int valid_case_v(FlightID flightID, char arrivalAirportID[MAX_AIRPORT_ID],
				 char departureAirportID[MAX_AIRPORT_ID], Date departureDate,
				 Time duration, int capacity, Airport airportBank[MAX_AIRPORTS],
				 Flight flightBank[MAX_FLIGHTS], Date today) {

	int departureIndexPlus1, arrivalIndexPlus1;	/* indice + 1 */
	if (validFlightID(flightID) &&
		 notDuplicateFlight(flightID, departureDate, flightBank) &&
		 validAirportID(departureAirportID) &&
		 validAirportID(arrivalAirportID)) {
			 departureIndexPlus1 = airportExist(departureAirportID,
									  airportBank, 'v');
			 arrivalIndexPlus1 = airportExist(arrivalAirportID,
									 airportBank, 'v');
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


void case_p_c(char airportID[MAX_AIRPORT_ID], Flight flightBank[MAX_FLIGHTS],
			  Airport airportBank[MAX_AIRPORTS], char flag){

	int i, number_flights, n_wanted_flights=0;
	int airportIndexPlus1 = airportExist(airportID, airportBank, 'v');
	Flight desiredFlights[MAX_FLIGHTS];

	if (!airportIndexPlus1) 		/*	if airport doesnt exist	*/
		return;

	if (CASE_P)
		number_flights = airportBank[airportIndexPlus1-1].n_Departure_Flights;
	else 	/* when flag == 'c' */
		number_flights = airportBank[airportIndexPlus1-1].n_Arrival_Flights;

	for (i=0; i < n_flights; i++) {

		if (n_wanted_flights==number_flights)
			break;

		if ((CASE_P && !strcmp(flightBank[i].departureAirport, airportID))
			|| (CASE_C && !strcmp(flightBank[i].arrivalAirport, airportID)))
		{
			desiredFlights[n_wanted_flights] = flightBank[i];
			n_wanted_flights++;
		}
	}
	sortFlights( desiredFlights, 0, n_wanted_flights-1, flag);
	outputFlights(desiredFlights, n_wanted_flights, flag);
	return;
}


void commandA(Airport airportBank[MAX_AIRPORTS]){
	char airportID[MAX_AIRPORT_ID], country[MAX_COUNTRY], city[MAX_CITY];
	scanf(" %s %s ", airportID, country);
	scanf("%[^\n]", city);
	if (validate_case_a(airportID, airportBank)) {

		Airport new_airport = createAirport(airportID, country, city);
		addAirport(new_airport, airportBank);
		printf(OUT_AIRPORT_ID, airportID);
		n_airports++;

	}
	return;
}


void commandL(Airport airportBank[MAX_AIRPORTS]){
	char airportID[MAX_AIRPORT_ID];
	if (getchar() == '\n') {
		sortAirports(airportBank, 0, n_airports - 1,'l');
		listAirports(airportBank, 0);
	}
	else {
		char requested_IDs[MAX_AIRPORTS][MAX_AIRPORT_ID];
		int num_IDs = 0;
		do {
			scanf("%s", airportID);
			strcpy(requested_IDs[num_IDs], airportID);
			num_IDs++;

		} while (getchar() != '\n');

		listRequestedAirports(airportBank, requested_IDs, num_IDs);
	}
	return;
}

void commandV(Airport airportBank[MAX_AIRPORTS], Flight flightBank[MAX_FLIGHTS],
	Date today){
	if (getchar() == '\n') {
		listFlights(flightBank);

	} else {
		int capacity;
		char depAirportID[MAX_AIRPORT_ID], arrAirportID[MAX_AIRPORT_ID];
		FlightID flightID;
		Date departureDate;
		Time duration, departureTime;
		Flight newFlight;
		dateTime departureDateTime, arrivalDateTime;

		scanf("%02s%d", flightID.letters, &flightID.num);

		scanf(" %s %s", depAirportID, arrAirportID);
		scanf(" %d-%d-%d", &departureDate.day, &departureDate.month,
			  &departureDate.year);
		scanf(" %d:%d", &departureTime.hour, &departureTime.min);
		scanf(" %d:%d %d", &duration.hour, &duration.min, &capacity);


		if (!valid_case_v(flightID, arrAirportID,
						  depAirportID, departureDate,
						  duration, capacity,
						  airportBank, flightBank, today)){
			return;
		}

		departureDateTime = createDateTime(departureDate,
										   departureTime);
		arrivalDateTime = sumDuration(departureDateTime, duration);
		newFlight = createFlight(flightID,
								 depAirportID, arrAirportID,
								 departureDateTime, arrivalDateTime,
								 duration, capacity);

		addFlight(flightBank, newFlight);
		n_flights++;

	}
	return;
}


void command_P_C(char flag, Airport airportBank[MAX_AIRPORTS],
				 Flight flightBank[MAX_FLIGHTS]){

	char airportID[MAX_AIRPORT_ID];
	scanf(" %s", airportID);
	case_p_c(airportID, flightBank, airportBank, flag);
	return;
}


Date command_T(Date today){

	int day, month, year;
	Date possibleDate;

	scanf("%d-%d-%d", &day, &month, &year);
	possibleDate = createDate(day, month, year);

	if (check_date(possibleDate, today))
	{
		today = newDate(possibleDate, today);
		outputDate(today);
	}
	return today;
}


Date readCommand(char cmd, Airport airportBank[MAX_AIRPORTS],
				 				Flight flightBank[MAX_FLIGHTS], Date today) {

	switch (cmd) {
		case 'a':
			commandA(airportBank);
			break;

		case 'l':
			commandL(airportBank);
			break;

		case 'v':
			commandV(airportBank, flightBank, today);
			break;

		case 'p':
			command_P_C('p', airportBank, flightBank);
			break;

		case 'c':
			command_P_C('c', airportBank, flightBank);
			break;

		case 't':
			today = command_T(today);
			break;
	}
	return today;
}


int main() {
	Airport airportBank[MAX_AIRPORTS] = {0};
	Flight flightBank[MAX_FLIGHTS] = {0};
	Date today = {1,1,2022};
	char cmd;
	while ((cmd = getchar()) != EOF && cmd != END_PROGRAM){
		today = readCommand(cmd, airportBank, flightBank, today);
	}
	return 0;
}



