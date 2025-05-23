#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "libs/jsonw.h"

char* discoverlangpath(char *maindir){
	// GETTING A FILE NAME
	char *lang = getenv("LANG"); // GETTING LANG
	char *filename;
	sprintf(filename, "%s/lang/%s.lang", maindir, lang);
	// CONFIRMING THAT THE FILENAME EXISTS AND IF NOT PUT IT ON FALLBACK
	if(access(filename, F_OK) != 0){
		sprintf(filename, "%s/lang/pt_PT.UTF-8.lang", maindir);
	}
	return filename;
}

int main(){
	// DOING THIS SO THE PROGRAM CAN BE RUNNED EVEN IF IT'S NOT INSTALLED
	char *langpath;
	if(access(discoverlangpath("/usr/share/wordinator"), F_OK) != 0){
		langpath = discoverlangpath("."); // BECAUSE DOING THIS WE KNOW THAT IT'S NOT INSTALLED
	}
	else{
		langpath = discoverlangpath("/usr/share/wordinator");
	}
	//CONFIG
	char *palavras[] = { /* TODO: PUT THIS ON A JSON WITH A .LANG EXTENTION // DONE --> AND MAKE THIS READ THE LANGUAGE IN LINUX
			      USING THE $LANG ENVIORMENT VARIABLE. EG OF LANG FILES en_US.UTF-8.lang / pt_PT.UTF-8 */
		"BANANA",
		"TRABALHO",
		"SAMUEL",
		"PESSOA",
		"ANIMAL",
		"FELICIDADE",
		"OBRA",
		"TRISTEZA",
		"INFERNO",
		"ESTRELA",
		"PANELA",
		"GRIPE",
		"CARRO",
		"GIRAR",
		"BONITO",
		"FEIO",
		"ELIAS",
		"COMPUTADOR"
	};

	int sarray = sizeof(palavras) / sizeof(palavras[0]);
	srand(time(NULL));
	int r = rand() % sarray;
	char *palavra = palavras[r]; // TEM DE SER TUDO MAIUSCULAS

	int maxtentativas; // DECLARA A MAXTENTATIVAS PARA main()
	for(int h=0;palavra[h] != '\0';h++){maxtentativas = h+1;} // DEFINE O VALOR DE MAXTENTATIVAS
	char pensamento[maxtentativas+1]; // DECLARA PENSAMENTO PARA main()

	for(int i=1; i<=maxtentativas; i++){ // VERIFICA SE O NUMERO DE TENTATIVAS NÃO É MAIOR DO QUE PREMITIDO
		printf(cleardata(readjson(langpath,3)), maxtentativas); // PERGUNTA AO JOGADOR
		scanf("%s",&pensamento ); // LÊ A TENTATIVA DE ADVINHAÇÃO
		if(sizeof(pensamento)>maxtentativas+1){return 6;}
		for(int j = 0;pensamento[j] != '\0'; j++){pensamento[j] = toupper(pensamento[j]);} // DEIXA TUDO EM MAIUSCULAS
		if(strcmp(pensamento, palavra) ==  0){ // VERIFICA SE A RESPOSTA TÁ CORRETA
			if(i == 1){
				printf("%s",cleardata(readjson(langpath,4))); // FEEDBACK DE ACERTO
				return 0; // FECHA O JOGO
			}
			printf(cleardata(readjson(langpath,5)),i); // FEEDBACK DE ACERTO
			return 0; // FECHA O JOGO
	}
		printf(cleardata(readjson(langpath,6)), maxtentativas-i, maxtentativas, i, palavra[i-1]); // FEEDBACK DE ERRO
}
	printf(cleardata(readjson(langpath,7)), palavra); // GAME-OVER
	return 0; // FECHA O JOGO
}
