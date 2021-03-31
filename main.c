#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

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

/*
 * Função: moverFita
 * ---------------------
 * Realiza um movimento na fita da máquina para a direita ou para a esquerda
 * Realiza uma verificação para garantir que o ponteiro para a fita e do sentindo do movimento não são inválidos (NULL). Caso sejam, aloca espaço para um símbolo e o preenche com o símbolo Branco e realiza o movimento
 *
 * *turing: a máquina de Turing a qual possui uma fita a ser lida e escrita
 * direcao: direção para a qual o leitor da fita deve se mover
 */
void moverFita (turing_t *turing, int direcao) {
    fita_t *fitaAntesDoMovimento = turing->fita;

    if (direcao == DIREITA) {
        // Verifica se o ponteito da fita e o ponteiro da sua direita são válidos
        if (fitaAntesDoMovimento && fitaAntesDoMovimento->direita) {
            // Move a fita para a direita
            turing->fita = fitaAntesDoMovimento->direita;
        } else {
            turing->fita = calloc(1, sizeof(fita_t));
            turing->fita->simbolo = turing->branco;

            if (fitaAntesDoMovimento) {
                // As duas linhas seguintes configuram um movimento para a direita porque a posição antiga da fita é movida para a esquerda da nova posição
                turing->fita->esquerda = fitaAntesDoMovimento;
                fitaAntesDoMovimento->direita = turing->fita;
            }
        }
    } else if (direcao == ESQUERDA) {
        // Verificia se o ponteiro da fita e o ponteiro da sua esquerda são válidos
        if (fitaAntesDoMovimento && fitaAntesDoMovimento->esquerda) {
            // Move a fita para a esquerda
            turing->fita = fitaAntesDoMovimento->esquerda;
        } 
        else {
            turing->fita = calloc(1, sizeof(fita_t));
            turing->fita->simbolo = turing->branco;

            if (fitaAntesDoMovimento) {
                // As duas linhas seguintes configuram um movimento para a esquerda porque a posição antiga da fita é movida para a direita da nova posição
                turing->fita->direita = fitaAntesDoMovimento;
                fitaAntesDoMovimento->esquerda = turing->fita;
            }
        }
    }
}

/* Função: CriarMaquina
 * -------------------------
 * Cria um elemento do tipo turing_t com os dados passados para a função, ou seja, "monta" a máquina de turing
 * 
 * Essa função se utiliza do header <stdarg.h> para que o número de argumentos seja variável
 * A ordem dos argumentos é presente na struct do tipo turing_t, bastando inserir cada argumento por vez, separando-os por vírgula:
 **** int estadosComprimento (apenas um valor inteiro)
 **** char **estados (quantos caracteres forem desejados, contanto que cada caractere individual esteja entre aspas e separados por vírgula)
 **** int estadosFinaisComprimento (apenas um valor inteiro)
 **** int *estadosFinais (quantos caracteres forem desejados, contanto que cada caractere individual esteja entre aspas e separados por vírgula )
 **** int simbolosComprimento (apenas um valor inteiro)
 **** char *simbolos (quantos caracteres forem desejados como símbolos do alfabeto, contanto que estejam entre aspas e separados por vírgula)
 **** int branco (um dos caractere que esteja presente nos símbolos do alfabeto)
 **** int estadoAtual (um dos estados que esteja presente nos estados)
 **** int fitaComprimento
 **** fita_t *fita (conteúdo inicial da fita)
 **** int transicoesComprimento (apenas um valor inteiro com a quantidade de transições da máquina)
 **** transicao_t ***transicoes (descrição das transições da máquina, isso é, a função programa ou função de transição)
 *
 * Retorna: um elemento do tipo turint_t com todos dados passados como argumento
 */
turing_t *criarMaquina (int estadosComprimento, ...) {

}