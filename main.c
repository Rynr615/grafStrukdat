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

*/

typedef struct edge Edge;

typedef struct node {
    struct node *nextNode;
    Edge *nextEdge;
    char label[20];
} Node;

struct edge {
    Edge *nextEdge;
    Node *nextNode;
    int cost;
};

typedef struct graf {
    Node *first;
} Graf;

Node *createNode(Graf *g, char label[]) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->label, label);
    newNode->nextEdge = NULL;
    newNode->nextNode = NULL;

    if(g->first == NULL) {
        g->first = newNode;
    } else {
        Node *tempNode = g->first;
        while(tempNode->nextNode != NULL) {
            tempNode = tempNode->nextNode;
        }
        tempNode->nextNode = newNode;
    }

    printf("Komputer '%s' berhasil ditambahkan.\n", label);
    return newNode;
}

void addEdge(Node *start, Node *last, int cost) {
    Edge *newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->nextNode = last;
    newEdge->cost = cost;
    newEdge->nextEdge = NULL;

    if(start->nextEdge == NULL) {
        start->nextEdge = newEdge;
    } else {
        Edge *tempEdge = start->nextEdge;
        while(tempEdge->nextEdge != NULL) {
            tempEdge = tempEdge->nextEdge;
        }
        tempEdge->nextEdge = newEdge;
    }
}

void printGraf(Graf *g) {
    Node *tempNode = g->first;

    if(tempNode != NULL) {
        while(tempNode != NULL) {
            printf("Komputer %s terhubung ke:\n", tempNode->label);
            Edge *tempEdge = tempNode->nextEdge;
            if(tempEdge == NULL) {
                printf("   (tidak ada koneksi)\n");
            } else {
                while(tempEdge != NULL) {
                    printf("   - %s dengan jarak LAN %d meter\n", 
                        tempEdge->nextNode->label, tempEdge->cost);
                    tempEdge = tempEdge->nextEdge;
                }
            }
            printf("\n");
            tempNode = tempNode->nextNode;
        }
    } else {
        printf("Graf masih kosong!!!\n");
    }
}


Node *findNode(Graf *g, char label[]) {
    Node *temp = g->first;

    while(temp != NULL) {
        if(strcmp(temp->label, label) == 0) {
            return temp;
        }
        temp = temp->nextNode;
    }
    return NULL;
}

