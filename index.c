#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

#define N 100
int TOTAL_USER, TOTAL_BLOG;
struct user
{
    char NAME[100];
    char PASS[100];
} USER[N];

struct blog
{
    char TITLE[100];
    char VIEW[1000];
    char AUTHOR[100];
} BLOG[N];

// FUNCTIONS PROTOTYPE
int login(char name[], char pass[]);
void CREATE_BLOG(char name[]);
void SHOW_IMG(char txtname[]);
void READ_BLOG(int Num);
void HOME(char name[]);
void DELETE_BLOG();
int USER_INFO();
int BLOG_INFO();
int signup();

int main()
{
    for (;;)
    {
        system("cls");
        SHOW_IMG("txt/intro.txt");
        printf("1. SIGN UP\n");
        printf("2. LOG IN\n");
        printf("3. ABOUT\n\n");
        printf("CHOOSE (1/2/3): ");
        int c;
        scanf("%d", &c);
        fflush(stdin);
        if (c == 1)
        {

            if (signup() == 1)
                printf("\n\nPLEASE WAIT");
            for (int i = 0; i < 2; i++)
            {
                printf(".");
                sleep(1);
            }
            printf("\nSUCCESSFULLY CREATED");
            for (int i = 0; i < 2; i++)
            {
                printf(".");
                sleep(1);
            }
        }
        else if (c == 3)
        {
            // ABOUT SECTION
            system("cls");
            SHOW_IMG("txt/about.txt");
            printf("\nABOUT US\n\n");
            printf("Blogpotro is a website that allows users who sign up for free profiles\n");
            printf("to explore extraordinary blogs from creative people\n");
            printf("SIGN UP NOW!!! www.blogpotro.com\n\n");
            for (int i = 0; i < 10; i++)
            {
                printf(".");
                sleep(1);
            }
        }
        else
        {
            TOTAL_USER = USER_INFO();
            TOTAL_BLOG = BLOG_INFO();
            printf("\n\n___________LOG IN____________\n");
            char name[100], pass[100];
            printf("\nEnter your name: ");
            gets(name);
            fflush(stdin);
            printf("\nEnter your password: ");
            gets(pass);
            fflush(stdin);
            if (login(name, pass) == 1)
            {
                printf("\nPLEASE WAIT");
                for (int i = 0; i < 3; i++)
                {
                    printf(".");
                    sleep(1);
                }
                HOME(name);
                continue;
            }

            else
            {
                printf("\nLOG IN FAILED!!!");
                for (int i = 0; i < 2; i++)
                {
                    sleep(1);
                }
            }
        }
    }
}

// FUNCTIONS

int login(char name[100], char pass[100])
{
    int flag = 1;
    for (int i = 0; i < TOTAL_USER; i++)
    {
        int verify_name = strcmp(name, USER[i].NAME);
        int verify_pass = strcmp(pass, USER[i].PASS);
        if (!verify_name && !verify_pass)
        {
            flag = 0;
        }
        else
        {
            flag = 1;
        }

        if (flag == 0)
            return 1;
    }
}

int signup()
{
    system("cls");
    SHOW_IMG("txt/signup.txt");
    FILE *signup = fopen("users.txt", "a");
    printf("\n\n___________SIGN UP___________\n");
    char newName[100], newPass[100];
    printf("\nSet your Name: ");
    gets(newName);
    fflush(stdin);
    printf("\nSet your Password: ");
    gets(newPass);
    fflush(stdin);
    fprintf(signup, "\n%s %s", newName, newPass);
    fclose(signup);
    return 1;
}

void HOME(char name[])
{
    for (;;)
    {
        system("cls");
        TOTAL_BLOG = BLOG_INFO();
        printf("___________WELCOME HOME %s____________\n\n", name);
        SHOW_IMG("txt/home.txt");
        printf("\n( 0 ) CREATE A BLOG");
        printf("\n(-2 ) DELETE A BLOG");
        printf("\n(-1 ) LOGOUT");
        printf("\n__________________________\n");
        for (int i = 0; i < TOTAL_BLOG; i++)
        {
            printf("\n");
            printf("%d : ", i + 1);
            printf("%s", BLOG[i].TITLE);
            printf("\n");
        }
        int c = 0;
        printf("\n\nCHOOSE: ");
        scanf("%d", &c);
        fflush(stdin);
        if (c > 0 && c <= 10)
        {
            READ_BLOG(c);
            char b;
            printf("\n\nPRESS ENTER TO GO BACK---->");
            scanf("%c", &b);
            continue;
        }
        else if (c == 0)
        {
            CREATE_BLOG(name);
        }
        else if (c == -1)
        {
            system("cls");
            printf("Logging out");
            for (int i = 0; i < 3; i++)
            {
                printf(".");
                sleep(1);
            }

            break;
        }
        else if (c == -2)
        {
            DELETE_BLOG();
            continue;
        }
        else
        {
            printf("OUT OF CONTEXT");
            for (int i = 0; i < 3; i++)
            {
                sleep(1);
            }
        }
    }
}

