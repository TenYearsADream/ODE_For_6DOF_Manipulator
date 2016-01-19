//PCtest.cpp

#include <iostream>
#include "Execute.h"
#include "PC.h"

using namespace std;

SOCKET PC::PC_socket;
DataPacket PC::m_Data;

bool SEND_FLAG;
bool RECV_FLAG;
extern DWORD WINAPI RECV4BOX(void * Data);
extern DWORD WINAPI SEND2BOX(void * Data);

//����
void Check();

void main()
{
	cout<<sizeof(DataPacket)<<endl;
	PC myPC;

	myPC.CreateSocket();
	if(myPC.Connect())
	{
		cout<<"Connect Successed."<<endl;
	}

	//�¿����ڷ��͵��߳�
	HANDLE hThreadSend = ::CreateThread(NULL, 0, SEND2BOX, NULL, 0, NULL);
	CloseHandle(hThreadSend);
	//�¿����ڽ��յ��߳�
	HANDLE hThreadRecv = ::CreateThread(NULL, 0, RECV4BOX, NULL, 0, NULL);	
	CloseHandle(hThreadRecv);

	::Run(&myPC.m_Data.m_program, myPC.m_Data.ROBOT, myPC.m_Data.VARIABLE);

	while(1);
}

//��BOX��������
DWORD WINAPI RECV4BOX(void * Data)
{
	while(true)
	{
		PC pc;
		pc.Receive();		
		
		Check();//����	
	}
	return 0;
}


//��BOX��������
DWORD WINAPI SEND2BOX(void * Data)
{
	while(true)
	{
		if(true == SEND_FLAG)
		{
			PC pc;
			pc.Send();

			SEND_FLAG = false;
		}		
	}

	return 0;
}

void Check()
{
	PC pc;
	char mission = pc.m_Data.GetMission();
	cout<<"Mission: "<<mission<<endl;

	switch(mission)
	{
	case 'A'://mission A
		{
			cout<<"Key= "<<pc.m_Data.A_Mission.GetKey()<<endl;
			break;
		}
	case 'B'://����һ����֪��
		{
			int point = pc.m_Data.B_Mission.GetTarget();
			if(0 == point)
			{
				cout<<"����ԭ��"<<endl;
			}
			else if(1 == point )
			{
				cout<<"�ڶ�ԭ��"<<endl;
			}
			else if(2 == point)
			{
				cout<<"��ҵԭ��"<<endl;
			}
			else
			{
				cout<<"ԭ�����"<<endl;
			}
			break;
		}
	case 'D'://ǰ��
		{
			char key = pc.m_Data.D_Mission.GetKey();
			if('A' == key)
			{
				cout<<"ǰ��"<<endl;
			}
			else if('B' == key)
			{
				cout<<"������ǰ��"<<endl;
			}
			else if('C' == key)
			{
				cout<<"ת����ǰ��"<<endl;
			}

			break;
		}

	case 'C':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
		{
			break;
		}
	default:
		{
			cout<<"Mission error"<<endl;
			break;
		}
	}
}