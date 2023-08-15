#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SUCCESS 1
#define UNSUCCESS 0

/*
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
TO ADD NEW USER -> 
    1- CREATE STRUCTURE OBJECT
    2- INCREMENT MEMORY SIZE VAR
    3- ADD STRING OF USERNAME 
    TO CREATE_ID()
    4- ADD LONG LONG VAR OF PASSCODE
    TO CREATE_ID()
    5- CREATE ID USING THESE VAR
    6- APPEND THE USER OBJECT TO 
    MEMORY
    7- INCREMENT MEM INDEX VAR
    8- ADD COMPARE STATEMENT INTO 
    LOGINVALIDATION()
    **DONT FORGET THE IF STATEMENTS
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

/*Structure of ID*/
struct userId
{
    char username[20];
    long long passcode;
};

/*Structure objects - users of the software*/
struct userId admin;
struct userId id1;

/*Structure data structure + index - Memory of users*/
const int memSize = 2;
struct userId user_memory[2];
//memory length is small so no need for using a pointer
//memory length is small and fixed so no need for dynamic memory allocation

/*
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
* !! Maybe with dynamic mem allocation -> no need for a fixed mem size
* !! and we can assign it a variable => delete 2nd to-do in add new  
* !! user list
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

static int memIndex = 0;


/*
* Creating the ids of all users
*/
int createId()
{
    /*admin user*/
    char admin_username[] = "admin";
    long long admin_passcode = 123456;

    int i;
    int size0 = strlen(admin_username);

    for(i=0; i<size0; i++)
        admin.username[i] = admin_username[i];
    
    admin.passcode = admin_passcode;

    /*------------------------------------------------*/

    /*user 1 - Kemal Suner*/
    char id1_username[] = "admin2";
    long long id1_passcode = 123456; 

    int x;
    int size1 = strlen(id1_username);

    for(x=0; x<size1; x++)
        id1.username[x] = id1_username[x];

    id1.passcode = id1_passcode;

    /*------------------------------------------------*/
    
    return SUCCESS;
}

/*
* Appending all users to the global memory for a validation check later on
*/
int append()
{
    /*
    * while index is less than size:
    * + add structe object to the memory
    * + increment memory index
    */
    while(memIndex < memSize)
    {
        /*admin user*/
        user_memory[memIndex] = admin;
        memIndex++;

        /*1st user*/
        user_memory[memIndex] = id1;
        memIndex++;
    }

    return SUCCESS;
}

/*
* Introduction printed at the beginning
*/
void printIntro()
{
    printf("#############################################\n");

    printf("  ---Welcome to encryptor-decryptor 3.1---\n");
    printf("\n");
    printf("     ---Created by Efe Suner - 2021---\n");

    printf("############################################\n");

    printf("\n");

    printf("---Please enter your user details: \n");
}

/*
* User validation check:
* + compare user_id_var(s) and parameter var
* + create temporary passcode(s)
* + if parameter var(s) and the same id username and passcode 
* matches --> return SUCCESS
* + otherwise UNSUCCESS is returned
*/
int loginValidation(char str[], long long code)
{
    /*Comparision of username*/
    int compare0 = strcmp(str, admin.username); //admin
    int compare1 = strcmp(str, id1.username); //id1

    /*Temporary variables for user passscodes*/
    long long temp0 = admin.passcode; //admin
    long long temp1 = id1.passcode; //id1

    /*Validation part*/
    if((compare0 == 0 && temp0 == code) || (compare1 == 0 && temp1 == code))
        return SUCCESS;
    else return UNSUCCESS;
}

/*
* Introduction printed after a successful login
*/
void printWelcome()
{
    printf("---Please choose the operation you want to execute: \n");
    printf("1- Encryption\n");
    printf("2- Decryption\n");

    printf("--> ");
}

/*
* Introduction printed after the user chooses the encryption option
*/
void printEncrypt_intro()
{
    printf("\n\n---Please enter the path of the file you wanna encrypt:\n");
    printf("\n");
    printf("If the file is in this directory --> just enter the name of the file!\n");
    printf("(Including the file extension --> .txt)\n");

    printf("--> ");
}

/*
* Introduction printed after the user chooses the decryption option
*/
void printDecrypt_intro()
{
    printf("\n\n---Please enter the path of the file you wanna decrypt:\n");
    printf("\n");
    printf("If the file is in this directory --> just enter the name of the file!\n");
    printf("(Including the file extension --> .txt)\n");

    printf("--> ");
}

/*
* Encryption Algorithm:
* key = 3
*/
char encrypt_char(char c)
{
    int key = 3;
    
    c = c + key;

    return c;
}

/*
* Decryption Algorithm:
* key = 3
*/
char decrypt_char(char c)
{
    int key = 3;
    
    c = c - key;

    return c;
}

