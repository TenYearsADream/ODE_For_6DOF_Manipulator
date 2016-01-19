//Robot.h ������ʵ���ͷ�ļ�
//2010-7-28 8:40:39

#include "RobotDetail.h"
#include "Macro.h"
#pragma once

struct Robot//�����Ӷ���Ķ�����ʽ,��Ϊ�»���+������Сд
{
public:
	SafeMode   _safemode;             //��ȫģʽ
	int        _runmode;              //����ģʽ,0Ϊʾ��,1Ϊ����
	int        _loopmode;             //ѭ��ģʽ,0Ϊ����,1Ϊ��ѭ��,2Ϊ����ѭ��
	SpecialRun _specialrun;           //��������
	int        _handspeed;            //�ֶ��ٶ�,0Ϊ΢��,1Ϊ����,2Ϊ����,3Ϊ����
	bool       _softlimit;            //����,trueΪ������Ч,falseΪ���޽��
	bool       _alllimit;             //ȫ������,trueΪ������Ч,falseΪ���޽��

	int        _frametype;            //��������,0�ؽ�����,1ֱ������,2��������,3�û�����
	int        _frameno;              //�������,���Թ���������û�������Ч
	ToolFrame  _toolframe[_FRAME_NO]; //������������
	UserFrame  _userframe[_FRAME_NO]; //�û���������


	Interfere  _axis[_AXIS_SUM];       //�������
	Interfere  _cube[_CUBE_SUM];       //�����������

	IO         _GIN;                   //ͨ������
	IO         _GOUT;                  //ͨ�����
	IO         _SIN;                   //ר������
	IO         _SOUT;                  //ר�����
	IO         _DELAY;                 //�̵���

	Position   _AbsoluteOrigin;        //����ԭ��
	Position   _WorkOrigin;            //��ҵԭ��
	Position   _SecondOrigin;          //�ڶ�ԭ��

	Alarm      _alarm;                 //������Ϣ
 
	Position   _currentposition;       //��ǰλ��

private:
	double     _ManualHigh;            //�����ٶ�ֵ
	double     _ManualMiddle;          //�����ٶ�ֵ
	double     _ManualLow;             //�����ٶ�ֵ
	double     _ManualSlow;            //΢���ٶ�ֵ


public:
	/****************************
	double GetManualSpeed()
	-----------------------------
	�����ֶ��ٶȵȼ���ȡ�ֶ��ٶ�ֵ
	-----------------------------
	���� : ��Ӧ���ֶ��ٶ�ֵ
	****************************/
	double GetManualSpeed()
	{
		double result=0;//�����ص�ֵ

		switch(this->_handspeed)
		{
		case 0://΢��
			{
				result = _ManualSlow;
				break;
			}
		case 1://����
			{
				
				result = _ManualLow;
				break;
			}
		case 2://����
			{
				
				result = _ManualMiddle;
				break;
			}
		case 3://����
			{
				
				result = _ManualHigh;
				break;
			}
		default:break;
		}

		return result;
	}//GetManualSpeed()

	/****************************
	bool SetFrameType(int type)
	-----------------------------
	˵��:
	�޸�����ϵ����
	-----------------------------
	����:
	type: ����ϵ��������,ֻ��ȡ0-4
	-----------------------------
	����:
	true : �޸ĳɹ�
	false: �������Խ��,�޸�ʧ��
	****************************/
	bool SetFrameType(int type)
	{
		if(type<0 || type>4)
		{
			return false;
		}
		else
		{
			_frametype = type;
			return true;
		}		
	}

	/****************************
	bool SetFrameNo(int no)
	-----------------------------
	˵��:
	�޸�����ϵ����
	-----------------------------
	����:
	no: ����ϵ����,ֻ��ȡ0- _FRAMENO
	-----------------------------
	����:
	true : �޸ĳɹ�
	false: �������Խ��,�޸�ʧ��
	****************************/
	bool SetFrameNo(int no)
	{
		if(no<0 || no>_FRAME_NO)
		{
			return false;
		}
		else
		{
			_frameno = no;
			return true;
		}
	}

