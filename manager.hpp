#ifndef _ANNUAIRE_H
#define _ANNUAIRE_H
#include <string>
#include <map>

class Manager
{
public:
    void add(const std::string &platform, const std::string &id, const std::string &password, const bool &twofa);
    void remove(const std::string &platform);
    void get(const std::string &platform);
    void print();
    void encrypt(const std::string &key);
    void decrypt(const std::string &key);
    void checkSafety(const std::string &key);
    std::string passwordGenerator();
};

#endif
