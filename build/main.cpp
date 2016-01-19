/*************************************************************************
*                                                                       *
* Open Dynamics Engine, Copyright (C) 2001,2002 Russell L. Smith.       *
* All rights reserved.  Email: russ@q12.org   Web: www.q12.org          *
*                                                                       *
* This library is free software; you can redistribute it and/or         *
* modify it under the terms of EITHER:                                  *
*   (1) The GNU Lesser General Public License as published by the Free  *
*       Software Foundation; either version 2.1 of the License, or (at  *
*       your option) any later version. The text of the GNU Lesser      *
*       General Public License is included with this library in the     *
*       file LICENSE.TXT.                                               *
*   (2) The BSD-style license that is included with this library in     *
*       the file LICENSE-BSD.TXT.                                       *
*                                                                       *
* This library is distributed in the hope that it will be useful,       *
* but WITHOUT ANY WARRANTY; without even the implied warranty of        *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the files    *
* LICENSE.TXT and LICENSE-BSD.TXT for more details.                     *
*                                                                       *
*************************************************************************/

/*
This program demonstrates how the PU joint works.
A PU joint is a combination of a Universal joint and a Slider joint.
It is a universal joint with a slider between the anchor point and
body 1.


The upper yellow body is fixed to the world
The lower yellow body is attached to the upper body by a PU joint
The green object is one aprt of the slider.
The purple object is the second part of the slider.
The red object represent the axis1 of the universal part.
The blue object represent the axis2 of the universal part.
The gray object represent the anchor2 of the PU joint.
*/


#include <ode/ode.h>
#include <drawstuff/drawstuff.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>
#include "texturepath.h"
#include <Manipulator.h>
#include "Defines.h"
#include "RobotControl.h"
#include "stdafx.h"
#include "defines.h"
#include "kinematicPro.h"
#include "head.h"
#include "PC.h"
using namespace std;


#ifdef _MSC_VER
#pragma warning(disable:4244 4305)  // for VC++, no precision loss complaints
#endif
// select correct drawing functions
#ifdef dDOUBLE
#define dsDrawBox dsDrawBoxD
#define dsDrawCylinder dsDrawCylinderD
#define dsDrawCapsule dsDrawCapsuleD
#endif
#define WELDA  30
#define WELDVEL 50000
#define WELDCOUNTER 5


// SOCKET  PC::PC_socket;     //����ͨ�ŵ�SOCKET
// DataPacket PC::m_Data; 

// physics parameters
//const dReal PI = 3.14159265358979323846264338327950288419716939937510;




//ofstream out50("data\\M22.txt");

//camera view
// X����
static float xyz[3] = {3.0f,0.0f,2.0000f};
static float hpr[3] = {180.000f,-20.0000f,0.0000f}; // {-176.000f,-19.5000f,0.0000f};

//Y����
//static float xyz[3] = {0.0f,3.0f,1.5f};
//static float hpr[3] = {-90.000f,-15.0000f,0.0000f}; // {-176.000f,-19.5000f,0.0000f};

static CManipulator SimRobot;
static CRobotControl RobotController(&SimRobot);
//world,space,body & geom
static dWorldID         world;
static dSpaceID         space;
static dJointGroupID    contactgroup;
static dGeomID geomGround;

int ArcSection=0;// the steps that has simulated
int CONTROLLER_TYPE=VELOCITY;
Pose LastGivenPos ;
TracePlan Planner;
PC SCommunication;



	dT44 NewPos=LastGivenPos .pos;
	double Rx=atan2(NewPos.mat[2][1],NewPos.mat[2][2]);
	double sp=sin(Rx);
	double cp=cos(Rx);
	double Ry=atan2(-NewPos.mat[2][0],sp*NewPos.mat[2][1]+cp*NewPos.mat[2][2]);
	double Rz=atan2(sp*NewPos.mat[0][2]-cp*NewPos.mat[0][1],cp*NewPos.mat[1][1]-sp*NewPos.mat[1][2]);
	double x=NewPos.mat[0][3];double y=NewPos.mat[1][3];double z=NewPos.mat[2][3];


int CmdIndex=0;
//double  simstep = 0.0002; ///////////////////////////////////////////////////////////////////////////////////////////////////////////// 1ms simulation steps���沽��
char LASTCODE;
double startpoint[6]={0};
double endpoint[6]={0};
double middlepoint[6]={0};
int PointIndex=0;
int WeldIndex=0;
int WeldSection=0;
SGivenState GivenState;	
SManipulatorState CurrentState;
//collision detection

//static void nearCallback (void *data, dGeomID o1, dGeomID o2)
//{
//	int i,n;
//	dBodyID b1 = dGeomGetBody (o1);
//	dBodyID b2 = dGeomGetBody (o2);
//	if (b1 && b2 && dAreConnectedExcluding (b1,b2,dJointTypeContact) ) return;
//	const int N = 10;
//	dContact contact[N];
//	n = dCollide (o1,o2,N,&contact[0].geom,sizeof (dContact) );
//	if (n > 0)
//	{
//		for  (i=0; i<n; i++) {
//			contact[i].surface.mode = (dContactSlip1 | dContactSlip2 |
//				dContactSoftERP | dContactSoftCFM |
//				dContactApprox1);
//			contact[i].surface.mu = 1;
//			contact[i].surface.slip1 = 0.02;
//			contact[i].surface.slip2 = 0.02;
//			contact[i].surface.soft_erp = 0.01;
//			contact[i].surface.soft_cfm = 0.00001;
//			dJointID c = dJointCreateContact (world,contactgroup,&contact[i]);
//			dJointAttach (c,dGeomGetBody (contact[i].geom.g1),dGeomGetBody (contact[i].geom.g2) );
//	}
//	}
//}