	/****************************
	int GetFrameType()
	-----------------------------
	˵��:
	��ȡ����ϵ����
	-----------------------------
	����:
	����ϵ��������
	****************************/
	int GetFrameType()
	{
		return _frametype;
	}

	/****************************
	int GetFrameNo()
	-----------------------------
	˵��:
	��ȡ���߻����û�����ϵ����
	-----------------------------
	����:
	����ϵ����
	****************************/
	int GetFrameNo()
	{
		return _frameno;
	}

	/****************************
	int GetLoopmode()
	-----------------------------
	˵��:
	��ȡѭ��ģʽ
	-----------------------------
	����:
	ѭ��ģʽ����
	****************************/
	int GetLoopmode()
	{
		return _loopmode;
	}

	/****************************
	void SetLoopmode(int mode)
	-----------------------------
	˵��:
	�޸�ѭ��ģʽ
	-----------------------------
	����:
	mode: ѭ��ģʽȡֵ,ֻ��ȡ0,1,2
	****************************/
	void SetLoopmode(int mode)
	{
		_loopmode = mode;
	}

	/****************************
	bool GetAlllimit()
	-----------------------------
	˵��:
	��ȡȫ������
	-----------------------------
	����:
	ȫ��������Ϣ
	****************************/
	bool GetAlllimit()
	{
		return _alllimit;
	}

	/****************************
	void SetAlllimit(bool value)
	-----------------------------
	˵��:
	�޸�ȫ������
	-----------------------------
	����:
	value: ȫ�������Ƿ���Ч
	       true : ��Ч
		   false: ��Ч
	****************************/
	void SetAlllimit(bool value)
	{
		_alllimit = value;
	}

	/****************************
	void SetAlllimit()
	-----------------------------
	˵��:
	�޸�ȫ������,��ȫ�����޵�ֵȡ��
	****************************/
	void SetAlllimit()
	{
		_alllimit = !_alllimit;
	}

	/****************************
	bool GetSoftlimit()
	-----------------------------
	˵��:
	��ȡ����
	-----------------------------
	����:
	������Ϣ
	****************************/
	bool GetSoftlimit()
	{
		return _softlimit;
	}

	/****************************
	void SetSoftlimit(bool value)
	-----------------------------
	˵��:
	�޸�����
	-----------------------------
	����:
	value: �����Ƿ���Ч
	       true : ��Ч
		   false: ��Ч
	****************************/
	void SetSoftlimit(bool value)
	{
		_softlimit = value;
	}

	/****************************
	void SetSoftlimit()
	-----------------------------
	˵��:
	�޸�����,�����޵�ֵȡ��
	****************************/
	void SetSoftlimit()
	{
		_softlimit = !_softlimit;
	}	

	/****************************
	void AddHandspeed()
	-----------------------------
	˵��:
	�����ֶ��ٶ�,ÿ������һ���ȼ����ڸ�������£���������
	-----------------------------
	****************************/
	void AddHandspeed()
	{
		++ _handspeed;
		if(_handspeed > 3)
		{
			_handspeed = 3;
		}
	}

	/****************************
	void ReduceHandspeed()
	-----------------------------
	˵��:
	��С�ֶ��ٶ�,ÿ�μ�Сһ���ȼ�����΢������£����ټ�С
	-----------------------------
	****************************/
	void ReduceHandspeed()
	{
		-- _handspeed;
		if(_handspeed < 0)
		{
			_handspeed = 0;
		}
	}

