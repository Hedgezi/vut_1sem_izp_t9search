#include <stdio.h>
#include <string.h>
#include <ctype.h> // tolower(), toupper()
#include <stdbool.h>

/* checkNumbers
Finds all fitted substrings in checked string

Arguments:
    int lencs, char checkedstring[]: Length and the string which we will find through and find example string
    int lenex, char example[]: Length and the string, which we will use to find substrings in the checked string
    char textmode, char textstring[]: if charmode == 't', than it will uppercase fitted substrings in textstring[]
Returns: bool: true, if found at least one match, false, if none was found
*/
bool checkNumbers(int lencs, char checkedstring[], int lenex, char example[], char textmode, char textstring[]) {
    bool fullyFits, oneMatch = false;
    int lastEntry = -10;
    for (int i = 0; i < lencs - lenex; i++) {
        fullyFits = true;
        if (checkedstring[i] == example[0]) {
            for (int j = 1; j < lenex; j++) { // if first element of find_substring (example[]) matches some element in checked string, we will check if next chars in checked string matches other chars in example substring
                if (checkedstring[i+j] != example[j]) { 
                    fullyFits = false;
                    break;
                }
            }
            if (fullyFits && lastEntry + lenex <= i) {
                // printf("true good %i\n", i);
                lastEntry = i;
                if (textmode == 't') {
                    oneMatch = true;
                    for (int j = 0; j < lenex; j++) {
                        textstring[i+j] = toupper(textstring[i+j]);
                    }
                }
                else {
                    return true;
                }
            }
        }
    }
    if (oneMatch) {
        return true;
    }
    else {return false;}
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
    bool atleastoneentry = false;
    // checking the number of given arguments in shell
    if (argc == 1) {
        scanf("%100[^\n]%*c", nameline);
        scanf("%100[^\n]%*c", telline);
        charsToLowercase(strlen(nameline), nameline);
        printf("%s, %s\n", nameline, telline);
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
        if (checkNumbers(strlen(namenumline), namenumline, strlen(argv[1]), argv[argc-1], 't', nameline) || checkNumbers(strlen(telline), telline, strlen(argv[1]), argv[1], 'n', "")){
            printf("%s, %s\n", nameline, telline);
            atleastoneentry = true;
        }
    }
    if (!atleastoneentry) {
        printf("Not found\n");
    }
    return 0;
}