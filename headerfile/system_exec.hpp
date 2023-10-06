#ifndef CONTROL_PANEL_SYSTEM_EXEC_HPP
    #define CONTROL_PANEL_SYSTEM_EXEC_HPP


    #include <string>
    #include <vector>

    #include "../headerfile/data.hpp"

    class system_exec
    {
    private:
        std::string _pwd;
        std::string _pwd_rewritten;

        std::string _ls;
        std::string _ls_directory;
        std::string _ls_file;
        int file_count;
        int directory_count;

    public:

        system_exec();
        ~system_exec() = default;

        std::string exe(std::string command);

        void refresh_pwd();
        std::string return_pwd(Command_Option option);

        void refresh_ls();
        void refresh_ls_directory();
        void refresh_ls_file();

        std::vector<int> return_file_and_directory_count();
    };


#endif //CONTROL_PANEL_SYSTEM_EXEC_HPP
