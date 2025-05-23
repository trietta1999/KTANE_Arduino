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
CData<uint16_t> Button2Value;
CData<int32_t> SliderValue;
CData<int32_t> ArcValue;
CData<uint16_t> CheckboxValue;
CData<std::string> DropdownValue;
CData<uint16_t> SwitchValue;
CData<std::string> RollerValue;
#pragma endregion

// Add auto reset state for custom data only
void UpdateAll()
{
    Button2Value.ResetState();
    SliderValue.ResetState();
    ArcValue.ResetState();
    CheckboxValue.ResetState();
    DropdownValue.ResetState();
    SwitchValue.ResetState();
    RollerValue.ResetState();
    sys_gui::Brightness.ResetState();
}
