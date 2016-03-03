#ifndef MSTRING_H
#define MSTRING_H

/********************************************************************
*  @
*********************************************************************
*  @brief    : �ַ�����
*  @author   : Ī����
*  @date     : 2015/03/04
*  @version  : ver 1.0
*  @filename : mstring.h
*  @note     :
*  @attention:
*  @remark   : 1. 2015/03/04 23:31 Created By Ī���� version 1.0
*********************************************************************/


/********************************************************************
*  @note     : ���ڴ˴�����ϵͳͷ�ļ�
********************************************************************/


/********************************************************************
*  @note     : ���ڴ˴������Զ���ͷ�ļ�
********************************************************************/
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
using namespace std;


//�ַ�������
#ifndef SZ_LENGTH
#define SZ_LENGTH 128
#endif

#ifndef SZ_S_LENGTH
#define SZ_S_LENGTH 64
#endif

#ifndef SZ_L_LENGTH
#define SZ_L_LENGTH 512
#endif

#ifndef SZ_8_LENGTH
#define SZ_8_LENGTH 8
#endif

#ifndef SZ_16_LENGTH
#define SZ_16_LENGTH 16
#endif

#ifndef SZ_32_LENGTH
#define SZ_32_LENGTH 32
#endif

#ifndef SZ_1024_LENGTH
#define SZ_1024_LENGTH 1024
#endif

#ifndef SZ_2048_LENGTH
#define SZ_2048_LENGTH 2048
#endif

#ifndef SZ_4096_LENGTH
#define SZ_4096_LENGTH 4096
#endif


class MString;

ostream &operator<<(ostream &,const MString& mstr);
istream &operator>>(istream &,MString& mstr);

class MString
{
public:

	//========================================================
	//���캯��
	//========================================================

	MString()
	{
		m_pszData = NULL;
		Init();
	}

	~MString()
	{
		m_iPos = 0;
		m_iLength = 0;

		if (m_pszData != NULL)
		{
			delete[] m_pszData;
			m_pszData = NULL;
		}
	}

	


	

	MString(char chData)
	{
		m_iLength = 0;
		SetData(chData);
	}

	MString::MString(const MString& mstrData)
	{
		m_pszData = NULL;
		m_iLength = 0;
		SetData(mstrData);
	}

	MString(__int64 iData)
	{
		m_pszData = NULL;
		m_iLength = 0;
		SetData(iData);
	}

	MString(long lData)
	{
		m_pszData = NULL;
		m_iLength = 0;
		SetData(lData);
	}

	MString(const string& strData)
	{
		m_pszData = NULL;
		m_iLength = 0;
		SetData(strData);
	}

	MString(const char* pszData)
	{
		m_pszData = NULL;
		m_iLength = 0;
		SetData(pszData);
	}


	MString(int iData)
	{
		m_pszData = NULL;
		m_iLength = 0;
		SetData(iData);
	}

	MString(double dData)
	{
		m_pszData = NULL;
		m_iLength = 0;
		SetData(dData);
	}

	MString(unsigned uData)
	{
		m_pszData = NULL;
		m_iLength = 0;
		SetData(uData);
	}
	MString(float fData)
	{
		m_pszData = NULL;
		m_iLength = 0;
		SetData(fData);
	}
	MString(unsigned long ulData)
	{
		m_pszData = NULL;
		m_iLength = 0;
		SetData(ulData);
	}
	MString(short nData)
	{
		m_pszData = NULL;
		m_iLength = 0;
		SetData(nData);
	}
	MString(unsigned short nData)
	{
		m_pszData = NULL;
		m_iLength = 0;
		SetData(nData);
	}
	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////


	void SetData(char chData)
	{
		/*Init();
		m_szData[0] = chData;
		m_iLength = 1;*/

		Init();
		Alloc(1);
		m_pszData[0] = chData;
		m_iLength = 1;
	}

	void SetData(const MString& mstrData)
	{
		//֮������>=m_iLength������=m_iLength��ԭ������SetData("")��������ڣ���strlen("")==0�������ʱm_pszData==NULL�Ļ�
		//memset(m_pszData,0,m_iLength+1);�ͻ�ʧ��
		if (mstrData.GetLength()>=m_iLength)
		{
			Init();
			m_iLength = mstrData.GetLength();
			Alloc(m_iLength);
		}
		else
		{
			memset(m_pszData,0,m_iLength+1);
			m_iLength = mstrData.GetLength();
		}

		/*Init();
		m_iLength = mstrData.GetLength();
		Alloc(m_iLength);*/

		strcpy(m_pszData,mstrData.GetData());
	}

