/*Project 1 - ATM SIMULATION in C using linked list
by Andrew R. Oloroso and Armand Angelo C. Barrios*/
#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

/*
Mga Problema/Kulang:
1. design sa update nalang
    -birthday
    -contact number
    -pin
*/

typedef struct details{
    int accountNumber;
    char accountName[31];
    int balance;
    char pinCode[7];
    int month,day,year;
    char contactNumber[12];
}REC;
typedef struct node{
    REC atm;
    struct node* next;
}LIST;LIST *L;

//declaration of functions
void makenull();
void retrieve();
int insertcard();
int uniqueAcc(int x);
int pin(REC *x, int a, int y, int z);
int checkPin(char *n[7],int a,int b);
void addNewATMaccount(REC x);
void updateAccount(REC *x);
void getBirthDay(REC *x);
void getContact(REC *x);
void balance(REC *x);
void withdraw(REC *x);
void deposit(REC *x);
void fundTransfer(REC *x, int a);
void utility(REC *x);
void encrypt();
void decrypt();
int transactionMenu();
int otherTransaction();
void save();
void saveFD();

//design functions
void gotoxy(int x,int y);
void printToxy(int x, int y, char *str);
void box(int a,int x, int y, int len, char *str);
void setFontStyle(int FontSize);
void delay(int ms);
void titleScreen();

//animation functions
void loading();
int scanScreen(int a);
void cardAnimate();

//global variables
int balanceFD;
int accNumFD,count;
char nameFD[31];
char pinCodeFD[7];

int main(){
    int accTransfer,index=2;
    REC bdo;
    srand(time(NULL));
    makenull();
    setFontStyle(18);
    switch(insertcard()){
        case 1: bdo.contactNumber[0]='0'; bdo.contactNumber[1]='9';
                do{
                    bdo.accountNumber = rand() % 999999 + 10000;
                    accNumFD = bdo.accountNumber;
                }while(uniqueAcc(bdo.accountNumber)==1);

                system("cls");
                box(3,34,3,100,""); printToxy(40,5,"R E G I S T R A T I O N    M O D U L E");
                box(2,34,7,100,""); printToxy(35,8,"Account Name: ");
                box(2,34,9,58,""); gotoxy(35,10);printf("Account Number: %d",bdo.accountNumber);
                box(2,34,11,100,""); printToxy(35,12,"Contact Number: 09");
                box(2,59,9,100,""); printToxy(61,10,"Birth date:  /  /");
                box(2,34,13,100,""); printToxy(35,14,"Initial Deposit (Min. 5,000): Php ");
                box(3,34,15,100,""); printToxy(35,16,"PIN Code: ");
                box(4,34,19,100,""); printToxy(45,21,"- - -"); printToxy(45,22,"- - -");

                gotoxy(49,8);scanf(" %[^\n]s",bdo.accountName);
                getBirthDay(&bdo); gotoxy(61,10); printf("Birth date: %d / %d / %d",bdo.month,bdo.day,bdo.year);
                gotoxy(53,12); getContact(&bdo); gotoxy(35,12); printf("Contact Number: %s",bdo.contactNumber);
                do{
                    printToxy(69,14,"               ");
                    printToxy(45,21,"- - -                           ");
                    printToxy(45,22,"- - -                           ");
                    printToxy(35,14,"Initial Deposit (Min. 5,000): Php ");
                    gotoxy(69,14);scanf("%d", &bdo.balance);
                    if(bdo.balance<5000){
                        printToxy(45,21,"MIN. DEPOSIT IS PHP 5,000 ! !");
                        gotoxy(45,22);system("pause");
                    }
                }while(bdo.balance<5000);

                pin(&bdo,1,45,21); gotoxy(35,16); printf("PIN Code: %s",bdo.pinCode);
                printToxy(45,21,"R E G I S T R A T I O N    S U C C E S S F U L"); gotoxy(45,22);system("pause");
                addNewATMaccount(bdo);
                system("cls");titleScreen();
                break;
        case 2: strcpy(bdo.accountName,nameFD);
                bdo.balance=balanceFD;
                strcpy(bdo.pinCode,pinCodeFD);
                bdo.accountNumber=accNumFD;
                system("cls");
                box(3,34,10,100," "); printToxy(35,12,"PIN Code: ");
                box(4,34,13,100," ");
                gotoxy(45,12);
                if(pin(&bdo,2,35,15)==2){
                    system("cls");
                    titleScreen();
                    break;
                }else{
                    exit(0);
                }
    }

    while(1){
        c: count=0;
        system ("cls");
        printToxy(47,2,"* T R A N S A C T I O N    M O D U L E *");
        switch(transactionMenu()){
            case 1: balance(&bdo); break;
            case 2: withdraw(&bdo);break;
            case 3: deposit(&bdo); break;
            case 4: do{
                        system("cls");
                        box(3,34,7,100," "); printToxy(35,9,"- - -");
                        box(3,34,11,100," "); printToxy(35,13,"- - -");
                        box(3,34,3,100," "); printToxy(35,5,"Enter the Account No. you want to transfer: ");scanf("%d",&accTransfer);
                        if(accTransfer<10000 || accTransfer>99999){
                            printToxy(35,9,"Invalid Account Number.");
                            gotoxy(35,13);system("pause");
                            count++;
                            if(count==4){
                                printToxy(35,9,"Too many failed attemps. Please try later.");
                                gotoxy(35,13);system("pause");
                                goto c;
                            }
                        }
                    }while(accTransfer<10000 || accTransfer>99999);
                    fundTransfer(&bdo,accTransfer);
                    break;
            case 5: system("cls");
                    switch(otherTransaction()){
                        case 1: system("cls");
                                box(3,34,10,100," "); printToxy(35,12,"PIN Code: ");
                                box(4,34,13,100," ");
                                gotoxy(45,12);
                                if(pin(&bdo,2,35,15)!=1){
                                    updateAccount(&bdo);
                                }break;
                        case 2: utility(&bdo); break;
                        case 3: break;
                        default: box(4,34,23,100," "); printToxy(45,25,"Invalid input. Try again.");gotoxy(45,26); system("pause");break;
                    }break;
            case 6: encrypt();save();saveFD();exit(0);break;
            default: box(4,34,35,100," "); printToxy(45,37,"Invalid input. Try again."); gotoxy(45,38); system("pause");break;
        }
    }
}


