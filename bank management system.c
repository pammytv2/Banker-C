#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
int i,j;
int main_exit;
struct user{
    char username[20];
    char password[20];


};
struct date{
    int month,day,year;

    };

struct  {
    char name[60];
    int acc_no, age;
    char address[60];
    char citizenship[15];
    double phone;
    char acc_type[10];
    float amt;
    struct date dob;
    struct date deposit;
    struct date withdraw;
    
   
    
    
    
} add, upd, check, rem, transaction;


float interest(float t,float amount,int rate)
{
    float SI;
    SI=(rate*t*amount)/100.0;
    return (SI);

}
void fordelay(int j)
{   int i,k;
    for(i=0;i<j;i++)
         k=i;
}
void add_user() {
    int choice;
    struct user u;

    char username[20];
    char password[20];

    printf("Enter a username: ");
    scanf("%s", username);

    FILE *user_file = fopen("users.dat", "r"); // พยายามเปิดไฟล์ผู้ใช้ในโหมดอ่าน

    if (user_file == NULL) {                   // หากไฟล์ไม่มีอยู่แล้ว จะสร้างไฟล์ใหม่ในโหมดเขียน
        user_file = fopen("users.dat", "w");
    } else {
        while (fread(&u, sizeof(u), 1, user_file) == 1) {         // กรณีไฟล์มีอยู่แล้ว ตรวจสอบว่าชื่อผู้ใช้ที่ป้อนเข้ามามีอยู่แล้วในไฟล์หรือไม่
            if (strcmp(u.username, username) == 0) {
                printf("Username already exists.\n");
                fclose(user_file);
                return;
            }
        }
        fclose(user_file);                                  //หากชื่อผู้ใช้ไม่ซ้ำกับในไฟล์ จะเปิดไฟล์ในโหมดเพิ่มเติม
        user_file = fopen("users.dat", "a");
    }

    printf("Enter a password: ");
    scanf("%s", password);                                  

    if (strlen(password) < 6) {                                    // ตรวจสอบว่าความยาวของรหัสผ่านมีอย่างน้อย 6 ตัวอักษรหรือไม่
        printf("Password must be at least 6 characters long.\n"); 
        fclose(user_file);
        return;
    }
                                                                    
    strcpy(u.username, username);                                       // เก็บชื่อผู้ใช้และรหัสผ่านลงในโครงสร้างผู้ใช้ใหม่
    strcpy(u.password, password);

    fwrite(&u, sizeof(u), 1, user_file);                                // เขียนโครงสร้างผู้ใช้ลงในไฟล์

    printf("User added successfully.\n");
    system("cls");
    system("color E");                                                  // แสดงเมนูหลัก
    printf("\n\n\t\t\tCUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM");
    printf("\n\n\n\t\t\t..................... WELCOME TO THE MAIN MENU .....................");
    printf("\n\n\t\t1.ADMIN\n\t\t2.USER\n\t\t7.Exit\n\n\n\n\n\t\t Enter your choice:");
    scanf("%d",&choice);

    system("cls");                                                                  
    switch(choice)
    {
        case 1:admin();
        break;
        case 2:user();
        break;
       
        case 7:close();
        break;

    }


    fclose(user_file);
}

    // ฟังก์ชั้นนี้ทำงานพิมพ์เพื่อตรวจสอบ username  password
void user(void) {
    char username[20];
    char password[20];
    int i = 0;

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your password: ");
    scanf("%s", password);
    // เปิดไฟล์ "users.dat" เพื่ออ่านข้อมูลผู้ใช้
    FILE *user_file = fopen("users.dat", "r");
    // ตรวจสอบว่าการเปิดไฟล์สำเร็จหรือไม่
    if (user_file == NULL) {
        printf("Error opening user file.\n");
        return;
    }
    // สร้าง struct user เพื่อเก็บข้อมูลผู้ใช้
    struct user u;
    // อ่านข้อมูลผู้ใช้จากไฟล์
    int found = 0;
    while (fread(&u, sizeof(u), 1, user_file) == 1) {
        // ตรวจสอบว่า username และ password ตรงกับข้อมูลในไฟล์หรือไม่
        if (strcmp(u.username, username) == 0 && strcmp(u.password, password) == 0) {
            found = 1;
            break;
        }
    }
     // ถ้าข้อมูลผู้ใช้ถูกต้อง แสดงข้อความ "Login successful." และเรียกใช้ฟังก์ชัน menu()
    if (found) {
        printf("Login successful.\n");  
         // แสดงจุดขึ้นบรรทัดใหม่เพื่อแสดงผล
        for(i=0;i<=6;i++) {
            fordelay(100000000);
            printf(".");
        }
        menu();

        // ถ้าข้อมูลผู้ใช้ไม่ถูกต้อง แสดงข้อความ "Invalid username or password."
    } else {
        printf("Invalid username or password.\n");
    }
     // ปิดไฟล์ "users.dat"
    fclose(user_file);
}

