/* Projeto1.c */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include </Users/beatrizgavilan/CLionProjects/IAED-project1/proj1.h>
/*#include <airport.c>*/
/* cant use qsort() */

// !!!!!existe %s +para scanf de strings e %02d para imprimir horas com 0 antes

int n_airports = 0;

/*	a 	*/

Airport createAirport(char airportID[MAX_AIRPORT_ID],
					  char country[MAX_COUNTRY], char city[MAX_CITY]){
	Airport airport;
	strcpy(airport.ID, airportID);
	strcpy(airport.country, country);
	strcpy(airport.city, city);
	airport.n_flights = 0;
	return airport;
}

void addAirport(Airport new_airport, Airport airportBank[MAX_AIRPORTS]){ //[[airport, voosPartida, voosChegada], ...]
	airportBank[n_airports] = new_airport;
	return;
}


int validAirportID(/*const */char airportID[]){
	int i;
	for (i=0; airportID[i] != '\0'; i++){
		if (i >= MAX_AIRPORT_ID) {	/*	mais de 3 letras */
			printf(TOO_MANY_AIRPORTS);
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
	for (int i=0; i < n_airports; i++){
		if (!strcmp(airportID, airportBank[i].ID)) {
			printf(DUPLICATE_AIRPORT);
			return 0;
		}
	}
	return 1;
}


int validate_case_a(char airportID[], Airport airportBank[MAX_AIRPORTS]){
	int num_airports = n_airports;
	return (num_airports++) <= MAX_AIRPORTS && validAirportID(airportID)
		   && notDuplicateAirport(airportID, airportBank);
}


/* 	l	 */
void listAirports(Airport airportBank[MAX_AIRPORTS], int num){
	if (!num) {
		num = n_airports;
	}
	for (int i=0; i < num; i++)
		printf(OUT_AIRPORT, airportBank[i].ID, airportBank[i].city, airportBank[i].country, airportBank[i].n_flights);
	return;
}

void listRequestedAirports(Airport airportBank[MAX_AIRPORTS], char requested_IDs[MAX_AIRPORTS][MAX_AIRPORT_ID], int num_IDs){
	Airport requestedAirports[num_IDs];				/* 	NAO TENHO DE VER INVALID ID??????	*/
	int existingID[num_IDs];
	int n=0, inicialized = 0;
	for (int i=0; i < n_airports; i++){
		if (n == num_IDs)	/*	ja temos todos os requested	*/
			break;
		for (int e=0; e < num_IDs; e++){
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
		for (int a=0; a < num_IDs; a++){	/* validar se existe o ID */
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


void readcommand(char cmd, Airport airportBank[MAX_AIRPORTS]) {
	char airportID[MAX_AIRPORT_ID], country[MAX_COUNTRY], city[MAX_CITY];
	switch (cmd) {
		case 'a':
			scanf(" %s %s ", airportID, country);
			scanf("%[^\n]", city);
			/*fgets(city, MAX_CITY, stdin);*/
			//tb posso criar dentro do add
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
			printf("yo");
			break;
		case 'p':
			printf("yo");
			break;
		case 'c':
			printf("yo");
			break;
		case 't':
			printf("yo");
			break;

	}
	return;
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
			readcommand(cmd, airportBank);
	}
	return 0;
}


/*três letras maiusculas, pais máximo de 30 carateres,
	cidade(uma string não vazia com um máximo de 50 carateres;
		   podem ocorrer carateres brancos(espaços ou tabulador \t))
		país apenas contém letras minusculas ou maíusculas.*/



int check_date(Date date) {
	int i, Months30days[4] = {4, 6, 9, 11};
	int Months31days[7] = {1, 3, 5, 7, 8, 10, 12};
	if (date.month == 2 && date.day > 28) /* caso dos 28 dias de fevereiro */
		return 0;
	for (i = 0; i < 7; i++) {
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



