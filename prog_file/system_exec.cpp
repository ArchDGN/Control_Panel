#include <iostream>

#include "../headerfile/system_exec.hpp"

system_exec::system_exec()
{
    _pwd = exe("pwd");
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
}
std::string system_exec::return_pwd()
{
    return _pwd;
}