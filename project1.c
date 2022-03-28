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
	if ((num_airports++) > MAX_AIRPORTS) {
		printf(TOO_MANY_AIRPORTS);
		return 0;
	}
	return (validAirportID(airportID) &&
		   notDuplicateAirport(airportID, airportBank));
}


/* 	l	 */
void listAirports(Airport airportBank[MAX_AIRPORTS], int num){
	int i;
	if (!num) {
		num = n_airports;
	}
	for (i=0; i < num; i++)
		printf(OUT_AIRPORT, airportBank[i].ID, airportBank[i].city,
			   airportBank[i].country, airportBank[i].n_flights);
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
					   requestedAirports[a].n_flights);
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


Date newDate(Date possibleDate, Date today){
	today.day = possibleDate.day;
	today.month = possibleDate.month;
	today.year = possibleDate.year;
	return today;
}


int pastDate(int day, int month, int year, Date today){
	return ((year < today.year) ||
			(year == today.year && month < today.month) ||
			(year == today.year && month == today.month && day < today.day));
}

int oneYearAfter(int day, int month, int year, Date today,
				 int daysPerMonth[12]) {
	int days_between = 0,a;


	while (!(today.year == year && today.month == month)) {
		if (today.month <= 12){
			days_between += daysPerMonth[today.month-1];
			today.month++;
		}
		else {
			today.year++;
			today.month = 1;
		}
	}
	days_between += day - today.day;
	return (days_between > 365);
}


void outputDate(Date date){
	printf("%02d-%02d-%d\n", date.day, date.month, date.year);
	return;
}

int check_date(Date date, Date today) {
	int daysPerMonth[12] = {31,28,31,30,31, 30,
							31, 31, 30, 31, 30, 31};
	if (pastDate(date.day, date.month, date.year, today) ||
		oneYearAfter(date.day, date.month, date.year,
		  today, daysPerMonth)) {
		printf(INVALID_DATE);
		return 0;
	}
	if (date.day > daysPerMonth[date.month-1]){
		return 0;
	}
	return 1;
}


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

int validDuration(Time duration){
	if (duration.hour > 12 || (duration.hour == 12 && duration.min > 0)) {
		printf(INVALID_DURATION);
		return 0;
	}
	return 1;
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


int sameDate(Date date1, Date date2) {
	return (date1.day == date2.day && date1.month == date2.month
			&& date1.year == date2.year);
}

int airportIDs_exist(char arrivalAirportID[MAX_AIRPORT_ID],
	 char departureAirportID[MAX_AIRPORT_ID], Airport airportBank[MAX_AIRPORTS])
{
	int i, exists=1, Arr_flag=0, Dep_flag=0;
	for (i=0; i < n_airports; i++) {
		if (!strcmp(arrivalAirportID, airportBank[i].ID))
			Arr_flag++;

		if (!strcmp(departureAirportID, airportBank[i].ID))
			Dep_flag++;
	}
	if (!Dep_flag) {
		printf(OUT_NO_AIRPORT_ID, departureAirportID);
		exists = 0;
	}
	if (!Arr_flag){
		printf(OUT_NO_AIRPORT_ID, arrivalAirportID);
		exists = 0;
	}
	return exists;
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

int valid_case_v(FlightID flightID, char arrivalAirportID[MAX_AIRPORT_ID],
				 char departureAirportID[MAX_AIRPORT_ID], Date departureDate,
				 Date today, Time duration,
				 int capacity, Airport airportBank[MAX_AIRPORTS],
				 Flight flightBank[MAX_FLIGHTS])
{

	return (validFlightID(flightID) &&
		notDuplicateFlight(flightID, departureDate, flightBank) &&
		validAirportID(departureAirportID) &&
		validAirportID(arrivalAirportID) &&
		airportIDs_exist(arrivalAirportID, departureAirportID, airportBank)
		&& !tooManyFlights() && check_date(departureDate, today) &&
		validDuration(duration) && validCapacity(capacity)
		);
}


void addFlight(Flight flightBank[MAX_FLIGHTS], Flight new_flight){
	flightBank[n_flights] = new_flight;
	return;
}

Date createDate(int day, int month, int year) {
	Date date;
	date.day = day;
	date.month = month;
	date.year = year;
	return date;
}

Time createTime(int hour, int min) {
	Time time;
	time.hour = hour;
	time.min = min;
	return time;
}

dateTime createDateTime(Date date, Time time) {
	dateTime DateTime;
	DateTime.date = date;
	DateTime.time = time;
	return DateTime;
}

FlightID createFlightID(char flightID_str[MAX_LETTERS_FLIGHT_ID],
											int flightID_num){
	FlightID flightId;
	flightID_str[MAX_LETTERS_FLIGHT_ID-1] = '\0';
	strcpy(flightId.letters, flightID_str);
	flightId.num = flightID_num;
	return flightId;
}


Date readCommand(char cmd, Airport airportBank[MAX_AIRPORTS],
				 				Flight flightBank[MAX_FLIGHTS], Date today) {
	char airportID[MAX_AIRPORT_ID], country[MAX_COUNTRY], city[MAX_CITY];
	switch (cmd) {
		case 'a':
			scanf(" %s %s ", airportID, country);
			scanf("%[^\n]", city);
			/*fgets(city, MAX_CITY, stdin);*/
			/*tb posso criar dentro do add*/
			if (validate_case_a(airportID,
								airportBank)) { /*should I checkCountry and
												   checkLetters too??*/
				Airport new_airport = createAirport(airportID, country, city);
				addAirport(new_airport, airportBank);
				printf(OUT_AIRPORT_ID, airportID);
				n_airports++;
				/*tenho de aumentar o n_airports mas variaveis n se alteram fora da funcao, so tabelas*/
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
			printf("na\n");
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



