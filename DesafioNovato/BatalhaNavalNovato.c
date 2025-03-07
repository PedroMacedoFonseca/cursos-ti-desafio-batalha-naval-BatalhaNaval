#include <stdio.h>

// Constantes para definir tamanho do tabuleiro e dos navios
const int tamanho_tabuleiro = 10; // O tabuleiro será de 10x10
const int tamanho_navio = 3; // O navio terá 3 unidades de comprimento
const int agua = 0; // Representação da água (células vazias)
const int navio = 3; // Representação do navio (ocupa as células do tabuleiro)

// Função para inicializar o tabuleiro com a água (0)
void inicializarTabuleiro(int tabuleiro[tamanho_tabuleiro][tamanho_tabuleiro]) {
    // Laço para percorrer todas as células do tabuleiro
    for (int i = 0; i < tamanho_tabuleiro; i++) {
        for (int j = 0; j < tamanho_tabuleiro; j++) {
            tabuleiro[i][j] = agua; // Define todas as células como água (0)
        }
    }
}

// Função para posicionar um navio no tabuleiro
int posicionarNavio(int tabuleiro[tamanho_tabuleiro][tamanho_tabuleiro], int linha, int coluna, char orientacao) {
    // Verifica a orientação do navio
    if (orientacao == 'H') { // Navio na orientação horizontal
        // Verifica se o navio cabe dentro da linha sem ultrapassar os limites
        if (coluna + tamanho_navio > tamanho_tabuleiro) return 0; // Caso ultrapasse, retorna 0 (falha)
        
        // Verifica se o navio irá sobrepor outro já existente
        for (int i = 0; i < tamanho_navio; i++) {
            if (tabuleiro[linha][coluna + i] == navio) return 0; // Já há um navio aqui, falha
        }
        
        // Posiciona o navio no tabuleiro
        for (int i = 0; i < tamanho_navio; i++) {
            tabuleiro[linha][coluna + i] = navio; // Preenche as células com o valor do navio (3)
        }
    } else if (orientacao == 'V') { // Navio na orientação vertical
        // Verifica se o navio cabe na coluna sem ultrapassar os limites
        if (linha + tamanho_navio > tamanho_tabuleiro) return 0; // Caso ultrapasse, retorna 0 (falha)
        
        // Verifica se o navio irá sobrepor outro navio
        for (int i = 0; i < tamanho_navio; i++) {
            if (tabuleiro[linha + i][coluna] == navio) return 0; // Já há um navio aqui, falha
        }
        
        // Posiciona o navio no tabuleiro
        for (int i = 0; i < tamanho_navio; i++) {
            tabuleiro[linha + i][coluna] = navio; // Preenche as células com o valor do navio (3)
        }
    } else {
        return 0; // Se a orientação não for 'H' ou 'V', retorna 0 (falha)
    }
    
    return 1; // Se tudo ocorrer bem, retorna 1 (sucesso)
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[tamanho_tabuleiro][tamanho_tabuleiro]) {
    // Exibe os índices das colunas
    printf("  ");
    for (int i = 0; i < tamanho_tabuleiro; i++) {
        printf("%d ", i); // Exibe os números das colunas no topo
    }
    printf("\n");
    
    // Exibe as linhas do tabuleiro
    for (int i = 0; i < tamanho_tabuleiro; i++) {
        printf("%d ", i); // Exibe o número da linha à esquerda
        for (int j = 0; j < tamanho_tabuleiro; j++) {
            printf("%d ", tabuleiro[i][j]); // Exibe o conteúdo de cada célula
        }
        printf("\n"); 
    }
}

// Função principal onde o jogo é executado
int main() {
    int tabuleiro[tamanho_tabuleiro][tamanho_tabuleiro]; // Declara o tabuleiro
    
    // Inicializa o tabuleiro com água (0)
    inicializarTabuleiro(tabuleiro);
    
    // Definindo manualmente as posições dos navios
    int linhaNavio1 = 2, colunaNavio1 = 3; // Posição do primeiro navio
    int linhaNavio2 = 5, colunaNavio2 = 6; // Posição do segundo navio
    
    // Tenta posicionar o primeiro navio de forma horizontal
    if (!posicionarNavio(tabuleiro, linhaNavio1, colunaNavio1, 'H')) {
        printf("Falha ao posicionar o navio horizontal!\n");
    }
    
    // Tenta posicionar o segundo navio de forma vertical
    if (!posicionarNavio(tabuleiro, linhaNavio2, colunaNavio2, 'V')) {
        printf("Falha ao posicionar o navio vertical!\n");
    }
    
    // Exibe o tabuleiro após os posicionamentos
    exibirTabuleiro(tabuleiro);
    
    return 0; // Fim do programa
}
