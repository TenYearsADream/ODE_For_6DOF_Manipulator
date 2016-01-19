//Position.h  λ��������λ�ñ�����ͷ�ļ�
//2010-7-11 16:48:46
#include "Macro.h"
#include "kinematicPro.h"
#pragma once

typedef struct Position
{
	private:
		//λ������
		double x, y, z;//ĩ�˿ռ�λ��
		double Rx, Ry, Rz;//С������������н�
		//��������
		double S, L, U, R, B, T;//��������
		//����ֱ�����껹�ǹؽ�����, true ֱ������, false�ؽ�����
		
	public:
		dT44 Tpos;
		bool Flag;
		
		Position()              //���캯��
		{
			S = L = U = R = B = T = 0;
			this->Pulse2Pos();
			Flag = false;//�ؽ�����
		}
		void Clear()            //���
		{
			S = L = U = R = B = T = 0;
			x = y = z = Rx = Ry = Rz = 0.0;
			Flag = false;
			this->Pulse2Pos();
		}

		//��ȡFlag
		bool GetFlag()
		{
			return Flag;
		}

		//�޸�Flag
		void SetFlag(bool value)
		{
			Flag = value;
		}

		void Pulse2Pos()        //����ֵת��Ϊ�ռ�����
		{
			Pulse2T();
			T2pos();			
		}

		void Pos2Pulse()        //�ռ�����ת��Ϊ����ֵ
		{
		}
		void T2pos()
		{
			Rx=atan2(Tpos.mat[2][1],Tpos.mat[2][2]);
			double sp=sin(Rx);
			double cp=cos(Rx);
			Ry=atan2(-Tpos.mat[2][0],sp*Tpos.mat[2][1]+cp*Tpos.mat[2][2]);
			Rz=atan2(sp*Tpos.mat[0][2]-cp*Tpos.mat[0][1],cp*Tpos.mat[1][1]-sp*Tpos.mat[1][2]);
		}

		void Pulse2T()
		{
			Pose temp;
			double angle[6]={S,L,U,R,B,T};
			temp.update(angle);
			Tpos=temp.pos;
		}
		void Pos2T()
		{
			double a[4][4]={{1,0,0,0},{0,cos(Rx),-sin(Rx),0},{0,sin(Rx),cos(Rx),0},{0,0,0,1}};
			double b[4][4]={{cos(Ry),0,sin(Ry),0},{0,1,0,0},{-sin(Ry),0,cos(Ry),0},{0,0,0,1}};
			double c[4][4]={{cos(Rz),-sin(Rz),0,0},{sin(Rz),cos(Rz),0,0},{0,0,1,0},{0,0,0,1}};
			dT44 Rotx(a);
			dT44 Roty(b);
			dT44 Rotz(c);
			Tpos=Rotz*Roty*Rotx;
			Tpos.mat[0][3]=x;Tpos.mat[1][3]=y;Tpos.mat[2][3]=z;
		}
		double GetPulse(int No)       //��ȡ����ֵ
		{
			double result;
			switch(No)
			{
			case 1: result = S; break;
			case 2: result = L; break;
			case 3: result = U; break;
			case 4: result = R; break;
			case 5: result = B; break;
			case 6: result = T; break;
			default: break;
			}
			return result;
		}
		void SetPulse(int No,double value) //�޸�����ֵ
		{
			switch(No)
			{
			case 1: S = value; break;
			case 2: L = value; break;
			case 3: U = value; break;
			case 4: R = value; break;
			case 5: B = value; break;
			case 6: T = value; break;
			default: break;
			}
			this->Pulse2Pos(); 
			this->Pulse2T();//ͬ���޸�����ֵ����
		}
		double GetPos(int No)      //��ȡ����ֵ
		{
			double result;
			switch(No)
			{
			case 1: result = x;  break;
			case 2: result = y;  break;
			case 3: result = z;  break;
			case 4: result = Rx; break;
			case 5: result = Ry; break;
			case 6: result = Rz; break;
			default: break;
			}
			return result;
		}
		void SetPos(int No, double value)//�޸�����ֵ
		{
			switch(No)
			{
			case 1: x  = value; break;
			case 2: y  = value; break;
			case 3: z  = value; break;
			case 4: Rx = value; break;
			case 5: Ry = value; break;
			case 6: Rz = value; break;
			default: break;
			}
			this->Pos2Pulse();
			this->Pos2T();//ͬ���޸���������
		}
		//���������
		Position & operator += (Position & right)//+=
		{
			S += right.S; L += right.L; U += right.U;
			R += right.R; B += right.B; T += right.T;
			this->Pulse2Pos();//ͬ���޸�����ֵ
			this->Pulse2T();
			return *this;
		}
		Position & operator += (int right)//+=
		{
			S += right; L += right; U += right;
			R += right; B += right; T += right;
			this->Pulse2Pos();//ͬ���޸�����ֵ
			this->Pulse2T();
			return *this;
		}
		Position & operator -= (Position & right)//-=
		{
			S -= right.S; L -= right.L; U -= right.U;
			R -= right.R; B -= right.B; T -= right.T;
			this->Pulse2Pos();//ͬ���޸�����ֵ
			this->Pulse2T();
			return *this;
		}
		Position & operator -= (int right)//-=
		{
			S -= right; L -= right; U -= right;
			R -= right; B -= right; T -= right;
			this->Pulse2Pos();//ͬ���޸�����ֵ
			this->Pulse2T();
			return *this;
		}
		Position & operator *= (int right)// *=
		{
			S *= right; L *= right; U *= right;
			R *= right; B *= right; T *= right;
			this->Pulse2Pos();//ͬ���޸�����ֵ
			this->Pulse2T();
			return *this;
		}
		Position & operator /= (int right)// /=
		{
			S /= right; L /= right; U /= right;
			R /= right; B /= right; T /= right;
			this->Pulse2Pos();//ͬ���޸�����ֵ
			this->Pulse2T();
			return *this;
		}
}_POSITION;



//λ���ͱ���
typedef struct POStype
{
	public:
		Position value;
	private:
		char Note[17];
		
	public:
		POStype()//���캯��
		{
			strcpy(Note, "");
		}
		void Clear()//���
		{
			value.Clear();
			strcpy(Note, "");
		}
		Position GetValue()//��ȡvalue
		{
			return value;
		}
		void SetValue(Position newvalue)//�޸�value
		{
			value = newvalue;
		}
		char * GetNote()//��ȡע��
		{
			return Note;
		}
		void SetNote(char * newnote)//�޸�ע��
		{
			strcpy(Note, newnote);
		}
		//���������
		POStype & operator += (POStype & right)//+=
		{
			value += right.value;
			return *this;
		}
		POStype & operator += (int right)
		{
			value += right;
			return *this;
		}
		POStype & operator -= (POStype & right)
		{
			value -= right.value;
			return *this;
		}
		POStype & operator -= (int right)
		{
			value -= right;
			return *this;
		}
		POStype & operator *= (int right)
		{
			value *= right;
			return *this;
		}
		POStype & operator /= (int right)
		{
			value /= right;
			return *this;
		}
}_POSTYPE;
