#define _CRT_SECURE_NO_WARNINGS 1

//ʵ�ֺ���������

#include <stdio.h>
#include "contact.h"

//�����ٳ��� main����������
//void main(void)
//{
//
//
//}

int FindName(struct Contact* ps, char name[MAX_NAME]);  //���������Ƿ��ڸ�ͨѶ¼��
void CheckCapacity(struct Contact* ps);  //���ͨѶ¼�����Ƿ���

void LoadContact(Contact* ps)
{
	FILE* pfRead = fopen("contact.txt","rb");
	PeoInfo tmp = { 0 };  //��ʱ�����������Ϣ
	if (pfRead == NULL)
	{
		printf("coadContact: %s\n", strerror(errno));//����������ʾ��ͬ�Ĵ�����Ϣ
		return;
	}
	//��ȡ�ļ�����ŵ�ͨѶ¼��
	while (fread(&tmp, sizeof(PeoInfo), 1, pfRead))
	{
		//�ֱ��� �������ݵĵ�ַ�������һ����Ԫ�Ĵ�С��ÿ�ζ���ĸ������ļ���
		//������ʵ������Ԫ�صĸ���
		
		CheckCapacity(ps);  //��������Ƿ���Դ洢����������Ծ�����
		ps->data[ps->size] = tmp;
		ps->size++;  //��������
		
	}
	printf("�ɹ���ȡ�ϴα������Ϣ��\n");
	fclose(pfRead);
	pfRead = NULL;

}

void InitContact(struct Contact* ps)  //��ʼ��ͨѶ¼�ṹ��
{
	ps->data = (struct PeoInfo* )malloc(DEFAULT_SZ * sizeof(struct PeoInfo));
	//��data�ĳ�ʼ�������ֻ������λ�ã�Ϊ���޸ķ��㣬��������Զ����DEFAULT_SZ
	if (ps->data == NULL)
	{
		return;
	}
	ps->size = 0;
	ps->capacity = DEFAULT_SZ;  //��ʼ��С

	//��ʵ�ֽ�ͨѶ¼�����ļ�֮��Ϳ������´γ�ʼ����ʱ�����������Щ��Ϣ
	LoadContact(ps);  //ps ���ǵ�ַ�������������ﲻ��ȡ��ַ��&

}

void CheckCapacity(struct Contact* ps)
{
	if (ps->size == ps->capacity)
	{
		//����
		struct PeoInfo* ptr = realloc(ps->data, (ps->capacity + 2)*sizeof(struct PeoInfo));
		//��ԭ���ĵ�ַ�ϣ������������洢�ռ�
		if (ptr != NULL)
		{
			ps->data = ptr;
			ps->capacity += 2;
			printf("���ݳɹ���\n");
		}
		else
		{
			printf("����ʧ�ܣ�\n");
		}
	}
}

void AddContact(struct Contact * ps)  //���ͨѶ¼��Ϣ
{
	//if (ps->size == MAX)
	//{
	//	printf("ͨѶ¼�������޷�������ӣ�");

	//}
	//else
	
	//�������������ͨѶ¼�����������ӿռ䣨�����������û������������
	CheckCapacity(ps);
		printf("���������֣�");
		scanf("%s", ps->data[ps->size].name);
		//�洢��data����ĵ�size��λ�õ�name����

		printf("���������䣺");
		scanf("%d", &(ps->data[ps->size].age));
		//��Ϊ���ﴫ�ݵ��ǵ�ַ��Ҫ�����ݴ洢�����λ�õı�����
		while (0>ps->data[ps->size].age || 150<ps->data[ps->size].age )
		{
			printf("���������������������룺");
			scanf("%d", &(ps->data[ps->size].age));
		}

		printf("�������Ա�");
		scanf("%s", ps->data[ps->size].sex);

		printf("������绰���룺");
		scanf("%s", ps->data[ps->size].tele);
		while (11 != strlen(ps->data[ps->size].tele))//�Ե绰���볤�ȵļ��
		{
			printf("�绰��������λ������11λ�绰���룩�����������룺");
			scanf("%s", ps->data[ps->size].tele);
		}

		printf("������סַ��");
		scanf("%s", ps->data[ps->size].addr);
		ps->size++;
		printf("�����Ϣ�ɹ���\n");
		printf("\n");

}

