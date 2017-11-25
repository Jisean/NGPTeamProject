#pragma once
#include "Obj.h"

template<typename T>
class CObjFactory
{
public:
	static CObj*	CreateObj()
	{
		CObj*	pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	///////////////////////////////////
	static CObj*	CreateObj(D3DXVECTOR3 vPos)
	{
		CObj*	pObj = new T;
		pObj->Initialize();
		pObj->SetPos(vPos);

		return pObj;
	}

	static CObj*	CreateObj(float _fX, float _fY)
	{
		CObj*	pObj = new T;
		pObj->Initialize();
		pObj->SetPos(_fX, _fY);

		return pObj;
	}
	////////�Ϲ� ��ü ������//////////

	//////////////////////////////////
	static CObj*	CreateObj(D3DXVECTOR3 vPos, FIREWAY _way)
	{
		CObj*	pObj = new T;
		pObj->Initialize();
		pObj->SetPos(vPos, _way);

		return pObj;
	}

	static CObj*	CreateObj(float _fX, float _fY, FIREWAY _way)
	{
		CObj*	pObj = new T;
		pObj->Initialize();
		pObj->SetPos(_fX, _fY, _way);

		return pObj;
	}
	////////////���� ������///////////


	//////////////////////////////////
	static CObj*	CreateObj(D3DXVECTOR3 vPos, HUDTYPE _type)
	{
		CObj*	pObj = new T;
		pObj->Initialize();
		pObj->SetPos(vPos, _type);

		return pObj;
	}

	static CObj*	CreateObj(D3DXVECTOR3 vPos, HUDNUMTYPE _type)
	{
		CObj*	pObj = new T;
		pObj->Initialize();
		pObj->SetPos(vPos, _type);

		return pObj;
	}
	///////////�Ⱦ�ui ������/////////

	/////////////////////////////////

	static CObj*	CreateObj(D3DXVECTOR3 vPos, BOSSHP _type)
	{
		CObj*	pObj = new T;
		pObj->Initialize();
		pObj->SetPos(vPos, _type);

		return pObj;
	}

	/////////����hp�� ������/////////

	/////////////////////////////////

	static CObj*	CreateObj(D3DXVECTOR3 vPos, PICKUP _type)
	{
		CObj*	pObj = new T;
		pObj->Initialize();
		pObj->SetPos(vPos, _type);

		return pObj;
	}
	////////�Ⱦ������� ������////////

	/////////////////////////////////
	static CObj*	CreateObj(D3DXVECTOR3 vPos, PASSIVEITEM _type)
	{
		CObj*	pObj = new T;
		pObj->Initialize();
		pObj->SetPos(vPos, _type);

		return pObj;
	}
	////////�ڵ������� ������///////

	////////////////////////////////


	///////���������� ������////////

	////////////////////////////////

	static CObj*	CreateObj2(float _fX, float _fY, PASSIVEITEM _type)
	{
		CObj*	pObj = new T;
		pObj->Initialize();
		pObj->SetPos2(_fX, _fY, _type);

		return pObj;
	}
	///////�ڽ�Ƭ ������////////////

	////////////////////////////////
	static CObj*	CreateObj(float _fX, float _fY, D3DXVECTOR3 _vDir, float Angle)
	{
		CObj*	pObj = new T;
		pObj->Initialize();
		pObj->SetPos(_fX,_fY,_vDir,Angle);

		return pObj;
	}
	////////�� �Ѿ� ������//////////

	////////////////////////////////

	static CObj*	CreateObj(D3DXVECTOR3 vPos, EFFECT _type)
	{
		CObj*	pObj = new T;
		pObj->Initialize();
		pObj->SetPos(vPos, _type);

		return pObj;
	}
	///////����Ʈ ������////////////

public:
	CObjFactory(void){	}
	~CObjFactory(void){	}
};
