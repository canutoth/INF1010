#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h> 

#define TAM 10

typedef struct _viz Viz;
struct _viz {
    int noj;
    float peso;
    Viz* prox;
};

struct _grafo {
    int nv;
    int na;
    Viz** viz;
};

typedef struct {
    int* pai;
    int* rank;
    int n;
} DSU;

typedef struct {
    int u, v;
    float peso;
} Aresta;

Viz* novoViz(int noj, float peso) {
    Viz* v = (Viz*)malloc(sizeof(Viz));
    v->noj = noj;
    v->peso = peso;
    v->prox = NULL;
    return v;
}

struct _grafo* criaGrafo(int nv) {
    struct _grafo* g = (struct _grafo*)malloc(sizeof(struct _grafo));
    g->nv = nv;
    g->na = 0;
    g->viz = (Viz*)malloc(nv * sizeof(Viz));

    for (int i = 0; i < nv; i++) {
        g->viz[i] = NULL;
    }

    return g;
}

void insereAresta(struct _grafo* g, int origem, int destino, float peso) {
    Viz* novaArestaOrigem = novoViz(destino, peso);
    novaArestaOrigem->prox = g->viz[origem];
    g->viz[origem] = novaArestaOrigem;

    Viz* novaArestaDestino = novoViz(origem, peso);
    novaArestaDestino->prox = g->viz[destino];
    g->viz[destino] = novaArestaDestino;

    g->na++;
}

void imprimeGrafoComEnderecos(struct _grafo* g) {
    for (int i = 0; i < TAM; i++) {
        if (i == 2) continue;

        printf("Vertice %d (Endereco de memoria do vertice: %p) ->", i, (void*)&(g->viz[i]));
        Viz* v = g->viz[i];
        while (v != NULL) {
            printf(" (Destino: %d, Endereco Destino: %p)", v->noj, (void*)&(g->viz[v->noj]));
            v = v->prox;
        }
        printf("\n");
    }
}

