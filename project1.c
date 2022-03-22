/* Projeto1.c */
#include <stdio.h>; <stdlib.h>; <ctype.h>; <string.h>
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

/* 
Airport - ID, country, city
Flight - ID, departure airport, arrival airport, departure date and time, duration, max passengers 
Date
Time?
 */

typedef struct airport Airport;
Airport listAirports();
Airport addAirport();
typedef struct flight Flight;
Flight listFlights();
Flight list_Arrival_Flights();
Flight list_Departure_Flights();
Flight addFlight(Flight f);
typedef struct date Date;
Date nextDay(Date today);


int main(){
    char cmd;
    scanf("%c", &cmd);
    while (cmd != EOF){
        while (getchar(cmd) != "\0"){
            readcommand(cmd);
        }
        scanf("%c", &cmd);
    }
    return 0;
}


int readcommand(){
    char cmd;
    switch (cmd = getchar()){
        case 'q':
            //quit
        case 'a':
            addAirport();
        case 'l':
            listAirports();
        case 'v':
            listFlights();
            addFlight();    //falta if
        case 'p':
            list_Departure_Flights();
        case 'c':
            list_Arrival_Flights();
        case 't':
            nextDay();
    }
    return 0;
}