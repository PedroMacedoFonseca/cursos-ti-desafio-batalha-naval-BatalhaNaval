#include <stdio.h>

//Declaração de Variaveis
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define AREA_AFETADA 5

#define LINHAS_HABILIDADE 3
#define COLUNAS_HABILIDADE 5

//Criando o tabuleiro só com água
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO])
{
    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
    {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++)
        {
            tabuleiro[i][j] = AGUA;
        }
    }
}

//Função de análise do espaço
int espacoLivre(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna)
{
    return tabuleiro[linha][coluna] == AGUA;
}

//Adicionando os navios no espaço
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char orientacao)
{
    if (orientacao == 'H' && coluna + TAMANHO_NAVIO <= TAMANHO_TABULEIRO)
    {
        for (int i = 0; i < TAMANHO_NAVIO; i++)
            if (!espacoLivre(tabuleiro, linha, coluna + i))
                return 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++)
            tabuleiro[linha][coluna + i] = NAVIO;
    }
    else if (orientacao == 'V' && linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO)
    {
        for (int i = 0; i < TAMANHO_NAVIO; i++)
            if (!espacoLivre(tabuleiro, linha + i, coluna))
                return 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++)
            tabuleiro[linha + i][coluna] = NAVIO;
    }
    else if (orientacao == 'E' && linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO && coluna - (TAMANHO_NAVIO - 1) >= 0)
    {
        for (int i = 0; i < TAMANHO_NAVIO; i++)
            if (!espacoLivre(tabuleiro, linha + i, coluna - i))
                return 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++)
            tabuleiro[linha + i][coluna - i] = NAVIO;
    }
    else if (orientacao == 'D' && linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO && coluna + TAMANHO_NAVIO <= TAMANHO_TABULEIRO)
    {
        for (int i = 0; i < TAMANHO_NAVIO; i++)
            if (!espacoLivre(tabuleiro, linha + i, coluna + i))
                return 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++)
            tabuleiro[linha + i][coluna + i] = NAVIO;
    }
    else
        return 0;
    return 1;
}

//Função para aplicar a habilidade sobre o tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int habilidade[LINHAS_HABILIDADE][COLUNAS_HABILIDADE])
{
    int offsetLinha = 1, offsetColuna = 2; //Centro da habilidade definida pelo tamanho da matriz da habilidade
    for (int i = 0; i < LINHAS_HABILIDADE; i++)
    {
        for (int j = 0; j < COLUNAS_HABILIDADE; j++)
        {
            if (habilidade[i][j] == 1)
            {
                int x = linha + i - offsetLinha, y = coluna + j - offsetColuna;
                if (x >= 0 && x < TAMANHO_TABULEIRO && y >= 0 && y < TAMANHO_TABULEIRO && tabuleiro[x][y] == AGUA)
                {
                    tabuleiro[x][y] = AREA_AFETADA;
                }
            }
        }
    }
}

// Aplica a habilidade "Cone"
void aplicarHabilidadeCone(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna)
{
    int cone[LINHAS_HABILIDADE][COLUNAS_HABILIDADE] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {1, 1, 1, 1, 1}};
    aplicarHabilidade(tabuleiro, linha, coluna, cone);
}

// Aplica a habilidade "Cruz"
void aplicarHabilidadeCruz(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna)
{
    int cruz[LINHAS_HABILIDADE][COLUNAS_HABILIDADE] = {
        {0, 0, 1, 0, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 1, 0, 0}};
    aplicarHabilidade(tabuleiro, linha, coluna, cruz);
}

// Aplica a habilidade "Octaedro"
void aplicarHabilidadeOctaedro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna)
{
    int octaedro[LINHAS_HABILIDADE][COLUNAS_HABILIDADE] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0}};
    aplicarHabilidade(tabuleiro, linha, coluna, octaedro);
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO])
{
    printf("   ");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
        printf("%d ", i);
    printf("\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
    {
        printf("%d  ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++)
            printf("%d ", tabuleiro[i][j]);
        printf("\n");
    }
}

int main()
{
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    posicionarNavio(tabuleiro, 3, 3, 'H');
    posicionarNavio(tabuleiro, 5, 5, 'V');
    posicionarNavio(tabuleiro, 2, 8, 'E');
    posicionarNavio(tabuleiro, 0, 0, 'D');

    aplicarHabilidadeCone(tabuleiro, 7, 3);
    aplicarHabilidadeCruz(tabuleiro, 1, 6);
    aplicarHabilidadeOctaedro(tabuleiro, 7, 7);

    exibirTabuleiro(tabuleiro);

    return 0;
}
