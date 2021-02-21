#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conio2.h"
#include "rlyres.h"
#include <ctype.h>  //header file to call "isDigit()" fn to check mob no.
int enterchoice()
{

    int choice,i;
    textcolor(YELLOW);
    gotoxy(28,1);
    printf("RAILWAY RESERVATION SYSTEM\n");
    for(i=1;i<=80;i++)
    {
        printf("-");
        printf("-");
    }
    printf("\nSelect an option\n");
    printf("\n1 -> View Trains");
    printf("\n2 -> Book Ticket");
    printf("\n3 -> View Ticket");
    printf("\n4 -> Search Ticket No");
    printf("\n5 -> View All Bookings");
    printf("\n6 -> View Train Bookings");
    printf("\n7 -> Cancel Ticket");
    printf("\n8 -> Cancel Train");
    printf("\n9 -> Quit");
    printf("\n\nEnter choice:\t");
    scanf("%d",&choice);
    return choice;

}
void add_trains()
{
    Train alltrains[4]={
              {"123","BPL","GWA",2100,1500},
              {"546","BPL","DEL",3500,2240},
              {"345","HBJ","AGR",1560,1135},
              {"896","HBJ","MUM",4500,3360},
              };
    FILE *fp=fopen("d:\\cproject\\railway.dat","rb");
    if(fp==NULL)
    {
        fp=fopen("d:\\cproject\\Railway.dat","wb");
        fwrite(alltrains,4*sizeof(Train),1,fp);
        printf("File created and saved!\n");

    }
    else
        printf(":)\n");
    fclose(fp);

}
void view_trains()
{
    int i;
    printf("TRAIN NO\tFROM\tTO\tFIRST AC FARE\tSECOND AC FARE\n");
     for(i=1;i<=80;i++)
        printf("-");
    FILE *fp=fopen("d:\\Cproject\\Railway.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
        printf("\n%s\t\t%s\t%s\t%d\t\t%d",tr.train_no,tr.from,tr.to,tr.fac_fare,tr.sac_fare);

    }
    printf("\n\n\n\n");
    fclose(fp);
}
int check_train_no(char *trainno)
{
    FILE *fp=fopen("d:\\cproject\\Railway.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
          if(strcmp(tr.train_no,trainno)==0)
          {
                  fclose(fp);
                  return 1;
          }

    }
fclose(fp);
return 0;
}
Passenger* get_passenger_details()
{
clrscr();
gotoxy(60,1);
textcolor(LIGHTGREEN);
printf("Press 0 to exit");
gotoxy(1,1);
textcolor(YELLOW);
printf("Enter passenger name:");
static Passenger psn;
fflush(stdin);
fgets(psn.p_name,20,stdin);
//fgets4() adds "\n" at the end of file,
//Removing "\n" from the end of name.
char *pos;
pos=strchr(psn.p_name,'\n');
*pos='\0';
//checking for name entered as 0.
if(strcmp(psn.p_name,"0")==0)
{
    textcolor(LIGHTRED);
    gotoxy(1,25);
    printf("RESERVATION CANCELLED !\n");
    getch();
    textcolor(YELLOW);
    return NULL;
}
//taking gender input.
int valid;  //taking valid=1 for verifying input.
gotoxy(1,2);
printf("Enter gender(M/F):");
do
{
    valid=1;
    fflush(stdin);
    scanf("%c",&psn.gender);
    if(psn.gender=='0')
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("\t\t\t\t\t\t\t");   //for clearing previous message.
        gotoxy(1,25);
        printf("RESERVATION CANCELLED !\n");
        getch();
        textcolor(YELLOW);
        return NULL;
    }
    if(psn.gender!='M' && psn.gender!='F')
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("Error! Gender should be M or F (in uppercase)");
        valid=0;
        getch();
        gotoxy(19,2);
        printf("\b");
        textcolor(YELLOW);
    }
}
while(valid==0);
gotoxy(1,25);
printf("\t\t\t\t\t\t\t");
//entering train no as input.
gotoxy(1,3);    //reset the cursor at the 1st col 3rd row.
printf("Enter train number:");
do
{
    fflush(stdin);
    scanf("%s",&psn.train_no);
    if(strcmp(psn.train_no,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("\t\t\t\t\t\t\t");   //for clearing previous message.
        gotoxy(1,25);
        printf("RESERVATION CANCELLED !\n");
        getch();
        textcolor(YELLOW);
        return NULL;
    }
    valid=check_train_no(psn.train_no);
    if(valid==0)    //if train no is correct, returns 0, otherwise 1.
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("Error! Invalid Train No");
        getch();
        gotoxy(20,3);
        printf("\t\t\t\t\t\t\t");   //for clearing previous message.
        gotoxy(20,3);
        textcolor(YELLOW);
    }
}
while(valid==0);
gotoxy(1,25);
printf("\t\t\t\t\t\t\t");   //for clearing previous message.
gotoxy(1,4);
printf("Enter travelling class(First AC-F,Second AC-S):");
do
{
    valid=1;
    fflush(stdin);
    scanf("%c",&psn.p_class);
    if(psn.p_class=='0')    //checking for invalid input (or zero).
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("\t\t\t\t\t\t\t");   //for clearing previous message.
        gotoxy(1,25);
        printf("RESERVATION CANCELLED !\n");
        getch();
        textcolor(YELLOW);
        return NULL;
    }
    if(psn.p_class!='F' && psn.p_class!='S')
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("Error! Travelling class should be F or S (in uppercase)");
        valid=0;
        getch();
        gotoxy(48,4);
        printf("\b");
        textcolor(YELLOW);
    }
}
while(valid==0);
gotoxy(1,25);
printf("\t\t\t\t\t\t\t");   //for clearing previous message.
gotoxy(1,5);
printf("Enter address:");
fflush(stdin);
fgets(psn.address,30,stdin);
pos=strchr(psn.address,'\n');
*pos='\0';  //replacing '\n' with '\0' at the end of file to make address input.
if(strcmp(psn.address,"0")==0)
{
    textcolor(LIGHTRED);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t");   //for clearing previous message.
    gotoxy(1,25);
    printf("RESERVATION CANCELLED !\n");
    getch();
    textcolor(YELLOW);
    return NULL;
}
gotoxy(1,6);
printf("Enter age:");
do
{
    valid=1;
    fflush(stdin);
    scanf("%d",&psn.age);
    if(psn.age==0)  //checking for age for 0.
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("\t\t\t\t\t\t\t");   //for clearing previous message.
        gotoxy(1,25);
        printf("RESERVATION CANCELLED !\n");
        getch();
        textcolor(YELLOW);
        return NULL;
    }
    if(psn.age<=0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("Error! Age should be positive");
        valid=0;
        getch();
        gotoxy(11,6);
        printf("\t\t\t\t\t\t\t");   //for clearing previous message.
        gotoxy(11,6);
        textcolor(YELLOW);
    }
}
while(valid==0);
gotoxy(1,25);
printf("\t\t\t\t\t\t\t");   //for clearing previous message.
gotoxy(1,7);
printf("Enter mobile no:");
do
{
    fflush(stdin);
    fgets(psn.mob_no,12,stdin);
    pos=strchr(psn.mob_no,'\n');
    if(pos!=NULL)
        *pos='\0';  //replacing '\n' with '\0' .
    if(strcmp(psn.mob_no,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("\t\t\t\t\t\t\t");   //for clearing previous message.
        gotoxy(1,25);
        printf("RESERVATION CANCELLED !\n");
        getch();
        textcolor(YELLOW);
        return NULL;
    }
    valid=check_mob_no(psn.mob_no);
    if(valid==0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("Error! Invalid Mobile No");
        getch();
        gotoxy(21,7);
        textcolor(YELLOW);
    }
}
while(valid==0);
return &psn;
}
//fn for checking mob no.
int check_mob_no(char *p_mob)
{
    //checking for mob no be 10-digit or 0.
    if(strlen(p_mob)!=10)
        return 0;
    while(*p_mob!='\0')
    {
    if(isdigit(*p_mob)==0)
        return 0;
    p_mob++;
    }
    return 1;
}
//fn "get_booked_ticket_count()" to retrieve no of tickets booked.
int get_booked_ticket_count(char *train_no, char tc)
{
    FILE *fp=fopen("d:\\Cproject\\Railway Reservation System\\allbookings.dat","rb");
    if(fp==NULL)
        return 0;
    Passenger pr;
    int count=0;    //to count no of tickets booked in total.
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,train_no)==0 && pr.p_class==tc)
            ++count;
    }
    fclose(fp);
    return count;
}
//getting last ticket booked so as to number the next ticket to-be-booked.
int last_ticket_no()
{
    FILE *fp=fopen("d:\\Cproject\\Railway Reservation System\\allbookings.dat","rb");
    if(fp==NULL)
        return 0;
    Passenger pr;
    fseek(fp,-1L*sizeof(pr),SEEK_END);
    fread(&pr,sizeof(pr),1,fp);
    fclose(fp);
    return pr.ticketno;
}
//designing "book_ticket()"fn to book ticket.
int book_ticket(Passenger p)
{
    int ticket_count=get_booked_ticket_count(p.train_no,p.p_class);
    if(ticket_count==30)
    {
        textcolor(LIGHTRED);
        printf("All seats full in train no %s in %c class!\n",p.train_no,p.p_class);
        return -1;
    }
    int ticket_no=last_ticket_no()+1;
    p.ticketno=ticket_no;
    FILE *fp;
    fp=fopen("d:\\Cproject\\allbookings.dat","ab");   //ab is used so to append the next ticket no.
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! File can't be opened");
        return -1;
    }
    fwrite(&p,sizeof(p),1,fp);
    fclose(fp);
    return ticket_no;
}
//designing get_ticket_no() to view all tickets booked.
int accept_ticket_no()
{
    printf("Enter a valid ticket no:");
    int valid;
    int ticket_no;
    do
    {
        valid=1;
        scanf("%d",&ticket_no);
        if(ticket_no==0)
        {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("\t\t\t\t\t\t\t");   //for clearing previous message.
        gotoxy(1,25);
        printf("Cancelling input !\n");
        getch();
        textcolor(YELLOW);
        clrscr();
        return 0;
        }
        if(ticket_no<0)
        {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("Invalid ticket no!");   //for clearing previous message.
        getch();
        valid=0;
        gotoxy(25,1);
        printf("\t\t\t\t\t\t\t");
        gotoxy(25,1);
        textcolor(YELLOW);
        }
    }
    while(valid==0);
    return ticket_no;
}
void view_ticket(int ticket_no)
{
    FILE *fp;
    fp=fopen("d:\\Cproject\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry!File can't be opened");
        return;
    }
    Passenger pr;
    int found=0;
    printf("\n--------------------------------------------------------------------------------\n");
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(pr.ticketno==ticket_no)
        {
            printf("\nNAME:%s\nGENDER:%c\nTRAIN NO:%s\nCLASS:%c\nADDRESS:%s\nAGE:%d\nMOBILE NO:%s\nTICKET NO:%d\n",pr.p_name,pr.gender,pr.train_no,pr.p_class,pr.address,pr.age,pr.mob_no,pr.ticketno);
            found=1;
            break;
        }
    }
    printf("\n--------------------------------------------------------------------------------\n");
    if(!found)
    {
        textcolor(LIGHTRED);
        printf("NO details found for ticket no : %d",ticket_no);
    }
    fclose(fp);
}
//designing accept_mob_no() fn to search ticket based on mob no.
char *accept_mob_no()
{
    static char mob_no[11];
    char *pos;
    int valid;
    printf("Enter valid mobile number:");
    do
    {
        fflush(stdin);
        fgets(mob_no,13,stdin);
        pos=strchr(mob_no,'\n');
        if(pos!=NULL)
            *pos='\0';
        if(strcmp(mob_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Cancelling Input...!");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        valid=check_mob_no(mob_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Invalid Mobile No");
            getch();
            gotoxy(21,1);
            printf("\t\t\t\t\t\t\t");
            gotoxy(27,1);
            textcolor(YELLOW);
        }
    }
    while(valid==0);
    clrscr();
    return mob_no;
}
//designing get_ticket_no() to retrieve ticket no.
int* get_ticket_no(char* p_mob_no)
{
    int count=0;
    FILE *fp;
    fp=fopen("d:\\Cproject\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! File can't be opened");
        return NULL;
    }
    Passenger pr;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,p_mob_no)==0)
            ++count;    //increment count in order to store mob no in array and adding '\0' at the last position of array.
    }
    if(!count)    //if mob no is not correct then return NULL.
    {
        fclose(fp);
        return NULL;
    }
    int *p=(int*)malloc((count+1)*sizeof(int));     //creating dynamic array to store mob no.
    rewind(fp);     //when pointer is at last index of array, then rewind() will bring back the pointer to first index.
    int i=0;    //i=0 variable is used to increment the char array pointer to check all digits of mobile no.
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,p_mob_no)==0)
        {
            *(p+i)=pr.ticketno;     //navigating here.
            i++;    //incrementing i to navigate to next pointer position.
        }
    }
    *(p+i)=-1;
    fclose(fp);
    return p;       //returning the pointer address to main function to further view ticket details.
}
//designing view_all_tickets().
void view_all_tickets(char *pmob_no,int *pticket_no)
{
    if(pticket_no==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry no tickets booked for mobile no %s",pmob_no);
        textcolor(WHITE);
        printf("\n\nPress any key to go to main menu\n");
        textcolor(YELLOW);
        getch();
        return;
    }
    printf("Following are tickets booked for mobile no %s",pmob_no);
    int i;
    printf("\n\nTICKET NO :\n");
    printf("\n--------------------------------------------------------------------------------\n");
    for(i=0; *(pticket_no+i)!=-1; i++)
    {
        printf("\n%d",*(pticket_no+i));
        printf("\n--------------------------------------------------------------------------------\n");
    }
    textcolor(WHITE);
    printf("\n\nPress any key to go to main menu\n");
    textcolor(YELLOW);
    getch();
    free(pticket_no);
}

