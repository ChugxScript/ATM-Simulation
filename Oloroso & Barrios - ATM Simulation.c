/*Project 1 - ATM SIMULATION in C using linked list
by Andrew R. Oloroso and Armand Angelo C. Barrios*/
#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//tinanggal ko muna yung mga comments sa codes dati para makita mo yung mga kemeru, balik nalang siguro pag tapos na natin

/*
READ THIS SHITTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT BROOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO!
Mga Problema/Kulang:
1. Retrieve(); (ewan ko pano to)
2. Save();     (eto rin, ewan ko kung pano to)
3. Yung display ng birthday (tsaka yung sa update na birthday rin ata)
4. Contact No., need ata natin ma-ensure rito na 09-keme-keme ilalagay niya o wag na(??)
5. Pin Code sa regMode (dapat naka-char)
6. Palitan siguro yung initialDeposit na name tas gawing balance (suggestion lang, nakakalito kase)
7. Pagchecheck ng Pin Code (char kse eh so need ata natin i-compare every char)
8. Fund Transfer, di ko alam paano to gagawin
9. Yung decrypt (san banda to nakalagay)
10. Encrypt (san din to nakalagay)
11. Yung "Wrong Pin Code" sa Existing User na lumalabas pag hiningi yung pin
12. Yung sa update tas delete account pre, di na need yung name kasi bakit mo naman idedelete/i-uupdate account ng iba HAHAHA
    siguro tanong nalang yung pin, tas pag tama, g na yon.

Addtl kineme:
Yung #11 ayusin ko na rin sana ngayon kaso inaantok nako HAHAHA.
Di ko pa masyado na-rurun and nachecheck yung mga nalagay ko so baka may mga bagong problems pa dyan HAHAHA. Check mo nalang kung trip mo.
delete mo nalang siguro yung mga keme na comments ko except dun sa listahan ng mga problema/kulang
Tulog pa ata ako habang binabasa mo to. HAHAHA.
*/

typedef struct details{
    char accountName[31];
    int accountNumber;
    int month,day,year;
    int contactNumber;
    int initialDeposit;
    char pinCode[7];
}REC;
typedef struct node{
    REC atm;
    struct node* next;
}LIST; LIST *L;

char c,ping[7];

void makenull(){
    L=NULL;
}

void insertcard(){
    FILE *fp;
    do{
        system("cls");
        printf("Please insert card...");
        fp=fopen("F:\pakanangpakshet.txt","r+");
    }while(fp==NULL);
    fclose(fp);
    printf("\nCard inserted successfully.\n"); system("pause");
}

int isUSER(){
    int x;
    printf("\nAre you a NEW or EXISTING user?\n");
    printf("Press [1] if NEW [2] if EXISTING\n"); scanf("%d", &x);
    return x;
}

void birthDayy(REC sm){
    int x,y,z;
    printf("\nBirthday (MM/DD/YYYY)\n");
    a:
    printf("\nIf your birth month is January, enter 01");
    printf("\nEnter your birth month: ");scanf("%d",&x);
    if(x<=0 || x>12){
        printf("\nInvalid Month.");system("pause");
        goto a;
    }else{
        sm.month=x;
    }
    b:
    printf("\nEnter your birth day: ");scanf("%d",&y);
    if(y<=0 || y>31){
        printf("\nInvalid Day.");system("pause");
        goto b;
    }else{
        sm.day=y;
    }
    c:
    printf("\nEnter your birth year: ");scanf("%d",&z);
    if(z<=0 || z>2023){
        printf("\nInvalid Year.");system("pause");
        goto c;
    }else{
        sm.year=z;
    }
}

void regMode(REC bpi){
    char ch;
    int marker=0;
    int index=0;
    bpi.accountNumber = rand() % 99999 + 10000; //10k para sure na 5 digits
    system("cls");
    printf("REGISTRATION MODULE\n");
    printf("Please fill out the following informations: \n\n");
    printf("\nAccount Number: %d",bpi.accountNumber);
    printf("\nAccount Name: ");scanf(" %[^\n]s",bpi.accountName);
    birthDayy(bpi);
    printf("\nBirthdate (MM/DD/YYYY): %d / %d / %d",bpi.month,bpi.day,bpi.year);
    printf("\nContact Number: ");scanf("%d", &bpi.accountNumber);
    do{
        printf("\nInitial Deposit (Min. 5,000): ");scanf("%d", &bpi.initialDeposit);
        if(bpi.initialDeposit<5000)
            printf("Minimum deposit is 5000 petot, betch.\n");
    }while(bpi.initialDeposit<5000);
    printf("\nPIN Code: ");scanf("%d",&bpi.pinCode);  //gagawin 'tong ano tulad dun sa isa na char, pre
}

