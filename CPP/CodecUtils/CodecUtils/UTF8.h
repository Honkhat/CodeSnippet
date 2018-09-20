#pragma once

/*
	@Date: 2018/09/13 09:39;
	@Author: jian.he;
	@Mail: worksdata@163.com;
	@Purpose: UTF-8 Encryption/Decryption Algorithm Implementation;
*/


namespace CodecUtils
{
class CUTF8
{
public:
	CUTF8(void);
	~CUTF8(void);

	static bool IsTextUtf8(const char* szText);
};
}
