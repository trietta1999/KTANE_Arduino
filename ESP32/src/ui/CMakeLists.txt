SET(SOURCES ui_Main.c
    ui.c
    ui_comp_hook.c
    ui_helpers.c
    ui_events.cpp
    ui_img_maze0_png.c
    ui_img_assistant_navigation_png.c
    ui_img_arrow_up_png.c
    ui_img_arrow_left_png.c
    ui_img_arrow_right_png.c
    ui_img_arrow_down_png.c
    ui_img_success_png.c
    ui_img_fail_png.c
    ui_img_maze1_png.c
    ui_img_maze2_png.c
    ui_img_maze3_png.c
    ui_img_maze4_png.c
    ui_img_maze5_png.c
    ui_img_maze6_png.c
    ui_img_maze7_png.c
    ui_img_maze8_png.c)

add_library(ui ${SOURCES})
