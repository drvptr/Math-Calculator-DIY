#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct exersise{
    int num1;
    int num2;
    char operator;
} EXERCISE;

char getC(void)
{
    char c;
    do{c=getchar();}while(c==' '); 
    return c;
}

int main(void)
{
    EXERCISE ex;
    ex.num1 = 0 ;
    ex.num2 = 0 ;

    int res;
    char c;
    fputs("Enter your equation: ", stdout);
    do {
        c = getC();

        if(isdigit(c)){
            do{
                ex.num1 = ex.num1*10 + (c - '0');
                c = getchar();
            } while(isdigit(c));
    }

    if(c == '+' || c == '-' || c == '*' || c == '/'){
        ex.operator = c;
        c = getC();
        if(isdigit(c)){
            do{
                ex.num2 = ex.num2*10 + (c - '0');
                c = getchar();
            } while(isdigit(c));
        }
    }
    } while(c==' ');
    

    switch(ex.operator){
        case '+': res = ex.num1 + ex.num2;    break;
        case '-': res = ex.num1 - ex.num2;    break;
        case '*': res = ex.num1 * ex.num2;    break;
        case '/': res = ex.num1 / ex.num2;    break;
    }

    printf("First number: %d;\nSecond number: %d;\nOperation: %c;\nResult: %d;", ex.num1, ex.num2, ex.operator, res);

    return 0;
}