// SimStart simulation - set viewpoint
static void SimStart()
{
	dAllocateODEDataForThread(dAllocateMaskAll);
	dsSetViewpoint (xyz,hpr);
	for(int i=0;i<6;++i)
	{
			GivenState.angle[i]=LastGivenPos .lev[i].para.joint_angle;
			GivenState.speed[i]=0;
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int result; 
	int const len = sizeof(SCommunication.m_Data);
	cout<<"���ݰ���С����   :"<<len<<endl;

	//�¿����ڷ��͵���

	if(SCommunication.CreateSocket()==true)
	{
		printf("��ʼ���ɹ�\n");
		do
		{
			printf("�ȴ�����........\n");
			result=SCommunication.Connect();
		}while(result==0);		
			printf("���ӳɹ�\n");
			
	}
	else
		printf("�׽��ִ���ʧ��\n");

	
}





// function to SimControl camera position at each step.
void SimControl()
{

	CurrentState.angle[0]=dJointGetHingeAngle(SimRobot.jointManipulator[0].joint);
	CurrentState.angle[0]=-CurrentState.angle[0];
	CurrentState.angle[1]=dJointGetHingeAngle(SimRobot.jointManipulator[1].joint);
	CurrentState.angle[2]=dJointGetHingeAngle(SimRobot.jointManipulator[2].joint);
	CurrentState.angle[3]=dJointGetHingeAngle(SimRobot.jointManipulator[4].joint);
	CurrentState.angle[4]=dJointGetHingeAngle(SimRobot.jointManipulator[5].joint);
	CurrentState.angle[5]=dJointGetHingeAngle(SimRobot.jointManipulator[6].joint);

	CurrentState.speed[0]=dJointGetHingeAngleRate(SimRobot.jointManipulator[0].joint);
	CurrentState.speed[0]=-CurrentState.speed[0];
	CurrentState.speed[1]=dJointGetHingeAngleRate(SimRobot.jointManipulator[1].joint);
	CurrentState.speed[2]=dJointGetHingeAngleRate(SimRobot.jointManipulator[2].joint);
	CurrentState.speed[3]=dJointGetHingeAngleRate(SimRobot.jointManipulator[4].joint);
	CurrentState.speed[4]=dJointGetHingeAngleRate(SimRobot.jointManipulator[5].joint);
	CurrentState.speed[5]=dJointGetHingeAngleRate(SimRobot.jointManipulator[6].joint);

	RobotController.GetManipulatorState(CurrentState);
	RobotController.GetGivenState(GivenState);
	RobotController.Controller(CONTROLLER_TYPE);

	switch(CONTROLLER_TYPE)/////////////////////////////////////222222222222222222222222222222222222222222222222
	{
			case ANGLE:
					for(int i=0;i<NUMOFLEGJOINTS;i++)
					{
						dBodySetPosition(SimRobot.jointManipulator[i].bodyJoint,RobotController.positionLink[i].pos[0],RobotController.positionLink[i].pos[1],RobotController.positionLink[i].pos[2]);
						dBodySetRotation(SimRobot.jointManipulator[i].bodyJoint,RobotController.positionLink[i].rot);
					}
					break;
			case VELOCITY:
					for(int i=0;i<NUMOFLEGJOINTS;i++)
					{
						dJointSetHingeParam(SimRobot.jointManipulator[i].joint, dParamFMax, MaxForce);
					}	
					dJointSetHingeParam(SimRobot.jointManipulator[0].joint,dParamVel,RobotController.CommandManipulator.vel[0]);
					dJointSetHingeParam(SimRobot.jointManipulator[1].joint,dParamVel,RobotController.CommandManipulator.vel[1]);
					dJointSetHingeParam(SimRobot.jointManipulator[2].joint,dParamVel,RobotController.CommandManipulator.vel[2]);
					dJointSetHingeParam(SimRobot.jointManipulator[4].joint,dParamVel,RobotController.CommandManipulator.vel[3]);
					dJointSetHingeParam(SimRobot.jointManipulator[5].joint,dParamVel,RobotController.CommandManipulator.vel[4]);
					dJointSetHingeParam(SimRobot.jointManipulator[6].joint,dParamVel,RobotController.CommandManipulator.vel[5]);
					break;
			case FORCE:
					dJointAddHingeTorque(SimRobot.jointManipulator[0].joint,RobotController.CommandManipulator.force[0]);
					dJointAddHingeTorque(SimRobot.jointManipulator[1].joint,RobotController.CommandManipulator.force[1]);
					dJointAddHingeTorque(SimRobot.jointManipulator[2].joint,RobotController.CommandManipulator.force[2]);
					dJointAddHingeTorque(SimRobot.jointManipulator[4].joint,RobotController.CommandManipulator.force[3]);
					dJointAddHingeTorque(SimRobot.jointManipulator[5].joint,RobotController.CommandManipulator.force[4]);
					dJointAddHingeTorque(SimRobot.jointManipulator[6].joint,RobotController.CommandManipulator.force[5]);
					break;
			default:
					break;
	}

	//�Ϳͻ���ͨ��ʱ������ĺ�����������
	//Receive_Send();	
}


// called when a key pressed
static void Type_Select (int cmd)
{
	switch (cmd)
	{
		  case 'a': case 'A':
			  CONTROLLER_TYPE=ANGLE;
			  break;
		  case 'V':case 'v':
			  CONTROLLER_TYPE=VELOCITY;
			  break;
		  case 'F':case 'f':
			  CONTROLLER_TYPE=FORCE;
			  break;
	}
}

//static void drawBox (dGeomID id, int R, int G, int B)
//{
//	if (!id)
//		return;
//
//	const dReal *pos = dGeomGetPosition (id);
//	const dReal *rot = dGeomGetRotation (id);
//	dsSetColor (R,G,B);
//
//	dVector3 l; 
//	dGeomBoxGetLengths (id, l);
//	dsDrawBox (pos, rot, l);
//}
//static void drawTransformBox (dGeomID id, int R, int G, int B)
//{
//	if (!id)
//		return;
//
//	const dReal *pos = dGeomGetPosition (id);
//	const dReal *rot = dGeomGetRotation (id);
//	dsSetColor (R,G,B);
//
//	dVector3 l; 
//	dGeomBoxGetLengths (dGeomTransformGetGeom (id), l);
//	dsDrawBox (pos, rot, l);
//}
//
//static void drawCylinder (dGeomID id, int R, int G, int B)
//{
//	if (!id)
//		return;
//
//	const dReal *pos = dGeomGetPosition (id);
//	const dReal *rot = dGeomGetRotation (id);
//	dsSetColor (R,G,B);
//
//	dReal l,r;
//	dGeomCylinderGetParams(id,&r,&l);
//	dsDrawCylinder(pos, rot, l,r);
//}

// simulation loop



bool SwingWeld(double A,double vel,int counter)
{			

	if(WeldIndex<=counter)
	{
			for(int i=0;i<6;++i)
			{
				startpoint[i]=LastGivenPos.lev[i].para.joint_angle;
			}
			for(int i=0;i<6;++i)
					endpoint[i]=startpoint[i]; 
			if(WeldSection==0||WeldSection==3)
			{
				endpoint[4]+=A*Pi/180;
			}
			else
			{
				endpoint[4]-=A*Pi/180;
			}
			Planner.init(JMETHOD,endpoint,startpoint,vel,startpoint,5000);
			if(PointIndex<=Planner.Total)
			{
				Planner.Traceplanning(PointIndex,GivenState.angle);
				++PointIndex;
			}
			else
			{
	
				++WeldSection;
				if(WeldSection==4)
				{
					WeldSection=0;
					++WeldIndex;
				}
				LastGivenPos.update(endpoint);
				PointIndex=0;		
			}
			return false;
	}
	else
	{
		WeldIndex=0;
		return true;
	}

}



int CmdExcute(Program *pro, CommandLine cmd, Robot &ROBOT, UserVariable &VARIABLE, int &go)
{
	int result = 0;//ִ�н��,Ԥ�ȸ�ֵΪ0
//	int n;
//	double temp[6];
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
			for(int i=0;i<6;++i)
			{
				startpoint[i]=LastGivenPos.lev[i].para.joint_angle;
			}
			for(int i=0;i<6;++i)
				endpoint[i]=0; 			
			Planner.init(JMETHOD,endpoint,startpoint,50000,startpoint,5000);
			if(PointIndex<=Planner.Total)
			{
				Planner.Traceplanning(PointIndex,GivenState.angle);
				++PointIndex;
			}
			else
			{
				cout<<"���"<<go<<"���"<<endl;
				++go;
				LastGivenPos.update(endpoint);
				PointIndex=0;
			}
			break;
		}
		case 1:     //END
		{//done
			if(SwingWeld(WELDA,WELDVEL,WELDCOUNTER)==true)
			go = pro->GetLineNumber();//��֤���������˳�
			//return 0;//�������
			break;
		}
		//////////////////�˶�����
		case 2:     //MOVJ
		{		

			for(int i=0;i<6;++i)
			{
				startpoint[i]=LastGivenPos.lev[i].para.joint_angle;
			}
			for(int i=0;i<6;++i)
				endpoint[i]=cmd.Target.GetPulse(i+1); 
			Planner.init(JMETHOD,endpoint,startpoint,50000,startpoint,5000);
			if(PointIndex<=Planner.Total)
			{
				Planner.Traceplanning(PointIndex,GivenState.angle);
				++PointIndex;
			}
			else
			{
				cout<<"���"<<go<<"���"<<endl;
				++go;
				LastGivenPos.update(endpoint);
				PointIndex=0;
				
			}


		break;
		}
	case 3:     //MOVL
		{//done
			//////////////////////////////////////////////////////////////////////////
			//�ڴ�����ƶ������˵Ĵ���
			//////////////////////////////////////////////////////////////////////////
			//int n=0;
			for(int i=0;i<6;++i)
			{
				startpoint[i]=LastGivenPos.lev[i].para.joint_angle;
			}
			for(int i=0;i<6;++i)
				endpoint[i]=cmd.Target.GetPulse(i+1); 
			Planner.init(CMETHOD,endpoint,startpoint,2000,startpoint,5000);	
			if(PointIndex<=Planner.Total)
			{
				Planner.Traceplanning(PointIndex,GivenState.angle);
				++PointIndex;
			}
			else
			{
				LastGivenPos.update(endpoint);
				PointIndex=0;
				cout<<"���"<<go<<"���"<<endl;
				++go;
			}

			break;
		}
	case 4:     //MOVC
		{
			for(int i=0;i<6;++i)
			{
				startpoint[i]=LastGivenPos.lev[i].para.joint_angle;
			}
			if(ArcSection==0)
			{
				for(int i=0;i<6;++i)
				{
					middlepoint[i]=cmd.Target.GetPulse(i+1);	
				}
				ArcSection=1;
				++go;
			}
			else
			{
				for(int i=0;i<6;++i)
				{
					endpoint[i]=cmd.Target.GetPulse(i+1); 
				}
				Planner.init(ARCMETHOD,endpoint,startpoint,50000,middlepoint,50000);	
				if(PointIndex<=Planner.Total)
				{
					Planner.Traceplanning(PointIndex,GivenState.angle);
					++PointIndex;
				}
				else
				{
					LastGivenPos.update(endpoint);
					PointIndex=0;
					ArcSection=0;
					cout<<"���"<<go<<"���"<<endl;
					++go;
				}
			
			}
			break;
		}
		//////////////////�źŴ���
	case 5:     //SET
		{//done
			bool value = cmd.GetbVariable();//�õ�ON/OFF
			int No = cmd.GetiVariable(1);
			ROBOT._GOUT.io[No].SetValue(value);//�޸�IO
			cout<<"���"<<go<<"���"<<endl;
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
					{
						cout<<"���"<<go<<"���"<<endl;//�Ѿ�����ȴ�����
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
				
				cout<<"���"<<go<<"���"<<endl;//Ϊ����INͨ���ȴ�����,���ȴ�ʱ���ѵ�
				++go;
			} 
			else//����
			{
				cout<<"���"<<go<<"����"<<endl;
				result=60;//60�Ŵ���,WAIT�����str1��������
			}					
			
			//++go;
			break;
		}
	case 7:     //DELAY
		{
			double t = cmd.GetdVariable();//�õ���ʱ��ʱ��
			cout<<"���"<<go<<"���"<<endl;
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
					cout<<"���"<<go<<"���"<<endl;
					go = i;
					break;//ִ�гɹ�
				}
			}
			cout<<"���"<<go<<"����"<<endl;
			result=90;//������Ϣ90 : ��תĿ�Ĳ�����
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
			VARIABLE._R[No] += 1;  
			cout<<"���"<<go<<"���"<<endl;//�Լ�1
			++go;
			break;
		}
	case 15:     //R
		{
			VARIABLE.R = cmd.GetiVariable(1);//��ֵ��ȫ��R����
			cout<<"���"<<go<<"���"<<endl;
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
			{cout<<"���"<<go<<"����"<<endl;
				result=160;//160�Ŵ���,PR����str2����
			}					
			cout<<"���"<<go<<"���"<<endl;
			++go;
			break;
		}
	case 17:     //SHIFON
		{
			//////////////////////////////////////////////////////////////////////////
			//�ڴ����ƽ�ƿ�ʼ����
			//////////////////////////////////////////////////////////////////////////
			cout<<"���"<<go<<"���"<<endl;
			++go;
			break;
		}
	case 18:     //SHIFOFF
		{
			//////////////////////////////////////////////////////////////////////////
			//�ڴ����ƽ�ƽ�������
			//////////////////////////////////////////////////////////////////////////
			cout<<"���"<<go<<"���"<<endl;
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
			cout<<"���"<<go<<"���"<<endl;
			++go;
			break;
		}
		
	default:break;
	}//switch			
			return result;
}//CmdExcute()
			 
		 

 //int Step(Program *pro, Robot &ROBOT, UserVariable &VARIABLE)
 //{		 
	// int result = 0;//���н��
	// //////////////////////////////////////////////////////
	// static int CurrentLine = 0;//��ǰִ�е�������
	// 
	// bool End = false;//�Ƿ�ִ�е����һ�г���
	// if(pro->GetLineNumber() == CurrentLine)//ִ�е����һ��
	// {
	//	 End = true;
	// }	
	// 
	// result = CmdExcute(pro, pro->commands[CurrentLine], ROBOT, VARIABLE, CurrentLine);
	// //////////////////////////////////////////////////////
	// 
	// if(End)//ִ�е����һ��
	// {
	//	 CurrentLine = 0;//�޸ĵ�ǰ������
	// }
	// 
	// return result;
 //}//int Step()




 void SimUpdate()
{
		
	
		//double simstep = 0.001; ///////////////////////////////////////////////////////////////////////////////////////////////////////////// 5ms simulation steps���沽��

		//dSpaceCollide (space,0,&nearCallback);////��ײ���
		dWorldStep (world, simstep);
		dJointGroupEmpty (contactgroup);		
		dsSetTexture (DS_WOOD);
		SimRobot.drawManipulator();
	
}



 void Joint_Teaching()
{

 
	double Manual_Vel=SCommunication.m_Data.ROBOT.GetManualSpeed();
	//double Manual_Vel=50000;
	char Key=SCommunication.m_Data.A_Mission.GetKey();
	//char Key='A';
	if(Key=='A')
	{
		GivenState.angle[0]+=Manual_Vel*simstep;
		GivenState.speed[0]=Manual_Vel;
	}
	if(Key=='B')
	{
		GivenState.angle[0]-=Manual_Vel*simstep;
		GivenState.speed[0]=Manual_Vel;
	}
	if(Key=='C')
	{
		GivenState.angle[1]+=Manual_Vel*simstep;
		GivenState.speed[1]=Manual_Vel;
	}
	if(Key=='D')
	{
		GivenState.angle[1]-=Manual_Vel*simstep;
		GivenState.speed[1]=Manual_Vel;
	}
	if(Key=='E')
	{
		GivenState.angle[2]+=Manual_Vel*simstep;
		GivenState.speed[2]=Manual_Vel;
	}
	if(Key=='F')
	{
		GivenState.angle[2]-=Manual_Vel*simstep;
		GivenState.speed[2]=Manual_Vel;
	}
	if(Key=='G')
	{
		GivenState.angle[3]+=Manual_Vel*simstep;
		GivenState.speed[3]=Manual_Vel;
	}
	if(Key=='H')
	{
		GivenState.angle[3]-=Manual_Vel*simstep;
		GivenState.speed[3]=Manual_Vel;
	}
	if(Key=='I')
	{
		GivenState.angle[4]+=Manual_Vel*simstep;
		GivenState.speed[4]=Manual_Vel;
	}
	if(Key=='J')
	{
		GivenState.angle[4]-=Manual_Vel*simstep;
		GivenState.speed[4]=Manual_Vel;
	}
	if(Key=='K')
	{
		GivenState.angle[5]+=Manual_Vel*simstep;
		GivenState.speed[5]=Manual_Vel;
	}
	if(Key=='L')
	{
		GivenState.angle[5]-=Manual_Vel*simstep;
		GivenState.speed[5]=Manual_Vel;
	}

	for(int i=0;i<6;++i)
	{
		if(GivenState.angle[i]>(LastGivenPos .lev[i].para.max-0.08))
			GivenState.angle[i]=LastGivenPos .lev[i].para.max-0.08;
		if(GivenState.angle[i]<(LastGivenPos .lev[i].para.min+0.08))
			GivenState.angle[i]=LastGivenPos .lev[i].para.min+0.08;
	}

	LastGivenPos.update(GivenState.angle);
}

