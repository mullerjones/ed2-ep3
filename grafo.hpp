#include <bits/stdc++.h>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <fstream>
//#include "vetorord.hpp"
using namespace std;

bool checaSemLetraI(string primeira, string segunda, int i);
bool checaTrocaLetras(string a, string b, int tamanho);
bool checaTrocarUmaLetra(string a, string b, int tamanho);

//k definido como no enunciado será passado como argumento de linha de comando
class Grafo
{

private:
    bool **matrizAdj;

    int size;
    string regex;

public:
    Grafo(string regOrigem)
    {
        /* Inicializa um grafo com parâmetro k */
        /*Le arquivo e monta tabela de simbolos*/
        int i, j;
        size = regOrigem.size();
        regex = regOrigem;

        /*Conta numero de palavras e aloca matriz de adjacencias*/
        matrizAdj = (bool **)malloc(size * sizeof(bool *));
        for (i = 0; i < size; i++)
        {
            matrizAdj[i] = (bool *)malloc(size * sizeof(bool));
            for (j = 0; j < size; j++)
            {
                matrizAdj[i][j] = false;
            }
        }
        /*Inicializa arcos*/
        stack<int> pilha;
        for (int i = 0; i < size; i++)
        {
            int ant = i;
            if (regex[i] == '(' || regex[i] == '|' || regex[i] == '[')
            {
                //if(i!=0 && regex[i-1]!='\\')
                pilha.push(i);
            }
            else if (regex[i] == ')')
            {
                int optopo;
                optopo = pilha.top();
                pilha.pop();
                vector<int> meios;
                while (regex[optopo] != '(')
                {
                    if (regex[optopo] == '|')
                    {
                        meios.push_back(optopo);
                        matrizAdj[optopo][i] = true;
                        if (!pilha.empty())
                        {
                            optopo = pilha.top();
                            pilha.pop();
                        }
                        else
                        {
                            optopo = ant;
                        }
                        
                    }
                }
                if (regex[optopo] == '(')
                {
                    while(!meios.empty())
                    {
                        int aux = meios.back();
                        meios.pop_back();
                        matrizAdj[optopo][aux+1] = true;
                    }
                    ant = optopo;
                }
            }
            /*
            else if(regex[i]==']')
            {
                int comeco = pilha.top();
                pilha.pop();
                for (int j = comeco+1; j < i; j++)
                {
                    matrizAdj[comeco][j] = true;
                    matrizAdj[j][i] = true;
                }
            }*/
            if (i < size - 1 && regex[i + 1] == '*')
            {
                matrizAdj[ant][i + 1] = true;
                matrizAdj[i + 1][ant] = true;
            }
            if (i < size - 1)
            {
                if (regex[i] == '*' || regex[i] == '(' || regex[i] == ')')
                    matrizAdj[i][i + 1] = true;
            }
        }
    }

    ~Grafo()
    {
        for (int i = 0; i < size; i++)
        {
            free(matrizAdj[i]);
        }
        free(matrizAdj);
    }

    void dfsR(int v, bool *marked)
    {
        marked[v] = true;
        for (int i = 0; i < size; i++)
        {
            if (matrizAdj[v][i] && !marked[i])
                dfsR(i, marked);
        }
    }
    bool reconheceG(string texto)
    {

        bool saida;
        bool *atingidos = new bool[size];
        for (int i = 0; i < size; i++)
        {
            atingidos[i] = false;
        }
        dfsR(0, atingidos);
        bool *atual = new bool[size+1];
        atual[size] = false;
        for (int i = 0; i < texto.size() && !atual[size]; i++)
        {
            for (int j = 0; j <= size; j++)
                atual[j] = false;
            for (int j = 0; j < size; j++)
            {
                if (atingidos[j] && regex[j] == texto[i])
                {
                    atual[j + 1] = true;
                }

            }
            bool *marcado = new bool[size];
            for (int j = 0; j < size; j++)
            {
                atingidos[j] = false;
            }
            for (int j = 0; j < size; j++)
            {
                if (atual[j])
                {
                    for (int k = 0; k < size; k++)
                    {
                        marcado[k] = false;
                    }
                    dfsR(j, marcado);
                    for (int k = 0; k < size; k++)
                    {
                        if (marcado[k])
                            atingidos[k] = true;
                    }
                }
            }
            
            delete[] marcado;
        }
        if(atual[size]) saida = true;
        else
        {
            saida = atingidos[size - 1];
        }
        delete[] atual;
        delete[] atingidos;
        return saida;
    }
};