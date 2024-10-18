#include <iostream>
#include <string>
#include "manager.hpp"

using namespace std;

void unitTest(){
    Manager manager;
    manager.decrypt("roch");
    manager.add("platform", "id", "password", false);
    manager.encrypt("roch");
}

void ui() {
    Manager manager;
    string command;
    string key;
    cout << "Entrez la clé de chiffrement : ";
    getline(cin, key);

    manager.decrypt(key);

    while (true) {
        cout << "\n-----------------------------------\n|     Que voulez vous faire ?     |" << endl;
        cout
                << "-----------------------------------\n|   a : ajouter                   |\n|   l : afficher un objet         |\n|   r : enlever un objet          |\n|   p : afficher tous les objets  |\n|   v : tester un mdp             |\n|   g : générer un mdp            |\n|   q : quitter                   |\n-----------------------------------"
                << endl;
        cout << "> ";
        getline(cin, command);

        if (command == "a") {
            string platform;
            string id;
            string password;
            string twofaString;
            cout << "platform : ";
            getline(cin, platform);
            cout << "id : ";
            getline(cin, id);
            cout << "password : ";
            getline(cin, password);
            if (password == "") {
                password = manager.passwordGenerator();
                cout << "Mot de passe généré : " << password << endl;
            }
            cout << "Voulez vous ajouter une 2fa ? (y/n) : ";
            getline(cin, twofaString);
            if (twofaString == "y") {
                manager.add(platform, id, password, true);
            } else {
                manager.add(platform, id, password, false);
            }
        } else if (command == "l") {
            string platform;
            cout << "\nplatform : ";
            getline(cin, platform);
            manager.get(platform);
        } else if (command == "r") {
            string platform;
            cout << "platform : ";
            getline(cin, platform);
            manager.remove(platform);
        } else if (command == "p") {
            manager.print();
        } else if (command == "q") {
            manager.encrypt(key);
            break;
        } else if (command == "v") {
            string password;
            cout << "password : ";
            getline(cin, password);
            manager.checkSafety(password);
        } else if (command == "g") {
            cout << "Mot de passe généré : " << manager.passwordGenerator() << endl;
        }
        else {
            cout << "Commande inconnue" << endl;
        }
    }
}

int main() {
    unitTest();
    ui();
    return 0;
}
