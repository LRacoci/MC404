#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* data structures to hold the labels and .set constants */
/* holds the name */
char labelTable[500][1000];
/* holds the value and, src case of memory, the alignment */
int addressTable[500][2];
/* holds size of the stack */
int tablePosition = 0;

/* function that searchs and returns the value
of a label/.set, aborts if it can't find one */
int labelToNumber(char *label, int line){
	int i;
	for(i=0;i<tablePosition;i++){
		if(!strcmp(label,labelTable[i])){
			return addressTable[i][0];
		}
	}
	printf("--Valor de endereco ou rotulo invalido, linha %dn",line);
	abort();
	return 0;
}

/* function that validates a number. Return 0 if non valid, 1 if decimal, 2 if hex, 3 if binary, 4 if octal */
int validateNumber(char *number){
	int i;
	int len = strlen(number);

	/* checks strings with up to 2 chars, which can only represent decimal numbers */
	if(len==0)
		return 0;
	else if(len==1){
		if(number[0]>47&&number[0]<58)
			return 1;
		else
			return 0;
	}
	else if(len==2){
		if((number[0]>47&&number[0]<58)&&(number[1]>47&&number[1]<58))
			return 1;
		else
			return 0;
	}
	/* string has >3 chars */
	else{
		/* checks if number is hex */
		if(number[0]=='0'&&number[1]=='X'){
			for(i=2;i<len;i++)
				if((number[i]<48||number[i]>57)&&(number[i]<65||number[i]>70))
					return 0;
			return 2;
		}
		/* checks if number is binary */
		else if(number[0]=='0'&&number[1]=='B'){
			for(i=2;i<len;i++)
				if(number[i]<48||number[i]>49)
					return 0;
			return 3;
		}
		/* checks if number is octal */
		else if(number[0]=='0'&&number[1]=='O'){
			for(i=2;i<len;i++)
				if(number[i]<48||number[i]>55)
					return 0;
			return 4;
		}
		/* number is decimal */
		else{
			for(i=2;i<len;i++)
				if(number[i]<48||number[i]>57)
					return 0;
			return 1;
		}
	}
}

/* function that reads a memory address  or number as a string and return its converted decimal form, as an int */
int convertAddress(char *address, int lineCounter){
	int result;
	unsigned int value;
	int len,i;
	int base = 1;
	char newnumber[1000];
	if((result = validateNumber(address))){
		/* number is valid and decimal */
		if(result==1){
			return atoi(address);
		}
		/* number is valid and binary */
		else if(result==3){
			value = 0;
			len = strlen(address);
			for (i=len-1;i>1;i--){
				if(address[i]=='1')
					value+=base;
				base*=2;
			}
			return value;
		}
		/* number is valid and hex */
		else if(result==2){
			sscanf(address,"%x",&value);
			return value;
		}
		/* number is valid and octal */
		else if(result==4){
			len = strlen(address);
			for(i=0;i<len-2;i++)
				newnumber[i] = address[i+2];
			newnumber[i] = '\0';
			sscanf(newnumber,"%o",&value);
			return value;
		}
	}
	else{
		printf("--Numero invalido na linha %dn",lineCounter);
		abort();
	}
	return 0;
}

/* function to retrieve a memory address (constant or label) and return its value as an int */
int getAddress(char *buffer2, int line){
	int memAddress;
	char newstring[1000];
	int i;
	int len;

	len = strlen(buffer2);

	if(buffer2[0]=='\"'&&buffer2[len-1]=='\"'){
		for(i=2;i<len-1;i++)
			newstring[i-2] = buffer2[i];
		newstring[len-3] = '\0';

		if(isdigit(newstring[0]))
			memAddress = convertAddress(newstring, line);
		else
			memAddress = labelToNumber(newstring, line);
		return memAddress;
	}
	else{
		printf("--Endereco invalido na linha %dn",line);
		abort();
	}
}