void Carte_Teaching()
{

	double lastGiventh1=GivenState.angle[0];
	double lastGiventh2=GivenState.angle[1];
	double lastGiventh3=GivenState.angle[2];
	double lastGiventh4=GivenState.angle[3];
	double lastGiventh5=GivenState.angle[4];
	double lastGiventh6=GivenState.angle[5];
	double Manual_Vel=SCommunication.m_Data.ROBOT.GetManualSpeed();
	char Key=SCommunication.m_Data.A_Mission.GetKey();



	NewPos=LastGivenPos .pos;
	Rx=atan2(NewPos.mat[2][1],NewPos.mat[2][2]);
	sp=sin(Rx);
	cp=cos(Rx);
	Ry=atan2(-NewPos.mat[2][0],sp*NewPos.mat[2][1]+cp*NewPos.mat[2][2]);
	 Rz=atan2(sp*NewPos.mat[0][2]-cp*NewPos.mat[0][1],cp*NewPos.mat[1][1]-sp*NewPos.mat[1][2]);
	 x=NewPos.mat[0][3];
	y=NewPos.mat[1][3];
	z=NewPos.mat[2][3];


	if(Key=='A')
	{
		NewPos.mat[0][3]=NewPos.mat[0][3]+Manual_Vel*simstep*100;
	}
	if(Key=='B')
	{
		NewPos.mat[0][3]=NewPos.mat[0][3]-Manual_Vel*simstep*100;
	}
	if(Key=='C')
	{
		NewPos.mat[1][3]=NewPos.mat[1][3]+Manual_Vel*simstep*100;
	}
	if(Key=='D')
	{
		NewPos.mat[1][3]=NewPos.mat[1][3]-Manual_Vel*simstep*100;
	}
	if(Key=='E')
	{
		NewPos.mat[2][3]=NewPos.mat[2][3]+Manual_Vel*simstep*100;
	}
	if(Key=='F')
	{
		NewPos.mat[2][3]=NewPos.mat[2][3]-Manual_Vel*simstep*100;
	}	
	if(Key=='G')
	{
			Rx+=Manual_Vel*simstep;
			double a[4][4]={{1,0,0,0},{0,cos(Rx),-sin(Rx),0},{0,sin(Rx),cos(Rx),0},{0,0,0,1}};
			double b[4][4]={{cos(Ry),0,sin(Ry),0},{0,1,0,0},{-sin(Ry),0,cos(Ry),0},{0,0,0,1}};
			double c[4][4]={{cos(Rz),-sin(Rz),0,0},{sin(Rz),cos(Rz),0,0},{0,0,1,0},{0,0,0,1}};
			dT44 Rotx(a);
			dT44 Roty(b);
			dT44 Rotz(c);
			NewPos=Rotz*Roty*Rotx;
			NewPos.mat[0][3]=x;NewPos.mat[1][3]=y;NewPos.mat[2][3]=z;
	}
	if(Key=='H')
	{
			Rx-=Manual_Vel*simstep;
			double a[4][4]={{1,0,0,0},{0,cos(Rx),-sin(Rx),0},{0,sin(Rx),cos(Rx),0},{0,0,0,1}};
			double b[4][4]={{cos(Ry),0,sin(Ry),0},{0,1,0,0},{-sin(Ry),0,cos(Ry),0},{0,0,0,1}};
			double c[4][4]={{cos(Rz),-sin(Rz),0,0},{sin(Rz),cos(Rz),0,0},{0,0,1,0},{0,0,0,1}};
			dT44 Rotx(a);
			dT44 Roty(b);
			dT44 Rotz(c);
			NewPos=Rotz*Roty*Rotx;
			NewPos.mat[0][3]=x;NewPos.mat[1][3]=y;NewPos.mat[2][3]=z;
	}
	if(Key=='I')
	{
			Ry+=Manual_Vel*simstep;
			double a[4][4]={{1,0,0,0},{0,cos(Rx),-sin(Rx),0},{0,sin(Rx),cos(Rx),0},{0,0,0,1}};
			double b[4][4]={{cos(Ry),0,sin(Ry),0},{0,1,0,0},{-sin(Ry),0,cos(Ry),0},{0,0,0,1}};
			double c[4][4]={{cos(Rz),-sin(Rz),0,0},{sin(Rz),cos(Rz),0,0},{0,0,1,0},{0,0,0,1}};
			dT44 Rotx(a);
			dT44 Roty(b);
			dT44 Rotz(c);
			NewPos=Rotz*Roty*Rotx;
			NewPos.mat[0][3]=x;NewPos.mat[1][3]=y;NewPos.mat[2][3]=z;
	}
	if(Key=='J')
	{
			Ry-=Manual_Vel*simstep;
			double a[4][4]={{1,0,0,0},{0,cos(Rx),-sin(Rx),0},{0,sin(Rx),cos(Rx),0},{0,0,0,1}};
			double b[4][4]={{cos(Ry),0,sin(Ry),0},{0,1,0,0},{-sin(Ry),0,cos(Ry),0},{0,0,0,1}};
			double c[4][4]={{cos(Rz),-sin(Rz),0,0},{sin(Rz),cos(Rz),0,0},{0,0,1,0},{0,0,0,1}};
			dT44 Rotx(a);
			dT44 Roty(b);
			dT44 Rotz(c);
			NewPos=Rotz*Roty*Rotx;
			NewPos.mat[0][3]=x;NewPos.mat[1][3]=y;NewPos.mat[2][3]=z;
	}
	if(Key=='K')
	{
			Rz+=Manual_Vel*simstep;
			double a[4][4]={{1,0,0,0},{0,cos(Rx),-sin(Rx),0},{0,sin(Rx),cos(Rx),0},{0,0,0,1}};
			double b[4][4]={{cos(Ry),0,sin(Ry),0},{0,1,0,0},{-sin(Ry),0,cos(Ry),0},{0,0,0,1}};
			double c[4][4]={{cos(Rz),-sin(Rz),0,0},{sin(Rz),cos(Rz),0,0},{0,0,1,0},{0,0,0,1}};
			dT44 Rotx(a);
			dT44 Roty(b);
			dT44 Rotz(c);
			NewPos=Rotz*Roty*Rotx;
			NewPos.mat[0][3]=x;NewPos.mat[1][3]=y;NewPos.mat[2][3]=z;
	}
	if(Key=='L')
	{
			Rz-=Manual_Vel*simstep;
			double a[4][4]={{1,0,0,0},{0,cos(Rx),-sin(Rx),0},{0,sin(Rx),cos(Rx),0},{0,0,0,1}};
			double b[4][4]={{cos(Ry),0,sin(Ry),0},{0,1,0,0},{-sin(Ry),0,cos(Ry),0},{0,0,0,1}};
			double c[4][4]={{cos(Rz),-sin(Rz),0,0},{sin(Rz),cos(Rz),0,0},{0,0,1,0},{0,0,0,1}};
			dT44 Rotx(a);
			dT44 Roty(b);
			dT44 Rotz(c);
			NewPos=Rotz*Roty*Rotx;
			NewPos.mat[0][3]=x;NewPos.mat[1][3]=y;NewPos.mat[2][3]=z;
	}

	GSK::Inverse_Kinematics(NewPos,GivenState.angle,LastGivenPos);
	for(int i=0;i<6;++i)
	GivenState.speed[i]=(GivenState.angle[i]-LastGivenPos.lev[i].para.joint_angle)/simstep;
	for(int i=0;i<6;++i)
	{
		if(GivenState.angle[i]>(LastGivenPos .lev[i].para.max-0.08))
			GivenState.angle[i]=LastGivenPos .lev[i].para.max-0.08;
		if(GivenState.angle[i]<(LastGivenPos .lev[i].para.min+0.08))
			GivenState.angle[i]=LastGivenPos .lev[i].para.min+0.08;
	}
	LastGivenPos.update(GivenState.angle);

}







	void GoOrigin()
{
			int i=0;
			int type=SCommunication.m_Data.B_Mission.GetTarget();
			double lastGiventh[6]={0};
			for(i=0;i<6;++i)
			{
				startpoint[i]=LastGivenPos.lev[i].para.joint_angle;
			}	
			if(type==0)
			{
				for( i=0;i<6;++i)
					endpoint[i]=SCommunication.m_Data.ROBOT._AbsoluteOrigin.GetPulse(i+1);
			}
			if(type==1)
			{
				for( i=0;i<6;++i)
					endpoint[i]=SCommunication.m_Data.ROBOT._SecondOrigin.GetPulse(i+1);
			}
			if(type==2)
			{
				for( i=0;i<6;++i)
					endpoint[i]=SCommunication.m_Data.ROBOT._WorkOrigin.GetPulse(i+1);
			}
			for(i=0;i<6;++i)
			lastGiventh[i]=GivenState.angle[i];
			Planner.init(JMETHOD,endpoint,startpoint,5000,startpoint,5000);
			if(PointIndex<Planner.Total)
			{
				Planner.Traceplanning(PointIndex,GivenState.angle);
				++PointIndex;
			}
			else
			{
				LastGivenPos.update(GivenState.angle);
				PointIndex=0;
			}
			for(i=0;i<6;++i)
			GivenState.speed[i]=(GivenState.angle[i]-lastGiventh[i])/simstep;


}




