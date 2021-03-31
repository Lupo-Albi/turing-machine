#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {
    ESQUERDA,
    DIREITA
}

// Dados para a execução de uma transição
typedef struct {
    int estadoAtual;
    int simboloLido;
    int simboloGravado;
    int estadoSeguinte;
    int movimento;
} transicao_t;

// Definindo a fita do autômato com o símbolo e ponteiros para a esquerda e direita da posição atual
typedef struct fita {
    int simbolo;
    fita *esquerda;
    fita *direita;
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
 * Função: agruparValores
 * ------------------------
 * Agrupa valores iguais encontrados em um array e os ordena em ordem crescente.
 * Exemplo: Se o vetor de origem é [3, 3, 1, 1, 2] o vetor de destino será [1, 2, 3] após a execução da função e retorna o valor 3 (número de elementos no array de destino)
 * 
 * vetorOrigem: array de inteiros
 * vetorDestino: array que recebe o agrupamento em ordem crescence
 * comprVetor: tamanho do array de origem vetorOrigem
 * 
 * returns: retorna a quantidade final de elementos gravados no vetor de destino
 */