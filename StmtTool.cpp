#include "stdafx.h"
#include "StmtTool.h"
#include "windows.h"
CStmtTool::CStmtTool() noexcept
	:m_size(0),m_Stmt(nullptr),m_StmtStr(nullptr),m_RetCode(-1)
{

}
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
	m_size = 0;
	m_RetCode = -1;
}
CStmtTool::~CStmtTool() {
	finalize();
}

const unsigned char* CStmtTool::column_text(int icol) {
	if (m_Stmt != nullptr) {
		return sqlite3_column_text(m_Stmt, icol);
	}
	return nullptr;
}

int CStmtTool::column_int(int icol) {

	if (m_Stmt != nullptr) {
		return sqlite3_column_int(m_Stmt, icol);
	}
	return 0;
}

void CStmtTool::changeStmt(sqlite3 * db,const char* str, int strSize, ENCODE code) {
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
bool CStmtTool:: operator == (int sqliteVal) {
	return isOK(sqliteVal);
}
bool CStmtTool:: operator != (int sqliteVal) {
	return !isOK(sqliteVal);
}

CStmtTool::ErrorCode CStmtTool::exec(sqlite3 * db, const char * cstr, ENCODE code, int size)
{
	ErrorCode eCode = ErrorCode::SUCCESS;
	changeStmt(db, cstr, size, code);
	if (isOK(SQLITE_OK))
	{
		step();
		if (isOK(SQLITE_DONE))
		{
			eCode = ErrorCode::SUCCESS;
		}
		else
		{
			eCode = ErrorCode::UNSUCCESS;
		}
	}
	else
	{
		eCode = ErrorCode::STMTERROR;
	}
	return eCode;
}

CStmtTool::ErrorCode CStmtTool::exec(sqlite3 * db, const char * cstr, int size, ENCODE code, int * retVal, int pos)
{
	//假定retVal指向有效地址
	ErrorCode eCode = ErrorCode::SUCCESS;
	changeStmt(db, cstr, size, code);
	if (isOK(SQLITE_OK))
	{
		step();
		if (isOK(SQLITE_DONE))
		{
			(*retVal) = column_int(pos);
			eCode = ErrorCode::UNSUCCESS;
		}
		else
		{
			eCode = ErrorCode::UNSUCCESS;
		}
	}
	else
	{
		eCode = ErrorCode::STMTERROR;
	}
	return eCode;
}

CStmtTool::ErrorCode CStmtTool::exec(sqlite3 * db, const char * cstr, int size, ENCODE code, const unsigned char ** retVal, int pos)
{
	//假定retVal指向有效地址
	ErrorCode eCode = ErrorCode::SUCCESS;
	changeStmt(db, cstr, size, code);
	if (isOK(SQLITE_OK))
	{
		step();
		if (isOK(SQLITE_DONE))
		{
			(*retVal) = column_text(pos);
			eCode = ErrorCode::UNSUCCESS;
		}
		else
		{
			eCode = ErrorCode::UNSUCCESS;
		}
	}
	else
	{
		eCode = ErrorCode::STMTERROR;
	}
	return eCode;
}