/* function to treat directives during the first run (i.e., to build the address table) */
void treatDirectiveFirst(int *currentPos, int *right, char *buffer1, char *buffer2, int line){
	int memAddress;
	int start;
	int len;

	/* treats .org directive */
	if(!strcmp(buffer1,".org")){
		memAddress = convertAddress(buffer2, line);
		if(memAddress<0){
			printf("--A diretiva .org nao aceita numeros negativos, linha %dn",line);
			abort();
		}
		if(memAddress>1023){
			printf("--Endereco de memoria fora do limite, linha %dn",line);
			abort();
		}
		*currentPos = memAddress;
		*right = 0;
		return;
	}
	/* treats .align directive */
	else if(!strcmp(buffer1,".align")){
		memAddress = convertAddress(buffer2, line);
		if(memAddress<1){
			printf("--A diretiva .align nao aceita numeros negativos ou zero, linha %dn",line);
			abort();
		}
		if(*right){
			start = *currentPos + 1;
		}
		else{
			start = *currentPos;
		}
		while(!(start%memAddress==0)){
			start++;
		}
		if(start>1023){
			printf("--Endereco de memoria fora do limite, linha %dn",line);
			abort();
		}
		*currentPos = start;
		*right = 0;
		return;
	}
	/* treats .word directive */
	else if(!strcmp(buffer1,".word")){
		if(*right){
			printf("--A diretiva .word precisa de uma palavra de memoria alinhada a esquerda, linha %dn",line);
			abort();
		}
		(*currentPos)++;
		return;
	}
	/* treats .wfill directive */
	else if(!strcmp(buffer1,".WFILL")){
		if(*right){
			printf("--A diretiva .wfill precisa de uma palavra de memoria alinhada a esquerda, linha %dn",line);
			abort();
		}
		len = strlen(buffer2);
		if(buffer2[len-1]==','){
			buffer2[len-1] = '\0';
			memAddress = convertAddress(buffer2, line);
			if(memAddress<1){
				printf("--A diretiva .align nao aceita numeros negativos ou zero, linha %dn",line);
				abort();
			}
			*currentPos += memAddress;
			return;
		}
		else{
			printf("--Erro de sintaxe da diretiva .wfill, linha %dn",line);
			abort();
		}
	}
	/* treats .set directive */
	else if(!strcmp(buffer1,".SET")){
		return;
	}
	else{
		printf("--Diretiva nao reconhecida, linha %dn",line);
		abort();
	}
}

