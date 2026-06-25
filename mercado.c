/*
PROJETO MERCADINHO
O objetivo principal do projeto é criar um sistema que permita
o gerenciamento de um mercado. Por meio de diversas funções será possível 
realizar ações como adição de produtos e vendas. As três variáveis principais
do nosso código são: O saldo, que se altera de acordo com processos de 
venda e compra. O ID (código do produto), que é único por produto adicionado
e começa no zero, sendo incrementado a cada novo produto. Além disso, no nosso
programa, o ID também representa o número de produtos únicos presentes no estoque. 
E, por fim, o estoque, que é um vetor de structs alocado dinamicamente que
guarda todos os produtos adicionados. O nosso código, ao final da execução, salva
essas três informações e, na próxima execução, carrega elas. Decidimos fazer o uso
de arquivos binários pois os processos de carregar e salvar os arquivos são mais
simples. 
*/


//Definindo as diretives de pré-processamento:
#include <stdio.h>
#include <stdlib.h>

//Definindo a estrutura do produto
typedef struct produto{

    char nome[51]; //Nome do produto
    int id, qtd; //Código e quantidade inicial do produto
    float preco; //Preço do produto

} produto;

//FUNÇÕES UTILIZADAS:

/*
Essa função serve para alocar dinamicamente o espaço para o vetor
de produtos, será utilizada quando o programa ler o arquivo do
dia anterior e quando o programa for iniciado sem arquivo anterior.
*/
produto* aloca(int n){ //O parâmetro é o número de produtos que serão adicionados.
    produto *alocar = (produto*) malloc(n*sizeof(produto)); // Alocamos o espaço para o número de produtos vezes o tamanho da struct produto.
    if (alocar==NULL){ //Conferimos se foi possível alocar.
        printf("Erro ao alocar memória.");
        exit(1);
    }
    return alocar; //Retornamos o ponteiro para a primeira posição do vetor alocado.
}

/*
A função a seguir será executada na main() após declararmos as variáveis 
padrão do programa. O seu objetivo é: baseado na existência de um arquivo do
dia anterior, decidir se vai recuperar as informações sobre produtos, ID e
saldo, ou iniciar as variáveis de forma padrão. Os três parâmetros estão
sendo desreferenciados porque vamos mudar na main o valor dessas variáveis
(passagem por referência). A função é int porque ela vai retornar o número 
de produtos que o usuário quer adicionar inicialmente (faz sentido apenas se
o usuário não tiver o arquivo do dia anterior), isso será usado depois na 
função de inserir produto: se o espaço alocado dinamicamente para os produtos
for o suficiente, não é necessário realocar.
*/
int inicializar(float *saldo, produto **estoque, int *id){ 
    FILE *arq = fopen("estoque.bin", "rb"); //Tentamos abrir o arquivo binário em modo de leitura.
    int tamanhoEstoque = 0;
    if(arq != NULL){ //Se o arquivo existe, vai carregar as informações:
        fread(id, sizeof(int), 1, arq); //Primeiro lemos o ID (que representa a quantidade de produtos únicos no estoque).
        fread(saldo, sizeof(float), 1, arq); //Então, lemos o saldo final da última execução salvo no arquivo.
        *estoque = aloca(*id); //Baseado na quantidade de produtos, alocamos o estoque dinamicamente.
        fread(*estoque, sizeof(produto), *id, arq); //Por fim, lemos todos produtos e suas informações e copiamos eles no estoque.
        fclose(arq); //Fechamos o arquivo.
        return(tamanhoEstoque);

    }else{ //Se o arquivo NÃO existe, vai iniciar as informações como padrão:
        
        *id = 0; //Inicializa o ID como zero(que também é a quantidade de produtos).
        *saldo = 100.00; //Inicializa o saldo como 100,00.
        scanf("%d", &tamanhoEstoque); //Pergunta ao usuário quantos produtos únicos ele vai querer adicionar inicialmente.
        *estoque = aloca(tamanhoEstoque); //Aloca o estoque dinamicamente baseado no número de produtos únicos escolhidos pelo usuário.
        return(tamanhoEstoque);
        
    }
} 

