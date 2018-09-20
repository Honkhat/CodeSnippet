#include "rc4.h"
#include <io.h>
#include <fstream>

const int DEF_CHUNK_SIZE = 4096;//4K Bytes;

namespace CodecUtils
{
	ANYMACRO_RC4::~ANYMACRO_RC4()
	{
		if(S)
			delete S;
		if(m_pKeySchedule)
			delete m_pKeySchedule;
		if(m_pResult)
			delete m_pResult;
	}

	ANYMACRO_RC4::ANYMACRO_RC4():m_sKeyRc4("anymacro"),m_pKeySchedule(nullptr),m_iKeyScheduleSize(0),m_pResult(nullptr),m_iResultSize(0)
	{
		S = new unsigned char[256];
	}

	void ANYMACRO_RC4::SetKey(const char* szKey)
	{
		m_sKeyRc4 = szKey;//no check, set anything you like;
	}

	//��ʼ��S Box;
	void ANYMACRO_RC4::ksa(unsigned char* s, const unsigned char* szKey, int iKeySize)
	{
		for (int i = 0; i < 256; ++i)
			s[i] = i;

		int j = 0;
		for (int i = 0; i < 256; ++i)
		{
			j = (j + s[i] + szKey[i%iKeySize]) % 256;
			swap(s, i, j);
		}
	}

	//1.2 RPGA--α��������㷨--���������������е�S�����������ⳤ�ȵ���Կ��;
	void ANYMACRO_RC4::rpga(unsigned char* s, unsigned char* keySchedule, int plaintextLength)
	{
		int i = 0, j = 0;
		for (int k = 0; k < plaintextLength; ++k)
		{
			i = (i + 1) % 256;
			j = (j + s[i]) % 256;
			swap(s, i, j);
			keySchedule[k] = s[(s[i] + s[j]) % 256];
		}
	}

	unsigned char* ANYMACRO_RC4::encrypt(const char* plaintext, int plaintextsize)
	{
		unsigned char* keySchedul = GetKeyScheduleBuffer(plaintextsize);//���ɵ���Կ��;
		unsigned char* ciphertext = GetResultBuffer(plaintextsize);//���� or ����;

		ksa(S, (const unsigned char*)m_sKeyRc4.c_str(), m_sKeyRc4.length());
		rpga(S, keySchedul, plaintextsize);

		for (int i = 0; i < plaintextsize; ++i)
			ciphertext[i] = plaintext[i] ^ keySchedul[i];

		return ciphertext;
	}

	void ANYMACRO_RC4::swap(unsigned char a[], int i, int j)
	{
		unsigned char bTmp = a[i];
		a[i] = a[j];
		a[j] = bTmp;
	}

	//��Կ����������;
	unsigned char* ANYMACRO_RC4::GetKeyScheduleBuffer(int iBuffSize)
	{
		if(iBuffSize > m_iKeyScheduleSize)
		{
			if(m_pKeySchedule)
				delete m_pKeySchedule;
			m_pKeySchedule = new unsigned char[iBuffSize];
			memset(m_pKeySchedule, 0, iBuffSize);
			m_iKeyScheduleSize = iBuffSize;
		}
		return m_pKeySchedule;
	}

	unsigned char* ANYMACRO_RC4::GetResultBuffer(int iBuffSize)
	{
		if(iBuffSize > m_iResultSize)
		{
			if(m_pResult)
				delete m_pResult;
			m_pResult = new unsigned char[iBuffSize];
			memset(m_pResult, 0, iBuffSize);
			m_iResultSize = iBuffSize;
		}
		return m_pResult;
	}

	bool ANYMACRO_RC4::encrypt(const char* srcFile, const char* dstFile, const char* szKey)
	{
		if(!srcFile || (strlen(srcFile)<1) || !dstFile || (strlen(dstFile)<1))
			return false;

		//check file existence;
		if(0 != _access(srcFile, 0))
			return false;
		if(0 == _access(dstFile, 0))
			remove(dstFile);

		//check src file size;
		std::ifstream fIn(srcFile, std::ios::binary);
		std::ofstream fOut(dstFile, std::ios::binary);

		if(!fIn || !fOut) //not exists or create failed;
			return false;

		fIn.seekg(0, std::ios_base::end);
		std::streampos sp = fIn.tellg();
		if(sp < 1)//���ļ��ж�!
		{
			fIn.close();
			fOut.close();
			return false;
		}
		fIn.seekg(0, std::ios_base::beg);

		char *in_data  = new char[DEF_CHUNK_SIZE + 1];

		try
		{
			if(szKey && strlen(szKey) > 0)
				SetKey(szKey);

			while(!fIn.eof())
			{
				fIn.read(in_data, DEF_CHUNK_SIZE);
				const int iActualSize = fIn.gcount();
				unsigned char *out_data = encrypt(in_data, iActualSize);
				fOut.write((const char*)out_data, iActualSize);
			}
		}
		catch(std::exception& e)
		{
			
		}

		fOut.close();
		fIn.close();
		if(in_data)
			delete in_data;
		//out_data��ռ�õ��ڴ���ANYMACRO_RC4�����ڲ������,�ⲿ����care;
		
		return true;
	}

	//���ܺͽ��ܵ��ļ�����ͬ��;
	bool ANYMACRO_RC4::encrypt(const char* srcFile, const char* szKey)
	{
		if(!srcFile || strlen(srcFile)<1)
			return false;

		bool bRet = false;
		std::string sTmp = srcFile;
		sTmp += "_tmp";
		if(encrypt(srcFile, sTmp.c_str(), szKey))
		{
			//�h��Դ�ļ�;
			remove(srcFile);
			//����������/���ܺ���ļ�;
			rename(sTmp.c_str(), srcFile);

			bRet = true;
		}
		return bRet;
	}

