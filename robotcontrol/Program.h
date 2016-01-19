//Program.h �ͻ�����
//2010-7-9 23:12:13 
#pragma once

#include "head.h"
//#include "BOX.h"
#include "string.h"

//���ַ���ת��Ϊint.����CmdEdit����
#define   _TOint      atoi(EditSourceOrder.c_str())
//���ַ���ת��Ϊdouble.����CmdEdit����
#define   _TOdouble   atof(EditSourceOrder.c_str())
//�Ƚ��ַ����Ƿ���ͬ,����CmdEdit����
#define   _STRCMP(x)  strcmp(EditSourceOrder.c_str(), x) 

//����ṹ�壬���ͻ����򡱵����ݼ����ɡ������С����ɵ�һ������
struct Program
{
	public:
		CommandLine commands[_VALID_CMDLINE * _NEST_DEEPTH];//���100 * 10������
		
	private:		
		char   Name[_PRO_NAME_LENGTH];      //������
		char   Note[_PRO_NOTE_LENGTH];     //����ע��
		int    LineNumber;   //����
		int    ToolNumber;   //���ߺ���
		bool   Lock;		 //�༭����
		
		int Date[3];     //��������
		int Size;        //�����С

	private:
		/****************************
		bool MoveCmd(int start, int end, int dis, bool Upward)
		-----------------------------
		�ƶ������е�����,��start�е�end��,�����ƶ�dis����
		-----------------------------
		start : �ƶ�����ʼ��
		end   : �ƶ��Ľ�����
		dis   : �ƶ��ľ���
		Upward: �ƶ�����
		    true : �����β�ƶ�
			false: �����ͷ�ƶ�
		-----------------------------
		���� :
		true : �ƶ��ɹ�
		false: �ƶ�ʧ��
		****************************/
		bool MoveCmd(int start, int end, int dis, bool Upward)
		{
			for(int i=0; i<dis; ++i)//��¼��λ�Ĵ���
			{
				if(Upward)//�����β�ƶ�
				{
					for(int j=end; j>=start; --j)//ѡ����Ҫ�ƶ��ķ�Χ
					{
						this->commands[j+1] = this->commands[j];
						++this->LineNumber;
					}					
				}
				else//�����ͷ�ƶ�
				{
					for(int j=start; j<=end; ++j)
					{
						this->commands[j] = this->commands[j+1];
						--this->LineNumber;
					}
				}			
			}		

			return true;
		}
		
	public:

		/*******************************
		 string GetStack()
		 ��������ջ
		 ���� : �����������õ������ӳ��������ӳɵ�string
		*******************************/
		string GetStack()
		{
			string result;
			for(int i=0; i<LineNumber; ++i)
			{
				if(!strcmp(commands[i].GetName(), "CALL"))//�����ӳ�������
				{
					result += commands[i].GetstrVariable(1);
					result += "\r\n";
				}
			}
			return result;
		}//GetStack()


		Program()                       //���캯��
		{
			this->InitProgram();
		}

		/****************************
		Program(char *name)
		-----------------------------
		���ι��캯��
		****************************/
		Program(char *name)
		{
			this->InitProgram();//��ʼ������
			strcpy(Name, name);//�޸�����
		}

		/****************************
		bool Save()
		-----------------------------
		����Programд��Ӳ�̱���
		-----------------------------
		���� : 
		true : ����ɹ�
		false: ����ʧ��
		****************************/
		bool Save()
		{
			//����·��
			char Location[50];
			sprintf(Location, _PROGRAM_LOCATION, this->Name);
			//���ļ�
			FILE *mypro;
			mypro = fopen(Location, "w");
			if(NULL == mypro)
			{
				return false;
			}

			//д������
			fwrite(this, sizeof(*this), 1, mypro);

			//���ļ�
			fclose(mypro);
			return true;			
		}

		/****************************
		bool Read()
		-----------------------------
		��Ӳ���ж�ȡͬ����������
		-----------------------------
		���� :
		true : ��ȡ�ɹ�
		false: ��ȡʧ��
		****************************/
		bool Read()
		{
			bool result;
			result = this->Read(this->Name);
			return result;
		}

		/****************************
		bool Read(char *name)
		-----------------------------
		��Ӳ���н�Program��ȡ���ڴ�
		-----------------------------
		name : ���򿪵ĳ�����
		-----------------------------
		���� : 
		true : ��ȡ�ɹ�
		false: ��ȡʧ��
		****************************/
		bool Read(char *name)
		{
			//��ȡ·��
			char Location[50];
			sprintf(Location, _PROGRAM_LOCATION, name);
			//���ļ�
			FILE *mypro;
			mypro = fopen(Location, "r");
			if(NULL == mypro)
			{
				return false;
			}

			//��ȡ����
			fread(this, sizeof(*this), 1, mypro);

			//�ر��ļ�
			fclose(mypro);
			return true;
		}
		
		/****************************
		int GetToolNo()
		-----------------------------
		˵��:
		��ȡ���ߺ���
		-----------------------------
		����:
		���ߺ���
		****************************/
		int GetToolNo()
		{
			return ToolNumber;
		}
		
