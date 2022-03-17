#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "route-records.h"

/*
    Nikhil Kapoor - Project 2
    This was my second project for CS 1714: Intro to Comp Sci II. The task here was to use FILE* variables and Strings in C to
    write a program simulating a menu for airline travel, that would allow the user to search through information on airlines
    from either the route, departings, arrivals, or by directly looking up the airline. Edits have been made to avoid copyright
    issues and such. 
*/
/* main function */
int main(int argc, char* argv[]) {
    RouteRecord* mainR = NULL; // pointer to struct array
    FILE* mainFile = NULL; // file pointer
    int userInput; // user input for  menu
    char userString[5]; // user string for atoi
    int uniqueRoutes; // Unique routes counter
    char userKey1[50]; // user input for searching by ORIGIN, DESTINATION, or AIRLINE
    char userKey2[50]; // user input for searching by ROUTE
    int clearChar; // integer for clearing buffer (professional programming does this a lot)
    SearchType mainST; // main SearchyType object

    if (argc < 2) {
        printf("ERROR: Missing file name\n");
        return 1;
    }

    printf("Opening passenger-data.csv...\n");
    mainFile = fopen(argv[1], "r");
    if (argv[1] == NULL) {
        printf("ERROR: Could not open file\n");
        return -1;
    }

    mainR = createRecords(mainFile);
    uniqueRoutes = fillRecords(mainR, mainFile);
    fclose(mainFile);
    printf("Unique routes operated by airlines: %d\n", uniqueRoutes);

    while (userInput != 5) { // Infinite loop

        printMenu(); // prints menu
        scanf("%s", userString); // takes user's input as string
        if (atoi(userString) == 0) {
            printf("Invalid input.\n"); // if user input isn't an integer, print this
        }
        else {
            userInput = atoi(userString); // turns userString into input for switch case
            switch(userInput) {
                case 1:
                mainST = ROUTE;
                    printf("Enter origin: ");
                    scanf("%s", userKey1);
                    printf("Enter destination: ");
                    scanf("%s", userKey2);
                    printf("Searching by route...\n");
                    searchRecords(mainR, uniqueRoutes, userKey1, userKey2, ROUTE);
                    break;
                case 2:
                    mainST = ORIGIN;
                    printf("Enter origin: ");
                    scanf("%s", userKey1);
                    printf("Searching by origin...\n");
                    searchRecords(mainR, uniqueRoutes, userKey1, userKey2, ORIGIN);
                    break;
                case 3:
                    mainST = DESTINATION;
                    printf("Enter destination: ");
                    scanf("%s", userKey1);
                    printf("Searching by destination...\n");
                    searchRecords(mainR, uniqueRoutes, userKey1, userKey2, DESTINATION);
                    break;
                case 4:
                    mainST = AIRLINE;
                    printf("Enter airline: ");
                    scanf("%s", userKey1);
                    printf("Searching by airline...\n");
                    searchRecords(mainR, uniqueRoutes, userKey1, userKey2, AIRLINE);
                    break;
                case 5:
                    printf("Good-bye!\n");
                    free(mainR);
                    break;
                default:
                    printf("Invalid choice\n");
                    break;
            }
        }

    }

     return 0;
}
