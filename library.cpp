// library.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#include "string.h"
#include "stdlib.h"
#define LEN sizeof(struct Book)

struct Book {
	char ISBN[11];   //图书编号
	char name[12];     //书名
	char author[12];   //作者
	char type[10];     //书籍分类
	char publish[12];  //出版社  
	char time[10];      //出版时间 
	float price;       //价格   
	int num;           //数量   
	struct Book *next;  //指针域
};

//公共声明
void loca(int x, int y); //光标位置
void menu();             //菜单   
void input_book();       //图书入库  
Book *read_from_file();  //将文件中的内容读出到链表中
void save_to_file(Book *p); //将图书信息存入文件   
void find_book();        //查询   
void print_book();       //图书总览   
void del_book();         //删除图书   
void revise_book();       //修改信息   
void find_name_book();   //按书名查询   
void find_author_book(); //按作者查询   
void find_ISBN_book(); //按图书编号查询
void find_publish_book();//按出版社查询
Book *sort_book(Book *head); //按图书编号由大到小排序
void over();             //退出

int main()
{
	menu();     //菜单 
	return 0;
}

void loca(int x, int y)        //将光标移动到x,y坐标处  
{
	COORD pos = { x,y };          //COORD是Windows API中定义的一种结构，表示一个字符在控制台屏幕上的坐标
	HANDLE Out = GetStdHandle(STD_OUTPUT_HANDLE); //GetStdHandle（）返回标准的输入、输出或错误的设备的句柄，也就是获得输入、输出/错误的屏幕缓冲区的句柄
	SetConsoleCursorPosition(Out, pos); //API中定位光标位置的函数
}

void menu()//菜单
{
	do 
	{
		//菜单界面模仿了其他系统
		system("cls");      //清屏 
		loca(50, 5);
		printf("  图书信息管理系统");
		loca(48, 8);
		printf("|      1.图书入库      |");
		loca(48, 10);
		printf("|      2.图书遍览      |");
		loca(48, 12);
		printf("|      3.图书查询      |");
		loca(48, 14);
		printf("|      4.图书删除      |");
		loca(48, 16);
		printf("|      5.修改信息      |");
		loca(48, 18);
		printf("|      6.退出书库      |");
		loca(80, 26);
		printf("designed by 周绍峰");
		loca(48, 20);
		printf("------------------------");
		loca(54, 22);
		printf("请选择操作：");
		int t;   //选择功能
		scanf("%d", &t);
		switch (t)
		{
		case 1:input_book(); break;
		case 2:print_book(); break;
		case 3:find_book(); break;
		case 4:del_book(); break;
		case 5:revise_book(); break;
		case 6:over(); break;
		default:break;
		}
	} while (1);
}

Book *read_from_file()  //从文件中读取，得到一个链表，用指针返回
{
	FILE *fp;    //文件指针   
	int n = 0;
	Book *head = NULL, *p2 = NULL, *p1, *pr=NULL;
	fp = fopen("mybook.dat", "rb");  //以只读的方式打开文件（二进制）   
	if (fp == NULL)
	{
		printf("cannot open file\n");
	}
	while (!feof(fp))        //判断文件位置标志是否移动到文件末尾   
	{
		n++;
		p1 = (Book*)malloc(LEN);     //向内存申请一段空间 
		fread(p1, LEN, 1, fp);       //将fp所指向的文件中的内容赋给p1   
		if (n == 1)                  //头指针、头结点
		{
			head = p1;
			p2 = p1;
		}
		else
		{
			pr = p2;
			p2->next = p1;
			p2 = p1;
		}
	}
	if (pr != NULL)              //处理末尾节点
		pr->next = NULL;
	fclose(fp);       //关闭文件   
	return(head);     //返回头指针   
}

void save_to_file(Book *p)      //将p中内容写入文件   
{
	FILE *fp;   //文件指针 
	if ((fp = fopen("mybook.dat", "ab"))== NULL)    //以追加的方式打开名为mybook的二进制文件 
	{
		printf("cannot open file");      //文件找不到
		exit(0);
	}

	if (fwrite(p, LEN, 1, fp) != 1)   //将p所指向的一段大小为N的内容存入fp所指向的文件中   
	{
		printf("write error");         //没有存储成功则不返回1
	}
	fclose(fp);     //关闭文件    
}

