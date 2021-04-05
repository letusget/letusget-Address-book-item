#define _CRT_SECURE_NO_WARNINGS 1

//#define MAX 1000

#define MAX_NAME 20
#define MAX_SEX 5
#define MAX_TELE 12
#define MAX_ADDR 30
#define DEFAULT_SZ 3 //����ǳ�ʼ��ʱ���Դ洢��ͨѶ¼��Ա�ĸ���

#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <errno.h>  //�ļ�������صĻ���string.hͷ�ļ�

enum Option
{//��˵�������Ӧ
	EXIT,  //0
	ADD,  //1
	DEL,  //2
	SEARCH,  //3
	MODIFY,  //4
	SHOW,  //5
	SORT,  //6
	SAVE  //7
};

//����������
/*
Ҫʵ�ֿ��Դ��1000��������Ϣ���������֣��绰���Ա�סַ������
�������Ӻ�����Ϣ
����ɾ��ָ�����ֵĺ�����Ϣ
���Բ��Һ�����Ϣ
�����޸ĺ�����Ϣ
���Դ�ӡ������Ϣ
����
*/

//�����ﶨ����ֳ�����ֵ�����Է���������޸�


typedef struct PeoInfo
{
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	char tele[MAX_TELE];
	char addr[MAX_ADDR];

}PeoInfo;

typedef struct Contact  //ͨѶ¼����
{
	//���������ռ����洢��Ϣ������������������룬ÿ��������С
	struct PeoInfo *data; 
	int size;//��¼��ǰ�Ѿ������ͨѶ¼����
	int capacity;  //��ǰͨѶ¼�������������������������µĿռ�
}Contact;

void menu(void);  //��ӡ�����˵�
void InitContact(struct Contact* ps);  //��ʼ��ͨѶ¼�ṹ��
void AddContact(struct Contact* ps);  //���ͨѶ¼��Ϣ
void ShowContact(const struct Contact* ps);  //��ʾ�������Ϣ,��Ҫ�����޸ģ�����const����
void DelContact(struct Contact* ps);  //ɾ��ָ����ϵ��
void SearchContact(const struct Contact* ps);  //����ָ������
void ModifyContact(struct Contact* ps);  //�޸�ָ����ֵ
void SortContact(struct Contact* ps);  //ͨѶ¼����
void DestroyContact(Contact* ps);  //����ͨѶ¼�ͷ��ڴ�
void SaveContact(Contact* ps);  //�����Ѿ��������Ϣ�ļ�
void LoadContact(Contact* ps);