void READ_BLOG(int Num)
{
    system("cls");
    SHOW_IMG("txt/read.txt");
    printf("\n\n\n>   ");
    puts(BLOG[Num - 1].TITLE);
    printf("\n>   ");
    puts(BLOG[Num - 1].VIEW);
    printf("\n\n>   Written by ");
    puts(BLOG[Num - 1].AUTHOR);
}

int BLOG_INFO()
{
    // TITLE INFO
    FILE *blogFile = fopen("blogs.txt", "r");
    int i = 0, count = 0;
    while (!feof(blogFile))
    {
        fgets(BLOG[i].TITLE, 100, blogFile);
        count++;
        i++;
    }
    fclose(blogFile);

    // VIEW INFO
    FILE *blogView = fopen("view.txt", "r");
    i = 0;
    while (!feof(blogView))
    {
        fgets(BLOG[i].VIEW, 1000, blogView);
        i++;
    }
    fclose(blogView);

    // AUTHOR INFO
    FILE *blogAuthor = fopen("author.txt", "r");
    i = 0;
    while (!feof(blogAuthor))
    {
        fgets(BLOG[i].AUTHOR, 100, blogAuthor);
        i++;
    }
    fclose(blogAuthor);

    // SENDING BLOG COUNT
    return count;
}
int USER_INFO()
{
    FILE *userFile;
    userFile = fopen("users.txt", "r");
    int i = 0, count = 0;
    while (!feof(userFile))
    {
        fscanf(userFile, "%s %s", &USER[i].NAME, &USER[i].PASS);
        count++;
        i++;
    }
    fclose(userFile);
    return count;
}

void CREATE_BLOG(char name[])
{
    system("cls");
    SHOW_IMG("txt/create.txt");
    printf("\n\nWRITE YOUR TITLE: ");
    gets(BLOG[TOTAL_BLOG].TITLE);
    fflush(stdin);
    printf("\n\nWRITE YOUR BLOG: ");
    gets(BLOG[TOTAL_BLOG].VIEW);
    fflush(stdin);
    char title[100];
    char blog[1000];
    strcpy(title, BLOG[TOTAL_BLOG].TITLE);
    strcpy(blog, BLOG[TOTAL_BLOG].VIEW);

    // ADDING TITLE
    FILE *addTitle = fopen("blogs.txt", "a");
    fprintf(addTitle, "\n%s", title);
    fclose(addTitle);

    // ADDING VIEW
    FILE *addView = fopen("view.txt", "a");
    fprintf(addView, "\n%s", blog);
    fclose(addView);

    // ADDING AUTHOR
    FILE *addAuthor = fopen("author.txt", "a");
    fprintf(addAuthor, "\n%s", name);
    fclose(addAuthor);
}

void DELETE_BLOG()
{
    int NO;
    FILE *blogTitle = fopen("blogs.txt", "w");
    FILE *blogView = fopen("view.txt", "w");
    FILE *blogAuthor = fopen("author.txt", "w");
    printf("Which blog you want to delete?\nBlog No: ");
    scanf("%d", &NO);
    fflush(stdin);
    for (int k = NO - 1; k < TOTAL_BLOG; k++)
    {
        strcpy(BLOG[k].TITLE, BLOG[k + 1].TITLE);
        strcpy(BLOG[k].VIEW, BLOG[k + 1].VIEW);
        strcpy(BLOG[k].AUTHOR, BLOG[k + 1].AUTHOR);
        TOTAL_BLOG--;
    }
    char line1[100], line2[1000], line3[100];
    // DELETE TITLE
    for (int j = 0; j < TOTAL_BLOG; j++)
    {
        strcpy(line1, BLOG[j].TITLE);
        int i = 0;
        while (line1[i] != '\n')
        {
            fprintf(blogTitle, "%c", line1[i]);
            i++;
        }
        if (j < TOTAL_BLOG - 1)
        {
            fprintf(blogTitle, "\n");
        }
        else
        {
            fprintf(blogTitle, "\0");
        }
    }
    // DELETE VIEW
    for (int j = 0; j < TOTAL_BLOG; j++)
    {
        strcpy(line2, BLOG[j].VIEW);
        int i = 0;
        while (line2[i] != '\n')
        {
            fprintf(blogView, "%c", line2[i]);
            i++;
        }
        if (j < TOTAL_BLOG - 1)
        {
            fprintf(blogView, "\n");
        }
    }

    // DELETE AUTHOR
    for (int j = 0; j < TOTAL_BLOG; j++)
    {
        strcpy(line3, BLOG[j].AUTHOR);
        int i = 0;
        while (line3[i] != '\n')
        {
            fprintf(blogAuthor, "%c", line3[i]);
            i++;
        }
        if (j < TOTAL_BLOG - 1)
        {
            fprintf(blogAuthor, "\n");
        }
    }

    fclose(blogTitle);
    fclose(blogView);
    fclose(blogAuthor);

    printf("SUCCESSFULLY DELETED");
    for (int i = 0; i < 3; i++)
    {
        sleep(1);
    }
}

void SHOW_IMG(char txtname[])
{
    FILE *intr;

    intr = fopen(txtname, "r");

    char line[1000];
    while (fgets(line, sizeof(line), intr))
    {
        printf("%s", line);
    }
    fclose(intr);
}