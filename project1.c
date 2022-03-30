/* Projeto1.c */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proj1.h"





 /*existe %s +para scanf de strings e %02d para imprimir horas com 0 antes*/

int n_airports = 0;
int n_flights = 0;

/*	a 	*/

/*sortAlphabetically()------------------------------------------------------*/



#define less(A, B) (A < B)


int beforeLetters(char beforeWord[MAX_AIRPORT_ID], char afterWord[MAX_AIRPORT_ID]) {
	return (less(beforeWord[0], afterWord[0]) ||
			((beforeWord[0] == afterWord[0]) &&
			 less(beforeWord[1], afterWord[1])) ||
			((beforeWord[0] == afterWord[0]) && (beforeWord[1] == afterWord[1])
			 && less(beforeWord[2], afterWord[2])));
}



void exch(Airport airportBank[MAX_AIRPORTS], int i, int right){
	Airport t = airportBank[i];
	airportBank[i] = airportBank[right];
	airportBank[right] = t;
	return;

}

int partition(Airport airportBank[MAX_AIRPORTS], int left, int right) {
	int i = left-1;
	int j = right;
	char v[MAX_AIRPORT_ID];
	strcpy(v, airportBank[right].ID);
	while (i < j) {
		while (beforeLetters(airportBank[++i].ID, v));

		while (beforeLetters(v, airportBank[--j].ID)){
			if (j == left)
				break;
		}
		if (i < j)
			exch(airportBank, i, j);
	}
	exch(airportBank, i, right);
	return i;
}


void quicksort(Airport airportBank[MAX_AIRPORTS], int left, int right)
{
	int i;
	if (right <= left)
		return;
	i = partition(airportBank, left, right);
	quicksort(airportBank, left, i-1);
	quicksort(airportBank, i+1, right);
}


/*------------------------------------------------------------------------*/


