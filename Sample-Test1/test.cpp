#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../3-3DeviceDriver/DeviceDriver.cpp"

using namespace std;
using namespace testing;

class FlashMemoryDeviceMock : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(TestCaseName, TestReadSuccess) {
	//대역
	FlashMemoryDeviceMock flashMemoryMock;

	//스터빙 or behavior 검증
	EXPECT_CALL(flashMemoryMock, read(_)).Times(5);

	DeviceDriver testingDeviceDriver(&flashMemoryMock);
	testingDeviceDriver.read(0xA);

}