#include <string>
#include <iostream>
#include "grafo.hpp"
using namespace std;

int main(int argc, char** argv)
{
    string regex;
    string* palavras;
    if(argc > 2)
    {
        regex = argv[1];
        palavras = new string[argc-2];
        for (int i = 2; i < argc; i++)
        {
            palavras[i-2] = argv[i];
        }
    }
    else
    {
        cout << "Para uso pela linha de comando, execute \'./ep3 [regex] [palavra]\'" << endl;
        cout << "Insira expressão do ReGex: ";
        cin >> regex;
        cout << "Insira palavra de teste: ";
        cin >> palavras[0];
    }

    cout << "Regex = " << regex << endl;
    
    Grafo g(regex);
    for (int i = 0; i < argc-2; i++)
    {
        cout << "Palavra " << i << " = " << palavras[i] << endl;
        if(g.reconheceG(palavras[i])) printf("Palavra reconhecida pela expressão regular.\n");
        else printf("Palavra não reconhecida pela expressão regular.\n");
    }
    
    
    

    return 0;
}