		/*****************************
		bool SetToolNo(int No)
		------------------------------
		˵��:
		�޸Ĺ��ߺ���
		------------------------------
		����:
		No : ���ߺ���
		------------------------------
		����:
		true : �޸ĳɹ�
		false: �������Խ��,�޸�ʧ��
		*****************************/
		bool SetToolNo(int No)
		{
			if((No>=0) && (No<_FRAME_NO))
			{
				ToolNumber = No;
				return true;
			}
			else
			{
				return false;
			}			
		}
		
		/***********************************
		void InitProgram()
		------------------------------------
		�Գ�����г�ʼ��
		***********************************/
		void InitProgram()              //��ʼ���ͻ�����
		{//����һ��ֻ��������"������"������
			commands[0].SetName("START");
			commands[1].SetName("END");
			LineNumber = 2;
			ToolNumber = 0;
			
			strcpy(Name, "");
			strcpy(Note, "");
			Lock = false;
			
			//	return true;
		}

		/***************************************
		bool InsertCommand(int No, CommandLine cmd)
		��һ���༭�õ���������������,�ڵ�No��֮��
		---------------- ���� ------------------
		No : ����λ��,������commands�����е��±�
		cmd: ������
		---------------- ���� ------------------
		true : ����ɹ�
		false: ����ʧ��
		***************************************/
		bool InsertCommand(int No, CommandLine cmd)
		{			
			if(_VALID_CMDLINE == LineNumber)//LineNumer�Ѵﵽ�����ʧ��
			{
				return false;
			}
			if(No+1 >= LineNumber)//����λ�ó���LineNumer��Χ����ʧ��
			{
				return false;
			}
			else
			{
				for(int i=LineNumber-1; i>No; --i)//���κ���
				{
					commands[i+1] = commands[i];
				}
				commands[No+1] = cmd;//���������
				
				++LineNumber;
				return true;
			}
		}//InsertComamnd()
		
		/***************************************
		bool InsertCommand(int No, char  *newcmd)
		Ϊ�������һ��������,�ڵ�No��֮��
		-------------- ���� --------------------
		No    : ����λ��,�����������е��±�
		newcmd: ���������������
		-------------- ���� --------------------
		true : ��������ɹ�
		false: ��������ʧ��
		***************************************/
		bool InsertCommand(int No, char * newcmd) //��������
		{//�˴�NoΪ�����������е��±�
			if(_VALID_CMDLINE == LineNumber)//LineNumer�Ѵﵽ�����ʧ��
			{
				return false;
			}
			if(No+1 >= LineNumber)//����λ�ó���LineNumer��Χ����ʧ��
			{
				return false;
			}
			else
			{
				for(int i=LineNumber-1; i>No; --i)//���κ���
				{
					commands[i+1] = commands[i];
				}
				commands[No+1].SetName(newcmd);//���������
				
				++LineNumber;
				return true;
			}
		}//InsertCommand()

		/**************************************************
		bool DeleteCommand(int No)
		---------------------------------------------------
		ɾ��һ�г���
		---------------------------------------------------
		No : ��ɾ����������commands[]�е��±�
		---------------------------------------------------
		���� :
		true : ɾ���ɹ�
		false: ɾ��ʧ��
		**************************************************/
//		bool DeleteCommand(
//		{
//			return true;
//		}
		
		//2010-9-28 11:32:22
		/**************************************************
		bool DeleteCommand(int No)
		---------------------------------------------------
		˵����ɾ��һ������
		---------------------------------------------------
		���� :
		true : ɾ���ɹ�
		false: ɾ��ʧ��
		**************************************************/
		bool DeleteCommand(int No)         //ɾ������
		{//�˴�NoΪ�����������е��±�
			if(No+1 >= LineNumber)//ɾ��λ�ó���LineNumer��Χ����ʧ��
			{
				return false;
			}
			else if(!No)//����ɾ����0�г���
			{
				return false;
			}
			else
			{
				for(int i=No; i<LineNumber; ++i)
				{
					commands[i] = commands[i+1];//���������֮ǰ����			
				}
				--LineNumber;
			}
			commands[LineNumber+1].SetName("");//ԭ�е����һ������(END),�޸�Ϊ������
			return true;
		}

		char * GetName()                //��ȡ������
		{
			return Name;
		}

		void SetName(char * newname)            //�޸ĳ�����
		{
			strcpy(Name, newname);
		}

		char * GetNote()                //��ȡ����ע��
		{
			return Note;
		}

		void SetNote(char * newnote)            //�޸ĳ���ע��
		{
			strcpy(Note, newnote);
		}

		int GetLineNumber()             //��ȡ��������
		{
			return LineNumber;
		}

		void Clear()                   //��ճ���
		{
			this->InitProgram();
		}

