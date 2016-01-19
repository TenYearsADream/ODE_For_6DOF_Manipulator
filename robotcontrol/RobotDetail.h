//:RobotDeatil.h 
//��ɻ�����ʵ��ĸ�������
//2010-7-28 8:39:01

/*************************************************************************************
//���嵥:SafeMode    SpecialRun    Interfere    IODetail    IO    AlarmDetail    Alarm
//       ToolFrame   UserFrame
*************************************************************************************/

#include "Position.h"
#include "Macro.h"
#include <time.h>
#pragma once

typedef struct SafeMode//��ȫģʽ��0Ϊ����ģʽ��1�༭ģʽ��2����ģʽ
	{
	private:
		int SafeModeLevel;//ת��������ģʽ������Ҫ����.0Ϊ������1Ϊ�༭��2Ϊ����
		char EditorPassword[9];
		char AdministratorPassword[9];
		
		//�޸İ�ȫ�ȼ�
		void SetLevel(int newlevel)
		{	
			SafeModeLevel = newlevel;
		}
		//�޸ı༭����
		bool SetEditorPassWord(char * newpassword)
		{
			if(strlen(newpassword) > 8)
			{
				return false;
			}

			strcpy(EditorPassword, newpassword);
			return true;
		}
		//�޸Ĺ�������
		bool SetAdministratorPassword(char * newpassword)
		{
			if(strlen(newpassword) > 8)
			{
				return false;
			}

			strcpy(AdministratorPassword, newpassword);
			return true;
		}

	public:
		//��ȡ��ȫ�ȼ�
		int GetLevel()
		{
			return SafeModeLevel;
		}
		//����ȷ��,��ȷtrue,����false
		bool CheckPassword(int mode, char * password)
		{
			switch(mode)
			{
			case 1:
				{
					if(strcmp(EditorPassword, password))//�༭����
					{
						return false;//��������
					}
					else
					{
						return true;
					}
					break;
				}
			case 2:
				{
					if(strcmp(AdministratorPassword, password))//�༭����
					{
						return false;//��������
					}
					else
					{
						return true;
					}
					break;
				}
			default:break;
			}
			return false;
		}
		//�޸İ�ȫ�ȼ�,�ɹ�true,ʧ��false
		bool SetLevel(int newlevel, char * password)
		{
			if(SafeModeLevel >= newlevel)//�ɸ�Ȩ�޵ȼ��л�����Ȩ�޵ȼ�������Ҫ����
			{
				SafeModeLevel = newlevel;
				return true;
			}
			switch(newlevel)
			{
			case 1://�л����༭ģʽ
				{
					bool state = this->CheckPassword(1, password);
					if(state)
					{
						SafeModeLevel = 1;//�༭ģʽ
						return true;
					}
					else
					{
						return false;
					}
					break;
				}
			case 2://�л�������ģʽ
				{
					bool state = this->CheckPassword(2, password);
					if(state)
					{
						SafeModeLevel = 2;//����ģʽ
						return true;
					}
					else
					{
						return false;
					}
					break;
				}
			default:break;
			}
			return false;
		}
		//�޸�����,�ɹ�true,ʧ��false
		bool SetPassword(int level, char * password, char * newpassword)
		{
			switch(level)
			{
			case 0://����ģʽ
				return true;
			case 1://�༭ģʽ
				{
					if(this->CheckPassword(1, password))//ԭ������ȷ
					{
						if(this->SetEditorPassWord(newpassword))//�޸�����
							return true;//�޸ĳɹ�
						else
							return false;//�޸�ʧ��
					}
					break;
				}
			case 2://����ģʽ
				{
					if(this->CheckPassword(2, password))//ԭ������ȷ
					{
						if(this->SetAdministratorPassword(newpassword))//�޸�����
							return true;//�޸ĳɹ�
						else
							return false;//�޸�ʧ��
					}
					break;
				}
			default:break;
			}
			return false;
		}

		//���캯��
		SafeMode()
		{ 
			SafeModeLevel = 0;                         //��ʼ��Ϊ����ģʽ
			strcpy(EditorPassword, "00000000");        //�༭���룬��ʼ��Ϊ00000000(8��0)
			strcpy(AdministratorPassword, "99999999"); //�������룬��ʼ��Ϊ99999999(8��9)
		}
}SAFEMODE;

