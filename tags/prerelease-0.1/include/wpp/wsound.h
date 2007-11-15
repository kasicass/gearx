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

		Description:		�������ͷ�ļ�
 		Original Author:	�Ʒ�
		Authors:
		Create Time:		2001/8/7
		Modify Time:		2002/3/11

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#pragma once

#ifdef _BCB
    #ifndef _LIB
        #pragma comment (lib,"wppsnd.lib")
    #endif        
    #define WINDSOULSOUND_API
#else

#if defined(WINDSOULSOUND_STATICLIB) || defined(_LIB) || defined(_API) || defined(WINDSOULSOUND_NODLL)
	#define WINDSOULSOUND_API
	#if !defined(_LIB) && !defined(_API) && !defined(WINDSOULSOUND_NODLL)
		#pragma comment (lib,"wssnds.lib")
	#endif
#elif defined(WSOUND_EXPORTS)
	#define WINDSOULSOUND_API __declspec(dllexport)
#else
	#define WINDSOULSOUND_API __declspec(dllimport)
    #ifdef _DEBUG
	   	#pragma comment (lib,"wsoundd.lib")
    #else
	   	#pragma comment (lib,"wsound.lib")
  	#endif
#endif

#endif

class WSample;
struct WSampleStruct;
class WMusic;
struct WMusicStruct;
class WSoundDevice;

#define _ERR_WAVE 'w'
#define WS_INVALIDWAVETYPE MAKE_ERR(_ERR_WAVE,'TYP')
#define WS_UNSUPPORTWAVETYPE MAKE_ERR(_ERR_WAVE,'USP')
#define WS_DIRECTSOUNDERROR MAKE_ERR(_ERR_WAVE,'DSD')

class WINDSOULSOUND_API WSound {
	enum { MaxSample=256, MaxMix=15, c_Channels=2, c_SPS=22050, c_BPS=16 };

	WSoundDevice *m_pDevice;
	int m_CurrentMix;
	WSample *m_pCurrentSample[MaxMix];

	friend class WSampleLoader;
	friend class WSample;
	friend class WMusic;

	void Play(WSample *s);
	bool IsPlaying(void *buf);
	void DeletePlayingSample(WSample *s);

	void * ReadWav(const char *filename,int &rSize);	// ��һ�� wav �ļ����� dsound buffer, ����. ����¼����
public:
	enum WPlayMode { play_normal, play_once, play_loop, play_over };

	WSound(HWND h_wnd,int cachesize=0x800000);	// Cache ��СĬ�� 8M
	~WSound();

	bool IsAvailable() const;
	void TurnOn();
	void TurnOff();

	void SetVolume(long vol);		// ��������
	long GetVolume() const;			// ��ȡ����

	WSample* LoadSample(const char *filename);
	void PlaySample(const char *filename,long vol=0);
	WMusic* OpenMusic(const char *filename);
	WMusic* GetMusic();
};

class WINDSOULSOUND_API WSample {
	WSound *m_DS;				// Dsound ָ��
	WSampleStruct *m_SS;		// SampleStruct ָ��


	WSample(WSound *dev);

	void DuplicateBuffer();			// ����һ�� SoundBuffer
	bool IsPlaying();				// �Լ��Ƿ��ڲ���

	friend class WSound;
public:
	~WSample();
	void SetVolume(long vol);		// ��������
	long GetVolume() const;			// ��ȡ����

	void Play(WSound::WPlayMode mode=WSound::play_normal);		// ����
	void Stop();				// ֹͣ
};

class WINDSOULSOUND_API WMusic {
	enum { c_BufferSize=221184 };
	WSound *m_DS;				// DSound ָ��
	WMusicStruct *m_pMS;		// ����ָ��

	friend class WSound;

	static unsigned long __stdcall MusicThread(void *p);

	WSERR OpenFile(const char *filename);
	void InitBuffer();
	void ReadNext(void *buffer);
	void Release();
	void StopBuffer();
	WMusic(WSound *ws);
	~WMusic();
public:
	void SetVolume(long vol);		// ��������
	long GetVolume() const;			// ��ȡ����

	void Play(WSound::WPlayMode mode=WSound::play_loop);		// ����
	bool IsAvailable() const;
	void Stop();
	bool IsEnd() const;
};

