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
1. Nastustuck sa pincheck pag nakalimutan HAHA
2. Fund Transfer (di nababawasan si sender)
3. Yung decrypt (san banda to nakalagay)
4. Encrypt (san din to nakalagay)
5. Account number kailangan unique or kailangan icompare yung acc number sa database (ok na ata to?)
6. di maverify yung pin pag di pa nag-eexit sa first time use si user (oks na ata to?)
7. FEEELING KO MAY MALI SA RETRIEVE/SAVE YATA EWAN NAG-IIBA YUNG LAMAN NG ATM HAHAHA
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
void pin(REC *x, int a);
int checkPin(char *n[7]);
void addNewATMaccount(REC x);
void updateAccount(char n[31]);
void deleteAccount(char n[31]);
void birthDayy(REC *bday);
void balance(REC *x);
void withdraw(REC *x);
void deposit(REC *x);
void fundTransfer(REC *x, int a);
void utility(REC *x);
void encrypt();
void decrypt();
int menu();
int AccountMenu();
int transactionMenu();
void save();
void saveFD();
void display(); //reremove to pag tapos na HAHA

//global variables
int balanceFD, accNumFD;
char nameFD[31];
char pinCodeFD[7];

int main(){
    int x,accTransfer,index=2;
    char ch;
    REC bdo;
    srand(time(NULL));
    makenull();
    retrieve();
    decrypt();
    switch(insertcard()){
        case 1: bdo.contactNumber[0]='0'; bdo.contactNumber[1]='9';
                do{
                    bdo.accountNumber = rand() % 999999 + 10000;
                }while(uniqueAcc(bdo.accountNumber)==1);
                system("cls");
                printf("REGISTRATION MODULE\n");
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
        case 2: pin(&bdo,2);
                break;
    }

    while(1){
        system ("cls");
        switch(menu()){
            case 1: system("cls"); printf("ACCOUNT MODULE\n\n");
                    b:
                    x = AccountMenu();
                    if(x==1){
                        system("cls");printf("Input Account Pin Code: \n");system("pause");pin(&bdo,2);
                        updateAccount(bdo.pinCode); break;
                    }else if(x==2){
                        system("cls");printf("Input Account Pin Code: \n");system("pause");pin(&bdo,2);
                        deleteAccount(bdo.pinCode); break;
                    }else if(x==3){
                        break;
                    }else{
                        printf("\nSelect 1-3 only.");system("pause");goto b;
                    }break;
            case 2: system("cls"); printf("TRANSACTION MODULE\n\n");
                    switch(transactionMenu()){
                        case 1: balance(&bdo); break;
                        case 2: system("cls"); printf("WITHDRAW MONEY\n");
                                withdraw(&bdo);break;
                        case 3: system("cls"); printf("DEPOSIT MONEY\n");
                                deposit(&bdo); break;
                        case 4: system("cls"); printf("FUND TRANSFER\n");
                                do{
                                    printf("Enter the Account No. you want to transfer: ");
                                    scanf("%d",&accTransfer);
                                    if(accTransfer<10000 || accTransfer>99999)
                                        printf("\nInvalid Account Number.");
                                }while(accTransfer<10000 || accTransfer>99999);
                                fundTransfer(&bdo,accTransfer);system("pause");
                                break;
                        case 5: system("cls"); printf("PAY UTILITY BILLS\n");
                                utility(&bdo);break;
                        case 6:break;
                        default: system("cls"); printf("Invalid input.\n");transactionMenu();
                    }break;
            case 3: encrypt();save();saveFD();exit(0);break;
            default: printf("Invalid input. Try again."); system("pause\n");
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
    if(fp==NULL){
        printf("No Record in DATABASE\n");
        system("pause");
    }else{
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
        printf("\nWELCOME\n");system("pause");
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

void pin(REC *x, int a){
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
        do{
            c:
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

void updateAccount(char n[31]){
    int x,index=2;
    char ch;
    REC bdo;
    LIST *p, *q;
    p=q=L;
    while(p!=NULL && strcmp (n, p->atm.pinCode)!=0){
        q=p;
        printf("\n%s  ",p->atm.pinCode);
        p=p->next;
    }
    if(p==NULL){
            printf("Account not found.\n");system("pause");
    }else{
        while(x!=5){
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
            printf("\n\nEnter a Number: ");scanf("%d", &x);
            switch(x){
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
                case 4: printf("\nPlease Enter CURRENT Pin Code\n");system("pause");pin(&bdo,2);
                        printf("\nPlease Enter NEW Pin Code");pin(&bdo,1);
                        strcpy(p->atm.pinCode,bdo.pinCode); break;
                case 5: printf("\n%s's account is successfully updated.", p->atm.accountName);system("pause");break;
                default: printf("\nSelect 1-6 only\n");system("pause");
            }
        }
    }
}

void deleteAccount(char n[31]){
    int userChoice;
    LIST *p, *q;
    p=q=L;
    while(p!=NULL && strcmp (n, p->atm.pinCode)!=0){
        q=p;
        p=p->next;
    }
    if (p==NULL){
        printf("Account not found.\n");system("pause");
    }else{
        printf("\n\nAre you sure you want to delete your account?\n");
        printf("[1]YES\n");
        printf("[2]NO\n");
        scanf("%d", &userChoice);
        if(userChoice==1){
            if (p==L){
                L=p->next;
            }else{
                q->next=p->next;
            }
            if(remove("F:\\ATM.txt")==0){
                free(p);printf("%s's account is successfully deleted.\n",n);system("pause");
            }else{
                printf("\nDeletion not successfull.");system("pause");
            }
        }else{
            AccountMenu();
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

void balance(REC *x){
    LIST *p, *q;
    p=q=L;
    while(p!=NULL && strcmp(x->pinCode,p->atm.pinCode)!=0){
        q=p;
        p=p->next;
    }
    if (p==NULL){
        printf("\nAccount not found.\n");
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
    while(p!=NULL && strcmp(x->pinCode,p->atm.pinCode)!=0){
        q=p;
        p=p->next;
    }
    if (p==NULL){
        printf("\nAccount not found.\n");
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
    while(p!=NULL && strcmp(x->pinCode,p->atm.pinCode)!=0){
        q=p;
        p=p->next;
    }
    if (p==NULL){
        printf("\nAccount not found.\n");
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
        printf("\nAccount not found.\n");
    }else{
        printf("\nAccount found!");
        do{
            printf("\nInput amount to transfer: Php ");
            scanf("%d",&transfer);
            if(transfer>x->balance)
                    printf("\nInsufficient balance.");
            else if(transfer<=0)
                    printf("\nMinimum transfer amount is Php 1.");
        }while(transfer>x->balance || transfer<=0);
        p->atm.balance+=transfer;
        printf("\nAmount was successfully transferred to %s   total balance: %d.\n",p->atm.accountName,p->atm.balance);

        //back to the previous node to store the balance to the current user
        p=q=L;
        while(p!=NULL && x->accountNumber!=p->atm.accountNumber){
            q=p;
            p=p->next;
        }
        p->atm.balance-=transfer;
    }
}

void utility(REC *x){
    int Meralco,Maynilad,userNum;
    LIST *p, *q;
    p=q=L;
    while(p!=NULL && strcmp(x->pinCode,p->atm.pinCode)!=0){
        q=p;
        p=p->next;
    }
    if (p==NULL){
        printf("\nAccount not found.\n");
    }else{
        Meralco=rand()%1000 + 1;
        Maynilad=rand()%500 + 1;
        printf("Meralco Bill: Php %d\n", Meralco);
        printf("Maynilad Bill: Php %d\n", Maynilad);
        printf("\n\nTotal Utility Bill: Php %d", Meralco+Maynilad);
        printf("\nAccount Balance: Php %d", p->atm.balance);
        printf("\n\n[1]Pay Utility Bills.\n");
        printf("[2]Back\n");
        scanf("%d", &userNum);
        switch(userNum){
            case 1: if(p->atm.balance>=(Maynilad+Meralco)){
                        p->atm.balance-=(Maynilad+Meralco);
                        printf("\nPayment successful.\n");
                    }else{
                        printf("\nInsufficient Balance.\n");
                    }system("pause");
                    break;
            case 2: break;
            default:printf("Invalid input.\n");system("pause\n");
        }
    }
}

void encrypt(){
    int i=0;
    LIST *p; p=L;
    while(p!=NULL){
        while(p->atm.pinCode[i]!='\0'){
            p->atm.pinCode[i]=p->atm.pinCode[i] + 70;
            i++;
        }p=p->next;
    }
}
void decrypt(){
    int i=0;
    LIST *p; p=L;
    while(p!=NULL){
        while(p->atm.pinCode[i]!='\0'){
            p->atm.pinCode[i]=p->atm.pinCode[i] - 70;
            i++;
        }p=p->next;
    }
}

int menu(){
    int UserNum;
    system("cls");
    printf("Choose Module: \n");
    printf("[1] ACCOUNT SETTINGS\n");
    printf("[2] TRANSACTION MODULE\n");
    printf("[3] EXIT\n");
    printf("\nEnter your choice 1-3: ");
    scanf("%d", &UserNum);
    return UserNum;
}
int AccountMenu(){
    system("cls");
    REC other;
    int UserNum;
    printf("Choose account option: \n");
    printf("[1] Update Account\n");
    printf("[2] Delete Account\n");
    printf("[3] Back\n");
    printf("\nEnter your choice 1-3: ");
    scanf("%d", &UserNum);
    return UserNum;
}
int transactionMenu(){
    int UserNum;
    while(1){
    system("cls");
    printf("Choose Transaction: \n");
    printf("[1] Balance Inquiry\n");
    printf("[2] Withdraw\n");
    printf("[3] Deposit\n");
    printf("[4] Fund Transfer\n");
    printf("[5] Other Transactions\n");
    printf("[6] Back\n");
    printf("\nEnter your choice 1-6: ");
    scanf("%d", &UserNum);
    return UserNum;
    }
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
            /*while(p->atm.pinCode[i]!='\0'){
                p->atm.pinCode[i]=p->atm.pinCode[i] + 70;
                i++;
            }*/
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
    while (p!=NULL){
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

void display(){ //tatanggalin to pero dito muna pang check lang HAHA
    LIST *p;
    int x = 1;
    p=L;
    printf("\n\nALL LIST: \n");
    while (p!=NULL){
        printf("%d.) %d\t%s\t%d\t%s\t%d %d %d\t%s\n",x++,p->atm.accountNumber,p->atm.accountName,p->atm.balance,p->atm.pinCode,p->atm.month,p->atm.day,p->atm.year,p->atm.contactNumber);
        p=p->next;
    }
    system("pause");system("cls");
}
