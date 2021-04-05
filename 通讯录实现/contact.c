#define _CRT_SECURE_NO_WARNINGS 1

//实现函数功能用

#include <stdio.h>
#include "contact.h"

//不能再出现 main函数！！！
//void main(void)
//{
//
//
//}

int FindName(struct Contact* ps, char name[MAX_NAME]);  //查找名字是否在该通讯录中
void CheckCapacity(struct Contact* ps);  //检查通讯录容量是否够用

void LoadContact(Contact* ps)
{
	FILE* pfRead = fopen("contact.txt","rb");
	PeoInfo tmp = { 0 };  //临时变量来存放信息
	if (pfRead == NULL)
	{
		printf("coadContact: %s\n", strerror(errno));//这样可以显示不同的错误信息
		return;
	}
	//读取文件。存放到通讯录中
	while (fread(&tmp, sizeof(PeoInfo), 1, pfRead))
	{
		//分别是 接受数据的地址，读入的一个单元的大小，每次读入的个数，文件流
		//返回真实读到的元素的个数
		
		CheckCapacity(ps);  //检查容量是否可以存储，如果不可以就扩容
		ps->data[ps->size] = tmp;
		ps->size++;  //加载容量
		
	}
	printf("成功读取上次保存的信息！\n");
	fclose(pfRead);
	pfRead = NULL;

}

void InitContact(struct Contact* ps)  //初始化通讯录结构体
{
	ps->data = (struct PeoInfo* )malloc(DEFAULT_SZ * sizeof(struct PeoInfo));
	//对data的初始化，最初只有三个位置，为了修改方便，这里改用自定义的DEFAULT_SZ
	if (ps->data == NULL)
	{
		return;
	}
	ps->size = 0;
	ps->capacity = DEFAULT_SZ;  //初始大小

	//在实现将通讯录存入文件之后就可以在下次初始化的时候继续读入这些信息
	LoadContact(ps);  //ps 就是地址变量，所以这里不用取地址符&

}

void CheckCapacity(struct Contact* ps)
{
	if (ps->size == ps->capacity)
	{
		//增容
		struct PeoInfo* ptr = realloc(ps->data, (ps->capacity + 2)*sizeof(struct PeoInfo));
		//在原来的地址上，再申请两个存储空间
		if (ptr != NULL)
		{
			ps->data = ptr;
			ps->capacity += 2;
			printf("增容成功！\n");
		}
		else
		{
			printf("增容失败！\n");
		}
	}
}

void AddContact(struct Contact * ps)  //添加通讯录信息
{
	//if (ps->size == MAX)
	//{
	//	printf("通讯录已满，无法继续添加！");

	//}
	//else
	
	//增加容量，如果通讯录已满，则增加空间（两个），如果没满，则不做操作
	CheckCapacity(ps);
		printf("请输入名字：");
		scanf("%s", ps->data[ps->size].name);
		//存储在data区域的第size个位置的name区域

		printf("请输入年龄：");
		scanf("%d", &(ps->data[ps->size].age));
		//因为这里传递的是地址，要将数据存储在这个位置的变量中
		while (0>ps->data[ps->size].age || 150<ps->data[ps->size].age )
		{
			printf("年龄输入有误，请重新输入：");
			scanf("%d", &(ps->data[ps->size].age));
		}

		printf("请输入性别：");
		scanf("%s", ps->data[ps->size].sex);

		printf("请输入电话号码：");
		scanf("%s", ps->data[ps->size].tele);
		while (11 != strlen(ps->data[ps->size].tele))//对电话号码长度的检查
		{
			printf("电话号码输入位数有误（11位电话号码），请重新输入：");
			scanf("%s", ps->data[ps->size].tele);
		}

		printf("请输入住址：");
		scanf("%s", ps->data[ps->size].addr);
		ps->size++;
		printf("添加信息成功！\n");
		printf("\n");

}