void Forward()
{
	  
	int result = 0;
	int CmdTotal=SCommunication.m_Data.m_program.GetLineNumber();
	int OrderNo=0;
	 
	 if(CmdIndex<CmdTotal)//�ӵ�һ��������һ��
	 {	
		for(int i=0; i<63; i++)
		{
			if(strcmp(SCommunication.m_Data.m_program.commands[CmdIndex].GetName(),TargetOrderName[i])==0)
			{
				OrderNo = i;
				break;
			}
		}
		if(OrderNo==2||OrderNo==3||OrderNo==4)
		{
			result = CmdExcute(&(SCommunication.m_Data.m_program),SCommunication.m_Data.m_program.commands[CmdIndex], SCommunication.m_Data.ROBOT, SCommunication.m_Data.VARIABLE, CmdIndex);
		}
		else
			++CmdIndex;

	 }		 
}


void Backward()
{
	  
	  int result = 0;

	int CmdTotal=SCommunication.m_Data.m_program.GetLineNumber();
	// int CmdTotal=testpro.GetLineNumber();
	 int OrderNo=0;
	 int invline;
	 
	 if(CmdIndex<=CmdTotal)//�ӵ�һ��������һ��
	 {	
		invline=CmdTotal-CmdIndex;
		for(int i=0; i<63; i++)
		{
			if(strcmp(SCommunication.m_Data.m_program.commands[invline].GetName(),TargetOrderName[i])==0)
			//if(strcmp(testpro.commands[CmdIndex].GetName(),TargetOrderName[i])==0)
			{
				OrderNo = i;
				break;
			}
		}
		if(OrderNo==2||OrderNo==3||OrderNo==4)
		{
			result = CmdExcute(&(SCommunication.m_Data.m_program),SCommunication.m_Data.m_program.commands[invline], SCommunication.m_Data.ROBOT, SCommunication.m_Data.VARIABLE, CmdIndex);
		}
		else
			++CmdIndex;


	 }	


}


