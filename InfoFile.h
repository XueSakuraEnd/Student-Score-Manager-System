#pragma once

#include <list>
#include <fstream>
#include <iostream>
#include <string>

#define _F_LOGIN "./login.ini"
#define _F_STOCK "./stock.txt"
#define _F_MESSA "./messa.ini"
using namespace std;

struct msg
{
	string id;		//ѧ��ѧ��
	string name;	//ѧ������
	string sex;		//ѧ���Ա�
	int score1;
	int score2;
	int score3;      //ѧ�������ųɼ�
	int score_sum;	//ѧ���ܳɼ�
};
struct message
{
	string id;		//���
	string m_user;	//�û���
	string m_pwd;	//����
};
class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();
	//ע��
	bool Resider(CString& id,CString& name, CString& pwd);

	//ƥ���½��Ϣ
	bool ReadLogin(CString &name, CString &pwd);

	//��ȡ��¼��Ϣ
	message ReadMessage();
	
	//�޸�����
	void WritePwd(string& id, string& user, string& pwd);

	// ��ȡѧ����Ϣ
	void ReadDocline();

	//ѧ����Ϣд���ļ�
	void WirteDocline();

	//���ѧ����Ϣ
	void Addline(CString id,CString name, CString sex, int score1, int score2, int score3);

	//������Ϣ�����ĵ�
	void Save_Import(CString path);

	//��������Ϣ�����ĵ�
	void New_Import(CString path);
	//����ĵ�
	void Clear_file();
	list<message> vms; //�洢�˻�����
	list<msg> ls;	//�洢ѧ����Ϣ����
	int num;			//������¼ѧ����Ŀ
};

