//DataPacket.h
//����ͨ�����ݰ���ͷ�ļ�
#pragma once
#include "Position.h"
#include "head.h"
#include "Program.h"

//����A : ʾ��һ����
struct A_information
{
private:
//	int FrameType;     //��������,0:�ؽ�����; 1:������; 2:�û�����; 3��������
//	int FrameNo;       //�������
	char Key;          //��ֵS+ ~ T- : 'A' ~ 'L'
//	double Speed;      //�����ٶ�, ���ٶ�: ��/s, ���ٶ�: mm/s
//�ٶ�ȡ��ROBOT��_handspeed

public:
	/***************************
	A_information()
	���캯��
	***************************/
	A_information()
	{
//		FrameType = -1;//����ϵ������Ϊ��Ч
//		FrameNo = -1;//����ϵ������Ϊ��Ч
		Key = NULL;//��ֵ��Ϊ��
//		Speed = 0;//�ٶ���Ϊ0
	}//A_information()

	/****************************
	~A_information()
	��������
	****************************/
	~A_information()
	{}//~A_information()

	/****************************
	int GetFrameType()
	��ȡ��������
	-----------------------------
	���� : ��������
	
	****************************/
//	int GetFrameType()
//	{
//		return this->FrameType;
//	}//GetFrameType()

	/****************************
	void SetFrameType(int NewType)
	�޸�����ϵ����
	-----------------------------
	NewType : �µ�����ϵ���� 
	****************************/
//	void SetFrameType(int NewType)
//	{
//		this->FrameType = NewType;
//	}//SetFrameType()

	/****************************
	int GetFrameNo()
	��ȡ����ϵ����
	-----------------------------
	���� : ����ϵ����
	****************************/
//	int GetFrameNo()
//	{
//		return this->FrameNo;
//	}//GetFrameNo()

	/****************************
	void SetFrameNo(int NewNo)
	�޸�����ϵ����
	-----------------------------
	NewNo : �µ�����ϵ����
	****************************/
//	void SetFrameNo(int NewNo)
//	{
//		this->FrameNo = NewNo;
//	}//SetFrameNo()

	/***************************
	char GetKey()
	��ȡ��ֵ
	----------------------------
	���� : ��ֵ
	***************************/
	char GetKey()
	{
		return this->Key;
	}//GetKey()

	/***************************
	void SetKey(char NewKey)
	�޸ļ�ֵ
	----------------------------
	NewKey : �¼�ֵ
	***************************/
	void SetKey(char NewKey)
	{
		this->Key = NewKey;
	}//SetKey()

	/***************************
	double GetSpeed()
	��ȡ�ٶ�ֵ
	----------------------------
	���� : �ٶ�ֵ
	***************************/
//	double GetSpeed()
//	{
//		return this->Speed;
//	}//GetSpeed()

	/***************************
	void SetSpeed(double NewSpeed)
	�޸��ٶ�ֵ
	----------------------------
	NewSpeed : �µ��ٶ�ֵ
	***************************/
//	void SetSpeed(double NewSpeed)
//	{
//		this->Speed = NewSpeed;
//	}//SetSpeed()

};//A_information

//����B : ���ƻ������˶���һ����֪��
struct B_information
{
private:
//	int InterType;//�岹��ʽ:0�ؽڲ岹MOVJ, 1ֱ�߲岹MOVL, 2Բ���岹MOVC, 3���߲岹MOVS
//�岹��ʽĬ��ΪMOVJ
//	double Speed; //�岹�ٶ�, Բ��: ��/s, ����: mm/s
//�ٶ�Ϊ�ֶ��ٶ�,��Robot�µ�_handspeed
//	Position Target[2];//Ŀ��λ����Ϣ; MOVJ/MOVLֻȡTarget[0]; MOVC/MOVSȡTarget����������
	int Target;//Ŀ���,0:����ԭ��, 1:�ڶ�ԭ��, 2:����ԭ��
	

public:
	/*****************************
	B_information()
	���캯��
	*****************************/
	B_information()
	{
//		InterType = -1;//�岹��ʽ��Ϊ��Чֵ
//		Speed = 0.0;// �ٶ���Ϊ0
		Target = -1;
	}//B_information()

	/******************************
	~B_information()
	��������
	******************************/
	~B_information(){}//~B_information()

	/******************************
	int GetTarget()
	��ȡĿ������
	******************************/
	int GetTarget()
	{
		return Target;
	}//int GetTarget()

	/******************************
	void SetTarget(int value)
	�޸�Ŀ������
	----------- ���� --------------
	******************************/
	void SetTarget(int value)
	{
		Target = value;
	}//void SetTarget()

	/******************************
	int GetInterType()
	��ȡ�岹��ʽ
	-------------------------------
	���� : �岹��ʽ
	******************************/
//	int GetInterType()
//	{
//		return this->InterType;
//	}//GetInterType()

