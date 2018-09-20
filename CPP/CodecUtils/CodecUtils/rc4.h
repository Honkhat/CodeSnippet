#pragma once
#include <string>


/*
	@Date: 2018/09/07 11:35;
	@Author: jian.he;
	@Mail: worksdata@163.com;
	@Purpose: Simple,Fast Encryption/Decryption Algorithm Implementation;
*/


namespace CodecUtils
{
	class ANYMACRO_RC4
	{
	public:
		ANYMACRO_RC4();
		~ANYMACRO_RC4();
		
		void SetKey(const char* szKey);
		unsigned char* encrypt(const char* plaintext, int plaintextsize);//结果的长度与输入的字节序列的长度一致;
		bool encrypt(const char* srcFile, const char* dstFile, const char* szKey = nullptr);//文件加密,内部使用流式文件读写;
		bool encrypt(const char* srcFile, const char* szKey = nullptr);//文件加密,内部使用流式文件读写;
	private:
		static void ksa(unsigned char* s, const unsigned char* szKey, int iKeySize);
		static void rpga(unsigned char* s, unsigned char* keySchedule, int plaintextLength);
		static void swap(unsigned char a[], int i, int j);

		unsigned char* GetKeyScheduleBuffer(int iBuffSize);
		unsigned char* GetResultBuffer(int iBuffSize);

		unsigned char* S;
		unsigned char* m_pKeySchedule;//密钥流, 与明文/密文的长度保持一致;
		int m_iKeyScheduleSize;
		unsigned char* m_pResult;//结果序列;
		int m_iResultSize;
		std::string m_sKeyRc4;
	};

	/*
		RC4是在ANYMACRO_RC4的基础上做了优化:
		1.SBOX只初始化一次;
		2.
	*/

	class RC4
	{
	public:
		RC4();
		~RC4();

		//接口设计目标: 外部只需调用一个方法即可完成任务;
		bool Crypt(unsigned char* data, int datalen, const char* key, int keylen);//字符串加解密;
		bool Crypt(unsigned char* srcData, unsigned char*& dstData, int datalen, const char* key, int keylen);//字符串加解密;
		bool Crypt(const char* file, const char* key, int keylen);//文件加解密;
		bool Crypt(const char* srcFile, const char* dstFile, const char* key, int keylen);//文件加解密;

	private:
		void swap(unsigned char& a, unsigned char& b);
		void rc4_init(unsigned char*s, unsigned char* szKey, unsigned long iKeyLen);
		void rc4_crypt(unsigned char*s, unsigned char*Data, unsigned long Len);
		void copy_sbox();
		unsigned char* GetResultBuffer(int iBuffSize);

		unsigned char* m_S;//不可修改;
		unsigned char* m_SCopy;//可修改;
		unsigned char* m_pResult;//结果序列;
		int m_iResultSize;
		std::string m_sKeyRc4;
	};
}