void input_book()      //图书录入，写一个记录存一个记录   
{
	do
	{
		system("cls");
		char t;
		Book *p;
		p = (struct Book *)malloc(LEN);   //申请空间,用p记录   
		//输入图书信息  
		loca(48, 8);
		printf("请输入图书编号：");
		scanf("%s", p->ISBN); getchar();
		loca(48, 10);
		printf("请输入书名：");
		scanf("%s", p->name); getchar();
		loca(48, 12);
		printf("请输入作者名：");
		scanf("%s", p->author); getchar();
		loca(48, 14);
		printf("请输入图书类别：");
		scanf("%s", p->type); getchar();
		loca(48, 16);
		printf("请输入图书出版单位：");
		scanf("%s", p->publish); getchar();
		loca(48, 18);
		printf("请输入图书出版时间：");
		scanf("%s", p->time); getchar();
		loca(48, 20);
		printf("请输入图书价格：");
		scanf("%f", &p->price); getchar();
		loca(48, 22);
		printf("请输入图书数量：");
		scanf("%d", &p->num);
		save_to_file(p);     //存储入文件
		system("cls");
		loca(46, 8);
		printf("-------------------------");
		loca(46, 9);
		printf("|                       |");
		loca(46, 10);
		printf("| 保存成功！是否继续？  |");
		loca(46, 12);
		printf("| 1.是             2.否 |");
		loca(46, 13);
		printf("|                       |");
		loca(46, 14);
		printf("-------------------------");
		loca(46, 15);
		printf("=");
		while (1)      //利用死循环防止其他按键干扰   
		{
			t = getchar();
			if (t == '1')
				break;
			else if (t == '2')
				menu();
		}
	} while (1);
}

void print_book()    //图书遍历  
{
	system("cls");
	struct Book* head, *p;
	int i = 11;
	int sum = 0;
	head = read_from_file();        //读取文件
	loca(5, 5);
	printf("***********************************************图书遍览******************************************************");
	loca(5, 8);
	printf("-------------------------------------------------------------------------------------------------------------");
	loca(5, 9);
	printf("图书编号   书名       作者名      图书类别       出版单位       出版时间          价格        数量");
	loca(5, 10);
	printf("-------------------------------------------------------------------------------------------------------------");
	if (head == NULL)
	{
		loca(45, 11);
		printf("书库暂时没有书(按任意键返回)");
		getchar();
		menu();
	}
	head = sort_book(head);        //链表排序
	p = head;          //开始遍历
	do
	{
		loca(5, i);
		printf("%-10s%-12s%-12s%-16s%-16s%-18s%-14.2f%-10d\n", p->ISBN, p->name, p->author, p->type, p->publish, p->time, p->price, p->num);
		i+=2;
		sum += p->num;      //计算图书总量   
		p = p->next;
	}while (p != NULL);	
	loca(48, 7);
	printf("图书总数: %d 本", sum);
	loca(48, i+1);
	printf("按任意键返回...");
	getchar(); getchar();
	menu();
}