/*Essa função lê as informações de um produto e o insere no estoque.
Se o espaço alocado dinamicamente estiver cheio ela vai realocar o espaço
do estoque para que o próximo produto adicionado se adeque sem invadir 
memória. Os parâmetros são o endereço do estoque e do ID e o estoque inicial.
Os dois primeiros estão sendo desreferenciados porque vão mudar na main().
*/
void insereProduto(produto **estoque, int *id, int estoqueinicial){
    if(estoqueinicial>*id){ //Se ainda houver espaço no estoque, ele só adiciona o produto.

    }else{ //Se não houver espaço no estoque a função realoca e aumenta o tamanho do vetor de structs para receber o novo produto.
        int novotamanho = *id + 1;

    //realoca aumentando o tamanho do estoque para receber o novo produto
    produto *temp = (produto*) realloc( *estoque, novotamanho * sizeof(produto));
    if(temp == NULL) {
        printf("Falha ao realocar memória.");
        exit(1);
    }  

    *estoque = temp;
    }

    //Aqui ocorre a atribuição das informações do produto.
    //O usuário coloca nome, quantidade e preço e o sistema insere o ID automaticamente. 

    scanf("%s", (*estoque)[*id].nome);
    scanf("%d", &(*estoque)[*id].qtd);
    scanf("%f", &(*estoque)[*id].preco);
    (*estoque)[*id].id = *id;
    //O ID é incrementado de forma a representar o número de produtos únicos no estoque.
    *id = *id + 1;
    
    return;

}

/*Essa função aumenta a quantidade em estoque de um produto especifico e retira dinheiro
do saldo do caixa de forma proporcional à quantidade de produtos adicionados. Os parâmetros
são: o vetor de structs e o saldo (este está desreferenciado pois seu valor vai mudar na main()).
*/
void aumentaEstoque(produto *estoque, float *saldo){
    
    int id, qtdAdc;
    scanf("%d", &id);
    scanf("%d", &qtdAdc);
    estoque[id].qtd += qtdAdc; //Adiciona a quantidade do produto de ID especificado.
    *saldo -= (float) estoque[id].preco * qtdAdc; //Retira do saldo o valor gasto.

    return;
    
}
/*Essa função realiza a venda de produtos no estoque para clientes. Após o comando o usuário
deverá colocar o ID dos produtos que quer vender e, ao final, deverá digitar -1 para comunicar
o fim do processo de venda. Será impresso na tela a lista de itens comprados pelo cliente, seus
valores e o total gasto. O dinheiro recebido será adicionado no saldo do mercado. Os parâmetros 
da função são o estoque, o saldo (que será alterado) e o número n que representa o ID do produto
de maior ID.
*/
void venda(produto *estoque, float *saldo, int n){

    int id;
    float total = 0;

    while(1){ //O loop vai rodar até a condição de parada, que é o -1.
        scanf("%d", &id); //Será lido o ID do produto a ser vendido
        if(id < 0) break; //Se esse número for negativo o loop é cancelado.
        if(estoque[id].qtd < 1) continue; //Se o usuário tentar vender mais que a quantidade em estoque essa venda é ignorada.
        if(id >= n) continue; //Se o usuário quiser vender um ID inválido ele só ignora e lê o próximo número.
        estoque[id].qtd -= 1; //É decrementado no estoque uma unidade do produto.
        *saldo = *saldo + estoque[id].preco; //Adiciona-se os ganhos da venda.
        total = total + estoque[id].preco; //Calcula o total da venda.
        printf("%s %.2f\n", estoque[id].nome, estoque[id].preco); //Imprime o produto vendido e seu preço.
    }
    printf("Total: %.2f\n", total); //Imprime o preço total da compra.
    printf("--------------------------------------------------\n");

}

