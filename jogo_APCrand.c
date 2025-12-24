#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define linhas 10
#define colunas 5
#define arquivo_ranking "ranking.bin"


//armazena os dados do jogador
typedef struct {

    char nickname[100];
    int pontuacao;

} dadosjogador;



int matriz_jogo[linhas][colunas] = {0}; //inicializando a matriz com zeros
char nome[100];  // variavel para armazenar o nome do jogador
int score = 0;  // variavel para armazenar o score
int altura[colunas] = {0};
FILE *arquivo_numeros;



//Funcao que limpa a tela
void limpatela() {

    #ifdef _WIN32
        system("cls");

    #else
        system("clear");

    #endif
}


//Funcao para exibir o nome do jogo na tela
//Funcao para armazenar o nome do jogador
void tela_inicial() {

    printf("===============> JOGO DE APC <===============\n");

    printf("\n- -> Digite seu nickname |");
    //lE o nome do jogador
    fgets(nome, sizeof(nome), stdin);
    //remove a nova linha
    nome[strcspn(nome, "\n")] = 0;
    //limpa a tela apAs a insercao do nome
    limpatela();

}



//Funcao que printa o tabuleiro do jogo
void exibir_tab(int nro, int nro_seguinte, char *nome) {

    limpatela();

    //mostra o nome do jogador e o score
    printf("           +----+  +----+\t - - - - - - - - - - - - - - - - - - - - - - - - - ->\n");
    printf("           |%4d|  |%4d|\t JOGADOR: %s            SCORE: %d\n", nro, nro_seguinte, nome, score);
    printf("           +----+  +----+\t - - - - - - - - - - - - - - - - - - - - - - - - - ->\n");

    //mostra o tabuleiro do jogo em matriz
    for (int i = 0; i < linhas; i++) {

        printf("  +----+----+----+----+----+\n");
        printf("  |");

        for (int j = 0; j < colunas; j++) {

            if (matriz_jogo[i][j] != 0){
                //exibe o n�mero dentro da c�lula
                printf("%4d|", matriz_jogo[i][j]);

            } else {

                //exibe um espa�o vazio
                printf("    |");
            }
        }

        printf("\n");
    }

    printf("  +----+----+----+----+----+\n");
    printf("  +----+----+----+----+----+\t");
    printf("- - -> Digite 9 para sair\n");
    printf("  |  1 |  2 |  3 |  4 |  5 |\n");;
    printf("  +----+----+----+----+----+\n\n");

}


//Funcao para escolher a coluna onde o numero sera inserido
int escolher_coluna() {

    int leitura;

    printf("-> Digite a coluna do numero |");
    //leitura da celula escolhida
    scanf("%d", &leitura);

    getchar();

    return leitura;
}


//Funcao para escolher a linha disponivel para a aplicacao do numero na celula
int encontrar_linha(int coluna) {

    for (int i = linhas - 1; i >= 0; i--) {

        //verifica se a c�lula est� vazia
        if (matriz_jogo[i][coluna] == 0) {

            return i; //retorna a primeira linha vazia
        }
    }
    //se nao tiver linha dispon�vel, retorna -1
    return -1;
}


//Funcao para zerar a matriz no fim do jogo
void reiniciar_jogo() {

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {

            matriz_jogo[i][j] = 0; //zera a matriz
        }
    }

    score = 0; //o score zera
}



//funcao para verificar para fazer fusoes dos numeros iguais
void verificar_fusao() {

    int fusao = 1;

    while (fusao) {

        fusao = 0;

        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                if (matriz_jogo[i][j] != 0) {

                    int num = matriz_jogo[i][j];

                    if (i < linhas - 1 && matriz_jogo[i + 1][j] == num) {
                        matriz_jogo[i + 1][j] *= 2;
                        matriz_jogo[i][j] = 0;
                        score += matriz_jogo[i + 1][j];
                        fusao = 1;

                    } else if (j < colunas - 1 && matriz_jogo[i][j + 1] == num) {
                        matriz_jogo[i][j + 1] *= 2;
                        matriz_jogo[i][j] = 0;
                        score += matriz_jogo[i][j + 1];
                        fusao = 1;
                    }

                    if (j < colunas - 1 && i < linhas - 1 && matriz_jogo[i][j + 1] == num && matriz_jogo[i + 1][j] == num) {

                        matriz_jogo[i][j] = num * 4;
                        matriz_jogo[i][j + 1] = 0;
                        matriz_jogo[i + 1][j] = 0;
                        score += matriz_jogo[i][j];
                        fusao = 1;
                    }
                }
            }
        }
    }
}


