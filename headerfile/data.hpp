#ifndef CONTROL_PANEL_DATA_HPP
    #define CONTROL_PANEL_DATA_HPP

    enum class Square_Color
    {
        Red,
        Blue,

        Gray1,
        Gray2,

        LightGray1,

        White,
        NONE
    };

    enum class Text_Property
    {
        Fit_Screen,
        Cut,
        Revert_Cut,
        Cut_With_Points,
        Revert_Cut_With_Points,
        Change_Size,

        NONE
    };

    enum class Command_Option
    {
        Rewrite,

        NONE
    };

#endif //CONTROL_PANEL_DATA_HPP