void PlayBack()
{

	 int result = 0;
	 int CmdTotal=SCommunication.m_Data.m_program.GetLineNumber(); 
	 if(CmdIndex<CmdTotal)//�ӵ�һ��������һ��
	 {
		 result = CmdExcute(&(SCommunication.m_Data.m_program),SCommunication.m_Data.m_program.commands[CmdIndex], SCommunication.m_Data.ROBOT, SCommunication.m_Data.VARIABLE, CmdIndex);
		 if(result!=0)//ʧ���˳�
		 {
			 SCommunication.send_Data.state=false;
			 
		 }	
		 else
			 SCommunication.send_Data.state=true;

	 }	 
	 if(CmdIndex>=CmdTotal)//ִ�е����һ��
	 {
		 CmdIndex = 0;//�޸ĵ�ǰ������
	 }	
	 
}

void CmdStop()
{
	for(int i=0;i<6;++i)
	{
		GivenState.angle[i]=CurrentState.angle[i];
	}
		CmdIndex=0;
		PointIndex=0;
		WeldIndex=0;
		WeldSection=0;
		ArcSection=0;
		LastGivenPos.update(GivenState.angle);	
}


void CmdPause()
{

	for(int i=0;i<6;++i)
	{
		GivenState.angle[i]=CurrentState.angle[i];
	}
	
}