struct SpecialRun//��������
{
private:
	bool Low;      //��������
	bool Limit;    //��������
	bool Null;     //������
	bool Lock;     //��е��������
	bool Check;    //�������
public:
	SpecialRun()    //���캯��
	{
		Low = false;
		Limit = false;
		Null = false;
		Lock = false;
		Check = false;
	}

	bool GetLow() //��ȡLow
	{return Low;}

	void SetLow(bool value)//�޸�Low
	{Low = value;}

	bool GetLimit()//��ȡLimit
	{return Limit;}

	void SetLimit(bool value)//�޸�Limit
	{Limit = value;}

	bool GetNull()//��ȡNull
	{return Null;}

	void SetNull(bool value)//�޸�Null
	{Null = value;}

	bool GetLock()//��ȡLock
	{return Lock;}

	void SetLock(bool value)//�޸�Lock
	{Lock = value;}

	bool GetCheck()//��ȡCheck
	{return Check;}

	void SetCheck(bool value)//�޸�Check
	{Check = value;}
};

//Interfere������
struct Interfere
{
private:
	bool Type;     //trueΪ�����������,falseΪ�������	

public:
	Position Max;  //���ֵ
	Position Min;  //��Сֵ

	Interfere()
	{
		Type = true;
	}

	bool GetType()//��ȡType
	{return Type;}

	void SetType(bool newType)//�޸�Type
	{Type = newType;}
};

//IO�������,����ͨ��
struct IODetail
{
private:
	bool Value;
	char Note[33];

public:
	IODetail()
	{
		Value = false;
		strcpy(Note, "");
	}

	bool GetValue()//��ȡVale
	{return Value;}

	void SetValue(bool newValue)//�޸�Value
	{Value = newValue;}

	char *GetNote()//��ȡNote
	{return Note;}

	void SetNote(char * newNote)
	{
		strcpy(Note, newNote);
	}

};

//IO,ÿ��ͨ��8��
struct IO
{
	IODetail io[_IO_SUM];

public:
	/********************
	��ʾIO,��IO��Ϣת��Ϊ�ַ�������
	string Show()
	********************/
	string Show()
	{
		string result="";
		for(int i=_IO_SUM-1; i>=0; --i)
		{
			if(this->io[i].GetValue())
			{
				result += "1";
			}
			else
			{
				result += "0";
			}

			if(4==i)
			{
				result += "_";
			}
		}
		return result;
	}
};

//AlarmDetail����ϸ��
struct AlarmDetail
{
private:
	char  Time[25];    //��������ʱ��
	char  ProName[9];  //���������ĳ���
	int   LineNo;      //��������������
	char  Note[33];    //��������

public:
	/*****************************
	AlarmDetail()
	------------------------------
	˵��: 
	���캯��
	*****************************/
	AlarmDetail()
	{
	}

	/*******************************
	void SetTime()
	--------------------------------
	˵��:
	�޸ı���ʱ��
	*******************************/
	void SetTime()
	{
		time_t *tp,t;
		tp = &t;
		time(tp);
		strcpy(Time, ctime(tp));//�õ�ʱ���ַ���
		Time[24]='\0';
	}

	/*******************************
	char *GetTime()
	--------------------------------
	˵��:
	��ȡʱ��
	--------------------------------
	����:
	����ʱ���ַ���
	*******************************/
	char *GetTime()
	{
		return Time;
	}

	/*******************************
	void SetProName(char * name)
	--------------------------------
	˵��:
	�޸ķ��������ĳ�����
	--------------------------------
	����:
	name: ������
	*******************************/
	void SetProName(char *name)
	{
		strcpy(ProName, name);
	}

	/*******************************
	char *GetProName()
	--------------------------------
	˵��:
	��ȡ���������ĳ�����
	*******************************/
	char *GetProName()
	{
		return ProName;
	}

	/*******************************
	void SetLineNo(int no)
	--------------------------------
	˵��:
	�޸ķ����������к�
	--------------------------------
	����:
	no: �����������к�
	*******************************/
	void SetLineNo(int no)
	{
		LineNo = no;
	}

	/*******************************
	int GetLineNo()
	--------------------------------
	˵��:
	��ȡ�����������к�
	--------------------------------
	����:
	no : �����������к�
	*******************************/
	int GetLineNo()
	{
		return LineNo;
	}

