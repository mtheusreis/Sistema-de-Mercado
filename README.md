# Sistema de Mercado (Protótipo)

Este é o protótipo inicial de um sistema de gerenciamento de mercado desenvolvido em Linguagem C (padrão C99). O objetivo desta versão é testar a lógica central das funções de manipulação de estoque, precificação e fluxo de caixa utilizando alocação dinâmica de memória, antes da implementação da persistência em arquivos.

---

## Integrantes do Grupo
* Matheus de Oliveira Reis Pereira
* Marcos
* Davi Miguel Moreira Resende 

---

## Estrutura

O sistema utiliza uma `struct` para agrupar as características essenciais de cada produto:
```c
typedef struct produto {
    char nome[51]; // Nome do produto
    int id;        // Código identificador único
    int qtd;       // Quantidade atual em estoque
    float preco;   // Preço de venda
} produto;
