/*
 Created by Beatriz Gavilan on 29/03/2022.
*/

#ifndef IAEDPROJ1_FLIGHT_H
#define IAEDPROJ1_FLIGHT_H

#include "date_time.h"
extern int n_flights;


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


int validFlightID(FlightID flightID){
	int i;
	for (i=0; flightID.letters[i] != '\0' && i < MAX_LETTERS_FLIGHT_ID; i++) {
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


FlightID createFlightID(char flightID_str[MAX_LETTERS_FLIGHT_ID],
						int flightID_num){
	FlightID flightId;
	flightID_str[MAX_LETTERS_FLIGHT_ID-1] = '\0';
	strcpy(flightId.letters, flightID_str);
	flightId.num = flightID_num;
	return flightId;
}


int notDuplicateFlight(FlightID flightID, Date departureDate,
					   Flight flightBank[MAX_FLIGHTS]) {
	int i;
	for (i=0; i < n_flights; i++) {
		if (flightID.num == flightBank[i].ID.num &&
			!strcmp(flightID.letters, flightBank[i].ID.letters)
			&& sameDate(departureDate,
						flightBank[i].departureDateTime.date)) /* same code for same day*/
		{
			printf(DUPLICATE_FLIGHT);
			return 0;
		}
	}
	return 1;
}

int tooManyFlights(){
	int num_flights = n_flights;
	if (num_flights++ > MAX_FLIGHTS) {
		printf(TOO_MANY_FLIGHTS);
		return 1;
	}
	return 0;
}


void addFlight(Flight flightBank[MAX_FLIGHTS], Flight new_flight){
	flightBank[n_flights] = new_flight;
	return;
}


#endif	/* IAEDPROJ1_FLIGHT_H */
