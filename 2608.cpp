#include <vector>
#include <queue> //fila para usar na bfs
#include <limits.h>
#include <list>

using namespace std;

class Grafo {
public:
    int V;
    list<int> *adj; //ponteiro para lista de adjacencia

    Grafo(int V) {
        this->V = V;
        adj = new list<int>[V]; // aloca memoria para a lista de adjacencia
    }

    void addAresta(int v, int w) {
        adj[v].push_back(w); // add aresta no grafo
    }
};

class Solution {
public:
    int findShortestCycle(int n, vector<vector<int>>& edges) {
        Grafo grafo(n);

        // inicializa o grafo 
        int tamanho = edges.size();
        for (int i = 0; i < tamanho; i++) {
            int origem = edges[i][0];
            int destino = edges[i][1];
            grafo.addAresta(origem, destino);
            grafo.addAresta(destino, origem); // grafo bidirecional
        }

        int shortestCycle = INT_MAX; // ciclo mais curto

        // busca em largura para encontrar o ciclo mais curto
        for (int start = 0; start < n; start++) {
            vector<int> distance(n, -1);
            vector<int> tempDistance = distance;
            queue<int> q; 
            q.push(start); // add o vertice inicial na fila
            tempDistance[start] = 0; // atribuindo distancia inicial como 0
            distance[start] = tempDistance[start]; 

            while (!q.empty()) {
                int node = q.front(); // pega o primeiro elemento da fila
                int currentNode = node; 
                q.pop(); // remove o primeiro elemento da fila

                // percorre os vertices adjacentes ao vertice atual
                for (auto it = grafo.adj[currentNode].begin(); it != grafo.adj[currentNode].end(); it++) {
                    int vizinho = *it;
                    if (distance[vizinho] == -1) { // se o vertice nao foi visitado
                        int novaDistancia = distance[currentNode] + 1; 
                        distance[vizinho] = novaDistancia;
                        tempDistance[vizinho] = distance[vizinho]; 
                        q.push(vizinho);
                    } else if (distance[vizinho] >= distance[currentNode]) { // se o vertice ja foi visitado
                        int cicloAtual = distance[currentNode] + distance[vizinho] + 1; 
                        shortestCycle = min(shortestCycle, cicloAtual);
                    }
                }
            }
        }

        // se nao foi encontrado nenhum ciclo retorna -1
        int resultado;
        if (shortestCycle == INT_MAX) {
            resultado = -1;
        } else {
            resultado = shortestCycle;
        }
        return resultado;
    }
};
