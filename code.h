#pragma once
#include "windows.h"
/*
* @filename code.h
* @class CCcode
* @brief 用于Windows环境下的编解码
不保存源编码的地址和字节数，因为可能会出现野指针的问题，仅管理保存目的编码字符串的内存和所需字节数。
* @author Jiap
*/

class CCode {
private:
	/*保存目的编码所需的字节数*/
	int m_DesSize;
	/*保存目的编码字符串的地址*/
	char * m_pDesStr;
protected:
	/*
	* @brief 分配将iSocStr指向的多字节字符串由iCodePage执行转换所需的内存
	* @return  ipDesStr 分配的内存起始地址
	* @return 函数返回值大于0表示分配的内存大小，返回0表示分配内存失败
	*/
	int AllocToWide(const char * iSocStr, int iSize, UINT iCodePage, wchar_t *& iDesStr);
	/*
	* @brief 将iSocStr指向的多字节字符串由iCodePage执行转换，并将结果保存在m_pDesStr
	* @return ipDesStr 指向执行转换后的结果 
	* @return 函数返回true表示执行转换成功，flase表示转换失败
	*/
	bool CodeToWide(const char * iSocStr, int iSocSize, int iDesSize, UINT iCodePage, wchar_t *& iDesStr);
	/*
	* @brief 分配将iSocStr指向的宽字节字符串由iCodePage执行转换所需的内存
	* @return  ipDesStr 分配的内存起始地址
	* @return 函数返回值大于0表示分配的内存大小，返回0表示分配内存失败
	*/
	int AllocToMutli(const wchar_t * iSocStr, int iSize, UINT iCodePage, char *& iDesStr);
	/*
	* @brief 将iSocStr指向的宽字节字符串由iCodePage执行转换，并将结果保存在m_pDesStr
	* @return ipDesStr 指向执行转换后的结果
	* @return 函数返回true表示执行转换成功，flase表示转换失败
	*/
	bool CodeToMutli(const wchar_t * iSocStr, int iSocSize,int iDesSize, UINT iCodePage, char *& iDesStr);
public:
	/*空构造函数*/
	CCode();
	/*析构函数*/
	virtual ~CCode();
	/*
	* @brief 由多字节转为多字节
	由多字节转为多字节需要先将源多字节转为宽字节，然后转为目的多字节
	* @param iMutliStr 指向需要转换的源字符串指针
	* @param iSize 需要转换的源字符串的大小
	* @param iDesCodePage 需要到转换的目的编码页
	* @param iSocCodePage 当前的编码页
	* @return iDesMutliStr 指向编码后字符串的指针，在对象销毁后，其指向的内存被释放，如果为nullptr转换失败
	* @return 函数返回值为指向编码后字符串的大小，如果为0，转换失败
	*/
	int MutliToMutli(const char * iSocMutliStr, int iSize, UINT iSocCodePage, UINT iDesCodePage, char *& iDesMutliStr );
};