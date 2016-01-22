/**
 * @version 3.0
 * @author Sullivan Wenger
 * The purpose of this project is to create
 * a program that calculates the distance
 * between two days or adds or subtracts an
 * amount of days from a given date.
 * So far, the part where the user enters a distance is fully functional
 * If the program enters two dates, the program can parse the dates and tell which comes first.
 * If they're in the same month, it can do the calculation.
 * This has been changed from version 2.0 in a couple ways.
 *   2.0 had all dates and day distance in an array called data. This one splits them up.
 *   The char array date has been changed to dateInput.
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int leap (int);
int divisible (int, int);

int main () {
	char dateInput [15], *ptr, type;
	int date1 [3]; //initial input date
	int date2 [3]; //second date input or resulting date, depending
	int days = 0; //resulting distance or input distance, depending
	int m [12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int *months = m; months --; //this way, the index of months will be 1-12 rather than 0-11
	int negative = 0; //if days will be negative, regardless of path taken
	int leap_count = 0;
	ptr = dateInput;
	for (int i = 0; i < 3; i ++) { //initialize arrays to 0
		date1 [i] = 0;
		date2 [i] = 0;
	}
	printf("Enter the desired date in the form mm/dd/yyyy\n");
	for (int i = 0; i < 15; i ++) {
		scanf("%c", ptr);
		if (*ptr == '\n') {
			if (i > 0) { //end at the newline character
				break;
			}
			else { //in case there was a lingering newline in stdin
				i --;
				ptr --;
			}
		}
		ptr ++;
	}
	ptr = dateInput;	
	//parse the value for month
	while (*ptr != '/') {
		date1 [0] *= 10;
		date1 [0] += (int) *ptr;
		date1 [0] -= (int) '0';
		ptr ++;
	}
	ptr ++;
	//parse the value for day
	while (*ptr != '/') {
		date1 [1] *= 10;
		date1 [1] += (int) *ptr;
		date1 [1] -= (int) '0';
		ptr ++;
	}
	ptr ++;
	//parse the value for year
	while (*ptr != '\n') {
		date1 [2] *= 10;
		date1 [2] += (int) *ptr;
		date1 [2] -= (int) '0';
		ptr ++;
	}
	printf("'1' to type another date. '2' to type an amount of days.\n");
	scanf("%c",&type);
	//another date stored in variable date2. The result will be in variable days.
	if (((int) type) % 2) { //if the character has an odd ascii value (like '1').
		ptr = dateInput;
		printf("Enter the other date in the form mm/dd/yyyy\n");
		for (int i = 0; i < 15; i ++) {
			scanf("%c", ptr);
			if (*ptr == '\n') {
				if (i > 0) { //end at the newline character
					break;
				}
				else { //in case there was a lingering newline in stdin
					i --;
					ptr --;
				}
			}
			ptr ++;
		}
		ptr = dateInput;
		//parse the value for month
		while (*ptr != '/') {
			date2 [0] *= 10;
			date2 [0] += (int) *ptr;
			date2 [0] -= (int) '0';
			ptr ++;
		}
		ptr ++;
		//parse the value for day
		while (*ptr != '/') {
			date2 [1] *= 10;
			date2 [1] += (int) *ptr;
			date2 [1] -= (int) '0';
			ptr ++;
		}
		ptr ++;
		//parse the value for year
		while (*ptr != '\n') {
			date2 [2] *= 10;
			date2 [2] += (int) *ptr;
			date2 [2] -= (int) '0';
			ptr ++;
		}

		//begin calculating distance
		if (date2 [2] < date1 [2]) { //first year is higher
			negative = 1;
		}
		else if (date2 [2] > date1 [2]) { //second year is higher
			negative = 0;
		}
		else if (date2 [0] < date1 [0]) { //years match, first month is higher
			negative = 1;
		}
		else if (date2 [0] > date1 [0]) { //years match, second month is higher
			negative = 0;
		}
		else if (date2 [1] < date1 [1]) { //years and months match, first day is higher
			days = date2 [1] - date1 [1];
			negative = 2; //to prevent any further calculation. this is already solved
		}
		if (negative < 2) {
			
		}
		printf("%i\n",days);
	}
	//an amount of days stored in variable days. Result will be in variable date2.
	else { //if the character has an even ascii value (like '2').
		printf("How many days (negative for before, positive for after).\n");
		scanf("%i",&days);

		//begin calculating date
		negative = (days < 0);
		for (int i = 0; i < 3; i ++) { //initally assign the result to the original. It will get manipulated later
			date2 [i] = date1 [i];
		}
		/** 
		 * my manipulation of days involves a weird concept, so here's my explanation
		 * a date can be in the previous month with the number being continued from that month.
		 * for example, Oct 2 can be treated as Sept 32
		 * one step further would be Nov 2 as Sept 63
		 * one step even further would treat Jan 2 2010 as Dec 33 2009
		 * so when the user input for day is negative, I can infinitely increase the day value until a straight subtraction is possible
		 * or if they enter something positive, I can just add it to the day value, then determine what month and year it's in
		 */
		if (negative) {
			days = -days; //set days to absolute value
			while (date2 [1] <= days) { //increase the value of date2 [1] until variable days can be subtracted from it
				date2 [0] --; //decrement month first, because the length of the earlier month matters
				if (!date2 [0]) { //check if month has reached 0. If so, decrement year and reset month to December
					date2 [0] = 12;
					date2 [2] --;
				}
				date2 [1] += months [date2 [0]]; //add month length to the date
				//the previous line only increases 28 for February regardless
				//this part adds the 29th if it's a leap year
				if (leap (date2 [2]) && (date2 [0] == 2)) { 
					date2 [1] ++;
				}
			}
			date2 [1] -= days;
		}
		else {
			date2 [1] += days;
			while (date2 [1] > months [date2 [0]]) { //waits for date2 to represent a true date
				if (date2 [0] == 2 && date2 [1] == 29 && leap (date2 [2])) {
					break; //this means it landed on Feb 29
				}
				date2 [1] -= months [date2 [0]]; //subtract days first because the earlier month is what matters
				//the previous part subtracts 28 for February no matter what
				//this part subtracts one more day if it's a leap year
				if (leap (date2 [2]) && (date2 [0] == 2)) {
					date2 [1] --;
				}
				date2 [0] ++;
				if (date2 [0] == 13) { //if months goes out of range, it loops back to one and increments year
					date2 [0] = 1;
					date2 [2] ++;
				}
			}
		}
		printf("%i/%i/%i\n",date2 [0], date2 [1], date2 [2]);
	}
	return 0;
}

int leap (int year) {
	if (divisible (year, 400)) {
		return 1;
	}
	if (divisible (year, 100)) {
		return 0;
	}
	if (divisible (year, 4)) {
		return 1;
	}
	return 0;
}

int divisible (int dividend, int divisor) {
	return (!(dividend % divisor));
}