void makenull(){
    L=NULL;
}

void retrieve(){
    int i;
    FILE *fp;
    REC bdo;
    fp=fopen("D:\\Database.txt","r+");
    if(fp!=NULL){
        while(!feof(fp)){
            fscanf(fp," %[^\t]s", bdo.accountName);
            fscanf(fp,"%d",&bdo.accountNumber);
            fscanf(fp," %[^\t]s", bdo.pinCode);
            fscanf(fp,"%d", &bdo.balance);
            fscanf(fp," %[^\t]s", bdo.contactNumber);
            fscanf(fp,"%d %d %d\n", &bdo.month, &bdo.day, &bdo.year);
            addNewATMaccount(bdo);
        }fclose(fp);
    }

    fp=fopen("F:\\ATM.txt","r+");
    if(fp!=NULL){
        fscanf(fp," %[^\t]s", nameFD);
        fscanf(fp,"%d", &balanceFD);
        fscanf(fp," %[^\t]s", pinCodeFD);
        fscanf(fp,"%d\n", &accNumFD);
        fclose(fp);
    }
}

int insertcard(){
    LIST *p; p=L;
    FILE *fp;
    do{
        fp=fopen("F:\\Check.txt","w"); //in flashdrive
        loading();
    }while(fp==NULL);
    fclose(fp);
    fp=fopen("F:\\ATM.txt","r");
    if(fp==NULL){
        retrieve();
        decrypt();
        scanScreen(1);
        gotoxy(40,11);system("pause");return 1;
    }else{
        retrieve();
        decrypt();
        scanScreen(2);
        gotoxy(40,11);system("pause");
        system("cls"); return 2;
    }
    fclose(fp);
}

int uniqueAcc(int x){
    LIST *p, *q;
    p=q=L;
    while(p!=NULL && x!=p->atm.accountNumber){
            q=p;
            p=p->next;
    }
    if(p==NULL)
        return 2;
    else
        return 1;
}

int pin(REC *x, int a, int y, int z){
    int index=0;
    char ch;
    printToxy(y,z,"- - -                         ");
    printToxy(y,z+1,"- - -                       ");
    if(a==1){
        b:
        printToxy(45,17,"Enter 4 - 6 digits.");
        printToxy(45,16,"       "); gotoxy(45,16);
        while((ch=getch())!=13 && index<5){
            if (index<0){
                index=0;
            }
            if(ch==8){
                putch('\b'); putch(' ');
                putch('\b'); index--;
                continue;
            }
            if(isdigit(ch)){
                x->pinCode[index++]=ch;
                putchar('*');
            }
        }
        if (index==5){
            x->pinCode[index++]=ch;
            putchar('*');
        }x->pinCode[index]='\0';
        if(strlen(x->pinCode)<4){
            index=0;
            printToxy(y,z,"I N V A L I D   P I N");
            gotoxy(y,z+1);system("pause");
            printToxy(y,z,"- - -                         ");
            printToxy(y,z+1,"- - -                           ");
            goto b;
        }strcpy(pinCodeFD,x->pinCode);
    }else if(a==2){
        count=0;
        do{
            c:
            count++;
            if(count==5)
                break;
            index=0;
            printToxy(45,12,"       "); gotoxy(45,12);
            while((ch=getch())!=13 && index<5){
                if (index<0){
                    index=0;
                }
                if(ch==8){
                    putch('\b'); putch(' ');
                    putch('\b'); index--;
                    continue;
                }
                if(isdigit(ch)){
                 x->pinCode[index++]=ch;
                 putchar('*');
                }
            }
            if (index==5){
                x->pinCode[index++]=ch;
                putchar('*');
            }x->pinCode[index]='\0';
            if(strlen(x->pinCode)<4){
                printToxy(y,z,"I N V A L I D   P I N");
                gotoxy(y,z+1);system("pause");
                printToxy(y,z,"- - -                         ");
                printToxy(y,z+1,"- - -                           ");
                goto c;
            }
        }while(checkPin(&x->pinCode,y,z)==1);
    }
    if(count==5){
        printToxy(y,z,"Too many failed attempts. Please try later.");
        gotoxy(y,z+1);system("pause");
        return 1;
    }else{
        return 2;
    }
}


