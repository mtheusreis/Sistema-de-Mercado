/*
PROJETO MERCADINHO
O objetivo principal do projeto é criar um sistema que permita
o gerenciamento de um mercado. Por meio de diversas funções será possível 
realizar ações como vendas e 
*/


//Definindo as diretives de pre-processamento
#include <stdio.h>
#include <stdlib.h>

//definindo a estrutura do produto
typedef struct produto{

    char nome[51]; 
    int id, qtd; // quantidade e codigo 
    float preco; 

} produto;

//usada às sextas-feiras| tem como parâmetro quantos produtos vão caber no estoque
produto* aloca(int n){
    produto *alocar = (produto*) malloc(n*sizeof(produto)); 
    if (alocar==NULL){
        printf("Erro ao alocar memória.");
        exit(1);
    }
    return alocar;
}

void inicializar(float *saldo, produto **estoque, int *id){
    FILE *arq = fopen("estoque.bin", "rb");
    int tamanhoEstoque;
    if(arq != NULL){
        fread(id, sizeof(int), 1, arq);
        fread(saldo, sizeof(float), 1, arq);
        *estoque = aloca(*id);
        fread(*estoque, sizeof(produto), *id, arq);
        fclose(arq);
        
        return;
    } else{
        
        *id = 0;
        *saldo = 100.00;
        scanf("%d", &tamanhoEstoque);
        *estoque = aloca(tamanhoEstoque);
        return;
        
    }
} 

//Funções ultilizadas pelo sistema

//função lẽ as informações do produto e o insere no estoque |
//parametros: vetor do estoque alocado dinamicamente e ponteiro para ID, que aumenta de 1 em 1 em cada chamada da função 
void insereProduto(produto **estoque, int *id){
    
    int novotamanho = *id + 1;

    //realoca aumentando o tamanho do estoque para receber o novo produto
    produto *temp = (produto*) realloc( *estoque, novotamanho * sizeof(produto));
    if(temp == NULL) {
        printf("Falha ao realocar memória.");
        exit(1);
    }  

    *estoque = temp;

    scanf("%s", (*estoque)[*id].nome);
    scanf("%d", &(*estoque)[*id].qtd);
    scanf("%f", &(*estoque)[*id].preco);
    (*estoque)[*id].id = *id;
    *id = *id + 1;
    
    return;

}

//função que aumenta a quantidade em estoque de um produto e retira do saldo proporcionalmente
//parãmetros: vetor de structs do estoque e ponteiro para saldo 
void aumentaEstoque(produto *estoque, float *saldo){
    
    int id, qtdAdc;
    scanf("%d", &id);
    scanf("%d", &qtdAdc);
    estoque[id].qtd += qtdAdc;
    *saldo -= (float) estoque[id].preco * qtdAdc;

    return;
    
}

void venda(produto *estoque, float *saldo, int n){

    int id;
    float total = 0;

    while(1){
        scanf("%d", &id);
        if(id < 0) break;
        if(estoque[id].qtd < 1) continue;
        if(id >= n) continue;
        estoque[id].qtd -= 1;
        *saldo = *saldo + estoque[id].preco;
        total = total + estoque[id].preco;
        printf("%s %.2f\n", estoque[id].nome, estoque[id].preco);
    }
    printf("Total: %.2f\n", total);
    printf("--------------------------------------------------\n");

}

void modificaPreco(produto *estoque){

    int id;
    float precoAlt;
    scanf("%d %f", &id, &precoAlt);

    estoque[id].preco = precoAlt;

    return;

}

void consultaEstoque(produto *estoque, int *id){

    for(int i = 0; i < *id; i++){
        printf("%d %s %d\n", 
            estoque[i].id,
            estoque[i].nome,
            estoque[i].qtd
        );
    }
    printf("--------------------------------------------------\n");

    return;

}

void consultaSaldo(float *saldo){
    printf("Saldo: %.2f\n", *saldo);
    printf("--------------------------------------------------\n");

}

void fechaArquivo(FILE *arquivo){
    fclose(arquivo);
}
 
void finalizarDia(produto *estoque, float *saldo, int *id){
    FILE *arq = fopen("estoque.bin", "wb");
    if(arq == NULL){
        printf("Falha ao salvar o arquivo.");
        exit(1);
    }

    fwrite(id, sizeof(int), 1, arq);
    fwrite(saldo, sizeof(float), 1, arq);
    fwrite(estoque, sizeof(produto), *id, arq);

    fclose(arq);
    

}


int main(){

    char comando[3] = "a";
    int id;
    float saldo;
    produto *estoque;
    inicializar(&saldo, &estoque, &id);

    //enqunto comando nao for FE, continua*/
    
     while(1){
        scanf("%s", comando);
        if ((comando[0]=='I')&&(comando[1]=='P')){
            insereProduto(&estoque,&id);
        }
        if ((comando[0]=='A')&&(comando[1]=='E')){
            aumentaEstoque(estoque, &saldo);
        }
        if ((comando[0]=='M')&&(comando[1]=='P')){
            modificaPreco(estoque);
        }
        if ((comando[0]=='V')&&(comando[1]=='E')){
            venda(estoque, &saldo, id);
        }
        if ((comando[0]=='C')&&(comando[1]=='E')){
            consultaEstoque(estoque, &id);
        }
        if ((comando[0]=='C')&&(comando[1]=='S')){
            consultaSaldo(&saldo);
        }
        if ((comando[0]=='F')&&(comando[1]=='E')){
            //logica de salvar o arquivo
            finalizarDia(estoque, &saldo, &id); 
            break;
        }
        
    } 

    //free das alocações
    free(estoque);


    return 0;
}
