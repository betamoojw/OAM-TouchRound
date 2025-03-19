#include "OpenKNX.h"
#include "Cell.h"
#include "EmptyCell.h"
#include "CellParameterDefines.h"
#include "JumpCell.h"
#include "DateTimeCell.h"
#include "DeactivatedCell.h"
#include "DeviceMainFunctionCell.h"
#include "SmartHomeBridgeModule.h"

const std::string Cell::logPrefix()
{
    return _name;
}

void Cell::init(uint8_t channelIndex, uint8_t cellIndex, CellObject &cellObject)
{
    _name = cellType();
    _name += "Cell";
    _name += std::to_string(channelIndex + 1);
    _name += "/";
    _name += std::to_string(cellIndex + 1);
    _channelIndex = channelIndex;
    _cellIndex = cellIndex;
    _cellObject = &cellObject;
    setup();
}

Cell *Cell::createCell(uint8_t channelIndex, uint8_t cellIndex, CellObject &cellObject)
{
    uint8_t _channelIndex = channelIndex; // Used in parameter macros
    uint8_t _cellIndex = cellIndex;       // Used in parameter macros
    Cell *result = nullptr;

    // <Enumeration Text="Leer" Value="0" Id="%ENID%" />
    // <Enumeration Text="Gerät" Value="1" Id="%ENID%" />
    // <Enumeration Text="Sprung zu Seite" Value="2" Id="%ENID%" />
    // <Enumeration Text="Zeit" Value="3" Id="%ENID%" />
    // <Enumeration Text="Datum" Value="4" Id="%ENID%" />
    switch (ParamTCH_ChannelTCHCellType1)
    {
    case 0:
        result = new EmptyCell();
        break;
    case 1:
    {
        uint8_t deviceIndex = ParamTCH_ChannelDeviceSelection1 - 1;
        auto device = openknxSmartHomeBridgeModule.getChannel(deviceIndex);
        if (device == nullptr)
        {
            result = new DeactivatedCell();
        }
        else
        {
            auto deviceCell = new DeviceMainFunctionCell();
            deviceCell->init(device);
            result = deviceCell;
        }
    }
    break;
    case 2: // Jump cell
        result = new JumpCell();
        break;
    case 3:
        result = new DateTimeCell(false, true);
        break;
    case 4:
        result = new DateTimeCell(true, false);
        break;
    }
    result->init(channelIndex, cellIndex, cellObject);
    return result;
}