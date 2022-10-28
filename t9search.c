#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> // tolower(), toupper()
#include <stdbool.h>
#define max(a,b) (a > b)? a : b

/* xvoron03
https://github.com/Hedgezi/t9search
Hledání přerušených posloupností znaků bez parametru -s.
*/

/* lcsfunc
Finds longest common subsequence, using methods of dynamic programming

Arguments:
    int lencs, char checkedstring[], int lenex, char example[]: 2 lengths and 2 strings for which we will find LCS
Returns: int: longest common subsequence
*/
int lcsfunc(int lencs, char checkedstring[], int lenex, char example[]) {
    int lcs[lencs+1][lenex+1];
    for (int i = 0; i < lencs+1; i++) {
        lcs[i][0] = 0;
    }
    for (int j = 0; j < lenex+1; j++) {
        lcs[0][j] = 0;
    }
    for (int i = 1; i < lencs+1; i++) {
        for (int j = 1; j < lenex+1; j++) {
            lcs[i][j] = (checkedstring[i-1] == example[j-1]) ? lcs[i-1][j-1] + 1 : max(lcs[i-1][j], lcs[i][j-1]);
        }
    }
    return lcs[lencs][lenex];
}

/* levenstein
This function checks if checked string matches an example or if posserr was given, count it

Arguments:
    int lencs, char *checkedstring, int lenex, char *example: 2 lengths and 2 strings for which we will check if it fits matched arguments
Returns: bool: true, if fits, false if doesn't
*/
bool levenstein(int lencs, char *checkedstring, int lenex, char *example, int posserr) {
    return (lcsfunc(lencs, checkedstring, lenex, example) + posserr >= lenex) ? true : false;
}

/* checkIsNumber
This function checks if given string contains only numbers

Arguments:
    int length, char checkedstring[]: The length and the string, which we will check for containing only numbers
    bool plusIncluded: Does it counts that number can contain plus too
Returns: bool: false, if string contains something besides numbers, true, if it consists of numbers
*/
bool checkIsNumber(int length, char checkedstring[], bool plusIncluded) {
    if (plusIncluded && !((checkedstring[0] > '0' && checkedstring[0] < '9') || checkedstring[0] == '+')) { // plus must be only on start of phone number
        return false;
    }
    for (int i = 1; i < length; i++) {
        if (checkedstring[i] < '0' || checkedstring[i] > '9') {
            return false;
        }
    }
    return true;
}

/* translateToNumbers
Translate given string from letters to numbers, based on old mobile phone's keyboard

Arguments:
    int len, char given_str[]: Length and the string, that it will translate
    char number_str[]: The string, in which it will put the translated result
Returns: nothing
*/
void translateToNumbers(int len, char given_str[], char number_str[]) {   
    for (int i = 0; i < len; i++) {
        switch (given_str[i])
        {
        case 'a':
        case 'b':
        case 'c':
            number_str[i] = '2';
            break;
        case 'd':
        case 'e':
        case 'f':
            number_str[i] = '3';
            break;
        case 'g':
        case 'h':
        case 'i':
            number_str[i] = '4';
            break;
        case 'j':
        case 'k':
        case 'l':
            number_str[i] = '5';
            break;
        case 'm':
        case 'n':
        case 'o':
            number_str[i] = '6';
            break;
        case 'p':
        case 'q':
        case 'r':
        case 's':
            number_str[i] = '7';
            break;
        case 't':
        case 'u':
        case 'v':
            number_str[i] = '8';
            break;
        case 'w':
        case 'x':
        case 'y':
        case 'z':
            number_str[i] = '9';
            break;
        case '+':
            number_str[i] = '0';
            break;
        default:
            number_str[i] = given_str[i];
            break;
        }
    }
}

/* charsToLowercase
Checks the whole string and change uppercase chars to lowercase and writes it back to gived string

Arguments: 
    int len, char given_str[]: Length and the string, in which we need to lowercase symbols

Returns: nothing
*/
void charsToLowercase(int len, char given_str[]) {
    for (int i = 0; i < len; i++) {
        if (given_str[i] >= 'A' && given_str[i] <= 'Z') {
            given_str[i] = tolower(given_str[i]);
        }
    }
}

int main(int argc, char* argv[]) {
    char nameline[102];
    char telline[102];
    char namenumline[101];
    int posserr = 0;
    char *pexample; // pointer to argument, that contains example string
    int lenexample;
    bool atleastoneentry = false;

    // checking the number of given arguments in shell
    if (argc == 1) { // if 1 argument just show every contact in file
        while (scanf("*") != EOF) {
            if (scanf("%101[^\n]\n", nameline) == EOF || scanf("%101[^\n]\n", telline) == EOF) {
                fprintf(stderr, "(error) contact have only number or name\n");
                return 2;
            }
            if (strlen(nameline) == 101 || strlen(telline) == 101) {
                fprintf(stderr, "(error) too long contact (max 100 symbols)\n");
                return 3;
            }
            charsToLowercase(strlen(nameline), nameline);
            printf("%s, %s\n", nameline, telline);
        }
        return 0;
    }
    else if (argc == 3 || argc > 4) { // if count of arguments is incorrect
        fprintf(stderr, "(error) incorrect arguments! (use -l L, where L some int number)\n");
        return 1;
    }
    if (argc == 2 && !checkIsNumber(strlen(argv[1]), argv[1], false)) {
        fprintf(stderr, "(error) given argument must be a number!\n");
        return 1;
    }
    else {
        pexample = argv[1];
        lenexample = strlen(argv[1]);
    }
    if (argc == 4) { // checking where argument -l in given arguments
        if (strcmp(argv[1], "-l") == 0 && checkIsNumber(strlen(argv[2]), argv[2], false) && checkIsNumber(strlen(argv[3]), argv[3], false)) {
            pexample = argv[3];
            lenexample = strlen(argv[3]);
            posserr = atoi(argv[2]);
        }
        else if (strcmp(argv[2], "-l") == 0 && checkIsNumber(strlen(argv[1]), argv[1], false) && checkIsNumber(strlen(argv[3]), argv[3], false)) {
            pexample = argv[1];
            lenexample = strlen(argv[1]);
            posserr = atoi(argv[3]);
        }
        else {
            fprintf(stderr, "(error) incorrect usage of arguments! (specify L (num of possible errors) after -l)\n");
            return 1;
        }
    }

    while (scanf("*") != EOF)
    {
        if (scanf("%101[^\n]\n", nameline) == EOF || scanf("%101[^\n]\n", telline) == EOF) {
            fprintf(stderr, "(error) contact have only number or name\n");
            return 2;
        }
        if (strlen(nameline) == 101 || strlen(telline) == 101) {
            fprintf(stderr, "(error) too long contact (max 100 symbols)\n");
            return 2;
        }
        if (strlen(nameline) < strlen(pexample) && strlen(nameline) < strlen(pexample)) { // if given example string longer than contact
            continue; 
        }
        if (!checkIsNumber(strlen(telline), telline, true)) {
            fprintf(stderr, "(error) phone number contains not only numbers or plus on start\n");
            return 2;
        }
        charsToLowercase(strlen(nameline), nameline);
        translateToNumbers(strlen(nameline), nameline, namenumline);
        if (levenstein(strlen(namenumline), namenumline, lenexample, pexample, posserr) || levenstein(strlen(telline), telline, lenexample, pexample, posserr)){
            printf("%s, %s\n", nameline, telline);
            atleastoneentry = true;
        }
    }
    if (!atleastoneentry) { // if we haven't found any fitted contacts
        printf("Not found\n");
    }
    return 0;
}