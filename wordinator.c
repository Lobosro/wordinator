#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>
#include "libs/jsonw.h"

const char* get_default_langpath() {
#if defined(__APPLE__) && defined(__MACH__)
    static char path[1024];
    const char *home = getenv("HOME");
    snprintf(path, sizeof(path), "%s/Library/Application Support/wordinator", home);
    return path;
#elif
    return "/usr/share/wordinator";
#endif
}

char* discoverlangpath(const char *maindir){
    char *lang = getenv("LANG");
    if (!lang) lang = "pt_PT.UTF-8";

    char *filename = malloc(512);
    if (!filename) return NULL;

    snprintf(filename, 512, "%s/lang/%s.lang", maindir, lang);

    if (access(filename, F_OK) != 0){
        snprintf(filename, 512, "%s/lang/pt_PT.UTF-8.lang", maindir);
    }
    return filename;
}

int main(int argc, char *argv[]){
	// VERIFING DEBUG FLAG
	
	/*
		int debug = 0; // CREATING DEBUG INT TO MAIN
		for (int i = 1; i < argc; i++){
			if(strcmp(argv[i],"--debug") == 0){
				debug = 1;
			}
		}
	*/
		int debug = 0;

		static struct option long_options[] =
		{
			{"debug", no_argument, 0, 'd'},
			{0, 0, 0, 0}
		};
		int opt;
		while ((opt = getopt_long(argc, argv, "d", long_options, NULL)) != -1) {
			switch(opt){
				case 'd':
					debug = 1;
					break;
				default:
					printf("Invalid Flag");
					break;
			}
		}

		if(debug){printf("[DEBUG] DEBUG MODE ACTIVATED\n");} // TELLING THE USER THAT HE IS IN DEBUG MODE
						  
	// DOING THIS SO THE PROGRAM CAN BE RUNNED EVEN IF IT'S NOT INSTALLED
	if(debug){printf("[DEBUG] LANG: %s\n", getenv("LANG"));}
	
	char *langpath;
	if(access(discoverlangpath(get_default_langpath()), F_OK) != 0){
		langpath = discoverlangpath("."); // BECAUSE DOING THIS WE KNOW THAT IT'S NOT INSTALLED
	}
	else{
		langpath = discoverlangpath(get_default_langpath());;
	}
	if(debug){printf("[DEBUG] LANGPATH %s\n", langpath);}
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
 	if(debug){printf("[DEBUG] Answer: %s\n", palavra);}
	for(int i=1; i<=maxtentativas; i++){ // VERIFICA SE O NUMERO DE TENTATIVAS NÃO É MAIOR DO QUE PREMITIDO
		char *line = readjson(langpath, 3);
		if (!line) {
		    printf("[FATAL] No Language File Found!!\n");
		    return 1;
		}
		printf(line, maxtentativas); // segura
		free(line); // sempre liberar

		
		printf(readjson(langpath,3), maxtentativas); // PERGUNTA AO JOGADOR
		scanf("%s",pensamento); // LÊ A TENTATIVA DE ADVINHAÇÃO
		if(sizeof(pensamento)>maxtentativas+1){return 6;}
		for(int j = 0;pensamento[j] != '\0'; j++){pensamento[j] = toupper(pensamento[j]);} // DEIXA TUDO EM MAIUSCULAS
		if(strcmp(pensamento, palavra) ==  0){ // VERIFICA SE A RESPOSTA TÁ CORRETA
			if(i == 1){
				printf("%s",readjson(langpath,4)); // FEEDBACK DE ACERTO
				return 0; // FECHA O JOGO
			}
			printf(readjson(langpath,5),i); // FEEDBACK DE ACERTO
			return 0; // FECHA O JOGO
	}
		printf(readjson(langpath,6), maxtentativas-i, maxtentativas, i, palavra[i-1]); // FEEDBACK DE ERRO
}
	printf(readjson(langpath,7), palavra); // GAME-OVER
	return 0; // FECHA O JOGO
}