int checkPin(char *n[7],int a,int b){
    LIST *p, *q;
    p=q=L;
    while(p!=NULL && strcmp (n, pinCodeFD)!=0){
        q=p;
        p=p->next;
    }
    if (p==NULL){
        printToxy(a,b,"Wrong PIN Code");
        gotoxy(a,b+1);system("pause");
        printToxy(a,b,"- - -                         ");
        printToxy(a,b+1,"- - -                           ");
        return 1;
    }else{
        printToxy(a,b,"PIN verified.");
        gotoxy(a,b+1);system("pause");
        printToxy(a,b,"- - -                         ");
        printToxy(a,b+1,"- - -                           ");
        return 2;
    }
}

void addNewATMaccount(REC x){
    LIST *p,*q,*temp;
    q=p=L;
    temp = (LIST*) malloc(sizeof(LIST));
    temp->atm = x;
    while (p!=NULL){
        q=p;
        p=p->next;
    }
    if (p==L){
        L=temp;
    }else{
        q->next = temp;
    }temp->next = p;
}

void balance(REC *x){
    LIST *p, *q;
    p=q=L;
    while(p!=NULL && x->accountNumber!=p->atm.accountNumber){
        q=p;
        p=p->next;
    }
    if (p==NULL){
        system("cls");
        box(3,34,3,100," "); printToxy(50,5,"B A L A N C E   I N Q U I R Y");
        box(3,34,7,100," "); printToxy(55,9,"Account not found.");
        box(3,34,11,100," "); gotoxy(50,13); system("pause");
    }else{
        system("cls");
        box(3,34,3,100," "); printToxy(50,5,"B A L A N C E   I N Q U I R Y");
        box(3,34,7,52," "); printToxy(35,9,"Account Name:");
        box(3,54,7,100," "); gotoxy(56,9);printf("%s",p->atm.accountName);
        box(3,34,11,52," "); printToxy(35,13,"Current Balance:");
        box(3,54,11,100," "); gotoxy(56,13);printf("Php %d",p->atm.balance);
        box(3,34,15,100,""); printToxy(50,17," "); system("pause"); system("cls");
    }
}

void withdraw(REC *x){
    int withdraww;
    LIST *p, *q;
    p=q=L;
    while(p!=NULL && x->accountNumber!=p->atm.accountNumber){
        q=p;
        p=p->next;
    }
    if (p==NULL){
        system("cls");
        box(3,34,3,100," "); printToxy(50,5,"W I T H D R A W   M O N E Y");
        box(3,34,7,100," "); printToxy(55,9,"Account not found.");
        box(3,34,11,100," "); gotoxy(50,13); system("pause");
    }else{
        if(p->atm.balance!=0){
            do{
                system("cls");
                box(3,34,3,100," "); printToxy(50,5,"W I T H D R A W   M O N E Y");
                box(3,34,7,79," "); printToxy(36,9,"Please input amount to withdraw:");
                box(3,81,7,100," ");
                box(3,34,11,100," "); printToxy(45,13,"- - -");
                box(3,34,15,100," "); printToxy(45,17,"- - -");
                box(3,34,19,100," "); printToxy(45,21,"- - -");
                printToxy(83,9,"Php ");scanf("%d",&withdraww);
                if(withdraww>(p->atm.balance)){
                    printToxy(50,13,"Insufficient Balance."); gotoxy(45,17); system("pause");
                }else if(withdraww<=0){
                    printToxy(50,13,"Invalid amount.");gotoxy(45,17); system("pause");
                }else if(p->atm.balance==0){
                    printToxy(50,13,"Insufficient Balance.");gotoxy(45,17); system("pause");
                }
            }while(withdraww>(p->atm.balance) || withdraww<=0 || p->atm.balance==0);
            p->atm.balance-=withdraww;
            printToxy(45,13,"Withdraw successful.");
            gotoxy(45,17);printf("Your new balance: Php %d", p->atm.balance);
            gotoxy(45,21);system("pause");
        }else{
            system("cls");
            box(3,34,3,100," "); printToxy(50,5,"W I T H D R A W   M O N E Y");
            box(3,34,7,100," "); printToxy(55,9,"You have no balance. Please deposit first.");
            box(3,34,11,100," "); gotoxy(50,13); system("pause");
        }
    }
}

