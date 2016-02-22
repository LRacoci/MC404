#include "MemMap.h"

MemMap new_MemMap(){
	MemMap n = malloc(sizeof(sMemMap));
	n->l = NULL;
	n->pos = 0;
	return n;
}
void free_MemMap(MemMap *del){
	MemWord p, temp;
	if(!del || !*del){
		return;
	}
	p = (*del)->l;
	while(p){
		temp = p;
		p = p->prox;
		free(temp);
	}
	free(*del);
	*del = NULL;
}
void fprint_MemMap(FILE * out, MemMap m){
	MemWord aux;
	if(!m) return;
	for(aux = m->l; aux; aux = aux->prox){
		fprint_MemWord(out, aux);
	}
}
MemWord new_MemWord(unsigned int pos, bool is_word){
	unsigned short int i;
	MemWord new = malloc(sizeof(sMemWord));
	new->pos = pos;
	new->is_word = is_word;
	if(is_word){
		new->c.w.w = 0;
	}else{
		for(i = 0; i < 2; i++){
			new->c.i[i].code = 0;
			new->c.i[i].arg  = 0;
		}
	}
	new->prox = 0;
	return new;

}
bool get_MemMap(MemMap m, unsigned int pos, MemWord *resp){
	MemWord ini = m->l, p = ini;
	while(p && pos != p->pos){
		p = p->prox;
	}
	if(p == NULL){
		*resp = NULL;
		return false;
	}
	if(resp){
		*resp = p;
	}
	return true;
}
bool is_in_MemMap(MemMap m, unsigned int pos){
	return get_MemMap(m, pos, NULL);
}

bool put_MemMap(MemMap m, MemWord p){
	MemWord * aux = &(m->l);
	/* Avança aux até a posicao certa*/
	while(*aux && p->pos > (*aux)->pos){
		aux = &((*aux)->prox);
	}
	/* Verifica se já esta na lista */
	if(*aux && p->pos == (*aux)->pos){
		return false;
	}
	*aux = p;
	return true;

}
bool insert_instr_MemMap(
	MemMap m,
	unsigned int code,
	unsigned int arg,
	unsigned int line
 ){
	MemWord aux;
	if(!m) return false;
	if(!between(0, m->pos, 1023)) return false;
	if(get_MemMap(m, m->pos/2, &aux)){
		if(aux->is_word){
			stderror(line, "Position %03X have already a word", (m->pos)/2);
			return false;
		}else{
			if(
				aux->c.i[(m->pos)%2].code && aux->c.i[(m->pos)%2].arg
			){
				stderror(
					line,
					"Position %03X %c have already a instruction (%02X %03X)", (m->pos)/2, ((m->pos)%2) ? 'D' : 'E',
					aux->c.i[(m->pos)%2].code,
					aux->c.i[(m->pos)%2].arg
				);
				return false;

			}else{
				aux->c.i[(m->pos)%2].code = code;
				aux->c.i[(m->pos)%2].arg = arg;
				aux->pos = m->pos/2;
				m->pos++;
			}
		}
	}else{
		aux = new_MemWord(m->pos/2, false);
		aux->c.i[(m->pos)%2].code = code;
		aux->c.i[(m->pos)%2].arg = arg;
		put_MemMap(m, aux);
		m->pos++;
	}

	return true;

}
bool insert_word_MemMap(
	MemMap m,
	unsigned long long int w,
	unsigned int line
){
	unsigned short int i;
	MemWord aux;
	if(!m) return false;
	if(!between(0, m->pos, 2*1023)){
		stderror(line, "Position %03X is not int he memory\n",
		m->pos/2
	);
		return false;
	}
	if(get_MemMap(m, m->pos/2, &aux)){
		if(aux->is_word){
			stderror(line, "Position %03X have already a word\n", m->pos/2);
			return false;
		}else{
			for(i = 0; i < 2; i++){
				if(
					aux->c.i[i].code &&
					aux->c.i[i].arg
				){
					stderror(
						line,
						"Position %03X %c have already a instruction (%02X %03X)\n",
						m->pos/2,
						(i) ? 'D' : 'E',
						aux->c.i[i].code,
						aux->c.i[i].arg
					);
					return false;
				}
			}
		}
	}else{
		aux = new_MemWord(m->pos/2, true);
		aux->c.w.w = w;
		put_MemMap(m, aux);
		m->pos += 2;
	}
	return true;
}

void fprint_ias_format(FILE * out, unsigned long long int hex){
	char aux[65];
	unsigned int i, j, k, len, f[] = {2, 3, 2, 3};
	sprintf(aux, "%064llX", hex);
	len = strlen(aux);
	for(k = len -10, i = 0; i < 4; i++){
		fprintf(out, " ");
		for(j = 0; j < f[i]; j++, k++){
			fprintf(out, "%c", aux[k]);
		}
	}
	fprintf(out, "\n");
}
void fprint_MemWord(FILE * out, MemWord p){
	if(p == NULL){
		return;
	}
	fprintf(out, "%03X", p->pos);
	if(p->is_word){
		fprint_ias_format(out, p->c.w.w);
	}else{
		fprintf(
			out,
			" %02X %03X %02X %03X\n",
			p->c.i[0].code,
			p->c.i[0].arg,
			p->c.i[1].code,
			p->c.i[1].arg
		);
	}
}
