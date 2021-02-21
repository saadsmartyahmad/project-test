#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "conio2.h"
#include "rlyres.h"

int main()
{
    int choice,ticket_no,*pticket_no,result;
    char *pmob_no, *ptrain_no, *train_no;
    Passenger *ptr;
    add_trains();
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit");
    while(1)
    {
        choice=enterchoice();
        if(choice==9)
            exit(0);
        else if(choice==0)
            {
            gotoxy(1,25);
            clrscr();
            printf("EXITTING!!!");
            exit(0);
            }
        switch(choice)
        {
                       case 1:
                                view_trains();
                                getch();
                                clrscr();
                                break;
                       case 2:
                                ptr=get_passenger_details();
                                clrscr();
                                if(ptr!=NULL)
                                {
                                    ticket_no=book_ticket(*ptr);
                                    if(ticket_no==-1)
                                    {
                                        textcolor(LIGHTRED);
                                        printf("Booking Failed!");
                                    }
                                    else
                                    {
                                        textcolor(LIGHTGREEN);
                                        printf("Ticket successfully booked\nYour ticket no is:\t%d",ticket_no);
                                    }
                                    textcolor(WHITE);
                                    printf("\nPress any key to continue to main window!");
                                    getch();
                                    clrscr();
                                }
                                break;
                       case 3:
                                clrscr();
                                gotoxy(60,1);
                                textcolor(LIGHTGREEN);
                                printf("Press 0 to exit");
                                textcolor(YELLOW);
                                gotoxy(1,1);
                                ticket_no=accept_ticket_no();
                                if(ticket_no!=0)
                                    view_ticket(ticket_no);
                                textcolor(WHITE);
                                printf("\n\nPress any key to continue to main screen!\n");
                                getch();
                                clrscr();
                                break;
                       case 4:
                                clrscr();
                                gotoxy(60,1);
                                textcolor(LIGHTGREEN);
                                printf("Press 0 to exit");
                                textcolor(YELLOW);
                                gotoxy(1,1);
                                pmob_no=accept_mob_no();
                                if(pmob_no!=NULL)
                                {
                                    pticket_no=get_ticket_no(pmob_no);
                                    view_all_tickets(pmob_no,pticket_no);
                                }
                                clrscr();
                                break;
                       case 5:
                                clrscr();
                                view_all_bookings();
                                break;
                       case 6:
                                clrscr();
                                clrscr();
                                gotoxy(60,1);
                                textcolor(LIGHTGREEN);
                                printf("Press 0 to exit");
                                textcolor(YELLOW);
                                gotoxy(1,1);
                                ptrain_no=accept_train_no();
                                if(ptrain_no!=NULL)
                                    view_bookings(ptrain_no);
                                clrscr();
                                break;
                       case 7:
                                clrscr();
                                clrscr();
                                gotoxy(60,1);
                                textcolor(LIGHTGREEN);
                                printf("Press 0 to exit");
                                textcolor(YELLOW);
                                gotoxy(1,1);
                                ticket_no=accept_ticket_no();
                                if(ticket_no!=0)
                                {
                                    result=cancel_ticket(ticket_no);
                                    if(result==0)
                                    {
                                        textcolor(LIGHTRED);
                                        printf("Sorry! No tickets booked against ticket no %d",ticket_no);
                                    }
                                    else if(result==1)
                                    {
                                        textcolor(LIGHTGREEN);
                                        printf("Ticket No %d successfully cancelled",ticket_no);
                                    }
                                    else if(result==2)
                                    {
                                        textcolor(LIGHTRED);
                                        printf("Sorry! Error in cancellation. Try again!");
                                    }
                                        textcolor(WHITE);
                                        printf("\n\nPress any key to go to main menu!");
                                }
                                getch();
                                clrscr();
                                break;
                       case 8:
                                clrscr();
                                train_no=accept_train_no();
                                if(train_no!=NULL)
                                {
                                    //result=cancel_train(train_no);
                                    if(result==0)
                                    {
                                        textcolor(LIGHTRED);
                                        gotoxy(1,3);
                                        printf("Sorry!No ticket has been booked against %s no!",train_no);
                                    }
                                    else if(result==1)
                                    {
                                        textcolor(GREEN);
                                        gotoxy(1,3);
                                        printf("Train has been cancelled");
                                    }
                                    else if(result==2)
                                    {
                                        textcolor(GREEN);
                                        gotoxy(1,3);
                                        printf("Error contact application provider");
                                    }
                                    textcolor(WHITE);
                                    printf("\nPress any key to go back to main screen");
                                    getch();
                                    clrscr();
                                }
                                break;
                      default:
                                textcolor(LIGHTRED);
                                printf("Wrong Choice! \tTry Again\n");
                                getch();
                                clrscr();
        }
    }

    return 0;
}

