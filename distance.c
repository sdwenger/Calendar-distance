/**
 * @version 2.0
 * @author Sullivan Wenger
 * The purpose of this project is to create
 * a program that calculates the distance
 * between two days or adds or subtracts an
 * amount of days from a given date.
 * So far, the program gets and parses all the data.
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main () {
	char date [15], *ptr, type;
	int data [6]; //0 is month1, 1 is day1, 2 is year1, 3 4 and 5 depend.
	ptr = date;
	for (int i = 0; i < 6; i ++) {
		data [i] = 0;
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
	ptr = date;	
	//parse the value for month
	while (*ptr != '/') {
		data [0] *= 10;
		data [0] += (int) *ptr;
		data [0] -= (int) '0';
		ptr ++;
	}
	ptr ++;
	//parse the value for day
	while (*ptr != '/') {
		data [1] *= 10;
		data [1] += (int) *ptr;
		data [1] -= (int) '0';
		ptr ++;
	}
	ptr ++;
	//parse the value for year
	while (*ptr != '\n') {
		data [2] *= 10;
		data [2] += (int) *ptr;
		data [2] -= (int) '0';
		ptr ++;
	}
	printf("'1' to type another date. '2' to type an amount of days.\n");
	scanf("%c",&type);
	//another date
	if (((int) type) % 2) {
		ptr = date;
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
		ptr = date;
		//parse the value for month
		while (*ptr != '/') {
			data [3] *= 10;
			data [3] += (int) *ptr;
			data [3] -= (int) '0';
			ptr ++;
		}
		ptr ++;
		//parse the value for day
		while (*ptr != '/') {
			data [4] *= 10;
			data [4] += (int) *ptr;
			data [4] -= (int) '0';
			ptr ++;
		}
		ptr ++;
		//parse the value for year
		while (*ptr != '\n') {
			data [5] *= 10;
			data [5] += (int) *ptr;
			data [5] -= (int) '0';
			ptr ++;
		}
	}
	//an amount of days
	else {
		printf("How many days (negative for before, positive for after).");
		scanf("%i",data + 4);
	}
	return 0;
}
