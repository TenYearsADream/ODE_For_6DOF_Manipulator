//:CommandLine.h ��������Ķ���
//2010-9-28 11:12:30
//2010-7-9 23:07:03
#include "Macro.h"
#include "Position.h"
#pragma once

//�����У��ͻ�����Ļ�����ɵ�Ԫ
class CommandLine
{
private:
	//2010-9-28 10:49:20
	char Name[_CMD_NAME_LENGTH];                                //��������
	int iVariable1 ,iVariable2 ,iVariable3 ;                    //int�Ͳ���
	double dVariable;                                           //double�Ͳ���
	bool bVariable;                                             //bool�ͱ���
	char strVariable1[_CMD_STR_LENGTH] ,strVariable2[_CMD_STR_LENGTH] 
		,strVariable3[_CMD_STR_LENGTH],strVariable4[_CMD_STR_LENGTH]; 
	                                                            //string�Ͳ���
	char Note[_CMD_NOTE_LENGTH];                                //��ע�͡������ר�ò���
public:
	Position Target;                                            //Ŀ��λ��
	
public:
	//���캯��
	//2010-9-28 10:49:27
	CommandLine()                   
	{

		strcpy(Name, "");                                        //��������ʼ��Ϊ�մ�
		strcpy(strVariable1, "");  strcpy(strVariable2, "");     //string�Ͳ�����ʼ��Ϊ�մ�
		strcpy(strVariable3, "");  strcpy(strVariable4, "");
		strcpy(Note, ""); 		 
		dVariable = 0.0;                                         //double�Ͳ�����ʼ��Ϊ0.0
		iVariable1 = iVariable2 = iVariable3 = 0;                //int�Ͳ�����ʼ��Ϊ0
			  
		bVariable = true;                                      //bool�Ͳ�����ʼ��Ϊtrue

	}

	/***************************************
	�������캯��
	***************************************/
	CommandLine(CommandLine &cmd)
	{
		strcpy(Name, cmd.GetName());
		iVariable1 = cmd.GetiVariable(1); iVariable1 = cmd.GetiVariable(2); iVariable1 = cmd.GetiVariable(3);
		dVariable = cmd.GetdVariable();
		bVariable = cmd.GetbVariable();
		strcpy(strVariable1, cmd.GetstrVariable(1)); strcpy(strVariable2, cmd.GetstrVariable(2)); 
		strcpy(strVariable3, cmd.GetstrVariable(3)); strcpy(strVariable4, cmd.GetstrVariable(4));
		strcpy(Note, cmd.GetstrVariable(0));
		Target = cmd.Target;
	}//CommandLine(CommandLine& cmd)

	//2010-9-28 10:49:47
	void Clear()                    //�������
	{
		strcpy(strVariable1, "");  strcpy(strVariable2, "");          //string�Ͳ�����ʼ��Ϊ�մ�
		strcpy(strVariable3, "");  strcpy(Note, ""); 
		this->dVariable = 0.0;                                        //dobule�Ͳ������Ϊ0.0
		this->iVariable1 = this->iVariable2 = this->iVariable3 = 0;   //int�Ͳ�����ʼ��Ϊ0
		this->bVariable = true;                                       //bool�Ͳ�����ʼ��Ϊtrue
	}

	//2010-9-28 10:49:57
	char * GetName()                                             //��ȡ������
	{
		return Name;
	}

	//2010-9-28 10:50:04
	void SetName(char * newName)                                //�޸�������
	{
		strcpy(Name, newName);
		this->Clear();                                          //�޸�����������ո�����
		this->InitCommand();                                    //�޸�����֮��,���¶Բ������г�ʼ��
	}

	//2010-9-28 10:50:10
	double GetdVariable()                                       //��ȡdouble�Ͳ���
	{
		return dVariable;
	}

	//2010-9-28 10:50:16
	void SetdVariable(double value)                            //�޸�double�Ͳ���
	{
		dVariable = value;
	}

	//2010-9-28 10:50:25
	int GetiVariable(int No)                                   //��ȡint�Ͳ���
	{
		int result;
		switch(No)
		{
		case 1:
			result = this->iVariable1;break;
		case 2:
			result = this->iVariable2;break;
		case 3:
			result = this->iVariable3;break;
		default:break;
		}
		return result;
	}

	//2010-9-28 10:50:31
	void SetiVariable(int No, int value)                       //�޸�int�Ͳ���
	{
		switch(No)
		{
		case 1:
			this->iVariable1 = value;break;
		case 2:
			this->iVariable2 = value;break;
		case 3:
			this->iVariable3 = value;break;
		default:break;
		}
	}


	//2010-9-28 10:50:45
	bool GetbVariable()                //��ȡbool�Ͳ���
	{
		return bVariable;
	}


