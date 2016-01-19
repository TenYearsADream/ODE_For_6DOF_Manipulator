//PC.h
//PC�����ڽ������ݵĽṹ��

#include <Winsock2.h>
#include <memory.h>
#include "DataPacket.h"

#define _BOX_ADDR "127.0.0.1"//BOX��IP��ַ
#define NET_PORT 6000//����˿ں�

struct PC
{
private:
	SOCKET PC_socket;     //����ͨ�ŵ�SOCKET

public:
	DataPacket m_Data;           //��BOX���յ�����
	C_information send_Data;     //��BOX���͵�����

public:
	/**************************************
	bool Comunicate()
	��BOX����ͨ��,��ʹ�þ�̬SOCKET
	**************************************/
	bool Comunicate()
	{
		//SOCKADDR_IN addrBOX;//BOX�ĵ�ַ
		//addrBOX.sin_addr.S_un.S_addr = inet_addr(_BOX_ADDR);
		//addrBOX.sin_family = AF_INET;
		//addrBOX.sin_port = htons(6000);

		//int result = connect(this->PC_socket, (SOCKADDR*)&addrBOX, sizeof(SOCKADDR));

		//char* Recv_buffer = new char[sizeof(this->m_Data)];//����һ�����ݻ�����
		//int size = recv(this->PC_socket, Recv_buffer, sizeof(this->m_Data), 0);//��������

		//if(sizeof(this->m_Data) != size)//����ʧ��
		//{
		//	delete Recv_buffer;
		//	return false;
		//}
		//else
		//{
		//	memcpy(&this->m_Data, Recv_buffer, sizeof(this->m_Data));//�ѽ��յ������ݿ���������
		//	delete Recv_buffer;
		//	return true;
		//}
		return false;

	}//Comunicate()

	/**************************************
	PC()
	���캯��, ���׽��ֽ��а汾Э��
	��"�����͵�����"���г�ʼ��
	**************************************/
	PC()
	{
		//�׽��ֵİ汾Э��
		WORD version = MAKEWORD(1,1);//1.1�汾
		WSADATA wsaData;

		WSAStartup(version, &wsaData);//�����׽���
		//���������ݵĳ�ʼ��
	}//PC()

	/**************************************
	~PC()
	��������,�����ݽ�������
	**************************************/
	~PC()
	{
	//	WSACleanup();//�ر��׽���
	}//~PC()

	/**************************************
	bool CreateSocket()
	�����׽���,����ֵ��PC_socket
	---------------------------------------
	true  : �����ɹ�
	false : ����ʧ��
	**************************************/
	bool CreateSocket()
	{
		this->PC_socket = socket(AF_INET, SOCK_STREAM, 0);

		if(INVALID_SOCKET == this->PC_socket)
		{
			return false;
		}
		else
		{
			return true;
		}
	}//CreateSocket()

	/**************************************
	bool Connect()
	��BOX��������
	---------------------------------------
	true  : ���ӳɹ�
	false : ����ʧ��
	**************************************/
	bool Connect()
	{
		SOCKADDR_IN addrBOX;//BOX�ĵ�ַ
		addrBOX.sin_addr.S_un.S_addr = inet_addr(_BOX_ADDR);
		addrBOX.sin_family = AF_INET;
		addrBOX.sin_port = htons(NET_PORT);

		int result = connect(this->PC_socket, (SOCKADDR*)&addrBOX, sizeof(SOCKADDR));

		if(SOCKET_ERROR == result)
		{
			return false;
		}
		else
		{
			return true;
		}
	}//Accept()

	/**************************************
	bool Send()
	��BOX��������
	---------------------------------------
	true  : ���ͳɹ�
	false : ����ʧ��
	**************************************/
	bool Send()
	{
		int const len = sizeof(this->m_Data);
		char* Send_buffer = new char[len];//�������ݻ�����
		memcpy(Send_buffer, &this->m_Data, len);//��Ҫ���͵�����,������������

		int size = send(this->PC_socket, Send_buffer, len, 0);//����
		delete Send_buffer;//�رջ�����
		
		if(len == size)
		{
			return true;
		}
		else
		{
			return false;
		}
	}//Send()

	//bool Send(bool Flag)
	//��BOX��������,������Mission����,ֻ����λ�˺��û�����VARIABLE
	//Flag : ֻ��������ԭ��Send()��������,�����κ�����
	//���� :
	//true  : ���ͳɹ�
	//false : ����ʧ��
	bool Send(bool Flag)
	{
		//int const size_Variable = sizeof(this->m_Data.VARIABLE);
		int const size_C = sizeof(this->m_Data.C_Mission);
		//int const len = size_Variable + size_C; //���ݻ�������С
		int const len = size_C;

		char *Send_buffer = new char[len];//���ݻ�����
		//memcpy(Send_buffer, &this->m_Data.VARIABLE, size_Variable);//�����û�����VARIABLE
		//memcpy(Send_buffer+size_Variable, &this->m_Data.C_Mission, size_C);//����C_Mission
		memcpy(Send_buffer, &this->send_Data, len);

		int Send_size = send(this->PC_socket, Send_buffer, len, 0);//����
		delete Send_buffer;//�ر����ݻ�����

		if(len == Send_size)
		{
			return true;
		}
		else
		{
			return false;
		}

	}//Send()

	/**************************************
	bool Receive()
	��BOX��������
	---------------------------------------
	true  : ���ճɹ�
	false : ����ʧ��
	**************************************/
	bool Receive()
	{
		char* Recv_buffer = new char[sizeof(this->m_Data)];//�������ݻ�����
		int size = recv(this->PC_socket, Recv_buffer, sizeof(this->m_Data), 0);//��������
		memcpy(&this->m_Data, Recv_buffer, sizeof(this->m_Data));//��������
		delete Recv_buffer;//�ر����ݻ�����

		if(sizeof(this->m_Data) == size)
		{
			return true;
		}
		else
		{
			return false;
		}
	}//Receive()

};//PC