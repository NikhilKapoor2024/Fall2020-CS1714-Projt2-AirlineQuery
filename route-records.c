#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "route-records.h"

/* createRecords() function */
RouteRecord* createRecords (FILE* fileIn) {
    
    int count = 0; // count of records (minus the header)
    RouteRecord* r = NULL; // pointer for dynamic memory allocated array
    char buffy[500]; // array for holding the first line
    char buffer[100]; // array for reading the lines
    int i; // Outer loop counter
    int j; // Inner loop counter
    
    fgets(buffy, 100, fileIn); // holds the first line in the csv file (the headers)
    while (fgets(buffer, 100, fileIn) != NULL) {
        count = count + 1;
    }
    // printf("Records in excel file: %d\n", count); <--- This print statement is used to check the count ineger to compare to the number of unique records that will be printed out into the array

    r = (RouteRecord*)malloc(count * sizeof(RouteRecord));
    
    for (i = 0; i < count; i++) {
        for (j = 0; j < 6; j++) {
            r[i].passCount[j] = 0; // initializes each element in the passCount struct array to 0
        }
    }

    rewind(fileIn);

    return r;
}

/* fillRecords() function */
int fillRecords(RouteRecord* r, FILE* fileIn) {

    int records = 0; // number of records used in the RouteRecords array (will be less than what's actually in the csv file since not all records in the original CSV file will be entered into the array)
    char buffer[500]; // array for parsing in data (500 char's max per line)
    char buff[500]; // for canceling out first line
    char actualArray[500]; // Actual record for route array
    int tempMonth; // Temporarily stores month for array
    char tempOrigin[4]; // Temp for Origin
    char tempDestination[4]; // Temp for Destination
    char tempAirline[3]; // Temp for Airline
    int tempPassCount = 0; // Temp for passenger count for that month
    int i = 0; // counter for length
    int j = 0; // counter for passCount
    int month; // for months
    char tempType[50]; // Temp for type
    char type[50]; // Actual type
    int indxStore; // stores index if findAirlineRoute returns an index

    fgets(buff, 500, fileIn); // cancels out header row
    while (fgets(buffer, 500, fileIn) != NULL) {
        sscanf(buffer, "%d, %[^,], %[^,], %[^,], %[^,], %d", &tempMonth, tempOrigin, tempDestination, tempAirline, tempType, &tempPassCount);
        i++;
        indxStore = findAirlineRoute(r, i, tempOrigin, tempDestination, tempAirline, 0); // stores return value for findAirlineRoute in indxStore
        if (indxStore == -1) {
            strcpy(r[records].origin, tempOrigin);
            strcpy(r[records].destination, tempDestination);
            strcpy(r[records].airline, tempAirline);
            r[records].passCount[tempMonth - 1] = tempPassCount; // array goes 0 1 2 3 4 5, but excel goes 1 2 3 4 5 6, hence the tempMonth - 1
            records++;
        }
        else {
             r[indxStore].passCount[tempMonth - 1] = tempPassCount; // stores into the current month (indxStore)
        }
    }

    return records;
}

/* findAirlineRoute() function */
int findAirlineRoute(RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int currIdx) {

    if (currIdx >= length) {
        return -1;                  // Base Case 1: The current index has gone past the max length and has not found any similar indexes
    }
    else if (strcmp(r[currIdx].origin, origin) == 0 && strcmp(r[currIdx].destination, destination) == 0 && strcmp(r[currIdx].airline, airline) == 0){
        return currIdx;            // Base Case 2: The current index has matching fields
    }
    else {
        return findAirlineRoute(r, length, origin, destination, airline, (currIdx + 1)); // Recursion case: The current index can't find simularities in one line, but may find more in others
    }
}

/* searchRecords() function */
void searchRecords(RouteRecord* r, int length, const char* key1, const char* key2, SearchType st) {

    int i = 0; // For traversing arrray
    int j = 0; // For passengers per month array
    int match = 0; // For counting search results
    int totalCount = 0; // For total passengers
    int monthlyCount[6] = {0, 0, 0, 0, 0, 0}; // array for monthly passenger counting
    int averagePass = 0; // Average Passangers per Month
    
    for (i = 0; i < length; i++) { // length, in the main function, will be the number of unique records
        switch (st) {
            // ORIGIN CASE
            case ORIGIN:
                for (i = 0; i < length; i++) {
                    if (strcmp(key1, r[i].origin) == 0) {
                        for (j = 0; j < 6; j++) {
                            monthlyCount[j] += r[i].passCount[j]; // changes element values in monthlyCount array to add by the passengers of month "j"
                            totalCount += r[i].passCount[j]; // adds total passengers
                        }
                        printf("%s(%s-%s) ", r[i].airline, r[i].origin, r[i].destination); // prints matches in "AIRLINE (ORIGIN-DESTINATION)" format
                        match++; // increments match counter by 1
                    }
                }
                break;
            // DESTINATION CASE
            case DESTINATION:
                for (i = 0; i < length; i++) {
                    if (strcmp(key1, r[i].destination) == 0) {
                        for (j = 0; j < 6; j++) {
                            monthlyCount[j] += r[i].passCount[j];
                            totalCount += r[i].passCount[j];
                        }
                        printf("%s(%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
                        match++;
                    }
                }
                break;
            // AIRLINE CASE
            case AIRLINE:
                for (i = 0; i < length; i++) {
                    if (strcmp(key1, r[i].airline) == 0) {
                        for (j = 0; j < 6; j++) {
                            monthlyCount[j] += r[i].passCount[j];
                            totalCount += r[i].passCount[j];
                        }
                        printf("%s(%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
                        match++;
                    }
                }
                break;
            // ROUTE CASE
            case ROUTE:
                for (i = 0; i < length; i++) {
                    if (strcmp(key1, r[i].origin) == 0 && strcmp(key2, r[i].destination) == 0 ) {
                        for (j = 0; j < 6; j++) {
                            monthlyCount[j] += r[i].passCount[j];
                            totalCount += r[i].passCount[j];
                        }
                        printf("%s(%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
                        match++;
                    }
                }
                break;
        }
    }
         
        printf("\n%d matches were found.", match);
        printf("\n\nStatistics\n");
        printf("Total Passengers:\t\t  %d\n", totalCount);
        for (i = 0; i < 6; i++) {
            printf("Total Passengers for Month %d:\t  %d\n", (i + 1), monthlyCount[i]); // prints number of passengers per month
        }
        averagePass = totalCount / 6;
        printf("\nAverage Passengers per Month:\t  %d\n", averagePass);

}

/* printRecords() function */
void printRecords(RouteRecord* r, int length) {

    int i; // counter for for loop

    for (i = 0; i < length; i++) {
        printf("%s(%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
    }

}

/* printMenu() function */
void printMenu() {
    
    printf("\n\n######### Airline Route Records Database MENU #########\n");
    printf("1. Search by Route\n");
    printf("2. Search by Origin Airport\n");
    printf("3. Search by Destination Airport\n");
    printf("4. Search by Airline\n");
    printf("5. Quit\n");
    printf("Enter your selection: ");

}