char *accept_train_no()
{
    static char train_no[10];
    int valid;
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter train number:");
    do
    {
        fflush(stdin);
        scanf("%s",train_no);
        if(strcmp(train_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Cancelling Input...!");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        valid=check_train_no(train_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Invalid Train No");
            getch();
            gotoxy(20,1);
            printf("\t\t\t\t\t\t\t");
            gotoxy(20,1);
            textcolor(YELLOW);
        }
    }
    while(valid==0);
    clrscr();
    return train_no;
}
void view_bookings(char* train_no)
{
    int found=0,i;  //it is used to return the ticket no or an error message
                    //since ticket no may be correct, but it may possible that no ticket
                    //has been booked for some unknown reasons.Therefore if after loop, found=0 then , error message be
                    //displayed to end user.
    FILE *fp;
    fp=fopen("d:\\Cproject\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry!File cannot be opened");
        return;
    }
    Passenger pr;
    printf("TICKET NO\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILE NO\n");
    for(i=1; i<=80; i++)
        printf("-");
    int row=4;    //to know the exact row after showing all the details to user.
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,train_no)==0)
        {
            printf("\n\n%d\t\t%c\t%s",pr.ticketno,pr.p_class,pr.p_name);
            gotoxy(41,row);
            printf("%c\t%d\t%s\n",pr.gender,pr.age,pr.mob_no);
            row++;
            found=1;
        }
    }
    if(!found)
    {
        clrscr();
        textcolor(LIGHTRED);
        printf("\nNo details of bookings in train no %s found",train_no);
    }
    textcolor(WHITE);
    printf("\n\nPress any key to go to main menu!");
    textcolor(YELLOW);
    getch();
    fclose(fp);
}
int cancel_ticket(int ticket_no)
{
    FILE *fp1;
    fp1=fopen("d:\\Cproject\\allbookings.dat","rb");
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo bookings done yet!");
        return -1;
    }
    FILE *fp2;
    fp2=fopen("d:\\C_Project\\Railway Reservation System\\temp.dat","wb");
    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp1)==1)
    {
        if(pr.ticketno==ticket_no)
            found=1;    //if ticket is found,then make found=1.
        else
        {
            fwrite(&pr,sizeof(pr),1,fp2);   //if not found, then simply add the ticket to 'temp.dat' file.
        }
    }
    fclose(fp1);
    fclose(fp2);    //closing both the files before any operations.
    if(found==0)
    {
        remove("d:\\C_Project\\Railway Reservation System\\temp.dat");      //if ticket is not found,then delete the 'temp.dat' file.
    }
    else
    {
        remove("d:\\Cproject\\allbookings.dat");
        rename("d:\\C_Project\\Railway Reservation System\\temp.dat","d:\\Cproject\\allbookings.dat");     //if found,then rename 'temp.dat' to 'allbookings.dat' and check for cancelticket.
    }
    return found;
}
void view_all_bookings()
{
    int row=3;
    FILE *fp=fopen("d:\\Cproject\\allbookings.dat","rb");
    clrscr();
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("File can not be opened try after some time");
        getch();
        textcolor(YELLOW);
    }

    else
    {
        Passenger pr;
        printf("Ticket NO\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILE NO\n");
        int row=3;    //to know the exact row after showing all the details to user.
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
            printf("%d\t\t%c\t%s",pr.ticketno,pr.p_class,pr.p_name);
            gotoxy(41,row);
            printf("%c\t%d\t%s\n",pr.gender,pr.age,pr.mob_no);
            row++;
    }
    }
    fclose(fp);
}
int cancle_train(char*train_no)
{
    int result;
    FILE *fp1=fopen("d:\\Cproject\\allbookings.dat","rb");
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNO booking done yet");
        return -1;
    }


    FILE *fp2=fopen("d:\\C_Project\\Railway Reservation System\\temp.dat","wb");
    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp1)==1)
    {
        if(strcmp(pr.train_no,train_no)==0)
        {
            found=1;
        }
        else
        {
            fwrite(&pr,sizeof(pr),1,fp2);
        }

    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("d:\\C_Project\\Railway Reservation System\\temp.dat");
    }
    else
    {
        result=remove("d:\\Cproject\\allbookings.dat");
        if(result!=0)
            return 2;
        result=rename("d:\\C_Project\\Railway Reservation System\\temp.dat","d:\\Cproject\\allbookings.dat.dat");
        if(result!=0)
            return 2;

    }

    return found;

}



