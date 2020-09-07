#pragma once
/*
* @class CStmtTool
* @brief CStmtTool 用来操纵sqlite3_stmt对象
* @discussion 一个CStmtTool对应一个sqlite3_stmt对象
* @author Jp
*
*/
#include "sqlite3.h"
//指定UTF-8或UTF-16编码创建的数据库
enum ENCODE
{
	UTF8,
	UTF16
};
class CStmtTool {
private:
	/*标识一次sqlite3函数关于此sqlite3_stmt的执行状态，用户取得一次执行结果后，应当保存此结果（如果希望以后使用此结果的话，否则将会丢失此结果）*/
	int m_RetCode;
	char * m_StmtStr;
	int m_size;
	sqlite3_stmt * m_Stmt;
protected:
	void finalize();
public:
	int GetRetCode();
	CStmtTool(sqlite3* db, const char * str, int strSize, ENCODE code) noexcept;
	~CStmtTool();
	/*执行*/
	void  step();
	/*执行*/
	void operator() ();
	/*改变此CStmtTool对象对应的SQL语句*/
	void changeStmt(sqlite3 * db,const char* str, int strSize, ENCODE);
	/*取得一个text结果，以UTF-8的形式返回*/
	const unsigned char * column_text(int icol);
	/*取得一个int结果*/
	int column_int(int icol);
};