#include <iostream>
#include "DeviceDriver.h"

using namespace std;
const int START_ADDR = 0x00;
const int END_ADDR = 0x04;
class Application
{
public:
	Application(DeviceDriver* driver) :m_driver(driver) {}
	void ReadAndPrint(long startAddr, long endAddr)
	{
		for (long address = startAddr; address <= endAddr; address++)
		{
			cout << "address : " << address << " : " << m_driver->read(address) << endl;
		}
	}

	void WriteAll(int value)
	{
		for (long address = START_ADDR; address <= END_ADDR; address++)
		{
			m_driver->write(address, value);
		}
	}
private:
	DeviceDriver* m_driver;
};
