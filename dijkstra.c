#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define V 5
#define INF INT_MAX

void imprimirCaminho(int pai[], int j) {
    if (pai[j] == -1)
        return;
    imprimirCaminho(pai, pai[j]);
    printf(" -> %c", j + 'A');
}

void imprimirSolucao(int dist[], int pai[], int src) {
    int i;
	for (i = 0; i < V; i++) {
        printf("\ndistancia de %c ate %c = %d\n", src + 'A', i + 'A', dist[i]);
        printf("Caminho: %c", src + 'A');
        imprimirCaminho(pai, i);
        printf("\n");
    }
}

int menorDistancia(int dist[], bool visitado[]) {
    int min = INF, min_index;
    int v;
    for (v = 0; v < V; v++)
        if (visitado[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void dijkstra(int grafo[V][V], int src) {
    int dist[V];
    bool visitado[V];
    int pai[V];
    
    int i;
    for (i = 0; i < V; i++) {
        dist[i] = INF;
        visitado[i] = false;
        pai[i] = -1;
    }
    
    dist[src] = 0;
    
    int count;
    for (count = 0; count < V - 1; count++) {
        int u = menorDistancia(dist, visitado);
        visitado[u] = true;
        
        int v;
        for (v = 0; v < V; v++)
            if (!visitado[v] && grafo[u][v] && dist[u] != INF && dist[u] + grafo[u][v] < dist[v]) {
                dist[v] = dist[u] + grafo[u][v];
                pai[v] = u;
            }
    }
    
    imprimirSolucao(dist, pai, src);
}

int main() {
    int grafo[V][V] = {
        {0, 4, 2, 7, 0},
        {4, 0, 1, 0, 1},
        {2, 1, 0, 3, 3},
        {7, 0, 3, 0, 2},
        {0, 1, 3, 2, 0}
    };
    
    dijkstra(grafo, 0);
    
    return 0;
} 
