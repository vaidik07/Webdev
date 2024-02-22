#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#define HEAP_SIZE 2000


void *my_malloc(size_t);
void my_free(void*);
void* my_realloc(void* ptr,size_t size);
void* my_calloc(size_t n,size_t size);
void defragment_my_heap(void);
size_t free_space_in_my_heap(void);
void hexdump(void);

char StaticMemory[HEAP_SIZE];

//Linked list used for memory management
struct allocatedList
{
    int free;
    int size;
    struct allocatedList *next;
};

typedef struct allocatedList NODE;

int Check_first_time(void);

NODE* head;
short int First_Allocation = 1;

/**************************************************************************************************************************************
* Module        :my_malloc()
*
* Description   : The order and contiguity of storage allocated by successive calls to the my_calloc,
* my_malloc, and my_realloc functions is unspecified. The pointer returned if the
* allocation succeeds is suitably aligned so that it may be assigned to a pointer to any type
* of object and then used to access such an object or an array of such objects in the space
* allocated (until the space is explicitly freed or reallocated). Each such allocation shall
* yield a pointer to an object disjoint from any other object.
* The pointer returned points to the start (lowest byte address) of the allocated space. If the
* space cannot be allocated, a null pointer is returned. If the size of the space requested is
* zero, a NULL pointer is returned; the value returned shall be either a null pointer or a
* unique pointer. The value of a pointer that refers to freed space is indeterminate.
*
* This function allocates space for an object whose size is specified by size and
* whose value is indeterminate.
**************************************************************************************************************************************/
void* my_malloc(size_t size)
{
    NODE *new_node,*traverse;
    short int foundflag=0;
    void* p;
    if(Check_first_time())
    {
        head = (NODE*)StaticMemory;
        head->next = NULL;
        head->free = 1;
    }

    traverse = (NODE*)StaticMemory;
    while(traverse->next != NULL)
    {
        if(traverse->free == 1&&traverse->size>= size)
        {
            foundflag=1;
            break;
        }
        //p = p + sizeof(NODE) + traverse->size;    
        traverse = traverse->next;
    }

    p = (void*)traverse + sizeof(NODE);
    if(p+size> (void*)StaticMemory + HEAP_SIZE)
    {
        p = NULL;
        return p;
    }
    if(foundflag == 1)
    {
        traverse->free = 0;
        traverse->size = size;
        return p;
    }
    
    if(p+ size + sizeof(NODE) < (void*)StaticMemory + HEAP_SIZE)
    {
        new_node = (NODE*)((void*)traverse + sizeof(NODE) + size);
        new_node->next = NULL;
        new_node->size = 0;
        traverse->next = new_node;
        traverse->free = 0;
        traverse->size = size;
        return p;
    }
    else
        return NULL;
}

int Check_first_time(void)
{
    if(First_Allocation==1)
    {
        First_Allocation = 0;
        return 1;
    }
    else
        return 0;
}

/**************************************************************************************************************************************
* Module        :my_free()
*
* Description   : This function causes the space pointed to by ptr to be deallocated, that is,
* made available for further allocation. If ptr is a null pointer, no action
* occurs. If the argument does not match with a pointer value that was returned
* earlier by the my_calloc. my_malloc, or my_realloc function, or if the space
* has been deallocared by a call to free or realloc, the behavior is undefined.
*
**************************************************************************************************************************************/
void my_free(void* ptr)
{
    NODE* traverse;
    short int found_flag=0;
    
    traverse = (NODE*)StaticMemory;
    do
    {       
        if((void*)traverse + sizeof(NODE) == ptr)
        {
            found_flag=1;
            break;
        }
        traverse = traverse->next;
    } while(traverse->next != NULL);

    if(found_flag)
    {
        traverse->free = 1;
        ptr = NULL;
    }
    else
        printf("\nFree Process Failed");
    
}

