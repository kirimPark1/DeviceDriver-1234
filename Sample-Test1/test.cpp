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

TEST(TestCaseName, TestRead) {
	//대역
	FlashMemoryDeviceMock flashMemoryMock;

	//스터빙 or behavior 검증
	EXPECT_CALL(flashMemoryMock, read(_)).Times(5);

	DeviceDriver testingDeviceDriver(&flashMemoryMock);
	testingDeviceDriver.read(0xA);
}

TEST(TestCaseName, TestReadException) {
	//대역
	FlashMemoryDeviceMock flashMemoryMock;

	//스터빙 4번은 잘 읽히는데 5번째 다른값이 읽힐때
	EXPECT_CALL(flashMemoryMock, read(0x2))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x3));

	DeviceDriver testingDeviceDriver(&flashMemoryMock);
	EXPECT_THROW(testingDeviceDriver.read(0x2), ReadFailException);
}
