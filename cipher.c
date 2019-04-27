#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void passencrypt(char a[],int pass)
{
    int i;
    srand(pass);
    for(i=0;i<=3;i++)
    {
       a[i]=a[i]+(rand()%9+1);
    }
}
void passdecrypt(char a[],int pass)
{
    int i;
    srand(pass);
    for(i=0;i<=3;i++)
    {
       a[i]=a[i]-(rand()%9+1);
    }
}

int passcheck(char *file,int pass,char *password)
{

    FILE *fp;
    fp = fopen(file, "r");

    int i;
    char passstring[5];

    fseek(fp,-4,SEEK_END);
    fgets(passstring,5,fp);
    //printf("%s",passstring);

    passdecrypt(passstring,pass);
    printf("%s - %s",passstring,password);

    if(strcmp(passstring,password)==0)
    {
        fclose(fp);
        FILE *fo;
        fo=fopen(file,"r+");
        fseek(fo,-4,SEEK_END);
        fputc(EOF,fo);
        fclose(fo);
        return 1;
    }
    else
    {
        fclose(fp);
        return 0;
    }
}

void show(char *file)
{
	FILE *fp;
    fp = fopen(file, "r");

    printf("\n");

	char c = fgetc(fp);
	while (c != EOF)
	{
		printf ("%c", c);
		c = fgetc(fp);
	}

    printf("\n");
	fclose(fp);
}

void encrypt(char *file)
{
    FILE *fp,*fo;
    fp=fopen(file,"r");
    fo=fopen("temp.txt","w");
    char ch,password[5];

    int pass;
    printf("\nEnter the PIN : ");
    scanf("%d",&pass);
    sprintf(password,"%d",pass);

    int flag=0;
    srand(pass);
    while(1)
    {
        if((ch=fgetc(fp))!=EOF)
        {
             fputc(ch+(rand()%9+1),fo);
        }
        else
            break;
    }
    passencrypt(password,pass);
    fseek(fo,0,SEEK_CUR);
    fputs(password,fo);
    fclose(fp);
    fclose(fo);
    remove(file);
    rename("temp.txt",file);
}

void decrypt(char *file)
{
    FILE *fp,*fo;
    fp=fopen(file,"r");
    fo=fopen("temp.txt","w");

    int pass;
    char password[5],ch;

    printf("\nEnter the PIN : ");
    scanf("%d",&pass);
    sprintf(password,"%d",pass);

    if(passcheck(file,pass,password))
    {
        srand(pass);
        while(1)
        {
            if((ch=fgetc(fp))!=EOF)
            {
                fputc(ch-(rand()%9+1),fo);
            }
            else
                break;
        }
        fclose(fp);
        fclose(fo);
        remove(file);
        rename("temp.txt",file);
    }
    else
        {
            printf("\nWrong PIN !!!");
            fclose(fp);
            fclose(fo);
        }
}

void main()
{
    int user_choice;
    char *file_name = "test.txt";

    while(1)
    {
        printf("\n1.Encrypt\n2.Decrypt\n3.Show\n4.Quit\n");
        scanf("%d",&user_choice);
        if(user_choice==1)
            encrypt(file_name);
        if(user_choice==2)
            decrypt(file_name);
        if(user_choice==3)
            show(file_name);
        if(user_choice==4)
            break;

    }
}