		//2010-9-28 15:38:32�������
		/*****************************************
		string Show()
		------------------------------------------
		˵��:
		������ת��Ϊstring����,������ʾ
		------------------------------------------
		����:
		����������϶��ɵ�string����
		*****************************************/
		string Show()                    //������ʾ
		{//������ʾ,������ת��Ϊ�ַ�������
			string Result;

			for(int No_Buffer=0; No_Buffer<LineNumber; ++No_Buffer)
			{


				//�õ��������Ƽ����ţ�������OrderNo
				int OrderNo;
				CommandLine *command;
				for(int i=0; i<_CMD_SUM; i++)
				{
					if(strcmp(commands[No_Buffer].GetName(), TargetOrderName[i])==0)
					{
						command = &commands[No_Buffer];
						OrderNo = i;
						break;
					}
				}

				//�����������Ƽ���ţ�ȷ��Ҫ��ʾ������
				char strOrder[2000]; 
				switch(OrderNo)
				{
				case 0:		//NOP
					{
						//strOrder.Format(_T("%d	NOP"),No_Buffer);
						sprintf(strOrder, "%d	START\r\n", No_Buffer);
						break;
					}
				case 1:		//END
					{
						//	strOrder.Format(_T("%d END"),No_Buffer);
						sprintf(strOrder, "%d	END", No_Buffer);

						//����END�У�ǿ�ƽ�����ֱ������
						Result += strOrder;
						return Result;
						break;
					}			
					/////////////////////////////�ƶ�����//////////////////////////////////
				case 2:     //MOVJ
				case 3:     //MOVL
				case 4:     //MOVC
					{
						//��ȡ������
						/*char name[9];*/
						sprintf(strOrder, "%d	%s  ", No_Buffer, command->GetName());
						//��ȡ�㡢�ٶȡ�����
						char detail[100];
						sprintf(detail, "P%d,  V%.2f,  Z%d\r\n", command->GetiVariable(1), command->GetdVariable(), command->GetiVariable(2));
						strcat(strOrder, detail);
						break;
					}

					////////////////////////////////�źŴ���//////////////////////////////
				case 5:     //SET
					{
						//ͨ����
						sprintf(strOrder, "%d	SET  OUT%d,  ", No_Buffer, command->GetiVariable(1));
						//ON/OFF
						char detail[10];
						if(command->GetbVariable())
						{
							strcpy(detail, "ON\r\n");
						}
						else
						{
							strcpy(detail, "OFF\r\n");
						}

						strcat(strOrder, detail);
						break;
					}
				case 6:     //WAIT
					{
						//ͨ����
						sprintf(strOrder, "%d	WAIT  IN%d == ", No_Buffer, command->GetiVariable(1));
						//ON/OFF
						char in[10];
						if(command->GetbVariable())
						{
							strcpy(in, "ON");
						}
						else
						{
							strcpy(in, "OFF");
						}
						strcat(strOrder, in);

						//T<10>
						char T[10];
						if(!strcmp(command->GetstrVariable(1), ""))//Ϊ��
						{
							strcpy(T, "\r\n");
						}
						else if(!strcmp(command->GetstrVariable(1), "T"))//T
						{
							sprintf(T, ",  T%.2f\r\n", command->GetdVariable()); 
						}
						else
						{
							sprintf(strOrder, "%d	WAIT  error1\r\n");
							break;
						}						
						strcat(strOrder, T);

						break;
					}

				case 7:     //DELAY
					{
						sprintf(strOrder, "%d	DELAY  T%.2f\r\n", No_Buffer, command->GetdVariable());
						break;
					}

					//////////////////////////���̿���////////////////////////////////
				case 8:     //L
					{
						sprintf(strOrder, "%d  L %s :\r\n", No_Buffer, command->GetstrVariable(1));
						break;
					}
				case 9:     //GOTO
					{
						//GOTO L0
						sprintf(strOrder, "%d	GOTO  L%s", No_Buffer, command->GetstrVariable(1));
						//
						char IF[30];
						if(!strcmp(command->GetstrVariable(2), ""))//Ϊ��,û��IF
						{
							strcpy(IF,"\r\n");
						}
						else if(!strcmp(command->GetstrVariable(2), "IF"))//��IF
						{
							sprintf(IF, ",  IF  %s%d %s ", command->GetstrVariable(3), command->GetiVariable(1), command->GetstrVariable(4));

							//ON/4
							char end[10];
							if(!strcmp(command->GetstrVariable(3), "IN"))
							{
								if(command->GetbVariable())//ON
								{
									strcpy(end, "ON\r\n");
								}
								else
								{
									strcpy(end, "OFF\r\n");
								}
							}
							else if(!strcmp(command->GetstrVariable(3), "R"))
							{
								sprintf(end, "%d\r\n", command->GetiVariable(2));
							}
							else//����
							{
								sprintf(strOrder, "%d	GOTO  error1", No_Buffer);
								break;
							}

							strcat(IF, end);
						}

						strcat(strOrder, IF);
						break;
					}

				case 10:     //#
					{
						sprintf(strOrder, "%d  #%s\r\n", No_Buffer, command->GetstrVariable(0));
						break;
					}
				case 11:     //CALL
					{
						sprintf(strOrder, "%d	CALL  %s\r\n", No_Buffer, command->GetstrVariable(1));
						break;
					}
				case 12:     //RET
					{
						sprintf(strOrder, "%d	RET\r\n", No_Buffer);
						break;
					}

					//////////////////////////��������///////////////////////////////
				case 13:     //DECR
				case 14:     //INCR
					{
						sprintf(strOrder, "%d	%s  R%d\r\n", No_Buffer, command->GetName(), command->GetiVariable(1));
						break;
					}
				case 15:     //R
					{
						sprintf(strOrder, "%d	R = %d\r\n", No_Buffer, command->GetiVariable(1));
						break;
					}

					/////////////////////////ƽ��ָ��/////////////////////////////////
				case 16:     //PR
					{
						//PR0 = PR0
						sprintf(strOrder, "%d	PR%d = PR%d", No_Buffer, command->GetiVariable(1), command->GetiVariable(2));

						//PR0 = PR0 - PR0
						char end[20];
						if(!strcmp(command->GetstrVariable(1), ""))//��
						{
							strcpy(end, "\r\n");
						}
						else if(!strcmp(command->GetstrVariable(1), "-"))
						{
							sprintf(end, " - PR%d\r\n", command->GetiVariable(3));
						}
						else if(!strcmp(command->GetstrVariable(1), "+"))
						{
							sprintf(end, " + PR%d\r\n", command->GetiVariable(3));
						}
						else
						{
							sprintf(strOrder, "%d	PR error1\r\n", No_Buffer);
							break;
						}

						strcat(strOrder, end);
						break;
					}
				case 17:     //SHIFTON
					{
						sprintf(strOrder, "%d	SHIFTON  PR%d\r\n", No_Buffer, command->GetiVariable(1));
						break;
					}
				case 18:     //SHIFTOFF
					{
						sprintf(strOrder, "%d	SHIFTOFF\r\n", No_Buffer);
						break;
					}
				case 19:     //MISHIFT
					{
						sprintf(strOrder, "%d	MISHIFT  PR%d,  P%d,  P%d\r\n", No_Buffer, command->GetiVariable(1), command->GetiVariable(2), command->GetiVariable(3));
						break;
					}
							 



					/////�ڴ˴�����µ�case���Ա༭�µ�����//////////////////////////

				default:break;
				}
				Result += strOrder;
			}
			return Result;
		}