void revise_book()       //修改图书信息   
{
	do
	{
		system("cls");
		Book *head, *p;
		int  j = 0;
		char ch, t;
		FILE *fp;   //文件指针   
		char _ISBN[11];   //图书编号
		char name[12];     //书名
		char author[12];   //作者
		char type[10];     //书籍分类
		char publish[12];  //出版社  
		char time[10];      //出版时间 
		float price;       //价格   
		int num;           //数量    
		head = read_from_file();    //读取文件
		p = head;
		loca(48, 10);
		printf("请输入你要修改的图书的编号：");
		scanf("%s",_ISBN);
		loca(5, 5);
		printf("***********************************************图书信息******************************************************");
		loca(5, 8);
		printf("-------------------------------------------------------------------------------------------------------------");
		loca(5, 9);
		printf("图书编号   书名       作者名      图书类别       出版社         出版时间          价格        数量");
		loca(5, 10);
		printf("-------------------------------------------------------------------------------------------------------------");
		while (p != NULL)
		{
			if (strcmp(p->ISBN, _ISBN) == 0)  //如果检索到ISBN，则输出此条记录
			{
				j++;
				loca(5, 12);
				printf("%-10s%-12s%-16s%-12s%-14s%-18s%-14.2f%-10d\n", p->ISBN, p->name, p->author, p->type, p->publish, p->time, p->price, p->num);
				Sleep(500);
			}
			p = p->next;
		}
		if (j == 0)           //如果j=0，没有找到相应的信息   
		{
			loca(40,12);
			printf("没有找到相应的书籍(按0返回)");
			while (1)               //死循环防止其他按键干扰   
			{
				ch = getchar();
				if (ch == '0')
					menu();
			}
		}
		p = head;        //让p重新指向表头   
		while (p != NULL) {
			if (strcmp(p->ISBN, _ISBN) == 0)      //如果p不为空
			{
				//输入要修改的信息 
				loca(48, 14);
				printf("请输入图书编号：");
				scanf("%s", _ISBN); getchar(); strcpy(p->ISBN, _ISBN);
				loca(48, 16);
				printf("请输入书名：");
				scanf("%s", name); getchar(); strcpy(p->name, name);
				loca(48, 18);
				printf("请输入作者名：");
				scanf("%s", author); getchar(); strcpy(p->author, author);
				loca(48, 20);
				printf("请输入图书类别：");
				scanf("%s", type); getchar(); strcpy(p->type, type);
				loca(48, 22);
				printf("请输入图书出版单位：");
				scanf("%s", publish); getchar(); strcpy(p->publish, publish);
				loca(48, 24);
				printf("请输入图书出版时间：");
				scanf("%s", time); getchar(); strcpy(p->time, time);
				loca(48, 26);
				printf("请输入图书价格：");
				scanf("%f", &price); getchar(); p->price = price;
				loca(48, 28);
				printf("请输入图书数量：");
				scanf("%d", &num); getchar(); p->num = num;
				break;
			}
			p = p->next;
		}
		system("cls");
		loca(46, 8);
		printf("-------------------------");
		loca(46, 9);
		printf("|                       |");
		loca(46, 10);
		printf("|     是否确认修改？    |");
		loca(46, 12);
		printf("| 1.是             2.否 |");
		loca(46, 13);
		printf("|                       |");
		loca(46, 14);
		printf("-------------------------");
		loca(46, 15);
		while (1)      //利用死循环防止其他按键干扰   
		{
			t = getchar();
			if (t == '1')
			{
				break;
			}
			else if (t == '2')
				menu();
		}
		system("cls");
		loca(46, 10);
		printf("正在修改，请稍后....");
		Sleep(1000);
		fp = fopen("mybook.dat", "wb");   //以只写的方式打开名为mybook的二进制文件，删除之前的文件并重建文件  
		if (fp == NULL)
		{
			printf("cannot open file");
			exit(0);
		}
		if (fwrite(head, LEN, 1, fp) != 1)    //将头结点写入fp所指向的文件中   
		{
			printf("write error!");
		}
		fclose(fp);    //关闭文件   
		if (head != NULL)    //如果head不为空   
		{
			p = head->next;     //让p指向第二个结点   
			fp = fopen("mybook.dat", "ab+");      //以追加的方式打开文件   
			while (p != NULL)
			{
				if (fwrite(p, LEN, 1, fp) != 1)//将p写入fp所指向的文件中  
				{
					printf("write error!");
				}
				p = p->next;
			}
			fclose(fp);    //关闭文件   
		}
		system("cls");
		loca(46, 10);
		printf("修改成功！即将返回主菜单...");
		Sleep(1000);
		break;
	} while (1);
}

