#include <stdio.h>
#include <ctype.h>

#define NUM_AM    128

typedef struct operator{
    unsigned char op : 6; //6bits enough for 64 numbers, if you use symbol that have bigger number in ASCII, just remove ": 6", and ": 2"
    unsigned char pr : 2; //priority of the operator. 2bits enough for numbers in range [0; 3], enough for what we need.
} OP;

typedef struct tokens{
    double nums[NUM_AM];
    OP ops[NUM_AM -1];
} TOK;

// gets char that isn't space(' ') and returns it
char getC(void)
{
    char c;
    do{c=getchar();}while(c==' ');
    return c;
}

//solving the math example, and return result
double solver(TOK *tokens, int *numAm)
{
    TOK temp;
    double res, res_mul;
    int i=0, j=0;

    for(i; i<*numAm; ++i, ++j){
        if(tokens->ops[i].pr==1){
            res_mul=tokens->nums[i];
            while(tokens->ops[i].pr==1){
                switch (tokens->ops[i].op)
                {
                case '*': res_mul *= tokens->nums[++i];     break;
                case '/': res_mul /= tokens->nums[++i];     break;
                }
            }
            temp.nums[j]=res_mul;
            if (i < *numAm - 1) temp.ops[j] = tokens->ops[i];
            else temp.ops[j].op = 0;
        } else{
            temp.ops[j] = tokens->ops[i];
            temp.nums[j] = tokens->nums[i];
        }
    }

    res = temp.nums[0];
    for(int u=0; u<=j; ++u){
        switch(temp.ops[u].op)
        {
            case '+': res += temp.nums[u+1];    break;
            case '-': res -= temp.nums[u+1];    break;
        }
    }

    return res;
}

// the function that parses elements, and gives it to solver func
void parser(void)
{
    int numIndx=0, opIndx=0;// numIndx - index that needed to add numbers into numbers array, opIndx is the same as numIndx, but for operators
    double num, weight;
    char c;
    TOK tokens; 

    printf("Enter math example below:\n");

    do{
        c=getC();
        if(isdigit(c)){
            num=0;
            do{
                num = num*10+(c-'0');
                c=getC();
            }while(isdigit(c));

            if(c=='.'||c==','){// for real numbers
                c=getC();
                weight=0.1;
                do{
                    num = num+(c-'0')*weight;
                    weight*=0.1;
                    c=getC();
                }while(isdigit(c));
            }
            
            if(tokens.ops[opIndx-1].op == '-'){// it's better, if example is "-150", solver will return -150, instead of 150
                tokens.ops[opIndx-1].op = '+';
                tokens.nums[numIndx] = -num;
            } else
                tokens.nums[numIndx] = num;
            
            ++numIndx;
            ungetc(c, stdin);
        } else {
            switch(c){
                case '-': 
                case '+':
                    tokens.ops[opIndx].op = c;
                    tokens.ops[opIndx].pr = 0;
                    if(numIndx==0){ // if first symbol of example is operation, we make first digit equals 0, and moving to the next digit
                        tokens.nums[0]=0;
                        numIndx++;
                    }
                    ++opIndx;
                    break;
                case '/':
                case '*':
                    tokens.ops[opIndx].op = c;
                    tokens.ops[opIndx].pr = 1;
                    if(numIndx==0){
                        tokens.nums[0]=0;
                        numIndx++;
                    }
                    ++opIndx;                    break;
                default: printf("Err: Unknon symbol '%c'", c); return;
            }
        }
    }while(c!='='&&c!='\n');
    printf("Your answer is %.2f", solver(&tokens, &numIndx));
}

int main(void)
{
    parser();

    printf("\n\nPress any button to close the window.");
    int c;      while ((c = getchar()) != '\n' && c != EOF) { }     // to clear input buffer stdin
    getchar();      // to wait till the button is pressed
    return 0;
}