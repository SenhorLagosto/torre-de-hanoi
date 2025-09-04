#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <locale.h>
#include <unistd.h>

typedef struct disco{
    int peso;
    struct disco* prox;
}Disco;

typedef struct pilha{  
    Disco* topo;
}Pilha;

/*     GLOBAIS     */
//Total de jogadas feitas.
int jogadas = 0;
//n é o número de discos que o usuário escolher
const int n;
//Caracter de controle. Feito pra pular pro final ou não.
char final;
Pilha* pilha1;
Pilha* pilha2;
Pilha* pilha3;


/*Encadeia n discos dentro de uma pilha, retorna o disco do topo*/
Disco* inicializa(Pilha* pilha, int n){
    Disco* aux = (Disco*) malloc(sizeof(Disco*));
    for(int i = n; i>0;i--){
        Disco* disco = (Disco*) malloc(sizeof(Disco*));
        disco->peso = i;
        if(i == n)disco->prox = NULL;
        else disco->prox = aux;
        aux = disco;
    }
    return aux;
}

//Função simples que move um disco de um topo para o outro.
void aloca(Pilha* mae, Pilha* filha){
    Disco* aux = filha->topo;
    filha->topo = mae->topo;
    mae->topo = mae->topo->prox;
    filha->topo->prox = aux;
}

/*Essa função conta quantos discos há na pilha. Ela vai até a flag, se a flag for diferente de 0(flag que indica pra esvaziar a pilha).
Se a flag for 0 a função conta até o final da pilha. Se a flag for outro valor, a função conta até chegar antes do valor(peso do disco)*/
int reconhecimento(Pilha* mae, int* flag){
Disco* base = mae->topo;
int quant = 1;
if(mae->topo == NULL)return n;
if(*flag == 0){
while(base->prox != NULL){
    quant = quant + 1;
    base = base->prox;
}
}else{
    while(base->prox != NULL && base->prox->peso < *flag){
    quant = quant + 1;
    base = base->prox;
}
}
return quant;
}

/*Função auxiliar da imprime. Ela imprime a linha :)*/
Disco* imprime_linha(Disco* d, int nNulo){
    if(d == NULL || nNulo){
        printf("-");
        printf("   ");
        return d;
    }
    else {
        printf("%d", d->peso);
        printf("   ");
        return d = d->prox;
    }
}

/*Visualização das jogadas e do estado das pilhas*/
void imprime(){
    if(jogadas)printf("\n\nJogada %d\n", jogadas);
    Disco* x1 = pilha1->topo;
    Disco* x2 = pilha2->topo;
    Disco* x3 = pilha3->topo;
    int j = 0;
    int qn1 = n - reconhecimento(pilha1, &j);
    int qn2 = n - reconhecimento(pilha2, &j);
    int qn3 = n - reconhecimento(pilha3, &j);
    for(int i=0; i<n;i++){
        x1 = imprime_linha(x1, qn1);
        if(qn1)qn1--;
        x2 = imprime_linha(x2, qn2);
        if(qn2)qn2--;
        x3 = imprime_linha(x3, qn3);
        if(qn3)qn3--;
        if(i==0)printf(" <- topo");
        printf("\n");
        if(i==n-1)printf("_   _   _");
    }
}

