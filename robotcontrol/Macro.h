//: Macaro.h
//�궨��ͷ�ļ��������к궨�������ȫ�����ڸ��ļ���
//2010-9-28 10:55:48
#include <string>
using namespace std;
#pragma once

//2010-9-28 11:11:49
const int _CMD_SUM = 20;//�ܵ���������,��TargetOrderName������
//��������
const char TargetOrderName[][9]=
{
	{"START"},    //0
	{"END"},      //1
	
	//�ƶ�����
	{"MOVJ"},     //2
	{"MOVL"},     //3
	{"MOVC"},     //4

	//�źŴ���
	{"SET"},      //5
	{"WAIT"},     //6
	{"DELAY"},    //7

	//���̿���
	{"L"},        //8
	{"GOTO"},     //9
	{"#"},        //10
	{"CALL"},     //11
	{"RET"},      //12

	//��������
	{"DECR"},     //13
	{"INCR"},     //14
	{"R"},        //15

	//ƽ������
	{"PR"},       //16
	{"SHIFTON"},  //17
	{"SHIFTOFF"}, //18
	{"MISHIFT"},  //19
	
	///////////////////////////�ڴ˴�����µ�����
};

const  int      _VALID_CMDLINE     = 20;  //ÿ��������,�û����༭��������
const  int      _NEST_DEEPTH       = 2;   //����Ƕ�׵ĳ������
const  int      _MAXCDMLINE        = _NEST_DEEPTH * _VALID_CMDLINE; //����������ɵ�������

const  int      _PROGRAM_MAXNUMBER = 10;   //�����û����������������
const  int      _PRO_NAME_LENGTH   = 9;    //������������ĳ���
const  int      _PRO_NOTE_LENGTH   = 33;   //����ע������ĳ���
const  int      _CMD_NAME_LENGTH   = 9;    //����������ĳ���
const  int      _CMD_NOTE_LENGTH   = 17;   //ע����������ĳ���
const  int      _CMD_STR_LENGTH    = 9;    //Command�ṹ��str�����ĳ���

const  int      _P_MAX             = 127;  //P�����������
const  int      _P_MIN             = 0;    //P��������С���
const  int      _PR_MAX            = 127;  //PR�����������
const  int      _PR_MIN            = 0;    //PR��������С���
const  int      _R_MAX             = 127;  //R�����������
const  int      _R_MIN             = 0;    //R��������С���
const  int      _PL_MAX            = 7;    //λ�õȼ��������
const  int      _PL_MIN            = 0;    //λ�õȼ�����С���
const  int      _OUT_MAX           = 7;    //OUT�˿ڵ������
const  int      _OUT_MIN           = 0;    //OUT�˿ڵ���С���
const  int      _IN_MAX            = 7;    //IN�˿ڵ������
const  int      _IN_MIN            = 0;    //IN�˿ڵ���С���
const  double   _TIME_MIN          = 1;    //�ȴ�ʱ�����Сֵ   
const  double   _TIME_MAX          = 999;  //�ȴ�ʱ������ֵ

const  int      _R_VARIABLE        = 100;  //R�ͱ����ĸ���
const  int      _P_VARIABLE        = 100;  //P�ͱ����ĸ���
const  int      _PR_VARIABLE       = 100;  //PR�ͱ����ĸ���

const  int      _DELAY_1S          = 65536;//������ʱ1s��Ҫ�Ŀ�ѭ������

const  double   _MANUAL_HIGH       = 40.0;//����50cm/s
const  double   _MANUAL_MIDDLE     = 30.0;//����50cm/s
const  double   _MANUAL_LOW        = 20.0;//����50cm/s
const  double   _MANUAL_SLOW       = 10.0;//����50cm/s

#define         _NET_PORT          6000    //����˿�

//#define    _VARIABLE_NO    128   //��������

//�������ݵĴ���·��
#define    _PROGRAM_LOCATION  "C:\\Data\\%s.pro"
//�����б�Ĵ���·��
#define    _NAMES_LOCATION    "C:\\Data\\Names.nam"
//������������Ĵ���·��
#define    _PRIMARY_LOCATION  "C:\\Data\\Primary.nam"
//ROBOT�����Ĵ���·��
#define    _ROBOT_LOCATION    "C:\\Data\\ROBOT.rob"
//VARIABLE�����Ĵ���·��
#define    _VARIABLE_LOCATION "C:\\Data\\VARIABLE.var"

#define    _FRAME_NO       30    //�û�����ϵ����������ϵ��Ŀ
#define    _IO_SUM         8     //ÿ��IOͨ����IO��Ŀ

#define    _AXIS_SUM       10    //���������Ŀ
#define    _CUBE_SUM       10    //�������������Ŀ
#define    _FRAME_NO       30    //�û�����ϵ����������ϵ��Ŀ
#define    _DELAY_SUM      8     //�̵�����Ŀ
#define    _GIN_SUM        8     //ͨ��������Ŀ
#define    _GOUT_SUM       8     //ͨ�������Ŀ
#define    _SIN_SUM        8     //ר��������Ŀ
#define    _SOUT_SUM       8     //ר�������Ŀ
#define    _IO_SUM         8     //ÿ��IOͨ����IO��Ŀ
#define    _ALARM_SUM      30    //ÿ�鱨���ı�����



