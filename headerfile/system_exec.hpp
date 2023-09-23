#ifndef CONTROL_PANEL_SYSTEM_EXEC_HPP
    #define CONTROL_PANEL_SYSTEM_EXEC_HPP


    #include <string>

    class system_exec
    {
    private:
        std::string _pwd;

    public:

        system_exec();
        ~system_exec() = default;

        std::string exe(std::string command);

        void refresh_pwd();
        std::string return_pwd();
    };


#endif //CONTROL_PANEL_SYSTEM_EXEC_HPP