void deposit(REC *x){
    int depositt;
    LIST *p, *q;
    p=q=L;
    while(p!=NULL && x->accountNumber!=p->atm.accountNumber){
        q=p;
        p=p->next;
    }
    if (p==NULL){
        system("cls");
        box(3,34,3,100," "); printToxy(50,5,"D E P O S I T");
        box(3,34,7,100," "); printToxy(55,9,"Account not found.");
        box(3,34,11,100," "); gotoxy(50,13); system("pause");
    }else{
        system("cls");
        box(3,34,3,100," "); printToxy(50,5,"D E P O S I T");
        box(3,34,7,100," ");
        box(3,34,11,100," "); printToxy(35,13,"- - -");
        box(3,34,15,100," "); printToxy(35,17,"- - -");
        box(3,34,19,100," "); printToxy(35,21,"- - -");
        do{
            printToxy(35,9,"Please input amount to deposit: Php "); scanf("%d",&depositt);
            if(depositt<=0){
                printToxy(35,13,"Minimum deposit amount is Php 1.");
                gotoxy(35,17);system("pause");
                printToxy(71,9,"                             |     ");
                printToxy(35,13,"- - -                                           ");
                printToxy(35,17,"- - -                                           ");
            }
            if(depositt>=999999999){
                printToxy(35,13,"Hold up. Wait a minute. We don't do that here.");
                printToxy(35,17,"Please go to your nearest bank.");
                gotoxy(35,21);system("pause");
                printToxy(71,9,"                             |     ");
                printToxy(35,13,"- - -                                                            |     ");
                printToxy(35,17,"- - -                                                            |     ");
                printToxy(35,21,"- - -                                     ");
            }
        }while(depositt<=0 || depositt>=999999999);
        p->atm.balance+=depositt;
        printToxy(35,13,"Deposit successful.");
        gotoxy(35,17); printf("Your new balance: Php %d",p->atm.balance);
        gotoxy(35,21); system("pause");
    }
}

void fundTransfer(REC *x,int a){
    int transfer;
    FILE *fp;
    LIST *p, *q;
    p=q=L;
    while(p!=NULL && a!=p->atm.accountNumber){
        q=p;
        p=p->next;
    }
    if (p==NULL){
        system("cls");
        box(3,34,3,100," "); printToxy(50,5,"F U N D   T R A N S F E R");
        box(3,34,7,100," "); printToxy(55,9,"Account not found.");
        box(3,34,11,100," "); gotoxy(50,13); system("pause");
    }else if(x->balance!=0){
        count=0;
        system("cls");
        box(3,34,3,100," "); printToxy(50,5,"F U N D   T R A N S F E R");
        box(3,34,7,100," "); printToxy(55,9,"Account found!");
        box(3,34,11,59," "); printToxy(35,13,"Transfering money to:");
        box(3,61,11,100," "); gotoxy(62,13); printf("%s",p->atm.accountName);
        box(3,34,15,59," "); printToxy(35,17,"Your balance is:");
        box(3,61,15,100," "); gotoxy(62,17); printf("Php %d",x->balance);
        box(3,34,19,100," "); printToxy(35,21,"- - -");
        box(3,34,23,100," "); printToxy(35,25,"- - -");
        box(3,34,27,100," "); printToxy(35,29,"- - -");
        box(3,34,31,100," "); printToxy(35,33,"- - -");
        do{
            count++;
            if(count==5){
                printToxy(35,25,"Too many failed attempts. Please try later.");goto a;
            }
            gotoxy(35,21); printf("Input amount to transfer: Php ");scanf("%d",&transfer);
            if(transfer>x->balance){
                 printToxy(35,25,"Insufficient balance."); gotoxy(35,29); system("pause");
            }else if(transfer<=0){
                printToxy(35,25,"Minimum transfer amount is Php 1."); gotoxy(35,29); system("pause");
            }
        }while(transfer>x->balance || transfer<=0);
        p->atm.balance+=transfer;
        gotoxy(35,25); printf("Total Amount of Php %d was successfully transferred to %s.",transfer,p->atm.accountName);

        //back to the previous node to store the balance to the current user
        p=q=L;
        while(p!=NULL && x->accountNumber!=p->atm.accountNumber){
            q=p;
            p=p->next;
        }
        p->atm.balance-=transfer;
        x->balance-=transfer;
        gotoxy(35,29); printf("Your Total Balance is: Php %d",p->atm.balance);
        a: gotoxy(35,33); system("pause");
    }else{
        system("cls");
        box(3,34,3,100," "); printToxy(50,5,"F U N D   T R A N S F E R");
        box(3,34,7,100," "); printToxy(55,9,"Insufficient balance. Please deposit first.");
        box(3,34,11,100," "); gotoxy(50,13); system("pause");
    }
}

