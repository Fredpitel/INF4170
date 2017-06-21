/* 
 * Fichier: table.cpp
 * Auteur: Frédéric Pitel
 * Code permanent: PITF16088608
 * INF4170
 */

#include "table.h"

void Table::afficher(){
    if (un != 16 && un != 0){
        swap();
        if(un >= 8) groupeHuit();
        if(un >= 4 && restant > 0) groupeQuatre();
        if(un >= 2 && restant > 0) groupeDeux();
        if(restant > 0) elementSeul();
    } else {
        if(un == 16) cout << variables[4] << " = 1" << flush;
        if(un == 0) cout << variables[4] << " = 0" << flush;
    }
}

void Table::swap (){
    
    vector<Element> temp = resultat[2];
    resultat[2] = resultat[3];
    resultat[3] = temp;
    
    for(int i = 0; i < 4; i++){
        Element etemp = resultat[i][2];
        resultat[i][2] = resultat[i][3];
        resultat[i][3] = etemp;
    }
}

void Table::groupeHuit(){
    vector<Element*> groupe;
    
    for(int i = 0; i < 4; i++){
        for(int j = i; j < (i + 4); j++){
            if(resultat[i][j % 4].valeur != 1) break;
            groupe.push_back(&(resultat[i][j % 4]));
        }
        if(groupe.size() == 4){
            for(int j = i; j < (i + 4); j++){
                if(resultat[(i + 1) % 4][j % 4].valeur != 1) break;
                groupe.push_back(&(resultat[(i + 1) % 4][j % 4]));
            }
        }
        if(groupe.size() == 8){
            flagGroupe(groupe);
            afficherGroupe(groupe);
        }
        groupe.clear();
        for(int j = i; j < (i + 4); j++){
            if(resultat[j % 4][i].valeur != 1) break;
            groupe.push_back(&(resultat[j % 4][i]));
        }
        if(groupe.size() == 4){
            for(int j = i; j < (i + 4); j++){
                if(resultat[j % 4][(i + 1) % 4].valeur != 1) break;
                groupe.push_back(&(resultat[j % 4][(i + 1) % 4]));
            }
        }
        if(groupe.size() == 8){
            flagGroupe(groupe);
            afficherGroupe(groupe);
        }
        groupe.clear();
    }
}

void Table::groupeQuatre(){
    vector<Element*> groupe;
    vector<vector<Element*> > metagroupe;
    
    for(int i = 0; i < 4; i++){
        bool utiliser = true;
        for(int j = i; j < (i + 4); j++){
            if(resultat[i][j % 4].valeur != 1) break;
            if(!(resultat[i][j % 4].utiliser)) utiliser = false;
            groupe.push_back(&(resultat[i][j % 4]));
        }
        if(groupe.size() == 4 && !utiliser){
            for(vector<Element*>::const_iterator iter = groupe.begin(); iter < groupe.end(); iter++) {
                (*iter)->quatre++;
            }
            metagroupe.push_back(groupe);
        }
        groupe.clear();
        utiliser = true;
        for(int j = i; j < (i + 4); j++){
            if(resultat[j % 4][i].valeur != 1) break;
            if(!(resultat[j % 4][i].utiliser)) utiliser = false;
            groupe.push_back(&(resultat[j % 4][i]));
        }
        if(groupe.size() == 4 && !utiliser){
            for(vector<Element*>::const_iterator iter = groupe.begin(); iter < groupe.end(); iter++) {
                (*iter)->quatre++;
            }
            metagroupe.push_back(groupe);
        }
        groupe.clear();
    }
    
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            bool utiliser = true;
            for(int k = 0; k < 2; k++){
                for(int l = 0; l < 2; l++){
                    if(resultat[(i + k) % 4][(j + l) % 4].valeur != 1) break;
                    if(!(resultat[(i + k) % 4][(j + l) % 4].utiliser)) utiliser = false;
                    groupe.push_back(&(resultat[(i + k) % 4][(j + l) % 4]));
                }
            }
            if(groupe.size() == 4 && !utiliser){
                for(vector<Element*>::const_iterator iter = groupe.begin(); iter < groupe.end(); iter++) {
                    (*iter)->quatre++;
                }
                metagroupe.push_back(groupe);
            }
            groupe.clear();
        }
    }
    choisirGroupe(metagroupe);
}

