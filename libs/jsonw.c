#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readjson(const char *filename, int line) {
    if (!filename || line <= 0) return NULL;

    FILE *pF = fopen(filename, "r");
    if (!pF) return NULL;

    char buffer[512];
    int current = 0;

    while (fgets(buffer, sizeof(buffer), pF)) {
        current++;
        if (current == line) break;
    }
    fclose(pF);

    if (current != line) return NULL;

    // Procura o primeiro : depois da chave
    char *colon = strchr(buffer, ':');
    if (!colon) return NULL;

    char *start = strchr(colon, '"'); // primeira aspas
    if (!start) return NULL;
    start++; // pula a primeira aspas

    char *end = strchr(start, '"'); // próxima aspas
    if (!end) return NULL;
    *end = '\0';

    // Aloca memória para a string final, já com escape processado
    size_t len = strlen(start);
    char *final = malloc(len + 1); // tamanho máximo inicial
    if (!final) return NULL;

    char *dst = final;
    for (char *src = start; *src; src++) {
        if (*src == '\\' && *(src+1) == 'n') {
            *dst++ = '\n'; // substitui literal \n por newline
            src++;         // pula o 'n'
        } else {
            *dst++ = *src;
        }
    }
    *dst = '\0';

    return final;
}



char* cleardata(const char *data){
    if (!data) return NULL;
    size_t len = strlen(data);
    if (len < 2) return NULL; // nada para limpar

    char *copy = malloc(len - 1); // remove 1 char de cada lado
    if (!copy) return NULL;

    strncpy(copy, data + 1, len - 2);
    copy[len - 2] = '\0';
    return copy;
}

