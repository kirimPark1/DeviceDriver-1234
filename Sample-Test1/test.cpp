#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../3-3DeviceDriver/DeviceDriver.cpp"
#include "../3-3DeviceDriver/Application.cpp"

using namespace std;
using namespace testing;

class FlashMemoryDeviceMock : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};
class DeviceDriverTest : public testing::Test
{
public:
	FlashMemoryDeviceMock flashMemoryMock;
	DeviceDriver testingDeviceDriver{ &flashMemoryMock };
};
class ApplicationTest : public testing::Test
{
public:
	FlashMemoryDeviceMock flashMemoryMock;
	DeviceDriver testingDeviceDriver{ &flashMemoryMock };
	Application testingApplicaion{&testingDeviceDriver};
};
TEST_F(DeviceDriverTest, TestRead) {
	//스터빙 or behavior 검증
	EXPECT_CALL(flashMemoryMock, read(_)).Times(5);
	testingDeviceDriver.read(0xA);
}

TEST_F(DeviceDriverTest, TestReadException) {
	//스터빙 4번은 잘 읽히는데 5번째 다른값이 읽힐때
	EXPECT_CALL(flashMemoryMock, read(0x2))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x3));

	EXPECT_THROW(testingDeviceDriver.read(0x2), ReadFailException);
}

TEST_F(DeviceDriverTest, TestReadSuccess) {
	EXPECT_CALL(flashMemoryMock, read(0x2))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7));

	EXPECT_THAT(testingDeviceDriver.read(0x2), Eq(7));
}

TEST_F(DeviceDriverTest, TestWrite) {
	//지워져 있는지 확인하기위한 read
	EXPECT_CALL(flashMemoryMock, read(0x2)).Times(1);
	testingDeviceDriver.write(0x2, 1234);
}

TEST_F(DeviceDriverTest, TestWriteException) {
	//지워져 있는지 확인하기위한 read
	EXPECT_CALL(flashMemoryMock, read(0x2))
		.WillOnce(Return(ALREADY_WRITTEN));
	EXPECT_THROW(testingDeviceDriver.write(0x2, 1234), WriteFailException);
}

TEST_F(ApplicationTest, TestReadAndPrint)
{
	EXPECT_CALL(flashMemoryMock, read(_)).Times(25);
	testingApplicaion.ReadAndPrint(0x00, 0x04);
}