void Table::groupeDeux(){
    vector<Element*> groupe;
    vector<vector<Element*> > metagroupe;
    
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            bool utiliser = true;
            if(resultat[i][j].valeur == 1){
                if(!(resultat[i][j].utiliser)) utiliser = false;
                groupe.push_back(&(resultat[i][j]));
                if(resultat[i][(j+1) % 4].valeur == 1){
                    if(!(resultat[i][(j+1) % 4].utiliser)) utiliser = false;
                    groupe.push_back(&(resultat[i][(j+1) % 4]));
                }
                if(groupe.size() == 2 && !utiliser){
                    for(vector<Element*>::const_iterator iter = groupe.begin(); iter < groupe.end(); iter++) {
                        (*iter)->paire++;
                    }
                    metagroupe.push_back(groupe);
                }
                groupe.clear();
                utiliser = true;
                if(!(resultat[i][j].utiliser)) utiliser = false;
                groupe.push_back(&(resultat[i][j]));
                if(resultat[(i+1) % 4][j].valeur == 1){
                    if(!(resultat[(i+1) % 4][j].utiliser)) utiliser = false;
                    groupe.push_back(&(resultat[(i+1) % 4][j]));
                }
                if(groupe.size() == 2 && !utiliser){
                    for(vector<Element*>::const_iterator iter = groupe.begin(); iter < groupe.end(); iter++) {
                        (*iter)->paire++;
                    }
                    metagroupe.push_back(groupe);
                }
                groupe.clear();
            }
        }
    }
    
    choisirGroupe(metagroupe);
}

void Table::elementSeul(){
    vector<Element*> groupe;
    
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(resultat[i][j].valeur == 1 && !(resultat[i][j].utiliser)){
                groupe.push_back(&(resultat[i][j]));
                flagGroupe(groupe);
                afficherGroupe(groupe);
            }
            groupe.clear();
        }
    }
}

void Table::choisirGroupe(const vector<vector<Element*> >& metagroupe){
    for(vector<vector<Element*> >::const_iterator iter = metagroupe.begin(); iter < metagroupe.end(); iter++) {
        for(vector<Element*>::const_iterator iter2 = (*iter).begin(); iter2 < (*iter).end(); iter2++){
            if((*iter).size() == 4){
                if((*iter2)->quatre == 1){
                    flagGroupe(*iter);
                    afficherGroupe(*iter);
                    break;
                }
            } else {
                if((*iter2)->paire == 1){
                    flagGroupe(*iter);
                    afficherGroupe(*iter);
                    break;
                }
            }
        }
    }
    for(vector<vector<Element*> >::const_iterator iter = metagroupe.begin(); iter < metagroupe.end(); iter++) {
        bool utiliser = false;
        for(vector<Element*>::const_iterator iter2 = (*iter).begin(); iter2 < (*iter).end(); iter2++){
            if((*iter2)->utiliser) utiliser = true;
        }
        if(!utiliser){
            flagGroupe(*iter);
            afficherGroupe(*iter);            
        }
    }
    for(vector<vector<Element*> >::const_iterator iter = metagroupe.begin(); iter < metagroupe.end(); iter++) {
        for(vector<Element*>::const_iterator iter2 = (*iter).begin(); iter2 < (*iter).end(); iter2++){
            if(!((*iter2)->utiliser)){
                flagGroupe(*iter);
                afficherGroupe(*iter);                  
            }
        }
    }
}

void Table::afficherGroupe(const vector<Element*>& groupe){
    if(premier){
        cout << variables[4] << " = " << flush;
        premier = false;
    } else {
        cout << " + " << flush;
    }
    
    char solution[4];
    strcpy(solution, groupe[0]->bits);
    
    for(vector<Element*>::const_iterator iter = ++groupe.begin(); iter < groupe.end(); iter++) {
        for(int i = 0; i < 4; i++){
            if((*iter)->bits[i] != solution[i]) solution[i] = 2;
        }
    }
    
    for(int i = 0; i < 4; i++){
        if(solution[i] == '0') cout << "'" << variables[i] << flush;
        if(solution[i] == '1') cout << variables[i] << flush;
    }
    
}

void Table::flagGroupe(const vector<Element*>& groupe){
    for(vector<Element*>::const_iterator iter = groupe.begin(); iter < groupe.end(); iter++) {
        if(!(*iter)->utiliser){
            (*iter)->utiliser = true;
            restant--;
        }
    }
}

istream& operator >> (istream& is, Table& table) {
    string chaine;
    
    is >> chaine;
    strcpy(table.variables, (char*) chaine.c_str());
    is >> chaine;
    for(int i = 0; i < 4; i++){
        vector<Table::Element> elem;
        for(int j = 0; j < 4; j++){
            Table::Element e(chaine.at(4) - 48);
            strcpy(e.bits, (char*) chaine.substr(0,4).c_str());
            elem.push_back(e);
            if(e.valeur == 1) table.un++;
            is >> chaine;
        }
        table.resultat.push_back(elem);
        table.restant = table.un;
    }
    
    return is;
}

