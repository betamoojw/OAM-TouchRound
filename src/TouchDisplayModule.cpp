#include <TouchDisplayModule.h>
#include <Arduino.h>
#include <ui.h>
#include "lv_xiao_round_screen.h"

const std::string TouchDisplayModule::name()
{
    return "TouchRound";
}

const std::string TouchDisplayModule::version()
{
    return MAIN_Version;
}

void TouchDisplayModule::setup(bool configured)
{
}
void TouchDisplayModule::setup1(bool configured)
{
    TouchDisplayModule::doorState = DoorState::UNDEFINED;
    TouchDisplayModule::displayOn = true;
    TouchDisplayModule::lastPressed = 0;

    lv_log_register_print_cb(lv_log);

    lv_init();

    lv_xiao_disp_init();
    lv_xiao_touch_init();

    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Switch_screen_init();
    ui_Dimm_screen_init();
    ui_Color_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);

    lv_obj_add_event_cb(ui_Switch, handleGesture, LV_EVENT_GESTURE, NULL);
    lv_obj_add_event_cb(ui_Dimm, handleGesture, LV_EVENT_GESTURE, NULL);
    lv_obj_add_event_cb(ui_Color, handleGesture, LV_EVENT_GESTURE, NULL);
    lv_obj_add_event_cb(ui_DimmValue, handleValues, LV_EVENT_ALL, NULL);

    _ui_flag_modify(ui_DimmValue, LV_OBJ_FLAG_GESTURE_BUBBLE, _UI_MODIFY_FLAG_REMOVE);
    _ui_flag_modify(ui_Color, LV_OBJ_FLAG_GESTURE_BUBBLE, _UI_MODIFY_FLAG_REMOVE);
    _ui_flag_modify(ui_Dimm, LV_OBJ_FLAG_GESTURE_BUBBLE, _UI_MODIFY_FLAG_REMOVE);
    _ui_flag_modify(ui_Switch, LV_OBJ_FLAG_GESTURE_BUBBLE, _UI_MODIFY_FLAG_REMOVE);

    screenTypes[0] = ui_Switch;
    screenTypes[1] = ui_Dimm;
    screenTypes[2] = ui_Color;
    screenTypes[3] = ui_Color;
    screenLabels[0] = ui_Label1;
    screenLabels[1] = ui_LabelName;
    screenLabels[2] = ui_Label2;
    screenLabels[3] = ui_Label1;

    bool flag = false;
    if (configured)
    {
#ifdef USE_OPENKNXPRODUCER
        uint16_t channelCount = ParamTCH_VisibleChannels;
#else
        uint16_t channelCount = 2;
#endif

        for (uint16_t i = 0; i < channelCount; i++)
        {
            if (checkPageActive(i))
            {
                flag = true;
                loadPage(i);
                currentScreen = screenTypes[getPageType(i)];
                TouchDisplayModule::currentScreenIndex = i;
                break;
            }
        }
    }

    if (!flag)
    {
        logErrorP("No start Page found");
        ui_Message_screen_init();
        lv_disp_load_scr(ui_Message);
        TouchDisplayModule::currentScreenIndex = 255;
    }
}

void TouchDisplayModule::lv_log(const char *buf)
{
    //     logDebug("lvgl", buf);
}

void TouchDisplayModule::handleValues(lv_event_t *event)
{
    TouchDisplayModule::resetDisplayTimeout();
    switch (event->code)
    {
    case LV_EVENT_PRESSED:
    {
        logDebug("Display", "Pressed");
        break;
    }

    case LV_EVENT_RELEASED:
    {
        TouchDisplayModule::isChangingValue = false;
        logDebug("Display", "Released %i", TouchDisplayModule::last2Value);
        lv_arc_set_value(ui_Dimm, TouchDisplayModule::last2Value);
        break;
    }

    case LV_EVENT_VALUE_CHANGED:
    {
        uint16_t value = lv_arc_get_value(ui_DimmValue);
        if (!TouchDisplayModule::isChangingValue)
        {
            TouchDisplayModule::last2Value = value;
        }
        TouchDisplayModule::isChangingValue = true;
        TouchDisplayModule::last2Value = TouchDisplayModule::lastValue;
        TouchDisplayModule::lastValue = value;
        break;
    }
    }
}

void TouchDisplayModule::resetDisplayTimeout()
{
    TouchDisplayModule::lastPressed = millis();
    if (!TouchDisplayModule::displayOn)
    {
        logDebug("Display", "Turn display on.");
        TouchDisplayModule::displayOn = true;
        digitalWrite(XIAO_BL, HIGH);
    }
}

