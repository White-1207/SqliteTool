#include "StmtTool.h"
#include <stdlib.h>

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