		/**************************************************
		bool CmdEdit(int CommandNo, int MemberNo, string EditSourceOrder, const Robot &robot)
		---------------------------------------------------
		˵��:
		�޸ĳ����е�����
		---------------------------------------------------
		����:
		CommandNo       : �����к���
		MemberNo        : ���޸ĵĲ���λ��
		EditSourceOrder : �޸�Դ����
		cons &robot     : ȫ�ֱ���ROBOT
		---------------------------------------------------
		����:
		true : �޸ĳɹ�
		false: �޸�ʧ��
		**************************************************/
		bool CmdEdit(int CommandNo, int MemberNo, string EditSourceOrder,  Robot &robot)
		{//���������кš����޸Ĳ���λ�úš��޸�Դ����

			CommandLine *command = & this->commands[CommandNo];//ָ��ָ�����޸ĵ�����

			const char *InputOrder = EditSourceOrder.c_str();
			char InputOrder_Buffer[9];
			strcpy(InputOrder_Buffer, InputOrder);

			//�õ��������Ƽ����ţ�������OrderNo
			int OrderNo;
			for(int i=0; i<_CMD_SUM; i++)
			{
				if(strcmp(command->GetName(), TargetOrderName[i])==0)
				{
					OrderNo = i;
					break;
				}
			}

			//�����������Ʊ�ż�������Ա��ţ������޸Ĳ���
			switch(OrderNo)
			{				
			case 0:     //START
				{
					break;
				}
			case 1:     //END
				{break;}

				//////////////////////�ƶ�����////////////////////////////
			case 2:     //MOVJ
			case 3:     //MOVL
			case 4:     //MOVC
				{
					{
						switch(MemberNo)
						{
						case 1:    //int1, P00
							{
								int num = _TOint;
								if(num>=_P_MIN && num<=_P_MAX)
								{
									command->SetiVariable(1, num);
								}								
								break;
							}
						case 2:    //double, V10
							{
								double num = _TOdouble;
								command->SetdVariable(num);
								break;
							}
						case 3:    //int2, Z2
							{
								int num = _TOint;
								if(num>=_PL_MIN && num<=_PL_MAX)
								{
									command->SetiVariable(2, num);
								}
								break;
							}
						default:break;
						}
					}

					//�޸�Ŀ��λ��
					command->Target = robot.GetCurrentPosition();
					//�޸�λ�˱�־
					if( !strcmp(command->GetName(), "MOVJ"))//MOVJ
					{
						command->Target.SetFlag(false);//�ؽ�����
					}
					else
					{
						command->Target.SetFlag(true);//ֱ������
					}

					break;
				}

				///////////////////////////�źŴ���////////////////////////
			case 5:     //SET
				{
					{
						switch(MemberNo)
						{
						case 1:    //int1, OUT01
							{
								int num = _TOint;
								if(num>=_OUT_MIN && num<=_OUT_MAX)
								{
									command->SetiVariable(1, num);
								}
								break;
							}
						case 2:    //bool ,ON/OFF
							{
								if(!_STRCMP("OFF"))//OFF
								{
									command->SetbVariable(false);
								}
								else if(!_STRCMP("ON"))//ON
								{
									command->SetbVariable(true);
								}
								break;
							}
						default:break;
						}
					}
					break;
				}
			case 6:     //WAIT
				{
					{
						switch(MemberNo)
						{
						case 1:    //int1, IN02
							{
								int num = _TOint;
								if(num>=_IN_MAX && num<=_IN_MAX)
								{
									command->SetiVariable(1, num);
								}
								break;
							}
						case 2:    //OFF/ON
							{
								if(!_STRCMP("OFF"))//OFF
								{
									command->SetbVariable(false);
								}
								else if(!_STRCMP("ON"))//ON
								{
									command->SetbVariable(true);
								}
								break;
							}
						case 3:    //str1, T
							{
								if(!_STRCMP(""))//Ϊ��,��û��T����
								{
									command->SetstrVariable(1, "");//����û��T
									command->SetdVariable(_TIME_MAX);//�ȴ�ʱ���趨Ϊ���
								}
								else if(!_STRCMP("T"))//��T
								{
									command->SetstrVariable(1, "T");//����T
								}
								
								break;
							}
						case 4:    //double, �ȴ�ʱ��T999
							{
								if(!strcmp(command->GetstrVariable(1), "T"))//��T
								{
									double num = _TOdouble;
									if(num>=_TIME_MIN && num<=_TIME_MAX)
									{
										command->SetdVariable(num);
									}
								}
								break;
							}
						default:break;
						}
					}
					break;
				}
			case 7:     //DELAY
				{
					{
						switch(MemberNo)
						{
						case 1:    //double, T10
							{
								double num = _TOdouble;
								if(num>=_TIME_MIN && num<=_TIME_MAX)
								{
									command->SetdVariable(num);
								}
								break;
							}
						default:break;
						}
					}
					break;
				}

				/////////////////////////////���̿���/////////////////////////
			case 8:     //L
				{
					switch(MemberNo)
					{
					case 1:  //L<>
						{
							if(strlen(EditSourceOrder.c_str())<=8 && strlen(EditSourceOrder.c_str()) >=0)//��������							
							{
								char str[9];
								strcpy(str, EditSourceOrder.c_str());
								command->SetstrVariable(1, str);
							}
						}
					default:break;					
					}
					break;
				}
			case 9:     //GOTO
				{
					break;
				}
			case 10:     //#
				{
					switch(MemberNo)
					{
					case 1:  //L<>
						{
							if(EditSourceOrder.length()<=_CMD_NOTE_LENGTH-1 && EditSourceOrder.length()>=0)//��������							
							{
								char str[33];
								strcpy(str, EditSourceOrder.c_str());
								command->SetstrVariable(0, str);
							}
						}
					default:break;					
					}
					break;
				}
			case 11:     //CALL
				{
					{
						switch(MemberNo)
						{
						case 1:  //CALL<>
							{
								if(strlen(EditSourceOrder.c_str())<=8 && strlen(EditSourceOrder.c_str()) >=0)//��������							
								{
									char str[9];
									strcpy(str, EditSourceOrder.c_str());
									command->SetstrVariable(1, str);
								}
							}
						default:break;					
						}
					}
					break;
				}
			case 12:     //RET
				{
					break;
				}
				/////////////////////////////��������/////////////////////////
			case 13:     //DECR
			case 14:     //INCR
				{
					{
						switch(MemberNo)
						{
						case 1:    //int1, R01
							{
								int num = _TOint;
								if(num>=_R_MIN && num<=_R_MAX)
								{
									command->SetiVariable(1, num);
								}
								break;
							}
						default:break;
						}
					}
					break;
				}
			case 15:     //R
				{
					{
						switch(MemberNo)
						{
						case 1:    //int1, R=01
							{
								int num = _TOint;								
								command->SetiVariable(1, num);								
								break;
							}
						default:break;
						}
					}
					break;
				}

				/////////////////////////////ƽ������/////////////////////////
			case 16:     //PR
				{
					{
						switch(MemberNo)
						{
						case 1:    //int1, PR01
							{							
								int num = _TOint;
								if(num>=_PR_MIN && num<=_PR_MAX)
								{
									command->SetiVariable(1, num);
								}								
								break;
							}
						case 2:    //int2, PR02
							{
								int num = _TOint;
								if(num>=_PR_MIN && num<=_PR_MAX)
								{
									command->SetiVariable(2, num);
								}								
								break;
							}
						case 3:    //str1 -/+
							{
								if(!_STRCMP("-"))//-
								{
									command->SetstrVariable(1, "-");
								}
								else if(!_STRCMP("+"))//+
								{
									command->SetstrVariable(1, "+");
								}
								break;
							}
						case 4:    //int3 PR03
							{
								if(strcmp(command->GetstrVariable(1), ""))//str1����ǿ�
								{
									int num = _TOint;
									if(num>=_PR_MIN && num<=_PR_MAX)
									{
										command->SetiVariable(3, num);
									}
								}
								break;
							}
						default:break;
						}
					}
					break;
				}
			case 17:     //SHIFTON
				{
					{
						switch(MemberNo)
						{
						case 1:    //int1, PR01
							{
								int num = _TOint;
								if(num>=_PR_MIN && num<=_PR_MAX)
								{
									command->SetiVariable(1, num);
								}
							}
						default:break;
						}
					}
					break;
				}
			case 18:     //SHIFTOFF
				{
					break;
				}
			case 19:     //MISHIFT
				{
					{
						switch(MemberNo)
						{
						case 1:    //int1, PR01
							{
								int num = _TOint;
								if(num>=_PR_MIN && num<=_PR_MAX)
								{
									command->SetiVariable(1, num);
								}
								break;
							}
						case 2:    //int2, P01
							{
								int num = _TOint;
								if(num>=_P_MIN && num<=_P_MAX)
								{
									command->SetiVariable(2, num);
								}
								break;
							}
						case 3:    //int3, P02
							{
								int num = _TOint;
								if(num>=_P_MIN && num<=_P_MAX)
								{
									command->SetiVariable(3, num);
								}
								break;
							}
						default:break;
						}
					}
					break;
				}

				/////////////////////////////�������/////////////////////////
			default :break;
			}
			return true;
		}//CmdEdit()