	/******************************
	void SetInterType(int Type)
	�޸Ĳ岹��ʽ
	-------------------------------
	Type=0 : �ؽڲ鲹
	Type=1 : ֱ�߲鲹
	Type=2 : Բ���鲹
	Type=3 : ���߲鲹
	-------------------------------
	Type : �µĲ岹��ʽ
	******************************/
//	void SetInterType(int Type)
//	{
//		this->InterType = Type;
//	}//SetInterType()

	/******************************
	double GetSpeed()
	��ȡ�����ٶ�
	-------------------------------
	���� : �����ٶ�
	******************************/
//	double GetSpeed()
//	{
//		return this->Speed;
//	}//GetSpeed()

	/******************************
	void SetSpeed(double NewSpeed)
	�޸������ٶ�
	-------------------------------
	NewSpeed : �µ������ٶ�
	******************************/
//	void SetSpeed(double NewSpeed)
//	{
//		this->Speed = NewSpeed;
//	}//SetSpeed()

	/******************************
	Position GetTarget(int No)
	��ȡĿ��λ�õĵ�No������
	-------------------------------
	No : ����ȡ��������Target[]�е��±�
	No = (0 ~ 2)
	******************************/
//	Position GetTarget(int No)
//	{
//		Position Result;
//		switch(No)
//		{
//		case 0://��ȡTarge[0]
//			{
//				Result = this->Target[0];
//				break;
//			}
//		case 1://��ȡTarge[1]
///			{
///				Result = this->Target[1];
//				break;
//			}
//		default:break;
//		}
//		return Result;
//	}//GetTarget()

	/******************************
	bool SetTarget(int No, Position Pos)
	�޸�Ŀ��λ�õĵ�No������
	-------------------------------
	No : ����ȡ��������Target[]�е��±�,NO=(0 - 2)
	Pos: Target[No]��������
	******************************/
//	bool SetTarget(int No, Position Pos)
//	{
///		bool Result = true;
//		switch(No)
//		{
//		case 0://�޸�Target[0]
//			{
//				this->Target[0] = Pos;
//				break;
//			}
//		case 1://�޸�Target[1]
//			{
//				this->Target[1] = Pos;
//				break;
//			}
//		default:
//			{
//				Result = false;
//				break;
//			}
//		}
//		return Result;
//	}//SetTarget()

	
};//B_information

//����C : ����λ��������
struct C_information
{
public:
	bool state;
	Position Pos;//λ������
public:
};//C_information

//����D : ǰ��
struct D_information
{
private:
	char Key;//��ֵ��'A'��ǰ����'B'������+ǰ����'C'��ת��+ǰ��

public:
	D_information()
	{
		Key = NULL;
	}//D_information()

	//��ȡKey
	char GetKey()
	{
		return Key;
	}//GetKey()

	//�޸�Key
	void SetKey(char value)
	{
		Key = value;
	}//SetKey()
};//D_information

//���� E : ���˶���
struct E_information
{};//E_information

//����F : ����
struct F_information
{};//F_information

//����G : ������
struct G_information
{};//G_information

//����H : ֹͣ
struct H_information
{};//H_information

//����I : ��ͣ
struct I_information
{};//I_information




/********************DataPacket**************************/
struct DataPacket
{
	//���ݳ�Ա
private:
	char Mission;    //�������
public:
	//���ݶ�
	Program m_program;//��ִ�еĳ���
	Robot ROBOT;//ȫ�ֱ���ROBOT
	UserVariable VARIABLE;//ȫ�ֱ���VARIABLE

	//������Ϣ
	A_information A_Mission;//ʾ��һ����
	B_information B_Mission;//�˶���ĳ��ԭ��
	C_information C_Mission;//����λ������
	D_information D_Mission;//"ǰ��"����
	E_information E_Mission;//"����"����
	F_information F_Mission;//"����"����
	G_information G_Mission;//"������"����
	H_information H_Mission;//"ֹͣ"����
	I_information I_Mission;//"��ͣ"����

	//������Ա
public:
	/************************
	DataPacket()
	���캯��
	************************/
	DataPacket()
	{
		Mission = 'Z';//'Z' ��ʱ��Ϊ������Ĵ��� 
	}//DataPacket()

	/*************************
	~DataPacket()
	��������
	*************************/
	~DataPacket()
	{}//~DataPacket()

	/**************************
	char GetMission()
	��ȡ�������
	---------------------------
	����:
	�������
	**************************/
	char GetMission()
	{
		return this->Mission;
	}//GetMission()

	/**************************
	void SetMission(char NewMission)
	�޸��������
	---------------------------
	NewMission : �µ��������
	**************************/
	void SetMission(char NewMission)
	{
		this->Mission = NewMission;
	}//SetMission()

};//DataPacket