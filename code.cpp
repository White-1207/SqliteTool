#include "code.h"

CCode::CCode() :
m_DesSize(0),m_pDesStr(nullptr)
{

}
CCode::~CCode() {
	if (m_pDesStr != nullptr) {
		delete m_pDesStr;
	}
	m_pDesStr = nullptr;
	m_DesSize = 0;
}
int CCode::AllocToWide(const char * iSocStr, int iSize, UINT iCodePage, wchar_t *& iDesStr) {
	int size = MultiByteToWideChar(iCodePage, MB_PRECOMPOSED, iSocStr, iSize, NULL, 0);
	iDesStr =new wchar_t [size];
	return size;
}

bool CCode::CodeToWide(const char * iSocStr, int iSocSize, int iDesSize, UINT iCodePage,wchar_t *& iDesStr) {
	int num = MultiByteToWideChar(iCodePage, MB_PRECOMPOSED, iSocStr, iSocSize, iDesStr, iDesSize);
	if (num == 0) {
		return false;
	}
	return true;
}

int CCode::AllocToMutli(const wchar_t * iSocStr, int iSize, UINT iCodePage, char *& iDesStr) {
	int size = WideCharToMultiByte(iCodePage, 0, iSocStr, iSize, NULL, 0, NULL, NULL);
	iDesStr = new char[size];
	return size;
}

bool CCode::CodeToMutli(const wchar_t * iSocStr, int iSocSize, int iDesSize, UINT iCodePage, char *& iDesStr) {
	int num = WideCharToMultiByte(iCodePage, 0, iSocStr, iSocSize, iDesStr, iDesSize, NULL, NULL);
	if (num == 0) {
		return false;
	}
	return true;
}

int CCode::MutliToMutli(const  char * iSocMutliStr, int iSize, UINT iSocCodePage, UINT iDesCodePage,
	char *& iDesMutliStr) {
	int desSize = 0;
	/*
	* brief 首先转换为宽字节(UTF-16)
	 1 调用AllocToWide 分配转换为UTF-16所需的内存
	 2 调用CodeToWide 执行转换
	* localvariable pWide 指向保存转为UTF-16的字符串的地址
	* localvariable wideSize 保存转换为UTF-16所需的内存大小，以字节为单位
	*/
	int wideSize = 0;
	wchar_t * pWide;

	wideSize = AllocToWide(iSocMutliStr, iSize, iSocCodePage, pWide);
	if (wideSize == 0) {
		iDesMutliStr = nullptr;
		return 0;
	}
	CodeToWide(iSocMutliStr, iSize,wideSize, iSocCodePage, pWide);

	/*
	* brief 首先转换为多字节(UTF-8)
	* 1 调用AllocToWide 分配转换为UTF-16所需的内存
	* 2 调用CodeToWide 执行转换
	*/
	m_DesSize = AllocToMutli(pWide, wideSize, iDesCodePage,m_pDesStr);
	if (m_DesSize == 0) {
		iDesMutliStr = nullptr;
		return 0;
	}
	CodeToMutli(pWide, wideSize, m_DesSize, iDesCodePage, m_pDesStr);

	/*清理内存*/
	delete []pWide;

	/*返回执行结果*/
	iDesMutliStr = m_pDesStr;
	return m_DesSize;
}