		/***************************************
		bool Explain()
		----------------------------------------
		�������,��Ƕ�׵��õĳ���������һ������
		----------------------------------------
		���� :
		true : ������ͳɹ�
		false: �������ʧ��
		***************************************/
		bool Explain()
		{
			for(int i=0; i<this->LineNumber; ++i)//���μ��ÿ������
			{
				if(!strcmp(this->commands[i].GetName(), "CALL"))//����CALLָ��
				{
					if(!this->Nest(i, this->commands[i].GetstrVariable(1)))//Ƕ���ӳ���ʧ��
					{
						this->Read(this->Name);//��ԭ������
						return false;
					}
				}
			}
			return true;
		}//Explain()

		/***************************************
		bool Nest(int Line, char *name)
		----------------------------------------
		���Ӻ������ͺ�,Ƕ�뵱ǰ����
		----------------------------------------
		Line : CALLָ����ֵ�λ����commands[]�����е��±�
		name : �Ӻ����ĺ�����
		----------------------------------------
		���� :
		true : Ƕ�׳ɹ�
		false: Ƕ��ʧ��
		***************************************/
		bool Nest(int Line, char *name)
		{
			//���Ӻ������н���
			
			Program Sub;//�ӳ���
			if(!Sub.Read(name))//�õ��ӳ���
			{
				return false;
			}

			if(!Sub.Explain())
			{
				return false;
			}

			for(int i=1; i<Sub.GetLineNumber()-1; ++i)//ȥ���ӳ����ͷ��β
			{
				if(!strcmp(Sub.commands[i].GetName(), "RET"))//����RET����,��Ƕ�׽���
				{
					break;
				}
				if(_MAXCDMLINE == this->LineNumber)//�����Ѵﵽ����޶�
				{
					return false;
				}
				if(i>1)//�ӵڶ��ο�ʼ�ƶ������������
				{
					//��������CALL����֮�����������,���κ���һλ
					for(int j=this->LineNumber-1; j>Line; --j)//��β����,��CALL�������һ������
					{
						this->commands[j+1] = this->commands[j];//��λ
					}
					++this->LineNumber;//�޸����������������
					++Line;//�޸�Ƕ��λ��
				}
				this->commands[Line] = Sub.commands[i];//Ƕ��һ������				
			}
			return true;
		}//Nest()

