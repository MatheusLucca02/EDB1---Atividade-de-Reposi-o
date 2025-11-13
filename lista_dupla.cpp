#include <iostream>

// Estrutura para um "Elo" da lista
struct Elo
{
    int valor;
    Elo *anterior; // Conexao para o Elo de trás
    Elo *proximo;  // Conexao para o Elo da frente

    // Construtor do Elo
    Elo(int v, Elo *ant = nullptr, Elo *prox = nullptr) : valor(v), anterior(ant), proximo(prox) {}
};

// Classe principal da Lista Duplamente Encadeada, sentinelas
class ListaDupla
{
private:
    Elo *cabeca; // Sentinela de começo
    Elo *cauda;  // Sentinela de fim

    // Função interna pra remover qualquer Elo
    void desligaElo(Elo *elo_a_remover)
    {
        // Ignora se for sentinela ou nulo
        if (elo_a_remover == cabeca || elo_a_remover == cauda || elo_a_remover == nullptr)
            return;

        // Refaz as conexões
        elo_a_remover->anterior->proximo = elo_a_remover->proximo;
        // Elo próximo aponta para o anterior do removido
        elo_a_remover->proximo->anterior = elo_a_remover->anterior;

        delete elo_a_remover;
    }

public:
    // Construtor: Cria as duas sentinelas ligadas
    ListaDupla()
    {
        cabeca = new Elo(0); // Sentinela
        cauda = new Elo(0);  // Sentinela
        cabeca->proximo = cauda;
        cauda->anterior = cabeca;
    }

    // Destrutor: Limpa todos os Elos da lista e as sentinelas no final
    ~ListaDupla()
    {
        Elo *atual = cabeca->proximo;
        while (atual != cauda)
        {
            Elo *proximo_elo = atual->proximo;
            delete atual; // Deleta Elo atual
            atual = proximo_elo;
        }
        delete cabeca;
        delete cauda;
    }

    // --- Operações de Inserção ---

    // Coloca um novo Elo no começo
    void insereNoComeco(int valor)
    {
        // Novo Elo aponta para cabeca e para o primeiro Elo existente
        Elo *novo_elo = new Elo(valor, cabeca, cabeca->proximo);

        cabeca->proximo->anterior = novo_elo;
        cabeca->proximo = novo_elo;
    }

    // Coloca um novo Elo no fim
    void insereNoFim(int valor)
    {
        // Novo Elo aponta para o último Elo existente e para a cauda
        Elo *novo_elo = new Elo(valor, cauda->anterior, cauda);

        cauda->anterior->proximo = novo_elo;
        cauda->anterior = novo_elo;
    }

    // --- Operações de Remoção ---

    // Remove o Elo do começo e retorna o valor
    int removeDoComeco()
    {
        Elo *pra_remover = cabeca->proximo;
        if (pra_remover == cauda)
        { // Lista vazia
            std::cout << "ERRO: Lista vazia. ERRO.\n";
            return -1;
        }
        int valor_removido = pra_remover->valor;
        desligaElo(pra_remover);
        return valor_removido;
    }

    // Remove o Elo do fim e retorna o valor
    int removeDoFim()
    {
        Elo *pra_remover = cauda->anterior;
        if (pra_remover == cabeca)
        { // Lista vazia
            std::cout << "ERRO: Lista vazia. ERRO.\n";
            return -1;
        }
        int valor_removido = pra_remover->valor;
        desligaElo(pra_remover);
        return valor_removido;
    }

    // --- Funções de Impressão e Auxiliares ---

    // Imprime a lista do começo para o fim
    void mostraPraFrente() const
    {
        std::cout << "Lista (->): [";
        Elo *atual = cabeca->proximo;
        while (atual != cauda)
        {
            std::cout << atual->valor << (atual->proximo != cauda ? ", " : "");
            atual = atual->proximo;
        }
        std::cout << "]\n";
    }

    // Imprime a lista do fim para o começo
    void mostraPraTras() const
    {
        std::cout << "Lista (<-): [";
        Elo *atual = cauda->anterior;
        while (atual != cabeca)
        {
            std::cout << atual->valor << (atual->anterior != cabeca ? ", " : "");
            atual = atual->anterior;
        }
        std::cout << "]\n";
    }

    // Ajuda para se a lista está vazia
    bool estaVazia() const
    {
        return cabeca->proximo == cauda;
    }
};

int main()
{
    // Teste Sugerido
    std::cout << "--- Teste Lista Duplamente Encadeada (TAD) ---\n";
    ListaDupla lista;

    lista.insereNoFim(10);
    lista.insereNoFim(20);
    lista.insereNoFim(30);
    lista.insereNoFim(40);
    std::cout << "Lista depois de colocar os numeros:\n";
    lista.mostraPraFrente();

    // Remove o ultimo e ve o que saiu
    int saiu_do_fim = lista.removeDoFim();
    std::cout << "Elemento que saiu do final: " << saiu_do_fim << "\n";

    // Vê como a lista ficou nos dois sentidos
    std::cout << "Lista depois da remocao:\n";
    lista.mostraPraFrente();
    lista.mostraPraTras();

    // Remove do começo
    int saiu_do_comeco = lista.removeDoComeco();
    std::cout << "Elemento que saiu do comeco: " << saiu_do_comeco << "\n";
    lista.mostraPraFrente();

    return 0;
}