	/****************************
	����:
	ԭ��λ��У��.��ǰλ����ԭ��λ������������Χ,����Ϊ����
	-----------------------------
	ԭ��:
	bool CheckOrigin(int type, int error=5)
	-----------------------------
	����:
	type : ԭ������,0:����ԭ��; 1:��ҵԭ��; 2:�ڶ�ԭ��
	error: �����������������,Ĭ��Ϊ5
	-----------------------------
	����ֵ:
	true : ȷ������
	false: λ������
	****************************/
	bool CheckOrigin(int type, int error=5)
	{
		switch(type)
		{
		case 0://����ԭ��
			{break;}
		case 1://��ҵԭ��
			{break;}
		case 2://�ڶ�ԭ��
			{
				//����һ������������ֵ����error,����Ϊ����
				if(abs(this->_SecondOrigin.GetPulse(1) - this->_currentposition.GetPulse(1)) > error)
				{
					return false;
				}
				if(abs(this->_SecondOrigin.GetPulse(2) - this->_currentposition.GetPulse(2)) > error)
				{
					return false;
				}
				if(abs(this->_SecondOrigin.GetPulse(3) - this->_currentposition.GetPulse(3)) > error)
				{
					return false;
				}
				if(abs(this->_SecondOrigin.GetPulse(4) - this->_currentposition.GetPulse(4)) > error)
				{
					return false;
				}
				if(abs(this->_SecondOrigin.GetPulse(5) - this->_currentposition.GetPulse(5)) > error)
				{
					return false;
				}
				if(abs(this->_SecondOrigin.GetPulse(6) - this->_currentposition.GetPulse(6)) > error)
				{
					return false;
				}

				return true;//ȷ������
				break;
			}
		default:return false;break;
		}
		return false;
	}


	/****************************
	����:
	�ֶ��޸�ԭ��λ������
	�ֶ�ָ��Ŀ��λ��
	-----------------------------
	ԭ��:
	bool SetOrigin_Manual(int type, Position value)
	-----------------------------
	����:
	type : ԭ������,0:����ԭ��; 1:��ҵԭ��; 2:�ڶ�ԭ��
	value: Ŀ��λ��
	-----------------------------
	����ֵ
	true : �޸ĳɹ�
	false: �޸�ʧ��
	****************************/
	bool SetOrigin_Manual(int type, Position value)
	{
		switch(type)
		{
		case 0://����ԭ��
			{
				this->_AbsoluteOrigin = value;
				return true;
				break;
			}
		case 1://��ҵԭ��
			{
				this->_WorkOrigin = value;
				return true;
				break;
			}
		case 2://�ڶ�ԭ��
			{
				this->_SecondOrigin = value;
				return true;
				break;
			}
		default:return false;
		}
		return false;
	}

	/***************************************
	�Զ��趨ԭ��λ������
	�Զ��������˵�ǰλ�ñ���Ϊԭ��λ��
	bool SetOrigin_Auto(int type)
	type: ԭ������,0:����ԭ��; 1:��ҵԭ��; 2:�ڶ�ԭ��
	***************************************/
	bool SetOrigin_Auto(int type)
	{
		switch(type)
		{
		case 0://����ԭ��
			{
				this->_AbsoluteOrigin = this->_currentposition;
				return true;break;
			}
		case 1://��ҵԭ��
			{
				this->_WorkOrigin = this->_currentposition;
				return true;break;
			}
		case 2://�ڶ�ԭ��
			{
				this->_SecondOrigin = this->_currentposition;
				return true;break;
			}
		default:return false;break;
		}
		return false;
	}

	Position GetCurrentPosition()//��ȡ��ǰλ��
	{
		return _currentposition;
	}

	int GetRunMode()//��ȡ����ģʽ
	{
		return _runmode;
	}

	void SetRunMode(int newMode)//�޸�����ģʽ
	{
		_runmode = newMode;
	}

	//�����
	//ͨ���������ƻ������ƶ�,ͬʱ�޸���֮��صĲ���
	void Move()
	{
		//�������ƶ�
		/*�ڴ˴�����ƶ������˵Ĵ���*/

		//�޸���Ӧ����
		this->_currentposition = this->RobotCurrentPosition();//�޸ĵ�ǰλ��
	}

	//��û����˵�ǰλ��
	//�ӱ������ж�ȡ���������ֵ,����Position�������ݷ���
	Position RobotCurrentPosition()
	{
		Position pos;
		//��ȡ����ֵ,�޸�pos����
		//ģ���ȡ��������
		pos.SetPulse(6, this->_currentposition.GetPulse(6)+5);
		pos.SetPulse(1, this->_currentposition.GetPulse(1)+5);
		pos.SetPulse(2, this->_currentposition.GetPulse(2)+5);
		pos.SetPulse(3, this->_currentposition.GetPulse(3)+5);
		pos.SetPulse(4, this->_currentposition.GetPulse(4)+5);
		pos.SetPulse(5, this->_currentposition.GetPulse(5)+5);

		return pos;
	}

