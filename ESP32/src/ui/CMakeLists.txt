SET(SOURCES ui_Login.c
    ui_Main.c
    ui_Setting.c
    ui_TimerSetting.c
    ui_Score.c
    ui.c
    ui_comp_hook.c
    ui_helpers.c
    ui_events.cpp
    ui_img_play_png.c
    ui_img_setting_png.c
    ui_img_timer_png.c
    ui_img_leaderboard_png.c
    ui_img_restart_png.c
    ui_img_success_png.c
    ui_img_fail_png.c
    ui_img_back_png.c
    fonts/ui_font_Digit.c
    fonts/ui_font_XFail.c)

add_library(ui ${SOURCES})
