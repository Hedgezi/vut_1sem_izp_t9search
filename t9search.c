#include <stdio.h>
#include <string.h>
#include <ctype.h> // tolower()
#include <stdbool.h>

void checkNumbers(int lencs, char checkedstring[], int lenex, char example[]) {
    bool fullyFits;
    for (int i = 0; i < lencs - lenex; i++) {
        fullyFits = true;
        if (checkedstring[i] == example[0]) {
            printf("good %i\n", i);
            for (int j = 1; j < lenex; j++) {
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
    if (argc == 1) {
        scanf("%100[^\n]%*c", nameline);
        scanf("%100[^\n]%*c", telline);
        charsToLowercase(strlen(nameline), nameline);
        printf("%s, %s\n", nameline, telline);
    }
    if (argc > 3) {
        printf("incorrect number of arguments!\n");
    }
    while (scanf("*") != EOF)
    {
        scanf("%100[^\n]%*c", nameline);
        scanf("%100[^\n]%*c", telline);
        charsToLowercase(strlen(nameline), nameline);
        printf("%s, %s\n", nameline, telline);
        translateToNumbers(strlen(nameline), nameline, namenumline);
        checkNumbers(strlen(namenumline), namenumline, strlen(argv[1]), argv[argc-1]);
    }
    // for (int i = 0; i < 101; i++){
    //     namenumline[i]= ' ';
    // }
    return 0;
}