//Funcao para queda dos numeros apos a fusao
void gravidade() {

    for (int j = 0; j < colunas; j++) {
        for (int i = linhas - 1; i > 0; i--) {
            if (matriz_jogo[i][j] == 0) {
                for (int k = i; k > 0; k--) {
                    matriz_jogo[k][j] = matriz_jogo[k - 1][j];
                }

                matriz_jogo[0][j] = 0;
            }
        }
    }
}


//Funcao para processar a jogada
void processar_jogada(int linha, int coluna, int nro) {

    matriz_jogo[linha][coluna] = nro;
    altura[coluna]++;

    verificar_fusao();
    gravidade();
}



//Funcao que verifica se o jogo acabou
int verificar_fim() {

    for (int i = 0; i < colunas; i++) {

        //se sentir tiver celulas vazias na primeira linha
        //o jogo n�o acabou
        if (matriz_jogo[0][i] == 0) {

            return 0;
        }
    }

    //fim de jogo
    return 1;
}



//Funcao que exibe a area "4 - ranking"
//Composta e implementada dentro do "menu"
void exibir_ranking() {

    dadosjogador ranking[100];

    FILE *arquivo = fopen(arquivo_ranking, "rb");

    if (arquivo == NULL) {
        printf("                       AINDA SEM RANKING\n\n");
        printf("                    JOGUE E APARECA NO RANKING!\n");

        return;
    }

    // Carrega o ranking
    int i = 0;

    while (fread(&ranking[i], sizeof(dadosjogador), 1, arquivo)) {
        i++;
    }

    fclose(arquivo);

    // Ordena o ranking por pontua��o (ordem decrescente)
    for (int j = 0; j < i - 1; j++) {
        for (int k = j + 1; k < i; k++) {

            if (ranking[j].pontuacao < ranking[k].pontuacao) { //condiçao para ser decrescente

                dadosjogador temp = ranking[j]; //ordena o ranking
                ranking[j] = ranking[k];
                ranking[k] = temp;
            }
        }
    }

    // Exibe o ranking
    printf("-------------------> RANKING <-----------------------\n\n");

    for (int j = 0; j < i; j++) {

        printf("%d. %s - - - - - - -> %d pontos\n", j + 1, ranking[j].nickname, ranking[j].pontuacao);
    }
}


// Funcao para adicionar o jogador ao arquivo de ranking
void adicionar_ao_ranking(char *nickname, int pontuacao) {

    dadosjogador novojogador;
    strcpy(novojogador.nickname, nickname);
    novojogador.pontuacao = pontuacao;

    FILE *arquivo = fopen(arquivo_ranking, "ab");

    fwrite(&novojogador, sizeof(dadosjogador), 1, arquivo);
    fclose(arquivo);
}


// Funcao para zerar o ranking (deletar o arquivo)
void zerar_ranking() {

    if (remove(arquivo_ranking) == 0) {

        printf("- - - -> RANKING ZERADO - - - - - - - - \n");

    } else {
        printf("- - - -> RANKING JA ESTA ZERADO - - - - \n");

    }
}



//Funcao que exibe a area "2 - configuracoes"
//composta e implementada dentro do "menu"
void configuracoes() {

    int escolha;

    while (1) {

        char leitura;

        printf("-----------------> CONFIGURACOES <------------------- \n\n");

        printf("1. - - -> ZERAR RANKING\n");
        printf("2. - - -> MODO DE DIFICULDADE\n");
        printf("3. - - -> VOLTAR AO MENU PRINCIPAL\n\n");

        printf(" - - - -> Digite a opcao desejada: ");
        scanf("%d", &escolha);

        getchar();

        switch (escolha) {
            case 1:
                limpatela();

                printf(" VOCE TEM CERTEZA? ");
                scanf("%c", &leitura);
                //limpa tela apos a escolha
                limpatela();

                if (leitura == 'N' || leitura == 'n'){
                    getchar();
                    return configuracoes();


                } else {
                    getchar();
                    zerar_ranking();

                }

                break;

            case 2:
                limpatela();
                printf(" - - - -> EM DESENVOLVIMENTO...\n");

                break;

            case 3:
                limpatela();
                //retorna ao menu principal
                return;
        }

        getchar();
        limpatela();
    }
}


