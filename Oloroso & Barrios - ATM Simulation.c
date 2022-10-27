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
1. design HAHAHA

error sa birthday
error sa deposit
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
int pin(REC *x, int a);
int checkPin(char *n[7]);
void addNewATMaccount(REC x);
void updateAccount(REC *x);
void birthDayy(REC *bday);
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
void setFontStyle(int FontSize);
void delay(int ms);
void titleScreen();
void createBlock(int x, int y, int len, char *str);
void box();
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
    char ch;
    REC bdo;
    srand(time(NULL));
    makenull();
    setFontStyle(18);
    switch(insertcard()){
        case 1: system("cls");
                box();
                bdo.contactNumber[0]='0'; bdo.contactNumber[1]='9';
                do{
                    bdo.accountNumber = rand() % 999999 + 10000;
                    accNumFD = bdo.accountNumber;
                }while(uniqueAcc(bdo.accountNumber)==1);
                printToxy(40,4,"R E G I S T R A T I O N    M O D U L E");
                gotoxy(30,8);printf("Account Number: %d",bdo.accountNumber);
                printToxy(30,6,"Account Name: ");scanf(" %[^\n]s",bdo.accountName);
                birthDayy(&bdo);system("cls");
                box();
                printToxy(40,4,"R E G I S T R A T I O N    M O D U L E");
                gotoxy(30,8);printf("Account Number: %d",bdo.accountNumber);
                gotoxy(30,6);printf("Account Name: %s",bdo.accountName);
                gotoxy(54,8);printf("Birth date: %d / %d / %d",bdo.month,bdo.day,bdo.year);
                printToxy(30,10,"Contact Number: 09");
                a:
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
                if(strlen(bdo.contactNumber)!=11)
                    goto a;
                gotoxy(30,10); printf("Contact Number: %s",bdo.contactNumber);
                do{
                    printToxy(45,18,"                            ");
                    printToxy(30,12,"                                                 ");
                    printToxy(45,22,"                               ");
                    printToxy(30,12,"Initial Deposit (Min. 5,000): Php ");scanf("%d", &bdo.balance);
                    if(bdo.balance<5000){
                        printToxy(45,18,"MIN. DEPOSIT IS PHP 5000 ! !");
                        gotoxy(45,22);system("pause");
                    }
                }while(bdo.balance<5000);
                pin(&bdo,1);
                addNewATMaccount(bdo);
                printToxy(36,18,"R E G I S T R A T I O N    S U C C E S S F U L");gotoxy(45,22);system("pause");
                system("cls");titleScreen();
                break;
        case 2: strcpy(bdo.accountName,nameFD);
                bdo.balance=balanceFD;
                strcpy(bdo.pinCode,pinCodeFD);
                bdo.accountNumber=accNumFD;
                if(pin(&bdo,2)==2){
                    system("cls");
                    titleScreen();
                    break;
                }else{
                    printf("\nmain: Too many failed attempts. Please try later.");system("pause");exit(0);
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
                        printf("Enter the Account No. you want to transfer: ");
                        scanf("%d",&accTransfer);
                        if(accTransfer<10000 || accTransfer>99999){
                            printf("\nInvalid Account Number.\n\n");
                            count++;
                            if(count==4){
                                printf("\n\nToo many failed attemps. Please try later.\n");system("pause");
                                goto c;
                            }
                        }
                    }while(accTransfer<10000 || accTransfer>99999);
                    fundTransfer(&bdo,accTransfer);
                    break;
            case 5: system("cls");
                    switch(otherTransaction()){
                        case 1: system("cls");printf("Input Account Pin Code: \n");system("pause");
                                if(pin(&bdo,2)!=1){
                                    updateAccount(&bdo);
                                }break;
                        case 2: system("cls"); printf("PAY BILLS\n\n");
                                utility(&bdo); break;
                        case 3: break;
                        default: printf("\nInvalid input. Try again.\n"); system("pause");break;
                    }break;
            case 6: encrypt();save();saveFD();exit(0);break;
            default: printf("\nInvalid input. Try again.\n"); system("pause");break;
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

int pin(REC *x, int a){
    int index=0;
    char ch;
    if(a==1){
        b:
        printToxy(30,14,"PIN Code: ");
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
            system ("cls");
            printToxy(30,14,"PIN Code: ");
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
            if(strlen(x->pinCode)<4)
                goto c;
        }while(checkPin(&x->pinCode)==1);
    }
    if(count==5){
        printToxy(35,18,"Too many failed attempts. Please try later.");
        gotoxy(45,22);system("pause");
        return 1;
    }else{
        return 2;
    }
}


