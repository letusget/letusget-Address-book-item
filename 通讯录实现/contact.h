#define _CRT_SECURE_NO_WARNINGS 1

//#define MAX 1000

#define MAX_NAME 20
#define MAX_SEX 5
#define MAX_TELE 12
#define MAX_ADDR 30
#define DEFAULT_SZ 3 //这个是初始化时可以存储的通讯录成员的个数

#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <errno.h>  //文件操作相关的还有string.h头文件

enum Option
{//与菜单操作对应
	EXIT,  //0
	ADD,  //1
	DEL,  //2
	SEARCH,  //3
	MODIFY,  //4
	SHOW,  //5
	SORT,  //6
	SAVE  //7
};

//声明函数用
/*
要实现可以存放1000个好友信息，包括名字，电话，性别，住址，年龄
可以增加好友信息
可以删除指定名字的好友信息
可以查找好友信息
可以修改好友信息
可以打印好友信息
排序
*/

//在这里定义各种常量的值，可以方便后期做修改


typedef struct PeoInfo
{
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	char tele[MAX_TELE];
	char addr[MAX_ADDR];

}PeoInfo;

typedef struct Contact  //通讯录类型
{
	//创建连续空间来存储信息，如果不够则重新申请，每次两个大小
	struct PeoInfo *data; 
	int size;//记录当前已经保存的通讯录个数
	int capacity;  //当前通讯录的最大容量，如果超出则申请新的空间
}Contact;

void menu(void);  //打印操作菜单
void InitContact(struct Contact* ps);  //初始化通讯录结构体
void AddContact(struct Contact* ps);  //添加通讯录信息
void ShowContact(const struct Contact* ps);  //显示输入的信息,且要不可修改，就用const修饰
void DelContact(struct Contact* ps);  //删除指定联系人
void SearchContact(const struct Contact* ps);  //查找指定的人
void ModifyContact(struct Contact* ps);  //修改指定的值
void SortContact(struct Contact* ps);  //通讯录排序
void DestroyContact(Contact* ps);  //销毁通讯录释放内存
void SaveContact(Contact* ps);  //保存已经存入的信息文件
void LoadContact(Contact* ps);
