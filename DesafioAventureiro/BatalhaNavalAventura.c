#include <stdio.h>

// Declaração das variáveis
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// Função para inicializar o tabuleiro com água (valor 0).
// Essa função preenche toda a matriz do tabuleiro com o valor AGUA.
// indicando que, inicialmente, não há nenhum navio posicionado.
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO])
{
    // Loop externo para percorrer as linhas do tabuleiro
    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
    {
        // Loop interno para percorrer as colunas do tabuleiro
        for (int j = 0; j < TAMANHO_TABULEIRO; j++)
        {
            // Define a posição atual da matriz como água (0)
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para verificar se o espaço está livre
int espacoLivre(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna)
{
    return tabuleiro[linha][coluna] == AGUA;
}

// Função para posicionar um navio no tabuleiro com base na orientação especificada
// A função retorna 1 se o navio for posicionado com sucesso e 0 caso contrário
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char orientacao)
{
    // Caso a orientação seja horizontal ('H')
    if (orientacao == 'H')
    {
        // Verifica se o navio cabe na linha (considerando a largura do tabuleiro)
        if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO)
            return 0;
        // Verifica se os espaços necessários para o navio estão livres
        for (int i = 0; i < TAMANHO_NAVIO; i++)
        {
            if (!espacoLivre(tabuleiro, linha, coluna + i))
                return 0;
        }
        // Se todos os espaços estão livres, posiciona o navio horizontalmente
        for (int i = 0; i < TAMANHO_NAVIO; i++)
        {
            tabuleiro[linha][coluna + i] = NAVIO;
        }
    }
    // Caso a orientação seja vertical ('V')
    else if (orientacao == 'V')
    {
        // Verifica se o navio cabe na coluna (considerando a altura do tabuleiro)
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO)
            return 0;

        // Verifica se os espaços necessários para o navio estão livres
        for (int i = 0; i < TAMANHO_NAVIO; i++)
        {
            if (!espacoLivre(tabuleiro, linha + i, coluna))
                return 0;
        }

        // Se todos os espaços estão livres, posiciona o navio verticalmente
        for (int i = 0; i < TAMANHO_NAVIO; i++)
        {
            tabuleiro[linha + i][coluna] = NAVIO;
        }
    }
    // Caso a orientação seja diagonal de baixo para cima ('D')
    else if (orientacao == 'D')
    {
        // Verifica se o navio cabe diagonalmente (linha e coluna precisam permitir)
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO)
            return 0;

        // Verifica se os espaços necessários para o navio estão livres
        for (int i = 0; i < TAMANHO_NAVIO; i++)
        {
            if (!espacoLivre(tabuleiro, linha + i, coluna + i))
                return 0;
        }

        // Se todos os espaços estão livres, posiciona o navio diagonalmente de baixo para cima
        for (int i = 0; i < TAMANHO_NAVIO; i++)
        {
            tabuleiro[linha + i][coluna + i] = NAVIO;
        }
    }
    // Caso a orientação seja diagonal de cima para baixo ('E')
    else if (orientacao == 'E')
    {
        // Verifica se o navio cabe diagonalmente (linha e coluna precisam permitir)
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || coluna - (TAMANHO_NAVIO - 1) < 0)
            return 0;

        // Verifica se os espaços necessários para o navio estão livres
        for (int i = 0; i < TAMANHO_NAVIO; i++)
        {
            if (!espacoLivre(tabuleiro, linha + i, coluna - i))
                return 0;
        }

        // Se todos os espaços estão livres, posiciona o navio diagonalmente de cima para baixo
        for (int i = 0; i < TAMANHO_NAVIO; i++)
        {
            tabuleiro[linha + i][coluna - i] = NAVIO;
        }
    }

    // Caso a orientação seja inválida
    else
    {
        return 0;
    }
    // Se o navio foi posicionado com sucesso, retorna 1
    return 1;
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO])
{
    // Imprime a linha de cabeçalho com a numeração das colunas (0, 1, 2, ...)
    printf("   ");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
    {
        printf("%d ", i); // Imprime o índice da coluna
    }
    printf("\n");

    // Imprime cada linha do tabuleiro
    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
    {
        // Imprime a numeração da linha à esquerda (0, 1, 2, ...)
        printf("%d  ", i);

        // Imprime os valores das células da linha atual
        for (int j = 0; j < TAMANHO_TABULEIRO; j++)
        {
            // Cada célula do tabuleiro será representada por um número (por exemplo, 0 para água, 1 para navio)
            printf("%d ", tabuleiro[i][j]);
        }

        // Pula para a próxima linha após imprimir todos os valores da linha atual
        printf("\n");
    }
}

int main()
{
    // Declaração do tabuleiro com o tamanho definido por 'TAMANHO_TABULEIRO'
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    inicializarTabuleiro(tabuleiro);

    // Posicionar 4 navios no tabuleiro com diferentes orientações (horizontal, vertical, diagonal)
    // Posiciona um navio horizontal na linha 3, coluna 3. A orientação 'H' significa que o navio será colocado horizontalmente
    posicionarNavio(tabuleiro, 3, 3, 'H');
    
    // Posiciona um navio vertical na linha 5, coluna 5. A orientação 'V' significa que o navio será colocado verticalmente
    posicionarNavio(tabuleiro, 5, 5, 'V');
    
    // Posiciona um navio diagonal na linha 0, coluna 0. A orientação 'D' significa que o navio será colocado diagonalmente de cima para baixo (diagonal normal)
    posicionarNavio(tabuleiro, 0, 0, 'D');
    
    // Posiciona um navio diagonal na linha 3, coluna 9. A orientação 'E' significa que o navio será colocado diagonalmente de baixo para cima (diagonal invertida)
    posicionarNavio(tabuleiro, 3, 9, 'E');

    // Exibe o tabuleiro atual, mostrando a posição dos navioses
    exibirTabuleiro(tabuleiro);

    return 0;
}

