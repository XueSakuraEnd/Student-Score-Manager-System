#include "pch.h"
#include "InfoFile.h"


CInfoFile::CInfoFile()
{
}


CInfoFile::~CInfoFile()
{
}
//ע��
bool CInfoFile::Resider(CString& id,CString& name, CString& pwd)
{
	message mes;
	ifstream ifs;
	ifs.open(_F_LOGIN, ios::in);
	if (!ifs.is_open())
	{
		ofstream p_ofs;
		p_ofs.open(_F_LOGIN, ios::out);
		p_ofs.close();
	}
	char buf[1024] = { 0 };
	char* ptr = NULL;
	while (!ifs.eof())
	{
		ifs.getline(buf, sizeof(buf));
		char* sst = strtok_s(buf, " ", &ptr);
		if (sst != NULL)
		{
			mes.id = sst;
		}
		else
		{
			break;
		}
		sst = strtok_s(NULL, " ", &ptr);
		mes.m_user = sst;
		sst = strtok_s(NULL, " ", &ptr);
		mes.m_pwd = sst;
		if ((CString)mes.m_user.c_str() == name)
		{
			return FALSE;
		}
	}
	ofstream ofs;
	ofs.open(_F_LOGIN, ios::out | ios::app);
	std::string STDStr1(CW2A(id.GetString()));
	std::string STDStr2(CW2A(name.GetString()));
	std::string STDStr3(CW2A(pwd.GetString()));//CString ת string
	ofs << STDStr1 << " " << STDStr2 << " " << STDStr3 << endl;
	ofs.close();
	return TRUE;
}

//ƥ���½��Ϣ
bool CInfoFile::ReadLogin(CString &name, CString &pwd)
{
	ifstream ifs; //�����ļ��������
	ifs.open(_F_LOGIN,ios::in); //���ļ�

	char buf[1024] = { 0 };
	char* ptr = NULL;
	while (!ifs.eof())
	{
		
		ifs.getline(buf, sizeof(buf));
		char* sst = strtok_s(buf, " ", &ptr);
		message mes;
		if (sst != NULL)
		{
			mes.id = sst;//���
		}
		else
		{
			break;
		}
		
		sst = strtok_s(NULL, " ", &ptr);
		mes.m_user = sst;
		sst = strtok_s(NULL, " ", &ptr);
		mes.m_pwd = sst;
		vms.push_back(mes);
	}
	ifs.close();
	for (list<message>::iterator it = vms.begin();it != vms.end();it++)
	{
		if (name == (CString)it->m_user.c_str() && pwd == (CString)it->m_pwd.c_str())
		{
			ifs.close();
			ofstream ofs;
			ofs.open(_F_MESSA, ios::out | ios::trunc);
			ofs << it->id << " " << it->m_user << " " << it->m_pwd << endl;
			ofs.close();
			return TRUE;
		}
	}
	ifs.close();
	return FALSE;
}

//��ȡ��¼��Ϣ
message CInfoFile::ReadMessage()
{
	message mes;
	ifstream ifs;
	ifs.open(_F_MESSA, ios::in);
	char buf[1024] = { 0 };
	char* ptr = NULL;
	ifs.getline(buf, sizeof(buf));
	char* sst = strtok_s(buf," ", &ptr);
	mes.id = sst;
	sst = strtok_s(NULL, " ", &ptr);
	mes.m_user = sst;
	sst = strtok_s(NULL, " ", &ptr);
	mes.m_pwd = sst;
	ifs.close();
	return mes;
}

//�޸�����
void CInfoFile::WritePwd(string& id, string& user, string& pwd)
{
	for (list<message>::iterator it = vms.begin(); it != vms.end(); it++)
	{
		if (it->id == id && it->m_user == user)
		{
			vms.erase(it);
			break;
		}
	}
	message mes;
	mes.id = id;
	mes.m_user = user;
	mes.m_pwd = pwd;
	vms.push_back(mes);
	ofstream ofs;	 //�����ļ��������
	ofs.open(_F_LOGIN,ios::out | ios::trunc); //���ļ�
	for (list<message>::iterator it = vms.begin(); it != vms.end(); it++)
	{
		ofs << it->id << " ";
		ofs << it->m_user << " ";
		ofs << it->m_pwd << " " << endl;
	}
	ofs.close();	//�ر��ļ�
	ofstream ofs1;
	ofs1.open(_F_MESSA, ios::out | ios::trunc);
	ofs1 << id << " " << user << " " << pwd << endl;
	ofs1.close();
}

