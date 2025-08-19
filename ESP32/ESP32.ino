#include <lvgl.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

#include "src/ui/ui.h"
#include "src/CommonData.h"
#include "src/CommonLibrary.h"
#include "src/CommonService.h"

#define BL_PIN 21

// Touchscreen pins
#define XPT2046_IRQ 36   // T_IRQ
#define XPT2046_MOSI 32  // T_DIN
#define XPT2046_MISO 39  // T_OUT
#define XPT2046_CLK 25   // T_CLK
#define XPT2046_CS 33    // T_CS

// Screen resolution
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

// Get the Touchscreen data
void touchscreen_read(lv_indev_t* indev, lv_indev_data_t* data) {
  // Checks if Touchscreen was touched, and prints X, Y and Pressure (Z)
  if (touchscreen.tirqTouched() && touchscreen.touched()) {
    // Get Touchscreen points
    TS_Point p = touchscreen.getPoint();
    data->state = LV_INDEV_STATE_PRESSED;

    // Set the coordinates
    data->point.x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
    data->point.y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
  } else {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}

// Todo: ProcessRequest()

void setup() {
  // LVGL init
  lv_init();

  // Start the SPI for the touchscreen and init the touchscreen
  touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  touchscreen.begin(touchscreenSPI);
  touchscreen.setRotation(2);

  // Create a display object
  lv_display_t* disp;
  // Initialize the TFT display using the TFT_eSPI library
  disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));
  lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_270);

  // Initialize an LVGL input device object (Touchscreen)
  lv_indev_t* indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  // Set the callback function to read Touchscreen input
  lv_indev_set_read_cb(indev, touchscreen_read);

  // Create UI
  ui_init();

  // Init service
  InitData();

  // Init GUI
  Init();

  pinMode(BL_PIN, OUTPUT);
  analogWrite(BL_PIN, sys_gui::Brightness.GetValue());
}

void IOProcessData() {
  // Change brightness
  if (sys_gui::Brightness.GetState()) {
    analogWrite(BL_PIN, sys_gui::Brightness.GetValue());
  }
}

void loop() {
  lv_timer_handler();
  lv_task_handler();
  ProcessData();
  IOProcessData();
  AutoUpdate();
  UpdateAll();
  lv_tick_inc(10);
  delay(10);
}
