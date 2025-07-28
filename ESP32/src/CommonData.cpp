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
    CData<std::tuple<uint16_t, uint16_t, uint16_t>> EndlessTimeClock;
    CData<uint8_t> StrikeNum;
    CData<uint16_t> TimeCycle;
    CData<bool> StrikeState;
    CData<JsonDocument> JsonResponse;
    CData<bool> ModuleStatus;
}

namespace sys_gui
{
    CData<uint8_t> SuccessState;
    CData<uint8_t> Brightness;
    CData<bool> IsStarted;
    CData<std::unordered_map<std::string, MODULE_STATUS>> ModuleStatusMap;
}
#pragma endregion

// Allow modification
#pragma region Custom_data
CData<int8_t> CurrentSecond;
CData<COUNTER_TYPE> CounterType;
#pragma endregion

// Add auto reset state for custom data only
void UpdateAll()
{
    sys_gui::Brightness.ResetState();
    sys_gui::SuccessState.ResetState();
    CurrentSecond.ResetState();
    CounterType.ResetState();
}
