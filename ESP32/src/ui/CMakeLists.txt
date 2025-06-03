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
    ui_img_wirecomponent_png.c
    ui_img_buttoncomponent_png.c
    ui_img_keypadcomponent_png.c
    ui_img_simoncomponent_png.c
    ui_img_whosonfirstcomponent_png.c
    ui_img_memorycomponent_png.c
    ui_img_morsecodecomponent_png.c
    ui_img_vennwirecomponent_png.c
    ui_img_wiresequencecomponent_png.c
    ui_img_mazecomponent_png.c
    ui_img_passwordcomponent_png.c
    ui_img_needyventcomponent_png.c
    ui_img_needydischargecomponent_png.c
    ui_img_needyknobcomponent_png.c
    ui_img_back_png.c
    ui_img_exit_png.c
    fonts/ui_font_Digit.c
    fonts/ui_font_XFail.c)

add_library(ui ${SOURCES})