void criaMatrizAdjacencias(struct _grafo* g) {
    int matriz[TAM][TAM];

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            matriz[i][j] = 0;
        }
    }

    for (int i = 0; i < TAM; i++) {
        if (i == 2) continue;
        Viz* v = g->viz[i];
        while (v != NULL) {
            if (v->noj != 2) {
                matriz[i][v->noj] = 1;
            }
            v = v->prox;
        }
    }

    printf("\nMatriz de Adjacencias:\n");
    for (int i = 0; i < TAM; i++) {
        if (i == 2) continue;
        for (int j = 0; j < TAM; j++) {
            if (j == 2) continue;
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void criaListaAdjacencias(struct _grafo* g) {
    printf("\nLista de Adjacencias:\n");
    for (int i = 0; i < TAM; i++) {
        if (i == 2) continue;

        printf("Vertice %d: ", i);
        int count = 0;
        Viz* v = g->viz[i];
        while (v != NULL) {
            count++;
            v = v->prox;
        }

        int* vizinhos = (int*)malloc(count * sizeof(int));
        v = g->viz[i];
        int j = 0;
        while (v != NULL) {
            vizinhos[j++] = v->noj;
            v = v->prox;
        }

        for (int k = 0; k < count - 1; k++) {
            for (int l = k + 1; l < count; l++) {
                if (vizinhos[k] > vizinhos[l]) {
                    int temp = vizinhos[k];
                    vizinhos[k] = vizinhos[l];
                    vizinhos[l] = temp;
                }
            }
        }

        for (int j = 0; j < count; j++) {
            printf("%d -> ", vizinhos[j]);
        }
        printf("NULL\n");

        free(vizinhos);
    }
}

void liberaGrafo(struct _grafo* g) {
    for (int i = 0; i < TAM; i++) {
        Viz* v = g->viz[i];
        while (v != NULL) {
            Viz* temp = v;
            v = v->prox;
            free(temp);
        }
    }
    free(g->viz);
    free(g);
}

void bfs(struct _grafo* g, int inicio) {
    bool visitado[TAM];
    for (int i = 0; i < TAM; i++) {
        visitado[i] = false;
    }
    int fila[TAM];
    int inicioFila = 0, fimFila = 0;

    fila[fimFila++] = inicio;
    visitado[inicio] = true;

    printf("\nBFS a partir do vertice %d:\n", inicio);

    while (inicioFila < fimFila) {
        int v = fila[inicioFila++];

        printf("%d (Endereco: %p)\t", v, (void*)&(g->viz[v]));

        int count = 0;
        Viz* temp = g->viz[v];
        while (temp != NULL) {
            count++;
            temp = temp->prox;
        }

        int* vizinhos = (int*)malloc(count * sizeof(int));
        temp = g->viz[v];
        int j = 0;
        while (temp != NULL) {
            vizinhos[j++] = temp->noj;
            temp = temp->prox;
        }

        for (int k = 0; k < count - 1; k++) {
            for (int l = k + 1; l < count; l++) {
                if (vizinhos[k] > vizinhos[l]) {
                    int aux = vizinhos[k];
                    vizinhos[k] = vizinhos[l];
                    vizinhos[l] = aux;
                }
            }
        }

        for (int i = 0; i < count; i++) {
            int vizinho = vizinhos[i];
            if (!visitado[vizinho]) {
                fila[fimFila++] = vizinho;
                visitado[vizinho] = true;
            }
        }

        free(vizinhos);
    }
    printf("\n");
}



DSU* criaDSU(int n) {
    DSU* dsu = (DSU*)malloc(sizeof(DSU));
    dsu->pai = (int*)malloc(n * sizeof(int));
    dsu->rank = (int*)malloc(n * sizeof(int));
    dsu->n = n;

    for (int i = 0; i < n; i++) {
        dsu->pai[i] = i;
        dsu->rank[i] = 0;
    }
    return dsu;
}

int find(DSU* dsu, int x) {
    if (dsu->pai[x] != x) {
        dsu->pai[x] = find(dsu, dsu->pai[x]);
    }
    return dsu->pai[x];
}

void unionDSU(DSU* dsu, int x, int y) {
    int rootX = find(dsu, x);
    int rootY = find(dsu, y);

    if (rootX != rootY) {
        if (dsu->rank[rootX] > dsu->rank[rootY]) {
            dsu->pai[rootY] = rootX;
        }
        else if (dsu->rank[rootX] < dsu->rank[rootY]) {
            dsu->pai[rootX] = rootY;
        }
        else {
            dsu->pai[rootY] = rootX;
            dsu->rank[rootX]++;
        }
    }
}

int comparaArestas(const void* a, const void* b) {
    return ((Aresta*)a)->peso - ((Aresta*)b)->peso;
}

void kruskal(struct _grafo* g) {
    Aresta* arestas = (Aresta*)malloc(g->na * sizeof(Aresta));
    int indice = 0;

    for (int i = 0; i < TAM; i++) {
        Viz* v = g->viz[i];
        while (v != NULL) {
            if (i < v->noj) {
                arestas[indice].u = i;
                arestas[indice].v = v->noj;
                arestas[indice].peso = v->peso;
                indice++;
            }
            v = v->prox;
        }
    }

    qsort(arestas, g->na, sizeof(Aresta), comparaArestas);

    DSU* dsu = criaDSU(g->nv);

    printf("\nArvore Geradora Minima (MST) - Kruskal:\n");
    float pesoTotal = 0;
    int arestasMST = 0;

    for (int i = 0; i < g->na; i++) {
        int u = arestas[i].u;
        int v = arestas[i].v;
        float peso = arestas[i].peso;

        if (find(dsu, u) != find(dsu, v)) {
            printf("Aresta (%d [Endereco: %p], %d [Endereco: %p]) - Peso: %.1f\n",
                u, (void*)&(g->viz[u]), v, (void*)&(g->viz[v]), peso);
            unionDSU(dsu, u, v);
            pesoTotal += peso;
            arestasMST++;
            printf("Peso Total Atual da MST: %.1f\n", pesoTotal);
        }

        if (arestasMST == g->nv - 1) break;
    }

    printf("Peso Total da MST: %.1f\n", pesoTotal);

    free(dsu->pai);
    free(dsu->rank);
    free(dsu);
    free(arestas);
}


int main() {
    int nv = 10;
    struct _grafo* g = criaGrafo(nv);

    insereAresta(g, 0, 1, 4.0);
    insereAresta(g, 0, 8, 8.0);
    insereAresta(g, 1, 8, 11.0);
    insereAresta(g, 1, 3, 8.0);
    insereAresta(g, 3, 6, 4.0);
    insereAresta(g, 3, 4, 7.0);
    insereAresta(g, 4, 5, 9.0);
    insereAresta(g, 4, 6, 14.0);
    insereAresta(g, 6, 5, 10.0);
    insereAresta(g, 7, 6, 2.0);
    insereAresta(g, 8, 9, 7.0);
    insereAresta(g, 8, 7, 1.0);
    insereAresta(g, 9, 3, 2.0);
    insereAresta(g, 9, 7, 6.0);

    imprimeGrafoComEnderecos(g);

    criaListaAdjacencias(g);

    criaMatrizAdjacencias(g);

    bfs(g, 0);

    kruskal(g);

    liberaGrafo(g);

    return 0;
}