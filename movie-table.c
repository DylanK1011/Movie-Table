#include "student_functions.h"
#include <stdlib.h>
#include <stdio.h>

/* This function takes a string as input and removes
 * leading and trailing whitespace including spaces
 * tabs and newlines. It also removes multiple internal
 * spaces in a row. Arrays are passed by reference.
 */
void Clean_Whitespace(char str[]) {
    int size = Get_Array_Size(str);                   // Size of str, excluding terminating '\0'

    // Determine first non whitespace character
    int cntrBefore = 0;                               // Pointer first non whitespace character
    char x = str[cntrBefore];                         // Improves code compactness
    while (x == ' ' || x == '\n' || x == '\t') {
        ++cntrBefore;                                 // Skip any space character and increment pointer
        x = str[cntrBefore];
    }

    // Determine last non whitespace character
    int cntrAfter = size-1;                           // Pointer to last non whitespace character
    x = str[cntrAfter];                               // Improves code compactness
    while (x == ' ' || x == '\n' || x == '\t') {
        --cntrAfter;                                  // Skip any space character and decrement pointer
        x = str[cntrAfter];
    }

    // Remove whitespace
    int spaceCounter = 0;                             // Count number of spaces
    for (int i = cntrBefore; i < cntrAfter+1; ++i) {
        while (str[i] == ' ' && str[i+1] == ' ') {    // While the next two characters are spaces...
            ++spaceCounter;                           // increment space counter to update index offset
            ++i;                                      // increment pointer to skip excess space
        }
        str[i-cntrBefore-spaceCounter] = str[i];      // (i - cntrBefore): begins at 0, increments by 1 to fill every index;
                                                      // (-spaceCounter): provides an offset for characters after excess space
    }

    str[cntrAfter-cntrBefore-spaceCounter+1] = '\0';  // Add terminating '\0' to tell machine when the string ends
    return;
}

/* This helper function calculates the size of an array
 * excluding the final null character
 */
int Get_Array_Size(char arr[]) {
    int i = 0;
    while (arr[i] != '\0')  // Increments index until '\0' is found
        i++;
    return i;
}

/* This function takes a string and makes the first
 * letter of every word upper case and the rest of the
 * letters lower case
 */
void Fix_Case(char str[]) {
    int size = Get_Array_Size(str);      // Size of str, excluding terminating '\0'

    // Set first character
    if (Char_Case(str[0]) == 0)          // Check that the first character is a lower case letter
        str[0] = str[0]-32;              // Set first character to upper case

    // Set rest of string
    for (int i = 1; i < size; ++i) {

        // Start of word
        if (str[i] == ' ') {             // Implies str[i+1] is the start of a new word
            ++i;                         // Consider next letter (until corresponding else, i now refers to character after space)
            if (Char_Case(str[i]) == 0)  // Check that the first character is a lower case letter
                str[i] = str[i] - 32;    // Set first character to upper case

        // Not start of word
        } else {
            if (Char_Case(str[i]) == 1)  // Check that character is upper case
                str[i] = str[i] + 32;    // Change them to lower case
        }
    }

    str[size] = '\0';                    // Add terminating '\0' to tell machine when the string ends
    return;
}

/* This helper function determines the case of characters
 * by interpreting their ASCII representations
 */
int Char_Case(char c) {
    if (c <= 122 && c >= 97)  // Lower case
        return 0;
    if (c <= 90 && c >= 65)   // Upper case
        return 1;
    return -1;                // Not a letter
}

/* this function takes a string and returns the
 * integer equivalent
 */
int String_To_Year(char str[]) {
    int size = Get_Array_Size(str);                 // Size of str, excluding terminating '\0'
    int year = 0;
    for (int i = 0; i < size; ++i) {
        year += (str[i]-48) * Power(10, size-i-1);  // Subtract 48 to correct ASCII offset
    }
    return year;
}

/* this function takes the name of a
 * director as a string and removes all but
 * the last name.  Example:
 * "Bucky Badger" -> "Badger"
 */
void Director_Last_Name(char str[]) {
    int size = Get_Array_Size(str);     // Size of str, excluding terminating '\0'
    int i = size - 1;                   // Pointer to str that begins at final character (besides '\0')
    while (i > 0 && str[i-1] != ' ') {  // Search for ' ', which implies the start of the last name
        --i;
    }

    for (int j = i; j < size; ++j) {    // Copy values back to str considering offset indices
        str[j-i] = str[j];
    }
    str[size-i] = '\0';                 // Add terminating '\0' to tell machine when the string ends

    return;
}