void updateAccount(REC *x){
    int y,index=2;
    char ch;
    REC bdo;
    LIST *p, *q;
    q=p=L;
    while(p!=NULL && x->accountNumber!=p->atm.accountNumber){
        q=p;
        p=p->next;
    }
    if(p==NULL){
        system("cls");
        box(3,34,3,100," "); printToxy(50,5,"U P D A T E   A C C O U N T");
        box(3,34,7,100," "); printToxy(55,9,"Account not found.");
        box(3,34,11,100," "); gotoxy(50,13); system("pause");
    }else{
        while(y!=5){
            system("cls");
            box(3,34,3,100,""); printToxy(52,5,"U P D A T E   A C C O U N T");
            box(2,34,9,58,""); gotoxy(35,10);printf("Account Number: %d",p->atm.accountNumber);
            box(2,34,7,100,""); gotoxy(35,8);printf("Account Name: %s",p->atm.accountName);
            box(2,34,11,100,""); gotoxy(35,12);printf("Contact Number: %s",p->atm.contactNumber);
            box(2,59,9,100,""); gotoxy(61,10);printf("Birth date: %d / %d / %d",p->atm.month,p->atm.day,p->atm.year);
            box(2,34,13,100,""); gotoxy(35,14);printf("PIN Code: %s",p->atm.pinCode);
            box(2,34,16,100,""); printToxy(35,17,"U P D A T E :");
            box(4,34,18,100,"");
                printToxy(35,20,"[1] Account Name");
                printToxy(35,21,"[2] Birthday");
                printToxy(55,20,"[3] Contact Number");
                printToxy(55,21,"[4] Change PIN Code");
                printToxy(80,20,"[5] Back");
            box(3,34,23,100,""); printToxy(35,25,"Enter a Number: ");scanf("%d", &y);
            switch(y){
                case 1: system("cls");
                        box(3,34,3,100,"");printToxy(35,5,"Input new Account Name: ");scanf(" %[^\n]s",bdo.accountName);
                        strcpy(p->atm.accountName,bdo.accountName); break;
                case 2: system("cls");
                        box(3,34,3,100,"");getBirthDay(&bdo);
                        p->atm.month=bdo.month; p->atm.day=bdo.day; p->atm.year=bdo.year;
                        break;
                case 3: bdo.contactNumber[0]='0'; bdo.contactNumber[1]='9';
                        printf("\nInput new Contact Number: 09");
                        b:
                        while((ch=getch())!=13 && index<10){
                            if (index<0){
                                index=0;
                            }
                            if(ch==8){
                                putch('\b'); putch(' ');
                                putch('\b'); index--;
                                continue;
                            }
                            if(isdigit(ch)){
                                bdo.contactNumber[index++]=ch;
                                putch('*');
                            }
                        }
                        if (index==10){
                            bdo.contactNumber[index++]=ch;
                            putchar('*');
                        }bdo.contactNumber[index]='\0';
                        if(strlen(bdo.contactNumber)<11)
                            goto b;
                        strcpy(p->atm.contactNumber,bdo.contactNumber);
                        break;
                case 4: printf("\nPlease Enter CURRENT Pin Code\n");system("pause");
                        if(pin(&bdo,2,1,1)!=1){
                            printf("\nPlease Enter NEW Pin Code");pin(&bdo,1,1,1);
                            strcpy(p->atm.pinCode,bdo.pinCode);
                        }else{
                            printf("\nToo many failed attemps. Please try later.");
                        }break;
                case 5: box(4,34,27,100,""); gotoxy(35,29); printf("%s's account is successfully updated.", p->atm.accountName);
                        gotoxy(35,30); system("pause");break;
                default: box(4,34,27,100,""); gotoxy(35,29); printf("Select 1-6 only"); gotoxy(35,30); system("pause");break;
            }
        }
    }
}