	/*******************************
	void SetNote(char *note)
	--------------------------------
	˵��:
	�޸ı�������
	--------------------------------
	����:
	note: ��������
	*******************************/
	void SetNote(char *note)
	{
		strcpy(Note, note);
	}

	/*******************************
	char *GetNote()
	--------------------------------
	˵��:
	��ȡ��������
	--------------------------------
	����:
	��������
	*******************************/
	char *GetNote()
	{
		return Note;
	}

	/*******************************
	void Clear()
	--------------------------------
	˵��:
	��ձ�����¼
	*******************************/
	void Clear()
	{
		strcpy(Time, "");
		strcpy(ProName, "");
		strcpy(Note, "");
		LineNo = 0;
	}

	/********************************
	string Show()
	---------------------------------
	˵��:
	��������Ϣ��string��ʽ����
	---------------------------------
	����:
	������Ϣת���ɵ�string
	********************************/
	string Show()
	{
		string result;
		result += Time;
		result += "   ";
		result += ProName;
		result += "   ";

		char lineno[2];
		sprintf(lineno, "%d   ", LineNo);
		result += lineno;

		result += Note;

		return result;		 
	}
};

//����
struct Alarm
{
public:
	AlarmDetail Serious[_ALARM_SUM]; //���ر���
	AlarmDetail Slight[_ALARM_SUM];  //��΢����
	AlarmDetail System[_ALARM_SUM];  //ϵͳ����
	AlarmDetail User[_ALARM_SUM];    //�û�����
	AlarmDetail OffLine[_ALARM_SUM]; //���߱���

public:
	/*********************************
	void Clear(int type)
	----------------------------------
	˵��:
	��ձ���
	----------------------------------
	����:
	type=0: ������б�����Ϣ
	type=1: ���Serious����
	type=2: ���Slight����
	type=3: ���System����
	type=4: ���User����
	type=5: ���OffLine����
	**********************************/
	void Clear(int type)
	{
		switch(type)
		{
		case 0://�������
			{
				for(int i=0; i<_ALARM_SUM; ++i)
				{
					Serious[i].Clear();
					Slight[i].Clear();
					System[i].Clear();
					User[i].Clear();
					OffLine[i].Clear();
				}
				break;
			}
		case 1://���Serious
			{
				for(int i=0; i<_ALARM_SUM; ++i)
				{
					Serious[i].Clear();
				}
				break;
			}
		case 2://���Slight
			{
				for(int i=0; i<_ALARM_SUM; ++i)
				{
					Slight[i].Clear();
				}
				break;
			}
		case 3://���System
			{
				for(int i=0; i<_ALARM_SUM; ++i)
				{
					System[i].Clear();
				}
				break;
			}
		case 4://���User
			{
				for(int i=0; i<_ALARM_SUM; ++i)
				{
					User[i].Clear();
				}
				break;
			}
		case 5://���OffLine
			{
				for(int i=0; i<_ALARM_SUM; ++i)
				{
					OffLine[i].Clear();
				}
				break;
			}
		default:break;
		}
	}

	/******************************************
	string Show(int type)
	-------------------------------------------
	˵��: 
	������ʾ������Ϣ
	-------------------------------------------
	����:
	type=1: ��ʾSerious
	type=2: ��ʾSlight
	type=3: ��ʾSystem
	type=4: ��ʾUser
	type=5: ��ʾOffLine
	-------------------------------------------
	����ֵ:
	������������б�����Ϣת��Ϊһ��string����
	******************************************/
	string Show(int type)
	{
		string result;
		switch(type)
		{
		case 1://Serious
			{
				for(int i=0,j=1; i<_ALARM_SUM; ++i)
				{
					char *ProName = Serious[i].GetProName();
					if(strcmp(ProName , ""))//��Ϊ��
					{
						char No[10];
						sprintf(No, "%d   ", j);
						result += No;//���
						result += Serious[i].Show();//����
						result += "\r\n";//����

						++j;
					}
				}
				break;
			}
		case 2://Slight
			{
				for(int i=0,j=1; i<_ALARM_SUM; ++i)
				{
					char *ProName = Slight[i].GetProName();
					if(strcmp(ProName , ""))//��Ϊ��
					{
						char No[10];
						sprintf(No, "%d   ", j);
						result += No;//���
						result += Slight[i].Show();//����
						result += "\r\n";//����

						++j;
					}
				}
				break;
			}
		case 3://System
			{
				for(int i=0,j=1; i<_ALARM_SUM; ++i)
				{
					char *ProName = System[i].GetProName();
					if(strcmp(ProName , ""))//��Ϊ��
					{
						char No[10];
						sprintf(No, "%d   ", j);
						result += No;//���
						result += System[i].Show();//����
						result += "\r\n";//����

						++j;
					}
				}
				break;
			}
		case 4://User
			{
				for(int i=0,j=1; i<_ALARM_SUM; ++i)
				{
					char *ProName = User[i].GetProName();
					if(strcmp(ProName , ""))//��Ϊ��
					{
						char No[10];
						sprintf(No, "%d   ", j);
						result += No;//���
						result += User[i].Show();//����
						result += "\r\n";//����

						++j;
					}
				}
				break;
			}
		case 5://OffLine
			{
				for(int i=0,j=1; i<_ALARM_SUM; ++i)
				{
					char *ProName = OffLine[i].GetProName();
					if(strcmp(ProName , ""))//��Ϊ��
					{
						char No[10];
						sprintf(No, "%d   ", j);
						result += No;//���
						result += OffLine[i].Show();//����
						result += "\r\n";//����

						++j;
					}
				}
				break;
			}
		default:break;
		}
		return result;
	}

};