/* function to treat directives during the second run (i.e., outputing code) */
void treatDirectiveSecond(int *currentPos, int *right, char *buffer1, char *buffer2, char *buffer3, FILE *file, int line){
	int memAddress;
	int value;
	int i;
	int len;
	int flag = 0;
	char newnumber[1000];
	int dif;

	/* treats .org directive */
	if(!strcmp(buffer1,".org")){
		memAddress = convertAddress(buffer2, line);
		if(memAddress<0){
			printf("--A diretiva .org nao aceita numeros negativos, linha %dn",line);
			abort();
		}
		if(memAddress>1023){
			printf("--Endereco de memoria fora do limite, linha %dn",line);
			abort();
		}

		*currentPos = memAddress;
		*right = 0;
		return;
	}
	/* treats .align directive */
	else if(!strcmp(buffer1,".align")){
		memAddress = convertAddress(buffer2, line);
		if(memAddress<1){
			printf("--A diretiva .align nao aceita numeros negativos ou zero, linha %dn",line);
			abort();
		}
		if(*right){
			(*currentPos)++;
			fprintf(file,"00000n");
			*right = 0;
		}
		while(!((*currentPos)%memAddress==0)){
			(*currentPos)++;
		}
		if(*currentPos>1023){
			printf("--Endereco de memoria fora do limite, linha %dn",line);
			abort();
		}
		return;
	}
	/* treats .word directive */
	else if(!strcmp(buffer1,".word")){
		if(*right){
			printf("--A diretiva .word precisa de uma palavra de memoria alinhada a esquerda, linha %dn",line);
			abort();
		}
		else{
			/* check for hex number to output directly*/
			if(buffer2[0]=='0'&&buffer2[1]=='X'){
				len = strlen(buffer2);
				dif = 12 - len;
				for(i=0;i<dif;i++)
					newnumber[i] = '0';
				for(i=0;i<(len-2);i++)
					newnumber[i+dif] = buffer2[i+2];
				newnumber[i+dif] = '\0';

				fprintf(file,"%03X %sn",*currentPos,newnumber);
				(*currentPos)++;
				return;
			}
			/* check for negative number */
			if(buffer2[0]=='-'){
				flag = 1;
				len = strlen(buffer2);
				for(i=0;i<len;i++)
					buffer2[i] = buffer2[i+1];
			}

			if(isdigit(buffer2[0]))
				memAddress = convertAddress(buffer2, line);
			else
				memAddress = labelToNumber(buffer2, line);

			if(flag)
				memAddress *= -1;

			if(memAddress<0){
				fprintf(file,"%03X FF%Xn",*currentPos,memAddress);
			}
			else{
				fprintf(file,"%03X %010Xn",*currentPos,memAddress);
			}

			(*currentPos)++;
			return;
		}
	}
	/* treats .wfill directive */
	else if(!strcmp(buffer1,".WFILL")){
		if(*right){
			printf("--A diretiva .wfill precisa de uma palavra de memoria alinhada a esquerda, linha %dn",line);
			abort();
		}
		len = strlen(buffer2);
		buffer2[len-1] = '\0';
		memAddress = convertAddress(buffer2, line);
		if(memAddress<1){
			printf("--A diretiva .align nao aceita numeros negativos ou zero, linha %dn",line);
			abort();
		}

		if(isdigit(buffer3[0]))
			value = convertAddress(buffer3, line);
		else
			value = labelToNumber(buffer3, line);

		for(i=0;i<memAddress;i++){
			if(value>=0)
				fprintf(file,"%03X %010Xn",*currentPos,value);
			else
				fprintf(file,"%03X FF%08Xn",*currentPos,value);
			(*currentPos)++;
		}
		return;
	}
	/* treats .set directive */
	else if(!strcmp(buffer1,".SET")){
		return;
	}
	else{
		printf("--Diretiva nao reconhecida, linha %dn",line);
		abort();
	}
}

/* function to check whether a label already exists at the label table */
int labelExists(char *label){
	int i;
	for(i=0;i<tablePosition;i++){
		if(!strcmp(label,labelTable[i]))
			return 1;
	}
	return 0;
}

/* function to find the position of a label, aborting if it can't find it */
int findLabel(char *label, int lineCounter){
	int i;
	for(i=0;i<tablePosition;i++){
		if(!strcmp(label,labelTable[i]))
			return i;
	}
	printf("--Rotulo nao encontrado, linha %dn",lineCounter);
	abort();
	return 0;
}

/* function to transform a string to uppercase */
void stringToUpper(char *str){
	int size = strlen(str);
	int i;
	for(i=0;i<size;i++)
		str[i] = toupper(str[i]);
}

/* function to validate label names */
int validateLabel(char *str){
	int i;
	int size = strlen(str);
	char c = str[0];

	/* verify first char */
	if((c<65||c>90)&&(c!='_'))
		return 0;

	/* verify remaining chars */
	for(i=1;i<size;i++){
		c = str[i];
		if((c<65||c>90)&&(c!='_')&&(c<48||c>57))
			return 0;
	}

	return 1;
}

/* checks if a string is a valid instruction */
int validInstruction(char *opcode){
	if(!strcmp(opcode,"LD")){
		return 1;
	}
	else if(!strcmp(opcode,"LMQ")){
		return 1;
	}
	else if(!strcmp(opcode,"LDmq")){
		return 1;
	}
	else if(!strcmp(opcode,"LD-")){
		return 1;
	}
	else if(!strcmp(opcode,"LD|")){
		return 1;
	}
	else if(!strcmp(opcode,"ADD")){
		return 1;
	}
	else if(!strcmp(opcode,"ADD|")){
		return 1;
	}
	else if(!strcmp(opcode,"SUB")){
		return 1;
	}
	else if(!strcmp(opcode,"SUB|")){
		return 1;
	}
	else if(!strcmp(opcode,"MUL")){
		return 1;
	}
	else if(!strcmp(opcode,"DIV")){
		return 1;
	}
	else if(!strcmp(opcode,"LSH")){
		return 1;
	}
	else if(!strcmp(opcode,"RSH")){
		return 1;
	}
	else if(!strcmp(opcode,"ST")){
			return 1;
	}
	else if(!strcmp(opcode,"STM")){
		return 1;
	}
	else if(!strcmp(opcode,"JMP")){
		return 1;
	}
	else if(!strcmp(opcode,"JMP+")){
			return 1;
	}
	else
		return 0;
}

