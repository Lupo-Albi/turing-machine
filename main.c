#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {
    ESQUERDA,
    DIREITA
};

// Dados para a execução de uma transição
typedef struct {
    int estadoAtual;
    int simboloLido;
    int simboloGravado;
    int estadoSeguinte;
    int movimento;
} transicao_t;

// Definindo a fita do autômato com o símbolo e ponteiros para a esquerda e direita da posição atual
typedef struct fita_t {
    int simbolo;
    fita_t *esquerda;
    fita_t *direita;
} fita_t;

// Definindo um tipo com todos os elementos que compõem a máquina de Turing
typedef struct {
    int estadosComprimento;
    char **estados;
    int estadosFinaisComprimento;
    int *estadosFinais;
    int simbolosComprimento;
    char *simbolos;
    int branco;
    int estadoAtual;
    int fitaComprimento;
    fita_t *fita;
    int transicoesComprimento;
    transicao_t ***transicoes;
} turing_t;



void main(int argc, char *argv[]) {
    
}

/*
 * Função: indiceEstado
 * ------------------------
 * Procura por um estado no conjunto de estados de uma máquina
 * 
 * *turing: a máquina de Turing a qual possui um conjunto de estados
 * estado: estado que se deseja procurar no conjunto de estados da máquina
 * 
 * return: retorna o índice do estado. Retorna 0 caso não encontre nenhuma correspondência.
 */
int indiceEstado (turing_t *turing, char *estado) {
    int indice;
    for (indice = 0; indice < turing->estadosComprimento; indice++) {
        if (!strcmp(turing->estados[indice], estado)) {
            return indice;
        }
    }
    return 0;
}

/*
 * Função: indiceSimbolo
 * ------------------------
 * Procura por um símbolo no conjunto de símbolos de uma máquina
 * 
 * *turing: a máquina de Turing a qual possui um conjunto de símbolos
 * simbolo: símbolo que se deseja procurar no conjunto de símbolos da máquina
 * 
 * return: retorna o índice do símbolo. Retorna 0 caso não encontre nenhuma correspondência
 */
int indiceSimbolo(turing_t *turing, char simbolo) {
    int indice;

    for (indice = 0; indice < turing->simbolosComprimento; indice++) {
        if (turing->simbolos[indice] == simbolo) {
            return indice;
        }
    }
    return 0;
}