#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//节点结构体
struct LinkNode
{
    //数据域
    void * data;
    //指针域
    struct LinkNode * next;
};

//链表结构体
struct LList
{
    //头节点
    struct LinkNode pHeader;
    //链表长度
    int m_size;
};

typedef void * LinkList;

//初始化链表
LinkList init_LinkList()
{
    struct LList * myList = malloc(sizeof(struct LList));

    if(myList == NULL)
    {
        return NULL;
    }

    myList->pHeader.data = NULL;
    myList->pHeader.next = NULL;
    myList->m_size = 0;

    return myList;
}

//插入链表
void insert_LinkList(LinkList list, int pos, void * data)
{
   if (list == NULL)
    {
        return;
    }
    if (data == NULL)
    {
        return;
    }
    
    //将list还原成struct LList数据类型
    struct LList * myList = list;
    if (pos < 0 || pos > myList->m_size)
    {
        //无效位置强制尾插
        pos = myList->m_size;
    }

    //找到插入节点的前驱结点位置
    struct LinkNode * pCurrent = &myList->pHeader;

    for (int i = 0; i < pos; i++)
    {
        pCurrent = pCurrent->next;
    }
    //pCurrent 要插入节点的前驱

    //创建新节点

    struct LinkNode * newNode = malloc(sizeof(struct LinkNode));
    if (newNode == NULL)
    {
        return;
    }
    newNode->data = data;
    newNode->next = NULL;

    //建立节点关系

    newNode->next = pCurrent->next;
    pCurrent->next = newNode;

    //renew link list length
    myList->m_size++;
}

//iterate link list
void foreach_LinkList(LinkList list, void(*myForeach)(void *))
{
    if (list == NULL)
    {
        return;
    }

    struct LList * mylist = list;

    struct LinkNode * pCurrent = mylist->pHeader.next;

    for (int i = 0; i < mylist->m_size; i++)
    {
        myForeach(pCurrent->data);
        pCurrent = pCurrent->next;
    }
}

//Delete link list
void removeByPos_LinkList(LinkList list, int pos)
{
    if(list == NULL)
    {
        return;
    }

    struct LList * mylist = list;

    if(pos < 0 || pos > mylist->m_size - 1)
    {
        return;
    }

    //Finding the prior node of the removing node
    struct LinkNode * pCurrent = &mylist->pHeader;
    for(int i = 0; i < pos; i++)
    {
        pCurrent = pCurrent->next;
    }

    //Record the removing node
    struct LinkNode * pDel = pCurrent->next;

    //construct relationship
    pCurrent->next = pDel->next;

    free(pDel);
    pDel = NULL;

    //renew link list length
    mylist->m_size--;
}

//Delete by value
void removeByValue_LinkList(LinkList list, void * data, int(*myCompare)(void *, void *))
{
    if ( list == NULL)
    {
        return;
    }

    if ( data == NULL)
    {
        return;
    }

    struct LList *  mylist = list;
    //create two auxiliary pointers
    struct LinkNode * pPrev = &mylist->pHeader;
    struct LinkNode * pCurrent = pPrev->next;
    
    for ( int i = 0; i < mylist->m_size; i++)
    {
        //user pCurrent->data vs data
        if(myCompare( pCurrent->data, data))
        {
            pPrev->next = pCurrent->next;

            free(pCurrent);
            pCurrent = NULL;

            mylist->m_size--;
            break;
        }

        //if can't find that value, auxiliary pointers move backward
        pPrev = pCurrent;
        pCurrent = pCurrent->next;
    }
}

//Clear link list
void clear_LinkList(LinkList list)
{
    if ( list == NULL )
    {
        return;
    }

    struct LList * mylist = list;

    struct LinkNode * pCurrent = mylist->pHeader.next;

    for (int i = 0; i < mylist->m_size; i++)
    {
        struct LinkNode * pNext = pCurrent->next;

        free(pCurrent);

        pCurrent = pNext;
    }

    mylist->pHeader.next = NULL;
    mylist->m_size = 0;


}

//return link list length
int size_LinkList(LinkList list)
{
    if ( list == NULL )
    {
        return -1;
    }

    struct LList * mylist = list;

    return mylist->m_size;
}

//Destroy link list
void destroy_Linklist(LinkList list)
{
    if ( list == NULL )
    {
        return ;
    }

    //clear link list
    clear_LinkList(list);

    free(list);

    list = NULL;
}

//test
struct Person
{
	char name[64]; 
	int age; 
 };

void myPrintPerson(void * data)
{
    struct Person * p = data;
    printf("Name: %s Age: %d\n", p->name, p->age);
}

int myComparePerson(void * data1, void * data2)
{
    struct Person * p1 = data1;
    struct Person * p2 = data2;

    return strcmp(p1->name, p2->name) == 0 && p1->age == p2->age;
}

void test01()
{
    //preparing data
    struct Person p1 = {"John", 80};
	struct Person p2 = {"George", 75};
	struct Person p3 = {"Albert", 83};
	struct Person p4  = {"Nel", 79};
	struct Person p5  = {"Peter", 82};
	struct Person p6  = {"Steve", 95};


   //INITIALIZE LINK LIST
   LinkList mylist = init_LinkList();

   printf("The length of the link list: %d\n", size_LinkList(mylist));

   //insert data
   insert_LinkList(mylist, 0, &p1);
   insert_LinkList(mylist, 0, &p2);
   insert_LinkList(mylist, -1, &p3);
   insert_LinkList(mylist, 0, &p4);
   insert_LinkList(mylist, 1, &p5);
   insert_LinkList(mylist, 0, &p6);

   //iterate
   foreach_LinkList(mylist, myPrintPerson);
   
   printf("The length of the link list: %d\n", size_LinkList(mylist));

   //TEST DELETE BY POSITION
   removeByPos_LinkList(mylist, 4);

   printf("---------------------\n");

   foreach_LinkList(mylist, myPrintPerson);
   printf("The length of the link list: %d\n", size_LinkList(mylist));

   //TEST REMOVE BY VALUE
   struct Person p = {"Albert", 83};
   removeByValue_LinkList(mylist, &p, myComparePerson);

   printf("---------------------\n");

   foreach_LinkList(mylist, myPrintPerson);
   printf("The length of the link list: %d\n", size_LinkList(mylist));


   //TEST CLEAR LIST
   clear_LinkList(mylist);

   //return link list length
   printf("The length of the link list: %d\n", size_LinkList(mylist));

   //DESTROY
   destroy_Linklist(mylist);
   mylist = NULL;
}

int main()
{
    test01();
    system("pause");
    return EXIT_SUCCESS;
}