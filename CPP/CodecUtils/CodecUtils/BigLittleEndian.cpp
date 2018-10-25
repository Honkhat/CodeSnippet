#include "BigLittleEndian.h"
#include <iostream>

CBigLittleEndian::CBigLittleEndian(void)
{
}


CBigLittleEndian::~CBigLittleEndian(void)
{
}

bool CBigLittleEndian::IsCurrentCompilerLittleEndian()
{
	short iTest = 0x1122;
	//char bHigh = iTest >> 8;
	//char bLow = iTest & 0x00ff;
	//return (0x22 == (iTest>>8));//WRONG!结果一定是0x11.

	//位操作是逻辑位移操作,而非物理位移操作, 物理存储对逻辑操作是透明的.
	//Big/Little Endian的对象是数值, 与字符串的存储无关.

	static union { char c[4]; unsigned long l; }endian_test = { { 'l', '?', '?', 'b' } };
	char ch = (char)endian_test.l;//'l':little endian;

	return (0x22 == ((char*)&iTest)[0]);
}

//物理存储和逻辑值存在映射关系, 所以改变了逻辑值, 就改变了物理存储.
unsigned short CBigLittleEndian::SwapEndian16(unsigned short num)
{
	return (num >> 8) | (num << 8);
}

unsigned int CBigLittleEndian::SwapEndian32(unsigned int num)
{
	return (num >> 24) | ((num & 0x00ff0000) >> 8) | ((num & 0x0000ff00) << 8) | (num << 24);
}

void CBigLittleEndian::Test()
{
	//Short, Big Endian --> Little Endian;


	//ntohs ntohl VERIFY!

	//Short, Little Endian --> Big Endian;

	//Int, 
}