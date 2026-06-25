# Projeto Sistema de Mercado

Este projeto consiste em um sistema de gerenciamento de estoque e caixa, desenvolvido na linguagem C. O sistema permite realizar operações essenciais como cadastro de produtos, controle de vendas, atualização de preços e consulta de saldo, utilizando persistência de dados em arquivos binários.

## Integrantes
* Matheus de Oliveira Reis Pereira
* Marcos Vinicius Rodrigues da Costa
* Davi Miguel Moreira Resende 

## Funcionalidades

* **Persistência de Dados:** O sistema salva automaticamente o estado do estoque, o ID do último produto cadastrado e o saldo atual em um arquivo binário (`estoque.bin`), permitindo retomar o trabalho de onde parou.
* **Gerenciamento Dinâmico:** O estoque utiliza alocação dinâmica de memória (`malloc`/`realloc`), adaptando-se conforme novos produtos são adicionados.
* **Operações de Estoque:**
    * **Inserir Produto:** Cadastro de novos itens.
    * **Aumentar Estoque:** Reposição de mercadorias com ajuste automático no saldo.
    * **Modificar Preço:** Atualização de valores de produtos existentes.
* **Sistema de Vendas:** Processamento de vendas com decremento automático no estoque e atualização do saldo do caixa.
* **Consultas:** Verificação rápida do estoque atual e do saldo disponível.

## Comandos do Sistema

Ao executar o programa, utilize os seguintes comandos para navegar pelo menu:

| Comando | Descrição |
| :--- | :--- |
| **IP** | Inserir Produto |
| **AE** | Aumentar Estoque |
| **MP** | Modificar Preço |
| **VE** | Realizar Venda |
| **CE** | Consultar Estoque |
| **CS** | Consultar Saldo |
| **FE** | Finalizar o dia (Salvar e Sair) |

## Estrutura Técnica

O projeto baseia-se na struct `produto`:

```c
typedef struct produto {
    char nome[51];
    int id;
    int qtd;
    float preco;
} produto;
```

## Compilar e Executar
Certifique-se de ter um compilador C (como o gcc) instalado em seu sistema.

Abra o terminal na pasta do projeto.

Compile o código:

```Bash
gcc main.c -o mercadinho
```
Execute o programa:

Linux/macOS: 
```Bash
./mercadinho
```

Windows: 
```Bash
mercadinho.exe
```
