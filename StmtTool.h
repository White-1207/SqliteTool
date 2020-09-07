#pragma once
/*
* @class CStmtTool
* @brief CStmtTool用于与SQLite数据库进行交互，一个CStmtTool对象代表一个语句
* @discussion 编写此类可以放开管理Stmt对象的销毁工作，由unique_ptr来完成，避免更多错误
* @see
*
*/
#include "sqlite3.h"
enum ENCODE
{
	UTF8,
	UTF16
};
typedef void*(*callbackFunc)(void*);
class CStmtTool {

private:

	char * m_StmtStr;
	int m_size;//原始字符串所占用的字节大小
	sqlite3_stmt * m_Stmt;
public:
	int m_RetCode; //最近执行语句的返回结果
	CStmtTool(sqlite3* db, const char * str, int strSize, ENCODE) noexcept;
	~CStmtTool();
	void  step();
	void finalize();
	void changeStmt(sqlite3 * db,const char* str, int strSize, ENCODE);
	const unsigned char * column_text(int icol);
	int column_int(int icol);
	void operator() ();
};