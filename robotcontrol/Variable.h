//Variable.h ����ͷ�ļ�
//2010-7-11 11:13:08
#include "Position.h"
#pragma once

//��������
#define _VARIABLE_NO 128

template <typename T>  //������ģ��
class Variable
{
	private:
		T value;       //ȡֵ
		char Note[33]; //ע��

	public:
		Variable()//���캯��
		{
			value = 0;
			strcpy(Note, "");
		}
		char * GetNote()//��ȡNote
		{
			return Note;
		}
		void SetNote(char * newnote)//�޸�Note
		{
			strcpy(Note, newnote);
		}
		T GetValue()//��ȡvalue
		{
			return value;
		}
		void SetValue(T newvalue)//�޸�value
		{
			value = newvalue;
		}
		void Clear()//��ձ���
		{
			value = 0;
			strcpy(Note, "");
		}
		//���������
		Variable operator = (T right)//=
		{
			value = right;
			return *this;
		}
		//+=
		Variable operator += (Variable right)
		{
			value += right.value;
			return *this;
		}
		Variable operator += (T right)
		{
			value += right;
			return *this;
		}
		//-=
		Variable operator -= (Variable right)
		{
			value -= right.value;
			return *this;
		}
		Variable operator -= (T right)
		{
			value -= right;
			return *this;
		}
		//*=
		Variable operator *= (Variable right)
		{
			value *= right.value;
			return *this;
		}
		Variable operator *= (T right)
		{
			value *= right;
			return *this;
		}
		// /=
		Variable operator /= (Variable right)
		{
			value /= right.value;
			return *this;
		}
		Variable operator /= (T right)
		{
			value /= right;
			return *this;
		}
		// &
		Variable operator & (Variable &right)
		{
			value = (value & right.value);
			return *this;
		}
		Variable operator & (T right)
		{
			value = (value & (right%256));
			return *this;
		}
		// |
		Variable operator | (Variable &right)
		{
			value = (value | right.value);
			return *this;
		}
		Variable operator | (T right)
		{
			value = (value | (right%256));
			return *this;
		}
		// ~
		Variable operator ~ ()
		{
			value = ~value;
	        return *this;
		}
		// ^ 
		Variable operator ^ (Variable &right)
		{
			value = (value ^ right.value);
	        return *this;
		}
		Variable operator ^ (T right)
		{
			value = (value ^ (right%256));
        	return *this;
		}
};

//�ַ�����
typedef struct STRINGtype
{
	private:
		char value[17]; //ȡֵ
		char Note[33];  //ע��
		
	public:
		STRINGtype()          //���캯��
		{
			strcpy(value, "");
			strcpy(Note, "");
		}
		char * GetValue()     //��ȡvalue
		{
			return value;
		}
		void SetValue(char * newvalue) //�޸�value
		{
			strcpy(value, newvalue);
		}
		char * GetNote()      //��ȡNote
		{
			return Note;
		}
		void SetNote(char * newnote)  //�޸�Note
		{
			strcpy(Note, newnote);
		}
		void Clear()          //���
		{
			strcpy(value, "");
			strcpy(Note, "");
		}
}_STRINGtype;


//�û������ṹ��
typedef struct UserVariable
{
	public:
		//���ݰ���������˵�����趨�ı���
		Variable<unsigned char> _BYTE[100];    //�ֽ���
		Variable<int>           _INT[100];     //����
		Variable<long int>      _LONGINT[100]; //������
		Variable<float>         _FLOAT[100];   //ʵ����
		STRINGtype              _STRING[100];  //�ַ���
		POStype                 _POS[128];     //Pλ�ñ���
		POStype                 _BPOS[128];    //BPλ�ñ���
		POStype                 _EXPOS[128];   //EXλ�ñ���

		//���ݹ�����˵������ӵı���
		Variable<int>           _R[_R_VARIABLE];          //R�ͱ���
		POStype                 _P[_P_VARIABLE];          //p�ͱ���
		POStype                 _PR[_PR_VARIABLE];        //PR�ͱ���
		int                     R;                        //����ѭ����ȫ��R����
		
	public:
		unsigned char GetBYTEValue(int No)
		{
			return _BYTE[No].GetValue();
		}
		void SetBYTEValue(int No, int value)
		{
			value %= 256;
			_BYTE[No].SetValue(value);
		}
		char * GetBYTENote(int No)
		{
			return _BYTE[No].GetNote();
		}
		void SetBYTENote(int No, char * note)
		{
			_BYTE[No].SetNote(note);
		}
}_UserVariable;
