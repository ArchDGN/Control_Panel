#ifndef CONTROL_PANEL_SYSTEM_EXEC_HPP
    #define CONTROL_PANEL_SYSTEM_EXEC_HPP


    #include <string>

    #include "../headerfile/data.hpp"

    class system_exec
    {
    private:
        std::string _pwd;
        std::string _pwd_rewritten;

        std::string _ls;

    public:

        system_exec();
        ~system_exec() = default;

        std::string exe(std::string command);

        void refresh_pwd();
        std::string return_pwd(Command_Option option);

        void refresh_ls();
    };


#endif //CONTROL_PANEL_SYSTEM_EXEC_HPP