/**************************************************************************************************************************************
* Module        :my_realloc()
*
* Description   : The function changes the size of the object pointed to by ptr to the size
* specified by size. The contents of the object shall be unchanged up to the
* lesser of the new and old sizes. If the new size is larger, the value of the
* newly allocated portion of the object is indeterminate. If ptr is a null pointer,
* themy_realloc function behaves like the my_malloc function for the
* specified size. Otherwise, if ptr does not match a pointer earlier returned by
* themy_calloc. my_malloc, or my_realloc function, or if the space has been
* deallocated by a call to the my_free or my_realloc function, the behavior is
* undefined. If the space cannot be allocated, the object pointed to by ptr is
* unchanged. If size is zero and ptr is not a null pointer, the object it points to
* is freed.
**************************************************************************************************************************************/
void* my_realloc(void* ptr,size_t size)
{
    NODE *traverse;
    void *test;
    short int flag = 0;
    
    traverse = (void*)StaticMemory;

    do
    {
        if(ptr == (void*)traverse+sizeof(NODE))
        {
            flag=1;
            break;
        }
        traverse = traverse->next;
    } while(traverse->next != NULL);

    if (flag==0)
    {
        printf("Pointer Error... Re-alloc Failed\n");
        return NULL;
    }
    if(size == 0)
    {
        my_free(ptr);
        return ptr;
    }
    traverse->free = 1;
    test = my_malloc(size);
    if(test != NULL)
        memcpy(test,ptr,traverse->size);
    else
        printf("\nRe-alloc Failed\n");
    return test;
}

/**************************************************************************************************************************************
* Module        :my_calloc()
*
* Description   : This function allocates space for an array of nmemb objects, each of whose
* size is size. The space is initialized to all bits zero.
*
**************************************************************************************************************************************/
//void* 
//my_calloc(size_tn,size_t size)
//{
//  void* p;
//  size = size * n;
//  p = my_malloc(size);
//  if(p!=NULL)
//      memset(p,0,size);
//  return p;
//}

/**************************************************************************************************************************************
* Module        :free_space_in_my_heap()
*
* Description   : This function returns the total size of free space available in the heap.
*
**************************************************************************************************************************************/

size_t free_space_in_my_heap(void)
{
    size_t free_space = 0;
    NODE *traverse;
    traverse = (NODE*)StaticMemory;
    while(traverse->next != NULL)
    {
        if(!(traverse->free))
        {
            free_space += (void*)traverse->next - (void*)traverse - sizeof(NODE) - traverse->size;              
        }
        
        else
        {
            free_space += traverse->size + sizeof(NODE);
        }
        traverse = traverse->next;
    }
    free_space += (-(long)traverse +(long)StaticMemory + HEAP_SIZE);
    return free_space;
}

/**************************************************************************************************************************************
* Module        :hexdump()
*
* Description   : Produces hex demp of the contents in the heap space on the screen
**************************************************************************************************************************************/

void hexdump(void)
{
    int *a;
    int  rowCount,columnCount;
    a = (int*)StaticMemory;
    printf("\n***************************************************************************");
    printf("\nBeginning Hex Dump\n");
    printf("Address\t1\t2\t3\t4\t5\t6\t7\t8\n");
    for(rowCount = 0 ; rowCount<HEAP_SIZE/(sizeof(int)*8) ; rowCount++)
    {
        printf("%ld\t",(long)a + (sizeof(int)*8*rowCount));
        for(columnCount=0;columnCount<8;columnCount++)
        {
            printf("%d\t",*(a + 8*rowCount + columnCount));
        }
        printf("\n");
    }
    printf("***************************************************************************\n");
}

int main()
{
    int *a,*b;
    int count;
    
    a = (int*)my_malloc(sizeof(int)*40);
    if(a==NULL)
        printf("\n Malloc Failed\n");
    b = (int*)my_malloc(sizeof(int)*100);
    if(b==NULL)
        printf("\nMalloc Failed\n");

    if(a!=NULL)
    {
        for (count = 0; count<40; count++)
        {
            a[count] = count+1;
        }
    }
    hexdump();//hex dump is a hexadecimal view (on screen or paper) of computer data, from memory or from a computer file or storage device .
    printf("Free space in heap = %d\n",(int)free_space_in_my_heap());
    my_free(b);
    printf("Free space in heap after freeing B = %d\n",(int)free_space_in_my_heap());
    a = (int*)my_realloc(a,sizeof(int)*90);
    hexdump();
    printf("Free space in heap = %d\n",(int)free_space_in_my_heap());
    my_free(a);
    printf("Free space in heap after freeing A= %d\n",(int)free_space_in_my_heap());
    //a = (int*)my_calloc(sizeof(int),82);
    //if(a!=NULL)
    //{
    //  for (count = 0; count < 40; count++)
    //  {
    //      a[count] = count+1;
    //  }
    //}

    return 0;
}


