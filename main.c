#include <stdio.h>
#include <string.h>

typedef float (*Solver_t)(float a, float b);

float add(float a, float b) { return a + b; }
float sub(float a, float b) { return a - b; }
float mul(float a, float b) { return a * b; }
float div(float a, float b) { return a / b; }

Solver_t Eval[256] = {
	['+']	= add,
	['-']	= sub,
	['*']	= mul,
	['/']	= div
};

typedef enum { INVALID, CHAR, FLOAT } toktype_t;

typedef struct {
	toktype_t type;
	union {
		char c;
		float f;
	} val;
} Token;


toktype_t GetToken(Token *t) {
	int c;
	do { c = getchar(); } while (c == ' ' || c == '\n');
	if (c == EOF) { t->type = INVALID; return INVALID; }
	if (c >= '0' && c <= '9') {
		float val = 0;
		do {
			val = val*10 + (c-'0');
			c = getchar();
		} while (c >= '0' && c <= '9');
		ungetc(c, stdin);
		t->type = FLOAT;
		t->val.f = val;
		return FLOAT;
	}
	t->type = CHAR;
	t->val.c = c;
	return CHAR;
}


float BinaryOp(Token *t, const char *ops);
float Term(Token *t) { return BinaryOp(t, "*/"); }
float Expr(Token *t) { return BinaryOp(t, "+-"); }

float Factor(Token *t) {
	if (t->type == CHAR && t->val.c == '(') {
		GetToken(t);
		float res = Expr(t);
		if (t->type == CHAR && t->val.c == ')') GetToken(t);
		return res;
	}
	if (t->type == FLOAT) {
		float res = t->val.f;
		GetToken(t);
		return res;
	}
	return 0.0f;
}

float BinaryOp(Token *t, const char *ops) {
	float res = Factor(t);
	while (t->type == CHAR && strchr(ops, t->val.c)) {
		char op = t->val.c;
		GetToken(t);
		float rhs = (ops[0]=='+'||ops[0]=='-') ? Term(t) : Factor(t); 
		res = Eval[(unsigned char)op](res, rhs);
	}
	return res;
}


int main(void) {
	Token t;
	GetToken(&t);
	float result = Expr(&t);
	printf("result = %f\n", result);
}