/* interprets a statement and returns the respect opcode */
int interpretOpcode(char *opcode, char *address, int lineCounter){
	int position;
	char newstring[1000];
	int i;
	int len;

	if(!strcmp(opcode,"LD")){
		return 1;
	}
	else if(!strcmp(opcode,"LMQ")){
		return 10;
	}
	else if(!strcmp(opcode,"LDmq")){
		return 9;
	}
	else if(!strcmp(opcode,"LD-")){
		return 2;
	}
	else if(!strcmp(opcode,"LD|")){
		return 3;
	}
	else if(!strcmp(opcode,"ADD")){
		return 5;
	}
	else if(!strcmp(opcode,"ADD|")){
		return 7;
	}
	else if(!strcmp(opcode,"SUB")){
		return 6;
	}
	else if(!strcmp(opcode,"SUB|")){
		return 8;
	}
	else if(!strcmp(opcode,"MUL")){
		return 11;
	}
	else if(!strcmp(opcode,"DIV")){
		return 12;
	}
	else if(!strcmp(opcode,"LSH")){
		return 20;
	}
	else if(!strcmp(opcode,"RSH")){
		return 21;
	}
	else if(!strcmp(opcode,"ST")){
			return 33;
	}
	else{
		len = strlen(address);

		if(address[0]=='\"'&&address[len-1]=='\"'){
			for(i=2;i<len-1;i++)
				newstring[i-2] = address[i];
			newstring[len-3] = '\0';

			if (!strcmp(opcode,"STM")){
				if (isdigit(newstring[0]))
					return 18;
				position = findLabel(newstring, lineCounter);
				if (addressTable[position][1])
					return 19;
				else
					return 18;
			}
			else if(!strcmp(opcode,"JMP")){
				position = findLabel(newstring, lineCounter);
				if(addressTable[position][1])
					return 14;
				else
					return 13;
			}
			else if(!strcmp(opcode,"JMP+")){
				position = findLabel(newstring, lineCounter);
				if(addressTable[position][1])
					return 16;
				else
					return 15;
			}
			else
				return 0;
		}
		else
			return 0;
	}
	return 0;
}

