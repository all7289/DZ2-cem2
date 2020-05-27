#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#define size 100
#define max 1000
int test (char *Namefile,char test[size]);
void add_student(char *Namefile);
void delete_student (char *Namefile);
void search_student(char *Namefile);
void copy_file(char *Namefile);
void restore_file(char *Namefile);
int menu();
void history_student(int choice);
typedef struct {
    char idstd[size];
    char surname[size];
    char name[size];
    char middlename[size];
    char department[size];//faculty
    char major[size];
}student;
int test (char *Namefile,char test[size])
{
    student data[max];
    int i=0;
    char temp[size];
    FILE *f;
    f= fopen(Namefile,"r+");
    if(!f)
    {
        return 0;
    }
    else
    {
        rewind(f);//return poiter at first position
        while(fgets(temp,size,f))
        {
           fscanf(f, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",data[i].idstd,data[i].surname,data[i].name,data[i].middlename,data[i].department,data[i].major);
           i++;
        }
    }
    int k=-1;
    int j=0;
    for(j;j<=i;j++)
    {
        if(strcmp(test,data[j].idstd)==0) //compare two string
            k =j ;
    }
    fclose(f);
    return k;
}
void add_student(char *Namefile)
{
    student newstd;
    int n;
    int i=0;
    FILE *f;
    printf("How many students do you want to add?\n");
    scanf ("%d",&n);
    f=fopen(Namefile,"a");
    for(i=0;i<n;i++)
    {
        int k;
        printf("Enter information student %d\n",i+1);
        printf("Enter ID :");
        do{
        fflush(stdin);
        gets(newstd.idstd);
        k=test(Namefile, newstd.idstd);
        if(k!=-1)
        {
            printf("Error:This student is already in the file!!!\n");
            printf("Enter ID :");
        }
        }
        while(k!=-1);
        printf("Enter Surname : ");
        fflush(stdin);
        gets(newstd.surname);

        printf("Enter name :");
        fflush(stdin);
        gets(newstd.name);

        printf("Enter middle name :");
        fflush(stdin);
        gets(newstd.middlename);

        printf("Enter department :");
        fflush(stdin);
        gets(newstd.department);

        printf("Enter major :");
        fflush(stdin);
        gets(newstd.major);

       fprintf(f,"%s",newstd.idstd);
       fprintf(f,",%s",newstd.surname);
       fprintf(f,",%s",newstd.name);
       fprintf(f,",%s",newstd.middlename);
       fprintf(f,",%s",newstd.department);
       fprintf(f,",%s\n",newstd.major);
    }
    fclose(f);
    printf("\nSuccess!!!\n");
    getch();
}
void delete_student(char *Namefile)
{
    student data[max];
    char deleteid[size];
    int i=0;
    char temp[size];
    FILE *f;
    printf("Enter ID student to delete\n");
    fflush(stdin);
    gets(deleteid);
    f= fopen(Namefile,"r+");
    if(!f)
    {
        printf("No file!!!\n");
    }
    else
    {
        rewind(f);
        while(fgets(temp,size,f))
        {
           fscanf(f, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",data[i].idstd,data[i].surname,data[i].name,data[i].middlename,data[i].department,data[i].major);
           i++;
        }

    }
    int k=-1;
    int j=0;
    for(j;j<i;j++)
    {
        if(strcmp(deleteid,data[j].idstd)==0)
            k =j;
    }
    fclose(f);
    if(k==-1)
    {
        printf("No student found in file!!!\n");
    }
    else{
        f=fopen(Namefile,"w");
        rewind(f);
        fprintf(f,"ID,Surname,Name,Middlename,Department,Major\n");
        for(j=0;j<i-1 ;j++){
        if( j!=k){
        fprintf(f,"%s",data[j].idstd);
        fprintf(f,",%s",data[j].surname);
        fprintf(f,",%s",data[j].name);
        fprintf(f,",%s",data[j].middlename);
        fprintf(f,",%s",data[j].department);
        fprintf(f,",%s\n",data[j].major);
        }
    }
    fclose(f);
        printf("\nSuccess!!!\n");
    }
    getch();
}
void search_student(char *Namefile)
{
    student data[max];
    char searchsur[size];
    int i=0;
    char temp[size];
    FILE *f;
    printf("Enter surname\n");
    fflush(stdin);
    gets(searchsur);
    f= fopen(Namefile,"r+");
    if(!f)
    {
        printf("No file!!!\n");
    }
    else
    {
        rewind(f);
        while(fgets(temp,size,f))
        {
           fscanf(f, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",data[i].idstd,data[i].surname,data[i].name,data[i].middlename,data[i].department,data[i].major);
           i++;
        }
    }
    int test=0;
    int k[i+1];
    int j=0;
    for(j;j<=i;j++)
    {
        if(strcmp(searchsur,data[j].surname)==0)
                k[j]=j;
        else
            k[j]=-1;
    }
    fclose(f);
    printf("loading.....\n");
    printf("%10s%10s%10s%15s%10s%10s\n","ID","Surname","Name","Middlename","Department","Major");
    for(j=0;j<=i;j++){
        if(k[j]!=-1)
        {
            printf("%10s%10s%10s%15s%10s%10s\n",data[j].idstd,data[j].surname,data[j].name,data[j].middlename,data[j].department,data[j].major);
            test=1;
        }
    }
    if(test==0)
    {
        printf("No student found in file!!!\n");
    }
    else
        printf("\nSuccess!!!\n");
    getch();
}
void copy_file(char *Namefile)
{
    student data[max];
    int i=0,j;
    char temp[size];
    FILE *f;
    f= fopen(Namefile,"r+");
    if(!f)
    {
        printf("No file!!!\n");
    }
    else
    {
        rewind(f);
        while(fgets(temp,size,f))
        {
           fscanf(f, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",data[i].idstd,data[i].surname,data[i].name,data[i].middlename,data[i].department,data[i].major);
           i++;
        }
    }
    fclose(f);
    time_t     now;
    struct tm  ts;
    char  buf[size];
    int n1;
    int n2;
    int n;
    char c[size]="students_";
    time(&now);
    ts = *localtime(&now);
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S", &ts);
    n1=strlen(c);
    n2=strlen(buf);
    for(n=0; n<n2; n++)
    {
        if(buf[n]==' ')
        {
            buf[n]='.';
        }
        if(buf[n]==':')
        {
            buf[n]='-';
        }
        c[n+n1]=buf[n];
    }
    c[n1+n2]='.';
    c[n1+n2+1]='c';
    c[n1+n2+2]='s';
    c[n1+n2+3]='v';
    c[n1+n2+4]='\0';
    printf("%s\n",c);
    FILE *fcopy;
    fcopy=fopen(c,"w");
    rewind(fcopy);
    fprintf(fcopy,"ID,Surname,Name,Middlename,Department,Major\n");
    for(j=0;j<i-1 ;j++){
    fprintf(fcopy,"%s",data[j].idstd);
    fprintf(fcopy,",%s",data[j].surname);
    fprintf(fcopy,",%s",data[j].name);
    fprintf(fcopy,",%s",data[j].middlename);
    fprintf(fcopy,",%s",data[j].department);
    fprintf(fcopy,",%s\n",data[j].major);
    }
    fclose(fcopy);
    printf("\nSuccess!!!\n");
    getch();
}
void restore_file()
{
    student data[max];
    int i=0,j,n;
    char c[size];
    char temp[size];
    FILE *f,*f1;
    printf("Enter the folder you backed up:\n");
            char Namefile[size];
            fflush(stdin);
            gets(Namefile);
    f= fopen(Namefile,"r+");
    if(!f)
    {
        printf("No file!!!\n");
    }
    else
    {
        rewind(f);
        while(fgets(temp,size,f))//temp array->bufer memory
        {
           fscanf(f, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",data[i].idstd,data[i].surname,data[i].name,data[i].middlename,data[i].department,data[i].major);
           i++;
        }
    }
    fclose(f);
    f1=fopen("students.csv","w");
    rewind(f1);
    fprintf(f1,"ID,Surname,Name,Middlename,Department,Major\n");
    for(j=0;j<i-1 ;j++){
    fprintf(f1,"%s",data[j].idstd);
    fprintf(f1,",%s",data[j].surname);
    fprintf(f1,",%s",data[j].name);
    fprintf(f1,",%s",data[j].middlename);
    fprintf(f1,",%s",data[j].department);
    fprintf(f1,",%s\n",data[j].major);
    }
    fclose(f1);
    printf("\nYou've successfully restore the folder!!!\n");
    getch();
}

int menu()
{
  char c;
  printf("+-------- Menu --------+");
  printf("\n+----------------------+");
  printf("\n+ 1.Add new student    +");
  printf("\n+ 2.Search student     +");
  printf("\n+ 3.Delete student     +");
  printf("\n+ 4.Copy file student  +");
  printf("\n+ 5.Restore data       +");
  printf("\n+ 6.Exit programm      +");
  printf("\n+----------------------+");
  printf("\nTake choice : ");
  do {
    c = getch();
  } while (c<'0' || c>'6');
  return c-'0';
}
void history_student(int choice)
{
    FILE *fx;
    time_t     now;
    struct tm  ts;
    char   buf[size];
    time(&now);
    ts = *localtime(&now);
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S", &ts);
    printf("%s\n", buf);
    fx=fopen("library.log","a");
    fprintf(fx,"\n\"%s\"",buf);
    if(choice==1)
        fprintf(fx,",\"Add new students\"");
    if(choice==2)
        fprintf(fx,",\"Search students\"");
    if(choice==3)
        fprintf(fx,",\"Delete studens\"");
    if(choice==4)
        fprintf(fx,",\"Copy file\"");
    if(choice==5)
        fprintf(fx,",\"Restore file\"");
    fclose(fx);
}
int main()
{
    char Namefile[]="students.csv";
    int a;
    for(;;)
    {
        a=menu();
         switch(a){
        case 1:
            add_student(Namefile);
            break;
        case 2:
            search_student(Namefile);
            break;
        case 3:
            delete_student(Namefile);
            break;
        case 4:
            copy_file(Namefile);
            break;
        case 5:
            restore_file();
            break;
        }
        if(a==6)
            break;
        fflush(stdin);
        history_student(a);
    }
    return 0;
}