#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "auxTypes.h"
#include "iasDefs.h"
#include "genericDefs.h"
#include "Error.h"

#define MAX_MEM_MAP 1024
/* Declara o sruct responsável por guardar uma palavra de memoria */
typedef struct sMemWord{
	unsigned int pos;
	bool is_word;
	union sContent{
		struct sI{
			unsigned int code;
			unsigned int arg;
		} i [2];
		struct sW{
			unsigned long long int w;
		} w;
	} c;
} sMemWord, *MemWord;
/* Declara um Mapa de Memoria, vetor de palavras de memoria
 * juntamente com um indicador da posição atual de montagem */
typedef struct sMemMap{
	unsigned int pos;
	MemWord m[MAX_MEM_MAP];
}sMemMap, *MemMap;


/* Cria e inicializa um novo mapa de memoria */
MemMap new_MemMap();
/* Libera a memoria alocada por um mapa de memoria */
void free_MemMap(MemMap *del);
/* Imprime um mapa de memoria em um arquivo, de acordo com
 * as especificações do enunciado */
void fprint_MemMap(FILE * out, MemMap m);
/* Insere uma instrução no mapa de memoria se possível*/
bool insert_instr_MemMap(
	MemMap m,
	unsigned int code,
	unsigned int arg,
	unsigned int line
);
/* Insere um dado no mapa de memoria se possivel */
bool insert_word_MemMap(
	MemMap m,
	unsigned long long int w,
	unsigned int line
);
/* Imprime um dado no formato especificado no enunciado*/
void fprint_ias_format(FILE * out, unsigned long long hex);
/* Impeimre uma palavra de memoria em um arquivo conforme
 * especificaod no enunciado */
void fprint_MemWord(FILE * out, MemWord p);
