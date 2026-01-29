#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>
#include "libs/jsonw.h"

#define RED     "\x1b[31m"
#define YELLOW  "\x1b[33m"
#define RESET   "\x1b[0m"

const char* get_default_langpath() {
#if defined(__APPLE__) && defined(__MACH__)
    static char path[1024];
    const char *home = getenv("HOME");
    snprintf(path, sizeof(path), "%s/Library/Application Support/wordinator", home);
    return path;
#else
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
		int level = 0;

		static struct option long_options[] =
		{
			{"debug", no_argument, 0, 'd'},
			{"level",  required_argument, 0, 'l'},
			{0, 0, 0, 0}
		};
		int opt;
		while ((opt = getopt_long(argc, argv, "dl:", long_options, NULL)) != -1) {
			switch(opt){
				case 'd':
					debug = 1;
					break;
				case 'l':
					level = atoi(optarg);
					break;
				default:
					break;
			}
		}

		if(debug){printf(YELLOW "[DEBUG] DEBUG MODE ACTIVATED\n" RESET);} // TELLING THE USER THAT HE IS IN DEBUG MODE
						  
	// DOING THIS SO THE PROGRAM CAN BE RUNNED EVEN IF IT'S NOT INSTALLED
	if(debug){printf(YELLOW "[DEBUG] LANG: %s\n" RESET, getenv("LANG"));}
	
	char *langpath;
	if(access(discoverlangpath(get_default_langpath()), F_OK) != 0){
		langpath = discoverlangpath("."); // BECAUSE DOING THIS WE KNOW THAT IT'S NOT INSTALLED
	}
	else{
		langpath = discoverlangpath(get_default_langpath());;
	}
	if(debug){printf(YELLOW "[DEBUG] LANGPATH %s\n" RESET, langpath);}
	
	//WORDS LIST CHARGING
	char *line = readjson_raw(langpath, 2);
	if (!line) {
	    printf(RED "[ERROR][FATAL] Can't find the lang file\n");
	    return 1;
	}

	int total_words = 0;
	char **palavras = load_words(line, &total_words);
	free(line);

	if (!palavras || total_words == 0) {
	    printf("[ERROR][FATAL] File doesn't have words\n");
	    return 1;
	}
	int r;
	if(debug){
		printf(YELLOW"[DEBUG] level = %d\n"RESET, level);
		printf(YELLOW"[DEBUG] total_words = %d\n"RESET, total_words);
		if(level > total_words){printf(YELLOW"[DEBUG] Level exceded the words count. Ignoring Level\n"RESET);}
	}
	if(level && level <= total_words){
		if(debug){printf(YELLOW"[DEBUG] Specific Level Specified\n"RESET);}
		r = level-1;
	} else {
		if(debug){printf(YELLOW"[DEBUG] No Level Specified using random\n"RESET);}
		srand(time(NULL));
		r = rand() % total_words;
	}
	char *palavra = palavras[r]; // TEM DE SER TUDO MAIUSCULAS

	int maxtentativas; // DECLARA A MAXTENTATIVAS PARA main()
	for(int h=0;palavra[h] != '\0';h++){maxtentativas = h+1;} // DEFINE O VALOR DE MAXTENTATIVAS
	char pensamento[maxtentativas+1]; // DECLARA PENSAMENTO PARA main()
 	if(debug){printf(YELLOW "[DEBUG] Answer: %s\n" RESET, palavra);}
	for(int i=1; i<=maxtentativas; i++){ // VERIFICA SE O NUMERO DE TENTATIVAS NÃO É MAIOR DO QUE PREMITIDO
		char *line = readjson(langpath, 3);
		if (!line) {
		    printf(RED "[ERROR][FATAL] No Language File Found!!\n" RESET);
		    return 1;
		}
		printf(line, maxtentativas); // ASKS THE PLAYER
		free(line);
		scanf("%s",pensamento); // LÊ A TENTATIVA DE ADVINHAÇÃO
		if(sizeof(pensamento)>maxtentativas+1){return 6;}
		for(int j = 0;pensamento[j] != '\0'; j++){pensamento[j] = toupper(pensamento[j]);} // DEIXA TUDO EM MAIUSCULAS
		if(strcmp(pensamento, palavra) ==  0){ // VERIFICA SE A RESPOSTA TÁ CORRETA
			if(i == 1){
				printf(readjson(langpath,4)); // FEEDBACK DE ACERTO
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
