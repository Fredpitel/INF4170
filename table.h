/* 
 * Fichier: table.h
 * Auteur: Frédéric Pitel
 * Code permanent: PITF16088608
 * INF4170
 */

#ifndef TABLE_H
#define	TABLE_H

#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

class Table{
    private:
        class Element{
            public:
                Element(const Element& e){valeur = e.valeur, utiliser = e.utiliser, strcpy(bits, e.bits), paire = e.paire, quatre = e.quatre;}
                Element(int val): valeur(val), utiliser(false), paire(0), quatre(0){}
                Element(){}
                ~Element(){}
                int valeur;
                bool utiliser;
                char bits[4];
                int paire;
                int quatre;
        };
        // réorganise les Elements pour avoir le format des tables de Karnaugh 
        void swap();
        // cherche des groupes de 8
        void groupeHuit();
        // cherche des groupes de 4
        void groupeQuatre();
        // cherche des groupes de 2
        void groupeDeux();
        // checher les 1 sans groupe
        void elementSeul();
        // valide et choisi quels groupes doivent être affichés
        void choisirGroupe(const vector<vector<Element*> >& metagroupe);
        // affiche les groupes choisis
        void afficherGroupe(const vector<Element*>& groupe);
        // change le champ "utiliser" pour tous les Elements du groupe à true
        void flagGroupe(const vector<Element*>& groupe);
        
        bool premier;
        char variables[5];
        int restant;
        int un;
        vector<vector<Element> > resultat;
        
    public:
        Table(): premier(true), un(0){}
        ~Table(){}
        // affiche la solution de table de Karnaugh
        void afficher();
        // lit le fichier et enregistre les valeurs
        friend istream& operator >> (istream& is, Table& table);
};
#endif	/* TABLE_H */