	//==================================================================================================
	// RC4--�ο��ٶȰٿ�
	//==================================================================================================
	const int RC4_KEY_MAXLEN = 256;
	RC4::RC4():m_pResult(nullptr),m_iResultSize(0)
	{
		m_S = new unsigned char[RC4_KEY_MAXLEN];
		m_SCopy = new unsigned char[RC4_KEY_MAXLEN];
	}

	RC4::~RC4()
	{
		if(m_S)
			delete m_S;
		if(m_SCopy)
			delete m_SCopy;
		if(m_pResult)
			delete m_pResult;
	}

	/*��ʼ������--ksa�㷨*/
	void RC4::rc4_init(unsigned char*s, unsigned char*szKey, unsigned long iKeyLen)
	{
		for (int i = 0; i < 256; ++i)
			s[i] = i;

		int j = 0;
		for (int i = 0; i < 256; ++i)
		{
			j = (j + s[i] + szKey[i%iKeyLen]) % 256;
			swap(s[i], s[j]);
		}
	}

	void RC4::swap(unsigned char& a, unsigned char& b)
	{
		a = a + b;
		b = a - b;
		a = a - b;
	}

	void RC4::copy_sbox()
	{
		memcpy(m_SCopy, m_S, RC4_KEY_MAXLEN);
	}

	/*�ӽ���*/
	void RC4::rc4_crypt(unsigned char*s, unsigned char*Data, unsigned long Len)
	{
		int i = 0, j = 0, t = 0;
		unsigned long k = 0;
		for (k = 0; k < Len; ++k)
		{
			i = (i + 1) % 256;
			j = (j + s[i]) % 256;
			swap(s[i], s[j]);
			t = (s[i] + s[j]) % 256;
			Data[k] ^= s[t];
		}
	}

	unsigned char* RC4::GetResultBuffer(int iBuffSize)
	{
		if(iBuffSize > m_iResultSize)
		{
			if(m_pResult)
				delete m_pResult;
			m_pResult = new unsigned char[iBuffSize];
			memset(m_pResult, 0, iBuffSize);
			m_iResultSize = iBuffSize;
		}
		return m_pResult;
	}

	//�ַ����ӽ���:ֱ�����ַ����ϲ���;
	bool RC4::Crypt(unsigned char* data, int datalen, const char* key, int keylen)
	{
		if(!data)
			return false;

		//�Ż�:����ͬ����key,ֻ��ʼ��һ��;
		if(m_sKeyRc4.compare((char*)key) != 0)
		{
			m_sKeyRc4 = (char*)key;//����key��Ҫ��'\0'��β;
			rc4_init(m_S, (unsigned char*)key, keylen);
		}

		copy_sbox();
		rc4_crypt(m_SCopy, data, datalen);

		return true;
	}

	//�ַ����ӽ���:���޸�ԭ�ַ���;
	bool RC4::Crypt(unsigned char* srcData, unsigned char*& dstData, int datalen, const char* key, int keylen)
	{
		if(!srcData)
			return false;

		//�Ż�:����ͬ����key,ֻ��ʼ��һ��;
		if(m_sKeyRc4.compare((char*)key) != 0)
		{
			m_sKeyRc4 = (char*)key;
			rc4_init(m_S, (unsigned char*)key, keylen);
		}

		//result��RC4������������,�ⲿ�����ͷ�!
		dstData = GetResultBuffer(datalen);//�������кͽ������г�����һ����;
		memcpy(dstData, srcData, datalen);
		copy_sbox();
		rc4_crypt(m_SCopy, dstData, datalen);

		return true;
	}

	//�ļ��ӽ���:ֱ�Ӷ��ļ�����;
	bool RC4::Crypt(const char* file, const char* key, int keylen)
	{
		if(!file)
			return false;

		bool bRet = false;
		std::string sTmp = file;
		sTmp += "_tmp";
		if(Crypt(file, sTmp.c_str(), key, keylen))
		{
			//�h��Դ�ļ�;
			remove(file);
			//����������/���ܺ���ļ�;
			rename(sTmp.c_str(), file);

			bRet = true;
		}
		return bRet;
	}

	//�ļ��ӽ���:���޸�ԭ�ļ�;
	bool RC4::Crypt(const char* srcFile, const char* dstFile, const char* szKey, int iKeyLen)
	{
		if(!srcFile || (strlen(srcFile)<1) || !dstFile || (strlen(dstFile)<1))
			return false;

		//check file existence;
		if(0 != _access(srcFile, 0))
			return false;
		if(0 == _access(dstFile, 0))
			remove(dstFile);

		//check src file size;
		std::ifstream fIn(srcFile, std::ios::binary);
		std::ofstream fOut(dstFile, std::ios::binary);

		if(!fIn || !fOut) //not exists or create failed;
			return false;

		fIn.seekg(0, std::ios_base::end);
		std::streampos sp = fIn.tellg();
		if(sp < 1)//���ļ��ж�!
		{
			fIn.close();
			fOut.close();
			return false;
		}
		fIn.seekg(0, std::ios_base::beg);

		char *in_data  = new char[DEF_CHUNK_SIZE + 1];
		try
		{
			while(!fIn.eof())
			{
				fIn.read(in_data, DEF_CHUNK_SIZE);
				const int iActualSize = fIn.gcount();
				Crypt((unsigned char*)in_data, iActualSize, szKey, iKeyLen);
				fOut.write((const char*)in_data, iActualSize);
			}
		}
		catch(std::exception& e)
		{

		}

		fOut.close();
		fIn.close();
		if(in_data)
			delete in_data;

		return true;
	}
}
