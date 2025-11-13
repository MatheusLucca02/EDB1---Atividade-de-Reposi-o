#include <iostream>

// Sequência Dinâmica
class SequenciaDinamica
{
private:
    // O ponteiro para o array
    int *elementos;
    // Quantos elementos já tem no array
    int tamanho_atual;
    // O espaço máximo que o array comporta
    int capacidade_maxima;

    // Aumenta o array quando ele atinge a capacidade máxima
    void realoca_memoria()
    {
        capacidade_maxima *= 2;
        int *novo_array = new int[capacidade_maxima];

        // Copia os elementos antigos
        for (int i = 0; i < tamanho_atual; ++i)
        {
            novo_array[i] = elementos[i];
        }

        // Libera a memória
        delete[] elementos;
        elementos = novo_array;
    }

public:
    // Construtor - Inicializa com uma capacidade padrão
    SequenciaDinamica(int capacidade_inicial = 4)
        : tamanho_atual(0), capacidade_maxima(capacidade_inicial)
    {
        elementos = new int[capacidade_maxima];
    }

    // Destrutor -  Libera a memória alocada dinamicamente
    ~SequenciaDinamica()
    {
        delete[] elementos;
    }

    // Funções necessárias

    // Insere um elemento numa posição desejada
    void insere(int posicao, int valor_elemento)
    {
        if (posicao < 0 || posicao > tamanho_atual)
        {
            std::cout << "Erro: Posicao invalida !.\n";
            return;
        }

        if (tamanho_atual == capacidade_maxima)
        {
            realoca_memoria(); // Realoca quando lotado
        }

        // Desloca elementos para a direita
        for (int i = tamanho_atual; i > posicao; --i)
        {
            elementos[i] = elementos[i - 1];
        }

        // Insere o novo elemento
        elementos[posicao] = valor_elemento;
        tamanho_atual++;
    }

    // Remove o elemento numa posição desejada
    void remove(int posicao)
    {
        if (posicao < 0 || posicao >= tamanho_atual)
        {
            std::cout << "Erro: Posicao invalida !.\n";
            return;
        }

        // Desloca elementos para a esquerda
        for (int i = posicao; i < tamanho_atual - 1; ++i)
        {
            elementos[i] = elementos[i + 1];
        }

        tamanho_atual--;
    }

    // Retorna o elemento que está em uma posição
    int obtem_elemento(int posicao) const
    {
        if (posicao < 0 || posicao >= tamanho_atual)
        {
            std::cout << "Erro: Posicao invalida !.\n";
            return -1;
        }
        return elementos[posicao];
    }

    // Mostra todos os elementos
    void imprime() const
    {
        std::cout << "Sequenccia (" << tamanho_atual << "/" << capacidade_maxima << "): [";
        for (int i = 0; i < tamanho_atual; ++i)
        {
            std::cout << elementos[i] << (i < tamanho_atual - 1 ? ", " : "");
        }
        std::cout << "]\n";
    }
};

int main()
{

    SequenciaDinamica seq(2);
    std::cout << "--- Teste da Sequencia Dinamica ---\n";

    // Coloca 10 elementos
    for (int i = 0; i < 10; ++i)
    {
        seq.insere(i, (i + 1) * 10);
    }
    std::cout << "Sequencia Inicial com 10 elementos:\n";
    seq.imprime();

    // Remove 2 elementos, posicoes 5 e 2
    seq.remove(4);
    seq.remove(2);

    std::cout << "Sequencia depois da Remocao:\n";
    seq.imprime();

    // Obtém um elemento para conferir (posicao 5)
    int valor = seq.obtem_elemento(5);
    std::cout << "O elemento na posicaoo 2 e: " << valor << "\n";

    return 0;
}
