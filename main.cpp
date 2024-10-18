#include <iostream>
#include <string>
#include "manager.hpp"

void unitTest(){
    Manager manager;
    manager.decrypt("roch");
    manager.add("platform", "id", "password", false);
    manager.encrypt("roch");
}

void ui() {
    Manager manager;
    std::string command;
    std::string key;
    std::cout << "Entrez la clé de chiffrement : ";
    std::getline(std::cin, key);

    manager.decrypt(key);

    while (true) {
        std::cout << "\n-----------------------------------\n|     Que voulez vous faire ?     |" << std::endl;
        std::cout
                << "-----------------------------------\n|   a : ajouter                   |\n|   l : afficher un objet         |\n|   r : enlever un objet          |\n|   p : afficher tous les objets  |\n|   v : tester un mdp             |\n|   g : générer un mdp            |\n|   q : quitter                   |\n-----------------------------------"
                << std::endl;
        std::cout << "> ";
        std::getline(std::cin, command);

        if (command == "a") {
            std::string platform;
            std::string id;
            std::string password;
            std::string twofaString;
            std::cout << "platform : ";
            std::getline(std::cin, platform);
            std::cout << "id : ";
            std::getline(std::cin, id);
            std::cout << "password : ";
            std::getline(std::cin, password);
            if (password == "") {
                password = manager.passwordGenerator();
                std::cout << "Mot de passe généré : " << password << std::endl;
            }
            std::cout << "Voulez vous ajouter une 2fa ? (y/n) : ";
            std::getline(std::cin, twofaString);
            if (twofaString == "y") {
                manager.add(platform, id, password, true);
            } else {
                manager.add(platform, id, password, false);
            }
        } else if (command == "l") {
            std::string platform;
            std::cout << "\nplatform : ";
            std::getline(std::cin, platform);
            manager.get(platform);
        } else if (command == "r") {
            std::string platform;
            std::cout << "platform : ";
            std::getline(std::cin, platform);
            manager.remove(platform);
        } else if (command == "p") {
            manager.print();
        } else if (command == "q") {
            manager.encrypt(key);
            break;
        } else if (command == "v") {
            std::string password;
            std::cout << "password : ";
            std::getline(std::cin, password);
            manager.checkSafety(password);
        } else if (command == "g") {
            std::cout << "Mot de passe généré : " << manager.passwordGenerator() << std::endl;
        }
        else {
            std::cout << "Commande inconnue" << std::endl;
        }
    }
}

int main() {
    unitTest();
    ui();
    return 0;
}