void new_acc()

{
    int choice;
    FILE *ptr;

    ptr=fopen("record.dat","a+");                             // เปิดไฟล์ record.dat เพื่อเขียน/อ่านข้อมูลบัญชี
    account_no:                                                 // ป้ายชื่อสำหรับการกลับไปทำงานบนบัญชีเดิมหากเลขบัญชีที่ผู้ใช้ป้อนมามีอยู่แล้ว
    system("cls");                                              // ล้างหน้าจอ
    printf("\t\t\t\xB2\xB2\xB2\ ADD RECORD \xB2\xB2\xB2\xB2");
    printf("\n\n\nEnter today's date(mm/dd/yyyy):");
    scanf("%d/%d/%d",&add.deposit.month,&add.deposit.day,&add.deposit.year);
    printf("\nEnter the account number:");
    scanf("%d",&check.acc_no);
    while(fscanf(ptr,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",&add.acc_no,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.address,add.citizenship,&add.phone,add.acc_type,&add.amt,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
    {
        if (check.acc_no==add.acc_no)
            {printf("Account no. already in use!");
            fordelay(1000000000);
                goto account_no; // กลับไปทำงานบนบัญชีเดิม

            }
    }           
    add.acc_no=check.acc_no;         
        printf("\nEnter the name:"); //รับข้อมูล
    scanf("%s",add.name);
    printf("\nEnter the date of birth(mm/dd/yyyy):");
    scanf("%d/%d/%d",&add.dob.month,&add.dob.day,&add.dob.year);
    printf("\nEnter the age:");
    scanf("%d",&add.age);
    printf("\nEnter the address:");
    scanf("%s",add.address);
    printf("\nEnter the citizenship number:");
    scanf("%s",add.citizenship);
    printf("\nEnter the phone number: ");
    scanf("%lf",&add.phone);
    printf("\nEnter the amount to deposit:$");
    scanf("%f",&add.amt);
    printf("\nType of account:\n\t#Saving\n\t#Current\n\t#Fixed1(for 1 year)\n\t#Fixed2(for 2 years)\n\t#Fixed3(for 3 years)\n\n\tEnter your choice:");
    scanf("%s",add.acc_type);

        fprintf(ptr,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.citizenship,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);


    fclose(ptr);
    printf("\nAccount created successfully!");  /*เขียนข้อมูลของบัญชีลงในไฟล์โดยใช้ฟังก์ชัน fprintf และปิดไฟล์ด้วยฟังก์ชัน fclose หลังจากนั้นจะมีการแสดงข้อความบนหน้าจอเพื่อแจ้งว่าบัญชีถูกสร้างขึ้นเรียบร้อยแล้ว จากนั้นตรวจสอบว่าผู้ใช้ต้องการกลับไปที่เมนูหลักหรือออกจากโปรแกรม โดยใช้คำสั่ง scanf และ goto ในการทำงานเหล่านี้ หากผู้ใช้ป้อนค่าที่ไม่ถูกต้อง จะแสดงข้อความว่า "Invalid!" และกลับไปทำงานใหม่ใน label add_invalid*/
    add_invalid:
    printf("\n\n\n\t\tEnter 1 to go to the main menu and 0 to exit:");
    scanf("%d",&main_exit);
    system("cls");
    if (main_exit==1)
        menu();
    else if(main_exit==0)
            close();
    else
        {
            printf("\nInvalid!\a");
            goto add_invalid;
        }
}   
    void view_list()  /* ฟังก์ชันนี้ใช้สำหรับแสดงรายชื่อบัญชีทั้งหมดที่อยู่ในไฟล์ */
{
    FILE *view;
    view=fopen("record.dat","r");
    int test=0;
    system("cls");
    printf("\nACC. NO.\tNAME\t\t\tADDRESS\t\t\tPHONE\n");

    while(fscanf(view,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",&add.acc_no,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.address,add.citizenship,&add.phone,add.acc_type,&add.amt,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
       {
           printf("\n%6d\t %10s\t\t\t%10s\t\t%.0lf",add.acc_no,add.name,add.address,add.phone);
           test++;
       }

    fclose(view);
    if (test==0)
        {   system("cls");
            printf("\nNO RECORDS!!\n");}

    view_list_invalid:
     printf("\n\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d",&main_exit);
        system("cls");
        if (main_exit==1)
            menu();
        else if(main_exit==0)
            close();
        else
        {
            printf("\nInvalid!\a");
            goto view_list_invalid;
        }
}
/*ฟังก์ชัน edit() ใช้สำหรับแก้ไขข้อมูลลูกค้าในไฟล์ record.dat โดยการรับเลขบัญชีลูกค้าที่ต้องการแก้ไข จากนั้นอ่านข้อมูลลูกค้าทั้งหมดจากไฟล์ record.dat และตรวจสอบเลขบัญชีที่ผู้ใช้ต้องการแก้ไขว่ามีอยู่ในไฟล์หรือไม่ 
หากมีก็ให้ผู้ใช้เลือกว่าต้องการแก้ไขที่อยู่หรือเบอร์โทรศัพท์ จากนั้นแก้ไขข้อมูลและบันทึกในไฟล์ new.dat ถ้าเลขบัญชีที่ผู้ใช้ต้องการแก้ไขไม่มีในไฟล์ record.dat จะแสดงข้อความว่า "Record not found!!" และให้ผู้ใช้เลือกว่าจะลองใหม่ กลับไปเมนูหลัก หรือออกจากโปรแกรม 
โดยใช้ตัวแปร main_exit ในการรับค่าเลือกของผู้ใช้และใช้คำสั่ง goto เพื่อกระโดดไปยังป้ายกำกับ (label) edit_invalid และป้ายกำกับ (label) edit_success ในกรณีอื่น ๆ หลังจากแก้ไขข้อมูลเสร็จสิ้น ฟังก์ชันจะแสดงข้อความ "Changes saved!" และให้ผู้ใช้เลือกว่าจะกลับไปเมนูหลักหรือออกจากโปรแกรม โดยใช้ตัวแปร main_exit และคำสั่ง scanf() เพื่อรับค่าเลือกของผู้ใช้ 
สุดท้าย ฟังก์ชันจะปิดไฟล์ record.dat และ new.dat โดยใช้คำสั่ง fclose() และลบไฟล์ record.dat และเปลี่ยนชื่อไฟล์ new.dat เป็น record.dat โดยใช้คำสั่ง remove() และ rename() ตามลำดับ*/

void edit(void)
{
    int choice,test=0;
    FILE *old,*newrec;
    old=fopen("record.dat","r");
    newrec=fopen("new.dat","w");

    printf("\nEnter the account no. of the customer whose info you want to change:");
    scanf("%d",&upd.acc_no);
    while(fscanf(old,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",&add.acc_no,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.address,add.citizenship,&add.phone,add.acc_type,&add.amt,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
    {
        if (add.acc_no==upd.acc_no)
        {   test=1;
            printf("\nWhich information do you want to change?\n1.Address\n2.Phone\n\nEnter your choice(1 for address and 2 for phone):");
            scanf("%d",&choice);
            system("cls");
            if(choice==1)
                {printf("Enter the new address:");
                scanf("%s",upd.address);
                fprintf(newrec,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,upd.address,add.citizenship,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
                system("cls");
                printf("Changes saved!");
                }
            else if(choice==2)
                {
                    printf("Enter the new phone number:");
                scanf("%lf",&upd.phone);
                fprintf(newrec,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.citizenship,upd.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
                system("cls");
                printf("Changes saved!");
                }

        }
        else
            fprintf(newrec,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.citizenship,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
    }
    fclose(old);
    fclose(newrec);
    remove("record.dat");
    rename("new.dat","record.dat");

if(test!=1)
        {   system("cls");
            printf("\nRecord not found!!\a\a\a");
            edit_invalid:
              printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
              scanf("%d",&main_exit);
              system("cls");
                 if (main_exit==1)

                    menu();
                else if (main_exit==2)
                    close();
                else if(main_exit==0)
                    edit();
                else
                    {printf("\nInvalid!\a");
                    goto edit_invalid;}
        }
    else
        {printf("\n\n\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d",&main_exit);
        system("cls");
        if (main_exit==1)
            menu();
        else
            close();
        }
}

/*ซึ่งดูเหมือนจะนำมาใช้ในการดำเนินการธุรกรรมทางการเงิน ฟังก์ชันอ่านข้อมูลจากไฟล์ชื่อ "record.dat" ที่มีข้อมูลเกี่ยวกับลูกค้าธนาคาร แล้วให้ผู้ใช้ป้อนหมายเลขบัญชี แล้วค้นหาหมายเลขบัญชีนั้นในไฟล์ หากพบหมายเลขบัญชี ฟังก์ชันจะให้ผู้ใช้เลือกว่าจะฝากหรือถอนเงินจากบัญชี จากนั้นฟังก์ชันจะอัปเดตข้อมูลบัญชีในไฟล์ตามที่ผู้ใช้เลือก

ฟังก์ชันใช้โครงสร้างที่เรียกว่า "add" เพื่อเก็บข้อมูลลูกค้าที่อ่านจากไฟล์ และโครงสร้างอื่นที่เรียกว่า "transaction" เพื่อเก็บหมายเลขบัญชีและจำนวนเงินที่จะถอนหรือฝาก

ฟังก์ชันเปิดพอยน์เตอร์ไฟล์สองตัว คือ "old" และ "newrec" เพื่ออ่านจากไฟล์เก่าและเขียนลงในไฟล์ใหม่ที่เรียกว่า "new.dat" ฟังก์ชันอ่านข้อมูลลูกค้าจากไฟล์ "old" โดยใช้ fscanf () และเขียนข้อมูลลูกค้าที่อัปเดตไปยังไฟล์ "newrec" โดยใช้ fprintf () 
ในท้ายที่สุดฟังก์ชันลบไฟล์ "record.dat" และเปลี่ยนชื่อ "new.dat" เป็น "record.dat" เพื่ออัปเดตข้อมูลลูกค้าในไฟล์ต้นฉบับ*/
void transact(void)
{   int choice,test=0;
    FILE *old,*newrec;
    old=fopen("record.dat","r");
    newrec=fopen("new.dat","w");

        printf("Enter the account no. of the customer:");
    scanf("%d",&transaction.acc_no);
    while (fscanf(old,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",&add.acc_no,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.address,add.citizenship,&add.phone,add.acc_type,&add.amt,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
   {

            if(add.acc_no==transaction.acc_no)
            {   test=1;
                if(strcmpi(add.acc_type,"fixed1")==0||strcmpi(add.acc_type,"fixed2")==0||strcmpi(add.acc_type,"fixed3")==0)
                {
                    printf("\a\a\a\n\nYOU CANNOT DEPOSIT OR WITHDRAW CASH IN FIXED ACCOUNTS!!!!!");
                    fordelay(1000000000);
                    system("cls");
                    menu();

                }
                printf("\n\nDo you want to\n1.Deposit\n2.Withdraw?\n\nEnter your choice(1 for deposit and 2 for withdraw):");
                scanf("%d",&choice);
                if (choice==1)
                {
                    printf("Enter the amount you want to deposit:$ ");
                    scanf("%f",&transaction.amt);
                    add.amt+=transaction.amt;
                    fprintf(newrec,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.citizenship,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
                    printf("\n\nDeposited successfully!");
                }
                else
                {
                    printf("Enter the amount you want to withdraw:$ ");
                    scanf("%f",&transaction.amt);
                    add.amt-=transaction.amt;
                    fprintf(newrec,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.citizenship,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
                    printf("\n\nWithdrawn successfully!");
                }

            }
            else
            {
               fprintf(newrec,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.citizenship,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
            }
   }
   fclose(old);
   fclose(newrec);
   remove("record.dat");
   rename("new.dat","record.dat");
   if(test!=1)
   {
       printf("\n\nRecord not found!!");
       transact_invalid:
      printf("\n\n\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
      scanf("%d",&main_exit);
      system("cls");
      if (main_exit==0)
        transact();
    else if (main_exit==1)
        menu();
    else if (main_exit==2)
        close();
    else
    {
        printf("\nInvalid!");
        goto transact_invalid;
    }

   }
   else
   {
       printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d",&main_exit);
        system("cls");
        if (main_exit==1)
            menu();
        else
            close();
   }

}
/*erase" ซึ่งดูเหมือนจะมีการลบบันทึกลูกค้าของธนาคาร ฟังก์ชันอ่านข้อมูลจากไฟล์ที่ชื่อ "record.dat" ซึ่งมีข้อมูลเกี่ยวกับลูกค้าของธนาคาร และจะแสดงข้อความให้ผู้ใช้ป้อนหมายเลขบัญชี จากนั้นค้นหาหมายเลขบัญชีนั้นในไฟล์ หากพบหมายเลขบัญชี ฟังก์ชันจะลบบันทึกของลูกค้าออกจากไฟล์โดยเขียนบันทึกอื่น ๆ ไปยังไฟล์ใหม่ที่ชื่อ "new.dat" โดยไม่รวมบันทึกที่มีหมายเลขบัญชีที่ต้องการลบออก

ฟังก์ชันใช้ struct ที่ชื่อว่า "add" เพื่อเก็บข้อมูลของลูกค้าที่อ่านจากไฟล์ และ struct อีกตัวที่ชื่อว่า "rem" เพื่อเก็บหมายเลขบัญชีที่จะลบ

ฟังก์ชันเปิด pointer ไฟล์สองตัว คือ "old" และ "newrec" เพื่ออ่านไฟล์เก่าและเขียนไฟล์ไปยังไฟล์ใหม่ที่ชื่อ "new.dat" ฟังก์ชันอ่านข้อมูลลูกค้าจากไฟล์เก่าโดยใช้ fscanf() และเขียนข้อมูลลูกค้า (ยกเว้นที่ต้องการลบ) ไปยังไฟล์ "newrec" โดยใช้ fprintf() สุดท้าย ฟังก์ชันลบไฟล์ "record.dat" 
และเปลี่ยนชื่อไฟล์ "new.dat" เป็น "record.dat" เพื่ออัพเดทข้อมูลลูกค้าในไฟล์เดิม*/
void erase(void)
{
    FILE *old,*newrec;
    int test=0;
    old=fopen("record.dat","r");
    newrec=fopen("new.dat","w");
    printf("Enter the account no. of the customer you want to delete:");
    scanf("%d",&rem.acc_no);
    while (fscanf(old,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",&add.acc_no,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.address,add.citizenship,&add.phone,add.acc_type,&add.amt,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
   {
        if(add.acc_no!=rem.acc_no)
            fprintf(newrec,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.citizenship,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);

        else
            {test++;
            printf("\nRecord deleted successfully!\n");
            }
   }
   fclose(old);
   fclose(newrec);
   remove("record.dat");
   rename("new.dat","record.dat");
   if(test==0)
        {
            printf("\nRecord not found!!\a\a\a");
            erase_invalid:
              printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
              scanf("%d",&main_exit);

                 if (main_exit==1)
                    menu();
                else if (main_exit==2)
                    close();
                else if(main_exit==0)
                    erase();
                else
                    {printf("\nInvalid!\a");
                    goto erase_invalid;}
        }
    else
        {printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d",&main_exit);
        system("cls");
        if (main_exit==1)
            menu();
        else
            close();
        }

}

void see(void)
{
    FILE *ptr;
    int test=0,rate;
    int choice;
    float time;
    float intrst;
    ptr=fopen("record.dat","r");
    printf("Do you want to check by\n1.Account no\n2.Name\nEnter your choice:");
    scanf("%d",&choice);
    if (choice==1)
    {   printf("Enter the account number:");
        scanf("%d",&check.acc_no);

        while (fscanf(ptr,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",&add.acc_no,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.address,add.citizenship,&add.phone,add.acc_type,&add.amt,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
        {
            if(add.acc_no==check.acc_no)
            {   system("cls");
                test=1;

                printf("\nAccount NO.:%d\nName:%s \nDOB:%d/%d/%d \nAge:%d \nAddress:%s \nCitizenship No:%s \nPhone number:%.0lf \nType Of Account:%s \nAmount deposited:$ %.2f \nDate Of Deposit:%d/%d/%d\n\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.citizenship,add.phone,
                add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
                if(strcmpi(add.acc_type,"fixed1")==0)
                    {
                        time=1.0;
                        rate=9;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $%.2f as interest on %d/%d/%d",intrst,add.deposit.month,add.deposit.day,add.deposit.year+1);
                    }
                else if(strcmpi(add.acc_type,"fixed2")==0)
                    {
                        time=2.0;
                        rate=11;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d/%d/%d",intrst,add.deposit.month,add.deposit.day,add.deposit.year+2);

                    }
                else if(strcmpi(add.acc_type,"fixed3")==0)
                    {
                        time=3.0;
                        rate=13;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d/%d/%d",intrst,add.deposit.month,add.deposit.day,add.deposit.year+3);

                    }
                 else if(strcmpi(add.acc_type,"saving")==0)
                    {
                        time=(1.0/12.0);
                        rate=8;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d of every month",intrst,add.deposit.day);

                     }
                 else if(strcmpi(add.acc_type,"current")==0)
                    {

                        printf("\n\nYou will get no interest\a\a");

                     }

            }
        }
    }
    else if (choice==2)
    {   printf("Enter the name:");
        scanf("%s",&check.name);
        while (fscanf(ptr,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",&add.acc_no,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.address,add.citizenship,&add.phone,add.acc_type,&add.amt,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
        {
            if(strcmpi(add.name,check.name)==0)
            {   system("cls");
                test=1;
                printf("\nAccount No.:%d\nName:%s \nDOB:%d/%d/%d \nAge:%d \nAddress:%s \nCitizenship No:%s \nPhone number:%.0lf \nType Of Account:%s \nAmount deposited:$%.2f \nDate Of Deposit:%d/%d/%d\n\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.citizenship,add.phone,
                add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
                if(strcmpi(add.acc_type,"fixed1")==0)
                    {
                        time=1.0;
                        rate=9;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d/%d/%d",intrst,add.deposit.month,add.deposit.day,add.deposit.year+1);
                    }
                else if(strcmpi(add.acc_type,"fixed2")==0)
                    {
                        time=2.0;
                        rate=11;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d/%d/%d",intrst,add.deposit.month,add.deposit.day,add.deposit.year+2);

                    }
                else if(strcmpi(add.acc_type,"fixed3")==0)
                    {
                        time=3.0;
                        rate=13;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d/%d/%d",intrst,add.deposit.month,add.deposit.day,add.deposit.year+3);

                    }
                 else if(strcmpi(add.acc_type,"saving")==0)
                    {
                        time=(1.0/12.0);
                        rate=8;
                        intrst=interest(time,add.amt,rate);
                        printf("\n\nYou will get $.%.2f as interest on %d of every month",intrst,add.deposit.day);

                     }
                 else if(strcmpi(add.acc_type,"current")==0)
                    {

                        printf("\n\nYou will get no interest\a\a");

                     }

            }
        }
    }


    fclose(ptr);
     if(test!=1)
        {   system("cls");
            printf("\nRecord not found!!\a\a\a");
            see_invalid:
              printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
              scanf("%d",&main_exit);
              system("cls");
                 if (main_exit==1)
                    menu();
                else if (main_exit==2)
                    close();
                else if(main_exit==0)
                    see();
                else
                    {
                        system("cls");
                        printf("\nInvalid!\a");
                        goto see_invalid;}
        }
    else
        {printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d",&main_exit);}
        if (main_exit==1)
        {
            system("cls");
            menu();
        }

        else
           {

             system("cls");
            close();
            }

}


void close_program(void)
{
    printf("\n\n\n\nThis C Mini Project is developed by Code With C team!");
}

/*นี้เป็นเมนูหลักสำหรับระบบบริหารจัดการบัญชีธนาคารของลูกค้า โดยเมนูนี้จะแสดงตัวเลือกที่สามารถเลือกได้หลายรายการ เช่น สร้างบัญชีใหม่ อัปเดตข้อมูลบัญชีเดิม ทำธุรกรรม 
ตรวจสอบรายละเอียดของบัญชีที่มีอยู่ ลบบัญชีที่มีอยู่ และออกจากระบบ*/
void menu (void)
{   
    int choice;
    system("cls");
    system("color 9");
    printf("\n\n\t\t\tCUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM");
    printf("\n\n\n\t\t\t..................... WELCOME TO THE MAIN MENU .....................");
    printf("\n\n\t\t1.Create new account\n\t\t2.Update information of existing account\n\t\t3.For transactions\n\t\t4.Check the details of existing account\n\t\t5.Removing existing account\n\t\t6.MUNE admin AND user\n\t\t7.Exit\n\n\n\n\n\t\t Enter your choice:");
    scanf("%d",&choice);

    system("cls");
    switch(choice)
    {
        case 1:new_acc();
        break;
        case 2:edit();
        break;
        case 3:transact();
        break;
        case 4:see();
        break;
        case 5:erase();
        break;
        case 6: adminuser();
        break;
        case 7:close_program();
        break;
    }
}

void menuadmid (void)
{   int choice;
    system("cls");
    system("color 4");
    printf("\n\n\t\t\tCUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM");
    printf("\n\n\n\t\t\t..................... WELCOME TO THE MAIN MENU .....................");
    printf("\n\n\t\t1.Create new account\n\t\t2.Update information of existing account\n\t\t3.For transactions\n\t\t4.Check the details of existing account\n\t\t5.Removing existing account\n\t\t6.View customer's list\n\t\t7.MUNE ADDUserand password \n\t\t8.MUNE admin AND user \n\t\t9.Exit\n\n\n\n\n\t\t Enter your choice:");
    scanf("%d",&choice);

    system("cls");
    switch(choice)
    {
        case 1:new_acc();
        break;
        case 2:edit();
        break;
        case 3:transact();
        break;
        case 4:see();
        break;
        case 5:erase();
        break;
        case 6:view_list();
        break;
        case 7: add_user();
        break;
        case 8: adminuser();
        break;
        case 9:close();
        break;

    }



}

// เมนูเลือก user admin
void adminuser (void){
    int choice;
    system("cls");
    system("color E");
    printf("\n\n\t\t\tCUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM");
    printf("\n\n\n\t\t\t..................... WELCOME TO THE MAIN MENU .....................");
    printf("\n\n\t\t1.ADMIN\n\t\t2.USER\n\t\t7.Exit\n\n\n\n\n\t\t Enter your choice:");
    scanf("%d",&choice);

    system("cls");
    switch(choice)
    {
        case 1:admin();
        break;
        case 2:user();
        break;
       
        case 7:close();
        break;

    }


}

/*void user(void){
    char pass[20],password[20]="user";
    int i=0;
    printf("\n\n\t\tEnter the password to login:");
    scanf("%s",pass);
    
    if (strcmp(pass,password)==0) {
        printf("\n\nPassword Match!\nLOADING");
        for(i=0;i<=6;i++) {
            fordelay(100000000);
            printf(".");
        }
        system("cls");
        login();
    } else {
        printf("\n\nWrong password!!\a\a\a");
        login_try:
        printf("\nEnter 1 to try again and 0 to exit:");
        scanf("%d",&main_exit);
        if (main_exit==1) {
            system("cls");
            main();
        } else if (main_exit==0) {
            system("cls");
            close();
        } else {
            printf("\nInvalid!");
            fordelay(1000000000);
            system("cls");
            goto login_try;
        }
    }
}
*/


//เมนูadmin ตรวจสอบรหัสผ่าน
void admin(void){
     char pass[10],password[10]="admin";
    int i=0;
    printf("\n\n\t\tEnter the password to login:");
    scanf("%s",pass);
    /*do
    {
    //if (pass[i]!=13&&pass[i]!=8)
        {
            printf("*");
            pass[i]=getch();
            i++;
        }
    }while (pass[i]!=13);
    pass[10]='\0';*/
    if (strcmp(pass,password)==0)
        {printf("\n\nPassword Match!\nLOADING");
        for(i=0;i<=6;i++)
        {
            fordelay(100000000);
            printf(".");
        }
                system("cls");
            menuadmid();
        }
    else
        {   printf("\n\nWrong password!!\a\a\a");
            login_try:
            printf("\nEnter 1 to try again and 0 to exit:");
            scanf("%d",&main_exit);
            if (main_exit==1)
                    {

                        system("cls");
                        menuadmid();
                    }

            else if (main_exit==0)
                    {
                    system("cls");
                    close();}
            
            else
                    {printf("\nInvalid!");
                    fordelay(1000000000);
                    system("cls");
                    goto login_try;}

        }




}
int main()
{
    adminuser();
    
    //new_login();
    //add_user();
    //login();



        return 0;
}
