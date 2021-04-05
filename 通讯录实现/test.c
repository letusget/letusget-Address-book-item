#define _CRT_SECURE_NO_WARNINGS 1

// 功能测试用

#include <stdio.h>
#include "contact.h"
#include <string.h>
#include <string.h>

void menu(void);  //打印操作菜单

void main(void)
{
	int input=0;
	//在声明中定义结构体，要包含所有通讯录信息
	
	/*
	struct PeoInfo con[MAX];
	int size;	
		需要判断通讯录中已经存入的元素个数，好友剩余的空位（容量）
		所以这里可以把通讯录的成员信息 和通讯录的数据个数都存储到一个结构体中
	*/
	struct Contact con;  //新建通讯录

	//初始化通讯录
	InitContact(&con);

	//存入信息

	do
	{
		menu();
		printf("请选择：");
		scanf("%d", &input);

		/*在这里不同数字的含义不够明确，即代码可读性不高，可以使用 枚举 类型来定义改善*/
		switch (input)
		{
		default:printf("选择错误！\n");
			printf("\n");
			break;
		case EXIT:
			SaveContact(&con);  //在销毁前先保存文件
			DestroyContact(&con); //销毁通讯录，释放内存
			printf("退出通讯录！\n");
			printf("\n");
			break;
		case ADD:

			//存入信息
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
	} while (input);  //可以很有效的检查输入信息

	


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



