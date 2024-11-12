#include <vector>
#include <queue>

// questão 785 - Is Graph Bipartite?

// um grafo bipartido é um grafo que pode ser colorido com duas cores sem que vértices adjacentes tenham a mesma cor.

class Solution
{
public:
    bool isBipartite(std::vector<std::vector<int>> &grafo)
    {
        // recebe como entrada uma lista de adjacências representando um grafo não direcionado

        // duas estruturas principais:
        // vetor de cores inicializado com -1 (armazenando a cor de cada vertice)
        // fila para colrir (bfs)
        int tamanhoGrafo = grafo.size();

        std::vector<int> cores(tamanhoGrafo, -1); // -1 = não visitado
        // armazena cor de cada vertice (0 ou 1)

        // bfs modificado para colorir o grafo
        for (int vertice = 0; vertice < tamanhoGrafo; vertice++)
        {   
            // se o vertice já foi visitado, pula para o próximo
            if (cores[vertice] != -1) {continue;}

            std::queue<int> fila; // fila para bfs

            fila.push(vertice); // adiciona o vertice inicial na fila
            cores[vertice] = 0; // define a cor do vertice inicial


            // estrutura principal da bfs
            while (!fila.empty())
            {
                int verticeAtual = fila.front();//pega o vertice atual
                fila.pop();// remove o atual da fila

                int corVizinhos;
                if (cores[verticeAtual] == 0) { corVizinhos = 1; } // se a cor do vertice atual é 0, a cor dos vizinhos é 1
                else{ corVizinhos = 0;} // se a cor do vertice atual é 1, a cor dos vizinhos é 0

                for (int vizinho : grafo[verticeAtual])// para cada vizinho do vertice atual
                {
                    if (cores[vizinho] == -1) // se o vizinho não foi visitado
                    {
                        cores[vizinho] = corVizinhos; // define a cor do vizinho
                        fila.push(vizinho); // adiciona o vizinho na fila
                    }
                    else if (cores[vizinho] != corVizinhos) // se a cor do vizinho é diferente da cor do vertice atual
                    {
                        return false;
                    }
                }
            }
        }
        // se o grafo é bipartido, retorna true
        return true;
    }
};