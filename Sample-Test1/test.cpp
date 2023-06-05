#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../3-3DeviceDriver/DeviceDriver.h"
#include "../3-3DeviceDriver/FlashMemoryDevice.h"

class FlashMemoryDeviceMock : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(ReadTest, TestReadSuccess) {
	FlashMemoryDeviceMock flashMemoryMock;

}