	//2010-9-28 10:52:17
	void SetbVariable(bool value)      //�޸�bool�Ͳ���
	{
		this->bVariable = value;
	}

	//2010-9-28 10:52:51
	char * GetstrVariable(int No)      //��ȡstr�Ͳ���
	{
		char * result;
		switch(No)
		{
		case 0:
			result = Note;break;
		case 1:
			result = strVariable1;break;
		case 2:
			result = strVariable2;break;
		case 3:
			result = strVariable3;break;
		case 4:
			result = strVariable4;break;
		default:break;
		}
		return result;
	}
	void SetstrVariable(int No, char * value) //�޸�str�Ͳ���
	{
		switch(No)
		{
		case 0:
			strcpy(Note, value);break;
		case 1:
			strcpy(strVariable1, value);break;
		case 2:
			strcpy(strVariable2, value);break;
		case 3:
			strcpy(strVariable3, value);break;
		case 4:
			strcpy(strVariable4, value);break;
		default:break;
		}
	}

	//2010-9-28 10:53:12,�����
	/*******************************************
	bool InitCommand()
	˵������������г�ʼ��,�Բ�ͬ������,���ò�ͬ�ĳ�ʼ����
	���أ�true :��ʼ���ɹ�
	      false:��ʼ��ʧ��
	*******************************************/
	bool InitCommand()              //�����ʼ��
	{   //�Բ�ͬ��������ò�ͬ�ĳ�ʼ����ֵ
		//Ŀ��������
		//const char TargetOrderName[][9]	
		
		//�õ��������Ƽ����ţ�������OrderNo
		int OrderNo,OrderTotal;
		OrderTotal = 63;//TotalΪ��������������������޸Ĵ�ֵ
		for(int i=0; i<OrderTotal; i++)
		{
			if(strcmp(Name,TargetOrderName[i])==0)
			{
				OrderNo = i;
				break;
			}
		}
		
		//��str1�����ĳ�ʼ������Ϊ����˵�����и�������ֵĵ�һ��ȡֵ
		switch(OrderNo)
		{
		case 0:{break;}//START
		case 1:{break;}//END
	   /*************�ƶ�����***************************/ 
		case 2:     //MOVJ
		case 3:     //MOVL
		case 4:     //MOVC
			{
				this->SetiVariable(1, 0);//int1 = 0,P<00>
				this->SetdVariable(10);//double = 10,V<10>
				this->SetiVariable(2, 0);//int2=0;Z<0>
				break;
			}
	   /*********************�źŴ���*************************/
		case 5:     //SET
			{
				this->SetiVariable(1, 0);//OUT<00>
				this->SetbVariable(false);//OFF
				break;
			}
		case 6:    //WAIT
			{
				this->SetiVariable(1, 0);//IN<2>
				this->SetbVariable(false);//OFF
				this->SetstrVariable(1,"T");//T
				this->SetdVariable(10);//T<10>
				break;
			}
		case 7:     //DELAY
			{
				this->SetdVariable(10);//T<10>
				break;
			}
		case 8:     //L
			{
				//this->SetiVariable(1,0);//L<0>
				this->SetstrVariable(1, "0");
				break;
			}
		case 9:     //GOTO
			{
				//this->SetiVariable(1, 0);//L<0>
				this->SetstrVariable(1, "0");

				this->SetstrVariable(2, "");//Ĭ��û��IF
				this->SetstrVariable(3, "IN");//IN
				this->SetiVariable(1, 0);//IN<0>
				this->SetstrVariable(4, "==");
				this->SetbVariable(true);
				this->SetiVariable(2, 0);
				break;
			}
		case 10:     //#
			{
				break;
			}
		case 11:     //CALL
			{
				this->SetstrVariable(1, "");
				break;
			}
		case 12:     //RET
			{
				break;
			}

		/*****************************��������*****************************/
		case 13:     //DECR
		case 14:     //INCR
			{
				this->SetstrVariable(1, "R");
				this->SetiVariable(1, 0);//R<0>��������Ǵ�0��ʼ��š�
				break;
			}
		case 15:     //R
			{
				this->SetiVariable(1, 0);
				break;
			}

		/**************************ƽ������******************************/ 
		case 16:     //PR
			{
				this->SetiVariable(1, 0);
				this->SetiVariable(1, 0);
				this->SetstrVariable(1, "");
				this->SetiVariable(3, 0);
				break;
			}
		case 17:     //SHIFTON
			{
				this->SetiVariable(1, 0);//PR<0>
				break;
			}
		case 18:     //SHIFTOFF
			{
				break;
			}
		case 19:     //MISHIFT
			{
				this->SetiVariable(1, 0);
				this->SetiVariable(2, 0);
				this->SetiVariable(3, 0);
				break;
			}					
			
		default:break;
		}
		return true;
}

};
