#pragma once

class CBigLittleEndian
{
public:
	CBigLittleEndian(void);
	~CBigLittleEndian(void);

	static bool IsCurrentCompilerLittleEndian();
	static unsigned short SwapEndian16(unsigned short num);
	static unsigned int SwapEndian32(unsigned int num);

	//test methods;
	static void Test();
};

