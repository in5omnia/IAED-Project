/* Projeto1.c */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include </Users/beatrizgavilan/CLionProjects/IAED-project1/proj1.h>
/*#include <airport.c>*/

 /*existe %s +para scanf de strings e %02d para imprimir horas com 0 antes*/

int n_airports = 0;

/*	a 	*/

/*sortAlphabetically()------------------------------------------------------*/

/*

#define less(A, B) (A < B)


int beforeLetters(char beforeWord[MAX_AIRPORT_ID], char afterWord[MAX_AIRPORT_ID]) {
	return (less(beforeWord[0], afterWord[0]) ||
			((beforeWord[0] == afterWord[0]) &&
			 less(beforeWord[1], afterWord[1])) ||
			((beforeWord[0] == afterWord[0]) && (beforeWord[1] == afterWord[1])
			 && less(beforeWord[2], afterWord[2])));
}
*/



/*

void exch(Airport a, Airport b){
	char id[MAX_AIRPORT_ID], country[MAX_COUNTRY], city[MAX_CITY];
	*/
/*	temporary variables	*//*

	int flights = a.n_flights;
	strcpy(id, a.ID);
	strcpy(country, a.country);
	strcpy(city, a.city);
	*/
/* change airport a *//*

	strcpy(a.ID, b.ID);
	strcpy(a.country, b.country);
	strcpy(a.city, b.city);
	a.n_flights = b.n_flights;
	*/
/* change airport b *//*

	strcpy(b.ID, id);
	strcpy(b.country, country);
	strcpy(b.city, city);
	b.n_flights = flights;
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
			exch(airportBank[i], airportBank[j]);
	}
	exch(airportBank[i], airportBank[right]);
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
*/

/*------------------------------------------------------------------------*/

Airport createAirport(char airportID[MAX_AIRPORT_ID],
					  char country[MAX_COUNTRY], char city[MAX_CITY]){
	Airport airport;
	strcpy(airport.ID, airportID);
	strcpy(airport.country, country);
	strcpy(airport.city, city);
	airport.n_flights = 0;
	return airport;
}

void addAirport(Airport new_airport, Airport airportBank[MAX_AIRPORTS]){/*[[airport, voosPartida, voosChegada], ...]*/
	airportBank[n_airports] = new_airport;
	return;
}


int validAirportID(/*const */char airportID[]){
	int i;
	for (i=0; airportID[i] != '\0'; i++){
		if (i >= MAX_AIRPORT_ID-1) {	/*	mais de 3 letras */
			printf(INVALID_AIRPORT_ID);
			return 0;
		}
		if (airportID[i] < 'A' || airportID[i] > 'Z') {	/* nao sao maiusculas */
			printf(INVALID_AIRPORT_ID);
			return 0;
		}
	}
	if (i < MAX_AIRPORT_ID-1) {	/* menos de 3 letras */
		printf(INVALID_AIRPORT_ID);
		printf("2yo");
		return 0;
	}
	return 1;
}


int notDuplicateAirport(char airportID[], Airport airportBank[MAX_AIRPORTS]){
	int i;
	for (i=0; i < n_airports; i++){
		if (!strcmp(airportID, airportBank[i].ID)) {
			printf(DUPLICATE_AIRPORT);
			return 0;
		}
	}
	return 1;
}


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
		printf(OUT_AIRPORT, airportBank[i].ID, airportBank[i].city, airportBank[i].country, airportBank[i].n_flights);
	return;
}