void addNewATMaccount(REC x){
    LIST *p,*q,*temp;
    q=p=L;
    temp = (LIST*) ((malloc(sizeof(LIST))));
    temp->atm = x;
    while (p!=NULL && strcmp (x.accountName, p->atm.accountName)>=0){
        q=p;
        p=p->next;
    }
    if (p==L){
        L=temp;
    }else{
        q->next = temp;
    }temp->next = p;
}

void pin(){
    REC x;
    int index=0;
    int y=0,z=0;
    char ch;
    printf("Enter PIN: ");
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
         x.pinCode[index++]=ch;
         putchar('*');
        }
    }
    if (index==5){
        x.pinCode[index++]=ch;
        putchar('*');
    }x.pinCode[index]='\0';
    printf("\n\nPin Code = %s\n",x.pinCode); system("pause");

    while(x.pinCode[y]!='\0'){
        x.pinCode[y]=x.pinCode[y] + 70;
        y++;
    }printf("\n\nEncrypted Pin Code = %s\n",x.pinCode); system("pause");

    while(x.pinCode[z]!='\0'){
        x.pinCode[z]=x.pinCode[z] - 70;
        z++;
    }printf("\nDecrypted Pin Code = %s\n",x.pinCode); system("pause");
}

void save(){
/*
    FILE *fp;
    int i;
    fp = fopen("E:\pakanangpakshet.txt","w+");
    if (fp==NULL){
        printf("Error 404. File not found.\n");
        system("pause");
    }
    else {
        for (i=0;i<=;i++)
            fprintf(" ");
        fclose(fp);
      }
*/
}

void checkPin(char n[31]){
    LIST *p, *q;
    p=q=L;
    while(p!=NULL && strcmp (n, p->atm.pinCode)!=0){
        q=p;
        p=p->next;
    }
    if (p==NULL){
        printf("\nWrong PIN Code\n");system("pause");
    }else{
        printf("\nPIN verified.");system("pause");
    }
}

int menu(){
    int UserNum;
    system("cls");
    printf("Choose Module: \n");
    printf("[1] ACCOUNT\n");
    printf("[2] TRANSACTION MODULE\n");
    printf("[3] EXIT\n");
    printf("\nEnter your choice 1-3: ");
    scanf("%d", &UserNum);
    return UserNum;
}

void updateAccount(char n[31]){
    int marker=0;
    int x=0,y=0,z=0;
    LIST *p, *q;
    p=q=L;
    while(p!=NULL && strcmp (n, p->atm.accountName)!=0){
        q=p;
        p=p->next;
    }
    if(p==NULL){
            printf("Account not found.\n");system("pause");
    }else{
        while(x!=6){
            system("cls");
            printf("Updating Account: \n");
            printf("\nAccount Number: %d",p->atm.accountNumber);
            printf("\nAccount Name: %s",p->atm.accountName);
            printf("\nBirthday: %d / %d / %d",p->atm.month,p->atm.day,p->atm.year);
            printf("\nContact Number: %d",p->atm.contactNumber);
            printf("\nPIN Code: %d",p->atm.pinCode);
            printf("\nUPDATE: \n");
            printf("\n[1] Account Number");
            printf("\n[2] Account Name");
            printf("\n[3] Birthday");
            printf("\n[4] Contact Number");
            printf("\n[5] Change PIN Code");
            printf("\n[6] Back");
            printf("\n\nEnter a Number: ");scanf("%d", &x);
            switch(x){
                case 1: printf("\nInput new Account Number: ");scanf("%d", &p->atm.accountNumber);break;
                case 2: printf("\nInput new Account Name: ");scanf("%d",p->atm.accountName);break;
                case 3: while(marker!=1){
                            printf("\nInput new Birthday (MM/DD/YYYY)\n");
                            do{
                                printf("\nIf your birth month is January, enter 01");
                                printf("\nEnter your birth month: ");scanf("%d",&x);
                                system("cls");
                            }while(x>0 && x<=12); p->atm.month=x;
                            do{
                                printf("\nEnter your birth day: ");scanf("%d",&y);
                                system("cls");
                            }while(y>0 && y<=31); p->atm.day=y;
                            do{
                                printf("\nEnter your birth year: ");scanf("%d",&z);
                                system("cls");
                            }while(z>0 && z<=2023); p->atm.year=z; marker=1;
                        }break;
                case 4: printf("\nInput new Contact Number: ");scanf("%d", &p->atm.contactNumber);break;
                case 5: printf("\nEnter Pin: ");
                        scanf("%c",&p->atm.pinCode);
                        //checkPin(); kailangan i-compare to every lagay ng user
                        break;
                case 6: printf("\n%s's account is successfully updated.", p->atm.accountName);system("pause");break;
                default: printf("\nSelect 1-6 only\n");system("pause");
            }
        }
   }
}