void del_book()   //删除图书信息
{
	do
	{
		system("cls");
		FILE *fp;
		Book *head, *p, *p2 = NULL;
		int j = 0;
		char _ISBN[11];
		char t, c, ch;
		head = read_from_file(); //读取文件，返回表头地址 
		p = head;
		loca(48, 10);
		printf("请输入你要删除的图书的编号：");
		scanf("%s", _ISBN);
		loca(5, 5);
		printf("***********************************************图书信息******************************************************");
		loca(5, 8);
		printf("-------------------------------------------------------------------------------------------------------------");
		loca(5, 9);
		printf("图书编号   书名       作者名      图书类别       出版单位       出版时间          价格        数量");
		loca(5, 10);
		printf("-------------------------------------------------------------------------------------------------------------");
		while (p != NULL)
		{
			if (strcmp(p->ISBN, _ISBN) == 0)  //如果检索到ISBN，则输出此条记录以供查阅
			{
				j++;
				loca(5, 12);
				printf("%-10s%-12s%-14s%-14s%-14s%-18s%-14.2f%-10d\n", p->ISBN, p->name, p->author, p->type, p->publish, p->time, p->price, p->num);
				Sleep(500);
			}
			p = p->next;
		}
		if (j == 0)           //如果j=0，没有找到相应的信息   
		{
			loca(40, 12);
			printf("没有找到相应的书籍(按0返回)");
			while (1)               //死循环防止其他按键干扰   
			{
				ch = getchar();
				if (ch == '0')
					menu();
			}
		}
		loca(46, 14);
		printf("-------------------------");
		loca(46, 15);
		printf("|                       |");
		loca(46, 16);
		printf("|     是否确认删除？    |");
		loca(46, 17);
		printf("| 1.是             2.否 |");
		loca(46, 18);
		printf("|                       |");
		loca(46, 19);
		printf("-------------------------");
		loca(46, 20);
		printf("| =                     |");
		loca(46, 21);
		printf("-------------------------");
		loca(54, 20);
		while (1)
		{
			t = getchar();
			if (t == '1')
				break;
			else if (t == '2')
				menu();
		}
		p = head;                   //删除节点
		while (_ISBN != p->ISBN && p->next != NULL)
		{
			p2 = p;
			p = p->next;
		}
		if (p!=NULL)
		{
			if (p == head) head = p->next;
			else p2->next = p->next;
		}
		fp = fopen("mybook.dat", "wb");   //以只写的方式打开名为mybook的二进制文件，删除之前的文件并重建文件  
		if (fp == NULL)
		{
			loca(50, 10);
			printf("cannot open file");
			exit(0);
		}
		if (fwrite(head, LEN, 1, fp) != 1)    //将头结点写入fp所指向的文件中   
		{
			printf("write error!");
		}
		fclose(fp);    //关闭文件   
		if (head != NULL)    //如果head不为空   
		{
			p = head->next;     //让p指向第二个结点   
			fp = fopen("mybook.dat", "ab+");      //以追加的方式打开文件   
			while (p != NULL)
			{
				if (fwrite(p, LEN, 1, fp) != 1)//将p写入fp所指向的文件中  
				{
					printf("write error!");
				}
				p = p->next;
			}
			fclose(fp);    //关闭文件   
		}
		system("cls");
		loca(46, 10);
		printf("正在删除，请稍后....");
		Sleep(500);
		system("cls");
		loca(46, 8);
		printf("-------------------------");
		loca(46, 9);
		printf("|                       |");
		loca(46, 10);
		printf("|  删除成功，是否继续？ |");
		loca(46, 12);
		printf("| 1.是             2.否 |");
		loca(46, 13);
		printf("|                       |");
		loca(46, 14);
		printf("-------------------------");
		while (1)
		{
			c = getchar();
			if (c == '1')
			{
				break;
				head = read_from_file();
			}
			else if (c == '2')
			{
				menu();
			}
		}
	} while (1);
}

void find_book()   //查询图书   
{
	do
	{
		system("cls");   //清屏   
	    char t;
    	loca(56,5);
	    printf("图书查询");
	    loca(48,8);
	    printf("|     1.编号  查询      |");
	    loca(48,10);
    	printf("|     2.书名  查询      |");
    	loca(48,12);
	    printf("|     3.作者  查询      |");
		loca(48, 14);
		printf("|     4.出版社查询      |");
	    loca(48,16); 
	    printf("|     0.返回主菜单      |");
		loca(48, 18);
		printf("-------------------------");
		loca(54, 20);
		printf("选择查询方式:");
	    t = getchar();
		switch (t)                          //简单的选择语句
	    {
		case '0':menu(); break;
		case '1':find_ISBN_book(); break;
		case '2':find_name_book(); break;
		case '3':find_author_book(); break;
		case '4':find_publish_book(); break;
	    default :break;
	    }
	}while (1);
}

