#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#define size 100
#define max 1000
typedef struct {
  char ISBN[size];
  char idstd[size];
  char day[size];
}library;
typedef struct {
    char idstd[size];
    char surname[size];
    char name[size];
    char middlename[size];
    char department[size];
    char major[size];
}student;
typedef struct {
    char ISBN[size];
    char author[size];
    char namebook[size];
    int totalbook;
    int access;
}book;
//function----------------------------------------------------------------------------------
void search_student (char *filestd, char *filebook, char *filelibrary);
void search_book (char *filestd, char *filebook, char *filelibrary);
void return_book(char *filestd, char *filebook, char *filelibrary);
void borrow_book(char *filestd, char *filebook, char *filelibrary);
//definition function-----------------------------------------------------------------------
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
int main()
{
    char filestd[max]="students.csv";
    char filebook[max]="book.csv";
    char filelibrary[max]="students_book.csv";
    int i=0;
    FILE *fx;
    char *c[max];
    int temp;
    time_t     now;
    struct tm  ts;
    char   buf[size];
    time(&now);
    ts = *localtime(&now);
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S", &ts);
    printf("%s\n", buf);
    int a;
    for(;;)
    {
        printf("\n    *** Menu ***:\n");
        printf("=====================\n");
        printf("||1.Search student ||\n");
        printf("||2.Search book    ||\n");
        printf("||3.Return book    ||\n");
        printf("||4.Borrow book    ||\n");
        printf("||5.Exit           ||\n");
        printf("=====================\n");
        scanf("Choose what you want 1,2,3,4 or 5!!!\n");
        scanf("%d",&a);
        switch(a){
        case 1:
            search_student(filestd,filebook,filelibrary);
            break;
        case 2:
            search_book(filestd,filebook,filelibrary);
            break;
        case 3:
            return_book(filestd,filebook,filelibrary);
            break;
        case 4:
            borrow_book(filestd,filebook,filelibrary);
            break;
        }
        if(a==5)
            break;
        fflush(stdin);
        fx=fopen("library.log","a");
        fprintf(fx,"\n\"%s\"",buf);
        if(a==1)
            fprintf(fx,",\"Search student\"");
        else if(a==2)
            fprintf(fx,",\"Search book\"");
        else if(a==3)
            fprintf(fx,",\"Return book\"");
        else if(a==4)
            fprintf(fx,",\"borrow book\"");
        else break;
        fclose(fx);
    }
    return 0;
}