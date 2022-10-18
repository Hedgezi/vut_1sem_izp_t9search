#include <stdio.h>
#include <string.h>
#include <ctype.h> // tolower(), toupper()
#include <stdbool.h>
#define max(a,b) (a > b)? a : b

/* checkNumbers
Finds all fitted letters from substring in checked string, even if they have any symbols between them

Arguments:
    int lencs, char checkedstring[]: Length and the string which we will find through and find example string
    int lenex, char example[]: Length and the string, which we will use to find substrings in the checked string
Returns: bool: true, if found at least one match, false, if none was found
*/
bool checkNumbers(int lencs, char checkedstring[], int lenex, char example[]) {
    int cursymbolinex = 0;
    for (int i = 0; i < lencs; i++) {
        if (cursymbolinex == lenex) {
            return true;
        }
        if (checkedstring[i] == example[cursymbolinex]) {
            cursymbolinex++;
        }
    }
    if (cursymbolinex == lenex) {
            return true;
    }
    return false;
}

/* lcsfunc
Finds longest common subsequence

Arguments:
    int lencs, char checkedstring[], int lenex, char example[]: 2 engths and 2 strings for which we will find LCS
Returns: 
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
            lcs[i][j] = (checkedstring[i] == example[j]) ? lcs[i-1][j-1] + 1 : max(lcs[i-1][j], lcs[i][j-1]);
        }
    }
    printf("lcs: %i\n", lcs[lencs][lenex]);
    return lcs[lencs][lenex];
}

bool levenstein(int lencs, char checkedstring[], int lenex, char example[], int posserr) {
    return (lcsfunc(lencs, checkedstring, lenex, example) + posserr > lenex) ? false : true;
}

/* translateToNumbers
Translate given string from letters to numbers, based on old mobile phone's keyboard

Arguments:
    int len, char given_str[]: Length and the string, that it will translate
    char number_str[]: The string, to which it will put the translated result
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
    char nameline[101];
    char telline[101];
    char namenumline[101];
    int posserr = 2;
    bool atleastoneentry = false;
    // checking the number of given arguments in shell
    if (argc == 1) {
        while (scanf("*") != EOF) {
            scanf("%100[^\n]%*c", nameline);
            scanf("%100[^\n]%*c", telline);
            charsToLowercase(strlen(nameline), nameline);
            printf("%s, %s\n", nameline, telline);
        }
        return 0;
    }
    else if (argc > 3) {
        printf("incorrect number of arguments!\n");
        return 0;
    }
    else { // checking if given argument is number
        for (unsigned long int i = 0; i < strlen(argv[1]); i++) {
            if (argv[1][i] < '0' || argv[1][i] > '9') {
                printf("given argument isn't a number (\n");
                return 0;
            }
        }
    }
    while (scanf("*") != EOF)
    {
        scanf("%100[^\n]%*c", nameline); // to not give attention to spaces and start to check new string only after \n
        scanf("%100[^\n]%*c", telline);
        for (unsigned long int i = 0; i < strlen(telline); i++) {
            if (telline[i] < '0' || telline[i] > '9') {
                printf("incorrect input data\n");
                return 0;
            }
        }
        charsToLowercase(strlen(nameline), nameline);
        translateToNumbers(strlen(nameline), nameline, namenumline);
        printf(": %s\n", namenumline);
        if (checkNumbers(strlen(namenumline), namenumline, strlen(argv[1]), argv[argc-1]) || checkNumbers(strlen(telline), telline, strlen(argv[1]), argv[1])){
            printf("%s, %s\n", nameline, telline);
            atleastoneentry = true;
        }
        if (levenstein(strlen(namenumline), namenumline, strlen(argv[1]), argv[argc-1], posserr) || levenstein(strlen(telline), telline, strlen(argv[1]), argv[1], posserr)){
            printf("%s, %s\n", nameline, telline);
            atleastoneentry = true;
        }        
    }
    if (!atleastoneentry) {
        printf("Not found\n");
    }
    return 0;
}