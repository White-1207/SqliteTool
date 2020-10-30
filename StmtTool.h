#pragma once
/*
* @class CStmtTool
* @brief CStmtTool������SQLite���ݿ���н�����һ��CStmtTool�������һ�����
* @discussion ��д������Էſ�����Stmt��������ٹ�������unique_ptr����ɣ�����������
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
	/*��ʶһ��sqlite3�������ڴ�sqlite3_stmt��ִ��״̬���û�ȡ��һ��ִ�н����Ӧ������˽�������ϣ���Ժ�ʹ�ô˽���Ļ������򽫻ᶪʧ�˽����*/
	int m_RetCode;
	char * m_StmtStr;
	int m_size;
	sqlite3_stmt * m_Stmt;
protected:
	void finalize();
public:
	int GetRetCode();
	/*�չ��캯��*/
	CStmtTool() noexcept;
	CStmtTool(sqlite3* db, const char * str, int strSize, ENCODE code) noexcept;
	~CStmtTool();
	/*ִ��*/
	void  step();
	/*ִ��*/
	void operator() ();
	/*�ı��CStmtTool�����Ӧ��SQL���*/
	void changeStmt(sqlite3 * db, const char* str, int strSize, ENCODE);
	/*ȡ��һ��text�������const unsigned char*����ʽ����*/
	const unsigned char * column_text(int icol);
	/*ȡ��һ��int���*/
	int column_int(int icol);
	bool isOK(int sqliteVal);
	bool operator == (int sqliteVal);
	bool operator!= (int sqliteVal);
	/*ִ��һ���޷������*/
	ErrorCode exec(sqlite3 * db, const char * cstr, ENCODE code, int size);
	/*��ȡ���е�����ֵ����*/
	ErrorCode exec(sqlite3 * db, const char * cstr, int size, ENCODE code, int * retVal , int pos);
	/*��ȡ���е����ı�����*/
	ErrorCode exec(sqlite3 * db, const char * cstr, int size, ENCODE code, const unsigned char ** retVal,int pos);
	
};