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