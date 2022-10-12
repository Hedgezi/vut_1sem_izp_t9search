#include <stdio.h>
#include <string.h>
#include <ctype.h> // tolower()
#include <stdbool.h>

/* checkNumbers
Finds all fitted substrings in checked string

Arguments:
    int lencs, char checkedstring[]: Length and the string which we will find through and find example string
    int lenex, char example[]: Length and the string, which we will use to find substrings in the checked string

Returns: 

*/
void checkNumbers(int lencs, char checkedstring[], int lenex, char example[]) {
    bool fullyFits;
    for (int i = 0; i < lencs - lenex; i++) {
        fullyFits = true;
        if (checkedstring[i] == example[0]) {
            printf("good %i\n", i);
            for (int j = 1; j < lenex; j++) { // if first element of find_substring (example[]) matches some element in checked string, we will check if next chars in checked string matches other chars in example substring
                if (checkedstring[i+j] != example[j]) { 
                    fullyFits = false;
                    break;
                }
            }
            if (fullyFits) {
                printf("true good %i\n", i);
            }
        }
    }
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
    // checking the number of given arguments in shell
    if (argc == 1) {
        scanf("%100[^\n]%*c", nameline);
        scanf("%100[^\n]%*c", telline);
        charsToLowercase(strlen(nameline), nameline);
        printf("%s, %s\n", nameline, telline);
    }
    else if (argc > 3) {
        printf("incorrect number of arguments!\n");
    }
    while (scanf("*") != EOF)
    {
        scanf("%100[^\n]%*c", nameline); // to not give attention to spaces and start to check new string only after \n
        scanf("%100[^\n]%*c", telline);
        charsToLowercase(strlen(nameline), nameline);
        printf("%s, %s\n", nameline, telline);
        translateToNumbers(strlen(nameline), nameline, namenumline);
        checkNumbers(strlen(namenumline), namenumline, strlen(argv[1]), argv[argc-1]);
    }
    return 0;
}