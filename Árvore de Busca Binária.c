#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int valor;
    struct no *esquerda;
    struct no *direita;
} No;


No* adicionarNo(int valor){
    No* novo = (No*) malloc(sizeof(No));
    if(novo == NULL){
        printf("Erro ao alocar memória!\n");
        exit(EXIT_FAILURE);
    }

    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    
    return novo;
}


No* Inserir(No* raiz, int valor){
    if(raiz == NULL)
        return adicionarNo(valor);

    if(valor < raiz->valor){
        raiz->esquerda = Inserir(raiz->esquerda, valor);
    }
    else if(valor > raiz->valor){
        raiz->direita = Inserir(raiz->direita, valor);
    }
    else {
        printf("Valor repetido! Não inserido.\n");
    }

    return raiz; 
}


int BuscarNo(No* raiz, int valor){
    if(raiz == NULL)
        return 0;

    if(valor == raiz->valor)
        return 1;

    else if(valor < raiz->valor)
        return BuscarNo(raiz->esquerda, valor);

    else
        return BuscarNo(raiz->direita, valor);
}


No* Minimo(No* raiz){
    while(raiz->esquerda != NULL)
        raiz = raiz->esquerda;

    return raiz;
}


No* Remover(No* raiz, int valor){
    if(raiz == NULL){
        printf("Valor não encontrado!\n");
        return NULL;
    }

    if(valor < raiz->valor){
        raiz->esquerda = Remover(raiz->esquerda, valor);
    }
    else if(valor > raiz->valor){
        raiz->direita = Remover(raiz->direita, valor);
    }
    else {
        //  Nó folha
        if(raiz->esquerda == NULL && raiz->direita == NULL){
            free(raiz);
            return NULL;
        }

        // Nó só com filho direito
        if(raiz->esquerda == NULL){
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        }

        //  Nó só com filho esquerdo
        if(raiz->direita == NULL){
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        // Nó com 2 filhos 
        No* temp = Minimo(raiz->direita);
        raiz->valor = temp->valor;
        raiz->direita = Remover(raiz->direita, temp->valor);
    }

    return raiz;
}


void preOrdem(No* raiz){
    if(raiz != NULL){
        printf("%d ", raiz->valor);
        preOrdem(raiz->esquerda);
        preOrdem(raiz->direita);
    }
}

void emOrdem(No* raiz){
    if(raiz != NULL){
        emOrdem(raiz->esquerda);
        printf("%d ", raiz->valor);
        emOrdem(raiz->direita);
    }
}

void posOrdem(No* raiz){
    if(raiz != NULL){
        posOrdem(raiz->esquerda);
        posOrdem(raiz->direita);
        printf("%d ", raiz->valor);
    }
}


void liberarArvore(No* raiz){
    if(raiz != NULL){
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}


int main(){
    No* raiz = NULL;
    int opcao, valor;

    do {
        printf("\n--- lista de opcao ---\n");
        printf("1 – Inserir valor\n");
        printf("2 – Buscar valor\n");
        printf("3 – Remover valor\n");
        printf("4 – Percorrer árvore\n");
        printf("0 – Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao){

            case 1:
                printf("Digite o valor a inserir: ");
                scanf("%d", &valor);
                raiz = Inserir(raiz, valor);
                break;

            case 2:
                printf("Digite o valor a buscar: ");
                scanf("%d", &valor);
                if (BuscarNo(raiz, valor))
                    printf("Valor %d encontrado!\n", valor);
                else
                    printf("Valor %d NÃO encontrado!\n", valor);
                break;

            case 3:
                printf("Digite o valor a remover: ");
                scanf("%d", &valor);
                raiz = Remover(raiz, valor);
                break;

            case 4: {
                int sub;
                printf("\n--- PERCURSOS ---\n");
                printf("1 – Pré-ordem\n");
                printf("2 – Em ordem\n");
                printf("3 – Pós-ordem\n");
                printf("Escolha: ");
                scanf("%d", &sub);

                switch(sub){
                    case 1:
                        printf("Pré-ordem: ");
                        preOrdem(raiz);
                        printf("\n");
                        break;

                    case 2:
                        printf("Em ordem: ");
                        emOrdem(raiz);
                        printf("\n");
                        break;

                    case 3:
                        printf("Pós-ordem: ");
                        posOrdem(raiz);
                        printf("\n");
                        break;

                    default:
                        printf("Opção inválida!\n");
                }
                break;
            }

            case 0:
                liberarArvore(raiz);
                printf("Programa encerrado.\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while(opcao != 0);

    return 0;
}
