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

		Description:		���ʱ��ͷ�ļ�
 		Original Author:	�Ʒ�
		Authors:
		Create Time:		2000/12/26
		Modify Time:		2001/7/19

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_TIMER_H
#define _WINDSOUL_TIMER_H

 ///	��ʱ�� (timer.cpp)
/////////////////////////////

/*
class WINDSOUL_API WTimer {
	static int starttime;
	static DWORD CP10K;			// ���֮һ���������
public:
	static void Init();			// ��ʼ��
	static DWORD CyclePerSec;	// һ�� CPU ��������
	static int CPU();			//���� CPU Ƶ��
	static void Reset(int t=0);	// ��ʼ����ʱ��
	static void Start();		//����ʱ����
	static DWORD Stop();		//�õ�ʱ����ʱ��(��С��λ�� 16 ʱ������, ������� P200 �� 5 ��)
	static DWORD GetTime();		//���ص�ǰ����ֵ ( ��С��λΪ 1/10000 ��)
};
*/

class WINDSOUL_API WTimer {

	union uINT64 {
		__int64 time;
		struct {
			DWORD low;
			DWORD high;
		};
	};

	int m_iPriority;
	HANDLE m_hThread;
	uINT64 m_i64Timer;

	DWORD m_StartTime;
public:
	static DWORD s_CP10K;		// ���֮һ���������
	static DWORD s_Cycle;		// 0.1 �� CPU ��������
public:
	WTimer();

	static int CPU();			//���� CPU Ƶ��
	static void SetCpu(DWORD mhz);	// ���� CPU Ƶ��
	void Reset(int t=0);		//��ʼ����ʱ��
	void Start();				//����ʱ����
	DWORD Stop();				//�õ�ʱ����ʱ��(��С��λ�� 16 ʱ������, ������� P200 �� 5 ��)
	DWORD GetTime();			//���ص�ǰ����ֵ (��С��λΪ 1/10000 ��)
};

#endif