		/***********************************************
		int Run(Robot &ROBOT, UserVariable &VARIABLE)
		------------------------------------------------
		ȫ��ִ��һ�����
		------------------------------------------------
	 	&ROBOT    : �˴�Ϊȫ�ֱ���ROBOT
		&VARIABLE : �˴�Ϊȫ�ֱ���VARIABLE
		------------------------------------------------
		���� : 
		0 : ����ִ�гɹ�
		���� : ����ִ��ʧ��,����ʧ�ܴ���
		***********************************************/
		//int Run(Robot &ROBOT, UserVariable &VARIABLE, bool &SEND_FLAG, bool &RECV_FLAG)
		//{
		//	int result = 0;
		//	this->Explain();

		//	//int next = 0;
		//	int i=0;
		//	for (; i<this->LineNumber; )//�ӵ�һ��������һ��
		//	{
		//		int Last = i;//�����ϴ����е��к�
		//		result = this->CmdExcute(this, this->commands[i], ROBOT, VARIABLE, i, SEND_FLAG, RECV_FLAG);//ִ�е��г���
		//		if(result>0)//ʧ���˳�
		//		{
		//			break;
		//		}
		//	}

		//	this->Read();//��ԭ������
		//	return result;
		//}


		/***********************************************
		int Step(Robot &ROBOT, UserVariable &VARIABLE, bool &SEND_FLAG=false, bool &RECV_FALG = false)
		����ִ�г���
		------------------------------------------------
		  ROBOT  : ȫ�ֱ���::ROBOT
		VARIABLE : ȫ�ֱ���::VARIABLE
		SEND_FLAG: ȫ�ֱ���::SEND_FLAG������PC���ͳ���
		RECV_FLAG: ȫ�ֱ���::RECV_FLAG���ڽ���PC�˵�����
		------------------------------------------------
		����:
	 	 0  : ���гɹ�
		��0 : ����ʧ��
		***********************************************/
		//int Step(Robot &ROBOT, UserVariable &VARIABLE, bool& SEND_FLAG, bool& RECV_FLAG)
		//{			
		//	

