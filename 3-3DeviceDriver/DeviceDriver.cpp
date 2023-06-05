#include "DeviceDriver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int readValueFromAddress = (int)(m_hardware->read(address));
    for (int i = 1; i < 5; i++)
    {
	    if (readValueFromAddress != 
            (int)(m_hardware->read(address)))
	    {
            return 0;
	    }
    }
    return readValueFromAddress;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}