void Testing()
{
	 int result = 0;

	 int CmdTotal=SCommunication.m_Data.m_program.GetLineNumber();
	 
	 if(CmdIndex<CmdTotal)//�ӵ�һ��������һ��
	 {
		 int Last = CmdIndex;//�����ϴ����е��к�
		 result = CmdExcute(&(SCommunication.m_Data.m_program),SCommunication.m_Data.m_program.commands[CmdIndex], SCommunication.m_Data.ROBOT, SCommunication.m_Data.VARIABLE, CmdIndex);//ִ�е��г���
		 if(result!=0)//ʧ���˳�
		 {
			 SCommunication.send_Data.state=false;		 
		 }	
		 else
			 SCommunication.send_Data.state=true;
	 }	
	 if((LASTCODE!='I')&&(LASTCODE!='G'))//ִ�е����һ��
	 {
		 CmdIndex = 0;//�޸ĵ�ǰ������
	 }	

}





static void SimLoop (int pause)
{
	SCommunication.Receive();
	char CODE=SCommunication.m_Data.GetMission();
	if(CODE=='A')
	{
		if(SCommunication.m_Data.ROBOT.GetFrameType()==0){ //��������,0�ؽ�����,1ֱ������,2��������,3�û�����
			Joint_Teaching();
			cout<<"�ؽڿռ�ʾ����...."<<endl;}
		else
		{
			Carte_Teaching();
			cout<<"ֱ�ǿռ�ʾ����...."<<endl;
		}
	}
	if(CODE=='B')
	{
			GoOrigin();
			cout<<"����ԭ��"<<endl;
	}

	if(CODE=='D')
	{
			Forward();
			cout<<"ǰ��"<<endl;
	}
	
	if(CODE=='E')
	{
			Backward();
			cout<<"����"<<endl;
	}

	if(CODE=='F')
	{
		
			PlayBack();
			cout<<"����"<<endl;
	}
		if(CODE=='H')
	{
		
			CmdStop();
			cout<<"ֹͣ"<<endl;
	}
	if(CODE=='I')
	{
		
			CmdPause();
			cout<<"��ͣ"<<endl;
	}

	if(CODE=='G')
	{
		
			Testing();
			cout<<"������"<<endl;
	}
	SimUpdate();
	SimControl();
	LASTCODE=CODE;
	SCommunication.send_Data.Pos.SetPulse(1,CurrentState.angle[0]);
	SCommunication.send_Data.Pos.SetPulse(2,CurrentState.angle[1]);
	SCommunication.send_Data.Pos.SetPulse(3,CurrentState.angle[2]);
	SCommunication.send_Data.Pos.SetPulse(4,CurrentState.angle[3]);
	SCommunication.send_Data.Pos.SetPulse(5,CurrentState.angle[4]);
	SCommunication.send_Data.Pos.SetPulse(6,CurrentState.angle[5]);
	SCommunication.Send(true);
}


