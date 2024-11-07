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
        for (int i = 0; i < edges.size(); i++) {
            grafo.addAresta(edges[i][0], edges[i][1]);
            grafo.addAresta(edges[i][1], edges[i][0]); // grafo bidirecional
        }

        int shortestCycle = INT_MAX;// ciclo mais curto

        // busca em largura para encontrar o ciclo mais curto
        for (int start = 0; start < n; start++) {
            vector<int> distance(n, -1);
            queue<int> q; 
            q.push(start);// add o vertice inicial na fila
            distance[start] = 0;// atribundo distancia inicial como 0

            while (!q.empty()) {
                int node = q.front();// pega o primeiro elemento da fila
                q.pop();// remove o primeiro elemento da fila


                // percorre os vertices adjacentes ao vertice atual
                for (auto it = grafo.adj[node].begin(); it != grafo.adj[node].end(); it++) {
                    if (distance[*it] == -1) {// se o vertice nao foi visitado
                        distance[*it] = distance[node] + 1;// add +1 na distancia
                        q.push(*it);
                    } else if (distance[*it] >= distance[node]) {// se o vertice ja foi visitado
                        shortestCycle = min(shortestCycle, distance[node] + distance[*it] + 1);// atualiza o ciclo mais curto
                    }
                }
            }
        }
        // se nao foi encontrado nenhum ciclo retorna -1
        return (shortestCycle == INT_MAX) ? -1 : shortestCycle;
    }
};
