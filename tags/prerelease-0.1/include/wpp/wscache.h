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

		Description:		Cache ����
 		Original Author:	�Ʒ�
		Authors:
		Create Time:		2002/3/5
		Modify Time:		2002/3/7

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/


#ifndef _WINDSOUL_CACHE_H_
#define _WINDSOUL_CACHE_H_

#pragma once

#include "wsaddon.h"
#include "wsstring.h"

class WINDSOULADD_API WCacheNodeBase {
protected:
	WString m_Filename;			// ��Ӳ���ϵ��ļ���
	int m_Id;					// �ļ�����Ӧ ID
	int m_Size;					// ���ݳ���
	int m_Ref;					// ���ô���
protected:
	virtual int DoLoad(void *hint)=0;			// ��Ӳ�̼���(�������ݳ���,���� 0 ��ʾ����ʧ��)
	WCacheNodeBase() : m_Id(0), m_Size(0), m_Ref(0) {}
	~WCacheNodeBase() { ASSERT(m_Ref==0); }
public:
	const WString& GetFilename() const { return m_Filename; }
	int GetSize() const { return m_Size; }		// ����ռ���ڴ���
	int GetId() const { return m_Id; }			// ���� ID
	void AddRef() { ++m_Ref; }					// �������ô���
	int Release() { return --m_Ref; }			// �������ô���(�������ô���)
	void Load(void *hint) { if (m_Id) m_Size=DoLoad(hint); }// ����
	virtual int Create(const WString &filename,int id) {	// �����ļ�(��0 ʧ��)
		ASSERT((unsigned)id==WString2ID(filename));
		m_Filename=filename;
		m_Id=id;
		AddRef();
		return 0;
	};
};

template <typename T>
class WCacheNode : public WCacheNodeBase {
protected:
	T *m_Object;				// ����

	WCacheNode() : m_Object(0) {};
public:
	~WCacheNode() { Unload(); }
	void Unload() { delete m_Object; m_Object=0; }	// ж�ض�������
	T* Object() const { return m_Object; }		// ��ȡ����
	T* Quest(void *hint) {			// Quest ����, ����ָ��
		if (!m_Object) {
			Load(hint);
		}
		return m_Object;
	}
};

class WCacheBase;

class WINDSOULADD_API WCacheNodeLink {
public:
	WCacheNodeLink(WCacheBase *container) { m_Next=this, m_Prev=this, m_Container=container; }
	void Unlock() { MoveTo(InRam); }			// Unlock �Լ�
	virtual void Release()=0;					// �ͷ��Լ�(�������ô���)
	friend WCacheBase;
protected:
	enum Status { Locked=0, InRam=1, OutRam=2, Garbage=3 };
	virtual ~WCacheNodeLink();
	virtual WCacheNodeLink* Clone() const=0;	// Clone һ���Լ�
	virtual int GetSize() const=0;				// ���ؽڵ�ռ�ÿռ�Ĵ�С
	virtual bool IsFile(int id) const=0;		// �ж��Ƿ�������ļ�
	virtual void AddRef()=0;					// �������ô���
	virtual void Unload()=0;					// ж������
	virtual WCacheNodeLink* AllocNode(const WString &name,int id);		// ����һ���ڵ�, �������Լ��ĺ���

	WCacheNodeLink* GetNode(int id);			// ���ļ����������ڵ�
	void LinkHead(WCacheNodeLink *link);		// ��һ��������ǰ��
	void LinkNext(WCacheNodeLink *node);		// �ѽڵ��������Լ��ĺ���
	void ReleaseThis();							// �ѽڵ�������(�ǵ�ɾ��!)
	bool IsEmpty() const { return m_Next==this; }	// �Ƿ�Ϊ��
	void MoveTo(Status p);						// �ƶ��Լ���������ָ��λ��

	WCacheNodeLink *m_Next;
	WCacheNodeLink *m_Prev;
	WCacheBase *m_Container;					// ����
};

class WINDSOULADD_API WCacheBase {
protected:
	WCacheNodeLink *m_Link[4];				// ��������
	int m_CacheSize;						// Cache ��С
	int m_CacheUsed;						// Cache ʹ���˵Ĵ�С
	friend class WCacheNodeLink;
protected:
	WCacheBase(int size) : m_CacheSize(size),m_CacheUsed(0) {}	// Ӧ��������������ʼ��
	~WCacheBase();							// �ͷ����нڵ�
	void GC();								// ��������
	WCacheNodeLink *QuestFileInNeed(const WString &name);	// ������Ҫ����һ���ļ�
public:
	void LoadNode(WCacheNodeLink *node) {
		node->MoveTo(WCacheNodeLink::Locked);
		m_CacheUsed+=node->GetSize();
		GC();
	}
	void UnLock();							// UnLock ���ϴ� Lock �Ľڵ�
	int GetCacheUsed() const { return m_CacheUsed; }	// ���� Cache ʹ�����
};

template <typename T, typename NodeT>
class WNode : public WCacheNodeLink {
public:
	WNode(WCacheBase *container) : WCacheNodeLink(container) , m_Node(0) {}
	void AddRef() { m_Node->AddRef(); }						// �������ô���
	void Release() {								// �ͷ��Լ�(�������ô���)
		if (m_Node->Release()==0) 
			MoveTo(Garbage);
	}
	T* Quest(void *hint=0) { 									// ����һ������, �϶����ڴ�
		T *p=m_Node->Object();
		if (p) {
			MoveTo(Locked);
		}
		else {
			p=m_Node->Quest(hint);
			if (p)
				m_Container->LoadNode(this);
		}
		return p; 
	}
	const WString& GetFilename() const { return m_Node->GetFilename(); }
	int GetSize() const { return m_Node->GetSize(); }		// ���ؽڵ�ռ�ÿռ�Ĵ�С
	friend WCacheBase;
protected:
	~WNode() { 
		delete m_Node; 
	}
	WCacheNodeLink* Clone() const {							// Clone һ���Լ�
		WNode<T,NodeT>* p=new WNode<T,NodeT>(m_Container); 
		p->m_Node=new NodeT;
		return p;
	}	
	WCacheNodeLink* AllocNode(const WString &name,int id) {	// ����һ���ڵ�, �������Լ��ĺ���
		WNode<T,NodeT> *p=(WNode<T,NodeT>*)WCacheNodeLink::AllocNode(name,id);
		p->m_Node->Create(name,id);
		return p;
	}
	bool IsFile(int id) const { return id==m_Node->GetId(); }// �ж��Ƿ�������ļ�
	void Unload() { m_Node->Unload(); }						// ж������

	WCacheNode<T> *m_Node;
};


template <typename T, typename NodeT>
class WCache : public WCacheBase {
public:
	WCache(int size) : WCacheBase(size) {			// ��ʼ�� m_Link[4]
		for (int i=0;i<4;i++) {
			m_Link[i]=new WNode<T,NodeT>(this);
		}
	}
	WNode<T,NodeT> *Quest(const WString &name) {	// ����һ���ļ�
		return (WNode<T,NodeT>*)QuestFileInNeed(name); 
	}	
};

#endif