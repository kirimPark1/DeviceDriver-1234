#include "DeviceDriver.h"
#include <exception>

class ReadFailException : public std::exception
{};
class WriteFailException : public std::exception
{};
DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int firstReadTryValue = (int)(m_hardware->read(address));
    for (int tryCount = 2; tryCount <= TotalReadTryCount; tryCount++)
    {
        int nextReadTryValue = (int)(m_hardware->read(address));
	    if (firstReadTryValue == nextReadTryValue) continue;
        throw ReadFailException();
    }
    return firstReadTryValue;
}

void DeviceDriver::write(long address, int data)
{
    int readAddressForWrite = (int)(m_hardware->read(address));
    if (readAddressForWrite == 0xFF) throw WriteFailException();
    m_hardware->write(address, (unsigned char)data);
}