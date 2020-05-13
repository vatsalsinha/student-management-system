//STUDENT REGISTRATION SYSTEM
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<windows.h>
#include<ctype.h>
#include<conio.h>
 COORD coord={0,0}; // this is global variable
                                    //center of axis is set to the top left cornor of the screen
 void gotoxy(int x,int y)
 {
   coord.X=x;
 coord.Y=y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
 }
struct student
{
    int roll;
    char name[20];
    float marks;
    char branch[3];
};
typedef struct student stud;
void Registernew()
{   system("cls");
    FILE *fp=fopen("data.txt","wb");
    fseek(fp,0,SEEK_END);
    stud a; char ch;
    long int recsize= sizeof(a);
   do
    {   system("cls");
       gotoxy(20,16); printf("Enter roll no.: \t");
        gotoxy(40,16);scanf("%d",&a.roll);
        gotoxy(20,17);printf("Enter name: \t");
        gotoxy(40,17);scanf("%s",a.name);
        gotoxy(20,18);printf("Enter marks: \t");
        gotoxy(40,18);scanf("%f",&a.marks);
        gotoxy(20,19);printf("Enter branch: \t");
        gotoxy(40,19);scanf("%s", a.branch);
        fwrite(&a,recsize,1,fp);
        gotoxy(20,20);printf("more?y/n");
        fflush(stdin);
        gotoxy(40,20);scanf(" %c",&ch);
    }while(ch=='y'||ch=='Y');
    fclose(fp);
    system("cls");
}
void Editrecord()
{   system("cls");
    FILE *fp=fopen("data.txt","rb+");
    long int recsize;
    char ch; int r;
    stud b;
    recsize=sizeof(b);
    gotoxy(20,16);printf("enter roll which you want to edit:");
    gotoxy(100,16);scanf("%d",&r);
    //printf("pointer = %d\n", ftell(fp));
    rewind(fp); int flag=0;
    while(fread(&b,recsize,1,fp)==1)
    {
        if(r==b.roll)
        {
                gotoxy(20,17);printf("Enter new roll number\t");
                gotoxy(44,17);scanf("%d",&b.roll);
                gotoxy(20,18);printf("Enter new name: \t");
                gotoxy(40,18);scanf("%s",b.name);
                gotoxy(20,19);printf("Enter new marks: \t");
                gotoxy(40,19);scanf("%f",&b.marks);
                gotoxy(20,20);printf("Enter new branch: \t");
                gotoxy(40,20);scanf("%s", b.branch);
                fseek(fp,-recsize,SEEK_CUR);
                fwrite(&b,recsize,1,fp);
                flag=1;
                break;
        }
    }
    if(flag==0)
    {gotoxy(20,20);printf("record does not exist\n");}
          fflush(stdin);
          fclose(fp);
            getch();
    system("cls");
}
void Displayrecord()
{   system("cls");
    FILE *fp=fopen("data.txt","r");
    stud b; char ch;
    rewind(fp); int k=17;
    gotoxy(16,15);printf("Rollno.\t Name\tMarks\t\tBranch");
    while(fread(&b,sizeof(stud),1,fp)==1)
    {
        gotoxy(20,k);printf ( "%d\t %s\t %f\t %s\n",b.roll,b.name,b.marks,b.branch) ;
        k++;
    }
    fclose(fp);
    getch();
}
void Deleterecord()
{   system("cls");
    stud b; int r;
    FILE *fr=fopen("data.txt","rb+");
    FILE *fw=fopen("data1.txt","wb");
    gotoxy(20,17);printf("enter roll number to delete:\n");
    scanf("%d",&r);
    rewind(fr);
    while(fread(&b,sizeof(stud),1,fr)==1)
    {
        if(r!=b.roll)
        {
            fwrite(&b,sizeof(stud),1,fw);
        }
    }

    fclose(fr);
    fclose(fw);
    gotoxy(20,19);printf("done........\n");
    remove("data.txt");
    rename("data1.txt","data.txt");
    fr=fopen("data.txt","r");
    fclose(fr);
    getch();
}
void Addrecord()
{   system("cls");
    FILE *fp=fopen("data.txt","a");
    FILE *fr=fopen("data.txt","rb");
    fseek(fp,0,SEEK_END);
    stud a,b; char ch;
    gotoxy(20,16);printf("Enter roll no.: \t");
    scanf("%d",&a.roll); int found=0,r;
    r=a.roll;
    while(fread(&b,sizeof(b),1,fr)==1)
    {
        if(r==b.roll)
            found=1;
    }
    fclose(fr);
    if(found==1)
    {
        gotoxy(20,18);printf("record exists. Enter another roll number and try again\n");
    }
    else
    {



    long int recsize= sizeof(a);
        system("cls");
        gotoxy(20,17);printf("Enter name: \t");
        scanf("%s",a.name);
        gotoxy(20,18);printf("Enter marks: \t");
        scanf("%f",&a.marks);
        gotoxy(20,19);printf("Enter branch: \t");
        scanf("%s", a.branch);
        fwrite(&a,recsize,1,fp);
        gotoxy(20,20);
    fclose(fp);
    }
    getch();
    system("cls");


}
void Searchrecord()
{   system("cls");
    FILE *fp=fopen("data.txt","r");
    stud b;
    rewind(fp);
    int r , flag=0;
    gotoxy(20,16);printf("enter roll number to be searched:\n");
    scanf("%d",&r);
    while(fread(&b,sizeof(stud),1,fp)==1)
    {
        if(r==b.roll)
        {
            gotoxy(20,17);printf("Found :)\n");
            gotoxy(20,20);printf("%d\t %s\t %f\t %s\n",b.roll,b.name,b.marks,b.branch);
            flag++;
        }
    }
    if(flag==0)
        {gotoxy(20,20);printf("not found :(\n");}
    fclose(fp);
    getch();
}

int main()
{

    int ch;
    do
    {
        system("cls");
        gotoxy(20,5);printf("\t \tWelcome to Student Registration System:\n");
    gotoxy(15,8);printf("Select any one of these options below:\n");
        gotoxy(10,10);printf("1. Register New Student\n");
        gotoxy(10,12);printf("2. Edit Existing Student Record\n");
        gotoxy(10,14);printf("3. Delete existing Student Record\n");
        gotoxy(10,16);printf("4. Display existing records\n");
        gotoxy(10,18);printf("5. Search a particular record\n");
        gotoxy(10,20);printf("6. Append record\n");
        gotoxy(10,22);printf("7. Exit\n");
        gotoxy(70,15);scanf("%d",&ch);
        switch(ch)
        {
            case 1: Registernew();break;
            case 2: Editrecord();break;
            case 3: Deleterecord();break;
            case 4: Displayrecord();break;
            case 5: Searchrecord();break;
            case 6: Addrecord();break;
            case 7: system("cls"); printf("Exiting........");break;
            default:{system("cls");gotoxy(10,16);printf("enter valid choice\n");}
            getch();
        }
    }while(ch!=7);
    return 0;

}

