/*BT20CSE001
  A Sai Siddardha*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int free_count = 1, alloc_count = 0; 

typedef struct free_tag    //for Roots
{
    int index;
    int count;
    int size;
    struct free_tag *next;
}Free;
Free *free_head = NULL, *free_prev = NULL;

typedef struct alloc_tag    //for Processes
{
    int root_id;
    int index;
    int size;
    struct alloc_tag *next; 
}Alloc;
Alloc *alloc_head = NULL, *prev_alloc = NULL;

void create_free(int c)
{
    Free* p = (Free*)malloc(sizeof(Free));
    p->size = c;
    p->index = free_count;
    p->count = 0;
    p->next = NULL;
    
    if (free_head == NULL)
    {
        free_head = p;
    }
    else
    {
        free_prev->next = p;
    }
    free_prev = p;
    free_count++;
}

void print_free()
{
    Free* p = free_head;
    printf("root_ID\tcount\tfree_Size\n");
    while (p != NULL) 
    {
        printf("%d \t %d \t %d\n" ,p->index, p->count, p->size);
        p = p->next;
    }
}

void print_alloc()
{
    Alloc* p = alloc_head;
    printf("index\troot_ID\tSize\n");
    while (p != NULL) 
    {
        printf("%d \t %d  \t  %d\n",p->index,p->root_id,p->size);
        p = p->next;
    }
}

void create_alloc(int c)
{
    Alloc* q = (Alloc*)malloc(sizeof(Alloc));
    q->size = c;
    q->index = alloc_count;
    q->next = NULL;
    Free* p = free_head;

    while (p != NULL) 
    {
        if (q->size <= p->size)
        {
            (p->count)++;
            break;
        }
        p = p->next;
    }

    if (p != NULL) 
    {
        q->root_id = p->index;
        p->size -= q->size;
        if (alloc_head == NULL)
        {
            alloc_head = q;
        }
        else 
        {
            prev_alloc = alloc_head;
            while (prev_alloc->next != NULL)
            {
                prev_alloc = prev_alloc->next;
            }
            prev_alloc->next = q;
        }
        alloc_count++;
    }
    else 
    {
        printf("root of size %d  can't be allocated\n",c);
    }
}

void delete_alloc(int t)
{
    Alloc *p = alloc_head, *q = NULL;
    while (p != NULL && p->index != t) 
    {
        q = p;
        p = p->next;
    }
    if (p == NULL)
    {
        printf("index ID doesn't exist\n");
    }
    else if (p == alloc_head)
    {
        alloc_head = alloc_head->next;
    }
    else
    {
        q->next = p->next;
    }
    Free* temp = free_head;
    while (temp != NULL) 
    {
        if (temp->index == p->root_id) 
        {
            temp->count--;
            temp->size += p->size;
            Free* ptr=free_head;
            
            while(ptr->next != temp)
            {
                ptr=ptr->next;
            }
            if(temp->count == 0 && temp->index != 0)   //Merging adjacent free roots
            {
                ptr->size += temp->size;
                ptr->next=temp->next;
                temp->next=NULL;
                free(temp);      
            }
            break;
        }
        temp = temp->next;
    }
}

int main()
{
    int rootSize[] = {12, 40};
    int processSize[] = { 5, 1, 2, 7, 8, 9, 3, 10};
    int m = sizeof(rootSize) / sizeof(rootSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);
    int i;
    for (i = 0; i < m; i++)
    {
        create_free(rootSize[i]);
    }
    for (i = 0; i < n; i++)
    {
        create_alloc(processSize[i]);
    }
    print_alloc();
    print_free();

    return 0;
}
