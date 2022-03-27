typedef struct {
    date Date;
    time Time;
} dateTime;


dateTime sum_times(dateTime DateTime1, time Duration) {     // MAS TENHO DE TER EM CONTA QUE PODE MUDAR DE DIA LOGO NAO POSSO INSERIR SO TIMES, TEM DE SER UMA OUTRA STRUCT MAYBE
    DateTime1.Time.hour += Duration.hour;
    DateTime1.Time.min += Duration.min;
    if (DateTime1.Time.min > 59) {
        DateTime1.Time.min -= 60;
        DateTime1.Time.hour += 1;
    }
    if (DateTime1.Time.hour > 23) {
        DateTime1.Time.hour -= 24;
        DateTime1.Date.day += 1;
    }
    return DateTime1;
}

/*airportBank[n_airports][0] = airport;
	airportBank[n_airports][1] = airport;
	airportBank[n_airports][2] = airport;*/


int readcommand(char cmd, Airport airportBank[MAX_AIRPORTS], int n_airports) {
	int flag=1;
	char airportID[MAX_AIRPORT_ID], country[MAX_COUNTRY], city[MAX_CITY];
	switch (cmd) {
		case 'q':
			return 0;	//quit
		case 'a':
			scanf("%s %s ", airportID, country);
			fgets(city, MAX_CITY, stdin);
			//tb posso criar dentro do add
			return
		case 'l':

		case 'v':

		case 'p':

		case 'c':

		case 't':

	}
	return flag;
}


int main() {

	Airport airportBank[MAX_AIRPORTS] = {0};
	Date today = {1,1,2022};
	int n_airports = 0;
	char cmd, airportID[MAX_AIRPORT_ID], country[MAX_COUNTRY], city[MAX_CITY];
	while ((cmd = getchar()) != EOF){

		switch (readcommand(cmd)) {
			case 0:
				break;	// quit
			case 1:
				case_a();
			case 2:

			case 3:

			case 4:

			case 5:

			case 6:
				case_t()
		}

	}

	return 0;
}
