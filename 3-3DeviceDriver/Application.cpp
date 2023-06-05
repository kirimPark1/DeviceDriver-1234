#include <iostream>
#include "DeviceDriver.h"

using namespace std;
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

	}
private:
	DeviceDriver* m_driver;
};