/*
Essa função tem como objetivo modificar o preço de um produto presente no estoque.
O seu único parâmetro é o estoque. 
*/
void modificaPreco(produto *estoque){

    int id;
    float precoAlt;
    scanf("%d %f", &id, &precoAlt); //Lê o ID do produto a ter preço alterado e o novo preço
    estoque[id].preco = precoAlt; //Altera o preço
    return;

}
/*
Essa função imprime na tela o ID, nome e quantidade em estoque de todos os produtos em estoque.
Ela recebe como parâmetros o estoque e o ID.
*/
void consultaEstoque(produto *estoque, int *id){

    for(int i = 0; i < *id; i++){//Vai imprimir até os produtos e suas informações até alcançar o produto de último ID no estoque.
        printf("%d %s %d\n", 
            estoque[i].id,
            estoque[i].nome,
            estoque[i].qtd
        );
    }
    printf("--------------------------------------------------\n");

    return;

}
/*Essa função apenas imprime na tela o saldo do mercado. Tem como único parâmetro o saldo.*/
void consultaSaldo(float *saldo){
    printf("Saldo: %.2f\n", *saldo);
    printf("--------------------------------------------------\n");

}
/*
O objetivo dessa função é salvar em um arquivo binário, nessa ordem: o ID (que representa
o número de produtos em estoque), o saldo atual do mercado e todos os produtos em estoque 
e suas informações. No próximo uso do código esse arquivo será lido e interpretado pela função
int inicializar(). Seus parâmetros são o estoque, o saldo e o ID.
*/
void finalizarDia(produto *estoque, float *saldo, int *id){
    FILE *arq = fopen("estoque.bin", "wb");//Tenta criar e abre o arquivo em modo de escrita binária.
    if(arq == NULL){//Caso não seja possível criar, o programa é fechado.
        printf("Falha ao salvar o arquivo.");
        exit(1);
    }

    fwrite(id, sizeof(int), 1, arq); //Escreve no arquivo o ID(quantidade de produtos).
    fwrite(saldo, sizeof(float), 1, arq); //Escreve no arquivo o saldo.
    fwrite(estoque, sizeof(produto), *id, arq); //Escreve no arquivo os produtos no estoque e suas informações
    fclose(arq); //Fecha o arquivo.
    

}

//Função principal, na qual as demais funções são chamadas:
int main(){

    char comando[3] = "a"; //Criamos a string comando que vai auxiliar na chamada das funções.
    int id, tamanhoestoqueinicial; //Criamos as variáveis ID e tamanho inicial do estoque.
    float saldo; //Criamos a variável saldo
    produto *estoque; //Cria o vetor de produtos: estoque 
    tamanhoestoqueinicial = inicializar(&saldo, &estoque, &id); //Chama a função inicial

    
     while(1){//Roda o MENU para chamar funções, enquanto a função não for FE vai continuar rodando:
        scanf("%s", comando);
        if ((comando[0]=='I')&&(comando[1]=='P')){//Chama insereProduto()
            insereProduto(&estoque,&id,tamanhoestoqueinicial);
        }
        if ((comando[0]=='A')&&(comando[1]=='E')){//Chama aumentaEstoque()
            aumentaEstoque(estoque, &saldo);
        }
        if ((comando[0]=='M')&&(comando[1]=='P')){//Chama modificaPreco()
            modificaPreco(estoque);
        }
        if ((comando[0]=='V')&&(comando[1]=='E')){//Chama venda()
            venda(estoque, &saldo, id);
        }
        if ((comando[0]=='C')&&(comando[1]=='E')){//Chama consultaEstoque()
            consultaEstoque(estoque, &id);
        }
        if ((comando[0]=='C')&&(comando[1]=='S')){//Chama consultaSaldo()
            consultaSaldo(&saldo);
        }
        if ((comando[0]=='F')&&(comando[1]=='E')){//Chama finalizarDia()
            //logica de salvar o arquivo
            finalizarDia(estoque, &saldo, &id); 
            break;
        }
        
    } 

    //Libera a memória alocada dinamicamente para o vetor.
    free(estoque);


    return 0;
}