/* this function takes the a string and returns
 * the floating point equivalent
 */
float String_To_Rating(char str[]) {
    int size = Get_Array_Size(str);                             // Size of str, excluding terminating '\0'
    float rating = 0.0;

    // Determine location of decimal
    int decimalPtr = 0;
    while (decimalPtr < size && str[decimalPtr] != '.') {       // Once decimal is found, stop incrementing
        decimalPtr++;
    }

    // Add digits
    int i = 0;                                                  // Pointer to array indices
    while (i < size) {

        // Integer addition
        if (i < decimalPtr) {
            rating += (str[i]-48) * Power(10, decimalPtr-i-1);  // (decimalPtr-i) Determines how many spaces before the decimal point a digit is
                                                                // (-1) Reflects that the digit immediately to the left of decimal point is to the power of 0,
                                                                // while (decimalPtr-(decimalPtr-1) -  1
        }

        // Fractional addition
        else if (i > decimalPtr) {
            rating += (str[i]-48) * Power(10, decimalPtr-i);   // (decimalPtr-i) Determines how many spaces after the decimal point a digit is
                                                               // Does not subtract by one because the digit
        }
        i++;
    }
    return rating;
}

/* this function takes a string representing
 * the revenue of a movie and returns the decimal
 * equivlaent. The suffix M or m represents millions,
 * K or k represents thousands.
* example: "123M" -> 123000000
*/
long long String_To_Dollars(char str[])  {
    int size = Get_Array_Size(str);                         // Size of str, excluding terminating '\0'
    long long revenue = 0;
    for (int i = 0; i < size-1; ++i)
        revenue += (str[i]-48) * Power(10, size-i-2);       // Multiplies the int stored in str[i] by 10 raised to the power of (size-i-3)
                                                            // (size - i) takes into account the highest power possible, 10^size, and subtracts the pointer
                                                            // that effectively reduces result by a power of ten
                                                            // (-2) takes into account the '\0' terminator and ('K' or 'M')

    if (str[size-1] == 'M' || str[size-1] == 'm') {         // Case: Million
        revenue *= 1000000;
    } else if (str[size-1] == 'K' || str[size-1] == 'k') {  // Case: Thousand
        revenue *= 1000;
    } else {                                                // Case: Final character is a digit
        revenue *= 10;
        revenue += (str[size-1]-48);
    }
    return revenue;
}

/* This helper function multiples
 * a base integer by an exponent
 */
float Power(int base, int exponent) {
    float result = 1.0;
    if (exponent == 0)         // Anything raised to 0 equals 1
        return 1;

    // Positive exponent
    if (exponent > 0) {
        while (exponent > 0) {
            result *= base;
            --exponent;
        }
    }

    // Negative exponent
    if (exponent < 0) {
        while (exponent < 0) {
            result /= base;
            ++exponent;
        }
    }
    return result;
}

/* This helper function determines
 * the longest string in an array
 */
int Greatest_String_Length(char strArr[10][1024]) {
    int longest = Get_Array_Size(strArr[0]);        // Initialize longest to size of first string in array
    for (int i = 1; i < 10; ++i) {                  // Loop through remaining strings
        if (Get_Array_Size(strArr[i]) > longest)    // If a string is longer than the previous longest...
            longest = Get_Array_Size(strArr[i]);    // Update longest
    }
    return longest;
}

/* This helper function determines
 * which of two integers is greater
 */
int Maximum(int a, int b) {
    if (a >= b)
        return a;
    return b;
}

/* This function takes the array of strings representing
 * the csv movie data and divides it into the individual
 * components for each movie.
 * Use the above helper functions.
 */
