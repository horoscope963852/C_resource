#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996) 

struct student {

    char number[13];//学号

    char name[8];//姓名

    char major[13]; //班级

    int test_sco;//实验成绩

    int paper_sco;//卷面成绩

    int sum;//总成绩

};

int yi_per = 0, yi_ave, yi_sum = 0;

int er_per = 0, er_ave, er_sum = 0;

int san_per = 0, san_ave, san_sum = 0;//3个班的三种成绩初始值为0

int ReadStudentInfo(const char* filename, struct student** pStudents);

//打开数据文件，失败返回 - 1；

//从头到尾扫描数据文件（即预读一遍）获得学生人数；

//根据学生人数，利用malloc和sizeof等函数或运算符为struct student * *pStudents分配内存；

//利用rewind函数，定位到文件头；

//读取数据文件，并把每一条记录通过数组下标法或指针法保存到结构体数组pStudents中；

//关闭文件；

//返回学生人数。


int ReadStudentInfo(const char* filename, struct student** pStudents);
void Count(struct student pStudents[], int num);



int main()

{

    int count;

    struct student* list = NULL;// 定义结构体指针list，并初始化为NULL

    int m = 0;

    //struct student* list;//定义结构体指针list

    count = ReadStudentInfo("D:\\homework files\\Class1.txt", &list);//从文件中读取学生信息并存储到结构体数组中，list会被分配内存

    if (count > 0 && list != NULL) {
        printf("\n学生信息管理系统：\n\n");
        printf("学生信息：\n");
        printf("----------------------------------------------------\n");
        printf("学号\t\t姓名\t\t班级\t\t实验成绩\t\t半期成绩\t\t总成绩\n");

        // 在这里添加打印学生信息的代码，循环遍历结构体数组，并使用printf函数打印每个学生的信息

        // 在打印完学生信息后，释放动态分配的内存以避免内存泄漏
        free(list);
    }
    else {
        printf("未能成功读取学生信息或内存分配失败。\n");
    }

    int point;
    scanf_s("%d", &point);

    for (m = 1; m <count; m++)

    {

        printf("%2d %8s %8s %8s %5d %5d %5d\n", m, (list + m -1)->name, (list + m - 1)->number, (list + m - 1)->major, (list + m -1)->paper_sco, (list + m - 1)->test_sco, (list + m - 1)->sum);//打印学生信息

    }




    Count(list, count);//计算班级学生人数和平均成绩


    printf("\n统计信息 ：\n");


    printf("----------------------------------------------------\n");


    printf("学号      班级       班级学生人数   平均成绩\n");


    printf("1   2017020901 % 3d % 3d\n", yi_per, yi_ave);


        printf("2    2017020902 % 3d % 3d\n", er_per, er_ave);


            printf("3   2017020903 % 3d % 3d\n", san_per, san_ave);//打印统计信息

                            return 0;

}



void ClassFun(char* buf, char* temp, char sp);



int ReadStudentInfo(const char* filename, struct student** pStudents)

