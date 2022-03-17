#ifndef ROUTE_RECORDS_H
#define ROUTE_RECORDS_H

/* RouteRecord struct */
typedef struct RouteRecord_struct {

    char origin[4];
    char destination[4];
    char airline[3];
    int passCount[6];

} RouteRecord;

/* SearchType enum */
typedef enum SearchType {

    ROUTE,
    ORIGIN,
    DESTINATION,
    AIRLINE

} SearchType;

/* ---------- Function prototypes ----------  */
/* 
    Function: createRecords
    ----------------------------
    Creates a count of the number of records in the csv file, minus the header record, and initializes each
    initial value for an array of 6 months to 0.
        inFile: FILE pointer
            Returns: pointer to dynamically allocated array of RouteRecord

*/
RouteRecord* createRecords(FILE*);

/*
    Function: fillRecords
    ---------------------------
    Enters data in csv file into RouteRecord struct array, and replaces indexes with the same origin
    and destination codes as well as the same airline.
        r: RouteRecord pointer to array
        inFile: FILE pointer
            Returns: actual number of RouteRecord's used in the array

*/
int fillRecords(RouteRecord*, FILE*);

/*
    Function: findAirlineRoute
    ---------------------------
    RECURSIVE function that finds a index in RouteRecords of the same origin, destination,
    and airline.
        r: pointer to array
        length: length of file
        origin: origin string
        destination: destination string
        airline: airline string
        curIdx: current index
            Returns: the matching indexes if found, -1 if no matching index is found, or recalls the function again
            to continue recursion
*/
int findAirlineRoute(RouteRecord*, int, const char*, const char*, const char*, int);

/*
    Function: searchRecords
    --------------------------
    Searches array for matching user input by Route, Origin, Destination, or Airline code and
    prints results.
        r: pointer to array
        length: length of file
        key1: pointer to user input (used in ORIGIN, DESTINATION, and AIRLINE path if searching by
        only either of those)
        key2: pointer to user input (used in ROUTE path, which uses both key1 and key2 to hold
        both ORIGIN and DESTINATION, respectively)
            Returns: nothing (void)

*/
void searchRecords(RouteRecord*, int, const char*, const char*, SearchType);

/*
    Function: printRecords
    --------------------------
    After searchRecords, this function prints the records. Actually doesn't get used outside of itself, but TA's will grade this.
        r: pointer to array
        length: counter to for loop for printing
            returns: nothing (void)
*/
void printRecords(RouteRecord*, int);

/*
    Function: printMenu
    -------------------------
    Prints menu UI for user to interact with
        Returns: nothing (void)
*/
void printMenu();

#endif
