#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "../headerfile/system_exec.hpp"

system_exec::system_exec()
{
    set_default_pwd();
    refresh_pwd_style();
    refresh_ls();
    refresh_ls_directory();
}

std::string system_exec::exe(const std::string& command)
{
    char buffer[128];
    std::string result;

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

void system_exec::set_default_pwd()
{
    _pwd = exe("echo $HOME");
}

void system_exec::set_pwd(const std::string &pwd)
{
    _pwd = pwd;

    refresh_pwd_style();
    refresh_ls();
    refresh_ls_directory();
}

void system_exec::refresh_pwd_style()
{
    if (!_pwd.empty() && _pwd.back() == '\n')
        _pwd_rewritten = _pwd.substr(0, _pwd.length() - 1);
    else
        _pwd_rewritten = _pwd;

    std::string final;

    std::istringstream iss(_pwd_rewritten);
    std::vector<std::string> parsedStrings;

    // Utilise un stringstream pour séparer la chaîne par les '/'
    std::string word;
    while (std::getline(iss, word, '/')) {
        final += word + " > ";
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
    _ls = exe("ls " + _pwd);
    //std::cout << _ls << std::endl;
}

void system_exec::refresh_ls_directory()
{
    _ls_files = exe("ls -l " + _pwd);
    // Afficher uniquement les fichiers cachés    ls -a | grep "^\."
    //std::cout << _ls_files << std::endl;

    std::string final;

    std::string directory_name;
    std::string file_name;
    ordered_file_list = "";

    size_t pos1 = 0;
    size_t pos = _ls.find('\n',pos1);

    file_count = 0;
    directory_count = 0;

    for (int i=0;i<int(_ls_files.length());i++)
    {
        final += _ls_files[i];
        if (_ls_files[i] == '\n')
        {
            //std::cout << final << std::endl;
            if ("total" == final.substr(0, 5))
            {
                final = "";
                continue;
            }

            if (final[0] == 'd')
            {
                directory_count++;
                directory_name += _ls.substr(pos1, pos - pos1);
                directory_name += "\n";
                pos1 = pos+1;
                pos = _ls.find('\n',pos1);
            }
            else if (final[0] == '-')
            {
                file_count++;
                file_name += _ls.substr(pos1, pos - pos1);
                file_name += "\n";
                pos1 = pos+1;
                pos = _ls.find('\n',pos1);
            }
            final = "";
        }
    }
    ordered_file_list = directory_name + file_name;

    //std::cout << "File count: " << file_count << std::endl;
    //std::cout << "Directory count: " << directory_count << std::endl;
}

std::vector<int> system_exec::return_file_and_directory_count() const
{
    std::vector<int> vector;
    vector.push_back(directory_count);
    vector.push_back(file_count);

    return vector;
}

std::string system_exec::return_ofl(Command_Option option)
{
    if (option == Command_Option::Rewrite)
    {
        std::string final;
        size_t pos1 = 0;
        size_t pos = ordered_file_list.find('\n',pos1);

        for (int i = 0; i < directory_count + file_count; i++) {
            if (pos - pos1 > 30)
                final += ordered_file_list.substr(pos1, 35) + "..." + "\n";
            else
                final += ordered_file_list.substr(pos1, pos - pos1) + "\n";

            pos1 = pos+1;
            pos = ordered_file_list.find('\n',pos1);
        }
        return final;
    }
    return ordered_file_list;

}
