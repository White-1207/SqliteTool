#pragma once
/*
* @class CStmtTool
* @brief CStmtTool������SQLite���ݿ���н�����һ��CStmtTool�������һ�����
* @discussion ��д������Էſ�����Stmt��������ٹ�������unique_ptr����ɣ�����������
* @see
*
*/
#include "sqlite3.h"
enum ENCODE
{
	UTF8,
	UTF16
};
class CStmtTool {
private:
	int m_RetCode;//���ִ�����ķ��ؽ��
	char * m_StmtStr;
	int m_size;//ԭʼ�ַ�����ռ�õ��ֽڴ�С
	sqlite3_stmt * m_Stmt;
protected:
	void finalize();
public:
	int GetRetCode();
	CStmtTool(sqlite3* db, const char * str, int strSize, ENCODE) noexcept;
	~CStmtTool();
	void  step();
	void changeStmt(sqlite3 * db,const char* str, int strSize, ENCODE);
	const unsigned char * column_text(int icol);
	int column_int(int icol);
	void operator() ();
};