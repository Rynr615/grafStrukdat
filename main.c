#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Kode dibuat oleh:
1.  - Nama  :   Ryan Yanuar Pradana
    - NIM   :   2405188
2.  - Nama  :   Siti Maulida Rahmah
    - NIM   :   2409092

Pada Sabtu, 31 Mei 2025

Repository:
https://github.com/Rynr615/grafStrukdat
*/

/*
Posisi Komputer di lab pada umumnya

            Router

Switch1
PC1	    PC6	    PC11	PC16

PC2     PC7	    PC12	PC17
    Switch2
PC3	    PC8	    PC13	PC18

PC4	    PC9	    PC14	PC19
            Switch3
PC5	    PC10	PC15	PC20

Kami menggunakan ini sebagai acuan awal untuk membuat 
"Hubungan Antar Komputer pada Lab dengan Implementasi Graf Menggunakan Bahasa C"
*/
typedef struct edge Edge;

typedef struct node {
    struct node *nextNode;
    Edge *nextEdge;
    char label[20];
    int visited;
} Node;

struct edge {
    Edge *nextEdge;
    Node *nextNode;
    float cost;
};

typedef struct graf {
    Node *first;
} Graf;

Node *createNode(Graf *g, char label[]) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->label, label);
    newNode->visited = 0;
    newNode->nextEdge = NULL;
    newNode->nextNode = NULL;

    if (g->first == NULL) {
        g->first = newNode;
    } else {
        Node *temp = g->first;
        while (temp->nextNode != NULL) {
            temp = temp->nextNode;
        }
        temp->nextNode = newNode;
    }
    return newNode;
}

void addEdge(Node *start, Node *end, float cost) {
    Edge *newEdge = (Edge *)malloc(sizeof(Edge));
    newEdge->nextNode = end;
    newEdge->cost = cost;
    newEdge->nextEdge = NULL;

    if (start->nextEdge == NULL) {
        start->nextEdge = newEdge;
    } else {
        Edge *temp = start->nextEdge;
        while (temp->nextEdge != NULL) {
            temp = temp->nextEdge;
        }
        temp->nextEdge = newEdge;
    }
}

void printGraf(Graf *g) {
    Node *tempNode = g->first;

    while (tempNode != NULL) {
        printf("%s terhubung ke:\n", tempNode->label);
        Edge *tempEdge = tempNode->nextEdge;
        if (tempEdge == NULL) {
            printf("   (tidak ada koneksi)\n");
        } else {
            while (tempEdge != NULL) {
                printf("   - %s (jarak: %.2f meter)\n", tempEdge->nextNode->label, tempEdge->cost);
                tempEdge = tempEdge->nextEdge;
            }
        }
        printf("\n");
        tempNode = tempNode->nextNode;
    }
}

void resetVisited(Graf *g) {
    Node *temp = g->first;
    while(temp != NULL) {
        temp->visited = 0;
        temp = temp->nextNode;
    }
}

void DFS(Node *tempNode) {
    if (tempNode == NULL) return;

    tempNode->visited = 1;
    printf("%s -> ", tempNode->label);

    Edge *tempEdge = tempNode->nextEdge;
    while (tempEdge != NULL) {
        if (!tempEdge->nextNode->visited) {
            DFS(tempEdge->nextNode);
        }
        tempEdge = tempEdge->nextEdge;
    }
}


void BFS(Node *start) {
    Node *queue[100];
    int head = 0, tail = 0;

    start->visited = 1;
    queue[tail++] = start;

    while (head < tail) {
        Node *current = queue[head++];
        printf("%s -> ", current->label);
        Edge *tempEdge = current->nextEdge;
        while (tempEdge != NULL) {
            if (!tempEdge->nextNode->visited) {
                tempEdge->nextNode->visited = 1;
                queue[tail++] = tempEdge->nextNode;
            }
            tempEdge = tempEdge->nextEdge;
        }
    }
}

int main() {
    Graf *g = (Graf *)malloc(sizeof(Graf));
    g->first = NULL;

    Node *router = createNode(g, "Router");
    Node *switch1 = createNode(g, "Switch1");
    Node *switch2 = createNode(g, "Switch2");
    Node *switch3 = createNode(g, "Switch3");

    addEdge(router, switch1, 3.0);
    addEdge(router, switch2, 4.5);
    addEdge(router, switch3, 6.5);

    addEdge(switch1, router, 3.0);
    addEdge(switch2, router, 4.5);
    addEdge(switch3, router, 6.5);

    Node *PC[20];
    char name[10];
    for (int i = 0; i < 20; i++) {
        sprintf(name, "PC%d", i + 1);
        PC[i] = createNode(g, name);
    }

    for (int i = 0; i < 20; i++) {
        if (i < 7) {
            float cost = 1.0 + (i % 6) * 0.5;
            addEdge(PC[i], switch1, cost);
            addEdge(switch1, PC[i], cost);
        } else if (i < 14) {
            float cost = 1.0 + ((i - 7) % 6) * 0.5;
            addEdge(PC[i], switch2, cost);
            addEdge(switch2, PC[i], cost);
        } else {
            float cost = 1.0 + ((i - 14) % 6) * 0.5;
            addEdge(PC[i], switch3, cost);
            addEdge(switch3, PC[i], cost);
        }
    }

    for (int i = 0; i < 20; i++) {
        for (int j = i + 1; j < 20; j++) {
            int rowI = i / 5;
            int rowJ = j / 5;
            int colI = i % 5;
            int colJ = j % 5;
            float cost;
            if (rowI == rowJ) {
                cost = 1.0 + abs(colI - colJ) * 0.5;
            } else if (colI == colJ) {
                cost = 2.0 + abs(rowI - rowJ) * 1.0;
            } else {
                cost = 3.0 + (abs(rowI - rowJ) + abs(colI - colJ)) * 1.5;
            }
            addEdge(PC[i], PC[j], cost);
            addEdge(PC[j], PC[i], cost);
        }
    }

    printf("\n===============================================\n");
    printf("     Topologi Hybrid-Star Lab Komputer \n");
    printf("===============================================\n\n");
    printGraf(g);
    
    printf("\n===============================================\n");
    printf("     Penelusuran dengan DFS                     \n");
    printf("===============================================\n\n");
    resetVisited(g);
    printf("Traversal: ");
    DFS(g->first);
    printf("END\n\n");

    printf("\n===============================================\n");
    printf("     Penelusuran dengan BFS dari PC1              \n");
    printf("===============================================\n\n");
    resetVisited(g);
    printf("Traversal: ");
    BFS(PC[0]);
    printf("END\n");

    return 0;
}
