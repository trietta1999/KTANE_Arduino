/**
 * @brief Common data
 */

#include "CommonData.h"

 /* TODO: Declare shared data for the system
          Do not use "extern"
 */

 // Do not delete or rename
#pragma region System_data
namespace sys_host {
    CData<LABEL_INDICATOR> LabelIndicator;
    CData<BATTERY_TYPE> BatteryType;
    CData<COMPORT_TYPE> ComPortType;
    CData<std::string> SerialNum;
    CData<uint8_t> BatteryNum;
    CData<uint32_t> RandomSeed;
    CData<std::pair<uint8_t, uint8_t>> TimeClock;
}

namespace sys_gui
{
    CData<uint8_t> SuccessState;
    CData<uint8_t> StrikeNum;
    CData<uint16_t> TimeCycle;
    CData<bool> StrikeState;
    CData<uint8_t> Brightness;
}
#pragma endregion

// Allow modification
#pragma region Custom_data
CData<COLOR> ButtonColor;
CData<std::string> ButtonLabel;
CData<COLOR> StripColor;
CData<std::tuple<uint32_t, uint32_t, uint32_t>> CorrectEvent;
CData<std::tuple<uint32_t, uint32_t, uint32_t>> TempEvent;
#pragma endregion

// Add auto reset state for custom data only
void UpdateAll()
{
    sys_gui::Brightness.ResetState();
    ButtonColor.ResetState();
    ButtonLabel.ResetState();
    StripColor.ResetState();
    CorrectEvent.ResetState();
    TempEvent.ResetState();
}
