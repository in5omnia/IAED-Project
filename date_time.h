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
} DateTime;


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

DateTime createDateTime(Date date, Time time) {
	DateTime dateTime;
	dateTime.date = date;
	dateTime.time = time;
	return dateTime;
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


int oneYearAfter(int day, int month, int year, Date today) {

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
					 today)) {
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


int beforeTime(Time time1, Time time2){
	if (time1.hour < time2.hour ||
		(time1.hour == time2.hour && time1.min < time2.min))
		return 1;
	return 0;
}


int pastDateTime(DateTime dateTime1, DateTime dateTime2) {
	int day1 = dateTime1.date.day, month1 = dateTime1.date.month,
		year1 = dateTime1.date.year;
	if (pastDate(day1, month1, year1, dateTime2.date)){
		return 1;
	}
	if (sameDate(dateTime1.date, dateTime2.date) &&
		beforeTime(dateTime1.time, dateTime2.time)) {
		return 1;
	}
	return 0;
}

DateTime sumDuration(DateTime departure, Time duration) {
	int daysPerMonth[12] = {31,28,31,30,31, 30,
							31, 31, 30, 31, 30, 31};
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
	if (departure.date.day > daysPerMonth[departure.date.month-1]) {
		departure.date.month++;
		departure.date.day = 1;
	}
	if (departure.date.month > 12) {
		departure.date.year++;
		departure.date.month = 1;
	}
	return departure;
}




#endif	/* IAEDPROJ1_DATE_TIME_H */
