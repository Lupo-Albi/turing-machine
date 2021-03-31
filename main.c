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
    int estadoSeguinte;
    int simboloGravado;
    int movimento;
} Transicao;

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
    Transicao ***transicoes;
} turing_t;



void main(int argc, char *argv[]) {
    
}

/*
 * Função: indiceEstado
 * ------------------------
 * Procura por um estado no conjunto de estados de uma máquina
 * 
 * *maquina: a máquina de Turing a qual possui um conjunto de estados
 * estado: estado que se deseja procurar no conjunto de estados da máquina
 * 
 * return: retorna o índice do estado. Retorna 0 caso não encontre nenhuma correspondência.
 */
int indiceEstado(turing_t *maquina, char *estado) {
    int indice;
    for (indice = 0; indice < maquina->estadosComprimento; indice++) {
        if (!strcmp(maquina->estados[indice], estado)) {
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
 * *maquina: a máquina de Turing a qual possui um conjunto de símbolos
 * simbolo: símbolo que se deseja procurar no conjunto de símbolos da máquina
 * 
 * return: retorna o índice do símbolo. Retorna 0 caso não encontre nenhuma correspondência
 */
int indiceSimbolo(turing_t *maquina, char simbolo) {
    int indice;

    for (indice = 0; indice < maquina->simbolosComprimento; indice++) {
        if (maquina->simbolos[indice] == simbolo) {
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
 * *maquina: a máquina de Turing a qual possui uma fita a ser lida e escrita
 * direcao: direção para a qual o leitor da fita deve se mover
 */
void moverFita(turing_t *maquina, int direcao) {
    fita_t *fitaAntesDoMovimento = maquina->fita;

    if (direcao == DIREITA) {
        // Verifica se o ponteito da fita e o ponteiro da sua direita são válidos
        if (fitaAntesDoMovimento && fitaAntesDoMovimento->direita) {
            // Move a fita para a direita
            maquina->fita = fitaAntesDoMovimento->direita;
        } else {
            maquina->fita = calloc(1, sizeof(fita_t));
            maquina->fita->simbolo = maquina->branco;

            if (fitaAntesDoMovimento) {
                // As duas linhas seguintes configuram um movimento para a direita porque a posição antiga da fita é movida para a esquerda da nova posição
                maquina->fita->esquerda = fitaAntesDoMovimento;
                fitaAntesDoMovimento->direita = maquina->fita;
            }
        }
    } else if (direcao == ESQUERDA) {
        // Verificia se o ponteiro da fita e o ponteiro da sua esquerda são válidos
        if (fitaAntesDoMovimento && fitaAntesDoMovimento->esquerda) {
            // Move a fita para a esquerda
            maquina->fita = fitaAntesDoMovimento->esquerda;
        } 
        else {
            maquina->fita = calloc(1, sizeof(fita_t));
            maquina->fita->simbolo = maquina->branco;

            if (fitaAntesDoMovimento) {
                // As duas linhas seguintes configuram um movimento para a esquerda porque a posição antiga da fita é movida para a direita da nova posição
                maquina->fita->direita = fitaAntesDoMovimento;
                fitaAntesDoMovimento->esquerda = maquina->fita;
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
 *  int estadosComprimento (apenas um valor inteiro)
 *  char **estados (cada estado deve ser escrito como uma string entre aspas duplas e separados por vírgula)
 *  int estadosFinaisComprimento (apenas um valor inteiro)
 *  int *estadosFinais (cada estado final pode ser escrito como uma string entre aspas duplas e separados por vírgula)
 *  int simbolosComprimento (apenas um valor inteiro)
 *  char *simbolos (cada símbolo deve ser escrito como um caractere entre aspas simples e separados por vírgula)
 *  int branco (um dos caractere que esteja presente nos símbolos do alfabeto escrito entre aspas simples)
 *  int estadoAtual (um dos estados que esteja presente nos estados escrito entre aspas dupla)
 *  int fitaComprimento (apenas um valor inteiro)
 *  fita_t *fita (conteúdo inicial da fita com cada símbolo escrito entre aspas simples)
 *  int transicoesComprimento (apenas um valor inteiro com a quantidade de transições da máquina)
 *  Transicao ***transicoes (descrição das transições da máquina, isso é, a função programa ou função de transição como descrito pelo tipo Transicao)
 *
 * Retorna: um elemento do tipo turing_t com todos dados passados como argumento
 */
turing_t *criarMaquina (int estadosComprimento, ...) {
    va_list argumentos; 
    va_start(argumentos, estadosComprimento);
    turing_t *maquina = malloc(sizeof(turing_t));
    int i;

    // Estados da máquina
    maquina->estadosComprimento = estadosComprimento;
    maquina->estados = malloc(estadosComprimento * sizeof(char *));
    for (i = 0; i < estadosComprimento; i++){
        maquina->estados[i] = va_arg(argumentos, char *);
    }

    // Estados finais da máquina
    maquina->estadosFinaisComprimento = va_arg(argumentos, int);
    maquina->estadosFinais = malloc(maquina->estadosFinaisComprimento * sizeof(int));
    // Utiliza a função indiceEstado para retornar os índices dos estados finais e guarda-los na variável maquina->estadosFinais
    for (i = 0; i < maquina->estadosFinaisComprimento; i++) {
        maquina->estadosFinais[i] = indiceEstado(maquina, va_arg(argumentos, char *));
    }

    // Símbolos do alfabeto
    maquina->simbolosComprimento = va_arg(argumentos, int);
    maquina->simbolos = malloc(maquina->simbolosComprimento * sizeof(char));
    for (i = 0; i < maquina->simbolos; i++) {
        maquina->simbolos[i] = va_arg(argumentos, char);
    }
    // Símbolo Branco
    maquina->branco = indiceSimbolo(maquina, va_arg(argumentos, char));
    // Estado inicial
    maquina->estadoAtual = indiceEstado(maquina, va_arg(argumentos, char *));

    // Fita da máquina
    // Comprimento inicial da fita
    maquina->fitaComprimento = va_arg(argumentos, int);
    // Inicialização da fita como vazia
    maquina->fita = NULL;
    // Configuração inicial da fita
    for (i = 0; i < maquina->fitaComprimento; i++) {
        moverFita(maquina, DIREITA);
        maquina->fita->simbolo = indiceSimbolo(maquina, va_arg(argumentos, char));
    }
    // Se a fita iniciar vazia, realiza um movimento para a direita e iniciando ela com um símbolo branco (funcionamento da função moverFita)
    if (!maquina->fitaComprimento) {
        moverFita(maquina, DIREITA);
    }
    // Move a fita para a esquerda até retornar ao seu início (até encontrar NULL)
    while (maquina->fita->esquerda) {
        maquina->fita = maquina->fita->esquerda;
    }

    // Função Programa da máquina
    maquina->transicoesComprimento = va_arg(argumentos, int);
    // A função programa é uma matriz que armazena a transição de acordo com o estado e símbolo lido, assim são feitas duas alocações: alocação pela quantidade de estados (linhas da matriz) e alocação dos símbolos do alfabeto para cada estado (colunas da matriz)
    maquina->transicoes = malloc(maquina->estadosComprimento * sizeof(Transicao *));
    for (i = 0; i < maquina->estadosComprimento; i++) {
        maquina->transicoes[i] = malloc(maquina->simbolosComprimento * sizeof(Transicao));
    }
    // Após ser criada a matriz da função programa, cria-se as transições, alocando o espaço para cada uma e as preenchendo de acordo com os argumentos passados
    for (i = 0; i < maquina->transicoesComprimento; i++) {
        Transicao *transicao = malloc(sizeof(Transicao));

        transicao->estadoAtual = indiceEstado(maquina, va_arg(argumentos, char *));
        transicao->simboloLido = indiceSimbolo(maquina, va_arg(argumentos, char));
        transicao->simboloGravado = indiceSimbolo(maquina, va_arg(argumentos, char));;
        transicao->movimento = va_arg(argumentos, int);
        transicao->estadoSeguinte = indiceEstado(maquina, va_arg(argumentos, char *));

        maquina->transicoes[transicao->estadoAtual][transicao->simboloLido] = transicao; // Salvando a transição na sua célula da matriz correspondente
    }
    va_end(argumentos);

    return maquina;
}

/*
 * Função: imprimirCI
 * -------------------------
 * Imprime a configuração instantânea da máquina, exibindo o estado atual e o conteúdo da fita
 *
 * *maquina: Máquina de Turing a ser feita a configuração instantânea da sua execução
 */
void imprimirCI(turing_t *maquina) {
    printf("%-10s ", maquina->estados[maquina->estadoAtual]);
    fita_t *fita = maquina->fita;

    while (fita){
        if (fita == maquina->fita){
            printf("[%c]", maquina->simbolos[fita->simbolo]);
        } else {
            printf(" %c ", maquina->simbolos[fita->simbolo]);
        }
        fita = fita->direita;
    }
    printf("/n");
}


/*
 * Função: executarMaquina
 * --------------------------------------
 * Executa a máquina de Turing e suas configuraões instantâneas pela execução. 
 *
 * *maquina: máquina de Turing a ser executada
 */
void executarMaquina(turing_t *maquina) {
    int i;
    int contador = 0;
    int maximoIteracoes = 9999;

    while(contador < maximoIteracoes) {
        imprimirCI(maquina);

        for (i = 0; i < maquina->estadosFinaisComprimento; i++) {
            if (maquina->estadosFinais[i] == maquina->estadoAtual) {
                return;
            }
        }

        // Executa a transição
        Transicao *transicao = maquina->transicoes[maquina->estadoAtual][maquina->fita->simbolo];
        maquina->fita->simbolo = transicao->simboloGravado;
        moverFita(maquina, transicao->movimento);
        maquina->estadoAtual = transicao->estadoSeguinte;
    }

}