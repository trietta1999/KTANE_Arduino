/**
 * @file  LibEngine.cpp
 * @brief Library engine
 */

#include <iostream>
#include <LibEngine.h>
#include <CommonDataType.h>
#include <CommonData.h>
#include <string.h>
#include <src/misc/lv_event.h>

/*
TIEU CHI:
    TIMER               → TimeClock

    Label               → LabelIndicator --> CAR/FRK/...		(LABEL_INDICATOR)
    SL PIN (1 or >1)    → BatteryNum

    #1
    MÀU SẮC CỦA NÚT 	→ ButtonColor							(COLOR)
    CAI NUT GHI ...     → ButtonLabel -- Abort/Detonate/Hold: 	(string)

    ColorBar            → ENUM_COLOR							()

    .Random cdata #1
    .LIB → Generate queue:
            queue = <eventClickOrPress, release, number>
            CData<std::tuple<uint32_t, uint32_t, uint32_t>> CorrectEvent;
            CData<std::tuple<uint32_t, uint32_t, uint32_t>> TempEvent;

            CorrectEvent = std::make_tuple(eventCode, LV_EVENT_RELEASED, 0);
                → CorrectEvent(LV_EVENT_CLICKED, LV_EVENT_RELEASED, 4)
                → CorrectEvent(LV_EVENT_LONG_PRESSED, LV_EVENT_LONG_PRESSED, )

    .std::tuple → Already created
*/


/* Start timer: RunFakeTimer(timeForButtonModule) */
void ButtonModule(lv_event_t* e)
{
    /* Get common data */
    COLOR_TYPE buttonColor = ButtonColor.GetValue();
    LABEL_INDICATOR labelIndicator = sys_host::LabelIndicator.GetValue();
    std::string buttonLabel = ButtonLabel.GetValue();
    uint8_t batteryNum = sys_host::BatteryNum.GetValue();

    /* Get button event */
    lv_event_code_t eventCode = lv_event_get_code(e);

    CorrectEvent.SetValue(std::make_tuple(eventCode, LV_EVENT_RELEASED, 0));

    /* Case 1 */
    if ((buttonColor == COLOR_TYPE::BLUE) && (buttonLabel == "ABORT"))
    {
        CheckStripColor(e);
    }
    /* Case 2 */
    else if ((batteryNum > 1) && (buttonLabel == "DETONATE"))
    {
        CorrectEvent.SetValue(std::make_tuple(LV_EVENT_CLICKED, LV_EVENT_RELEASED, 0));
    }
    /* Case 3 */
    else if ((buttonColor == COLOR_TYPE::WHITE) && (labelIndicator == LABEL_INDICATOR::CAR))
    {
        CheckStripColor(e);
    }
    /* Case 4 */
    else if ((batteryNum > 2) && (labelIndicator == LABEL_INDICATOR::FRK))
    {
        CorrectEvent.SetValue(std::make_tuple(LV_EVENT_CLICKED, LV_EVENT_RELEASED, 0));
    }
    /* Case 6 */
    else if ((buttonColor == COLOR_TYPE::RED) && (buttonLabel == "ABORT"))
    {
        CorrectEvent.SetValue(std::make_tuple(LV_EVENT_CLICKED, LV_EVENT_RELEASED, 0));
    }
    /* Case 5, case 7 */
    else
    {
        CheckStripColor(e);
    }
}

bool CheckTimerNumbers(int number)
{
    int minute = std::get<MINUTE_POS>(sys_host::TimeClock.GetValue());
    int second = std::get<SECOND_POS>(sys_host::TimeClock.GetValue());

    std::string strMinute = std::to_string(minute);
    std::string strSecond = std::to_string(second);

    if ((strMinute.find('4') != std::string::npos)
        || (strSecond.find('4') != std::string::npos)
        )
    {
        std::cout << "The number contains a '4'.\n";
        return true;
    }
    else
    {
        std::cout << "The number does not contain a '4'.\n";
        return false;
    }
}

void CheckStripColor(lv_event_t* e)
{
    COLOR_TYPE stripColor = StripColor.GetValue();

    switch (stripColor)
    {
    case COLOR_TYPE::BLUE:
    {
        /* If number '4' exists on timer -> Release button */
        CorrectEvent.SetValue(std::make_tuple(LV_EVENT_LONG_PRESSED, LV_EVENT_RELEASED, 4));
    }
        break;
    case COLOR_TYPE::YELLOW:
    {
        /* If number '4' exists on timer -> Release button */
        if (CheckTimerNumbers(5))
        {
            if (lv_event_get_code(e) == LV_EVENT_LONG_PRESSED)
            {
                CorrectEvent.SetValue(std::make_tuple(LV_EVENT_LONG_PRESSED, LV_EVENT_RELEASED, 5));
            }
        }
        break;
    }
    default:
    {
        /* If number '1' exists on timer -> Release button */
        CorrectEvent.SetValue(std::make_tuple(LV_EVENT_LONG_PRESSED, LV_EVENT_RELEASED, 1));
    }
        break;
    }

    return;
}
