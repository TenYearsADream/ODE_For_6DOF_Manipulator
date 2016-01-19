//: Execute.h
//"����"���е���غ���
#pragma once
#include "Robot.h"
#include "Program.h"
#include "Variable.h"

/***********************************************
int Excute(Program *pro, CommandLine cmd, int cmdNo, Robot &ROBOT, UserVariable &VARIABLE, int &go)
------------------------------------------------
ִ�е�������
------------------------------------------------
pro       : ָ������ִ�еĿͻ������ָ��
cmd       : ָ��ǰ�����е�ָ��
ROBOT     : �˴�����Ϊȫ�ֱ���ROBOT
VARIABLE  : �˴�����Ϊȫ�ֱ���VARIABLE
go        : Ҫִ�е���һ��������±�
------------------------------------------------
���� : 
0  : ִ�гɹ�
���� : ִ��ʧ��,����ֵ�Ǵ������
***********************************************/
int Excute(Program *pro, CommandLine cmd, Robot &ROBOT, UserVariable &VARIABLE, int &go)
{
	int result = 0;//ִ�н��,Ԥ�ȸ�ֵΪ0
	
	//�õ��������Ƽ����ţ�������OrderNo
	int OrderNo;
	for(int i=0; i<_CMD_SUM; i++)
	{
		if(strcmp(cmd.GetName(), TargetOrderName[i])==0)
		{
			OrderNo = i;
			break;
		}
	}
	
	//�����������Ʊ��,ִ�в�ͬ�Ķ���
	switch(OrderNo)
	{
	case 0:     //START
		{//done
			++go;
			break;
		}
	case 1:     //END
		{//done
			go = pro->GetLineNumber();//��֤���������˳�
			//return 0;//�������
			break;
		}
		//////////////////�˶�����
	case 2:     //MOVJ
		{//done
			//////////////////////////////////////////////////////////////////////////
			//�ڴ�����ƶ������˵Ĵ���
			//////////////////////////////////////////////////////////////////////////
			++go;
			break;
		}
	case 3:     //MOVL
		{//done
			//////////////////////////////////////////////////////////////////////////
			//�ڴ�����ƶ������˵Ĵ���
			//////////////////////////////////////////////////////////////////////////
			++go;
			break;
		}
	case 4:     //MOVC
		{//done
			//////////////////////////////////////////////////////////////////////////
			//�ڴ�����ƶ������˵Ĵ���
			//////////////////////////////////////////////////////////////////////////
			++go;
			break;
		}
		//////////////////�źŴ���
	case 5:     //SET
		{//done
			bool value = cmd.GetbVariable();//�õ�ON/OFF
			int No = cmd.GetiVariable(1);
			ROBOT._GOUT.io[No].SetValue(value);//�޸�IO
			
			++go;
			break;
		}
	case 6:     //WAIT
		{//done
			int No = cmd.GetiVariable(1);//io����
			if (!strcmp(cmd.GetstrVariable(1), ""))//û��T,����ʱ�ȴ�
			{
				for (;;)
				{
					if ((cmd.GetbVariable() && ROBOT._SIN.io[No].GetValue())//ͬΪtrue
						|| (!cmd.GetbVariable() && !ROBOT._SIN.io[No].GetValue()))//ͬΪfalse
					{//�Ѿ�����ȴ�����
						++go;
						break;
					}
				}
			} 
			else if (!strcmp(cmd.GetstrVariable(1), "T"))//��T,��ʱ�ȴ�
			{
				for (int i=0; i<_DELAY_1S*cmd.GetdVariable(); ++i)
				{
					if ((cmd.GetbVariable() && ROBOT._SIN.io[No].GetValue())//ͬΪtrue
						|| (!cmd.GetbVariable() && !ROBOT._SIN.io[No].GetValue()))//ͬΪfalse
					{//�Ѿ�����INͨ���ȴ�����
						break;
					}
				}
				
				//Ϊ����INͨ���ȴ�����,���ȴ�ʱ���ѵ�
				++go;
			} 
			else//����
			{
				return 60;//60�Ŵ���,WAIT�����str1��������
			}					
			
			//++go;
			break;
		}
	case 7:     //DELAY
		{
			double t = cmd.GetdVariable();//�õ���ʱ��ʱ��
			////////////////////////////////////////////////////////////////////
			//�˴������ʱ����
			//Time(t);//��ʱ����
			////////////////////////////////////////////////////////////////////			
			
			++go;
			break;
		}
		/////////////////���̿���
	case 8:     //L
		{//done
			break;
		}
	case 9:     //GOTO
		{//done
			char Target[_CMD_STR_LENGTH];
			strcpy(Target, cmd.GetstrVariable(1));//�õ���תĿ��
			for (int i=0; i<pro->GetLineNumber(); ++i)
			{
				if (!strcmp(Target, pro->commands[i].GetName()))//�ж��Ƿ�Ϊ��ת��ַ
				{
					go = i;
					break;//ִ�гɹ�
				}
			}
			return 90;//������Ϣ90 : ��תĿ�Ĳ�����
			break;
		}
	case 10:     //#
		{//done
			break;
		}
	case 11:     //CALL
		{//done
			break;
		}
	case 12:     //RET
		{//done
			break;
		}
		/////////////////��������
	case 13:     //DECR
		{//done
			int No = cmd.GetiVariable(1);//�õ����޸ĵı�������
			VARIABLE._R[No] -= 1;        //�Լ�1
			++go;
			break;
		}
	case 14:     //INCR
		{//done
			int No = cmd.GetiVariable(1);//�õ����޸ĵı�������
			VARIABLE._R[No] += 1;        //�Լ�1
			++go;
			break;
		}
	case 15:     //R
		{
			VARIABLE.R = cmd.GetiVariable(1);//��ֵ��ȫ��R����
			
			++go;
			break;
		}
		//////////////////ƽ������
	case 16:     //PR
		{
			if (!strcmp(cmd.GetstrVariable(1), ""))//str2Ϊ��,û��+/-
			{
				VARIABLE._PR[cmd.GetiVariable(1)] = VARIABLE._PR[cmd.GetiVariable(2)];
			} 
			else if (!strcmp(cmd.GetstrVariable(1), "+"))//str2Ϊ+
			{
				POStype pr = VARIABLE._PR[cmd.GetiVariable(2)];
				pr += VARIABLE._PR[cmd.GetiVariable(3)];
				VARIABLE._PR[cmd.GetiVariable(1)] = pr;
				//VARIABLE._PR[cmd.GetiVariable(1)] += VARIABLE._PR[cmd.GetiVariable(2)];
			}
			else if (!strcmp(cmd.GetstrVariable(1), "-"))//str2Ϊ-
			{
				VARIABLE._PR[cmd.GetiVariable(1)] -= VARIABLE._PR[cmd.GetiVariable(2)];
			}
			else//����
			{
				return 160;//160�Ŵ���,PR����str2����
			}					
			
			++go;
			break;
		}
	case 17:     //SHIFON
		{
			//////////////////////////////////////////////////////////////////////////
			//�ڴ����ƽ�ƿ�ʼ����
			//////////////////////////////////////////////////////////////////////////
			++go;
			break;
		}
	case 18:     //SHIFOFF
		{
			//////////////////////////////////////////////////////////////////////////
			//�ڴ����ƽ�ƽ�������
			//////////////////////////////////////////////////////////////////////////
			++go;
			break;
		}
	case 19:     //MISHIFT
		{
			int PR_No = cmd.GetiVariable(1);//PR������
			int P_No1 = cmd.GetiVariable(2);//P����1
			int P_No2 = cmd.GetiVariable(3);//P����2
			
			VARIABLE._P[P_No2] -= VARIABLE._P[P_No1];
			VARIABLE._PR[PR_No] = VARIABLE._P[P_No2];
			
			++go;
			break;
		}
		
	default:break;
	}//switch			
			return result;
}//Excute()
		
		
 /***********************************************
 int Run(Program *pro, Robot &ROBOT, UserVariable &VARIABLE)
 ------------------------------------------------
 ȫ��ִ��һ�����
 ------------------------------------------------
 pro       : ��ִ�еĳ���
 &ROBOT    : �˴�Ϊȫ�ֱ���ROBOT
 &VARIABLE : �˴�Ϊȫ�ֱ���VARIABLE
 ------------------------------------------------
 ���� : 
 0 : ����ִ�гɹ�
 ���� : ����ִ��ʧ��,����ʧ�ܴ���
 ***********************************************/
 int Run(Program *pro, Robot &ROBOT, UserVariable &VARIABLE)
 {
	 int result = 0;	
	 
	 int i=0;
	 for (; i<pro->GetLineNumber(); )//�ӵ�һ��������һ��
	 {
		 int Last = i;//�����ϴ����е��к�
		 result = Excute(pro, pro->commands[i], ROBOT, VARIABLE, i);//ִ�е��г���
		 if(result>0)//ʧ���˳�
		 {
			 break;
		 }		 
	 }	 
	 return result;
 }//Run()
		 
		 
  /***********************************************
  int Step(Program *pro, Robot &ROBOT, UserVariable &VARIABLE)
  ����ִ�г���
  ------------------------------------------------
  pro    : ��ִ�еĳ���
  ROBOT  : ȫ�ֱ���::ROBOT
  VARIABLE : ȫ�ֱ���::VARIABLE
  ------------------------------------------------
  ����:
  0  : ���гɹ�
  ��0 : ����ʧ��
 ***********************************************/
 int Step(Program *pro, Robot &ROBOT, UserVariable &VARIABLE)
 {		 
	 int result = 0;//���н��
	 //////////////////////////////////////////////////////
	 static int CurrentLine = 0;//��ǰִ�е�������
	 
	 bool End = false;//�Ƿ�ִ�е����һ�г���
	 if(pro->GetLineNumber() == CurrentLine)//ִ�е����һ��
	 {
		 End = true;
	 }	
	 
	 result = Excute(pro, pro->commands[CurrentLine], ROBOT, VARIABLE, CurrentLine);
	 //////////////////////////////////////////////////////
	 
	 if(End)//ִ�е����һ��
	 {
		 CurrentLine = 0;//�޸ĵ�ǰ������
	 }
	 
	 return result;
 }//int Step()
