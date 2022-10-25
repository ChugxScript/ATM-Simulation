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
void decrypt(REC *x);
int transactionMenu();
int otherTransaction();
void save();
void saveFD();

//global variables
int balanceFD, accNumFD,count;
char nameFD[31];
char pinCodeFD[7];

int main(){
    int accTransfer,index=2;
    char ch;
    REC bdo;
    srand(time(NULL));
    makenull();
    retrieve();
    decrypt(&bdo);
    printf("\nBDO Name: %s AccNum: %d Pin: %s\n",bdo.accountName,bdo.accountNumber,bdo.pinCode);system("pause");
    switch(insertcard()){
        case 1: bdo.contactNumber[0]='0'; bdo.contactNumber[1]='9';
                do{
                    bdo.accountNumber = rand() % 999999 + 10000;
                    accNumFD = bdo.accountNumber;
                }while(uniqueAcc(bdo.accountNumber)==1);
                system("cls");
                printf("REGISTRATION MODULE: Creating new ATM Account\n\n");
                printf("Please fill out the following informations: \n\n");
                printf("\nAccount Number: %d",bdo.accountNumber);
                printf("\nAccount Name: ");scanf(" %[^\n]s",bdo.accountName);
                birthDayy(&bdo);system("cls");
                printf("REGISTRATION MODULE\n");
                printf("Please fill out the following informations: \n\n");
                printf("\nAccount Number: %d",bdo.accountNumber);
                printf("\nAccount Name: %s",bdo.accountName);
                printf("\nBirthdate (MM/DD/YYYY): %d / %d / %d",bdo.month,bdo.day,bdo.year);
                printf("\nContact Number: 09");
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
                printf("\nContact Number: %s",bdo.contactNumber);

                do{
                    printf("\nInitial Deposit (Min. 5,000): Php ");scanf("%d", &bdo.balance);
                    if(bdo.balance<5000)
                        printf("Minimum deposit is Php 5000.\n");
                }while(bdo.balance<5000);
                pin(&bdo,1);
                addNewATMaccount(bdo);
                printf("\nREGISTRATION SUCCESSFUL\n"); system("pause");
                break;
        case 2: if(pin(&bdo,2)==2){
                    break;
                }else{
                    printf("\nmain: Too many failed attempts. Please try later.");system("pause");exit(0);
                }
    }

    while(1){
        c: count=0;
        system ("cls");printf("TRANSACTION MODULE\n\n");
        switch(transactionMenu()){
            case 1: balance(&bdo); break;
            case 2: system("cls"); printf("WITHDRAW MONEY\n");
                    withdraw(&bdo);break;
            case 3: system("cls"); printf("DEPOSIT MONEY\n");
                    deposit(&bdo); break;
            case 4: system("cls"); printf("FUND TRANSFER\n\n");
                    do{
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
            case 5: system("cls"); printf("OTHER TRANSACTIONS\n");
                    switch(otherTransaction()){
                        case 1: system("cls");printf("Input Account Pin Code: \n");system("pause");
                                if(pin(&bdo,2)!=1){
                                    updateAccount(&bdo);
                                }break;
                        case 2: system("cls"); printf("PAY BILLS\n\n");
                                utility(&bdo); break;
                        default: printf("\nInvalid input. Try again.\n"); system("pause");
                    }break;
            case 6: encrypt();save();saveFD();exit(0);break;
            default: printf("\nInvalid input. Try again.\n"); system("pause");
        }
    }
}


void makenull(){
    L=NULL;
}

void retrieve(){
    int i;
    FILE *fp;
    REC z;
    fp=fopen("D:\\Database.txt","r+");
    if(fp!=NULL){
        while(!feof(fp)){
            fscanf(fp," %[^\t]s", z.accountName);
            fscanf(fp,"%d",&z.accountNumber);
            fscanf(fp," %[^\t]s", z.pinCode);
            fscanf(fp,"%d", &z.balance);
            fscanf(fp," %[^\t]s", z.contactNumber);
            fscanf(fp,"%d %d %d\n", &z.month, &z.day, &z.year);
            addNewATMaccount(z);
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
        system("cls");
        printf("Please insert card...");
        fp=fopen("F:\\Check.txt","w"); //in flashdrive
    }while(fp==NULL);
    fclose(fp);
    fp=fopen("F:\\ATM.txt","r");
    if(fp==NULL){
        printf("\nNOT YET REGISTERED\n"); system("pause");
        system("cls"); return 1;
    }else{
        printf("\nWELCOME %s!\n",p->atm.accountName);system("pause");
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
        printf("\nPIN Code: ");
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
            printf("\nPIN Code: ");
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
        printf("\nToo many failed attemps. Please try later.\n");system("pause");
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
        printf("\nWrong PIN Code\n");system("pause");
        return 1;
    }else{
        printf("\nPIN verified.\n");system("pause");
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
        printf("\nAccount not found.\n");system("pause");
    }else{
        system("cls"); printf("BALANCE INQUIRY\n");
        printf("\nAccount NAme: %s",p->atm.accountName);
        printf("\nCurrent Balance: Php %d\n\n", p->atm.balance);
        system("pause"); system("cls");
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
        printf("\nAccount not found.\n");system("pause");
    }else{
        if(p->atm.balance!=0){
            do{
                printf("Please input amount to withdraw: Php ");scanf("%d",&withdraww);
                if(withdraww>(p->atm.balance))
                    printf("\nInsufficient Balance.\n");
                else if(p->atm.balance<0)
                    printf("Invalid amount.\n");
                else if(p->atm.balance==0)
                    printf("Insufficient Balance.\n");
            }while(withdraww>(p->atm.balance) || p->atm.balance<0 || p->atm.balance==0);
            p->atm.balance-=withdraww;
            printf("\n\nWithdraw successful.");
            printf("\nYour new balance: Php %d\n", p->atm.balance);system("pause");
        }else{
            printf("\nYou have no balance.\n");system("pause");
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
        printf("\nAccount not found.\n");system("pause");
    }else{
        do{
            printf("Please input amount to deposit: Php ");scanf("%d",&depositt);
            if(depositt<=0)
                printf("\nMinimum deposit amount is Php 1.\n");
        }while(depositt<=0);
        p->atm.balance+=depositt;
        printf("\n\nDeposit successful.");
        printf("\nYour new balance: Php %d\n",p->atm.balance);system("pause");
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
        printf("\nAccount not found.\n");system("pause");
    }else{
        printf("\n\nAccount found!\n");
        printf("Transfering money to: %s\n",p->atm.accountName);
        do{
            printf("\nInput amount to transfer: Php ");
            scanf("%d",&transfer);
            if(transfer>x->balance){
                 printf("\nInsufficient balance.\n"); system("pause");
            }else if(transfer<=0){
                printf("\nMinimum transfer amount is Php 1.\n");system("pause");
            }
        }while(transfer>x->balance || transfer<=0);
        p->atm.balance+=transfer;
        printf("\nTotal Amount of Php %d was successfully transferred to %s.\n",transfer,p->atm.accountName);system("pause");

        //back to the previous node to store the balance to the current user
        p=q=L;
        while(p!=NULL && x->accountNumber!=p->atm.accountNumber){
            q=p;
            p=p->next;
        }
        p->atm.balance-=transfer;
        printf("\nYour Total Balance is: Php %d\n",p->atm.balance);system("pause");
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
            printf("Account not found.\n");system("pause");
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
    printf("\nBirthday (MM/DD/YYYY)\n");
    a:
    printf("\nIf your birth month is January, enter 01");
    printf("\nEnter your birth month: ");scanf("%d",&bday->month);
    if(bday->month<=0 || bday->month>12){
        printf("\nInvalid Month.");system("pause");
        goto a;
    }
    b:
    printf("\nEnter your birth day: ");scanf("%d",&bday->day);
    if(bday->day<=0 || bday->day>31){
        printf("\nInvalid Day.");system("pause");
        goto b;
    }
    c:
    printf("\nEnter your birth year: ");scanf("%d",&bday->year);
    if(bday->year<=1900 || bday->year>2022){
        printf("\nInvalid Year.");system("pause");
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
        printf("\nAccount not found.\n");system("pause");
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
void decrypt(REC *x){
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
            x->accountNumber=p->atm.accountNumber;
            x->pinCode[i]=p->atm.pinCode[i];
            pinCodeFD[i]=pinCodeFD[i]-70;
            i++;
        }
    }
}

int transactionMenu(){
    int UserNum;
    printf("TRANSACTION MENU\n");
    printf("[1] BALANCE INQUIRY\n");
    printf("[2] WITHDRAW\n");
    printf("[3] DEPOSIT\n");
    printf("[4] FUND TRANSFER\n");
    printf("[5] OTHER TRANSACTIONS\n");
    printf("[6] EXIT\n");
    printf("\nEnter your choice 1-6: ");
    scanf("%d", &UserNum);
    return UserNum;
}
int otherTransaction(){
    int UserNum;
    printf("[1] ACCOUNT SETTINGS\n");
    printf("[2] PAY BILLS\n");
    printf("[3] EXIT\n");
    printf("\nEnter your choice 1-3: ");
    scanf("%d", &UserNum);
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
    while (p!=NULL && p->atm.accountNumber!=accNumFD){
        q=p;
        p=p->next;
    }
    fp = fopen("F:\\ATM.txt","w+");
    if (fp==NULL){
        printf("Error 404. File not found.\n");
        system("pause");
    }
    else {
        fprintf(fp,"%s\t%d\t%s\t%d\n",q->atm.accountName,q->atm.balance,q->atm.pinCode,q->atm.accountNumber);
        fclose(fp);
    }
}
