#include <stdio.h>
#include <stdlib.h>

// Estrutura básica do nó da lista duplamente encadeada
typedef struct Node {
    int data; // Valor armazenado no nó
    struct Node* next; // Ponteiro para o próximo nó
    struct Node* prev; // Ponteiro para o nó anterior
} Node;

// Função para Inserir no Início
void inserirInicio(Node** head, int valor) {
    Node* novo = (Node*)malloc(sizeof(Node));
    if (novo == NULL) {
        printf("Erro de alocação de memória.\n");
        return;
    }
    novo->data = valor;
    novo->next = *head;
    novo->prev = NULL;

    if (*head != NULL)
        (*head)->prev = novo;
    *head = novo;
}

// Função para Inserir no Fim
void inserirFim(Node** head, int valor) {
    Node* novo = (Node*)malloc(sizeof(Node));
    if (novo == NULL) {
        printf("Erro de alocação de memória.\n");
        return;
    }
    novo->data = valor;
    novo->next = NULL;

    if (*head == NULL) {
        novo->prev = NULL;
        *head = novo;
        return;
    }
    
    Node* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
        
    temp->next = novo;
    novo->prev = temp;
}

// Função para Remover um Valor (Revisada)
void removerValor(Node** head, int valor) {
    Node* temp = *head;

    // 1. Buscar o nó a ser removido
    while (temp != NULL && temp->data != valor)
        temp = temp->next;
        
    // 2. Se não encontrou, sai.
    if (temp == NULL) {
        printf("Valor %d não encontrado para remoção.\n", valor);
        return;
    }

    // 3. Ajustar o ponteiro PREV (Se o nó removido NÃO for o primeiro)
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        // Se for o primeiro nó (HEAD), o HEAD deve ser movido para o próximo nó.
        *head = temp->next;
    }
    
    // 4. Ajustar o ponteiro NEXT (Se o nó removido NÃO for o último)
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    printf("Valor %d removido com sucesso.\n", valor);
    free(temp);
}

// Função para Buscar
Node* buscar(Node* head, int valor) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data == valor)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

// Função para Imprimir (Normal)
void imprimir(Node* head) {
    Node* temp = head;
    printf("Lista (sentido normal): ");
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Função para Imprimir (Reverso)
void imprimirReverso(Node* head) {
    Node* temp = head;

    // Vai até o final
    while (temp != NULL && temp->next != NULL)
        temp = temp->next;
        
    printf("Lista (sentido reverso): ");
    
    // Imprime voltando
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->prev;
    }
    printf("NULL\n");
}

// Função principal de teste
int main() {
    Node* minhaLista = NULL;
    
    printf("--- Teste de Inserção ---\n");
    inserirInicio(&minhaLista, 10);
    inserirInicio(&minhaLista, 20);
    inserirFim(&minhaLista, 5); // Lista: 20 <-> 10 <-> 5
    
    imprimir(minhaLista);
    imprimirReverso(minhaLista);
    
    printf("\n--- Teste de Remoção ---\n");
    
    // 1. Remover um elemento do meio (10)
    removerValor(&minhaLista, 10);
    imprimir(minhaLista); // Lista: 20 <-> 5
    
    // 2. Remover o HEAD (20)
    removerValor(&minhaLista, 20);
    imprimir(minhaLista); // Lista: 5 <-> NULL
    
    // 3. Remover o último elemento (5)
    removerValor(&minhaLista, 5);
    imprimir(minhaLista); // Lista: NULL
    
    // 4. Tentar remover de lista vazia
    removerValor(&minhaLista, 99);
    
    printf("\n--- Teste de Busca ---\n");
    inserirInicio(&minhaLista, 42);
    if (buscar(minhaLista, 42) != NULL) {
        printf("Valor 42 encontrado.\n");
    }
    
    return 0;
}
