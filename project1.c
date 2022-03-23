/* Projeto1.c */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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

/* 
Airport - ID, country, city
Flight - ID, departure airport, arrival airport, departure date and time, duration, max passengers 
Date
Time?
 */

typedef struct {
    int day;
    int month;
    int year;
} date;

int check_date(date Date){
    int Months30days = { 4, 6, 9, 11 }, Months31days = { 1, 3, 5, 7, 8, 10, 12 };
    if (Date.month == 2 && Date.day > 28)       /* caso dos 28 dias de fevereiro */
        return 0;
    for (i = 0, i < 7, i++){
        if (i < 4 && Date.month == Months30days[i] && Date.day > 30) /* SERIA MAIS EFICIENTE ESTAR NOUTRO FOR?*/
            return 0;
        if (Date.month == Months31days[i] && Date.day > 31)
            return 0;
    }
    // falta ver se data for antes ou mais de 1 ano no futuro
    return 1;
}

date sum_dates(date Date1, date Date2){
    date DateSum;
    DateSum.day = Date1.day + Date1.day
}


typedef struct {
    int hour;
    int min;
} time;

date sum_times(time Time1, time Time2){
    time TimeSum;       // MAS TENHO DE TER EM CONTA QUE PODE MUDAR DE DIA LOGO NAO POSSO INSERIR SO TIMES, TEM DE SER UMA OUTRA STRUCT MAYBE
    TimeSum.hour = Time1.hour + Time1.hour
}




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