	void SetData(__int64 iData)
	{
		//֮������>=m_iLength������=m_iLength��ԭ������SetData("")��������ڣ���strlen("")==0�������ʱm_pszData==NULL�Ļ�
		//memset(m_pszData,0,m_iLength+1);�ͻ�ʧ��
		Init();
		char szTemp[32];
		memset(szTemp,0,32);
		//ltoa(iData,szTemp,10);
		sprintf(szTemp,"%lld",iData);


		if (strlen(szTemp)>=m_iLength)
		{
			m_iLength = strlen(szTemp);
			Alloc(m_iLength);
		}
		else
		{
			memset(m_pszData,0,m_iLength+1);
			m_iLength = strlen(szTemp);
		}
		/*m_iLength = strlen(szTemp);
		Alloc(m_iLength);*/
		memcpy(m_pszData,szTemp,m_iLength);
	}

	void SetData(long lData)
	{
		//֮������>=m_iLength������=m_iLength��ԭ������SetData("")��������ڣ���strlen("")==0�������ʱm_pszData==NULL�Ļ�
		//memset(m_pszData,0,m_iLength+1);�ͻ�ʧ��
		char szTemp[32];
		memset(szTemp,0,32);
		//ltoa(lData,szTemp,10);
		sprintf(szTemp,"%ld",lData);

		if (strlen(szTemp)>=m_iLength)
		{
			Init();
			m_iLength = strlen(szTemp);
			Alloc(m_iLength);
		}
		else
		{
			memset(m_pszData,0,m_iLength+1);
			m_iLength = strlen(szTemp);
		}
		/*m_iLength = strlen(szTemp);
		Alloc(m_iLength);*/
		memcpy(m_pszData,szTemp,m_iLength);
	}

	void SetData(const string& strData)
	{
		//֮������>=m_iLength������=m_iLength��ԭ������SetData("")��������ڣ���strlen("")==0�������ʱm_pszData==NULL�Ļ�
		//memset(m_pszData,0,m_iLength+1);�ͻ�ʧ��
		if (strData.size()>=m_iLength)
		{
			Init();
			m_iLength = strData.size();
			Alloc(m_iLength);
		}
		else
		{
			memset(m_pszData,0,m_iLength+1);
			m_iLength = strData.size();
		}
		/*Init();
		m_iLength = strData.size();
		Alloc(m_iLength);*/
		strcpy(m_pszData,strData.c_str());
	}

	void SetData(const char* pszData)
	{
		//֮������>=m_iLength������=m_iLength��ԭ������SetData("")��������ڣ���strlen("")==0�������ʱm_pszData==NULL�Ļ�
		//memset(m_pszData,0,m_iLength+1);�ͻ�ʧ��
		if (strlen(pszData)>=m_iLength)
		{
			Init();
			m_iLength = strlen(pszData);
			Alloc(m_iLength);
		}
		else
		{
			memset(m_pszData,0,m_iLength+1);
			m_iLength = strlen(pszData);
		}
		/*Init();
		m_iLength = strlen(pszData);
		Alloc(m_iLength);*/
		strcpy(m_pszData,pszData);
	}

	void SetData(int iData)
	{
		//֮������>=m_iLength������=m_iLength��ԭ������SetData("")��������ڣ���strlen("")==0�������ʱm_pszData==NULL�Ļ�
		//memset(m_pszData,0,m_iLength+1);�ͻ�ʧ��
		char szTemp[32];
		memset(szTemp,0,32);
		//itoa(iData,szTemp,10);
		sprintf(szTemp,"%d",iData);

		if (strlen(szTemp)>=m_iLength)
		{
			Init();
			m_iLength = strlen(szTemp);
			Alloc(m_iLength);
		}
		else
		{
			memset(m_pszData,0,m_iLength+1);
			m_iLength = strlen(szTemp);
		}
		/*m_iLength = strlen(szTemp);
		Alloc(m_iLength);*/
		memcpy(m_pszData,szTemp,m_iLength);
	}

