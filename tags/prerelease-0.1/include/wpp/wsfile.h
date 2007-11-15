/*
 "               ..;;;;,                     ;;;,    
 '           ..;;;"` ;;:           ,;;;;;: ,;;;:.,;..          _/
 `     ,;..,;;"`    :;;'            :;;"`,;;;;;;"":;;         _/ 
       ;;;"  `:;;. ;;'           ..;;:  .;;,.;;:',;;"    _/_/_/_/_/
      .;;`   ,;;" .;"          ,;;;;;;" :;`',;",;;"         _/
     ,;;,:.,;;;  ,;:          :" ,;:` , `:.;;;;;'`         _/   
     ;;"'':;;:. .;; .          ,;;;,;:;;,;;;, ,;             _/
    :;;..;;;;;; :;' :.        :;;;"` `:;;;;;,;,.;.          _/
  .;;":;;`  '"";;:  ';;       '""   .;;`.;";:;;;;` ;,  _/_/_/_/_/
 ;;;" `'       "::. ,;;:          .;"`  ::. '   .,;;;     _/ 
 ""             ';;;;;;;"        ""     ';;;;;;;;;;`     _/
 
                        Windsoul++

                by �Ʒ� (Cloud Wu)  1999-2001
 
		http://member.netease.com/~cloudwu 
		mailto:cloudwu@263.net
 
		���Ķ� readme.txt �еİ�Ȩ��Ϣ
		See readme.txt for copyright information.

		Description:		����ļ�����ͷ�ļ�
 		Original Author:	�Ʒ�
		Authors:
		Create Time:		2000/12/14
		Modify Time:		2001/10/10

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_FILE_H
#define _WINDSOUL_FILE_H

 ///	�����ļ�
//////////////////////

#define WS_DATAFILECANTOPEN MAKE_ERR(_ERR_FILE,'DAT')
#define WS_INVALIDDATAFILE MAKE_ERR(_ERR_FILE,'DAH')

class WINDSOUL_API WFile {
protected:
	void *m_Ptr;
	DWORD m_Offset;
	HANDLE m_File;
	DWORD m_Size;
public:
	WFile();
	virtual ~WFile();
	static WSERR OpenDataFile(const char *filename);	// �����ݰ� (.wdf)
	WSERR Load(const char *filename);	// ����һ���ļ�
	operator void *() const { return m_Ptr; }
	void *GetPtr() { return m_Ptr; }		// ������ָ��
	void *GetPtr(int offset) { return (void*)((unsigned)m_Ptr+offset); }
	WSERR Open(const char *filename);	// ��һ���ļ�
	WSERR Read(void *buffer,int s,int offset,int *read=0);	// �����ݵ�ָ�� Buffer
	void Skip(int s);					// ���� s �ֽ�
	WSERR Read(void *buffer,int s,int *read=0);		// �����ݵ�ָ�� Buffer
	DWORD GetSize() { return m_Size; }	// ȡ�ļ�����
	DWORD Tell() const;					// ȡ�ļ�ָ��
	void Close();
	bool IsEnd() const { return Tell()>=m_Size; }	// �Ƿ��ļ�β
};

#endif
