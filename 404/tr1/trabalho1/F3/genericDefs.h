#ifndef GENERIC_DEFS
#define GENERIC_DEFS

#define COMENT_CHAR '#'
#define EXIT_FAIL -1
#define EXIT_SUCESS 0

/* Útil para depurar */
#define cfprintf(file, color, ...){ \
    fprintf(file, "\033[0;%02dm", color); \
    fprintf(file, __VA_ARGS__); \
    fprintf(stderr, "\033[0;00m"); \
}

/* Define uma macro pra comparar numeros */
#define numcmp(a, b) (((a) == (b)) ? 0 : ((a) < (b))? -1 : 1)
/* Define um tipo enumeravel para argumentos */
typedef enum TypeArg{
	HEX = 1,
	DEC = 2,
	SYM = 3,
	ROT = 4
} TypeArg;
#endif