void find_ISBN_book()    //按图书编号查询   
{
	system("cls");
	Book *head, *p;
	int i = 11, sum = 0, j = 0;
	head = read_from_file();
	char ch;
	char number[10];
	loca(48, 8);
	printf("请输入您要查询图书的编号：");
	getchar();
	gets_s(number);
	loca(48, 10);
	printf("正在查询...");
	Sleep(500);
	p = head;
	loca(5, 5);
	printf("***********************************************图书总览******************************************************");
	loca(5, 8);
	printf("-------------------------------------------------------------------------------------------------------------");
	loca(5, 9);
	printf("图书编号   书名       作者名      图书类别       出版社         出版时间          价格        数量");
	loca(5, 10);
	printf("-------------------------------------------------------------------------------------------------------------");
	while (p != NULL)
	{
		if (p != NULL && strcmp(p->ISBN, number) == 0)        //如果查询到相应的编号，则输出此条记录
		{
			j++;
			loca(5, i);
			printf("%-10s%-12s%-16s%-12s%-14s%-18s%-14.2f%-10d\n", p->ISBN, p->name, p->author, p->type, p->publish, p->time, p->price, p->num);
			i+=2;
			sum += p->num;           //记录数量
		}
		p = p->next;
	}
	if (j == 0)           //如果j=0，没有找到相应的信息   
	{
		loca(40, 12);
		printf("没有找到相应的书籍(按0返回查询菜单)");
		while (1)               //死循环防止其他按键干扰   
		{
			ch = getchar();
			if (ch == '0')
				find_book();
		}
	}
	loca(52, 7);
	printf("总量为%d本", sum);
	loca(50, i+2);
	printf("按任意键返回...");
	getchar();
	find_book();
}

void find_author_book()   //按作者名查询   
{
	system("cls");
	Book *head, *p;
	int i = 11, sum = 0, j = 0;
	head = read_from_file();
	char author[10];
	char ch;
	loca(48, 8);
	printf("请输入您要查询图书的作者名：");
	getchar();
	gets_s(author);
	loca(48, 10);
	printf("正在查询....");
	Sleep(500);
	p = head;
	loca(5, 5);
	printf("***********************************************图书总览******************************************************");
	loca(5, 8);
	printf("-------------------------------------------------------------------------------------------------------------");
	loca(5, 9);
	printf("图书编号   书名       作者名      图书类别       出版社         出版时间          价格        数量");
	loca(5, 10);
	printf("-------------------------------------------------------------------------------------------------------------");
	while (p != NULL)
	{
		if (p != NULL && strcmp(p->author, author) == 0)
		{
			j++;
			loca(5, i);
			printf("%-10s%-12s%-16s%-12s%-14s%-18s%-14.2f%-10d\n", p->ISBN, p->name, p->author, p->type, p->publish, p->time, p->price, p->num);
			sum += p->num;
			i+=2;
		}
		p = p->next;
	}
	if (j == 0)           //如果j=0，没有找到相应的信息   
	{
		loca(40, 12);
		printf("没有找到相应的书籍(按0返回查询菜单)");
		while (1)               //死循环防止其他按键干扰   
		{
			ch = getchar();
			if (ch == '0')
				find_book();
		}
	}
	loca(46, 7);
	printf("该作者图书数量为%d本",sum);
	loca(50, i+2);
	printf("按任意键返回...");
	getchar();
	find_book();
}

void find_name_book()   //按书名查询   
{
	system("cls");
	Book* head, *p;
	int i = 11, sum = 0, j = 0;
	head = read_from_file();
	char name[10];
	char ch;
	loca(48, 8);
	printf("请输入您要查询图书的书名：");
	getchar();
	gets_s(name);
	loca(48, 10);
	printf("正在查询....");
	Sleep(1500);
	p = head;
	loca(5, 5);
	printf("***********************************************图书总览******************************************************");
	loca(5, 8);
	printf("-------------------------------------------------------------------------------------------------------------");
	loca(5, 9);
	printf("图书编号   书名       作者名      图书类别       出版社         出版时间          价格        数量");
	loca(5, 10);
	printf("-------------------------------------------------------------------------------------------------------------");
	while (p != NULL)
	{
		if (p != NULL && strcmp(p->name, name) == 0)
		{
			j++;
			loca(5, i);
			printf("%-10s%-12s%-16s%-12s%-14s%-18s%-14.2f%-10d\n", p->ISBN, p->name, p->author, p->type, p->publish, p->time, p->price, p->num);
			i+=2;
			sum += p->num;
		}
		p = p->next;
	}
	if (j == 0)           //如果j=0，没有找到相应的信息   
	{
		loca(40, 12);
		printf("没有找到相应的书籍(按0返回查询菜单)");
		while (1)               //死循环防止其他按键干扰   
		{
			ch = getchar();
			if (ch == '0')
				find_book();
		}
	}
	loca(48, 7);
	printf("该图书总量为%d本", sum);
	loca(50, i+1);
	printf("按任意键返回...");
	getchar();
	find_book();
}

