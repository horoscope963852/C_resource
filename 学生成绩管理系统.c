#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996) 

struct student {

    char number[13];//ѧ��

    char name[8];//����

    char major[13]; //�༶

    int test_sco;//ʵ��ɼ�

    int paper_sco;//����ɼ�

    int sum;//�ܳɼ�

};

int yi_per = 0, yi_ave, yi_sum = 0;

int er_per = 0, er_ave, er_sum = 0;

int san_per = 0, san_ave, san_sum = 0;//3��������ֳɼ���ʼֵΪ0

int ReadStudentInfo(const char* filename, struct student** pStudents);

//�������ļ���ʧ�ܷ��� - 1��

//��ͷ��βɨ�������ļ�����Ԥ��һ�飩���ѧ��������

//����ѧ������������malloc��sizeof�Ⱥ����������Ϊstruct student * *pStudents�����ڴ棻

//����rewind��������λ���ļ�ͷ��

//��ȡ�����ļ�������ÿһ����¼ͨ�������±귨��ָ�뷨���浽�ṹ������pStudents�У�

//�ر��ļ���

//����ѧ��������


int ReadStudentInfo(const char* filename, struct student** pStudents);
void Count(struct student pStudents[], int num);



int main()

{

    int count;

    struct student* list = NULL;// ����ṹ��ָ��list������ʼ��ΪNULL

    int m = 0;

    //struct student* list;//����ṹ��ָ��list

    count = ReadStudentInfo("D:\\homework files\\Class1.txt", &list);//���ļ��ж�ȡѧ����Ϣ���洢���ṹ�������У�list�ᱻ�����ڴ�

    if (count > 0 && list != NULL) {
        printf("\nѧ����Ϣ����ϵͳ��\n\n");
        printf("ѧ����Ϣ��\n");
        printf("----------------------------------------------------\n");
        printf("ѧ��\t\t����\t\t�༶\t\tʵ��ɼ�\t\t���ڳɼ�\t\t�ܳɼ�\n");

        // ��������Ӵ�ӡѧ����Ϣ�Ĵ��룬ѭ�������ṹ�����飬��ʹ��printf������ӡÿ��ѧ������Ϣ

        // �ڴ�ӡ��ѧ����Ϣ���ͷŶ�̬������ڴ��Ա����ڴ�й©
        free(list);
    }
    else {
        printf("δ�ܳɹ���ȡѧ����Ϣ���ڴ����ʧ�ܡ�\n");
    }

    int point;
    scanf_s("%d", &point);

    for (m = 1; m <count; m++)

    {

        printf("%2d %8s %8s %8s %5d %5d %5d\n", m, (list + m -1)->name, (list + m - 1)->number, (list + m - 1)->major, (list + m -1)->paper_sco, (list + m - 1)->test_sco, (list + m - 1)->sum);//��ӡѧ����Ϣ

    }




    Count(list, count);//����༶ѧ��������ƽ���ɼ�


    printf("\nͳ����Ϣ ��\n");


    printf("----------------------------------------------------\n");


    printf("ѧ��      �༶       �༶ѧ������   ƽ���ɼ�\n");


    printf("1   2017020901 % 3d % 3d\n", yi_per, yi_ave);


        printf("2    2017020902 % 3d % 3d\n", er_per, er_ave);


            printf("3   2017020903 % 3d % 3d\n", san_per, san_ave);//��ӡͳ����Ϣ

                            return 0;

}



void ClassFun(char* buf, char* temp, char sp);



int ReadStudentInfo(const char* filename, struct student** pStudents)

