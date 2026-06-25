#include <stdio.h>
#include <stdlib.h>

//definindo a estrutura do produto
typedef struct produto{

    char nome[51]; 
    int id, qtd; // quantidade e codigo 
    float preco; 

} produto;

//Funções ultilizadas pelo sistema

//função lẽ as informações do produto e o insere no estoque |
//parametros: vetor do estoque alocado dinamicamente e ponteiro para ID, que aumenta de 1 em 1 em cada chamada da função 
void insereProduto(produto *estoque, int *id){
    

    scanf("%s", estoque[*id].nome);
    scanf("%d", &estoque[*id].qtd);
    scanf("%f", &estoque[*id].preco);
    estoque[*id].id = *id;
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

void venda(produto *estoque, float *saldo){

    int id;
    float total = 0;

    while(1){
        scanf("%d", &id);
        if(id < 0) break;
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
    printf("%.2f\n", *saldo);
    printf("--------------------------------------------------\n");

}
void finalizarDia(produto *estoque, float *saldo){
    //aqui vai fazer a logica do arquivo
}

//usada quando não ha arquivo do dia anterior | tem como parâmetro quantos produtos vão caber no estoque
produto* aloca(int n){
    produto *alocar = (produto*) malloc(n*sizeof(produto)); 
    return alocar;
}

int main(){

    char comando[3] = "a";
    int tamanhoEstoque, id = 0;
    produto *estoque;
    float saldo = 100;
    
    scanf("%d", &tamanhoEstoque);

    estoque = aloca(tamanhoEstoque);

    /*printf("Insere tres produtos (nome, qtd, preco)\n");
    insereProduto(estoque, &id);
    insereProduto(estoque, &id);
    insereProduto(estoque, &id);
    printf("Modifica preco: codigo preço\n");
    modificaPreco(estoque);
    printf("Aumenta estoque: codigo qtd\n");
    aumentaEstoque(estoque, &saldo);
    printf("consulta estoque\n");
    consultaEstoque(estoque, &id);
    printf("consulta saldo\n");
    consultaSaldo(&saldo);

    //enqunto comando nao for FE, continua*/
    
     while(1){
        scanf("%s", comando);
        if ((comando[0]=='I')&&(comando[1]=='P')){
            insereProduto(estoque,&id);
        }
        if ((comando[0]=='A')&&(comando[1]=='E')){
            aumentaEstoque(estoque, &saldo);
        }
        if ((comando[0]=='M')&&(comando[1]=='P')){
            modificaPreco(estoque);
        }
        if ((comando[0]=='V')&&(comando[1]=='E')){
            venda(estoque, &saldo);
        }
        if ((comando[0]=='C')&&(comando[1]=='E')){
            consultaEstoque(estoque, &id);
        }
        if ((comando[0]=='C')&&(comando[1]=='S')){
            consultaSaldo(&saldo);
        }
        if ((comando[0]=='F')&&(comando[1]=='E')){
            //logica de salvar o arquivo
            break;
        }
        
    } 

    //free das alocações


    return 0;
}
