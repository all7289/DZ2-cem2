#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#define size 100
#define max 1000
typedef struct {
  char login[size];
  char pass[size];
  int student;
  int book;
}users;
typedef struct {
    char idstd[size];
    char surname[size];
    char name[size];
    char middlename[size];
    char department[size];//faculty
    char major[size];
}student;
typedef struct {
    char ISBN[size];
    char author[size];
    char namebook[size];
    int totalbook;
    int access;
}book;
typedef struct {
  char ISBN[size];
  char idstd[size];
  char day[size];
}library;
//menu student
int test (char *Namefile,char test[size]);
void add_student(char *Namefile);
void delete_student(char *filestd,char *filelibrary);
void search_student (char *filestd, char *filebook, char *filelibrary);
void copy_file(char *Namefile);
void restore_file();
int menu();
void history_student(int choice,char *login);
void main_student(char *login,char *filestd, char *filebook, char *filelibrary);
//menu book
int test_book (char *Namefile,char test[size]);
void add_book(char *Namefile);
int delete_book(char *filebook,char *filelibrary);
void search_book (char *filestd, char *filebook, char *filelibrary);
void info_book(char *Namefile);
void return_book(char *filestd, char *filebook, char *filelibrary);
void borrow_book(char *filestd, char *filebook, char *filelibrary);
int menu_book();
void history_book(int choice,char *login);
void main_book(char *login,char *filestd, char *filebook, char *filelibrary);
//menu user 
void read_file(char *Namefile,char *filestd, char *filebook, char *filelibrary);
int test_user (char *Namefile,char test[size]);
void add_user(char *Namefile);
//definition function
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
void delete_student(char *filestd,char *filelibrary)
{
    student data[max];
    library datalbr[max];
    char deleteid[size];
    int i=0,j;
    char temp[size];
    FILE *f;
    printf("Enter ID student to delete\n");
    fflush(stdin);
    gets(deleteid);
    FILE *flbr;
    flbr=fopen(filelibrary,"r+");
    int b=0;
    if(!flbr)
    {
        printf("No file!!\n");
    }
    else
    {
        rewind(flbr);
        while(fgets(temp,size,flbr))
        {
           fscanf(flbr, "%[^,],%[^,],%[^\n]",datalbr[b].ISBN,datalbr[b].idstd,datalbr[b].day);
           b++;
        }
    }
    fclose(flbr);
    int del_id=0;
    for(j=0;j<b;j++)
    {
        if(strcmp(datalbr[j].idstd,deleteid)==0)
        {
            del_id=1;
            break;
        }
    }
    if(del_id==1)
    {
        printf(" Can not delete, this student is borrowing book");
        getch();
    }
    else
    {
        f= fopen(filestd,"r+");
        if(!f)
        {
            printf("No file!!!\n");
            getch();
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
        int k=-1;
        for(j=0;j<i;j++)
        {
            if(strcmp(deleteid,data[j].idstd)==0)
                k =j;
        }
        if(k==-1)
        {
            printf("No student found in file!!!\n");
        }
        else
        {
            f=fopen(filestd,"w");
            rewind(f);
            fprintf(f,"ID,Surname,Name,Middlename,Department,Major\n");
            for(j=0;j<i-1 ;j++)
            {
                if( j!=k)
                {
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
}
void search_student (char *filestd, char *filebook, char *filelibrary)
{
    student datastd[max];
    book databook[max];
    library datalbr[max];
    char searchidstd[size];
    char temp[size];
    int j=0;
    int test;
    FILE *fstd;
    printf("Enter Id student\n");
    fflush(stdin);
    gets(searchidstd);
    fstd= fopen(filestd,"r+");
    int a=0;
    if(!fstd)
    {
        printf("No file!\n");
    }
    else
    {
        rewind(fstd);
        while(fgets(temp,size,fstd))
        {
           fscanf(fstd, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",datastd[a].idstd,datastd[a].surname,datastd[a].name,datastd[a].middlename,datastd[a].department,datastd[a].major);
           a++;
        }
    }
    fclose(fstd);
    FILE *flbr;
    flbr=fopen(filelibrary,"r+");
    int b=0;
    if(!flbr)
    {
        printf("No file!!\n");
    }
    else
    {
        rewind(flbr);
        while(fgets(temp,size,flbr))
        {
           fscanf(flbr, "%[^,],%[^,],%[^\n]",datalbr[b].ISBN,datalbr[b].idstd,datalbr[b].day);
           b++;
        }
    }
    fclose(flbr);
    FILE *fbook;
    fbook=fopen(filebook,"r+");
    int x,c=0;
    if(!fbook)
    {
        printf("No file!!!\n");
    }
    else
    {
        rewind(fbook);
        while(fgets(temp,size,fbook))
        {
           fscanf(fbook, "%[^,],%[^,],%[^,],%d,%d]",databook[c].ISBN,databook[c].author,databook[c].namebook,&databook[c].totalbook,&databook[c].access);
           c++;
        }
    }
    x=-1;
    for(j=0;j<a;j++)
    {
        if(strcmp(searchidstd,datastd[j].idstd)==0)
                x=j;
    }
    int y ;
    int k[size];
    if(x==-1)
    {
        printf("No student in file!!!\n");
    }
    else
    {
        for(j=0;j<b;j++){
            if(strcmp(datalbr[j].idstd,datastd[x].idstd)==0)
                k[j]=j;
            else k[j]=-1;
        }
        printf("%10s%15s%10s%20s%25s%15s%10s\n","Idstd","Day","ISBN","Author","Namebook","Totalbook","Access");
        test=-1;
        for(j=0;j<b;j++){
            y=k[j];
            if(y!=-1){
                int m=0;
                for(m;m<=c;m++){
                    if(strcmp(datalbr[y].ISBN,databook[m].ISBN)==0)
                       {
                           printf("%10s%15s%10s%20s%25s%15d%10d\n",datastd[x].idstd,datalbr[y].day,databook[m].ISBN,databook[m].author,databook[m].namebook,databook[m].totalbook,databook[m].access);
                           test=1;
                       }
                }
            }
        }
        if(test==-1)
                printf("This student dont borrow book\n");
    }
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
  printf("\nTake choice : \n");
  do {
    c = getch();
  } while (c<'0' || c>'6');
  return c-'0';
}
void history_student(int choice,char *login)
{
    FILE *fx;
    time_t     now;
    struct tm  ts;
    char   buf[size];
    time(&now);
    ts = *localtime(&now);
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S", &ts);
    printf("%s\n", buf);
    fx=fopen("library_student.log","a");
    fprintf(fx,"\n\"%s\"",buf);
    fprintf(fx,",\"%s\"",login);
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
void main_student(char *login,char *filestd, char *filebook, char *filelibrary)
{
    //char filestd[]="students.csv";
    int i=0;
    int a;
    for(;;)
    {
        a=menu();
         switch(a){
        case 1:
            add_student(filestd);
            break;
        case 2:
            search_student(filestd,filebook,filelibrary);
            break;
        case 3:
            delete_student(filestd,filelibrary);
            break;
        case 4:
            copy_file(filestd);
            break;
        case 5:
            restore_file();
            break;
        }
        if(a==6)
            break;
        fflush(stdin);
        history_student(a,login);
    }
}
int test_book (char *Namefile,char test[size])
{
    book data[max];
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
        rewind(f);
        while(fgets(temp,size,f))
        {
           fscanf(f, "%[^,],%[^,],%[^,],%d,%d",data[i].ISBN,data[i].author,data[i].namebook,&data[i].totalbook,&data[i].access);
           i++;
        }
    }
    int k=-1;
    int j=0;
    for(j;j<=i;j++)
    {
        if(strcmp(test,data[j].ISBN)==0)
            k =j ;
    }
    fclose(f);
    return k;
}
void add_book(char *Namefile)
{
    book newb;
    int n;
    int i=0;
    FILE *f;
    printf("How many book do you want to add? \n");
    scanf ("%d",&n);
    f=fopen(Namefile,"a");
    for(i=0;i<n;i++)
    {
        int k;
        printf("Enter book %d\n",i+1);
        printf("Enter ISBN :\n");
        do{
        fflush(stdin);
        gets(newb.ISBN);
        k=test_book(Namefile, newb.ISBN);
        if(k!=-1)
        {
            printf("Error:This book is already in the file!!!\n");
            printf("Enter ISBN :\n");
        }
        }
        while(k!=-1);
        printf("Enter author : \n");
        fflush(stdin);
        gets(newb.author);

        printf("Enter namebook :\n");
        fflush(stdin);
        gets(newb.namebook);

        printf("Enter totalbook :\n");
        fflush(stdin);
        scanf("%d",&newb.totalbook);

        printf("Enter access:\n");
        fflush(stdin);
        scanf("%d",&newb.access);

       fprintf(f,"%s",newb.ISBN);
       fprintf(f,",%s",newb.author);
       fprintf(f,",%s",newb.namebook);
       fprintf(f,",%d",newb.totalbook);
       fprintf(f,",%d\n",newb.access);
    }
    fclose(f);
    printf("\nSuccess!!!\n");
    getch();
}
int delete_book(char *filebook,char *filelibrary)
{
    book data[max];
    library datalbr[max];
    char deletebook[size];
    int i=0,j;
    char temp[size];
    FILE *f;
    printf("Enter ISBN :\n");
    fflush(stdin);
    gets(deletebook);
    FILE *flbr;
    flbr=fopen(filelibrary,"r+");
    int b=0;
    if(!flbr)
    {
        printf("No file!!\n");
    }
    else
    {
        rewind(flbr);
        while(fgets(temp,size,flbr))
        {
           fscanf(flbr, "%[^,],%[^,],%[^\n]",datalbr[b].ISBN,datalbr[b].idstd,datalbr[b].day);
           b++;
        }
    }
    fclose(flbr);
    int del_IBSN=0;
    for(j=0;j<b;j++)
    {
        if(strcmp(deletebook,datalbr[j].ISBN)==0)
        {
            del_IBSN=1;
            break;
        }
    }
    if(del_IBSN==1)
    {
        printf(" Can not delete, this book is borrowed book");
        getch();
    }
    else
    {
        f= fopen(filebook,"r+");
        if(!f)
        {
            printf("No file!!!\n");
        }
        else
        {
            rewind(f);
            while(fgets(temp,size,f))
            {
                fscanf(f, "%[^,],%[^,],%[^,],%d,%d",data[i].ISBN,data[i].author,data[i].namebook,&data[i].totalbook,&data[i].access);
                i++;
            }
        }
        int k=-1;
        for(j=0;j<i;j++)
        {
            if(strcmp(deletebook,data[j].ISBN)==0)
                k =j ;
        }
        if(k==-1)
        {
            printf("No book found in file!!!\n");
        }
        else
        {
            f=fopen(filebook,"w");
            rewind(f);
            fprintf(f,"ISBN,Author,Namebook,Totalbook,Access\n");
            for(j=0;j<i-1;j++)
            {
                if( j!=k)
                {
                    fprintf(f,"%s",data[j].ISBN);
                    fprintf(f,",%s",data[j].author);
                    fprintf(f,",%s",data[j].namebook);
                    fprintf(f,",%d",data[j].totalbook);
                    fprintf(f,",%d\n",data[j].access);
                }
            }
            fclose(f);
            printf("\nSuccess!!!\n");
        }
        getch();
    }    
}
void search_book (char *filestd, char *filebook, char *filelibrary)
{
    student datastd[max];
    book databook[max];
    library datalbr[max];
    char searchISBN[size];
    char temp[size];
    int j=0;
    int test;
    FILE *fstd;
    printf("Enter ISBN\n");
    fflush(stdin);
    gets(searchISBN);
    fstd= fopen(filestd,"r+");
    int a=0;
    if(!fstd)
    {
        printf("No file!\n");
    }
    else
    {
        rewind(fstd);
        while(fgets(temp,size,fstd))
        {
           fscanf(fstd, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",datastd[a].idstd,datastd[a].surname,datastd[a].name,datastd[a].middlename,datastd[a].department,datastd[a].major);
           a++;
        }
    }
    fclose(fstd);
    FILE *flbr;
    flbr=fopen(filelibrary,"r+");
    int b=0;
    if(!flbr)
    {
        printf("No file!!\n");
    }
    else
    {
        rewind(flbr);
        while(fgets(temp,size,flbr))
        {
           fscanf(flbr, "%[^,],%[^,],%[^\n]",datalbr[b].ISBN,datalbr[b].idstd,datalbr[b].day);
           b++;
        }
    }
    fclose(flbr);
    FILE *fbook;
    fbook=fopen(filebook,"r+");
    int x,c=0;
    if(!fbook)
    {
        printf("No file!!!\n");
    }
    else
    {
        rewind(fbook);
        while(fgets(temp,size,fbook))
        {
           fscanf(fbook, "%[^,],%[^,],%[^,],%d,%d]",databook[c].ISBN,databook[c].author,databook[c].namebook,&databook[c].totalbook,&databook[c].access);
           c++;
        }
    }
    x=-1;
    for(j=0;j<a;j++)
    {
        if(strcmp(searchISBN,databook[j].ISBN)==0)
                x=j;
    }
    int y ;
    int k[size];
    if(x==-1)
    {
        printf("No book in library!!!\n");
    }
    else//co sach
    {
        for(j=0;j<b;j++){
            if(strcmp(datalbr[j].ISBN,databook[x].ISBN)==0)
                k[j]=j;
            else k[j]=-1;
        }
        test=-1;
        printf("%10s%15s%10s%10s%15s%15s%10s\n","IDstd","Day","Surname","Name","Middlename","Department","Major");
        for(j=0;j<b;j++){
            y=k[j];
            if(y!=-1){
                int m=0;
                for(m;m<c;m++){
                    if(strcmp(datalbr[y].idstd,datastd[m].idstd)==0)
                       {
                           printf("%10s%15s%10s%10s%15s%15s%10s\n",datastd[m].idstd,datalbr[y].day,datastd[m].surname,datastd[m].name,datastd[m].middlename,datastd[m].department,datastd[m].major);
                           test=1;
                       }
                }
            }
        }
        if(test==-1)
                printf("This book is not borrowed");
    }
    getch();
}
void info_book(char *Namefile)
{
    book data[max];
    int *arrdata[max];
    int i=0;
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
           fscanf(f, "%[^,],%[^,],%[^,],%d,%d",data[i].ISBN,data[i].author,data[i].namebook,&data[i].totalbook,&data[i].access);
           i++;
        }
    }
    //i-number of line
    fclose(f);
    int x,y;
    //bubblesort
    for(x=0;x<i-1;x++)
	{
		for(y=i-2;y>x;y--)
		{
		   if(strcmp(data[y-1].ISBN,data[y].ISBN)>0)
		  {
			book k=data[y];
            data[y]=data[y-1];
            data[y-1]=k;
		  }
		}
	}
    printf("\n%10s%25s%25s%10s%10s\n","ISBN","author","namebook","totalbook","access");
    for(x=0;x<i-1;x++)
    {
        printf("%10s%25s%25s%10d%10d\n",data[x].ISBN,data[x].author,data[x].namebook,data[x].totalbook,data[x].access);
    }
    printf("\nSuccess!!!\n");
    getch();
}
void return_book(char *filestd, char *filebook, char *filelibrary)
{
    book databook[max];
    library datalbr[max];
    char searchISBN[size];
    char searchIDstd[size];
    char temp[size];
    int j;
    printf("Enter Id student\n");
    fflush(stdin);
    gets(searchIDstd);
    printf("Enter ISBN\n");
    fflush(stdin);
    gets(searchISBN);
    FILE *flbr;
    flbr=fopen(filelibrary,"r+");
    int b=0;
    if(!flbr)
    {
        printf("No file!!\n");
    }
    else
    {
        rewind(flbr);
        while(fgets(temp,size,flbr))
        {
           fscanf(flbr, "%[^,],%[^,],%[^\n]",datalbr[b].ISBN,datalbr[b].idstd,datalbr[b].day);
           b++;
        }
    }
    fclose(flbr);
    FILE *fbook;
    fbook=fopen(filebook,"r+");
    int c=0;
    if(!fbook)
    {
        printf("No file!!!\n");
    }
    else
    {
        rewind(fbook);
        while(fgets(temp,size,fbook))
        {
           fscanf(fbook, "%[^,],%[^,],%[^,],%d,%d]",databook[c].ISBN,databook[c].author,databook[c].namebook,&databook[c].totalbook,&databook[c].access);
           c++;
        }
    }
    fclose(fbook);
    flbr=fopen(filelibrary,"w");
    fprintf(flbr,"%s,%s,%s\n","ISBN","ID std","Day");
    for(j=0;j<b-1;j++)
    {
        if(strcmp(searchISBN,datalbr[j].ISBN)==0 && strcmp(searchIDstd,datalbr[j].idstd)==0);//k[j]!=-1
        else
            fprintf(flbr,"%s,%s,%s\n",datalbr[j].ISBN,datalbr[j].idstd,datalbr[j].day);
    }
    fclose(flbr);
    fbook=fopen(filebook,"w");
    fprintf(fbook,"%s,%s,%s,%s,%s\n","ISBN","author","book name","total book","access");
    for(j=0;j<c-1;j++)
    {
        if(strcmp(databook[j].ISBN,searchISBN)==0)
            fprintf(fbook,"%s,%s,%s,%d,%d\n",databook[j].ISBN,databook[j].author,databook[j].namebook,databook[j].totalbook,(databook[j].access-1));
        else
            fprintf(fbook,"%s,%s,%s,%d,%d\n",databook[j].ISBN,databook[j].author,databook[j].namebook,databook[j].totalbook,databook[j].access);
    }
    fclose(fbook);
    printf("\n Suceess return!!!");
    getch();
}
void borrow_book(char *filestd, char *filebook, char *filelibrary)
{
    student datastd[max];
    book databook[max];
    library datalbr[max];
    char searchISBN[size];
    char searchIDstd[size];
    int j;
    char temp[size];
    printf("Enter Id student\n");
    fflush(stdin);
    gets(searchIDstd);
    printf("Enter ISBN\n");
    fflush(stdin);
    gets(searchISBN);
    FILE *flbr;
    flbr=fopen(filelibrary,"r+");
    int b=0;
    if(!flbr)
    {
        printf("No file!!\n");
    }
    else
    {
        rewind(flbr);
        while(fgets(temp,size,flbr))
        {
           fscanf(flbr, "%[^,],%[^,],%[^\n]",datalbr[b].ISBN,datalbr[b].idstd,datalbr[b].day);
           b++;
        }
    }
    fclose(flbr);
    FILE *fbook;
    fbook=fopen(filebook,"r+");
    int c=0;
    if(!fbook)
    {
        printf("No file!!!\n");
    }
    else
    {
        rewind(fbook);
        while(fgets(temp,size,fbook))
        {
           fscanf(fbook, "%[^,],%[^,],%[^,],%d,%d]",databook[c].ISBN,databook[c].author,databook[c].namebook,&databook[c].totalbook,&databook[c].access);
           c++;
        }
    }
    fclose(fbook);
    int test=-1;
    int x;
    for(j=0;j<c-1;j++)
    {
        if(strcmp(searchISBN,databook[j].ISBN)==0)
        {
            test=-1;
            x=j;
            break;
        }
        else
            test=j;  
    }
    if(test!=-1)
        printf("\nNo book in library!!!!\n");
    else
    {
        if(databook[x].totalbook == databook[x].access)
        {
            printf("\nNot enough book to borrow!!!\n");
            int y=0,n=0;
            for(j=0;j<b;j++)
            {
                if(strcmp(searchISBN,datalbr[j].ISBN)==0)
                {
                    n=j;//first place
                    y=j;//place run folllowing circle
                    break;
                }
            }
            for(j=n+1;j<b;j++)
            {
                if(strcmp(searchISBN,datalbr[j].ISBN)==0)
                {
                    if(strcmp(datalbr[y].day,datalbr[j].day)>0)
                    y=j;
                }
            }
            printf("Suggestion:  %s  you can borrow this book!!!",datalbr[y].day);
        }           
        else
        {
            fbook=fopen(filebook,"w");
            fprintf(fbook,"%s,%s,%s,%s,%s\n","ISBN","author","book name","total book","access");
            for(j=0;j<c-1;j++)
            {
                if(strcmp(databook[j].ISBN,searchISBN)==0)
                    fprintf(fbook,"%s,%s,%s,%d,%d\n",databook[j].ISBN,databook[j].author,databook[j].namebook,databook[j].totalbook,(databook[j].access+1));
                else
                    fprintf(fbook,"%s,%s,%s,%d,%d\n",databook[j].ISBN,databook[j].author,databook[j].namebook,databook[j].totalbook,databook[j].access);
            }
            fclose(fbook);
            char time[size];
            printf("Enter time you want to return folloing this form(year-month-date):\n");
            fflush(stdin);
            gets(time);
            flbr=fopen(filelibrary,"a+");
            fprintf(flbr,"%s,%s,%s\n",searchISBN,searchIDstd,time);
            fclose(flbr);
            printf("Borrow success!!!!");
        }
    }
    getch();
}
int menu_book()
{
    char c;
  printf("+-------- Menu --------+");
  printf("\n+----------------------+");
  printf("\n+ 1.Add new book       +");
  printf("\n+ 2.Search book        +");
  printf("\n+ 3.Delete book        +");
  printf("\n+ 4.Information book   +");
  printf("\n+ 5.Return book        +");
  printf("\n+ 6.Borow book         +");
  printf("\n+ 7.Exit               +");
  printf("\n+----------------------+");
  printf("\nTake choice : \n");
  do {
    c = getch();
  } while (c<'0' || c>'7');
  return c-'0';
}
void history_book(int choice,char *login)
{
     FILE *fx;
    time_t     now;
    struct tm  ts;
    char       buf[80];
    time(&now);
    ts = *localtime(&now);
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S", &ts);
    printf("%s\n", buf);
    fx=fopen("library_book.log","a");
    fprintf(fx,"\n\"%s\"",buf);
    fprintf(fx,",\"%s\"",login);
    if(choice==1)
        fprintf(fx,",\"Add new book\"");
    if(choice==2)
         fprintf(fx,",\"Search book\"");
    if(choice==3)
        fprintf(fx,",\"Delete book\"");
    if(choice==4)
        fprintf(fx,",\"Information book\"");
    if(choice==5)
        fprintf(fx,",\"Return book\"");
    if(choice==6)
        fprintf(fx,",\"Borrow book\"");
    fclose(fx);
}
void main_book(char *login,char *filestd, char *filebook, char *filelibrary)
{
    //char Namefile[]="book.csv";
    int a;
    for(;;)
    {
        a=menu_book();
        switch(a){
        case 1:
            add_book(filebook);
            break;
        case 2:
            search_book(filestd,filebook,filelibrary);
            break;
        case 3:
            delete_book(filebook,filelibrary);
            break;
        case 4:
            info_book(filebook);
            break;
        case 5:
            return_book(filestd,filebook,filelibrary);
            break;
        case 6:
            borrow_book(filestd,filebook,filelibrary);
            break;
        }
        if(a==7)
            break;
        fflush(stdin);
        history_book(a,login);
    }
}
void read_file(char *Namefile,char *filestd, char *filebook, char *filelibrary)
{
	char login[100];
	char pass[100];
	char temp[size];
	int i=0;
    FILE *f;
    users data[max];
    f=fopen(Namefile,"r+");
    if(!f)
    {
        printf("No file to read!!");
        exit(1);
    }
    else
    {
        rewind(f);
        while(fgets(temp,size,f))
        {
           fscanf(f, "%[^,],%[^,],%d,%d\n",data[i].login,data[i].pass,&data[i].student,&data[i].book);
           i++;
        }
    }
    fclose(f);
    int k=-1;
    int c;
    do{
        fflush(stdin);
        printf("Enter login : ");gets(login);
        printf("Enter password : ");gets(pass);
        int j=0;
        for(j;j<=i;j++)
        {
            if(strcmp(login,data[j].login)==0 && strcmp(pass,data[j].pass)==0)
                k =j ;
        }
        if(k==-1)
        {
            printf("Your login or password is not correct!!!\n");
            printf("You want to login again?\n");
            printf("1.Yes\n");
            printf("2.No\n");
            int test;
            scanf("%d",&test);
            if(test==2)
            {
                FILE *fx;
                time_t     now;
                struct tm  ts;
                char buf[80];
                time(&now);
                ts = *localtime(&now);
                strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S", &ts);
                fx=fopen("library_user.log","a");
                fprintf(fx,"\n\"%s\"",buf);
                fprintf(fx,",\"login unsuccessful\"");
                fclose(fx);
                break;
            }
        }
        else
        {
            FILE *fx;
            time_t     now;
            struct tm  ts;
            char buf[80];
            time(&now);
            ts = *localtime(&now);
            strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S", &ts);
            fx=fopen("library_user.log","a");
            fprintf(fx,"\n\"%s\"",buf);
            fprintf(fx,",\"login successful\"");
            fclose(fx);
        }
    }
    while(k==-1);
    if (k!=-1)
    {
        printf("Congratulations !!! You are successfully logged in!!!\n");
        printf("Book : %d \n",data[k].book);
        printf("Student : %d \n",data[k].student);

    if(data[k].book==1 && data[k].student==0 )
    {
        printf("\nWELCOME TO LIBRARY!!!\n");
        main_book(login,filestd,filebook,filelibrary);
        c=1;

    }
    if (data[k].book==0 && data[k].student==1 )
    {
        printf("\nWELCOME TO LIST STUDENTS!!!\n");
        main_student(login,filestd,filebook,filelibrary);
        c=2;

    }
    if(data[k].book==1 && data[k].student==1 )
    {
        for(;;)
        {
            printf("\n======================\n");
            printf("||1. MENU BOOK.     ||\n");
            printf("||2. MENU STUDENTS. ||\n");
            printf("||3. EXIT.          ||\n");
            printf("======================\n");
            printf("\nChoose what you want 1,2 or 3!!!\n"); scanf("%d",&c);
       if(c==1)
       {
            printf("\nWELCOME TO LIBRARY!!!\n");
            main_book(login,filestd,filebook,filelibrary);
       }
       else if(c==2)
       {
            printf("\nWELCOME TO LIST STUDENTS!!!\n");
            main_student(login,filestd,filebook,filelibrary);
       }
       else break;
    }
    }
    }
}
int test_user (char *Namefile,char test[size])
{
    users data[max];
    int i=0;
    char temp[size];
    FILE *f;
    f= fopen(Namefile,"a+");
    if(!f)
    {
        return 0;
    }
    else
    {
        rewind(f);//return poiter at first position
        while(fgets(temp,size,f))
        {
           fscanf(f, "%[^,],%[^,],%d,%d",data[i].login,data[i].pass,&data[i].student,&data[i].book);
           i++;
        }
    }
    int k=-1;
    int j=0;
    for(j;j<=i;j++)
    {
        if(strcmp(test,data[j].login)==0) //compare two string
            k =j ;
    }
    fclose(f);
    return k;
}
void add_user(char *Namefile)
{
    users new_user;
    int n;
    int i=0;
    FILE *f;
    f=fopen(Namefile,"a+");
        int k;
        printf("Login :");
        do{
        fflush(stdin);
        gets(new_user.login);
        k=test(Namefile, new_user.login);
        if(k!=-1)
        {
            printf("Error:This user is already in the file!!!\n");
            printf("Login :");
        }
        }
        while(k!=-1);
        printf("Password : ");
        fflush(stdin);
        gets(new_user.pass);

        printf("Acess student:");
        fflush(stdin);
        scanf("%d",&new_user.student);

        printf("Access book :");
        fflush(stdin);
        scanf("%d",&new_user.book);

       fprintf(f,"%s",new_user.login);
       fprintf(f,",%s",new_user.pass);
       fprintf(f,",%d",new_user.student);
       fprintf(f,",%d\n",new_user.book);
    fclose(f);
    printf("\nSuccess!!!\n");
}
int main()
{   
    int acc; 
    char user_file[]="users.csv";
    char filestd[max]="students.csv";
    char filebook[max]="book.csv";
    char filelibrary[max]="students_book.csv";
    for(;;)
    {
    printf ("\nYou have account?\n");
    printf("======================\n");
    printf("||1. Yes.           ||\n");
    printf("||2. No, Register . ||\n");
    printf("||3. EXIT.          ||\n");
    printf("======================\n");
    scanf("%d",&acc);
    switch(acc)
    {
    case 1:
        read_file(user_file,filestd,filebook,filelibrary);
        break;
    case 2:
        add_user(user_file);
        break;
    }
    if(acc==3)
        break;
    }
    return 0;
}