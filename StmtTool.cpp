#include "StmtTool.h"
#include <string.h>

CStmtTool::CStmtTool(sqlite3* db, const char * str, int strSize, ENCODE code) noexcept
	:m_size(strSize), m_Stmt(nullptr), m_StmtStr(nullptr), m_RetCode(-1)
{
	if (db == nullptr) {
		m_RetCode = SQLITE_ERROR;
		return;
	}
	m_StmtStr = new char[strSize];
	memcpy(m_StmtStr, str, strSize);
	m_size = strSize;
	if (code == UTF8) {
		m_RetCode = sqlite3_prepare_v2(db, m_StmtStr, -1, &m_Stmt, NULL);
	}
	else
	{
		m_RetCode = sqlite3_prepare16_v2(db, m_StmtStr, sizeof(m_StmtStr), &m_Stmt, NULL);
	}
}

void  CStmtTool::step() {
	m_RetCode = sqlite3_step(m_Stmt);
}

void CStmtTool::finalize() {
	if (m_Stmt != nullptr) {
		sqlite3_finalize(m_Stmt);
	}
	m_Stmt = nullptr;
	if (m_StmtStr != nullptr) {
		delete[] m_StmtStr;
	}
	m_StmtStr = nullptr;
}
CStmtTool::~CStmtTool() {
	finalize();
}

const unsigned char* CStmtTool::column_text_ANSI(int icol,ENCODE type) {
	char * desMutliAnsi = nullptr;
	int numAnsi = 0;
	int sizeUtf8 = 1;//sqlite3_column_text 返回的字符串即使是空字符串，也是由0结尾的，因此，其返回值长度至少为1 
	//语句不存在，返回nullptr;
	if (m_Stmt == nullptr) {
		return nullptr;
	}
	if (type == UTF8) {
		const char * socMutliUtf8 = (const char *)sqlite3_column_text(m_Stmt, icol);
		for (int i = 0; socMutliUtf8[i] != 0; i++) {
			sizeUtf8++;
		}
		numAnsi = code.MutliToMutli(socMutliUtf8, sizeUtf8, CP_UTF8, CP_ACP, desMutliAnsi);
		return (const unsigned char*)desMutliAnsi;
	}
	//暂时未定义utf16和utf32
	return nullptr;
}

int CStmtTool::column_int(int icol) {

	if (m_Stmt != nullptr) {
		return sqlite3_column_int(m_Stmt, icol);
	}
	return 0;
}

void CStmtTool::changeStmt(sqlite3 * db, const char* str, int strSize, ENCODE code) {
	finalize();
	if (db == nullptr) {
		m_RetCode = SQLITE_ERROR;
		return;
	}
	m_StmtStr = new char[strSize];
	memcpy(m_StmtStr, str, strSize);
	m_size = strSize;
	if (code == UTF8) {
		m_RetCode = sqlite3_prepare_v2(db, m_StmtStr, -1, &m_Stmt, NULL);
	}
	else
	{
		m_RetCode = sqlite3_prepare16_v2(db, m_StmtStr, sizeof(m_StmtStr), &m_Stmt, NULL);
	}
}

void CStmtTool::operator()() {
	step();
}

int CStmtTool::GetRetCode() {
	int tmp = m_RetCode;
	m_RetCode = -1;//赋值为-1，是由于SQLITE3 C++API的宏定义都是大于等于0的
	return tmp;
}

bool CStmtTool::isOK(int sqliteVal) {
	if (GetRetCode() == sqliteVal) {
		return true;
	}
	return false;
}

bool CStmtTool::operator==(int sqliteVal) {
	return isOK(sqliteVal);
}

bool CStmtTool::operator!=(int sqliteVal) {
	return !isOK(sqliteVal);
}

void CStmtTool::bind_text_ANSI(int index, const char *str, int size, void(*func)(void*),ENCODE type) {
	char * desStr = nullptr;
	int num = 0;
	UINT desCodePage = 0;
	if (type == UTF8) {
		num = code.MutliToMutli(str, size, CP_ACP, CP_UTF8, desStr);
	}
	if (num == 0) {
		m_RetCode = -1;
		return;
	}
	if (m_Stmt == nullptr) {
		m_RetCode = -1;
	}
	m_RetCode = sqlite3_bind_text(m_Stmt, index, desStr, num, func);
}