	void SetData(double dData)
	{

		//֮������>=m_iLength������=m_iLength��ԭ������SetData("")��������ڣ���strlen("")==0�������ʱm_pszData==NULL�Ļ�
		//memset(m_pszData,0,m_iLength+1);�ͻ�ʧ��
		stringstream str;
		str<<dData;

		if (str.str().size()>=m_iLength)
		{
			Init();
			m_iLength = str.str().size();
			Alloc(m_iLength);
		}
		else
		{
			memset(m_pszData,0,m_iLength+1);
			m_iLength = str.str().size();
		}

		//m_iLength = str.str().size();
		//Alloc(m_iLength);
		memcpy(m_pszData,str.str().c_str(),m_iLength);
	}

	void SetData(unsigned uData)
	{

		//֮������>=m_iLength������=m_iLength��ԭ������SetData("")��������ڣ���strlen("")==0�������ʱm_pszData==NULL�Ļ�
		//memset(m_pszData,0,m_iLength+1);�ͻ�ʧ��
		stringstream str;
		str<<uData;

		if (str.str().size()>=m_iLength)
		{
			Init();
			m_iLength = str.str().size();
			Alloc(m_iLength);
		}
		else
		{
			memset(m_pszData,0,m_iLength+1);
			m_iLength = str.str().size();
		}

		/*m_iLength = str.str().size();
		Alloc(m_iLength);*/
		memcpy(m_pszData,str.str().c_str(),m_iLength);
	}
	void SetData(float fData)
	{
		//֮������>=m_iLength������=m_iLength��ԭ������SetData("")��������ڣ���strlen("")==0�������ʱm_pszData==NULL�Ļ�
		//memset(m_pszData,0,m_iLength+1);�ͻ�ʧ��
		stringstream str;
		str<<fData;

		if (str.str().size()>=m_iLength)
		{
			Init();
			m_iLength = str.str().size();
			Alloc(m_iLength);
		}
		else
		{
			memset(m_pszData,0,m_iLength+1);
			m_iLength = str.str().size();
		}

		/*m_iLength = str.str().size();
		Alloc(m_iLength);*/
		memcpy(m_pszData,str.str().c_str(),m_iLength);

	}
	void SetData(unsigned long ulData)
	{

		//֮������>=m_iLength������=m_iLength��ԭ������SetData("")��������ڣ���strlen("")==0�������ʱm_pszData==NULL�Ļ�
		//memset(m_pszData,0,m_iLength+1);�ͻ�ʧ��
		stringstream str;
		str<<ulData;

		if (str.str().size()>=m_iLength)
		{
			Init();
			m_iLength = str.str().size();
			Alloc(m_iLength);
		}
		else
		{
			memset(m_pszData,0,m_iLength+1);
			m_iLength = str.str().size();
		}
		/*m_iLength = str.str().size();
		Alloc(m_iLength);*/
		memcpy(m_pszData,str.str().c_str(),m_iLength);
	}
	void SetData(short nData)
	{
		//֮������>=m_iLength������=m_iLength��ԭ������SetData("")��������ڣ���strlen("")==0�������ʱm_pszData==NULL�Ļ�
		//memset(m_pszData,0,m_iLength+1);�ͻ�ʧ��
		stringstream str;
		str<<nData;

		if (str.str().size()>=m_iLength)
		{
			Init();
			m_iLength = str.str().size();
			Alloc(m_iLength);
		}
		else
		{
			memset(m_pszData,0,m_iLength+1);
			m_iLength = str.str().size();
		}
		/*m_iLength = str.str().size();
		Alloc(m_iLength);*/
		memcpy(m_pszData,str.str().c_str(),m_iLength);
	}
	void SetData(unsigned short nData)
	{
		//֮������>=m_iLength������=m_iLength��ԭ������SetData("")��������ڣ���strlen("")==0�������ʱm_pszData==NULL�Ļ�
		//memset(m_pszData,0,m_iLength+1);�ͻ�ʧ��
		stringstream str;
		str<<nData;

		if (str.str().size()>=m_iLength)
		{
			Init();
			m_iLength = str.str().size();
			Alloc(m_iLength);
		}
		else
		{
			memset(m_pszData,0,m_iLength+1);
			m_iLength = str.str().size();
		}
		/*m_iLength = str.str().size();
		Alloc(m_iLength);*/
		memcpy(m_pszData,str.str().c_str(),m_iLength);
	}

