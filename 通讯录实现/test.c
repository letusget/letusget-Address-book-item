#define _CRT_SECURE_NO_WARNINGS 1

// ���ܲ�����

#include <stdio.h>
#include "contact.h"
#include <string.h>
#include <string.h>

void menu(void);  //��ӡ�����˵�

void main(void)
{
	int input=0;
	//�������ж���ṹ�壬Ҫ��������ͨѶ¼��Ϣ
	
	/*
	struct PeoInfo con[MAX];
	int size;	
		��Ҫ�ж�ͨѶ¼���Ѿ������Ԫ�ظ���������ʣ��Ŀ�λ��������
		����������԰�ͨѶ¼�ĳ�Ա��Ϣ ��ͨѶ¼�����ݸ������洢��һ���ṹ����
	*/
	struct Contact con;  //�½�ͨѶ¼

	//��ʼ��ͨѶ¼
	InitContact(&con);

	//������Ϣ

	do
	{
		menu();
		printf("��ѡ��");
		scanf("%d", &input);

		/*�����ﲻͬ���ֵĺ��岻����ȷ��������ɶ��Բ��ߣ�����ʹ�� ö�� �������������*/
		switch (input)
		{
		default:printf("ѡ�����\n");
			printf("\n");
			break;
		case EXIT:
			SaveContact(&con);  //������ǰ�ȱ����ļ�
			DestroyContact(&con); //����ͨѶ¼���ͷ��ڴ�
			printf("�˳�ͨѶ¼��\n");
			printf("\n");
			break;
		case ADD:

			//������Ϣ
			AddContact(&con);
			break;
		case DEL:DelContact(&con);
			break;
		case SEARCH:SearchContact(&con);
			break;
		case MODIFY:ModifyContact(&con);
			break;
		case SHOW:
			ShowContact(&con);
			break;
		case SORT:SortContact(&con);
			break;
		case SAVE:SaveContact(&con);
			break;

		}
	} while (input);  //���Ժ���Ч�ļ��������Ϣ

	


}

void menu(void)
{
	printf("\n");
	printf("***********************************\n");
	printf("***** 1. add		2. delet  *****\n");
	printf("***** 3.search		4. modify *****\n");
	printf("***** 5. show		6. sort   *****\n");
	printf("***** 7.save		0.exit	  *****\n");
	printf("***********************************\n");
	printf("\n");
}



