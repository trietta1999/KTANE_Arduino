#include <lvgl.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include "BluetoothSerial.h"

#include "src/ui/ui.h"
#include "src/CommonData.h"
#include "src/CommonLibrary.h"

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

BluetoothSerial SerialBT;

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

void InitCDataFromFakeTimer() {
  uint32_t seed = esp_random();
  srand(seed);

  sys_host::RandomSeed.SetValue(seed);
  sys_host::LabelIndicator.SetValue((LABEL_INDICATOR)RandomRange(0, (uint8_t)LABEL_INDICATOR::MAX));
  sys_host::BatteryType.SetValue((BATTERY_TYPE)RandomRange(0, (uint8_t)BATTERY_TYPE::MAX));
  sys_host::ComPortType.SetValue((COMPORT_TYPE)RandomRange(0, (uint8_t)COMPORT_TYPE::MAX));
  sys_host::BatteryNum.SetValue(RandomRange(1, 5));
  sys_host::SerialNum.SetValue(GenerateSerialNumber());

  sys_gui::StrikeNum.SetValue(0);
  sys_gui::TimeCycle.SetValue(TIMECYCLE_0);
  sys_gui::SuccessState.SetValue(INCORRECT);
}

void DataProcess() {
  if (sys_gui::Brightness.GetState()) {
    analogWrite(BL_PIN, sys_gui::Brightness.GetValue());
  }

  if (SerialBT.available()) {
    String read = SerialBT.readStringUntil('\n');

    if (read == "sys_data") {
      SerialBT.println("===== Dummy Data Initialized =====");
      SerialBT.println(String("LabelIndicator: ") + map_LABEL_INDICATOR[sys_host::LabelIndicator.GetValue()].c_str());
      SerialBT.println(String("BatteryType: ") + map_BATTERY_TYPE[sys_host::BatteryType.GetValue()].c_str());
      SerialBT.println(String("ComPortType: ") + map_COMPORT_TYPE[sys_host::ComPortType.GetValue()].c_str());
      SerialBT.println(String("BatteryNum: ") + sys_host::BatteryNum.GetValue());
      SerialBT.println(String("SerialNum: ") + sys_host::SerialNum.GetValue().c_str());
      SerialBT.println("==================================");
    }
  }

  // Temporary -->
  if (sys_gui::StrikeNum.GetValue() < 3) {
    if (sys_gui::StrikeState.GetValue()) {
      sys_gui::StrikeNum.SetValue(sys_gui::StrikeNum.GetValue() + 1);

      switch (sys_gui::StrikeNum.GetValue()) {
        case 0:
          sys_gui::TimeCycle.SetValue(TIMECYCLE_0);
          break;
        case 1:
          sys_gui::TimeCycle.SetValue(TIMECYCLE_1);
          break;
        case 2:
          sys_gui::TimeCycle.SetValue(TIMECYCLE_2);
          break;
        default:
          break;
      }

      sys_gui::StrikeState.SetValue(false);
    }
  }
  // Temporary <--
}

void setup() {
  // Bluetooth serial init
  SerialBT.begin("ESP32-BT-Wires-Module");

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

  // Temporary -->
  InitCDataFromFakeTimer();
  // Temporary <--

  // Custom init
  Init();

  pinMode(BL_PIN, OUTPUT);
  analogWrite(BL_PIN, sys_gui::Brightness.GetValue());
}

void loop() {
  lv_task_handler();
  AutoUpdate();
  DataProcess();
  UpdateAll();
  lv_tick_inc(10);
  delay(10);
}