void TouchDisplayModule::handleGesture(lv_event_t *event)
{
    TouchDisplayModule::resetDisplayTimeout();

    if (TouchDisplayModule::isChangingValue)
    {
        logDebug("Display", "ignore gesture");
        return;
    }

    int oldIndex = TouchDisplayModule::currentScreenIndex;
    if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT)
    {
        lv_indev_wait_release(lv_indev_get_act());
        do
        {
            TouchDisplayModule::currentScreenIndex++;
            if (TouchDisplayModule::currentScreenIndex >= VISU_MAX_PAGE)
                TouchDisplayModule::currentScreenIndex = 0;
        } while (!checkPageActive(TouchDisplayModule::currentScreenIndex));
    }
    else if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT)
    {
        lv_indev_wait_release(lv_indev_get_act());
        do
        {
            TouchDisplayModule::currentScreenIndex--;
            if (TouchDisplayModule::currentScreenIndex < 0)
                TouchDisplayModule::currentScreenIndex = VISU_MAX_PAGE - 1;
        } while (!checkPageActive(TouchDisplayModule::currentScreenIndex));
    }
    else
    {
        return;
    }

    if (oldIndex == TouchDisplayModule::currentScreenIndex)
        return;

    loadPage(TouchDisplayModule::currentScreenIndex);
}

void TouchDisplayModule::loadPage(int channel)
{
    logDebug("Display", "Loading Page %i", channel);
    logDebug("Display", "type: %i", getPageType(TouchDisplayModule::currentScreenIndex));
    TouchDisplayModule::currentScreen = screenTypes[getPageType(TouchDisplayModule::currentScreenIndex)];
    setTextForChannel(TouchDisplayModule::currentScreenIndex);
    lv_scr_load(currentScreen);
    // lv_scr_load_anim(currentScreen, LV_SCR_LOAD_ANIM_FADE_IN, 500, 0, false);
    //_ui_screen_change(&currentScreen, LV_SCR_LOAD_ANIM_FADE_IN, 500, 0, screenInits[TouchDisplayModule::currentScreenIndex]);
}

bool TouchDisplayModule::checkPageActive(int channel)
{
#ifdef USE_OPENKNXPRODUCER
    return ((knx.paramByte(TCH_ChannelActive + TCH_ParamBlockOffset + channel * TCH_ParamBlockSize) & TCH_ChannelActiveMask) >> TCH_ChannelActiveShift) > 0;
#else
    return ParamPAGE_typeIndex(channel) != 0;
#endif
}

uint8_t TouchDisplayModule::getPageType(int channel)
{
#ifdef USE_OPENKNXPRODUCER
    return (knx.paramByte(TCH_ChannelPageType + TCH_ParamBlockOffset + channel * TCH_ParamBlockSize) & TCH_ChannelPageTypeMask) >> TCH_ChannelPageTypeShift;
#else
    return ParamPAGE_typeIndex(TouchDisplayModule::currentScreenIndex) - 1;
#endif
}

void TouchDisplayModule::setTextForChannel(int channel)
{
#ifdef USE_OPENKNXPRODUCER
    char *display = (char *)knx.paramData(TCH_ChannelDisplayName + TCH_ParamBlockOffset + channel * TCH_ParamBlockSize);
#else
    char *display = (char *)ParamPAGE_displayIndex(channel);
#endif

    println(display);
    lv_label_set_text(screenLabels[channel], display);
}

void TouchDisplayModule::loop(bool configured)
{
}
void TouchDisplayModule::loop1(bool configured)
{
    lv_timer_handler(); // let the GUI do its work

    // if (TouchDisplayModule::currentScreenIndex != 255 && TouchDisplayModule::displayOn && (millis() - TouchDisplayModule::lastPressed > DISPLAY_SLEEP_DELAY)) {
    //     logDebugP("Turn display off.");
    //     TouchDisplayModule::displayOn = false;
    //     digitalWrite(XIAO_BL, LOW);
    // }
}

void TouchDisplayModule::processInputKo(GroupObject &iKo)
{
}

void TouchDisplayModule::processAfterStartupDelay()
{
}

// void TouchDisplayModule::writeFlash()
// {
//     for (size_t i = 0; i < flashSize(); i++)
//     {
//         //openknx.flash.writeByte(0xd0 + i);
//     }
// }

// void TouchDisplayModule::readFlash(const uint8_t* data, const uint16_t size)
// {
//     // printHEX("RESTORE:", data,  len);
// }

// uint16_t TouchDisplayModule::flashSize()
// {
//     return 10;
// }

TouchDisplayModule openknxTouchDisplayModule;