	//========================================================
	//���������
	//========================================================
	MString& operator=(const char* pszData)
	{
		SetData(pszData);
		return *this;
	}

	MString& operator=(const string& strData)
	{
		SetData(strData);
		return *this;
	}
	MString& operator=(long lData)
	{
		SetData(lData);
		return *this;
	}
	MString& operator=(__int64 iData)
	{
		SetData(iData);
		return *this;
	}
	MString& operator=(const MString& m_strData)
	{
		SetData(m_strData);
		return *this;
	}
	MString& operator=(char chData)
	{
		SetData(chData);
		return *this;
	}
	MString& operator=(int iData)
	{
		SetData(iData);
		return *this;
	}
	MString& operator=(double dData)
	{
		SetData(dData);
		return *this;
	}

	MString& operator=(unsigned uData)
	{
		SetData(uData);
		return *this;
	}
	MString& operator=(float fData)
	{
		SetData(fData);
		return *this;
	}
	MString& operator=(unsigned long ulData)
	{
		SetData(ulData);
		return *this;
	}
	MString& operator=(short nData)
	{
		SetData(nData);
		return *this;
	}
	MString& operator=(unsigned short nData)
	{
		SetData(nData);
		return *this;
	}

	MString& operator+=(const char* pszData)
	{
		MString mstr = pszData;
		*this += mstr;
		return *this;
	}
	MString& operator+=(const string& strData)
	{
		MString mstr = strData;
		*this += mstr;
		return *this;
	}
	MString& operator+=(long lData)
	{
		MString mstr = lData;
		*this += mstr;
		return *this;

	}
	MString& operator+=(__int64 iData)
	{
		MString mstr = iData;
		*this += mstr;
		return *this;
	}
	MString& operator+=(const MString& m_strData)
	{
		/*strcat(m_szData,m_strData.c_str());
		m_iLength += m_strData.GetLength();
		return *this;*/

		//����ԭ������
		char* pszTemp = new char[m_iLength + 1];
		memset(pszTemp,0,m_iLength + 1);
		memcpy(pszTemp,m_pszData,m_iLength);

		//�������ڴ�
		m_iLength += m_strData.GetLength();
		Alloc(m_iLength);

		//�ָ�ԭ������
		strcpy(m_pszData,pszTemp);
		//�����µ�����
		strcat(m_pszData,m_strData.c_str());

		//ɾ����ʱ������
		delete[] pszTemp;

		return *this;
	}
	MString& operator+=(char chData)
	{
		MString mstr = chData;
		*this += mstr;
		return *this;
	}
	MString& operator+=(int iData)
	{
		MString mstr = iData;
		*this += mstr;
		return *this;
	}
	MString& operator+=(double dData)
	{
		MString mstr = dData;
		*this += mstr;
		return *this;
	}

	MString& operator+=(unsigned uData)
	{
		MString mstr = uData;
		*this += mstr;
		return *this;
	}
	MString& operator+=(float fData)
	{
		MString mstr = fData;
		*this += mstr;
		return *this;
	}
	MString& operator+=(unsigned long ulData)
	{
		MString mstr = ulData;
		*this += mstr;
		return *this;
	}
	MString& operator+=(short nData)
	{
		MString mstr = nData;
		*this += mstr;
		return *this;
	}
	MString& operator+=(unsigned short nData)
	{
		MString mstr = nData;
		*this += mstr;
		return *this;
	}


	MString operator+(const char* pszData)
	{
		MString mstr = *this;
		mstr += pszData;
		return mstr;
	}
	MString operator+(const string& strData)
	{
		MString mstr = *this;
		mstr += strData;
		return mstr;
	}
	MString operator+(long lData)
	{
		MString mstr = *this;
		mstr += lData;
		return mstr;
	}
	MString operator+(__int64 iData)
	{
		MString mstr = *this;
		mstr += iData;
		return mstr;
	}
	MString operator+(const MString& m_strData)
	{

		MString mstr = *this;
		mstr += m_strData;
		return mstr;
	}
	MString operator+(char chData)
	{
		MString mstr = *this;
		mstr += chData;
		return mstr;
	}
	MString operator+(int iData)
	{
		MString mstr = *this;
		mstr += iData;
		return mstr;
	}
	MString operator+(double dData)
	{
		MString mstr = *this;
		mstr += dData;
		return mstr;
	}