void getBirthDay(REC *x){
    a:
    printToxy(84,10,"                |     ");
    printToxy(61,10,"Birth month(01-12):");
    gotoxy(84,10);scanf("%d",&x->month);
    if(x->month<=0 || x->month>12){
        printToxy(45,21,"I N V A L I D   M O N T H !!");
        gotoxy(45,22);system("pause");
        printToxy(45,21,"- - -                         ");
        printToxy(45,22,"- - -                           ");
        goto a;
    }
    b:
    printToxy(86,10," /            |     ");
    printToxy(61,10,"Birth  day (01-31):");
    gotoxy(89,10);scanf("%d",&x->day);
    if(x->day<=0 || x->day>31){
        printToxy(45,21,"I N V A L I D   D A Y ! !");
        gotoxy(45,22);system("pause");
        printToxy(45,21,"- - -                         ");
        printToxy(45,22,"- - -                           ");
        goto b;
    }
    c:
    printToxy(91,10," /       |     ");
    printToxy(61,10,"Birth year(1900-2022):");
    gotoxy(94,10);scanf("%d",&x->year);
    if(x->year<=1900 || x->year>2022){
        printToxy(45,21,"I N V A L I D   Y E A R ! !");
        gotoxy(45,22);system("pause");
        printToxy(45,21,"- - -                         ");
        printToxy(45,22,"- - -                           ");
        goto c;
    }
    printToxy(61,10,"                                     ");
}
void getContact(REC *x){
    int index=2;
    char ch;
    do{
        while((ch=getch())!=13 && index<10){
            if (index<0){
                index=0;
            }
            if(ch==8){
                putch('\b'); putch(' ');
                putch('\b'); index--;
                continue;
            }
            if(isdigit(ch)){
                x->contactNumber[index++]=ch;
                putch('*');
            }
        }
        if (index==10){
            x->contactNumber[index++]=ch;
            putchar('*');
        }x->contactNumber[index]='\0';
    }while(strlen(x->contactNumber)!=11);
}

void utility(REC *x){
    int Meralco,Maynilad,userNum;
    LIST *p, *q;
    p=q=L;
    while(p!=NULL && x->accountNumber!=p->atm.accountNumber){
        q=p;
        p=p->next;
    }
    if (p==NULL){
        system("cls");
        box(3,34,3,100," "); printToxy(50,5,"P A Y   B I L L S");
        box(3,34,7,100," "); printToxy(55,9,"Account not found.");
        box(3,34,11,100," "); gotoxy(50,13); system("pause");
    }else{
        system("cls");
        box(3,34,10,100," "); printToxy(50,12,"P A Y   B I L L S");
        box(4,34,14,100," ");
            printToxy(50,16,"[1] Meralco Bill");
            printToxy(50,17,"[2] Maynilad Bill");
            printToxy(75,16,"[3] Back");
        box(3,34,19,100," "); printToxy(35,21,"Enter a Number: ");
        gotoxy(51,21); scanf("%d",&userNum);
        switch(userNum){
            case 1: system("cls");
                    Meralco=rand()%2000 + 1;
                    box(3,34,10,100," "); printToxy(35,12,"M E R A L C O   B I L L");
                    box(3,34,14,100," ");gotoxy(35,16); printf("Meralco Bill: Php %d", Meralco);
                    box(3,34,18,100," ");gotoxy(35,20); printf("Account Balance: Php %d", p->atm.balance);
                    box(4,34,22,100," ");
                        printToxy(35,24,"[1] Pay Meralco Bill");
                        printToxy(35,25,"[2] Back");
                    box(3,34,27,100," "); printToxy(35,29,"Enter a Number: ");
                    gotoxy(51,29);scanf("%d",&userNum);
                    switch(userNum){
                        case 1: box(4,34,31,100," ");
                                if(p->atm.balance>=Meralco){
                                    p->atm.balance-=Meralco;
                                    printToxy(35,33,"Payment successful.");
                                }else{
                                    printToxy(35,33,"Insufficient Balance.");
                                }gotoxy(35,34); system("pause");
                                break;
                        case 2: break;
                        default: box(4,34,31,100," "); printToxy(35,33,"Invalid input.");gotoxy(35,34); system("pause");
                                 break;
                    }break;
            case 2: system("cls");
                    Maynilad=rand()%800 + 1;
                    box(3,34,10,100," "); printToxy(35,12,"M A Y N I L A D   B I L L");
                    box(3,34,14,100," ");gotoxy(35,16); printf("Maynilad Bill: Php %d", Maynilad);
                    box(3,34,18,100," ");gotoxy(35,20); printf("Account Balance: Php %d", p->atm.balance);
                    box(4,34,22,100," ");
                        printToxy(35,24,"[1] Pay Maynilad Bill");
                        printToxy(35,25,"[2] Back");
                    box(3,34,27,100," "); printToxy(35,29,"Enter a Number: ");
                    gotoxy(51,29);scanf("%d",&userNum);
                    switch(userNum){
                        case 1: box(4,34,31,100," ");
                                if(p->atm.balance>=Maynilad){
                                    p->atm.balance-=Maynilad;
                                    printToxy(35,33,"Payment successful.");
                                }else{
                                    printToxy(35,33,"Insufficient Balance.");
                                }gotoxy(35,34); system("pause");
                                break;
                        case 2: break;
                        default: box(4,34,31,100," "); printToxy(35,33,"Invalid input."); gotoxy(35,34); system("pause");
                                 break;
                    }break;
            case 3: break;
            default: box(4,34,23,100," "); printToxy(35,25,"Invalid input.");gotoxy(35,26); system("pause");
        }
    }
}

