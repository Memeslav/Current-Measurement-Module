#include "main.h"

// Структура для представления даты и времени
typedef struct {
    int tm_sec;   // Секунды [0, 59]
    int tm_min;   // Минуты [0, 59]
    int tm_hour;  // Часы [0, 23]
    int tm_mday;  // День месяца [1, 31]
    int tm_mon;   // Месяц [0, 11] (0 = январь)
    int tm_year;  // Год (от 1900)
    int tm_wday;  // День недели [0, 6] (0 = воскресенье)
    int tm_yday;  // День года [0, 365]
} tm;

// Константы для расчётов
#define SECONDS_PER_MINUTE  60
#define SECONDS_PER_HOUR    3600
#define SECONDS_PER_DAY     86400

// Год, от которого начинается Unix-время
#define UNIX_EPOCH_YEAR     1970

// Длительность месяцев (невисокосного года)
const int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

// Проверка високосного года
static inline int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Вычисление текущей даты из Unix Time
void unix_to_date(uint32_t unixtime, tm* result) {
    uint32_t seconds = unixtime;

    // Вычисляем секунды, минуты и часы
    result->tm_sec = seconds % SECONDS_PER_MINUTE;
    seconds /= SECONDS_PER_MINUTE;
    result->tm_min = seconds % 60;
    seconds /= 60;
    result->tm_hour = seconds % 24;
    seconds /= 24;

    // Вычисляем год
    int year = UNIX_EPOCH_YEAR;
    while (seconds >= 365) {
        int days_in_year = is_leap_year(year) ? 366 : 365;
        if (seconds < days_in_year) break;
        seconds -= days_in_year;
        year++;
    }
    result->tm_year = year - 1900;
    result->tm_yday = seconds;

    // Вычисляем месяц и день месяца
    int month = 0;
    while (1) {
        int days_in_current_month = days_in_month[month];
        if (month == 1 && is_leap_year(year)) { // Учитываем високосный февраль
            days_in_current_month++;
        }
        if (seconds < days_in_current_month) break;
        seconds -= days_in_current_month;
        month++;
    }
    result->tm_mon = month;
    result->tm_mday = seconds + 1;

    // Вычисляем день недели (воскресенье = 0)
    result->tm_wday = (unixtime / SECONDS_PER_DAY + 4) % 7;
}

int main(void)
{
    while (1)
    {

    }
}