//��ȡѧ����Ϣ
void CInfoFile::ReadDocline()
{
	ifstream ifs(_F_STOCK, ios::in); //���뷽ʽ���ļ�
	if (!ifs.is_open())
	{
		ofstream ofs(_F_STOCK, ios::out);
		ofs << "ѧ��ѧ�� ѧ������ �Ա� ��һ�ųɼ� �ڶ��ųɼ� �����ųɼ� �ܷ�" << endl; //д���ͷ
		ofs.close();
		return;
	}
	char ch;
	ifs >> ch;
	
	if (ifs.eof())
	{
		ofstream ofs(_F_STOCK,ios::out);
		ofs << "ѧ��ѧ�� ѧ������ �Ա� ��һ�ųɼ� �ڶ��ųɼ� �����ųɼ� �ܷ�" << endl; //д���ͷ
		ofs.close();
		num = 0;
		return;
	}
	char buf[1024] = { 0 };
	num = 0;	//��ʼ��ѧ����ĿΪ0
	ls.clear();
	//ȡ����ͷ
	ifs.getline(buf, sizeof(buf));
	char* ptr = NULL;
	while (!ifs.eof()) //û���ļ���β
	{
		msg tmp;

		ifs.getline(buf, sizeof(buf)); //��ȡһ��
		num++;	//ѧ����Ŀ��һ

		//AfxMessageBox(CString(buf));
		char *sst = strtok_s(buf, " ",&ptr); //�ԡ�|���и�
		if (sst != NULL)
		{
			tmp.id = sst; //ѧ��ѧ��
		}
		else
		{
			break;
		}

		sst = strtok_s(NULL, " ",&ptr);
		tmp.name = sst;	//ѧ������

		sst = strtok_s(NULL, " ",&ptr);
		tmp.sex = sst;	//ѧ���Ա�

		sst = strtok_s(NULL, " ", &ptr);
		tmp.score1 = atoi(sst);	//ѧ�����ųɼ�
		sst = strtok_s(NULL, " ", &ptr);
		tmp.score2 = atoi(sst);	//ѧ�����ųɼ�
		sst = strtok_s(NULL, " ", &ptr);
		tmp.score3 = atoi(sst);	//ѧ�����ųɼ�
		sst = strtok_s(NULL, " ", &ptr);
		tmp.score_sum = atoi(sst);	//ѧ�����ųɼ��ܷ�
		ls.push_back(tmp); //��������ĺ���
	}

	ifs.close(); //�ر��ļ�
}

//ѧ����Ϣ¼���ļ�
void CInfoFile::WirteDocline()
{
	ofstream ofs(_F_STOCK, ios::trunc);//�����ʽ���ļ�
	ofs << "ѧ��ѧ�� ѧ������ �Ա� ��һ�ųɼ� �ڶ��ųɼ� �����ųɼ� �ܷ�" << endl; //д���ͷ

	//	//ͨ��������ȡ���������ݣ�д���ļ����ԡ�|���ָ�����β�ӻ���
	for (list<msg>::iterator it = ls.begin(); it != ls.end(); it++)
	{
		ofs << it->id << " ";
		ofs << it->name << " ";
		ofs << it->sex << " ";
		ofs << it->score1 << " ";
		ofs << it->score2 << " ";
		ofs << it->score3 << " ";
		ofs << it->score_sum << endl;
	}
	ofs.close();//�ر��ļ�
	ls.clear();
}

//���ѧ����Ϣ
//id:ѧ��ѧ��, name:ѧ������, sex:ѧ���Ա�, arr[3]:ѧ�����ſ�Ŀ�ɼ�
void CInfoFile::Addline(CString id, CString name, CString sex, int score1, int score2, int score3)
{
	msg tmp;

		//ѧ����Ϣ��Ч
		if (!id.IsEmpty() || !name.IsEmpty() || !sex.IsEmpty())
		{
			CStringA str1;
			str1 = id;
			tmp.id = str1.GetBuffer();	//ѧ��CStringA str2;
			CStringA str2;
			str2 = name;	//CStringתCStirngA
			tmp.name = str2.GetBuffer(); //CStirngAתchar *����Ʒ����
			CStringA str3;
			str3 = sex;	//CStringתCStirngA
			tmp.sex = str3.GetBuffer();
			tmp.score1 = score1;
			tmp.score2 = score2;
			tmp.score3 = score3;
			tmp.score_sum = score1 + score2 + score3;
			ls.push_back(tmp);	//��������ĺ���
		}
}

void CInfoFile::Clear_file()
{
	this->ls.clear();
	ofstream ofs;
	ofs.open(_F_STOCK, ios::trunc);
	ofs.close();
}

