#pragma once
#include <string>


/*
	@Date: 2018/09/07 11:35;
	@Author: jian.he;
	@Mail: worksdata@163.com;
	@Purpose: Simple,Fast Encryption/Decryption Algorithm;
*/


namespace CodecUtils
{
	class ANYMACRO_RC4
	{
	public:
		ANYMACRO_RC4();
		~ANYMACRO_RC4();
		
		void SetKey(const char* szKey);
		unsigned char* encrypt(const char* plaintext, int plaintextsize);//����ĳ�����������ֽ����еĳ���һ��;
		bool encrypt(const char* srcFile, const char* dstFile, const char* szKey = nullptr);//�ļ�����,�ڲ�ʹ����ʽ�ļ���д;
		bool encrypt(const char* srcFile, const char* szKey = nullptr);//�ļ�����,�ڲ�ʹ����ʽ�ļ���д;
	private:
		static void ksa(unsigned char* s, const unsigned char* szKey, int iKeySize);
		static void rpga(unsigned char* s, unsigned char* keySchedule, int plaintextLength);
		static void swap(unsigned char a[], int i, int j);

		unsigned char* GetKeyScheduleBuffer(int iBuffSize);
		unsigned char* GetResultBuffer(int iBuffSize);

		unsigned char* S;
		unsigned char* m_pKeySchedule;//��Կ��, ������/���ĵĳ��ȱ���һ��;
		int m_iKeyScheduleSize;
		unsigned char* m_pResult;//�������;
		int m_iResultSize;
		std::string m_sKeyRc4;
	};

	/*
		RC4����ANYMACRO_RC4�Ļ����������Ż�:
		1.SBOXֻ��ʼ��һ��;
		2.
	*/

	class RC4
	{
	public:
		RC4();
		~RC4();


	private:
		unsigned char* m_S;
	};
}