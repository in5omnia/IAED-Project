/* Projeto1.c */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* cant use qsort() */

// !!!!!existe %s +para scanf de strings e %02d para imprimir horas com 0 antes

/*
q termina o programa
a adiciona um novo aeroporto ao sistema
l lista os aeroportos
v adiciona um voo ou lista todos os voos
p lista os voos com partida de um aeroporto
c lista os voos com chegada a um aeroporto
t avança a data do sistema
 */
#define MAX_CITY 51
#define MAX_COUNTRY 31
#define MAX_AIRPORT_ID 4
#define MAX_AIRPORTS 40
#define MAX_FLIGHTS 30000

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
	char ID[MAX_AIRPORT_ID];
	char country[MAX_COUNTRY];
	char city[MAX_CITY];
} Airport;


Airport createAirport(char airportID[MAX_AIRPORT_ID],
					  char country[MAX_COUNTRY], char city[MAX_CITY]){
	Airport airport;
	strcpy(airport.ID,airportID);
	strcpy(airport.country, country);
	strcpy(airport.city, city);
	return airport;
}

Airport addAirport(Airport airport, Airport airportBank[MAX_AIRPORTS], int n_airports){ //[[airport, voosPartida, voosChegada], ...]
	/*airportBank[n_airports][0] = airport;
	airportBank[n_airports][1] = airport;
	airportBank[n_airports][2] = airport;*/
	airportBank[n_airports] = airport;
	return airportBank;
}


int readcommand() {
	int n_airports = 0;
	char cmd, airportID[MAX_AIRPORT_ID], country[MAX_COUNTRY], city[MAX_CITY];
	switch (cmd = getchar()) {
		case 'q':
			flag = 0;	//quit
		case 'a':
			scanf("%s %s ", airportID, country);
			fgets(city, MAX_CITY, stdin);
			//tb posso criar dentro do add
			Airport airport = createAirport(airportID, country, city);
			addAirport(airport);
			outAirport();
		case 'l':

		case 'v':

		case 'p':

		case 'c':

		case 't':

	}
	return 0;
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

	return 0;
}

/*três letras maiusculas, pais máximo de 30 carateres,
	cidade(uma string não vazia com um máximo de 50 carateres;
		   podem ocorrer carateres brancos(espaços ou tabulador \t))
		país apenas contém letras minusculas ou maíusculas.*/



int check_date(Date date) {
	int i, Months30days = {4, 6, 9, 11}, Months31days = {1, 3, 5, 7, 8, 10, 12};
	if (date.month == 2 && date.day > 28) /* caso dos 28 dias de fevereiro */
		return 0;
	for (i = 0, i < 7, i++) {
		if (i < 4 && date.month == Months30days[i] &&
			date.day > 30) /* SERIA MAIS EFICIENTE ESTAR NOUTRO FOR?*/
			return 0;
		if (date.month == Months31days[i] && date.day > 31) return 0;
	}
	// falta ver se data for antes ou mais de 1 ano no futuro
	return 1;
}

Time sum_times(Time time1,
			   Time duration) {	 // MAS TENHO DE TER EM CONTA QUE PODE MUDAR DE
								 // DIA LOGO NAO POSSO INSERIR SO TIMES, TEM DE
								 // SER UMA OUTRA STRUCT MAYBE
	time1.hour += duration.hour;
	time1.min += duration.min;
	if (time1.min > 59) {
		time1.min -= 60;
		time1.hour += 1;
	}
	return time1;
}

typedef struct airport;
Airport listAirports();
Airport addAirport();
typedef struct flight Flight;
Flight listFlights();
Flight list_Arrival_Flights();
Flight list_Departure_Flights();
Flight addFlight(Flight f);
typedef struct date Date;
Date nextDay(Date today);