void encrypt(){
    int i=0;
    LIST *p, *q;
    q=p=L;
    while(p!=NULL && p->atm.accountNumber!=accNumFD){
        q=p;
        p=p->next;
    }
    if(p!=NULL){
        while(p->atm.pinCode[i]!='\0'){
            p->atm.pinCode[i]=p->atm.pinCode[i] + 70;
            i++;
        }
    }
}
void decrypt(){
    int i=0;
    LIST *p, *q;
    q=p=L;
    while(p!=NULL && p->atm.accountNumber!=accNumFD){
        q=p;
        p=p->next;
    }
    if(p!=NULL){
        while(p->atm.pinCode[i]!='\0'){
            p->atm.pinCode[i]=p->atm.pinCode[i] - 70;
            pinCodeFD[i]=pinCodeFD[i]-70;
            i++;
        }
    }
}

int transactionMenu(){
    int UserNum;
    box(3,34,3,100," "); printToxy(50,5,"T R A N S A C T I O N      M E N U");
    box(3,34,7,40," [1]"); box(3,42,7,100," "); printToxy(50,9,"BALANCE INQUIRY\n");
    box(3,34,11,40," [2]"); box(3,42,11,100," "); printToxy(50,13,"WITHDRAW");
    box(3,34,15,40," [3]"); box(3,42,15,100," "); printToxy(50,17,"DEPOSIT");
    box(3,34,19,40," [4]"); box(3,42,19,100," "); printToxy(50,21,"FUND TRANSFER");
    box(3,34,23,40," [5]"); box(3,42,23,100," "); printToxy(50,25,"OTHER TRANSACTIONS");
    box(3,34,27,40," [6]"); box(3,42,27,100," "); printToxy(50,29,"EXIT");
    box(3,34,31,100," "); printToxy(50,33,"Enter your choice 1-6: ");scanf("%d", &UserNum);
    return UserNum;
}
int otherTransaction(){
    int UserNum;
    box(3,34,3,100," "); printToxy(47,5,"- O T H E R   T R A N S A C T I O N S -");
    box(3,34,7,40," [1]"); box(3,42,7,100," "); printToxy(50,9,"ACCOUNT SETTINGS");
    box(3,34,11,40," [2]"); box(3,42,11,100," "); printToxy(50,13,"PAY BILLS");
    box(3,34,15,40," [3]"); box(3,42,15,100," "); printToxy(50,17,"BACK");
    box(3,34,19,100," ");printToxy(50,21,"Enter your choice 1-3: ");scanf("%d", &UserNum);
    return UserNum;
}

void save(){
    int i=0;
    FILE *fp;
    LIST *p; p=L;
    fp = fopen("D:\\Database.txt","w+");
    if (fp==NULL){
        printf("Error 404. File not found.\n");
        system("pause");
    }
    else {
        while(p!=NULL){
            fprintf(fp,"%s\t%d\t%s\t%d\t%s\t%d %d %d\n",
            p->atm.accountName,p->atm.accountNumber,p->atm.pinCode,p->atm.balance,p->atm.contactNumber,p->atm.month,p->atm.day,p->atm.year);
            p=p->next;
        }fclose(fp);
    }
}
void saveFD(){
    int i=0;
    FILE *fp;
    LIST *p, *q;
    q=p=L;
    while (p!=NULL && accNumFD!=p->atm.accountNumber){
        q=p;
        p=p->next;
    }
    fp = fopen("F:\\ATM.txt","w+");
    if (fp==NULL){
        printf("Error 404. File not found.\n");
        system("pause");
    }
    else {
        fprintf(fp,"%s\t%d\t%s\t%d\n",p->atm.accountName,p->atm.balance,p->atm.pinCode,p->atm.accountNumber);
        fclose(fp);
    }
}

