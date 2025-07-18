#include <Arduino.h>
#include "OpenKNX.h"
#include "FileTransferModule.h"
#include "UsbExchangeModule.h"
#include "FunctionBlocksModule.h"
#include "SmartHomeBridgeModule.h"
#include "TouchDisplayModule.h"
#include "Logic.h"
#include "SensorModule.h"
#include "SensorDevices.h"
#include "lv_xiao_round_screen.h"

bool core1_separate_stack = true;

bool touchIsPressed()
{
    return chsc6x_is_pressed();
}

void displayInit()
{
    lv_xiao_disp_init();
}

void touchInit()
{
    lv_xiao_touch_init();
}

void backgroundLight(bool on)
{
    digitalWrite(XIAO_BL, on ? HIGH : LOW);
}

void setup()
{
    int workaroundDmaChannel = dma_claim_unused_channel(true);
    const uint8_t firmwareRevision = 1;
    openknx.init(firmwareRevision);
    openknx.addModule(9, openknxFileTransferModule);
    openknx.addModule(8, openknxUsbExchangeModule);
    openknx.addModule(7, openknxSmartHomeBridgeModule);
    openknx.addModule(10, openknxTouchDisplayModule);
    openknx.addModule(1, openknxLogic);
    openknx.addModule(2, openknxFunctionBlocksModule);
    openknx.addModule(3, openknxSensorDevicesModule); // SensorDevices must be before SensorModule, because SensorModule uses SensorDevices
    openknx.addModule(4, openknxSensorModule);
    openknx.setup();
    dma_channel_unclaim(workaroundDmaChannel);
}

void loop()
{
    openknx.loop();
}

#ifdef OPENKNX_DUALCORE
void setup1()
{
    openknx.setup1();
}

void loop1()
{
    openknx.loop1();
}
#endif