//��������
//��һ��Position�������������湤����������
struct ToolFrame
{
public:
	Position data; //���ڱ�ʾ����ϵ��position������
	char Name[9];  //����ϵ����

public:

	/****************************
	bool SetName(char *name)
	-----------------------------
	˵��:
	�޸�����ϵ����
	-----------------------------
	����:
	name: ������
	-----------------------------
	����:
	true : �޸ĳɹ�
	false: �ַ������ȹ���,�޸�ʧ��
	****************************/
	bool SetName(char *name)
	{
		if(strlen(name) > 8)
		{
			return false;
		}
		else
		{
			strcpy(Name, name);
			return true;
		}		
	}

	/****************************
	char *GetName()
	-----------------------------
	˵��:
	��ȡ����ϵ����
	-----------------------------
	����:
	����ϵ����
	****************************/
	char *GetName()
	{
		return Name;
	}

	/****************************
	Position GetData()
	-----------------------------
	˵��: 
	����data����
	-----------------------------
	����:
	�������ڱ�ʾ����ϵ��data����
	****************************/
	Position GetData()
	{
		return data;
	}

	/****************************
	ToolFrame()
	-----------------------------
	˵��:
	���캯��
	****************************/
	ToolFrame()
	{
		strcpy(Name, "");
	}
};

struct UserFrame
{
private:
	char      Name[9]; //����ϵ����
public:
	Position  ORG;     //Զ��
	Position  _XX;      //X���ϵ�һ��
	Position  XY;      //XYƽ���ϵ�һ��	

public:
	/********************************
	bool SetName(char *name)
	---------------------------------
	˵��:
	�޸�����ϵ����
	---------------------------------
	����:
	name: ����ϵ����
	---------------------------------
	����:
	true : �޸����Ƴɹ�
	false: ���Ƴ��ȹ���,�޸�ʧ��
	********************************/
	bool SetName(char *name)
	{
		if(strlen(name) > 8)
		{
			return false;
		}
		else
		{
			strcpy(Name, name);
			return true;
		}
	}

	/********************************
	char *GetName()
	---------------------------------
	˵��:
	��ȡ����ϵ����
	---------------------------------
	����:
	����ϵ����
	********************************/
	char *GetName()
	{
		return Name;
	}

	/********************************
	bool SetPoint(int point, Position pos)
	---------------------------------
	˵��:
	�趨����ϵ�������ؼ���
	pointֻ��ȡ0��1��2
	---------------------------------
	����:
	point: �ؼ���
	       0: ORG��,����ϵ��ԭ��
		   1: XX��,X���ϵ�һ��
		   2: XY��,XYƽ���ϵ�һ��
	pos  : �ؼ����Position������
	---------------------------------
	����:
	true : �ؼ����趨�ɹ�
	false: pointȡֵ���ޣ��ؼ����趨ʧ��
	********************************/
	bool SetPoint(int point, Position pos)
	{
		switch(point)
		{
		case 0://ORG
			{
				ORG = pos;
				return true;
			}
		case 1://XX
			{
				_XX = pos;
				return true;
			}
		case 2://XY
			{
				XY = pos;
				return true;
			}
		default:break;
		}
		return false;
	}
};