	MString operator+(unsigned uData)
	{
		MString mstr = *this;
		mstr += uData;
		return mstr;
	}
	MString operator+(float fData)
	{
		MString mstr = *this;
		mstr += fData;
		return mstr;
	}
	MString operator+(unsigned long ulData)
	{
		MString mstr = *this;
		mstr += ulData;
		return mstr;
	}
	MString operator+(short nData)
	{
		MString mstr = *this;
		mstr += nData;
		return mstr;
	}
	MString operator+(unsigned short nData)
	{
		MString mstr = *this;
		mstr += nData;
		return mstr;
	}
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	unsigned int GetLength() const
	{
		if (m_pszData == NULL)
		{
			return 0;
		}

		return m_iLength;
	}

	const char* GetData() const
	{
		//return m_szData;
		if (m_pszData != 0)
		{
			m_pszData[m_iLength] = 0;
		}

		return m_pszData;
	}

	const char* c_str() const
	{
		//return m_szData;
		m_pszData[m_iLength] = 0;
		return m_pszData;
	}

	const char* ToString() const
	{
		//return m_szData;
		m_pszData[m_iLength] = 0;
		return m_pszData;
	}





	int Find(char chData)
	{
		unsigned int iIndex  = 0;
		for (iIndex = 0; iIndex <m_iLength ; ++iIndex)
		{
			//if (chData == m_szData[iIndex])
			if (chData == m_pszData[iIndex])
			{
				return iIndex;
			}
		}

		if (m_iLength == iIndex )
		{
			return -1;
		}
	}

	int RFind(char chData)
	{
		int iIndex  = 0;
		for (iIndex = m_iLength -1; iIndex >= 0 ; --iIndex)
		{
			//if (chData == m_szData[iIndex])
			if (chData == m_pszData[iIndex])
			{
				return iIndex;
			}
		}

		if (m_iLength == iIndex )
		{
			return -1;
		}
	}

	int Find(const char* pszData,unsigned int iStart)
	{
		//string str = m_szData;
		string str = m_pszData;
		string str2 = pszData;
		return str.find(str2,iStart);
	}
	int Find(const MString& mstrData,unsigned int iStart)
	{
		//string str = m_szData;
		string str = m_pszData;
		string str2 = mstrData.c_str();
		return str.find(str2,iStart);
	}

	bool Empty()
	{
		if (0 == m_iLength)
		{
			return true;
		}

		return false;
	}

	char& operator[](unsigned int uIndex)
	{
		//return m_szData[uIndex];

		return GetChar(uIndex);
	}

	char& operator[](int uIndex)
	{
		//return m_szData[uIndex];

		return GetChar(uIndex);
	}

	char& GetChar(unsigned nIndex)
	{
		return m_pszData[nIndex];
	}

	void Replace(const char* pszSrc,const char* pszDest)
	{

	}

	MString SplitString(MString& strCmdString,const char chToken)
	{

		int nIndex = 0;

		nIndex = strCmdString.Find(chToken);

		MString strTemp ;

		if (nIndex == -1)
		{
			strTemp = strCmdString;

			strCmdString = "";
		}
		else
		{
			strTemp = strCmdString.Left(nIndex);

			strCmdString = strCmdString.Rigth(nIndex);
		}

		return strTemp;
	}

	operator const char *() const
	{
		//return m_szData;
		return m_pszData;
	}

	operator char *()
	{
		//return m_szData;
		return m_pszData;
	}



	//========================================================
	//ȥ�ո����
	//========================================================
	void Trim()
	{

		TrimRigth();
		TrimLeft();
	}
	void TrimLeft()
	{
		MString mstr;
		unsigned int iIndex = 0;
		for (iIndex = 0; iIndex < m_iLength ; ++iIndex)
		{
			//if (' ' != m_szData[iIndex])
			if (' ' != m_pszData[iIndex] && '\t' != m_pszData[iIndex])
			{
				break;
			}
			--m_iLength;
		}

		//mstr = &m_szData[iIndex];
		mstr = &m_pszData[iIndex];

		*this = mstr ;
	}
	void TrimRigth()
	{
		MString mstr;
		int iIndex = 0;
		for (iIndex = m_iLength-1; iIndex >= 0 ; --iIndex)
		{
			//if (' ' != m_szData[iIndex])
			if (' ' != m_pszData[iIndex] && '\t' != m_pszData[iIndex] && '\r' != m_pszData[iIndex] && '\n' != m_pszData[iIndex])
			{

				break;
			}
			else
			{
				--m_iLength;
				m_pszData[iIndex] = 0;
			}
		}

		//m_szData[iIndex+1] = 0;

		//m_pszData[iIndex+1] = 0;

	}

