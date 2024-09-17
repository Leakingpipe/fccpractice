#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//存储数组的结构体 
struct dynamicArray
{
	void ** pAddr;
	
	int m_capacity;
	
	int m_size;
};

//初始化数组 
struct dynamicArray * init_DynamicArray(int capacity)
{
	if(capacity<=0)
	{
		return NULL;
	}
	
	//给数组分配空间 
	
	struct dynamicArray * array = malloc(sizeof(struct dynamicArray));
	if (array == NULL)
	{
		return NULL;
	}
	
	//初始化 
	array->pAddr = malloc(sizeof(void *)* capacity); 
	array->m_capacity = capacity;
	array->m_size = 0;
	
	return array;
	
}

//插入操作
void insert_DynamicArray(struct dynamicArray * array, int pos, void * data)
{
	if (array == NULL)
	{
		return;
	}
	if (data == NULL)
	{
		return;
	}
	
	//检测插入位置是否合法，否的话默认插到末尾 
	if (pos < 0 || pos > array->m_size)
	{
		pos = array->m_size; 
	 } 
	 
	 //检查数组大小是否够 如果插满了需要扩展 
	 if (array->m_size >= array->m_capacity )
	 {
	 	//1、计算新空间大小 
	 	int newCapacity = array->m_capacity * 2;
	 	
	 	//2、创建新空间 
		void ** newSpace = malloc(sizeof(void *) * newCapacity);
		
		//3、拷贝新空间 
		memcpy(newSpace, array->pAddr, sizeof(void *)* array->m_capacity);
		
		//4、释放原来的空间 
		free(array->pAddr);
		
		//5、更新新空间指向 
		array->pAddr = newSpace;
		
		//6、更新新容量 
		array->m_capacity = newCapacity;
	 };
	 
	 //插入新元素 
	  
	  
	  //移动元素 插入新元素 
	  int insert_index = array->m_size-1; 
	  for (insert_index; insert_index>=pos;)
	  {
	  		//把数据往后移动 
			array->pAddr[insert_index+1] = array->pAddr[insert_index]; 
	   };
	   
	   //将新元素插入到指定位置上 
	    array->pAddr[pos] = data;
		
		//update size
		array->m_size++;
 } 
 
 //iterate the array 
 void foreach_DynamicArray(struct dynamicArray * array, void(*myPrint)(void*))
 {
 	if (array == NULL)
 	{
 		return;
	 };
	if (myPrint == NULL)
	{
		return;
	};
	 
	 int iteration_i = 0;
	 for (iteration_i;iteration_i < array->m_size;iteration_i++)
	 {
	 	myPrint(array->pAddr[iteration_i]);
	 };
  } 





//test
struct Person
{
	char name[64]; 
	int age; 
 };
 
void myPrintPerson(void * data)
{
	struct Person *p = (struct Person*)data;
	printf("Name: %s Age: %d\n", p->name, p->age);
};


int main(){
	
	//initialize dynamic array 
	struct dynamicArray * array = init_DynamicArray(5);
	
	//data preparation
	struct Person p1 = {"John", 80};
	struct Person p2 = {"George", 75};
	struct Person p3 = {"Albert", 83};
	struct Person p4  = {"Nel", 79};
	struct Person p5  = {"Peter", 82};
	struct Person p6  = {"Steve", 95};
	
	printf("Capacity before insertion%d Size before insertion %d\n", array->m_capacity, array->m_size); 
	
	//insert data
	insert_DynamicArray(array, 0, &p1); 
	insert_DynamicArray(array, 0, &p2); 
	insert_DynamicArray(array, 3, &p3); 
	insert_DynamicArray(array, 1, &p4); 
	insert_DynamicArray(array, -1, &p5); 
	insert_DynamicArray(array, 2, &p6); 
	
	//iterate the array
	foreach_DynamicArray(array, myPrintPerson); 

	printf("Capacity after insertion: %d Size after insertion %d\n", array->m_capacity, array->m_size); 
	
	system("pause");
	return EXIT_SUCCESS;
}
