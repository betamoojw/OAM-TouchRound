#include "DateTimePage.h"
#include "../Screens/DateTimeScreen.h"

const char* DateTimePage::pageType()
{
    return "DateTime";
}

void DateTimePage::setup()
{
    updateTime(true);
    lv_disp_load_scr(DateTimeScreen::instance->screen);
}

void DateTimePage::updateTime(bool forceUpdate)
{
    auto& instance = *DateTimeScreen::instance;
    bool timeValid = openknx.time.isValid();
    if (timeValid != _lastValid)
    {
        _lastValid = timeValid;
        forceUpdate = true;
    }
    if (timeValid)
    {
        auto localTime = openknx.time.getLocalTime();
        auto time = localTime.toTime_t();
        if (time != _lastTime || forceUpdate)
        {
            lv_label_set_text(instance.weekday, dayOfWeekString(localTime.dayOfWeek));

            char buffer[50];
            sprintf(buffer, "%02d.%02d.%04d", (int)localTime.day, (int)localTime.month, (int)localTime.year);
            lv_label_set_text(instance.date, buffer);
       
            sprintf(buffer, "%02d:%02d:%02d", (int) localTime.hour, (int)localTime.minute, (int)localTime.second);
            lv_label_set_text(instance.time, buffer);
            lv_label_set_text(instance.message, "");
        }
    }
    else
    {
        if (forceUpdate)
        {
            lv_label_set_text(instance.weekday, "");
            lv_label_set_text(instance.date, "");
            lv_label_set_text(instance.time, "");
            lv_label_set_text(instance.message, "Zeit nicht vorhanden.\nBitte prüfen ob Uhrzeit/Datum\nin der ETS korrekt verbunden ist");
        }
    }
}

const char* DateTimePage::dayOfWeekString(uint8_t dayOfWeek) 
{
    switch (dayOfWeek)
    {
    case 0:
        return "Sonntag";
    case 1:
        return "Montag";
    case 2:
        return "Dienstag";
    case 3:
        return "Mittwoch";
    case 4:
        return "Donnerstag";
    case 5:
        return "Freitag";
    case 6:
        return "Samstag";
    default:
        return "";
    }
}


void DateTimePage::loop()
{
   updateTime(false);
}

std::string DateTimePage::name()
{
    return "Uhrzeit";
}

std::string DateTimePage::image()
{
    return "Clock.png";
}