//Funcao que exibe a area "3 - Instrucoes"
//Composta e implementada dentro do "menu"
void instrucoes() {

    printf("- - - - - - - -> INSTRUCOES <- - - - - - - - - \n\n\n");

    printf("- -> OBJETIVOS:\n");
    printf("      O objetivo do Jogo de APC e combinar os numeros em um tabuleiro ate o numero 2048 ser formado!.\n");
    printf("      Coloque os numeros nas colunas (1-5) e coloque em pecas iguais formando uma peca com \n");
    printf("       o dobro do valor.\n");
    printf("      O jogo termina quando o tabuleiro estiver cheio e voce nao puder fazer mais movimentos validos.\n");
    printf("      Voce ganha quando alguma celula chegar a 2048!\n\n");

    printf("- -> COMO JOGAR:\n");
    printf("      1. O tabuleiro e uma matriz de 10x5.\n");
    printf("      2. Cada celula do tabuleiro pode conter um numero.\n");
    printf("      3. Voce pode colocar as pecas nas colunas de 1 a 5.\n");
    printf("      4. Quando duas pecas com o mesmo valor se encontram, elas se combinam e formam uma nova peca com o dobro do valor.\n");
    printf("      5. O jogo termina quando o tabuleiro estiver cheio.\n");
    printf("      6. O objetivo e alcancar uma celula com o numero '2048'.\n\n");

    printf("- -> Dicas:\n");
    printf("     - Tente manter as pecas maiores em um canto do tabuleiro.\n");
    printf("     - Planeje seus movimentos para evitar que o tabuleiro fique bloqueado.\n\n\n");

    printf("Tecla <enter> para proseguir\n");

    //aguarda o jogador teclar enter para voltar ao menu
    getchar();
    limpatela();
}



//funcao que executa o jogo
void jogar(char *nome) {
    reiniciar_jogo();
    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios

    int numeros[] = {2, 4, 8, 16, 32, 64, 128};
    int tamanho = sizeof(numeros) / sizeof(numeros[0]);

    int leitura = 0;
    int nro = numeros[rand() % tamanho]; // Gera um número aleatório da lista
    int nro_seguinte = numeros[rand() % tamanho];

    while (leitura != 9) {
        exibir_tab(nro, nro_seguinte, nome);
        leitura = escolher_coluna();

        if (leitura == 9) {
            adicionar_ao_ranking(nome, score);
            return;
        }

        int coluna = leitura - 1;
        if (coluna < 0 || coluna >= colunas) {
            printf("Coluna Invalida. Tente de 1 a 5!\n");
            getchar();
            continue;
        }

        int linha_disponivel = encontrar_linha(coluna);
        if (linha_disponivel != -1) {
            processar_jogada(linha_disponivel, coluna, nro);
            nro = nro_seguinte;
            nro_seguinte = numeros[rand() % tamanho]; // Gera um novo número aleatório da lista
        }

        if (verificar_fim()) {
            adicionar_ao_ranking(nome, score);
            limpatela();
            printf("\n\n\n\n\n\t\t GAME OVER!!!");
            getchar();
            return;
        }
    }
    limpatela();
}



int main() {

    //exibe a tela inicial
    //salva o nome do jogador
    tela_inicial();

    int selecao;

    while (1) {

        limpatela();

        printf(" ====================JOGO DE APC=====================\n\n\n");

        printf("1. - - -> JOGAR\n");
        printf("2. - - -> CONFIGURACOES\n");
        printf("3. - - -> INSTRUCOES\n");
        printf("4. - - -> RANKING\n");
        printf("5. - - -> SAIR\n\n");


        printf("- - - -> Digite a Opcao Desejada: ");
        scanf("%d", &selecao);

        getchar();
        limpatela();

        switch (selecao) {
            case 1:
               //exibe a area do jogo
               jogar(nome);
                break;

            case 2:
                //exibe as configura��es
                configuracoes();
                break;

            case 3:
                //exibe as instru��es
                instrucoes();
                break;

            case 4:
                //exibe o Ranking
                exibir_ranking();

                printf("\n\nPressione <enter> para voltar ao menu\n");
                getchar();

                break;

            case 5:
                //encerra o programa
                return 0;
        }
    }

    return 0;
}

//a falta de acentuacao serve para nao alternar os caracteres na execucao do codigo
//macos ---