	/********************************************************* 
	    2010-8-4 16:19:38 
	    bool SetInterfere(bool Type, int No, bool Point, Position Value, int Axis=0)
	----------------------------------------------------------
		����:  �趨����������
	----------------------------------------------------------
		Type:  ����������; true���������,false�����
		No:    ����������
		Point: Max��Min; true�趨Max, false�趨Min
		Value: λ������		
		Aixs:  �����������ʱʹ��,ָ�����趨����
	*********************************************************/
	bool SetInterfere(bool Type, int No, bool Point, Position Value, int Axis=0)
	{
		bool result = false;
		if(Type)//���������
		{
			if(No > _CUBE_SUM)
			{
				return false;
			}
			if(Point)//Max
			{
				this->_cube[No].Max = Value;
				return true;
			}
			else//Min
			{
				this->_cube[No].Min = Value;
				return true;
			}			
		}
		else//�����
		{
			if(No > _AXIS_SUM)//Խ��ʧ��
			{
				return false;
			}

			switch(Axis)
			{
			case 1://S
				{
					if(Point)//Max
					{
						this->_axis[No].Max.SetPulse(1, this->_currentposition.GetPulse(1));
					}
					else
					{
						this->_axis[No].Min.SetPulse(1, this->_currentposition.GetPulse(1));
					}					
					return true;
					break;
				}
			case 2://L
				{
					if(Point)//Max
					{
						this->_axis[No].Max.SetPulse(2, this->_currentposition.GetPulse(2));
					}
					else
					{
						this->_axis[No].Min.SetPulse(2, this->_currentposition.GetPulse(2));
					}					
					return true;
					break;
				}
			case 3://U
				{
					if(Point)//Max
					{
						this->_axis[No].Max.SetPulse(3, this->_currentposition.GetPulse(3));
					}
					else
					{
						this->_axis[No].Min.SetPulse(3, this->_currentposition.GetPulse(3));
					}					
					return true;
					break;
				}
			case 4://R
				{
					if(Point)//Max
					{
						this->_axis[No].Max.SetPulse(4, this->_currentposition.GetPulse(4));
					}
					else
					{
						this->_axis[No].Min.SetPulse(4, this->_currentposition.GetPulse(4));
					}					
					return true;
					break;
				}
			case 5://B
				{
					if(Point)//Max
					{
						this->_axis[No].Max.SetPulse(5, this->_currentposition.GetPulse(5));
					}
					else
					{
						this->_axis[No].Min.SetPulse(5, this->_currentposition.GetPulse(5));
					}					
					return true;
					break;
				}
			case 6://T
				{
					if(Point)//Max
					{
						this->_axis[No].Max.SetPulse(6, this->_currentposition.GetPulse(6));
					}
					else
					{
						this->_axis[No].Min.SetPulse(6, this->_currentposition.GetPulse(6));
					}					
					return true;
					break;
				}
			default:
				return false;
				break;
			}
	
		}
		return result;
	}

	/*******************************
	2010-8-4
	���캯��
	*******************************/
	Robot()
	{
		//��ʼ���ֶ��ٶ�
		this->_ManualHigh = _MANUAL_HIGH;
		this->_ManualMiddle = _MANUAL_MIDDLE;
		this->_ManualLow = _MANUAL_LOW;
		this->_ManualSlow = _MANUAL_SLOW;

		//��ʼ������ģʽΪ"ʾ��"
		_runmode = 0;

		//�ֶ��ٶȳ�ʼ��Ϊ����
		_handspeed = 1;

		//���ޡ�ȫ�����޾���ʼ��Ϊ��Ч
		_softlimit = true;
		_alllimit = true;

		//��ʼ���������
		for(int i=0; i<_AXIS_SUM; ++i)
		{
			_axis[i].SetType(false);
			_cube[i].SetType(true);
		}
	}
};

//extern Robot ROBOT;