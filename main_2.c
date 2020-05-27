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
void main_student(char *login)
{
    char Namefile[]="students.csv";
    int i=0;
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
int delete_book(char *Namefile)
{
    book data[max];
    char deletebook[size];
    int i=0;
    char temp[size];
    FILE *f;
    printf("Enter ISBN :\n");
    fflush(stdin);
    gets(deletebook);
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
    int k=-1;
    int j=0;
    for(j;j<i;j++)
    {
        if(strcmp(deletebook,data[j].ISBN)==0)
            k =j ;
    }
    if(k==-1)
    {
        printf("No book found in file!!!\n");
    }
    else{
        f=fopen(Namefile,"w");
        rewind(f);
        fprintf(f,"ISBN,Author,Namebook,Totalbook,Access\n");
        for(j=0;j<i-1;j++){
        if( j!=k){
        fprintf(f,"%s",data[j].ISBN);
        fprintf(f,",%s",data[j].author);
        fprintf(f,",%s",data[j].namebook);
        fprintf(f,",%d",data[j].totalbook);
        fprintf(f,",%d\n",data[j].access);
        }
    }
    fclose(f);
    }
    printf("\nSuccess!!!\n");
    getch();
}
void search_book(char *Namefile)
{
    book data[max];
    char searchISBN[size];
    int i=0;
    char temp[size];
    FILE *f;
    printf("Enter ISBN :\n");
    fflush(stdin);
    gets(searchISBN);
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
    int k=-1;
    int j=0;
    for(j;j<=i;j++)
    {
        if(strcmp(searchISBN,data[j].ISBN)==0)
            k =j ;
    }
    fclose(f);
    printf("Loading.....\n");
    printf("%10s%25s%25s%10d%10d\n","ISBN","Author","Namebook","Totalbook","Access");
    if(k!=-1)
    {
            printf("%10s%25s%25s%10d%10d\n",data[k].ISBN,data[k].author,data[k].namebook,data[k].totalbook,data[k].access);
            printf("Success!!!\n\n");
    }
    else
    {
        printf("\nNo book!!!\n");
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
int menu_book()
{
    char c;
  printf("+-------- Menu --------+");
  printf("\n+----------------------+");
  printf("\n+ 1.Add new book       +");
  printf("\n+ 2.Search book        +");
  printf("\n+ 3.Delete book        +");
  printf("\n+ 4.Information book   +");
  printf("\n+ 5.Exit               +");
  printf("\n+----------------------+");
  printf("\nTake choice : ");
  do {
    c = getch();
  } while (c<'0' || c>'5');
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
    fclose(fx);
}
void main_book(char *login)
{
    char Namefile[]="book.csv";
    int a;
    for(;;)
    {
        a=menu_book();
        switch(a){
        case 1:
            add_book(Namefile);
            break;
        case 2:
            search_book(Namefile);
            break;
        case 3:
            delete_book(Namefile);
            break;
        case 4:
            info_book(Namefile);
            break;
        }
        if(a==5)
            break;
        fflush(stdin);
        history_book(a,login);
    }
}
void read_file(char *Namefile)
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
        main_book(login);
        c=1;

    }
    if (data[k].book==0 && data[k].student==1 )
    {
        printf("\nWELCOME TO LIST STUDENTS!!!\n");
        main_student(login);
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
            main_book(login);
       }
       else if(c==2)
       {
            printf("\nWELCOME TO LIST STUDENTS!!!\n");
            main_student(login);
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
        read_file(user_file);
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