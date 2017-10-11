#include <stdio.h>
#include <stdlib.h>
#define STRMSIZE 30

struct student
{
    char name[STRMSIZE];
    int ID;
    struct student *left,*right;
}*root;
struct student *newstd(char nme[STRMSIZE],int id);
struct student *lNode(struct student *n,char nme[STRMSIZE],int id);
struct student *rNode(struct student *n,char nme[STRMSIZE],int id);
struct student *insertstudent(struct student *nwstd,char nme[STRMSIZE],int id );
void idstudentsearch(struct student *stud,int id);
void namestudentsearch(struct student *stud,char nme[STRMSIZE]);
void studentdelete(struct student *treert,int id);
void display(struct student *stud);
int main()
{
    FILE *file;
    FILE *file2;
    struct student *treert=NULL;
    char name[STRMSIZE];
    char nmesrch[STRMSIZE];
    int i,id,stdnum,idsrch,iddel,choice;
    printf("\t\t\t\tStudent Directory\n\n");
    while(choice!=7)
    {
        printf("\t\t\t       ====================\n\nPlease choose an operation:\n----------------------------\n1-Insert student.\n2-Display students.\n3-Search student by Name.\n4-Search student by ID.\n5-Delete student.\n6-Input from an external file.\n7-Exit\n\nYour Choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
        {
            file2=fopen("input students.txt","a+");
            printf("\nPlease enter the number of students you need to insert:");
            scanf("%d",&stdnum);
            for(i=1; i<=stdnum; i++)
            {
                printf("Please enter the name of student #%d: ",i);
                scanf("%s",&name);
                printf("Please enter the ID of student #%d: ",i);
                scanf("%d",&id);
                fprintf(file2,"%s,%d\n",name,id);
                treert=insertstudent(treert,name,id);
            }
            printf("\nOperation done!\n");
            fclose(file2);
        }
        break;
        case 2:
        {
            display(treert);
        }
        break;
        case 3:
        {
            printf("\nPlease enter the name of the student you need to search for: ");
            scanf("%s",&nmesrch);
            namestudentsearch(treert,nmesrch);
        }
        break;
        case 4:
        {
            printf("\nPlease enter the ID of the student you need to search for: ");
            scanf("%d",&idsrch);
            idstudentsearch(treert,idsrch);
        }
        break;
        case 5:
        {
            printf("\nPlease enter the id of the student you need to delete: ");
            scanf("%d",&iddel);
            studentdelete(treert,iddel);
        }
        break;
        case 6:
        {
            file2=fopen("input students.txt","a+");
            while(!feof(file2))
            {
                fscanf(file2,"%[^,],%d\n",&name,&id);
                treert=insertstudent(treert,name,id);
                printf("\nName:%s\nID:%d",name,id);
            }
            printf("\n\nOperation done!\n");
            fclose(file2);
        }
        }
    }

    return 0;
}


struct student *newstd(char nme[STRMSIZE],int id)
{
    struct student *n;
    n=(struct student*)malloc(sizeof(struct student));
    strcpy(n->name,nme);
    n->ID=id;
    n->left=NULL;
    n->right=NULL;
    return n;
}
//struct student *lNode(struct student *n,char nme[STRMSIZE],int id)
//{
//    struct student *newstudent=newstd(nme,id);
//    n->left=newstudent;
//    return newstudent;
//}
//struct student *rNode(struct student *n,char nme[STRMSIZE],int id)
//{
//    struct student *newstudent=newstd(nme,id);
//    n->right=newstudent;
//    return newstudent;
//}
struct student *insertstudent(struct student *nwstd,char nme[STRMSIZE],int id )
{
    if(nwstd==NULL)
    {
        return newstd(nme,id);
    }
    else
    {
        if(id!=nwstd->ID)
        {
            if(strcmp(nme,nwstd->name)<0)
            {
                nwstd->left=insertstudent(nwstd->left,nme,id);
                return nwstd;
            }
            else if(strcmp(nme,nwstd->name)>0)
            {
                nwstd->right=insertstudent(nwstd->right,nme,id);
                return nwstd;
            }
            else if(strcmp(nme,nwstd->name)==0)
            {
                if(id>nwstd->ID)
                {
                    nwstd->right=insertstudent(nwstd->right,nme,id);
                    return nwstd;
                }
                else
                {
                    nwstd->left=insertstudent(nwstd->left,nme,id);
                    return nwstd;
                }
            }
        }
        else
        {
            printf("\nThe student already exists!\n\n");
            return nwstd;
        }
    }
}
void namestudentsearch(struct student *stud,char nme[STRMSIZE])
{
    while(stud)
    {
        if(strcmp(nme,stud->name)==0)
        {
            printf("\nStudent Found!");
            printf("\nName:%s\nID:%d\n",stud->name,stud->ID);
            return stud;
        }
        else if(strcmp(nme,stud->name)<0)
        {
            stud=stud->left;
        }
        else if(strcmp(nme,stud->name)>0)
        {
            stud=stud->right;
        }
    }
    printf("\nThe student doesn't exist!\n");
}
void idstudentsearch(struct student *stud,int id)
{
    while(stud)
    {
        if(id==stud->ID)
        {
            printf("\nStudent Found!");
            printf("\nName:%s\nID:%d\n",stud->name,stud->ID);
            return stud;
        }
        else if(id<stud->ID)
        {
            stud=stud->left;
        }
        else if(id>stud->ID)
        {
            stud=stud->right;
        }
    }
    printf("\nThe student doesn't exist!\n");
}
void studentdelete(struct student *treert,int id)
{
    struct student *current=treert,*temp=NULL;
    struct student *parent=NULL;
    if(!current)
    {
        printf("\nThis student doesn't exist!\n");
        return;
    }
    if(current->ID==id)
    {
        if(!current->right&&!current->left)
        {
            treert=NULL;
            free(current);
//            current->ID=NULL;
            printf("\nOperation done!\n");
        }
        else if(!current->right)
        {
            treert=current->left;
            free(current);
//            current->ID=NULL;
            printf("\nOperation done!\n");
        }
        else
        {
            temp=current->right;
            if(!temp->left)
            {
                temp->left=current->left;
            }
            else
            {
                while(temp->left)
                {
                    parent=temp;
                    temp=temp->left;
                }
                parent->left=temp->right;
                temp->left=current->left;
                temp->right=current->right;
            }
            treert=temp;
            free(current);
//            current->ID=NULL;
            printf("\nOperation done!\n");
        }
    }
    else if(id>current->ID)
    {
        return studentdelete(treert->right,id);
    }
    else if(id<current->ID)
    {
        return studentdelete(treert->left,id);
    }
}
void display(struct student *stud)
{
    if(stud==NULL)
    {
        return;
    }
    else
    {
        display(stud->left);
        printf("\n===========\nName: %s\nID: %d\n-----------\n",stud->name,stud->ID);
        display(stud->right);
    }
}
