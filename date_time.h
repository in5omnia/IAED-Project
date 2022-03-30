/*
 Created by Beatriz Gavilan on 29/03/2022.
*/

#ifndef IAEDPROJ1_DATE_TIME_H
#define IAEDPROJ1_DATE_TIME_H



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
	Date date;
	Time time;
} dateTime;


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


int oneYearAfter(int day, int month, int year, Date today/*,
				 int daysPerMonth[12]*/) {
/*	int days_between = 0;


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
	return (days_between > 365);*/
	Date later_than_one_year = createDate(today.day+1, today.month,
									  today.year+1);
	return !pastDate(day, month, year, later_than_one_year);
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
					 today/*, daysPerMonth*/)) {
		printf(INVALID_DATE);
		return 0;
	}
	if (date.day > daysPerMonth[date.month-1]){
		return 0;
	}
	return 1;
}



int validDuration(Time duration){
	if (duration.hour > 12 || (duration.hour == 12 && duration.min > 0)) {
		printf(INVALID_DURATION);
		return 0;
	}
	return 1;
}



int sameDate(Date date1, Date date2) {
	return (date1.day == date2.day && date1.month == date2.month
			&& date1.year == date2.year);
}



#endif	/* IAEDPROJ1_DATE_TIME_H */