int validate_case_a(char airportID[], Airport airportBank[MAX_AIRPORTS]){
	int num_airports = n_airports;
	if ((++num_airports) > MAX_AIRPORTS) {
		printf(TOO_MANY_AIRPORTS);
		return 0;
	}
	return (validAirportID(airportID) &&
		   !airportExist(airportID, airportBank, 'a'));
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

void listFlights(Flight flightBank[MAX_FLIGHTS]) {
	int i;
	Date f_date;
	Time f_time;
	Flight f;
	for (i=0; i < n_flights; i++) {
		f = flightBank[i];
		f_date = f.departureDateTime.date;
		f_time = f.departureDateTime.time;
		printf(OUT_FLIGHT, f.ID.letters, f.ID.num, f.departureAirport, f.arrivalAirport,
			   f_date.day, f_date.month, f_date.year, f_time.hour, f_time.min);
	}
	return;
}

void listRequestedAirports(Airport airportBank[MAX_AIRPORTS],
			   char requested_IDs[MAX_AIRPORTS][MAX_AIRPORT_ID], int num_IDs){
	int i, e, a, c;
	Airport requestedAirports[MAX_AIRPORTS];
	int existingID[MAX_AIRPORTS];
	int n=0, inicialized = 0;
	for (c=0; c < num_IDs; c++){
		existingID[c] = 0;
	}
	for (i=0; i < n_airports; i++){
		if (n == num_IDs)	/*	ja temos todos os requested	*/
			break;
		for (e=0; e < num_IDs; e++){
			if (!inicialized) {		/* inicializa a 0 o vetor que ira ver se IDs existem */
				existingID[e] = 0;
				/*requestedAirports[e] = createAirport("", "", "");*/
			}

			if (!strcmp(airportBank[i].ID, requested_IDs[e])){
				requestedAirports[e] = airportBank[i];
				n++;
				existingID[e] = 1;
				break;	/*	TIRAR SE PEDIREM O MM ID 2 VEZES NO INPUT */
			}
		}
		inicialized = 1;
	}
	/*for (b=0; b < num_IDs; b++) {
		if (!existingID[b])
			requestedAirports[e] = createAirport("o", "o", "o");
	}*/

	if (n != num_IDs){	/* so ve os nao existem se nao tiver encontrado todos*/
		for (a=0; a < num_IDs; a++){	/* validar se existe o ID */
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



/*três letras maiusculas, pais máximo de 30 carateres,
	cidade(uma string não vazia com um máximo de 50 carateres;
		   podem ocorrer carateres brancos(espaços ou tabulador \t))
		país apenas contém letras minusculas ou maíusculas.*/




dateTime sumDuration(dateTime departure, Time duration) {
	departure.time.hour += duration.hour;
	departure.time.min += duration.min;
	if (departure.time.min > 59) {
		departure.time.min -= 60;
		departure.time.hour += 1;
	}
	if (departure.time.hour > 23) {
		departure.time.hour -= 24;
		departure.date.day += 1;
	}
	return departure;
}



int valid_case_v(FlightID flightID, char arrivalAirportID[MAX_AIRPORT_ID],
				 char departureAirportID[MAX_AIRPORT_ID], Date departureDate,
				 Date today, Time duration,
				 int capacity, Airport airportBank[MAX_AIRPORTS],
				 Flight flightBank[MAX_FLIGHTS])
{
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
				 airportBank[departureIndexPlus1].n_Departure_Flights++;
				 airportBank[arrivalIndexPlus1].n_Arrival_Flights++;
				 return 1;
			 }
	}
	return 0;
}


/*void case_p_c(char airportID[MAX_AIRPORT_ID], Flight flightBank[MAX_FLIGHTS],
			  Airport airportBank[MAX_AIRPORTS], char flag) {
	int i, number_flights;
	int airportIndexPlus1 = airportExist(airportID, airportBank, 'v');
	if (!airportIndexPlus1) {
		return;
	}
	number_flights = airportBank[airportIndexPlus1-1];
	for (i=0; i < n_flights; i++) {
		if (flag == 'p' && flightBank[i])
	}
	return;
}*/


Date readCommand(char cmd, Airport airportBank[MAX_AIRPORTS],
				 				Flight flightBank[MAX_FLIGHTS], Date today) {
	char airportID[MAX_AIRPORT_ID], country[MAX_COUNTRY], city[MAX_CITY];
	switch (cmd) {
		case 'a':
			scanf(" %s %s ", airportID, country);
			scanf("%[^\n]", city);
			if (validate_case_a(airportID,
								airportBank)) { /*should I checkCountry and
												   checkLetters too??*/
				Airport new_airport = createAirport(airportID, country, city);
				addAirport(new_airport, airportBank);
				printf(OUT_AIRPORT_ID, airportID);
				n_airports++;

			}
			break;
		case 'l':
			if (getchar() == '\n') {
				quicksort(airportBank, 0, n_airports - 1);
				listAirports(airportBank, 0);
			} else {
				char requested_IDs[MAX_AIRPORTS]
								  [MAX_AIRPORT_ID];
				int num_IDs = 0;
				do { /*	VER SE STRTOK ERA MELHOR PK ESQUECI ME */
					scanf("%s", airportID);
					strcpy(requested_IDs[num_IDs], airportID);
					num_IDs++;
				} while (getchar() != '\n');
				listRequestedAirports(airportBank, requested_IDs, num_IDs);
			}
			break;

		case 'v':
		{
			if (getchar() == '\n') {
				listFlights(flightBank);
			} else {
				int flightID_num, capacity, day, month, year, hour, min;
				int durationHour, durationMin;
				char departureAirportID[MAX_AIRPORT_ID],
					arrivalAirportID[MAX_AIRPORT_ID],
					flightID_str[MAX_LETTERS_FLIGHT_ID];
				FlightID flightID;
				Date departureDate;
				Time duration;

				/*Time departureTime;*/
				scanf("%02s%d", flightID_str, &flightID_num);
				scanf(" %s %s", departureAirportID, arrivalAirportID);
				scanf(" %d-%d-%d", &day, &month, &year);
				scanf(" %d:%d", &hour, &min);
				scanf(" %d:%d %d", &durationHour, &durationMin, &capacity);

				flightID = createFlightID(flightID_str, flightID_num);
				departureDate = createDate(day, month, year);
				duration = createTime(durationHour, durationMin);

				if (!valid_case_v(flightID, arrivalAirportID,
							  departureAirportID, departureDate, today,
							  duration, capacity,
							  airportBank, flightBank))
				{
					break;
				}
				else{
					Flight newFlight;
					Time departureTime;
					dateTime departureDateTime;
					departureTime = createTime(hour, min);
					departureDateTime = createDateTime(departureDate,
													   departureTime);
					newFlight = createFlight(flightID,
									departureAirportID, arrivalAirportID,
										departureDateTime, duration, capacity);

					addFlight(flightBank, newFlight);
					n_flights++;
				}
			}
			break; }

		case 'p':
		{
/*			char departureAirportID[MAX_AIRPORT_ID];
			scanf(" %s", departureAirportID);
			case_p_c(departureAirportID, flightBank, airportBank, 'p');*/

		}
			printf("na");
			break;
		case 'c':
			printf("na\n");
			break;
		case 't': {
			int day, month, year;
			Date possibleDate;
			scanf("%d-%d-%d", &day, &month, &year);
			possibleDate = createDate(day, month, year);
			if (check_date(possibleDate, today)) {
				today = newDate(possibleDate, today);
				outputDate(today);
			}
			break;
		}
		default:
			break;
	}
	return today;
}


int main() {
	/*char cmd;
	scanf("%c", &cmd);
	while (cmd != EOF) {
		while (getchar(cmd) != "\0") {
			readcommand(cmd);
		}
		scanf("%c", &cmd);
	}*/
	Airport airportBank[MAX_AIRPORTS] = {0};
	Flight flightBank[MAX_FLIGHTS] = {0};
	Date today = {1,1,2022};
	char cmd;
	while ((cmd = getchar()) != EOF && cmd != END_PROGRAM){
		today = readCommand(cmd, airportBank, flightBank, today);
	}
	return 0;
}