int checkPin(char *n[7]){
    LIST *p, *q;
    p=q=L;
    while(p!=NULL && strcmp (n, pinCodeFD)!=0){
        q=p;
        p=p->next;
    }
    if (p==NULL){
        printToxy(50,15,"Wrong PIN Code");gotoxy(45,16);system("pause");
        return 1;
    }else{
        printToxy(50,15,"PIN verified.");gotoxy(45,16);system("pause");
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
        createBlock(34,3,100," "); printToxy(50,5,"B A L A N C E   I N Q U I R Y");
        createBlock(34,7,100," "); printToxy(55,9,"Account not found.");
        createBlock(34,11,59," "); gotoxy(50,13); system("pause");
    }else{
        system("cls");
        createBlock(34,3,100," "); printToxy(50,5,"B A L A N C E   I N Q U I R Y");
        createBlock(34,7,52," "); printToxy(35,9,"Account Name:");
        createBlock(54,7,100," "); gotoxy(56,9);printf("%s",p->atm.accountName);
        createBlock(34,11,52," "); printToxy(35,13,"Current Balance:");
        createBlock(54,11,100," "); gotoxy(56,13);printf("Php %d",p->atm.balance);
        createBlock(34,15,100,""); printToxy(50,17," "); system("pause"); system("cls");
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
        createBlock(34,3,100," "); printToxy(50,5,"W I T H D R A W   M O N E Y");
        createBlock(34,7,100," "); printToxy(55,9,"Account not found.");
        createBlock(34,11,59," "); gotoxy(50,13); system("pause");
    }else{
        if(p->atm.balance!=0){
            do{
                system("cls");
                createBlock(34,3,100," "); printToxy(50,5,"W I T H D R A W   M O N E Y");
                createBlock(34,7,79," "); printToxy(36,9,"Please input amount to withdraw:");
                createBlock(81,7,100," ");
                createBlock(34,11,100," "); printToxy(50,13,"- - -");
                createBlock(34,15,100," "); printToxy(45,17,"- - -");
                createBlock(34,19,100," "); printToxy(45,21,"- - -");
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
            printToxy(50,13,"Withdraw successful.");
            gotoxy(45,17);printf("Your new balance: Php %d", p->atm.balance);
            gotoxy(45,21);system("pause");
        }else{
            system("cls");
            createBlock(34,3,100," "); printToxy(50,5,"W I T H D R A W   M O N E Y");
            createBlock(34,7,100," "); printToxy(55,9,"You have no balance. Please deposit first.");
            createBlock(34,11,59," "); gotoxy(50,13); system("pause");
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
        createBlock(34,3,100," "); printToxy(50,5,"D E P O S I T");
        createBlock(34,7,100," "); printToxy(55,9,"Account not found.");
        createBlock(34,11,59," "); gotoxy(50,13); system("pause");
    }else{
        system("cls");
        createBlock(34,3,100," "); printToxy(50,5,"D E P O S I T");
        do{
            createBlock(34,11,100," "); printToxy(35,13,"- - -");
            createBlock(34,15,100," "); printToxy(35,17,"- - -");
            createBlock(34,19,100," "); printToxy(35,21,"- - -");
            createBlock(34,7,100," "); printToxy(35,9,"Please input amount to deposit: Php "); scanf("%d",&depositt);
            if(depositt<=0)
                printToxy(35,13,"Minimum deposit amount is Php 1.");
        }while(depositt<=0);
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
        createBlock(34,3,100," "); printToxy(50,5,"F U N D   T R A N S F E R");
        createBlock(34,7,100," "); printToxy(55,9,"Account not found.");
        createBlock(34,11,59," "); gotoxy(50,13); system("pause");
    }else if(x->balance!=0){
        count=0;
        system("cls");
        createBlock(34,3,100," "); printToxy(50,5,"F U N D   T R A N S F E R");
        createBlock(34,7,100," "); printToxy(55,9,"Account found!");
        createBlock(34,11,59," "); printToxy(35,13,"Transfering money to:");
        createBlock(61,11,100," "); gotoxy(62,13); printf("%s",p->atm.accountName);
        createBlock(34,15,59," "); printToxy(35,17,"Your balance is:");
        createBlock(61,15,100," "); gotoxy(62,17); printf("Php %d",x->balance);
        createBlock(34,19,100," "); printToxy(35,21,"- - -");
        createBlock(34,23,100," "); printToxy(35,25,"- - -");
        createBlock(34,27,100," "); printToxy(35,29,"- - -");
        createBlock(34,31,100," "); printToxy(35,33,"- - -");
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
        printf("\nInsufficient balance. Please deposit first.\n"); system("pause");
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
        createBlock(34,3,100," "); printToxy(50,5,"U P D A T E   A C C O U N T");
        createBlock(34,7,100," "); printToxy(55,9,"Account not found.");
        createBlock(34,11,59," "); gotoxy(50,13); system("pause");
    }else{
        while(y!=5){
            system("cls");
            printf("Updating Account: \n");
            printf("\nAccount Number: %d",p->atm.accountNumber);
            printf("\nAccount Name: %s",p->atm.accountName);
            printf("\nBirthday: %d / %d / %d",p->atm.month,p->atm.day,p->atm.year);
            printf("\nContact Number: %s",p->atm.contactNumber);
            printf("\nPIN Code: %s",p->atm.pinCode);
            printf("\nUPDATE: \n");
            printf("\n[1] Account Name");
            printf("\n[2] Birthday");
            printf("\n[3] Contact Number");
            printf("\n[4] Change PIN Code");
            printf("\n[5] Back");
            printf("\n\nEnter a Number: ");scanf("%d", &y);
            switch(y){
                case 1: printf("\nInput new Account Name: ");scanf(" %[^\n]s",bdo.accountName);
                        strcpy(p->atm.accountName,bdo.accountName); break;
                case 2: birthDayy(&bdo);
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
                        if(pin(&bdo,2)!=1){
                            printf("\nPlease Enter NEW Pin Code");pin(&bdo,1);
                            strcpy(p->atm.pinCode,bdo.pinCode);
                        }else{
                            printf("\nToo many failed attemps. Please try later.");
                        }break;
                case 5: printf("\n%s's account is successfully updated.", p->atm.accountName);system("pause");break;
                default: printf("\nSelect 1-6 only\n");system("pause");
            }
        }
    }
}

void birthDayy(REC *bday){
    a:
    printToxy(36,18,"                                     ");
    printToxy(54,8,"               ");
    printToxy(45,22,"                               ");
    printToxy(54,8,"Birth month: ");
    gotoxy(67,8);scanf("%d",&bday->month);
    if(bday->month<=0 || bday->month>12){
        printToxy(45,18,"I N V A L I D   M O N T H !!");
        gotoxy(45,22);system("pause");
        goto a;
    }
    b:
    printToxy(41,18,"                                     ");
    printToxy(54,8,"Birth day:  ");
    printToxy(70,8,"/   ");
    printToxy(45,22,"                               ");
    gotoxy(72,8);scanf("%d",&bday->day);
    if(bday->day<=0 || bday->day>31){
        printToxy(46,18,"I N V A L I D   D A Y ! !");
        gotoxy(45,22);system("pause");
        goto b;
    }
    c:
    printToxy(36,18,"                                     ");
    printToxy(45,22,"                               ");
    printToxy(78,8,"           ");
    printToxy(54,8,"Birth year: ");
    printToxy(75,8,"/ ");
    gotoxy(78,8);scanf("%d",&bday->year);
    if(bday->year<=1900 || bday->year>2022){
        printToxy(45,18,"I N V A L I D   Y E A R ! !");
        gotoxy(45,22);system("pause");
        goto c;
    }
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
        createBlock(34,3,100," "); printToxy(50,5,"P A Y   B I L L S");
        createBlock(34,7,100," "); printToxy(55,9,"Account not found.");
        createBlock(34,11,59," "); gotoxy(50,13); system("pause");
    }else{
        printf("[1]Meralco Bill\n");
        printf("[2]Maynilad Bill\n");
        printf("[3]Back\n");
        scanf("%d",&userNum);
        switch(userNum){
            case 1: system("cls");
                    Meralco=rand()%2000 + 1;
                    printf("\nMERALCO BILL\n\n");
                    printf("Meralco Bill: Php %d\n", Meralco);
                    printf("\nAccount Balance: Php %d\n\n", p->atm.balance);
                    printf("[1]Pay Meralco Bill\n");
                    printf("[2]Back\n");
                    scanf("%d",&userNum);
                    switch(userNum){
                        case 1: if(p->atm.balance>=Meralco){
                                    p->atm.balance-=Meralco;
                                    printf("\nPayment successful.\n");
                                }else{
                                    printf("\nInsufficient Balance.\n");
                                }system("pause");break;
                        case 2: break;
                        default: printf("\nInvalid input.\n");system("pause");
                    }break;
            case 2: system("cls");
                    Maynilad=rand()%800 + 1;
                    printf("\nMAYNILAD BILL\n\n");
                    printf("Maynilad Bill: Php %d\n", Maynilad);
                    printf("\nAccount Balance: Php %d\n\n", p->atm.balance);
                    printf("[1]Pay Meralco Bill\n");
                    printf("[2]Back\n");
                    scanf("%d",&userNum);
                    switch(userNum){
                        case 1: if(p->atm.balance>=Maynilad){
                                    p->atm.balance-=Maynilad;
                                    printf("\nPayment successful.\n");
                                }else{
                                    printf("\nInsufficient Balance.\n");
                                }system("pause");break;
                        case 2: break;
                        default: printf("\nInvalid input.\n");system("pause");
                    }break;
            case 3: break;
            default: printf("\nInvalid input.\n");system("pause");
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
    createBlock(34,3,100," "); printToxy(50,5,"T R A N S A C T I O N      M E N U");
    createBlock(34,7,40," [1]"); createBlock(42,7,100," "); printToxy(50,9,"BALANCE INQUIRY\n");
    createBlock(34,11,40," [2]"); createBlock(42,11,100," "); printToxy(50,13,"WITHDRAW");
    createBlock(34,15,40," [3]"); createBlock(42,15,100," "); printToxy(50,17,"DEPOSIT");
    createBlock(34,19,40," [4]"); createBlock(42,19,100," "); printToxy(50,21,"FUND TRANSFER");
    createBlock(34,23,40," [5]"); createBlock(42,23,100," "); printToxy(50,25,"OTHER TRANSACTIONS");
    createBlock(34,27,40," [6]"); createBlock(42,27,100," "); printToxy(50,29,"EXIT");
    createBlock(34,31,100," "); printToxy(50,33,"Enter your choice 1-6: ");scanf("%d", &UserNum);
    return UserNum;
}
int otherTransaction(){
    int UserNum;
    createBlock(34,3,100," "); printToxy(47,5,"- O T H E R   T R A N S A C T I O N S -");
    createBlock(34,7,40," [1]"); createBlock(42,7,100," "); printToxy(50,9,"ACCOUNT SETTINGS");
    createBlock(34,11,40," [2]"); createBlock(42,11,100," "); printToxy(50,13,"PAY BILLS");
    createBlock(34,15,40," [3]"); createBlock(42,15,100," "); printToxy(50,17,"BACK");
    createBlock(34,19,100," ");printToxy(50,21,"Enter your choice 1-3: ");scanf("%d", &UserNum);
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

void createBlock(int x, int y, int len, char *str){
    int i;
    for(i = x; i < len; i++){
        printToxy(i,y,"_");
        printToxy(i,y + 3,"_");
    }
    for(i = y + 1; i < y + 4; i++){
        printToxy(x - 1,i,"|");
        printToxy(len,i,"|");
    }
    printToxy(x + 1, y + 2,str);
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

void box(){
int i;
gotoxy(54,8);printf("Birth date:               ");
printToxy(30,10,"Contact Number: 09");
printToxy(30,12,"Initial Deposit (Min. 5,000): Php ");
printToxy(30,14,"PIN Code: ");
for(i=0;i<10;i++){
    gotoxy(28,6+i);printf("|");
    gotoxy(90,6+i);printf("|");
 }
gotoxy(52,8);printf("|");
gotoxy(52,9);printf("|");
gotoxy(29,5);printf("_____________________________________________________________");
gotoxy(29,7);printf("_____________________________________________________________");
gotoxy(29,9);printf("_______________________|_____________________________________");
gotoxy(29,11);printf("_____________________________________________________________");
gotoxy(29,13);printf("_____________________________________________________________");
gotoxy(29,15);printf("_____________________________________________________________");

for(i=0;i<3;i++){
gotoxy(28,17+i);printf("|");
gotoxy(90,17+i);printf("|");
}
gotoxy(29,16);printf("_____________________________________________________________");
gotoxy(29,19);printf("_____________________________________________________________");
}
