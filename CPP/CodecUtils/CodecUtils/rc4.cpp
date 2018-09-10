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

	//初始化S Box;
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

	//1.2 RPGA--伪随机生成算法--利用上面重新排列的S盒来产生任意长度的密钥流;
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
		unsigned char* keySchedul = GetKeyScheduleBuffer(plaintextsize);//生成的密钥流;
		unsigned char* ciphertext = GetResultBuffer(plaintextsize);//明文 or 密文;

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

	//密钥流按需扩容;
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
		if(sp < 1)//空文件判断!
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
		//out_data所占用的内存是ANYMACRO_RC4对象内部管理的,外部不必care;
		
		return true;
	}

	//加密和解密的文件保持同名;
	bool ANYMACRO_RC4::encrypt(const char* srcFile, const char* szKey)
	{
		if(!srcFile || strlen(srcFile)<1)
			return false;

		bool bRet = false;
		std::string sTmp = srcFile;
		sTmp += "_tmp";
		if(encrypt(srcFile, sTmp.c_str(), szKey))
		{
			//刪除源文件;
			remove(srcFile);
			//重命名加密/解密后的文件;
			rename(sTmp.c_str(), srcFile);

			bRet = true;
		}
		return bRet;
	}

	//==================================================================================================
	// RC4
	//==================================================================================================
	RC4::RC4():m_S(nullptr)
	{
		m_S = new unsigned char[256];
	}

	RC4::~RC4()
	{
		if(m_S)
			delete m_S;
	}

}