/*Algorítimo de decisão.*/
int jogada(Pilha* mae, Pilha* obj, Pilha* aux, int* flag){
if(mae->topo == NULL || mae->topo->peso == *flag){return 0;}
int quant = reconhecimento(mae, flag);

//o disco do topo vai pra pilha aux
if(quant % 2==0){
    if(aux->topo == NULL || mae->topo->peso < aux->topo->peso){
        jogadas++;
        aloca(mae, aux);
        imprime();
        if(final != 'f')final = getch();
        if(final == 'f')sleep(1);
        if(mae->topo != NULL && *flag != 0 && mae->topo->peso > *flag)return 0;
        jogada(mae, obj, aux, flag);
    }
    else{// aux está obstruída, preciso tirar os discos com pesos menores até que seja possível alocar. 
        int flag2 = mae->topo->peso;    
        while(jogada(aux, obj, mae, &flag2)){}
        jogada(mae, obj, aux, flag);
        
    }
}
else{// o disco do topo vai pra pilha obj
    if(obj->topo == NULL || mae->topo->peso < obj->topo->peso){
        jogadas++;
        aloca(mae, obj);
        imprime();
        if(final != 'f')final = getch();
        if(final == 'f')sleep(1);
        if(mae->topo != NULL && *flag != 0 && mae->topo->peso > *flag)return 0;
        jogada(mae, obj, aux, flag);
    }
    else{// obj está obstruída, preciso tirar os discos com pesos menores até que seja possível alocar.
        /*É necessário uma segunda flag, diferente da primeira, pois ela precisa permanecer para as próximas jogadas saibam até onde devem ir
        e o reconhecimento precisa saber até onde contar.*/
    int flag2 = mae->topo->peso;
        while(jogada(obj, aux, mae, &flag2)){}
        jogada(mae, obj, aux, flag);
    }
}
}
 


char inicio(){
printf("     _______  _______  ______    ______    _______    ______   _______    __   __  _______  __    _  _______  ___ \n"); 
printf("    |       ||       ||    _ |  |    _ |  |       |  |      | |       |  |  | |  ||   _   ||  |  | ||       ||   |\n"); 
printf("    |_     _||   _   ||   | ||  |   | ||  |    ___|  |  _    ||    ___|  |  |_|  ||  |_|  ||   |_| ||   _   ||   |\n"); 
printf("      |   |  |  | |  ||   |_||_ |   |_||_ |   |___   | | |   ||   |___   |       ||       ||       ||  | |  ||   |\n"); 
printf("      |   |  |  |_|  ||    __  ||    __  ||    ___|  | |_|   ||    ___|  |       ||       ||  _    ||  |_|  ||   |\n"); 
printf("      |   |  |       ||   |  | ||   |  | ||   |___   |       ||   |___   |   _   ||   _   || | |   ||       ||   |\n"); 
printf("      |___|  |_______||___|  |_||___|  |_||_______|  |______| |_______|  |__| |__||__| |__||_|  |__||_______||___|\n\n");
printf("\nO famoso jogo da Torre de Hanói é um quebra-cabeça que consiste em uma base contendo três pinos, em um dos quais\n");
printf("são dispostos alguns discos uns sobre os outros, em ordem crescente de diâmetro, de cima para baixo.\n");
printf("\nObjetivo: Mover todos os disco para a terceira torre(última da esquerda pra direita).\n");
printf("\nRegras: Um disco de diâmetro maior não pode estar sobre um de menor. Por exemplo, o disco de diâmetro 3 não pode estar em cima do de 2 ou 1.");
printf(" Só é possível mover um disco por vez.\n\n");
printf("Total de discos a serem inseridos: ");
scanf(" %d", &n);
int minimo = pow(2, n) - 1;
char resposta;
if(n > 5){
    printf("\nO mínimo de jogadas para concluir é %d, certeza da quantidade de discos?(s/n)  ", minimo);
    resposta = getch();
    if(resposta == 'n'){
        system("cls");
        inicio();
        return ' ';
    }
}
else printf("\nO mínimo de jogadas é %d\n\n", minimo);
}

int main(void) {

inicio();
pilha1 = (Pilha*) malloc(sizeof(Pilha*));
pilha2 = (Pilha*) malloc(sizeof(Pilha*));
pilha3 = (Pilha*) malloc(sizeof(Pilha*));
pilha1->topo = inicializa(pilha1, n);
pilha2->topo = NULL;
pilha3->topo = NULL;
/*A flag serve para indicar até onde eu preciso esvaziar a pilha. Sendo 0 o valor para esvaziar a pilha por completo*/
int flag = 0;
printf("\n\nPressione qualquer tecla para ir pra próxima jogada ou 'f' para ir automático\n\n");
imprime();
int contador = 1;
jogada(pilha1, pilha3, pilha2, &flag);
while(pilha3->topo->peso != 1){
    if(contador % 2 == 0)jogada(pilha1, pilha3, pilha2, &flag);
    else jogada(pilha2, pilha3, pilha1, &flag);
    contador++;
}
return 1;
}