void ShowContact(const struct Contact * ps)
{//���ݵ��ǵ�ַ������Ҫ����ı��Ѿ��洢��ֵ�Ŀ��ܣ����Ծ���const������
	if (ps->size == 0)
	{
		printf("��ǰͨѶ¼��û�г�Ա��\n");
		printf("\n");

	}
	else
	{
		int i;
		printf("%-20s \t %-4s \t %-5s \t %-12s \t %-20s\n", "����", "����", "�Ա�", "�绰", "��ַ");
		//�ȴ�ӡһ�б�ͷ
		for (i = 0; i < ps->size; i++)
		{
			printf("%-20s \t %-4d \t %-5s \t %-12s \t %-20s\n",
				ps->data[i].name,
				ps->data[i].age,
				ps->data[i].sex,
				ps->data[i].tele,
				ps->data[i].addr);
		}
	}
}

void DelContact(struct Contact * ps)
{
	printf("������Ҫɾ�����˵����֣�");
	char name[MAX_NAME];
	scanf("%s", name);

	//�Ȳ��ң���ɾ����Ҫ�ҳ�Ҫɾ����Ԫ�����ڵ�λ��
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		/*strcmp �ַ����ȽϺ���
		C���� strcmp() �������ڶ������ַ������бȽϣ����ִ�Сд����ͷ�ļ���string.h
	�﷨/ԭ�ͣ�
	int strcmp(const char* stri1��const char* str2);
	���� str1 �� str2 �ǲ���Ƚϵ������ַ�����
	strcmp() ����� ASCII �������αȽ� str1 �� str2 ��ÿһ���ַ���ֱ�������Ҳ������ַ���
	���ߵ����ַ���ĩβ������\0����
	����ֵ = 0, ���ʾ str1 ���� str2
    ����ֵ < 0�����ʾ str1 С�� str2��
	����ֵ > 0�����ʾ str2 С�� str1������ֵ = 0�����ʾ str1 ���� str2��
		*/
		if (0 == strcmp(ps->data[i].name,name))
		{
			break;  //��ʱ i ��ΪҪɾ����Ԫ��
		}
	}

	if (i == ps->size)
	{
		printf("��Ǹ��Ҫɾ����Ԫ�ز����ڣ�");
		printf("\n");
	}
	else
	{
		int j=0;
		for (j = i; j < ps->size-1; j++)//�����±�Ҫ����һ��  
		{//��i��ʼ�������ú����Ԫ�� ����ǰһ��Ԫ��
			ps->data[j] = ps->data[j + 1];
		}
		ps->size--;
		printf("ɾ��ͨѶ¼��Ա�ɹ���\n");
		printf("\n");

	}

}
/*�ں����ķ�������ǰ���Ϲؼ���static�������ͱ������Ϊ��̬������
��ͨ�����Ķ��������Ĭ���������extern�ģ�����̬����ֻ�������������ļ����пɼ���
���ܱ������ļ����á���˶��徲̬���������ºô���
����<1> �����ļ��п��Զ�����ͬ���ֵĺ��������ᷢ����ͻ��
����<2> ��̬�������ܱ������ļ����á�*/
static int FindName(const struct Contact* ps, char name[MAX_NAME])
{
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		if (0 == strcmp(ps->data[i].name, name))
		{
			return i;  //�ҵ����������ڵ�λ��
		}
	}
	return -1;  //�Ҳ�����Ԫ��
}

void SearchContact(const struct Contact * ps)
{
	char name[MAX_NAME];
	printf("������Ҫ���ҵ��˵�������");
	scanf("%s", name);

	//int i = 0;
	//for (i = 0; i < ps->size; i++)
	//{
	//	if (0 == strcmp(ps->data[i].name, name))
	//	{
	//		break;  //�����break������forѭ��ʹ�õ�
	//	}
	//}
	// ������Ĵ����� ɾ�����޸ĵ�ʱ�򶼻��õ�������������Է�װ�ɺ���ʹ�ã�ʹ�� FindNmae����
	int pos=FindName(ps,name);  //���ز���ֵ���ڵ��±�λ�ã��Ҳ�������-1
	if (-1 == pos)
	{
		printf("��ͨѶ¼��û��%s!\n", name);
	}
	else
	{
		printf("���ҳɹ���\n");
		printf("%-20s \t %-4d \t %-5s \t %-12s \t %-20s\n",
			ps->data[pos].name,
			ps->data[pos].age,
			ps->data[pos].sex,
			ps->data[pos].tele,
			ps->data[pos].addr);
	}
	

}

