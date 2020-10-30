#pragma once
/*
* @class CStmtTool
* @brief CStmtTool用于与SQLite数据库进行交互，一个CStmtTool对象代表一个语句
* @discussion 编写此类可以放开管理Stmt对象的销毁工作，由unique_ptr来完成，避免更多错误
* @see
*
*/


#include "include/sqlite3.h"
#include <memory>
enum ENCODE
{
	UTF8,
	UTF16
};
class CStmtTool {
public:
	enum class ErrorCode {
		SUCCESS = 0,
		STMTERROR,
		INVALIDARG,
		UNSUCCESS
	};
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
	/*空构造函数*/
	CStmtTool() noexcept;
	CStmtTool(sqlite3* db, const char * str, int strSize, ENCODE code) noexcept;
	~CStmtTool();
	/*执行*/
	void  step();
	/*执行*/
	void operator() ();
	/*改变此CStmtTool对象对应的SQL语句*/
	void changeStmt(sqlite3 * db, const char* str, int strSize, ENCODE);
	/*取得一个text结果，以const unsigned char*的形式返回*/
	const unsigned char * column_text(int icol);
	/*取得一个int结果*/
	int column_int(int icol);
	bool isOK(int sqliteVal);
	bool operator == (int sqliteVal);
	bool operator!= (int sqliteVal);
	/*执行一个无返回语句*/
	ErrorCode exec(sqlite3 * db, const char * cstr, ENCODE code, int size);
	/*获取单行单个数值数据*/
	ErrorCode exec(sqlite3 * db, const char * cstr, int size, ENCODE code, int * retVal , int pos);
	/*获取单行单个文本数据*/
	ErrorCode exec(sqlite3 * db, const char * cstr, int size, ENCODE code, const unsigned char ** retVal,int pos);
	
};