/*
* Operations Done on the Files:
* + get file path
* + create enc file
* + open files
* + print original version
* + encrypt
* + write on enc file
*/
int fileEncryptor()
{
    char ch0, ch1;

    /*get the path of the file you want to operate on*/
    char filePath[100];
    scanf("%s", filePath);

    printf("\n");   //for terminal design

    /*create file pointers and open the files*/
    FILE *fp0, *fp1;
    fp0 = fopen(filePath, "r");
    fp1 = fopen("encrypted.txt", "w");

    /*check if file is empty or not*/
    if(fp0 == NULL)
	{
		printf("\nCannot open files!\n");
		exit(-1);
        return UNSUCCESS;
	}
    else 
    {
        printf("---File opening is successful---\n\n");
        printf("Original version:\n\n");

        /*operate on the file*/

        /*
        * + print the unencrypted version
        *
        * Encrption Process:
        * + encryption call (returns encrypted char)
        * + write enc_char into another file 
        * + continue to get char
        * + print success or unsuccess
        */
        ch0 = getc(fp0);
        while(ch0 != EOF)
        {
            printf("%c", ch0);
            ch1 = encrypt_char(ch0);
            putc(ch1, fp1);
            ch0 = getc(fp0);
        }

        printf("\n");   //for terminal design

        printf("\n---Encryption successful---");

        printf("\n\n---Encrypted text is successfuly copied to encrypted.txt--\n");

        /*close the files*/
        fclose(fp0);
        fclose(fp1);
    }

    return SUCCESS;
}

/*
* Operations Done on the Files:
* + get file path
* + create enc file
* + open files
* + print original version
* + encrypt
* + write on enc file
*/
int fileDecryptor()
{
    char ch0, ch1;

    /*get the path of the file you want to operate on*/
    char filePath[100];
    scanf("%s", filePath);

    printf("\n");   //for terminal design

    /*create file pointers and open the files*/
    FILE *fp0, *fp1;
    fp0 = fopen(filePath, "r");
    fp1 = fopen("decrypted.txt", "w");

    /*check if file is empty or not*/
    if(fp0 == NULL)
	{
		printf("\nCannot open files!\n");
		exit(-1);
        return UNSUCCESS;
	}
    else 
    {
        printf("---File opening is successful---\n\n");
        printf("Original version:\n\n");

        /*operate on the file*/

        /*
        * + print the undecrypted version
        *
        * Decryption Process:
        * + decryption call (returns decrypted char)
        * + write dec_char into another file 
        * + continue to get char
        * + print success or unsuccess
        */
        ch0 = getc(fp0);
        while(ch0 != EOF)
        {
            printf("%c", ch0);
            ch1 = decrypt_char(ch0);
            putc(ch1, fp1);
            ch0 = getc(fp0);
        }

        printf("\n");   //for terminal design

        printf("\n---Decryption successful---");

        printf("\n\n---Decrypted text is successfuly copied to decrypted.txt--\n");

        /*close the files*/
        fclose(fp0);
        fclose(fp1);
    }

    return SUCCESS;
}

/*
* Ending method for quiting or proceeding the software
* + print statements
* + get user choice
* + exceed the choice 
*/
int ending()
{
    /*print statements for introduction*/
    printf("\nWhat would you like to do next:\n");
    printf("1- Encryption\n");
    printf("2- Decryption\n");
    printf("3- Quit\n");

    printf("-->");

    /*get choice*/
    int wish;
    scanf("%d", &wish);

    /*Encryption choice*/
    if(wish == 1)
    {
        printEncrypt_intro();
        fileEncryptor();
        ending();
    }
    /*Decryption choice*/
    if(wish == 2)
    {
        printDecrypt_intro();
        fileDecryptor();
        ending();
    }
    /*Quit choice*/
    if(wish == 3)
    {
        while(3)
            break;
    }

    return SUCCESS;
}

/*
* Operation selector for user:
* + get user input of choice
* + 1 --> encryption: 
*   + print encryption introduction (call)
*   + file_encryptor() method call
* + 2 --> decryption:
*   + print decryption introduction (call)
*   + file_decryptor() method call
*/
int operationSelector()
{
    /*get user input of choice*/
    int choice;
    scanf("%d", &choice);

    switch(choice)
    {
        /*encryption choice*/
        case 1:
            printEncrypt_intro();
            fileEncryptor();
            ending();
            break;
        
        /*decryption choice*/ 
        case 2:
            printDecrypt_intro();
            fileDecryptor();
            ending();
            break;
    }

    return SUCCESS;
}

/*
* Login process for users:
* + get username
* + get passcode
* + check validity --> if both compare = 1 -> continue on operationSelector()
* + else try again
*/
int userLogin()
{
    /*get username & passcode*/
    char username_input[10];
    long long pass_input;

    printf("username: "); 
    scanf("%s", username_input);
    //%s is chosen becasuse we dont want an input with spaces
    printf("passcode: "); 
    scanf("%lld", &pass_input);

    printf("\n---Your details are being checked for validity---\n\n");

    /*check validity*/
    int valid_rslt = loginValidation(username_input, pass_input);
 
    if(valid_rslt == SUCCESS)
    {
        /*print success*/
        printf("----------------------");
        printf("\n---Login successful---\n");
        printf("----------------------\n\n");

        /*call printWelcome()*/
        printWelcome();

        /*call operationSelector()*/
        operationSelector();
    }
    else
    {
        printf("----------------------------------------");
        printf("\n---Your username or passcode is wrong---");
        printf("\n---Please try again---\n");
        printf("----------------------------------------\n");
    }

    return SUCCESS;
}

/*
* The main function of the whole program
*/
int main()
{
    /*
    * Background activities that must happen in each execution:
    * + creation of user_id(s)
    * + appending users into memory
    */
    createId();
    append();

    /*Introduction text printed at the beginning*/
    printIntro();

    /*
    * Login proccess for users
    * Validity check being done on input_information
    */
    userLogin();
    
    return 0;
}
