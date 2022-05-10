#include "pch.h"
#include "CppUnitTest.h"
#include"C:\Users\Даниил Михайлович\source\repos\AISD_LAB2_SEM4\AISD_LAB2_SEM4\AISD_LAB2_SEM4.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const string MSG = "Never gonna give you up. Never gonna let you cry.";
const string ENCODE_MSG ="000000000100010000100100011010001010110011001110011010010000001000010011100101011010001110101011110000110000000001000100001001000110100010101100110011100111101000011110001110010101101000111111001010011100";
namespace UnitTests
{
	TEST_CLASS(Lab_3)
	{
	public:
		TEST_METHOD(Encode)
		{
			string msg = "Never gonna give you up. Never gonna let you cry.";
				Assert::AreEqual(encode(msg).data1, ENCODE_MSG);
		}
		TEST_METHOD(Uncode) {
			Assert::AreEqual(uncode(ENCODE_MSG, &encode(MSG).data2), MSG);
		}
		TEST_METHOD(encode_size_equal) {
			string encode_msg = encode(MSG).data1;
			int size = encode_msg.length();
			Assert::AreEqual(size, 204);
		}
	};
}