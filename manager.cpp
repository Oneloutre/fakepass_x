#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "manager.hpp"
#include "AES.hpp"

void Manager::add(const std::string &platform, const std::string &id, const std::string &password, const bool &twofa)
{
    if (twofa)
    {
        std::string code;
        std::cout << "Entrez le code de vérification à deux facteurs : ";
        std::getline(std::cin, code);
        std::ofstream file("passwords.txt", std::ios::app);
        file << platform << " " << id << " " << password << " " << code << std::endl;
        file.close();
    }
    else {
        std::ofstream file("passwords.txt", std::ios::app);
        file << platform << " " << id << " " << password << "\n"; //std::endl ne fonctionne pas pitié
        file.close();
    }
}

void Manager::remove(const std::string &platformSearched){
    std::ifstream file("passwords.txt");
    std::string line;
    std::ofstream temp("temp.txt");
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string platform;
        iss >> platform;
        if (platform != platformSearched)
        {
            temp << line << std::endl;
        }
    }
    file.close();
    temp.close();
    std::remove("passwords.txt");
    std::rename("temp.txt", "passwords.txt");
}

void Manager::get(const std::string &platformSearched)
{
    std::ifstream file("passwords.txt");
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string platform, id, password;
        iss >> platform >> id >> password;
        if (platform == platformSearched)
        {
            std::cout << "-----------------------------------------------------------------------------------------------------------------------------" << std::endl;
            std::cout << "platform: " << platform << ", identifiant: " << id << ", password: " << password << std::endl;
            std::cout << "-----------------------------------------------------------------------------------------------------------------------------" << std::endl;

            return;
        }
    }
    std::cout << "Platforme introuvable, aucun identifiant enregistré pour celle-ci." << std::endl;
}

void Manager::print()
{
    std::ifstream file("passwords.txt");
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string platform, id, password, twofa;
        iss >> platform >> id >> password >> twofa;
        if (!empty(twofa)) // Je pensais utiliser if ( ! code="" ) mais mon IDE m'a conseillé cette méthode.
        {
            std::cout << "platform: " << platform << ", identifiant: " << id << ", password: " << password << ", 2fa: " << twofa << std::endl;
        }
        else
        std::cout << "platform: " << platform << ", identifiant: " << id << ", password: " << password << std::endl;
    }
    file.close();
}

void Manager::encrypt(const std::string &key)
{

    EasyAES aes;
    std::ifstream file("passwords.txt");
    std::ostringstream contenuStream;
    contenuStream << file.rdbuf();
    std::string contenu = contenuStream.str();
    std::string plain = aes.encrypt(contenu, key);
    file.close();
    std::ofstream newfile("passwords.txt", std::ios::trunc);
    newfile << plain;
    newfile.close();
    std::cout << "Les mots de passe ont été chiffrés." << std::endl;

}


bool is_empty(std::ifstream& pFile) // Merci StackOverflow...
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

void Manager::decrypt(const std::string &key)
{
    EasyAES aes;
    std::ifstream file("passwords.txt");
    if (is_empty(file))
    {
        return;
    }
    std::ostringstream contenuStream;
    contenuStream << file.rdbuf();
    std::string contenu = contenuStream.str();
    std::string plain = aes.decrypt(contenu, key);
    file.close();
    std::ofstream newfile("passwords.txt", std::ios::trunc);
    newfile << plain;
    newfile.close();
    std::cout << "Les mots de passe ont été déchiffrés." << std::endl;
}

void Manager::checkSafety(const std::string &password) {
    if (password.length() < 8) {
        std::cout << "Le mot de passe doit contenir au moins 8 caractères." << std::endl;
    } else if (password.find_first_of("0123456789") == std::string::npos) {
        std::cout << "Le mot de passe doit contenir au moins un chiffre." << std::endl;
    } else if (password.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == std::string::npos) {
        std::cout << "Le mot de passe doit contenir au moins une lettre majuscule." << std::endl;
    } else if (password.find_first_of("abcdefghijklmnopqrstuvwxyz") == std::string::npos) {
        std::cout << "Le mot de passe doit contenir au moins une lettre minuscule." << std::endl;
    }
    else {
        std::cout << "Le mot de passe est sécurisé." << std::endl;
    }
    std::ifstream file("common_passwords.txt");
    std::string line;
    while (std::getline(file, line)) {
        if (line == password) {
            std::cout << "Le mot de passe est trop commun." << std::endl;
            return;
        }
    }
    file.close();

}

std::string Manager::passwordGenerator() {
    std::string password;
    std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!?()&";
    for (int i = 0; i < 16; i++) {
        password += characters[rand() % characters.length()];
    }
    return password;
}