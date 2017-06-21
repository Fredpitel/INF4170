/* 
 * Fichier: main.cpp
 * Auteur: Frédéric Pitel
 * Code permanent: PITF16088608
 * INF4170
 */

#include "table.h"

using namespace std;

int main(int argc, char** argv) {
    
    if(argc!=2){
        cout << "Syntaxe: ./karnaugh fichier.txt" << endl;
        return 1;
    }

    ifstream fichier(argv[1]);
    if(fichier.fail()){
        cout << "Erreur lors de l'ouverture du fichier: " << argv[1] << endl;    
        return 1;
    }
    
    Table table;
    fichier >> table;
    table.afficher();
    cout << endl;

    return 0;
}
