#include <iostream>

// Classe pra simular um CONJUNTO de matemática, mas com números
class MeuConjunto
{
private:
    //  guarda os números do conjunto
    int *vetorDados;
    // Quantos números já colocamos
    int quantosTem;
    // O tamanho máximo do vetor (capacidade atual)
    int maximoEspaco;

    // Função pra aumentar o vetor
    void cresceVetor()
    {
        maximoEspaco *= 2;
        int *novoVetor = new int[maximoEspaco];

        // Copia tudo do vetor velho pro novo
        for (int i = 0; i < quantosTem; ++i)
        {
            novoVetor[i] = vetorDados[i];
        }

        // Usando o nvoo vetor
        delete[] vetorDados;
        vetorDados = novoVetor;
    }

public:
    // Construtor: Começa com um espaço pequeno
    MeuConjunto(int capacidadeInicial = 4) : quantosTem(0), maximoEspaco(capacidadeInicial)
    {
        vetorDados = new int[maximoEspaco];
    }

    // Destrutor: Limpa a memória
    ~MeuConjunto()
    {
        delete[] vetorDados;
    }

    // Construtor de Cópia
    MeuConjunto(const MeuConjunto &outro) : quantosTem(outro.quantosTem), maximoEspaco(outro.maximoEspaco)
    {
        vetorDados = new int[maximoEspaco];
        // Copia os números
        for (int i = 0; i < quantosTem; ++i)
        {
            vetorDados[i] = outro.vetorDados[i];
        }
    }

    // --- Operações de Conjunto ---

    // Confere se está no conjunto
    bool jaTem(int numero) const
    {
        for (int i = 0; i < quantosTem; ++i)
        {
            if (vetorDados[i] == numero)
            {
                return true;
            }
        }
        return false;
    }

    // Coloca um número no conjunto
    void adicionar(int numero)
    {
        if (jaTem(numero))
        {
            return;
        }

        if (quantosTem == maximoEspaco)
        {
            cresceVetor();
        }

        vetorDados[quantosTem] = numero;
        quantosTem++;
    }

    // Tira um número do conjunto
    void remover(int numero)
    {
        for (int i = 0; i < quantosTem; ++i)
        {
            if (vetorDados[i] == numero)
            {

                vetorDados[i] = vetorDados[quantosTem - 1];
                quantosTem--;
                return; // Removeu
            }
        }
    }

    // Faz a UNIÃO
    static MeuConjunto *fazUniao(const MeuConjunto &A, const MeuConjunto &B)
    {
        // Começa com uma cópia do conjunto A
        MeuConjunto *resultado = new MeuConjunto(A);

        // Adiciona todos os números de B no resultado
        for (int i = 0; i < B.quantosTem; ++i)
        {
            resultado->adicionar(B.vetorDados[i]);
        }
        return resultado;
    }

    // Faz a INTERSEÇÃO
    static MeuConjunto *fazIntersecao(const MeuConjunto &A, const MeuConjunto &B)
    {
        MeuConjunto *resultado = new MeuConjunto();

        for (int i = 0; i < A.quantosTem; ++i)
        {

            if (B.jaTem(A.vetorDados[i]))
            {
                resultado->adicionar(A.vetorDados[i]);
            }
        }
        return resultado;
    }

    // Mostra o conjunto
    void mostrar() const
    {
        std::cout << "Conjunto: {";
        for (int i = 0; i < quantosTem; ++i)
        {
            std::cout << vetorDados[i] << (i < quantosTem - 1 ? ", " : "");
        }
        std::cout << "}\n";
    }
};

int main()
{

    std::cout << "--- Teste do Conjunto ---\n";

    // Cria o Conjunto A e adiciona uns números
    MeuConjunto A;
    A.adicionar(1);
    A.adicionar(2);
    A.adicionar(3);
    A.adicionar(5);
    std::cout << "Conjunto A:\n";
    A.mostrar();

    // Cria o Conjunto B e adiciona outros
    MeuConjunto B;
    B.adicionar(3);
    B.adicionar(4);
    B.adicionar(5);
    B.adicionar(6);
    std::cout << "Conjunto B:\n";
    B.mostrar();

    // Calcula a União e imprime
    MeuConjunto *uniao_result = MeuConjunto::fazUniao(A, B);
    std::cout << "Uniao (A e B):\n";
    uniao_result->mostrar();

    // Calcula a Interseção e imprime
    MeuConjunto *intersecao_result = MeuConjunto::fazIntersecao(A, B);
    std::cout << "Intersecao (so o que e igual):\n";
    intersecao_result->mostrar();

    // delete do resultado
    delete uniao_result;
    delete intersecao_result;
    return 0;
}