{

    FILE* fp;

    char row;

    int i = 0, j;

    fp
        = fopen(filename, "r");//打开文件

    //打开数据文件，失败返回-1

    if (fp == NULL)

    {


        printf("cann't open the file");


        exit(-1);

    }

    row
        = fgetc(fp);//从文件指针fp指向的文件中读取一个字符并返回   

    //从头到尾扫描数据文件获得学生人数

    while (row != EOF)//EOF是end of file的意思, 用来判断是否到了文件的结尾处

    {


if (row == '\n')//读到回车


{


i++;//i为文件行数


}


row = fgetc(fp);//继续读取下一行

    }

    rewind(fp);
    //将文件内部的位置指针重新指向文件的开头



    row
        = fgetc(fp);

    *pStudents = (struct student*)malloc(sizeof(**pStudents) * i);//分配动态内存空间

    char buf[512] = { 0 };//缓冲



    char str[100];


    fgets(str, sizeof(str), fp); //文件的第一行是无效的数据，跳过第一行



    for (j = 0; j < i - 1;
        j++)

    {


        memset(*pStudents + j, 0, sizeof(struct student));//结构体初始化


        fgets(buf, 512, fp);//读取第j+1行的数据，遇到\n结束


        int len = strlen(buf);//计算该行字符数组buf的长度




        buf[len] = ' ';//该字符串后补充空格，以便下一步Cutstring作为结束标志


        ClassFun(buf, (*pStudents + j)->number, '   ');//第1个‘’前为学号


            ClassFun(buf, (*pStudents + j)->name, ' ');//第2个‘’前为姓名




            char test_Score[12], paper_Score[12];


        memset(test_Score, 0, 12);//初始化数组


        memset(paper_Score, 0, 12);//初始化数组




        ClassFun(buf, test_Score, ' ');//第3个‘’前为实验成绩


        (*pStudents + j)->test_sco = atoi(test_Score);//将实验成绩转化为整形数，赋给结构体地址(*pStudents + j)->test_sco




        ClassFun(buf, paper_Score, '   ');//第4个‘’前为卷面成绩


        (*pStudents + j)->paper_sco = atoi(paper_Score);//将卷面成绩转化为整形数，赋给结构体地址(*pStudents + j)->paper_sco


        (*pStudents + j)->sum = ((*pStudents +
            j)->test_sco) * 0.4 + ((*pStudents +
                j)->paper_sco) * 0.6;//计算总成绩


        memcpy((*pStudents + j)->major, (*pStudents + j)->number,
            10);

    }


    fclose(fp);//关闭文件

    return (i);//返回i值，i为学生人数

}



void ClassFun(char* buf, char* temp, char sp)//函数功能：读取文本文件每一行，将数据进行分类，赋给结构体各成员

{

    int len = strlen(buf);

    for (int i = 0; i < len;
        i++)

    {


        if (buf[i] == sp)


        {


            memcpy(buf, buf + i + 1, strlen(buf + i + 1));//若第i+1个字符为‘sp’则判断上一个字符串结束，将后面一个字符串拷贝下来覆盖buf


            break;//覆盖之后跳出if语句，此时指针位置在buf[i+1]


        }


        temp[i] = buf[i];//将buf中的一个字符存入temp中

    }

}



void Count(struct student pStudents[], int num)//函数功能：统计班级学生人数和平均成绩

{

    int n = 1;

    char yi[11] = "2017020901";

    char er[11] = "2017020902";

    char san[11] = "2017020903";

    char si[11] = "2017020904";

    char wu[11] = "2017020905";

    char liu[11] = "2017020906";  //用于后面根据学号判断学生的班级



    for (n = 1; n <= num; n++)

    {


        if (!strncmp((pStudents + n -
            1)->major, yi, 10))//比较字符串‘学号’‘班级’前十位，判断班级


        {


            yi_per++;//判断为1，则相应班级人数+1


            yi_sum = yi_sum + (pStudents + n - 1)->sum;


            yi_ave = yi_sum / yi_per;      //班级平均分 




        }


        if (!strncmp((pStudents + n -
            1)->major, er, 10))


        {


            er_per++;


            er_sum = er_sum + (pStudents + n - 1)->sum;


            er_ave = er_sum / er_per;



        }


        if (!strncmp((pStudents + n - 1)->major,
            san, 10))


        {


            san_per++;


            san_sum = san_sum + (pStudents + n - 1)->sum;


            san_ave = san_sum / san_per;



        }


        /*if (!strncmp((pStudents + n - 1)->major,
            si, 10))


        {
            si_per++;
            si_sum = si_sum + (pStudents + n - 1)->sum;
            si_ave = si_sum / si_per;
        }
        if (!strncmp((pStudents + n - 1)->major, wu, 10))
        {
            wu_per++;
            wu_sum = wu_sum + (pStudents + n - 1)->sum;
            wu_ave = wu_sum / wu_per;
        }
        if (!strncmp((pStudents + n - 1)->major, liu, 10))
        {
            liu_per++;
            liu_sum = liu_sum + (pStudents + n - 1)->sum;
            liu_ave = liu_sum / liu_per;
        }*/
    }
    free(pStudents);//释放内存
}