void listRequestedAirports(Airport airportBank[MAX_AIRPORTS], char requested_IDs[MAX_AIRPORTS][MAX_AIRPORT_ID], int num_IDs){
	int i, e, a;
	Airport requestedAirports[MAX_AIRPORTS];				/* 	NAO TENHO DE VER INVALID ID??????	*/
	int existingID[MAX_AIRPORTS];
	int n=0, inicialized = 0;
	for (i=0; i < n_airports; i++){
		if (n == num_IDs)	/*	ja temos todos os requested	*/
			break;
		for (e=0; e < num_IDs; e++){
			if (!inicialized) {		/* inicializa a 0 o vetor que ira ver se IDs existem */
				existingID[e] = 0;
			}

			if (!strcmp(airportBank[i].ID, requested_IDs[e])){	/* !!!!!QUERO ENCONTRAR FORMA + eficiente que nao percorra todos os requested */
				requestedAirports[e] = airportBank[i];
				n++;
				existingID[e] = 1;
				break;	/*	TIRAR SE PEDIREM O MM ID 2 VEZES NO INPUT */
			}
		}
		inicialized = 1;
	}

	if (n != num_IDs){	/* so ve os nao existem se nao tiver encontrado todos*/
		for (a=0; a < num_IDs; a++){	/* validar se existe o ID */
			if (!existingID[a]){
				printf(OUT_NO_AIRPORT_ID, requestedAirports[a].ID);
			}
			else{
				printf(OUT_AIRPORT, requestedAirports[a].ID, requestedAirports[a].city,
					   requestedAirports[a].country, requestedAirports[a].n_flights);
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


Date newDate(int day, int month, int year, Date today){
	today.day = day;
	today.month = month;
	today.year = year;
	return today;
}


int pastDate(int day, int month, int year, Date today){
	return ((year < today.year) ||
			(year == today.year && month < today.month) ||
			(year == today.year && month == today.month && day < today.day));
}

int oneYearAfter(int day, int month, int year, Date today,
				 int daysPerMonth[12]){
	int days_between = 0;
	while (today.year != year || today.month != month) {
		if (days_between >= 365) {
			return 1;
		}
		else if (month <= 12){
			days_between += daysPerMonth[month-1] - (today.day-1);
			today.month++;
			today.day = 1;
		}
		else {
			today.year++;
			today.month = 1;
			today.day = 1;
		}
	}
	days_between += day - (today.day-1);
	return (days_between >= 365);
}

void outputDate(Date date){
	printf("%02d-%02d-%d\n", date.day, date.month, date.year);
	return;
}

int check_date(int day, int month, int year, Date today) {
	int daysPerMonth[12] = {31,28,31,30,31, 30,
							31, 31, 30, 31, 30, 31};
	if (pastDate(day, month, year, today) || oneYearAfter(day, month, year,
		  today, daysPerMonth)) {
		printf("invalid date");
		return 0;
	}
	if (day > daysPerMonth[month-1]){
		return 0;
	}

	/*int i, Months30days[4] = {4, 6, 9, 11};
	int Months31days[7] = {1, 3, 5, 7, 8, 10, 12};
	if (month == 2 && day > 28) */ /* caso dos 28 dias de fevereiro */ /*
	{
		return 0;
	}
	for (i = 0; i < 7; i++) {
		if (i < 4 && month == Months30days[i] &&
			day > 30) */ /* SERIA MAIS EFICIENTE ESTAR NOUTRO FOR?*/ /*
		{
			return 0;
		}
		if (month == Months31days[i] && day > 31)
			return 0;
	}*/
	/* falta ver se data for antes ou mais de 1 ano no futuro*/
	return 1;
}



Date readCommand(char cmd, Airport airportBank[MAX_AIRPORTS], Date today) {
	char airportID[MAX_AIRPORT_ID], country[MAX_COUNTRY], city[MAX_CITY];
	switch (cmd) {
		case 'a':
			scanf(" %s %s ", airportID, country);
			scanf("%[^\n]", city);
			/*fgets(city, MAX_CITY, stdin);*/
			/*tb posso criar dentro do add*/
			if (validate_case_a(airportID, airportBank))
			{	/*should I checkCountry and checkLetters too??*/
				Airport new_airport = createAirport(airportID, country, city);
				addAirport(new_airport, airportBank);
				printf(OUT_AIRPORT_ID, airportID);
				n_airports++;
				/*tenho de aumentar o n_airports mas variaveis n se alteram fora da funcao, so tabelas*/
			}
			break;
		case 'l':
			if (getchar() == '\n') {
				/*quicksort(airportBank, 0, n_airports-1);*/
				listAirports(airportBank, 0);
			}
			else {
				char requested_IDs[MAX_AIRPORTS][MAX_AIRPORT_ID];	/* arrays of strings are confusing af */
				int num_IDs = 0;
				do {	/*	VER SE STRTOK ERA MELHOR PK ESQUECI ME */
					scanf("%s", airportID);
					strcpy(requested_IDs[num_IDs], airportID);
					num_IDs++;
				} while (getchar() != '\n');
				listRequestedAirports(airportBank, requested_IDs, num_IDs);
			}
			break;

		case 'v':
			/*if (getchar() == '\n') {
				*/ /*listFlights(flightBank, 0);*/ /*
				printf("yoyo case v if\n");
			}
			else {
				int flightID, capacity, day, month, year, hour, min;
				int durationHour, durationMin;
				char departureAirportID[MAX_AIRPORT_ID],
					arrivalAirportID[MAX_AIRPORT_ID];

				*/ /*Time departureTime;*/ /*
				scanf("%d", &flightID);
				scanf(" %s %s", departureAirportID, arrivalAirportID);
				scanf(" %d-%d-%d",  &day, &month, &year);
				scanf(" %d:%d", &hour, &min);
				scanf(" %d:%d %d", &durationHour, &durationMin, &capacity);

				if (!validAirportID(departureAirportID) ||
						!validAirportID(arrivalAirportID))
					break;
				if (check_date(day, month, year, today)){
					Date departureDate = {day, month, year};
					printf("ifnora v else date %d\n", departureDate.year);
			}
			printf("yoyo case v elseeee\n");*/
			break;

		case 'p':
			printf("yo");
			break;
		case 'c':
			printf("yo");
			break;
		case 't':
		{
			int day, month, year;
			scanf("%d-%d-%d", &day, &month, &year);
			if (check_date(day, month, year, today)) {
				today = newDate(day, month, year, today);
				outputDate(today);
			}
			break;
		}
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
	Date today = {1,1,2022};
	char cmd;
	while ((cmd = getchar()) != EOF && cmd != END_PROGRAM){
		today = readCommand(cmd, airportBank, today);
	}
	return 0;
}


Time sum_times(Time time1,
			   Time duration) {	  /*MAS TENHO DE TER EM CONTA QUE PODE MUDAR DE
								  DIA LOGO NAO POSSO INSERIR SO TIMES, TEM DE
								  SER UMA OUTRA STRUCT MAYBE*/
	time1.hour += duration.hour;
	time1.min += duration.min;
	if (time1.min > 59) {
		time1.min -= 60;
		time1.hour += 1;
	}
	return time1;
}

int validFlightID(int flightID){
	return (flightID > 0 && flightID <= 9999);
}

int validDuration(Time duration, Time departureTime){		/*ERRADO*/
	printf("---%d %d valid duration print\n", duration.hour, departureTime.hour);
	return 0;
}