void find_publish_book()   //按出版社查询   
{
	system("cls");
	Book* head, *p;
	int i = 11, sum = 0, j = 0;
	head = read_from_file();
	char _publish[10];
	char ch;
	loca(48, 8);
	printf("请输入您要查询的出版社：");
	getchar();
	gets_s(_publish);
	loca(48, 10);
	printf("正在查询....");
	Sleep(1500);
	p = head;
	loca(5, 5);
	printf("***********************************************图书遍览******************************************************");
	loca(5, 8);
	printf("-------------------------------------------------------------------------------------------------------------");
	loca(5, 9);
	printf("图书编号   书名       作者名      图书类别       出版社         出版时间          价格        数量");
	loca(5, 10);
	printf("-------------------------------------------------------------------------------------------------------------");
	while (p != NULL)
	{
		if (p != NULL && strcmp(p->publish, _publish) == 0)
		{
			loca(5, i);
			printf("%-10s%-12s%-16s%-12s%-14s%-18s%-14.2f%-10d\n", p->ISBN, p->name, p->author, p->type, p->publish, p->time, p->price, p->num);
			i += 2;
			sum += p->num;
		}
		p = p->next;
	}
	if (j == 0)           //如果j=0，没有找到相应的信息   
	{
		loca(40, 12);
		printf("没有找到相应的书籍(按0返回查询菜单)");
		while (1)               //死循环防止其他按键干扰   
		{
			ch = getchar();
			if (ch == '0')
				find_book();
		}
	}
	loca(46, 7);
	printf("该出版社图书总量为%d本", sum);
	loca(50, i + 1);
	printf("按任意键返回...");
	getchar();
	find_book();
}

Book *sort_book(Book *head)
{
	Book *first; //为原链表剩下用于直接插入排序的节点头指针
	Book *t;      //临时指针变量：插入节点
	Book *q, *p=NULL; //临时指针变量

	first = head->next;    //原链表剩下用于直接插入排序的节点链表
	head->next = NULL;     //只含有一个节点的链表

	while (first != NULL) //遍历剩下无序的链表
	{
		for (t = first, q = head; ((q!= NULL) && (strcmp(q->ISBN,t->ISBN)>0)); p = q, q = q->next); //无序节点在有序链表中找插入的位置
                                                                                                    //退出for循环，就是找到了插入的位置
		first = first->next;                          //无序链表中的节点离开，以便它插入到有序链表中
		if (q == head)                                //插在第一个节点之前
		{
			head = t;
		}
		else           //p是q的前驱
		{
			p->next = t;
		}
		t->next = q; 
	}
	return head;
}

void over()      //退出系统  
{
	char t;
	system("cls");
	loca(48, 11);
	printf("-----------------------");
	loca(48, 12);
	printf("|   您确定要退出吗?   |");
	loca(48, 14);
	printf("| 1.确定     2.取消   |");
	loca(48, 15);
	printf("-----------------------");
	loca(48, 16);
	while (1)
	{
		t = getchar();
		switch (t)
		{
			case '1':
			system("cls");
			loca(48, 10);
			printf("正在退出....");
			Sleep(1500);
			system("cls");
			loca(48, 10);
			printf("已退出软件");
			loca(48, 12);
			printf("谢谢使用！");
			Sleep(3000);
			loca(48, 14);
			exit(0);  break;      //终止程序   
			case '2':
			menu(); break;   //调用函数，进入菜单   
		default :break;
		}
	}
}