void deleteAccount(char n[31]){
    int userChoice;
    LIST *p, *q;
    p=q=L;
    while(p!=NULL && strcmp (n, p->atm.accountName)!=0){
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
            }free(p);printf("%s's account is successfully deleted.\n",n);system("pause");
        }else{
            AccountMenu();
        }
    }
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
    //lalagay siguro rito ng function na checker sa pincode tapos isang tanungan nalang or bago mag Account Menu?
    switch(UserNum){
        case 1: system("cls");
                printf("Input Account Name to be updated: ");scanf(" %[^\n]s",other.accountName);
                updateAccount(other.accountName);break;
        case 2: system("cls");
                printf("Input Account Name to be deleted: ");scanf(" %[^\n]s",other.accountName);
                deleteAccount(other.accountName);break;
        case 3: menu();system("cls");break;
        default:system("cls");break;
    }
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

int main(){
    int withdraw,deposit;
    REC bdo;
    srand(time(NULL));
    makenull();
    insertcard();
    if(isUSER()==1){
        regMode(bdo);
        addNewATMaccount(bdo);
        printf("\nRegistration successful! Thank you for choosing Bank Rupt, Mr/Ms. %s.\n", bdo.accountName);system("pause");
    }else{
        pin();
        checkPin(bdo.pinCode);
    }
    while(1){
        system ("cls");
        switch(menu()){
            case 1: system("cls"); printf("ACCOUNT SETTINGS\n\n");
                    while(1){
                        switch(AccountMenu()){
                            case 1: break;
                            default: break;
                        }
                    }break;
            case 2: system("cls"); printf("TRANSACTION MODULE\n\n");
                    while(1){
                        switch(transactionMenu()){
                            case 1:printf("BALANCE INQUIRY\n");
                                   printf("Current Balance: %d", bdo.initialDeposit);system("pause");break;
                            case 2:printf("WITHDRAW MONEY\n");
                                   do{
                                   printf("Please input amount to withdraw: ");scanf("%d",&withdraw);
                                   if(withdraw>(bdo.initialDeposit))
                                        printf("\nInsufficient Balance.");
                                   }while(withdraw>(bdo.initialDeposit));
                                   bdo.initialDeposit-=withdraw;
                                   printf("\n\nWithdraw successful.");
                                   printf("\nYour new balance: %d", bdo.initialDeposit);system("pause");break;
                            case 3:printf("DEPOSIT MONEY\n");
                                   do{
                                   printf("Please input amount to deposit: ");scanf("%d",&deposit);
                                   if(deposit==0)
                                        printf("\nMinimum deposit amount is 1.");
                                   }while(deposit!=0);
                                   bdo.initialDeposit+=deposit;
                                   printf("\n\nDeposit successful.");
                                   printf("\nYour new balance: %d",bdo.initialDeposit);system("pause");break;
                            case 4:printf("FUND TRANSFER");system("pause");break;                   //di ko alam pano to gagawin
                            case 5:printf("PAY UTILITY BILLS");
                                   int Meralco,Maynilad;
                                   Meralco=rand()%1000 + 1;
                                   Maynilad=rand()%500 + 1;
                                   printf("Meralco Bill: %d\n", Meralco);
                                   printf("Maynilad Bill: %d\n", Maynilad);
                                   printf("\n\n");
                                   printf("Total Utility Bill: %d\n", Meralco+Maynilad);
                                   int userNum;
                                   while(1){
                                        printf("[1]Pay Utility Bills.\n");
                                        printf("[2]Back\n");
                                        scanf("%d", userNum);
                                        switch(userNum){
                                            case 1: if(bdo.initialDeposit>(Maynilad+Meralco)){
                                                        bdo.initialDeposit-(Maynilad+Meralco);
                                                        printf("\nPayment successful.");
                                                    }else
                                                        printf("\nInsufficient Balance.");
                                                    system("pause");break;
                                            case 2:transactionMenu();break;
                                            default:printf("Invalid input.\n");system("pause");
                                        }


                                   }
                                   break;
                            case 6:menu();break;
                            default:printf("Invalid input.\n");transactionMenu();
                        }
                    }break;
            case 3: save();exit(0);break;
            default: printf("Invalid input. Try again."); system("pause\n");
        }
    }
}
