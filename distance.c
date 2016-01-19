/**
 * @Version 1.0
 * @author Sullivan Wenger
 * The purpose of this project is to create
 * a program that calculates the distance
 * between two days or adds or subtracts an
 * amount of days from a given date.
 * So far, this parses the date from a string.
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main () {
	char date [15], *ptr;
	int month = 0, day = 0, year = 0;
	ptr = date;
	printf("Enter the desired date in the form mm/dd/yyyy\n");
	fgets (date, sizeof (date), stdin);
	while (*ptr != '/') {
		month *= 10;
		month += (int) *ptr;
		month -= (int) '0';
		ptr ++;
	}
	ptr ++;
	while (*ptr != '/') {
		day *= 10;
		day += (int) *ptr;
		day -= (int) '0';
		ptr ++;
	}
	ptr ++;
	while (*ptr != '\n') {
		year *= 10;
		year += (int) *ptr;
		year -= (int) '0';
		ptr ++;
	}
	printf("%i\\%i\\%i",year, day, month);
	return 0;
}
