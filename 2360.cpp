#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int dfs(vector<int>& arestas, int atual, int c, vector<int>& visitado, vector<int>& tamanhoCiclo) {
        if (atual == -1) return -1; // Se não há aresta de saída, termina
        if (tamanhoCiclo[atual]) return tamanhoCiclo[atual]; // Se já calculamos para este nó, retorna o valor armazenado
        if (visitado[atual]) { // Detecta um ciclo
            tamanhoCiclo[atual] = c - visitado[atual] + 1; // Calcula o tamanho do ciclo
            return tamanhoCiclo[atual];
        }
        
        c++;
        visitado[atual] = c; // Marca o nó atual como visitado com a profundidade atual
        
        int resultado = dfs(arestas, arestas[atual], c, visitado, tamanhoCiclo); // Chamada recursiva para o próximo nó
        tamanhoCiclo[atual] = resultado; // Armazena o resultado no tamanhoCiclo
        return resultado;
    } 
    
    int longestCycle(vector<int>& arestas) {
        int n = arestas.size();
        vector<int> tamanhoCiclo(n); // Vetor de memorizar o tamanho do ciclo para cada nó
        int resposta = -1; // Armazena o tamanho do ciclo mais longo
        vector<int> visitado(n); // Vetor para armazenar o estado de visitação de cada nó
        
        for (int i = 0; i < n; i++) {
            resposta = max(resposta, dfs(arestas, i, 0, visitado, tamanhoCiclo)); // Atualiza o ciclo mais longo encontrado
        }
        
        return resposta;
    }
};