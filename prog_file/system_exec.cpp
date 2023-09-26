#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "../headerfile/system_exec.hpp"

system_exec::system_exec()
{
    refresh_pwd();
    refresh_ls();
    refresh_ls_directory();
    refresh_ls_file();
}

std::string system_exec::exe(std::string command)
{
    char buffer[128];
    std::string result = "";

    // Ouvre un processus et exécute la commande
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "Erreur lors de l'exécution de la commande." << std::endl;
    }

    // Lit la sortie de la commande et la stocke dans 'result'
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    pclose(pipe);

    return result;
}

void system_exec::refresh_pwd()
{
    _pwd = exe("pwd");
    _pwd_rewritten = _pwd;

    _pwd_rewritten = _pwd.substr(0, _pwd.length() - 1); // Enlève le '\n' à la fin de la chaîne

    std::string final = "";

    std::istringstream iss(_pwd_rewritten);
    std::vector<std::string> parsedStrings;

    // Utilise un stringstream pour séparer la chaîne par les '/'
    std::string word;
    while (std::getline(iss, word, '/')) {
        final = final + word + " > ";
        if (!word.empty())
            parsedStrings.push_back(word);
    }

    final = final.substr(0, final.length() - 3); // Enlève les 3 derniers caractères de la chaîne

    _pwd_rewritten = final;
}
std::string system_exec::return_pwd(Command_Option option)
{
    if (option == Command_Option::Rewrite)
        return _pwd_rewritten;
    return _pwd;
}

void system_exec::refresh_ls()
{
    _ls = exe("ls");
    //std::cout << _ls << std::endl;
}

void system_exec::refresh_ls_directory()
{
    _ls_directory = exe("ls -d */");
    //std::cout << _ls_directory << std::endl;
}

void system_exec::refresh_ls_file()
{
    _ls_file = exe("ls -p | grep -v /");
    //std::cout << _ls_file << std::endl;
}