		//	int result = 0;//���н��
		//	//////////////////////////////////////////////////////
		//	static int CurrentLine = 0;//��ǰִ�е�������

		//	bool End = false;//�Ƿ�ִ�е����һ�г���
		//	if(this->GetLineNumber() == CurrentLine)//ִ�е����һ��
		//	{
		//		End = true;
		//	}	

		//	result = CmdExcute(this, this->commands[CurrentLine], ROBOT, VARIABLE, CurrentLine, SEND_FLAG, RECV_FLAG);
		//	//////////////////////////////////////////////////////

		//	if(End)//ִ�е����һ��
		//	{
		//		CurrentLine = 0;//�޸ĵ�ǰ������
		//	}

		//	return result;
		//}//int Step()



		/***********************************************
		int CmdExcute(Program *pro, CommandLine cmd, int cmdNo, Robot &ROBOT, UserVariable &VARIABLE, int &go)
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
		//int CmdExcute(Program *pro, CommandLine cmd, Robot &ROBOT, UserVariable &VARIABLE, int &go, bool &SEND_FLAG, bool &RECV_FLAG)
		//{
		//	int result = 0;//ִ�н��,Ԥ�ȸ�ֵΪ0

		//	//�õ��������Ƽ����ţ�������OrderNo
		//	int OrderNo;
		//	for(int i=0; i<_CMD_SUM; i++)
		//	{
		//		if(strcmp(cmd.GetName(), TargetOrderName[i])==0)
		//		{
		//			OrderNo = i;
		//			break;
		//		}
		//	}

		//	//�����������Ʊ��,ִ�в�ͬ�Ķ���
		//	switch(OrderNo)
		//	{
		//	case 0:     //START
		//		{//done
		//			++go;
		//			break;
		//		}
		//	case 1:     //END
		//		{//done
		//			go = pro->GetLineNumber();//��֤���������˳�
		//			break;
		//		}
		//		//////////////////�˶�����
		//	case 2:     //MOVJ
		//		{//done
		//			//////////////////////////////////////////////////////////////////////////
		//			//�ڴ�����ƶ������˵Ĵ���
		//			//////////////////////////////////////////////////////////////////////////
		//			++go;
		//			break;
		//		}
		//	case 3:     //MOVL
		//		{//done
		//			//////////////////////////////////////////////////////////////////////////
		//			//�ڴ˴�����ƶ������˵Ĵ���
		//			//////////////////////////////////////////////////////////////////////////
		//			++go;
		//			break;
		//		}
		//	case 4:     //MOVC
		//		{//done
		//			//////////////////////////////////////////////////////////////////////////
		//			//�ڴ˴�����ƶ������˵Ĵ���
		//			//////////////////////////////////////////////////////////////////////////
		//			++go;
		//			break;
		//		}
		//		//////////////////�źŴ���
		//	case 5:     //SET
		//		{//done
		//			bool value = cmd.GetbVariable();//�õ�ON/OFF
		//			int No = cmd.GetiVariable(1);
		//			ROBOT._GOUT.io[No].SetValue(value);//�޸�IO

		//			++go;
		//			break;
		//		}
		//	case 6:     //WAIT
		//		{//done
		//			int No = cmd.GetiVariable(1);//io����
		//			if (!strcmp(cmd.GetstrVariable(1), ""))//û��T,����ʱ�ȴ�
		//			{
		//				for (;;)
		//				{
		//					if ((cmd.GetbVariable() && ROBOT._SIN.io[No].GetValue())//ͬΪtrue
		//						 || (!cmd.GetbVariable() && !ROBOT._SIN.io[No].GetValue()))//ͬΪfalse
		//					{//�Ѿ�����ȴ�����
		//						++go;
		//						break;
		//					}
		//				}
		//			} 
		//			else if (!strcmp(cmd.GetstrVariable(1), "T"))//��T,��ʱ�ȴ�
		//			{
		//				for (int i=0; i<_DELAY_1S*cmd.GetdVariable(); ++i)
		//				{
		//					if ((cmd.GetbVariable() && ROBOT._SIN.io[No].GetValue())//ͬΪtrue
		//						 || (!cmd.GetbVariable() && !ROBOT._SIN.io[No].GetValue()))//ͬΪfalse
		//					{//�Ѿ�����INͨ���ȴ�����
		//						break;
		//					}
		//				}

		//				//Ϊ����INͨ���ȴ�����,���ȴ�ʱ���ѵ�
		//				++go;
		//			} 
		//			else//����
		//			{
		//				return 60;//60�Ŵ���,WAIT�����str1��������
		//			}					

		//			//++go;
		//			break;
		//		}
		//	case 7:     //DELAY
		//		{
		//			double t = cmd.GetdVariable();//�õ���ʱ��ʱ��
		//			this->Time(t);//��ʱ

		//			++go;
		//			break;
		//		}
		//		/////////////////���̿���
		//	case 8:     //L
		//		{//done
		//			break;
		//		}
		//	case 9:     //GOTO
		//		{//done
		//			char Target[_CMD_STR_LENGTH];
		//			strcpy(Target, cmd.GetstrVariable(1));//�õ���תĿ��
		//			for (int i=0; i<pro->GetLineNumber(); ++i)
		//			{
		//				if (!strcmp(Target, pro->commands[i].GetName()))//�ж��Ƿ�Ϊ��ת��ַ
		//				{
		//					go = i;
		//					break;//ִ�гɹ�
		//				}
		//			}
		//			return 90;//������Ϣ90 : ��תĿ�Ĳ�����
		//			break;
		//		}
		//	case 10:     //#
		//		{//done
		//			break;
		//		}
		//	case 11:     //CALL
		//		{//done
		//			break;
		//		}
		//	case 12:     //RET
		//		{//done
		//			break;
		//		}
		//		/////////////////��������
		//	case 13:     //DECR
		//		{//done
		//			int No = cmd.GetiVariable(1);//�õ����޸ĵı�������
		//			VARIABLE._R[No] -= 1;        //�Լ�1
		//			++go;
		//			break;
		//		}
		//	case 14:     //INCR
		//		{//done
		//			int No = cmd.GetiVariable(1);//�õ����޸ĵı�������
		//			VARIABLE._R[No] += 1;        //�Լ�1
		//			++go;
		//			break;
		//		}
		//	case 15:     //R
		//		{
		//			VARIABLE.R = cmd.GetiVariable(1);//��ֵ��ȫ��R����

		//			++go;
		//			break;
		//		}
		//		//////////////////ƽ������
		//	case 16:     //PR
		//		{
		//			if (!strcmp(cmd.GetstrVariable(1), ""))//str2Ϊ��,û��+/-
		//			{
		//				VARIABLE._PR[cmd.GetiVariable(1)] = VARIABLE._PR[cmd.GetiVariable(2)];
		//			} 
		//			else if (!strcmp(cmd.GetstrVariable(1), "+"))//str2Ϊ+
		//			{
		//				POStype pr = VARIABLE._PR[cmd.GetiVariable(2)];
		//				pr += VARIABLE._PR[cmd.GetiVariable(3)];
		//				VARIABLE._PR[cmd.GetiVariable(1)] = pr;
		//				//VARIABLE._PR[cmd.GetiVariable(1)] += VARIABLE._PR[cmd.GetiVariable(2)];
		//			}
		//			else if (!strcmp(cmd.GetstrVariable(1), "-"))//str2Ϊ-
		//			{
		//				VARIABLE._PR[cmd.GetiVariable(1)] -= VARIABLE._PR[cmd.GetiVariable(2)];
		//			}
		//			else//����
		//			{
		//				return 160;//160�Ŵ���,PR����str2����
		//			}					

		//			++go;
		//			break;
		//		}
		//	case 17:     //SHIFON
		//		{
		//			//////////////////////////////////////////////////////////////////////////
		//			//�ڴ����ƽ�ƿ�ʼ����
		//			//////////////////////////////////////////////////////////////////////////
		//			++go;
		//			break;
		//		}
		//	case 18:     //SHIFOFF
		//		{
		//			//////////////////////////////////////////////////////////////////////////
		//			//�ڴ����ƽ�ƽ�������
		//			//////////////////////////////////////////////////////////////////////////
		//			++go;
		//			break;
		//		}
		//	case 19:     //MISHIFT
		//		{
		//			int PR_No = cmd.GetiVariable(1);//PR������
		//			int P_No1 = cmd.GetiVariable(2);//P����1
		//			int P_No2 = cmd.GetiVariable(3);//P����2
		//			 
		//			VARIABLE._P[P_No2] -= VARIABLE._P[P_No1];
		//			VARIABLE._PR[PR_No] = VARIABLE._P[P_No2];

		//			++go;
		//			break;
		//		}
		//		
		//	default:break;
		//	}

		//	return result;
		//}//CmdExcute()


		/************************************
		void Time(double time)
		-------------------------------------
		��ʱ����
		-------------------------------------
		time : ��ʱ��ʱ��
		************************************/
		void Time(double time)
		{

		}//Time()
};//struct Program