void CInfoFile::Save_Import(CString path)//�����ļ������ĵ�
{
	string str;
	std::string STDStr1(CW2A(path.GetString()));//CString ת string
	str = STDStr1;
	ifstream ifs;
	ifs.open(str, ios::in);
	char buf[1024] = { 0 };
	ifs.getline(buf, sizeof(buf));
	char* ptr = NULL;
	while (!ifs.eof()) //û���ļ���β
	{
		msg tmp;

		ifs.getline(buf, sizeof(buf)); //��ȡһ��

		//AfxMessageBox(CString(buf));
		char* sst = strtok_s(buf, " ", &ptr); //�ԡ� ���и�
		if (sst != NULL)
		{
			tmp.id = sst; //ѧ��ѧ��
		}
		else
		{
			break;
		}

		sst = strtok_s(NULL, " ", &ptr);
		tmp.name = sst;	//ѧ������

		sst = strtok_s(NULL, " ", &ptr);
		tmp.sex = sst;	//ѧ���Ա�

		sst = strtok_s(NULL, " ", &ptr);
		tmp.score1 = atoi(sst);	//ѧ�����ųɼ�
		sst = strtok_s(NULL, " ", &ptr);
		tmp.score2 = atoi(sst);	//ѧ�����ųɼ�
		sst = strtok_s(NULL, " ", &ptr);
		tmp.score3 = atoi(sst);	//ѧ�����ųɼ�
		sst = strtok_s(NULL, " ", &ptr);
		tmp.score_sum = atoi(sst);	//ѧ�����ųɼ��ܷ�
		ls.push_back(tmp); //��������ĺ���
	}
	ifs.close(); //�ر��ļ�
	ofstream ofs(_F_STOCK, ios::trunc);//�����ʽ���ļ�
	ofs << "ѧ��ѧ�� ѧ������ �Ա� ��һ�ųɼ� �ڶ��ųɼ� �����ųɼ� �ܷ�" << endl; //д���ͷ

	//	//ͨ��������ȡ���������ݣ�д���ļ����ԡ�|���ָ�����β�ӻ���
	for (list<msg>::iterator it = ls.begin(); it != ls.end(); it++)
	{
		ofs << it->id << " ";
		ofs << it->name << " ";
		ofs << it->sex << " ";
		ofs << it->score1 << " ";
		ofs << it->score2 << " ";
		ofs << it->score3 << " ";
		ofs << it->score_sum << endl;
	}
	ofs.close();//�ر��ļ�
}

void CInfoFile::New_Import(CString path)
{
	string str;
	std::string STDStr1(CW2A(path.GetString()));//CString ת string
	str = STDStr1;
	ifstream ifs;
	ifs.open(str, ios::in);
	char buf[1024] = { 0 };
	ifs.getline(buf, sizeof(buf));
	char* ptr = NULL;
	while (!ifs.eof()) //û���ļ���β
	{
		msg tmp;

		ifs.getline(buf, sizeof(buf)); //��ȡһ��

		//AfxMessageBox(CString(buf));
		char* sst = strtok_s(buf, " ", &ptr); //�ԡ� ���и�
		if (sst != NULL)
		{
			tmp.id = sst; //ѧ��ѧ��
		}
		else
		{
			break;
		}

		sst = strtok_s(NULL, " ", &ptr);
		tmp.name = sst;	//ѧ������

		sst = strtok_s(NULL, " ", &ptr);
		tmp.sex = sst;	//ѧ���Ա�

		sst = strtok_s(NULL, " ", &ptr);
		tmp.score1 = atoi(sst);	//ѧ�����ųɼ�
		sst = strtok_s(NULL, " ", &ptr);
		tmp.score2 = atoi(sst);	//ѧ�����ųɼ�
		sst = strtok_s(NULL, " ", &ptr);
		tmp.score3 = atoi(sst);	//ѧ�����ųɼ�
		sst = strtok_s(NULL, " ", &ptr);
		tmp.score_sum = atoi(sst);	//ѧ�����ųɼ��ܷ�
		ls.push_back(tmp); //��������ĺ���
	}
	ifs.close(); //�ر��ļ�
	ofstream ofs(_F_STOCK, ios::trunc);//�����ʽ���ļ�
	ofs << "ѧ��ѧ�� ѧ������ �Ա� ��һ�ųɼ� �ڶ��ųɼ� �����ųɼ� �ܷ�" << endl; //д���ͷ

	//	//ͨ��������ȡ���������ݣ�д���ļ����ԡ�|���ָ�����β�ӻ���
	for (list<msg>::iterator it = ls.begin(); it != ls.end(); it++)
	{
		ofs << it->id << " ";
		ofs << it->name << " ";
		ofs << it->sex << " ";
		ofs << it->score1 << " ";
		ofs << it->score2 << " ";
		ofs << it->score3 << " ";
		ofs << it->score_sum << endl;
	}
	ofs.close();//�ر��ļ�
}