void ModifyContact(struct Contact * ps)
{
	char name[MAX_NAME];
	printf("������Ҫ�޸ĵ���ϵ�˵����֣�");
	scanf("%s", name);

	int pos = FindName(ps, name);
	if (-1 == pos)
	{
		printf("��ͨѶ¼��û��%s!\n", name);
	}
	else
	{
		printf("���������֣�");
		scanf("%s", ps->data[pos].name);
		printf("���������䣺");
		scanf("%d", &(ps->data[pos].age));
		printf("�������Ա�");
		scanf("%s", ps->data[pos].sex);
		printf("������绰���룺");
		scanf("%s", ps->data[pos].tele);
		printf("������סַ��");
		scanf("%s", ps->data[pos].addr);

		printf("�޸���Ϣ��ɣ�\n");
		printf("\n");

	}

}

void SortContact(struct Contact * ps)
{
	printf("\n");
	printf("***********************************\n");
	printf("***** 1. ������������  ************\n");
	printf("***** 2.������������  *************\n");
	printf("***********************************\n");
	printf("��ѡ������ʽ��");
	int input;
	scanf("%d", &input);
	switch (input)
	{
	case 1:		
		printf("��������������");
		printf("\n");
		int i, j,issort;
		PeoInfo t;
		for (i = 0; i <ps->size - 1; i++)
		{
			issort = 1;
			for (j = 0; j < ps->size - i - 1; j++)
			{
				if (ps->data[j].age > ps->data[j + 1].age)
				{
					t = ps->data[j];
					ps->data[j] = ps->data[j + 1];
					ps->data[j+1] = t;
					issort = 0;
				}
			}
			if (issort)
				break;
		}
		ShowContact(ps);

		//printf("%-20s \t %-4s \t %-5s \t %-12s \t %-20s\n", "����", "����", "�Ա�", "�绰", "��ַ");
		////�ȴ�ӡһ�б�ͷ
		//for (i = 0; i < ps->size; i++)
		//{
		//	printf("%-20s \t %-4d \t %-5s \t %-12s \t %-20s\n",
		//		ps->data[i].name,
		//		ps->data[i].age,
		//		ps->data[i].sex,
		//		ps->data[i].tele,
		//		ps->data[i].addr);
		//} 

		break;
	case 2:
		printf("�������������������Ӣ�����֣�\n");
		printf("�ù����д����ƣ�");
		printf("\n");
		break;

	default:printf("�������!");
		printf("\n");
		break;


	}

}

void DestroyContact(Contact* ps)
{
	free(ps->data);
	ps->data = NULL;

}

void SaveContact(Contact* ps)
{
	FILE* pfWrite = fopen("contact.txt", "wb");
	//��ֻдģʽ�򿪣��½���һ��txt�ļ�,�������ļ�

	if (pfWrite == NULL)
	{
		printf("SaveContact: %s\n", strerror(errno));
		//strerror(errno)�ú�������һ��ָ������ַ�����ָ�룬�ô����ַ��������˴��� errnum��
		//��Ҫͷ�ļ� #include <string.h>��#include <errno.h>
		return;  //�޷���ֵ�Ľ�������

	}
	//д��ͨѶ¼�����ݵ��ļ���
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		fwrite(&(ps->data[i]), sizeof(PeoInfo), 1, pfWrite);
		//д���ַ��д���С��ÿ��д��������ļ���
	}
	printf("��Ϣ�ѱ�����contact.txt�ļ���!\n");

	fclose(pfWrite);  //д��֮��Ҫ�ر��ļ�
	pfWrite = NULL;


}