void setFontStyle(int FontSize){
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = FontSize;                  // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy(cfi.FaceName, L"Consolas"); // font style
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void gotoxy(int x,int y){
    COORD coord = {0,0};
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void printToxy(int x, int y, char *str){
    gotoxy(x,y);
    printf("%s",str);
}

void box(int a, int x, int y, int len, char *str){
    int i;
    if(a==2){ //2 lines
        for(i = x; i < len; i++){
            printToxy(i,y,"_");
            printToxy(i,y + 2,"_");
        }
        for(i = y + 1; i < y + 3; i++){
            printToxy(x - 1,i,"|");
            printToxy(len,i,"|");
        }
        printToxy(x + 1, y + 1,str);
    }else if(a==3){ //3 lines
        for(i = x; i < len; i++){
            printToxy(i,y,"_");
            printToxy(i,y + 3,"_");
        }
        for(i = y + 1; i < y + 4; i++){
            printToxy(x - 1,i,"|");
            printToxy(len,i,"|");
        }
        printToxy(x + 1, y + 2,str);
    }else if(a==4){ //4 lines
        for(i = x; i < len; i++){
            printToxy(i,y,"_");
            printToxy(i,y + 4,"_");
        }
        for(i = y + 1; i < y + 5; i++){
            printToxy(x - 1,i,"|");
            printToxy(len,i,"|");
        }
        printToxy(x + 1, y + 3,str);
    }
}

void delay(int ms){
    clock_t timeDelay = ms + clock();
    while(timeDelay > clock());
}

void loading(){
char load[] = {'.','.','.','o','.','.','0','o','.','0','0','o','0','0','0','o','0','0','.','o','0','.','.','o','.','.','.','\0'};
    int x=0,y=1,z=2,loop=0;
    while(loop != 9){
        if(loop > 0){
            x += 3;
            y += 3;
            z += 3;
        }
        delay(70);
        system("cls");
        gotoxy(40,4);printf("P L E A S E   I N S E R T   Y O U R   C A R D");
        gotoxy(56,6);printf("%c   %c   %c",load[x],load[y],load[z]);
        gotoxy(58,20);
        cardAnimate();
        loop++;
    }
}

int scanScreen(int a){
    system("cls");
    int i;
    if(a==1){
        gotoxy(40,4);printf("S C A N N I N G   A T M   C A R D");
        for(i=0;i<18;i++){
            delay(100);
            gotoxy(40+i,6);printf("||||||||||||||||");
        }
       gotoxy(39,10);printf("N O T   Y E T   R E G I S T E R E D");
    }else{
        gotoxy(40,4);printf("S C A N N I N G   A T M   C A R D");
        for(i=0;i<18;i++){
            delay(100);
            gotoxy(40+i,6);printf("||||||||||||||||");
        }
        gotoxy(45,10);printf("W E L C O M E %s !",nameFD);
    }
}

void titleScreen(){
    char title [20][56]={
        {"                                                        "},
        {"      ##### ##            ##### ##             # ###    "},
        {"   ######  /##         /#####  /##           /  /###    "},
        {"  /#   /  / ##       //    /  / ###         /  /  ###   "},
        {" /    /  /  ##      /     /  /   ###       /  ##   ###  "},
        {"     /  /   /            /  /     ###     /  ###    ### "},
        {"    ## ##  /            ## ##      ##    ##   ##     ## "},
        {"    ## ## /             ## ##      ##    ##   ##     ## "},
        {"    ## ##/              ## ##      ##    ##   ##     ## "},
        {"    ## ## ###           ## ##      ##    ##   ##     ## "},
        {"    ## ##   ###         ## ##      ##    ##   ##     ## "},
        {"    #  ##     ##        #  ##      ##     ##  ##     ## "},
        {"       /      ##           /       /       ## #      /  "},
        {"   /##/     ###       /###/       /         ###     /   "},
        {"  /  ########        /   ########/           ######/    "},
        {" /     ####         /       ####               ###      "},
        {" #                  #                                   "},
        {"  ##                 ##                                 "},
        {"                                                        "},
        {"                                                        "}
    };

    for (int x=0; x<20; x++){ // for looop for printing the title screen
        system("COLOR 0B");
        printf("\t\t\t");
        for (int y=0; y<56; y++){
                printf("%c", title[x][y]);
            }
        printf("\n");
        system("COLOR 0A");
    }
    printToxy(42,19,"~ Banco De Oloroso ~");
    printToxy(30,20,"- It's not your money it's OUR money t(^v^t)-");
    gotoxy(38,22);system("pause");system("cls");system("COLOR 0F");
}

void cardAnimate(){
    int x=50,y=10;
    printToxy(x,y,    "|_ _ _ _ _ |                ");
    printToxy(x,y + 1,"                            ");
    printToxy(x,y + 2,"   _ _ _ _          /\\     ");
    printToxy(x,y + 3,"  |+_+_+_+|        /  \\    ");
    printToxy(x,y + 4,"  |       \\       /    \\   ");
    printToxy(x,y + 5,"  |        |     /_    _\\  ");
    printToxy(x,y + 6,"  |        |       |  |     ");
    printToxy(x,y + 7,"  |        |       |  |     ");
    printToxy(x,y + 8,"  |________|       |__|     ");
        delay(300);
    printToxy(x,y,    "|_ _ _ _ _ |                ");
    printToxy(x,y + 1,"  |+_+_+_+|         /\\     ");
    printToxy(x,y + 2,"  |       \\        /  \\    ");
    printToxy(x,y + 3,"  |        |      /    \\   ");
    printToxy(x,y + 4,"  |        |     /_    _\\  ");
    printToxy(x,y + 5,"  |        |       |  |     ");
    printToxy(x,y + 6,"  |________|       |  |     ");
    printToxy(x,y + 7,"                   |__|     ");
    printToxy(x,y + 8,"                            ");
        delay(300);
}
