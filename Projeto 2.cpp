// Projeto 02 - Algoritmos & Programação II

// Eric Kanomata Schutz Cabrera - 10736688
// Pedro Henrique da Silva Lima - 10744246
// Luiza Lei Mao - 10740379

// ------------------------------------------------------
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// -------- FUNÇÃO PARA CONVERTER PARA MINÚSCULAS --------
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]); // Converte cada caractere para minúscula
    }
}

// -------- BUSCA BINÁRIA RECURSIVA --------
int binarySearch(char dicionario[][50], int left, int right, char *currStr) {
    if (left > right) {
        return -1; // Caso base: palavra não encontrada no dicionário
    }
    
    int mid = left + (right - left) / 2; // Calcula o ponto médio do intervalo atual
    int result = strcmp(dicionario[mid], currStr); // Compara a palavra do meio com a palavra buscada
    
    if (result == 0) {
        return mid; // Palavra encontrada, retorna a posição
    } else if (result > 0) {
        return binarySearch(dicionario, left, mid - 1, currStr); // Busca na metade esquerda
    } else {
        return binarySearch(dicionario, mid + 1, right, currStr); // Busca na metade direita
    }
}

// -------- INSERÇÃO ORDENADA --------
void insertOrdered(char dicionario[][50], int *arraySize, char *currStr, int uniqueWordCounter[]) {
    int pos = *arraySize; // Inicializa a posição como o final do array
    for (int i = 0; i < *arraySize; i++) {
        if (strcmp(dicionario[i], currStr) > 0) {
            pos = i; // Encontra a posição correta para manter ordem alfabética
            break;
        }
    }
    
    // Desloca palavras para a direita para abrir espaço
    for (int i = *arraySize; i > pos; i--) {
        strcpy(dicionario[i], dicionario[i - 1]); // Copia palavra para posição seguinte
        uniqueWordCounter[i] = uniqueWordCounter[i - 1]; // Copia frequência junto com a palavra
    }
    
    strcpy(dicionario[pos], currStr); // Insere a nova palavra na posição correta
    uniqueWordCounter[pos] = 1; // Inicializa contador de frequência para nova palavra
    (*arraySize)++; // Incrementa o tamanho do dicionário
}

// -------- FUNÇÃO PARA PROCESSAR PALAVRA --------
void processWord(char dicionario[][50], int *arraySize, char *currStr, int uniqueWordCounter[]) {
    toLowerCase(currStr); // ? CONVERTE PARA MINÚSCULAS ANTES DE PROCESSAR
    
    int pos = binarySearch(dicionario, 0, *arraySize - 1, currStr); // Busca palavra no dicionário
    
    if (pos != -1) {
        uniqueWordCounter[pos]++; // Se palavra existe, incrementa contador de frequência
    } else {
        insertOrdered(dicionario, arraySize, currStr, uniqueWordCounter); // Se não existe, insere ordenadamente
    }
}

// -------- FUNÇÃO PARA EXTRAIR PALAVRAS DO TEXTO --------
void extractWords(FILE *filePointer, char dicionario[][50], int *arraySize, int uniqueWordCounter[]) {
    char ch;
    char currStr[50] = ""; // Buffer para armazenar palavra sendo lida
    int wordIndex = 0; // Índice para controlar posição no buffer
    
    while ((ch = fgetc(filePointer)) != EOF) { // Lê caractere por caractere do arquivo
        if (isalpha(ch)) { // Verifica se é letra do alfabeto
            currStr[wordIndex++] = ch; // Adiciona letra à palavra atual
        } else {
            if (wordIndex > 0) { // Se tinha uma palavra sendo formada
                currStr[wordIndex] = '\0'; // Adiciona terminador de string
                processWord(dicionario, arraySize, currStr, uniqueWordCounter); // Processa palavra completa
                wordIndex = 0; // Reseta índice para próxima palavra
            }
        }
    }
    
    // Processa última palavra do arquivo (se houver)
    if (wordIndex > 0) {
        currStr[wordIndex] = '\0';
        processWord(dicionario, arraySize, currStr, uniqueWordCounter);
    }
}

// -------- FUNÇÃO MAIN --------
int main() {
    char dicionario[1000][50]; // Array para armazenar até 1000 palavras de 50 caracteres
    int uniqueWordCounter[1000] = {0}; // Array paralelo para contar frequência de cada palavra
    int arraySize = 0; // Contador de palavras únicas no dicionário
    
    FILE *filePointer;
    const char *fileName = "Projeto 02.txt"; // Nome do arquivo de entrada
    filePointer = fopen(fileName, "r"); // Abre arquivo no modo leitura
   
    extractWords(filePointer, dicionario, &arraySize, uniqueWordCounter); // Processa todo o arquivo
    fclose(filePointer); // Fecha arquivo após leitura
    
    // Imprime todas as palavras e suas frequências
    for (int i = 0; i < arraySize; i++) {
        printf("%s, %d\n", dicionario[i], uniqueWordCounter[i]);
    }
    printf("\nTotal de palavras diferentes no dicionario = %d\n", arraySize);
    
    return 0;
}
