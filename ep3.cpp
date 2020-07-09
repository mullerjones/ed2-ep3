#include <string>
#include <iostream>
#include "interface.hpp"
using namespace std;

int main(int argc, char** argv)
{
    string regex;
    string palavra;
    if(argc > 1)
    {
        regex = argv[1];
        palavra = argv[2];
    }
    else
    {
        cout << "Para uso pela linha de comando, execute \'./ep3 [regex] [palavra]\'" << endl;
        cout << "Insira expressão do ReGex: ";
        cin >> regex;
        cout << "Insira palavra de teste: ";
        cin >> palavra;
    }

    cout << "Regex = " << regex << endl;
    cout << "Palavra = " << palavra << endl;
    
    Grafo g(regex);
    if(g.reconheceG(palavra)) printf("Palavra reconhecida pela expressão regular.\n");
    else printf("Palavra não reconhecida pela expressão regular.\n");
    

    return 0;
}