{

    FILE* fp;

    char row;

    int i = 0, j;

    fp
        = fopen(filename, "r");//���ļ�

    //�������ļ���ʧ�ܷ���-1

    if (fp == NULL)

    {


        printf("cann't open the file");


        exit(-1);

    }

    row
        = fgetc(fp);//���ļ�ָ��fpָ����ļ��ж�ȡһ���ַ�������   

    //��ͷ��βɨ�������ļ����ѧ������

    while (row != EOF)//EOF��end of file����˼, �����ж��Ƿ����ļ��Ľ�β��

    {


if (row == '\n')//�����س�


{


i++;//iΪ�ļ�����


}


row = fgetc(fp);//������ȡ��һ��

    }

    rewind(fp);
    //���ļ��ڲ���λ��ָ������ָ���ļ��Ŀ�ͷ



    row
        = fgetc(fp);

    *pStudents = (struct student*)malloc(sizeof(**pStudents) * i);//���䶯̬�ڴ�ռ�

    char buf[512] = { 0 };//����



    char str[100];


    fgets(str, sizeof(str), fp); //�ļ��ĵ�һ������Ч�����ݣ�������һ��



    for (j = 0; j < i - 1;
        j++)

    {


        memset(*pStudents + j, 0, sizeof(struct student));//�ṹ���ʼ��


        fgets(buf, 512, fp);//��ȡ��j+1�е����ݣ�����\n����


        int len = strlen(buf);//��������ַ�����buf�ĳ���




        buf[len] = ' ';//���ַ����󲹳�ո��Ա���һ��Cutstring��Ϊ������־


        ClassFun(buf, (*pStudents + j)->number, '   ');//��1������ǰΪѧ��


            ClassFun(buf, (*pStudents + j)->name, ' ');//��2������ǰΪ����




            char test_Score[12], paper_Score[12];


        memset(test_Score, 0, 12);//��ʼ������


        memset(paper_Score, 0, 12);//��ʼ������




        ClassFun(buf, test_Score, ' ');//��3������ǰΪʵ��ɼ�


        (*pStudents + j)->test_sco = atoi(test_Score);//��ʵ��ɼ�ת��Ϊ�������������ṹ���ַ(*pStudents + j)->test_sco




        ClassFun(buf, paper_Score, '   ');//��4������ǰΪ����ɼ�


        (*pStudents + j)->paper_sco = atoi(paper_Score);//������ɼ�ת��Ϊ�������������ṹ���ַ(*pStudents + j)->paper_sco


        (*pStudents + j)->sum = ((*pStudents +
            j)->test_sco) * 0.4 + ((*pStudents +
                j)->paper_sco) * 0.6;//�����ܳɼ�


        memcpy((*pStudents + j)->major, (*pStudents + j)->number,
            10);

    }


    fclose(fp);//�ر��ļ�

    return (i);//����iֵ��iΪѧ������

}



void ClassFun(char* buf, char* temp, char sp)//�������ܣ���ȡ�ı��ļ�ÿһ�У������ݽ��з��࣬�����ṹ�����Ա

{

    int len = strlen(buf);

    for (int i = 0; i < len;
        i++)

    {


        if (buf[i] == sp)


        {


            memcpy(buf, buf + i + 1, strlen(buf + i + 1));//����i+1���ַ�Ϊ��sp�����ж���һ���ַ���������������һ���ַ���������������buf


            break;//����֮������if��䣬��ʱָ��λ����buf[i+1]


        }


        temp[i] = buf[i];//��buf�е�һ���ַ�����temp��

    }

}



void Count(struct student pStudents[], int num)//�������ܣ�ͳ�ư༶ѧ��������ƽ���ɼ�

{

    int n = 1;

    char yi[11] = "2017020901";

    char er[11] = "2017020902";

    char san[11] = "2017020903";

    char si[11] = "2017020904";

    char wu[11] = "2017020905";

    char liu[11] = "2017020906";  //���ں������ѧ���ж�ѧ���İ༶



    for (n = 1; n <= num; n++)

    {


        if (!strncmp((pStudents + n -
            1)->major, yi, 10))//�Ƚ��ַ�����ѧ�š����༶��ǰʮλ���жϰ༶


        {


            yi_per++;//�ж�Ϊ1������Ӧ�༶����+1


            yi_sum = yi_sum + (pStudents + n - 1)->sum;


            yi_ave = yi_sum / yi_per;      //�༶ƽ���� 




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
    free(pStudents);//�ͷ��ڴ�
}