void Split(char csv[10][1024], int num_movies, char titles[10][1024], int years[10], char directors[10][1024], float ratings[10], long long dollars[10]) {
    int commas[50];                               // Storage space for indices of every comma in csv
    int commaCounter;                             // Count commas for each string in csv

    // Loop through every string in csv
    for (int i = 0; i < num_movies; ++i) {
        commaCounter = 0;

        // Locate commas
        for (int j = 0; j < 1024; ++j) {
            if (csv[i][j] == ',') {
                commas[5*i+commaCounter] = j;     // (5*i+commaCounter) considers there are 5 commas per string in csv,
                                                  // so 5*i is the first comma in a string, and commaCounter is an offset
                commaCounter++;
            }
        }

        // Comma placements in csv[i]
        // Increases readability
        int a = commas[5*i];                      // 1st comma in csv[i]
        int b = commas[5*i+1];                    // 2nd
        int c = commas[5*i+2];                    // 3rd
        int d = commas[5*i+3];                    // 4th
        int e = commas[5*i+4];                    // 5th

        // Split Title
        char title[a+1];                          // Length determined by counting every character before the first comma (plus one for '\0')
        for (int k = 0; k < a; ++k)               // Loop through every character from beginning of string up to first comma
            title[k] = csv[i][k];                 // Copy corresponding values from CSV into title
        title[a] = '\0';

        // Run operations on title
        Clean_Whitespace(title);
        Fix_Case(title);
        for (int m = 0; m <= a; ++m)
            titles[i][m] = title[m];              // Add fixed title to array


        // Split Year
        char year[b-a];                           // Length determined by counting every character between the first and second comma
        for (int k = a+1; k < b; ++k) {           // Loop through every character between first and second comma
            year[k-(a+1)] = csv[i][k];            // Copy corresponding values from CSV into title
        }
        year[b-a-1] = '\0';

        // Run operations on year
        Clean_Whitespace(year);
        years[i] = String_To_Year(year);          // Add fixed year to array


        // Split Director
        char director[d-c];
        for (int k = c+1; k < d; ++k)             // Loop through every character between third and fourth comma
            director[k-(c+1)] = csv[i][k];        // Copy corresponding values from CSV into director
        director[d-c-1] = '\0';

        // Run operations on director
        Clean_Whitespace(director);
        Fix_Case(director);
        Director_Last_Name(director);
        for (int m = 0; m <= d-c; ++m) {
            directors[i][m] = director[m];        // Add fixed director to array
        }


        // Split Rating
        char rating[e-d];                         // Length determined by counting every character between the fourth and fifth comma
        for (int k = d+1; k < e; ++k) {           // Loop through every character between fourth and fifth comma
            rating[k-(d+1)] = csv[i][k];          // Copy corresponding values from CSV into rating
        }
        rating[e-d-1] = '\0';

        // Run operations on rating
        Clean_Whitespace(rating);
        ratings[i] = String_To_Rating(rating);    // Add fixed rating to array


        // Split Revenue
        int s = Get_Array_Size(csv[i])-1;         // Final index of string
        char revenue[s-e-1];                      // Length determined by counting every character between the fifth comma and end of string
        for (int k = e+1; k < s; ++k)             // Loop through every character between the fifth comma and end of string
            revenue[k-(e+1)] = csv[i][k];         // Copy corresponding values from CSV into revenue
        revenue[s-e-2] = '\0';

        // Run operations on revenue
        Clean_Whitespace(revenue);
        dollars[i] = String_To_Dollars(revenue);  // Add fixed revenue to array
    }
    return;
}

/* This function prints a well formatted table of
 * the movie data
 * Row 1: Header - use name and field width as below
 * Column 1: Id, field width = 3, left justified
 * Column 2: Title, field width = lenth of longest movie + 2 or 7 which ever is larger, left justified, first letter of each word upper case, remaining letters lower case, one space between words
 * Column 3: Year, field width = 6, left justified
 * Column 4: Director, field width = length of longest director last name + 2 or 10 (which ever is longer), left justified, only last name, first letter upper case, remaining letters lower case
 * column 5: Rating, field width = 5, precision 1 decimal place (e.g. 8.9, or 10.0), right justified
 * column 6: Revenue, field width = 11, right justified
 */
void Print_Table(int num_movies, char titles[10][1024], int years[10], char directors[10][1024], float ratings[10], long long dollars[10]) {
    int maxMovieFormat = Maximum(Greatest_String_Length(titles) + 2, 7);
    int maxNameFormat = Maximum(Greatest_String_Length(directors) + 2, 10);

    printf("%-3s%-*s%-6s%-*s%-6s%11s\n", "ID", maxMovieFormat, "Title", "Year", maxNameFormat, "Director", "Rating", "Revenue");
    for (int i = 0; i < num_movies; i++) {
        printf("%-3d%-*s%-6d%-*s%-6.1f%11lli\n", i+1, maxMovieFormat, titles[i], years[i], maxNameFormat, directors[i], ratings[i], dollars[i]);
    }
    return;
}