/* function to treat instructions during the second run (i.e., outputing code) */
void treatInstruction(char *opcode, char *address, int *currentPos, int *right, int lineCounter, FILE *file){
	int opcodeNum, addressNum;

	/* gets opcode */
	opcodeNum = interpretOpcode(opcode,address,lineCounter);

	/* gets mem address */
	if(opcodeNum!=20&&opcodeNum!=21&&opcodeNum!=10)
		addressNum = getAddress(address,lineCounter);
	else
		addressNum = 0;

	if(*right){
		fprintf(file,"%02X%03Xn",opcodeNum,addressNum);
		*right = 0;
		(*currentPos)++;
	}
	else{
		fprintf(file,"%03X %02X%03X",*currentPos,opcodeNum,addressNum);
		*right = 1;
	}

}
/*##################################### MAIN #########################################*/
int build_all(FILE * src, FILE * out){
	char stringBuffer[4000]; /* char buffer to store input strings */
	char firstBuffer[1000]; /* char buffer to store input strings */
	char secondBuffer[1000]; /* char buffer to store input strings */
	char thirdBuffer[1000]; /* char buffer to store input strings */
	char fourthBuffer[1000]; /* char buffer to store input strings */
	int bytesRead, totalBytesRead, firstToken, secondToken; /* aux input variables */
	int lineCounter; /*  holds current line at input file */
	int currentPos; /*  holds current memory address */
	int right; /*  holds alignment of current memory address */
	int len; /*  auxiliary variable */
	int i,cons; /*  auxiliary variable */
	int flag; /*  auxiliary variable */


	/* ------first run through input file to build table of labels-addresses ----- */
	currentPos = 0;
	right = 0;
	lineCounter = 1;
	while(fgets(stringBuffer,4000,src)){
		/* transform all chars to uppercase */
		stringToUpper(stringBuffer);

		totalBytesRead = 0;
		/* reads first token */
		firstToken = sscanf(stringBuffer,"%s%n",firstBuffer,&bytesRead);
		totalBytesRead += bytesRead;

		if(firstToken!=-1){
			/* checks if comment */
			if(firstBuffer[0]==';'){
				lineCounter++;
				continue;
			}
			/* checks if label */
			len = strlen(firstBuffer);
			if(firstBuffer[len-1]==':'){
				/* removes the : from the label */
				firstBuffer[len-1] = '\0';

				/* validates label */
				if(!validateLabel(firstBuffer)){
					printf("--Rotulo invalido na linha %dn",lineCounter);
					return 1;
				}
				/* store label and its address */
				if(labelExists(firstBuffer)){
					printf("--Rotulo declarado pela segunda vez na linha %dn",lineCounter);
					return 1;
				}
				strcpy(labelTable[tablePosition],firstBuffer);
				addressTable[tablePosition][0] = currentPos;
				addressTable[tablePosition][1] = right;
				tablePosition++;

				/* reads second token  */
				secondToken = sscanf(stringBuffer+totalBytesRead,"%s%n",secondBuffer,&bytesRead);
				totalBytesRead += bytesRead;

				if(secondToken!=-1){
					/* check if directive */
					if(secondBuffer[0]=='.'){
						/* reads third token  */
						sscanf(stringBuffer+totalBytesRead,"%s%n",thirdBuffer,&bytesRead);
						totalBytesRead += bytesRead;

						treatDirectiveFirst(&currentPos,&right,secondBuffer,thirdBuffer,lineCounter);

						/* store .SET constant, if the case */
						if(!strcmp(secondBuffer,".set")){
							flag = 0;
							/* validates .set name */
							if(!validateLabel(secondBuffer)){
								printf("--Nome de diretiva .set invalido na linha %dn",lineCounter);
								return 1;
							}
							/* reads fourth token  */
							sscanf(stringBuffer+totalBytesRead,"%s%n",fourthBuffer,&bytesRead);
							totalBytesRead += bytesRead;

							/* check for negative number */
							if(fourthBuffer[0]=='-'){
								flag = 1;
								len = strlen(fourthBuffer);
								for(i=0;i<len;i++)
									fourthBuffer[i] = fourthBuffer[i+1];
							}

							cons = convertAddress(fourthBuffer,lineCounter);
							if(flag)
								cons*=-1;

							strcpy(labelTable[tablePosition],thirdBuffer);
							addressTable[tablePosition][0] = cons;
							tablePosition++;
						}
					}
					/* check if instruction */
					else if(validInstruction(secondBuffer)){
						if(right){
							right = 0;
							currentPos++;
						}
						else{
							right = 1;
						}
					}
				}
			}
			/* checks if instruction */
			else if(validInstruction(firstBuffer)){
				if(right){
					right = 0;
					currentPos++;
				}
				else{
					right = 1;
				}
			}

			/* checks if directive */
			else if(firstBuffer[0]=='.'){
				/* reads second token  */
				sscanf(stringBuffer+totalBytesRead,"%s%n",secondBuffer,&bytesRead);
				totalBytesRead += bytesRead;

				treatDirectiveFirst(&currentPos,&right,firstBuffer,secondBuffer,lineCounter);

				/* store .SET constant, if the case */
				if(!strcmp(firstBuffer,".set")){
					flag = 0;
					/* reads third token  */
					sscanf(stringBuffer+totalBytesRead,"%s%n",thirdBuffer,&bytesRead);
					totalBytesRead += bytesRead;

					/* check for negative number */
					if(thirdBuffer[0]=='-'){
						flag = 1;
						len = strlen(thirdBuffer);
						for(i=0;i<len;i++)
							thirdBuffer[i] = thirdBuffer[i+1];
					}

					cons = convertAddress(thirdBuffer,lineCounter);
					if(flag)
							cons*=-1;

					strcpy(labelTable[tablePosition],secondBuffer);
					addressTable[tablePosition][0] = cons;
					tablePosition++;
				}
			}
		}
		lineCounter++;
	}

	/* ------ second run through input file to output machine code to out ---------- */
	rewind(src);
	currentPos = 0;
	right = 0;
	lineCounter = 1;
	while(fgets(stringBuffer,4000,src)){

		totalBytesRead = 0;
		/* reads first token */
		firstToken = sscanf(stringBuffer,"%s%n",firstBuffer,&bytesRead);
		totalBytesRead += bytesRead;

		if(firstToken!=-1){
			/* checks if comment */
			if(firstBuffer[0]==';'){
				lineCounter++;
				continue;
			}
			/* checks if label */
			len = strlen(firstBuffer);
			if(firstBuffer[len-1]==':'){
				/* reads second token  */
				secondToken = sscanf(stringBuffer+totalBytesRead,"%s%n",secondBuffer,&bytesRead);
				totalBytesRead += bytesRead;

				if(secondToken!=-1){
					/* check if directive */
					if(secondBuffer[0]=='.'){
						/* reads third token  */
						sscanf(stringBuffer+totalBytesRead,"%s%n",thirdBuffer,&bytesRead);
						totalBytesRead += bytesRead;
						/* reads fourth token  */
						sscanf(stringBuffer+totalBytesRead,"%s%n",fourthBuffer,&bytesRead);
						totalBytesRead += bytesRead;

						treatDirectiveSecond(&currentPos,&right,secondBuffer,thirdBuffer,fourthBuffer,out,lineCounter);
					}
					/* check if instruction */
					else if(validInstruction(secondBuffer)){
						/* reads third token  */
						sscanf(stringBuffer+totalBytesRead,"%s%n",thirdBuffer,&bytesRead);
						totalBytesRead += bytesRead;

						treatInstruction(secondBuffer,thirdBuffer,&currentPos,&right,lineCounter, out);
					}
				}
			}
			/* checks if directive */
			else if(firstBuffer[0]=='.'){
				/* reads second token  */
				sscanf(stringBuffer+totalBytesRead,"%s%n",secondBuffer,&bytesRead);
				totalBytesRead += bytesRead;
				/* reads third token  */
				sscanf(stringBuffer+totalBytesRead,"%s%n",thirdBuffer,&bytesRead);
				totalBytesRead += bytesRead;

				treatDirectiveSecond(&currentPos,&right,firstBuffer,secondBuffer,thirdBuffer,out,lineCounter);
			}
			/* checks if instruction */
			else if(validInstruction(firstBuffer)){
				/* reads second token  */
				sscanf(stringBuffer+totalBytesRead,"%s%n",secondBuffer,&bytesRead);
				totalBytesRead += bytesRead;

				treatInstruction(firstBuffer,secondBuffer,&currentPos,&right,lineCounter, out);
			}
			/* syntax error */
			else{
				printf("--Erro de sintaxe na linha %dn",lineCounter);
				return 1;
			}
		}
		lineCounter++;
	}

	if(right)
		fprintf(out,"00000n");

    return 0;
}


int main(int argc, char **argv){
	FILE *src = NULL, *out = NULL;
    int return_value;
    char * out_name;
	switch (argc){
		case 2:
			src = fopen(argv[1], "r");
			out_name = strcat(argv[1], ".aux");
			out = fopen(out_name, "w");
			break;
		case 3:
			src = fopen(argv[1], "r");
			out = fopen(argv[2], "w");
			break;
	}

	if( src == NULL ){
        fprintf(stderr, "Error while opening the source file.\n");
		return 1;
	}

	if( out == NULL ){
        fprintf(stderr, "Error while opening the output file.\n");
        return 1;
	}
    return_value = build_all(src, out);

    if(src)
        fclose(src);
    if(out)
        fclose(out);

	return return_value;
}
