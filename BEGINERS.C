
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#define max 15
void food();
void payment();
void export();
void admin();
void menu();
int top=-1,b=0,no1=0;
struct node
{
int s;
char item[20];
int price;
int stk;
struct node *next;
};
struct node *nn=NULL,*temp=NULL,*root=NULL,*arr[max]={0},*s[5],*first;
FILE *fp;
void push(struct node *root)
{
s[++top]=root;
}
struct node * pop()
{
return s[top--];
}
void export(int no)
{
struct node *last=NULL;
int i;
fp=fopen("food.c","w");
for(i=0;i<no;i++)
{
last=arr[i];
fprintf(fp,"\n\t%d",last->s);
fprintf(fp,"\t%s",last->item);
fprintf(fp,"\t%d",last->price);
fprintf(fp,"\t%d",last->stk);
}
fclose(fp);
}
void food()
{
int i,j,a,d,y,n,q,f;
clrscr();
fp=fopen("count.c","r");
fscanf(fp,"%d",&n);
fclose(fp);
fp=fopen("food.c","r");
for(i=0;i<n;i++)
{
nn=(struct node*)malloc(sizeof(struct node));
arr[i]=nn;
fscanf(fp,"%d",&nn->s);
fflush(stdin);
fscanf(fp,"%s",nn->item);
fscanf(fp,"%d",&nn->price);
fscanf(fp,"%d",&nn->stk);
nn->next=NULL;
}
fclose(fp);
printf("\n\t\titem no\t\titem\t\tprice\t\tstock");
for(j=0;j<n;j++)
{
temp=arr[j];
while(temp!=NULL)
{
printf("\n\t\t%d",temp->s);
printf("\t\t%s",temp->item);
printf("\t\t%d",temp->price);
printf("\t\t%d",temp->stk);
temp=temp->next;
}
}
printf("\n\n\n\t\t\t1:place your order\n\n\t\t\t2:main menu: ");
scanf("%d",&y);
if(y!=1)
{
menu();
}
else
{
printf("\n\t\t\tselect your item: ");
scanf("%d",&a);
printf("\n\n\t\t\t\tenter food quantity: ");
scanf("%d",&b);
for(i=0;i<n;i++)
{
temp=arr[i];
while(temp!=NULL)
{
if(a==temp->s)
push(temp);
temp=temp->next;
}
}
first=pop();
if((first->stk==0)||(first->stk<b))
{
clrscr();
printf("\n\n\n\t\t\tItem is out of stock");
printf("\n\n\t\t\t\t***>1:Back ");
scanf("%d",&q);
if(q==1)
food();
}
else
{
d=b*first->price;
clrscr();
printf("\n\n\t\tyour item is %s and its cost is %d",first->item,d);
printf("\n\n\n\t\t\t1:conform to buy\n\t\t\t2:food menu: ");
scanf("%d",&f);
switch(f)
{
case 1:payment(first,b,n,d);break;
case 2:food(n);break;
default:printf("invalid choise");
}
}
}
}
void payment(struct node *a,int b,int c,int d)
{
int g,h=0,ch,o;
long int ele;
char pass[5],k,fb[10];
clrscr();
printf("\n\n\t\t\t1:cash\n\t\t\t2:credit\n\t\t\t3:back: ");
scanf("%d",&g);
switch(g)
{
case 1:printf("\n\t\tyour order is conformed");
printf("\n\n\t\t\tpay the cash while taking your order");
printf("\n\n\n\t\t\t\tThank you..");
fp=fopen("total.c","r");
fscanf(fp,"%d",&ele);
fclose(fp);
d=d+ele;
fp=fopen("total.c","w");
fprintf(fp,"%d",d);
fclose(fp);
a->stk=a->stk-b;
export(c);
fp=fopen("sold.c","a");
fprintf(fp,"\n\t%s",first->item);
fprintf(fp,"\t%d",b);
fprintf(fp,"\t%d",b*first->price);
fclose(fp);
printf("\n\n\t\t\t1:Wanna buy another Delicious?\n\t\t\t2:main menu: ");
scanf("%d",&ch);
if(ch==1)
food(c);
else
{
clrscr();
fp=fopen("feedbk.c","a");
printf("\n\n\t\tPlease give your feedback");
printf("\n\n\t\t\tEnter your name:");
scanf("%s",fb);
fprintf(fp,"\n\t%s",fb);
printf("\n\t\t\tEnter your rating(out of 5):");
scanf("%d",&o);
fprintf(fp,"\t%d",o);
fclose(fp);
}
menu();
break;
case 2:printf("\n\n\t\tenter your card number:");
scanf("%ld",&ele);
printf("\n\t\t\tenter your 4 digit  pin number:");
while(h!=4)
{
k=getch();
printf("*");
pass[h]=k;
h++;
}
pass[h]='\0';
getch();
clrscr();
printf("\n\n\t\t\t\tpayment is successfull");
printf("\n\n\n\n\t\t\t\t Thnak you....");
fp=fopen("total.c","r");
fscanf(fp,"%d",&ele);
fclose(fp);
d=d+ele;
fp=fopen("total.c","w");
fprintf(fp,"%d",d);
fclose(fp);
a->stk=a->stk-b;
export(c);
fp=fopen("sold.c","a");
fprintf(fp,"\n\t%s",first->item);
fprintf(fp,"\t%d",b);
fprintf(fp,"\t%d",b*first->price);
fclose(fp);
printf("\n\n\t\t\t1:Wanna buy another Delicious?\n\t\t\t2:main menu: ");
scanf("%d",&ch);
if(ch==1)
food(c);
else
{
clrscr();
fp=fopen("feedbk.c","a");
printf("\n\n\t\tPlease give your feedback");
printf("\n\n\t\t\tEnter your name:");
scanf("%s",fb);
fprintf(fp,"\n\t%s",fb);
printf("\n\t\t\tEnter your rating(out of 5):");
scanf("%d",&o);
fprintf(fp,"\t%d",o);
fclose(fp);
}
menu();
break;
case 3:food(c);break;
}
}
void total()
{
int sum,i;
clrscr();
fp=fopen("total.c","r");
fscanf(fp,"%d",&sum);
fclose(fp);
printf("\n\t\t\tThe total cash is %d",sum);
printf("\n\n\t\t\t\t***>1:back:");
scanf("%d",&i);
if(i==1)
admin();
}
void add()
{
int b,q,qq,qqq,p;
char qa[10];
clrscr();
fp=fopen("count.c","r");
fscanf(fp,"%d",&p);
fclose(fp);
p=p+1;
fp=fopen("count.c","w");
fprintf(fp,"%d",p);
fclose(fp);
fp=fopen("food.c","a");
printf("\n\tenter s so:");
scanf("%d",&q);
fprintf(fp,"\n%d",q);
printf("\n\tenter item name:");
scanf("%s",&qa);
fprintf(fp,"\t%s",qa);
printf("\n\tenter price:");
scanf("%d",&qq);
fprintf(fp,"\t%d",qq);
printf("\n\tenter stk:");
scanf("%d",&qqq);
fprintf(fp,"\t%d",qqq);
fclose(fp);
clrscr();
printf("\n\n\t\t\tThe item is added successfully");
printf("\n\n\n\t\t\t\t***>1:Back ");
scanf("%d",&b);
if(b==1)
admin();
}
void del()
{
int j,q,i,key,k,m;
clrscr();
fp=fopen("count.c","r");
fscanf(fp,"%d",&m);
fclose(fp);
printf("\n\t\titem no\t\titem\t\tprice\t\tstock");
fp=fopen("food.c","r");
for(i=0;i<m;i++)
{
nn=(struct node*)malloc(sizeof(struct node));
arr[i]=nn;
fscanf(fp,"%d",&nn->s);
fflush(stdin);
fscanf(fp,"%s",nn->item);
fscanf(fp,"%d",&nn->price);
fscanf(fp,"%d",&nn->stk);
nn->next=NULL;
}
fclose(fp);
for(j=0;j<m;j++)
{
temp=arr[j];
while(temp!=NULL)
{
printf("\n\t\t%d",temp->s);
printf("\t\t%s",temp->item);
printf("\t\t%d",temp->price);
printf("\t\t%d",temp->stk);
temp=temp->next;
}
}
printf("\n\n\t\tEnter item no to delete:");
scanf("%d",&key);
fp=fopen("food.c","w");
for(k=0;k<m;k++)
{
temp=arr[k];
if(key!=temp->s)
{
fprintf(fp,"\n\t%d",temp->s);
fprintf(fp,"\t%s",temp->item);
fprintf(fp,"\t%d",temp->price);
fprintf(fp,"\t%d",temp->stk);
}
else
continue;
}
fclose(fp);
fp=fopen("count.c","w");
fprintf(fp,"%d",m-1);
fclose(fp);
clrscr();
printf("\n\n\t\tThe item is successfully deleted");
printf("\n\n\t\t\t\t***>1:Back ");
scanf("%d",&q);
if(q==1)
admin();
}
void stock()
{
int j,i,k,m,q;
clrscr();
fp=fopen("count.c","r");
fscanf(fp,"%d",&m);
fclose(fp);
printf("\n\t\titem no\t\titem\t\tprice\t\tstock");
fp=fopen("food.c","r");
for(i=0;i<m;i++)
{
nn=(struct node*)malloc(sizeof(struct node));
arr[i]=nn;
fscanf(fp,"%d",&nn->s);
fflush(stdin);
fscanf(fp,"%s",nn->item);
fscanf(fp,"%d",&nn->price);
fscanf(fp,"%d",&nn->stk);
nn->next=NULL;
}
fclose(fp);
for(j=0;j<m;j++)
{
temp=arr[j];
while(temp!=NULL)
{
printf("\n\t\t%d",temp->s);
printf("\t\t%s",temp->item);
printf("\t\t%d",temp->price);
printf("\t\t%d",temp->stk);
temp=temp->next;
}
}
printf("\n\n\t\t\t\t***>1:Back ");
scanf("%d",&q);
if(q==1)
admin();
}
void backup()
{
int i,q;
clrscr();
for(i=1;i<=100;i++)
{
delay(70);
gotoxy(32,12);
cprintf("Backup......%d %",i);
}
printf(" completed");
printf("\n\n\n\t\t\t\t***>1:Back ");
scanf("%d",&q);
if(q==1)
admin();
}
void sold()
{
int pri,q,it,t;
char ss[10];
clrscr();
fp=fopen("sold.c","r");
printf("\n\t\t\tItem\t\tquantity\tMoney");
while(!feof(fp))
{
fscanf(fp,"%s",ss);
printf("\n\t\t\t%s",ss);
fscanf(fp,"%d",&it);
printf("\t\t%d",it);
fscanf(fp,"%d",&pri);
printf("\t\t%d",pri);
}
fclose(fp);
fp=fopen("total.c","r");
fscanf(fp,"%d",&t);
printf("\n\t\t\t\t\t\t      ------");
printf("\n\t\t\t\t\t         Total: %d",t);
printf("\n\t\t\t\t\t\t      ------");
fclose(fp);
printf("\n\n\n\t\t\t\t***>1:Back ");
scanf("%d",&q);
if(q==1)
admin();
}
void feed()
{
int r,q;
char fb[10];
clrscr();
fp=fopen("feedbk.c","r");
printf("\n\t\t\tName\t\tRating");
while(!feof(fp))
{
fscanf(fp,"%s",fb);
printf("\n\n\t\t\t%s",fb);
fscanf(fp,"%d",&r);
printf("\t\t%d*",r);
}
fclose(fp);
printf("\n\n\n\t\t\t\t***>1:Back ");
scanf("%d",&q);
if(q==1)
admin();
}
void pswrd()
{
int q;
char ops[10],ps[10],np1[10],np2[10];
clrscr();
fp=fopen("pswrd.c","r");
fscanf(fp,"%s",ps);
fclose(fp);
fp=fopen("pswrd.c","w");
pass:
printf("\n\t\tEnter your old 8 digit pswrd:");
scanf("%s",ops);
clrscr();
if(strcmp(ps,ops)==0)
{
nn:
printf("\n\t\t\tEnter new 8 digit pswd:");
scanf("%s",np1);
printf("\n\t\tConform new 8 digit pswd:");
scanf("%s",np2);
if(strcmp(np1,np2)!=0)
{
printf("\n\t\tyour new pswrd does not  match,try again");
goto nn;
}
}
else
{
printf("\n\t\t\tYou enter wrong old pswrd");
goto pass;
}
clrscr();
printf("\n\n\t\tYour pswrd changed successfully..");
fprintf(fp,"%s",np1);
fclose(fp);
printf("\n\n\n\t\t\t\t***>1:Back ");
scanf("%d",&q);
if(q==1)
admin();
}
void pannel()
{
int ab,h=0;
char pass[10],k,pswd[10];
fp=fopen("pswrd.c","r");
fscanf(fp,"%s",pswd);
fclose(fp);
printf("\n\n\t\t\t1:login\n\t\t\t2:main menu  ");
scanf("%d",&ab);
if(ab!=1)
{
menu();
}
else
{
clrscr();
printf("\n\t\tEnter your 8 digit pswd:");
while(h!=8)
{
k=getch();
printf("*");
pass[h]=k;
h++;
}
pass[h]='\0';
getch();
if(strcmp(pswd,pass)==0)
{
admin();
}
else
{
clrscr();
printf("\n\t\tYou enter wrong pswd,please try again");
pannel();
}
}
}
void admin()
{
int ad;
clrscr();
printf("\n\t\t   You are in admin pannel");
printf("\n\n\n\t\t\t1:Total cash\n\t\t\t2:Add food\n\t\t\t3:Delete food");
printf("\n\t\t\t4:Items in stock\n\t\t\t5:Backup system\n\t\t\t6:ordered food ");
printf("\n\t\t\t7:Feedback\n\t\t\t8:Change pswrd\n\t\t\t0:Main menu\n\t\t\t\t");
scanf("%d",&ad);
if(ad==0)
menu();
else
{
switch(ad)
{
case 1:total();break;
case 2:add();break;
case 3:del();break;
case 4:stock();break;
case 5:backup();break;
case 6:sold();break;
case 7:feed();break;
case 8:pswrd();break;
}
}
}
void menu()
{
int op;
FILE *ptr;
clrscr();
ptr=fopen("count.c","r");
fscanf(ptr,"%d",&no1);
printf("\n\n\n\n\n\t\t\t1:Items menu\n\t\t\t2:Admin pannel\n\t\t\t3:Exit\n\t\t\t  ");
scanf("%d",&op);
if(op==3)
getch();
switch(op)
{
case 1:food();break;
case 2:clrscr();
pannel();
break;
}
}
void main()
{
int i;
int gd=DETECT,gm;
initgraph(&gd,&gm,"c:\\turboc3\\bgi");
outtextxy(200,170,"LOADING.....");
rectangle(199,179,450,191);
for(i=0;i<250;i++)
{
setcolor(2);
rectangle(200,180,200+i,190);
delay(15);
}
cleardevice();
settextstyle(7,0,2);
outtextxy(100,100,"WELCOME  TO");
delay(1500);
outtextxy(200,150,"FOOD ORDERED");
delay(1000);
outtextxy(300,200,"MANAGEMENT SYSTEM");
delay(1500);
settextstyle(0,0,1);
setcolor(3);
outtextxy(380,300,"Done by:");
outtextxy(380,315,"Sunischal-F1");
outtextxy(380,330,"Harshitha-F5");
outtextxy(380,345,"Geethika-D9");
outtextxy(380,360,"Rakesh-G4");
outtextxy(380,375,"Srithika-H7");
delay(2000);
closegraph();
menu();
}


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

 
 
 
 

 
 
 

 
 
 
 
 
 
 
 
 
 


























































