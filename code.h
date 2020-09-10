#pragma once
#include "windows.h"
/*
* @filename code.h
* @class CCcode
* @brief ����Windows�����µı����
������Դ����ĵ�ַ���ֽ�������Ϊ���ܻ����Ұָ������⣬��������Ŀ�ı����ַ������ڴ�������ֽ�����
* @author Jiap
*/

class CCode {
private:
	/*����Ŀ�ı���������ֽ���*/
	int m_DesSize;
	/*����Ŀ�ı����ַ����ĵ�ַ*/
	char * m_pDesStr;
protected:
	/*
	* @brief ���佫iSocStrָ��Ķ��ֽ��ַ�����iCodePageִ��ת��������ڴ�
	* @return  ipDesStr ������ڴ���ʼ��ַ
	* @return ��������ֵ����0��ʾ������ڴ��С������0��ʾ�����ڴ�ʧ��
	*/
	int AllocToWide(const char * iSocStr, int iSize, UINT iCodePage, wchar_t *& iDesStr);
	/*
	* @brief ��iSocStrָ��Ķ��ֽ��ַ�����iCodePageִ��ת�����������������m_pDesStr
	* @return ipDesStr ָ��ִ��ת����Ľ�� 
	* @return ��������true��ʾִ��ת���ɹ���flase��ʾת��ʧ��
	*/
	bool CodeToWide(const char * iSocStr, int iSocSize, int iDesSize, UINT iCodePage, wchar_t *& iDesStr);
	/*
	* @brief ���佫iSocStrָ��Ŀ��ֽ��ַ�����iCodePageִ��ת��������ڴ�
	* @return  ipDesStr ������ڴ���ʼ��ַ
	* @return ��������ֵ����0��ʾ������ڴ��С������0��ʾ�����ڴ�ʧ��
	*/
	int AllocToMutli(const wchar_t * iSocStr, int iSize, UINT iCodePage, char *& iDesStr);
	/*
	* @brief ��iSocStrָ��Ŀ��ֽ��ַ�����iCodePageִ��ת�����������������m_pDesStr
	* @return ipDesStr ָ��ִ��ת����Ľ��
	* @return ��������true��ʾִ��ת���ɹ���flase��ʾת��ʧ��
	*/
	bool CodeToMutli(const wchar_t * iSocStr, int iSocSize,int iDesSize, UINT iCodePage, char *& iDesStr);
public:
	/*�չ��캯��*/
	CCode();
	/*��������*/
	virtual ~CCode();
	/*
	* @brief �ɶ��ֽ�תΪ���ֽ�
	�ɶ��ֽ�תΪ���ֽ���Ҫ�Ƚ�Դ���ֽ�תΪ���ֽڣ�Ȼ��תΪĿ�Ķ��ֽ�
	* @param iMutliStr ָ����Ҫת����Դ�ַ���ָ��
	* @param iSize ��Ҫת����Դ�ַ����Ĵ�С
	* @param iDesCodePage ��Ҫ��ת����Ŀ�ı���ҳ
	* @param iSocCodePage ��ǰ�ı���ҳ
	* @return iDesMutliStr ָ�������ַ�����ָ�룬�ڶ������ٺ���ָ����ڴ汻�ͷţ����Ϊnullptrת��ʧ��
	* @return ��������ֵΪָ�������ַ����Ĵ�С�����Ϊ0��ת��ʧ��
	*/
	int MutliToMutli(const char * iSocMutliStr, int iSize, UINT iSocCodePage, UINT iDesCodePage, char *& iDesMutliStr );
};