void ShowContact(const struct Contact * ps)
{//传递的是地址，但是要避免改变已经存储的值的可能，所以就用const来修饰
	if (ps->size == 0)
	{
		printf("当前通讯录中没有成员！\n");
		printf("\n");

	}
	else
	{
		int i;
		printf("%-20s \t %-4s \t %-5s \t %-12s \t %-20s\n", "姓名", "年龄", "性别", "电话", "地址");
		//先打印一行表头
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
	printf("请输入要删除的人的名字：");
	char name[MAX_NAME];
	scanf("%s", name);

	//先查找，再删除，要找出要删除的元素所在的位置
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		/*strcmp 字符串比较函数
		C语言 strcmp() 函数用于对两个字符串进行比较（区分大小写）。头文件：string.h
	语法/原型：
	int strcmp(const char* stri1，const char* str2);
	参数 str1 和 str2 是参与比较的两个字符串。
	strcmp() 会根据 ASCII 编码依次比较 str1 和 str2 的每一个字符，直到出现找不到的字符，
	或者到达字符串末尾（遇见\0）。
	返回值 = 0, 则表示 str1 等于 str2
    返回值 < 0，则表示 str1 小于 str2。
	返回值 > 0，则表示 str2 小于 str1。返回值 = 0，则表示 str1 等于 str2。
		*/
		if (0 == strcmp(ps->data[i].name,name))
		{
			break;  //此时 i 即为要删除的元素
		}
	}

	if (i == ps->size)
	{
		printf("抱歉，要删除的元素不存在！");
		printf("\n");
	}
	else
	{
		int j=0;
		for (j = i; j < ps->size-1; j++)//数组下标要减少一个  
		{//从i开始，依次让后面的元素 覆盖前一个元素
			ps->data[j] = ps->data[j + 1];
		}
		ps->size--;
		printf("删除通讯录成员成功！\n");
		printf("\n");

	}

}
/*在函数的返回类型前加上关键字static，函数就被定义成为静态函数。
普通函数的定义和声明默认情况下是extern的，但静态函数只是在声明他的文件当中可见，
不能被其他文件所用。因此定义静态函数有以下好处：
　　<1> 其他文件中可以定义相同名字的函数，不会发生冲突。
　　<2> 静态函数不能被其他文件所用。*/
static int FindName(const struct Contact* ps, char name[MAX_NAME])
{
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		if (0 == strcmp(ps->data[i].name, name))
		{
			return i;  //找到，返回所在的位置
		}
	}
	return -1;  //找不到该元素
}

void SearchContact(const struct Contact * ps)
{
	char name[MAX_NAME];
	printf("请输入要查找的人的姓名：");
	scanf("%s", name);

	//int i = 0;
	//for (i = 0; i < ps->size; i++)
	//{
	//	if (0 == strcmp(ps->data[i].name, name))
	//	{
	//		break;  //这里的break是跳出for循环使用的
	//	}
	//}
	// 在这里的代码在 删除，修改的时候都会用到，所以这里可以封装成函数使用，使用 FindNmae函数
	int pos=FindName(ps,name);  //返回查找值所在的下标位置，找不到返回-1
	if (-1 == pos)
	{
		printf("该通讯录中没有%s!\n", name);
	}
	else
	{
		printf("查找成功！\n");
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
	printf("请输入要修改的联系人的名字：");
	scanf("%s", name);

	int pos = FindName(ps, name);
	if (-1 == pos)
	{
		printf("该通讯录中没有%s!\n", name);
	}
	else
	{
		printf("请输入名字：");
		scanf("%s", ps->data[pos].name);
		printf("请输入年龄：");
		scanf("%d", &(ps->data[pos].age));
		printf("请输入性别：");
		scanf("%s", ps->data[pos].sex);
		printf("请输入电话号码：");
		scanf("%s", ps->data[pos].tele);
		printf("请输入住址：");
		scanf("%s", ps->data[pos].addr);

		printf("修改信息完成！\n");
		printf("\n");

	}

}

void SortContact(struct Contact * ps)
{
	printf("\n");
	printf("***********************************\n");
	printf("***** 1. 按照年龄排序  ************\n");
	printf("***** 2.按照姓名排序  *************\n");
	printf("***********************************\n");
	printf("请选择排序方式：");
	int input;
	scanf("%d", &input);
	switch (input)
	{
	case 1:		
		printf("下面是排序结果：");
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

		//printf("%-20s \t %-4s \t %-5s \t %-12s \t %-20s\n", "姓名", "年龄", "性别", "电话", "地址");
		////先打印一行表头
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
		printf("按照姓名排序仅适用于英文名字！\n");
		printf("该功能尚待完善！");
		printf("\n");
		break;

	default:printf("输入错误!");
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
	//以只写模式打开（新建）一个txt文件,二进制文件

	if (pfWrite == NULL)
	{
		printf("SaveContact: %s\n", strerror(errno));
		//strerror(errno)该函数返回一个指向错误字符串的指针，该错误字符串描述了错误 errnum。
		//需要头文件 #include <string.h>和#include <errno.h>
		return;  //无返回值的结束函数

	}
	//写入通讯录中数据到文件中
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		fwrite(&(ps->data[i]), sizeof(PeoInfo), 1, pfWrite);
		//写入地址，写入大小，每次写入个数，文件流
	}
	printf("信息已保存至contact.txt文件中!\n");

	fclose(pfWrite);  //写完之后要关闭文件
	pfWrite = NULL;


}
