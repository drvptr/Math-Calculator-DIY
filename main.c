#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct exersise{
    double num1;
    char operator1;
    double num2;
    char operator2;
    double num3;
    char operator3; // I think i won't use it, but I need place for this unusable piece to be :(
} EXERCISE;


// Function to get non-space symbol from inputBuf
char getC(const char *inputBuf, int *i)
{
    char c;
    do { c = inputBuf[(*i)++]; } while (c == ' ');
    return c;
}

// Reads numbers and write them where you want.
double parser(double *num, const char *inputBuf, int *i, char *operator)
{
    *num = 0;
    char c = getC(inputBuf, i);
    if (isdigit(c)) {
        do {
            *num = *num * 10 + (c - '0');
            c = getC(inputBuf, i);
        } while (isdigit(c));
        if(c == '.' || c == ','){
            c = getC(inputBuf, i);
            do {
                double weight = 0.1;
                *num = *num + (c - '0') * weight;
                weight/=10;
                c = getC(inputBuf, i);
            } while (isdigit(c));
        }
        (*i)--;
    }

    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '\0') {
        *operator = c;
        c = getC(inputBuf, i);
    } else {
        printf("Error: Unknown symbol '%c'", c);
        return 1;
    }
    return 0;
}
double solver(EXERCISE *ex){
    double res;

    if((ex->operator3 == '=' || ex->operator3 == '\0') && (ex->operator2 == '*' || ex->operator2 == '/')){
        switch (ex->operator2) {
        case '*': res = ex->num2 * ex->num3; break;
        case '/': res = ex->num2 / ex->num3; break;
        }
    } else switch (ex->operator1) {
        case '+': res = ex->num1 + ex->num2; break;
        case '-': res = ex->num1 - ex->num2; break;
        case '*': res = ex->num1 * ex->num2; break;
        case '/': res = ex->num1 / ex->num2; break;
        }

    return res;
}
// Function that parse and solve math exercises from inputBuf.
int solve(const char *inputBuf)
{
    EXERCISE ex;
    int i = 0;
    

    parser(&ex.num1, inputBuf, &i, &ex.operator1);
    parser(&ex.num2, inputBuf, &i, &ex.operator2);
    parser(&ex.num3, inputBuf, &i, &ex.operator3);

    double res = solver(&ex);

    printf("First number: %.2f;\nSecond number: %.2f;\nThird number: %.2f;\nResult: %.2f;", ex.num1, ex.num2, ex.num3, res);
    return 0;
}

int main(void)
{
    char inputBuf[64];
    puts("Enter your equation:");
    fgets(inputBuf, 64, stdin);
    inputBuf[strcspn(inputBuf, "\n")] = '\0';

    solve(inputBuf);

    return 0;
}