int main (int argc, char **argv)/////1111
{
	dsFunctions fn;
	fn.version          = DS_VERSION;
	fn.start            = &SimStart;
	fn.step             = &SimLoop;
	fn.command          = &Type_Select;
	fn.stop             = 0;
	fn.path_to_textures = DRAWSTUFF_TEXTURE_PATH; 
	//initialize:brief ODE data allocation 
	dInitODE2(0);
	world = dWorldCreate();//create world first
	dWorldSetERP (world, 0.01);//set error limitation
	dWorldSetGravity (world,0,0,-9.81);///////////////////////////////////////////////////////////////////////////////////////////////////////////�����������ٶ�
	space = dHashSpaceCreate (0);//Create collision detection space
	contactgroup = dJointGroupCreate (0);//Create joint group to store joints
	geomGround = dCreatePlane (space, 0,0,1,0);//creat static ground
	SimRobot.CreateManipulator(world,space);
	printf ("-----------------------------------------------------------------------------\n");
	printf ("                          �����ɶȹؽڻ�����ODE����ƽ̨                  \n");
	printf ("    ˵��:��ƽ̨����ODE��Ҫ���ڴ��������˵��˶�ѧ�Ͷ���ѧ���漰��������ʵ�����    \n");
	printf ("    ��ѡ����:  \n");
	printf ("    -a/-A| --�Ƕȿ�����ѡ������ʱ���ã�\n");
	printf ("    -V/-v| --�ٶȿ�����ѡ������ʱ���ã�\n");
	printf ("    -F/-f| --���ؿ�����ѡ������ʱ���ã�\n");
	printf ("     Ĭ��3D�����ļ�·��= %s\n", DRAWSTUFF_TEXTURE_PATH);
	printf ("------------------------------------------------------------------------------\n");
	printf ("       Hit any key to continue:");
	_getch();

	dsSimulationLoop (argc,argv,400,300,&fn);////////////-1-1-1-1-1
	dJointGroupDestroy (contactgroup);
	dSpaceDestroy (space);
	dWorldDestroy (world);
	dCloseODE();
	return 0;
}

