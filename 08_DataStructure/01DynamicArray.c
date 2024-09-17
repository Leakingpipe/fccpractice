#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//�洢����Ľṹ�� 
struct dynamicArray
{
	void ** pAddr;
	
	int m_capacity;
	
	int m_size;
};

//��ʼ������ 
struct dynamicArray * init_DynamicArray(int capacity)
{
	if(capacity<=0)
	{
		return NULL;
	}
	
	//���������ռ� 
	
	struct dynamicArray * array = malloc(sizeof(struct dynamicArray));
	if (array == NULL)
	{
		return NULL;
	}
	
	//��ʼ�� 
	array->pAddr = malloc(sizeof(void *)* capacity); 
	array->m_capacity = capacity;
	array->m_size = 0;
	
	return array;
	
}

//�������
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
	
	//������λ���Ƿ�Ϸ�����Ļ�Ĭ�ϲ嵽ĩβ 
	if (pos < 0 || pos > array->m_size)
	{
		pos = array->m_size; 
	 } 
	 
	 //��������С�Ƿ� �����������Ҫ��չ 
	 if (array->m_size >= array->m_capacity )
	 {
	 	//1�������¿ռ��С 
	 	int newCapacity = array->m_capacity * 2;
	 	
	 	//2�������¿ռ� 
		void ** newSpace = malloc(sizeof(void *) * newCapacity);
		
		//3�������¿ռ� 
		memcpy(newSpace, array->pAddr, sizeof(void *)* array->m_capacity);
		
		//4���ͷ�ԭ���Ŀռ� 
		free(array->pAddr);
		
		//5�������¿ռ�ָ�� 
		array->pAddr = newSpace;
		
		//6������������ 
		array->m_capacity = newCapacity;
	 };
	 
	 //������Ԫ�� 
	  
	  
	  //�ƶ�Ԫ�� ������Ԫ�� 
	  int insert_index = array->m_size-1; 
	  for (insert_index; insert_index>=pos;)
	  {
	  		//�����������ƶ� 
			array->pAddr[insert_index+1] = array->pAddr[insert_index]; 
	   };
	   
	   //����Ԫ�ز��뵽ָ��λ���� 
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