	const char*  GainClassName() const
	{
		return "MString";
	}
	/*
	void Load(MAchive& ar)
	{
		int m_iLength = ar.Load_int();
		Alloc(m_iLength);
		ar.Load_pointer(m_pszData);
	}

	void Save(MAchive& ar)
	{
		ar.Save_int(m_iLength);
		ar.Save_pointer(m_pszData,m_iLength);
	}
	*/
	friend ostream& operator<<(ostream &out,const MString & mstr)
	{
		out<<(const char*)mstr;
		return out;
	}
	friend istream&operator>>(istream &in,MString &mstr)
	{
		in>>(char*)mstr;
		return in;
	}

	//========================================================
	//ȡ���ַ��������
	//========================================================
	MString substr(unsigned int uStart,unsigned int uLength)
	{
		MString mstr;
		string temp =m_pszData;
		mstr = temp.substr(uStart,uLength);
		//for (int iIndex = uStart ;iIndex<uStart+uLength;++iIndex)
		//{
		//	//mstr += m_szData[iIndex];
		//	mstr += m_pszData[iIndex];
		//}
		return mstr;
	}

	MString Left(unsigned nIndex)
	{
		if (nIndex == 0 || nIndex >= GetLength())
		{
			return "";
		}
		return substr(0,nIndex);
	}

	MString Rigth(unsigned nIndex)
	{
		if (nIndex == GetLength() - 1 || nIndex < 0)
		{
			return "";
		}
		return substr(nIndex+1,GetLength()-nIndex-1);
	}

	//========================================================
	//�Ƚ������
	//========================================================
	bool Equal(const string& src)
	{
		if (0== strcmp(GetData(),src.c_str()))
		{
			return true;
		}

		return false;
	}
	bool Equal(const char* src)
	{
		if (0== strcmp(GetData(),src))
		{
			return true;
		}

		return false;
	}
	bool Equal(char* src)
	{
		if (0== strcmp(GetData(),src))
		{
			return true;
		}

		return false;
	}
	bool Equal(const MString& src)
	{
		if (0== strcmp(GetData(),src.c_str()))
		{
			return true;
		}

		return false;
	}

	bool operator==(const string& src)
	{
		if (0== strcmp(GetData(),src.c_str()))
		{
			return true;
		}

		return false;
	}
	bool operator==(const char* src)
	{
		if (0== strcmp(GetData(),src))
		{
			return true;
		}

		return false;
	}
	bool operator==(char* src)
	{
		if (0== strcmp(GetData(),src))
		{
			return true;
		}

		return false;
	}
	bool operator==(const MString& src)
	{
		if (0== strcmp(GetData(),src.c_str()))
		{
			return true;
		}

		return false;
	}


	int GetObjSize()
	{
		return (sizeof(*this));
	}

	const char* GainClassName()
	{
		return "MString";
	}

private:
	void Alloc(int iLength)
	{
		if (m_pszData != NULL)
		{
			delete[] m_pszData;
			m_pszData = NULL;
		}

		m_pszData = new char[iLength +1];
		memset(m_pszData,0,iLength +1);
	}

	void Init()
	{
		/*memset(m_szData,0,SZ_L_LENGTH);
		m_iLength = 0;
		m_iPos = 0;*/

		//˵����ɾ���������е�ԭ���ǣ���MString��ֵ�������SetData�Ļ�������ڴ�й¶
		//m_pszData = new char[0];

		if (m_pszData != NULL)
		{
			delete[] m_pszData;
			m_pszData = new char[1];
			strcpy(m_pszData,"");
		}

		m_iLength = 0;
		m_iPos = 0;
	}

	char* m_pszData;

	unsigned int m_iLength;

	unsigned int m_iPos;
};


#endif // MSTRING_H
