#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "DynamicArray_Body.h"

// //Store the dynamic array in the structure
// struct dynamicArray
// {
// 	void ** pAddr;
	
// 	int m_capacity;
	
// 	int m_size;
// };

// //initialize the dynamic array
// struct dynamicArray * init_DynamicArray(int capacity)
// {
// 	if( capacity<=0 )
// 	{
// 		return NULL;
// 	}
	
// 	//assign space to the array
	
// 	struct dynamicArray * array = malloc(sizeof(struct dynamicArray));
// 	if (array == NULL)
// 	{
// 		return NULL;
// 	}
	
// 	//initialize
// 	array->pAddr = malloc(sizeof(void *)* capacity); 
// 	array->m_capacity = capacity;
// 	array->m_size = 0;
	
// 	return array;
	
// }

// //insertion
// void insert_DynamicArray(struct dynamicArray * array, int pos, void * data)
// {
// 	if (array == NULL)
// 	{
// 		return;
// 	}
// 	if (data == NULL)
// 	{
// 		return;
// 	}
	
// 	//Check if the insert position is legit 
// 	if (pos < 0 || pos > array->m_size)
// 	{
// 		pos = array->m_size; 
// 	 } 
	 
// 	 //Check if there's enough space for the array
// 	 if (array->m_size >= array->m_capacity )
// 	 {
// 	 	//1.reculculate the capacity
// 	 	int newCapacity = array->m_capacity * 2;
	 	
// 	 	//2.create new space
// 		void ** newSpace = malloc(sizeof(void *) * newCapacity);
		
// 		//3.Copy new space
// 		memcpy(newSpace, array->pAddr, sizeof(void *)* array->m_capacity);
		
// 		//4.Free old space
// 		free(array->pAddr);
		
// 		//5.renew the pointer
// 		array->pAddr = newSpace;
		
// 		//6.renew capacity
// 		array->m_capacity = newCapacity;
// 	 };
	 
// 	 //insert new elements
	  
	  
// 	  //move element and insert 
	  
// 	  for (int i = array->m_size-1;  i>=pos; i--)
// 	  {
// 	  		//move the elements to the back
// 			array->pAddr[i + 1] = array->pAddr[i]; 
// 	   };
	   
// 	   //put the new element at the assigned position
// 	    array->pAddr[pos] = data;
		
// 		//update size
// 		array->m_size++;
//  } 
 
//  //iterate the array 
//  void foreach_DynamicArray(struct dynamicArray * array, void(*myPrint)(void*))
//  {
//  	if (array == NULL)
//  	{
//  		return;
// 	 };
// 	if (myPrint == NULL)
// 	{
// 		return;
// 	};
	 
// 	 for (int i = 0; i < array->m_size; i++)
// 	 {
// 	 	myPrint(array->pAddr[i]);
// 	 };
//   } 
  

// //RemoveByPosition
// void removeByPos_DynamicArray(struct dynamicArray * array, int pos)
// {
// 	if(array == NULL)
// 	{
// 		return;
// 	}
	
// 	if (pos < 0 || pos > array->m_size - 1)
// 	{
// 		return;
// 	}
	
// 	//move data
// 	int move_i;
// 	for(move_i = pos; move_i < array->m_size - 1; move_i++)
// 	{
// 		array->pAddr[move_i] = array->pAddr[move_i + 1];
// 	}
	
// 	//renew the size of the array
// 	array->m_size--;
// }

// //remove by value
// void removeByValue_DynamicArray(struct dynamicArray * array, void * data, int (* myCompare)(void *, void *))
// {
// 	if (array == NULL)
// 	{
// 		return;
// 	}
// 	if ( data == NULL )
// 	{
// 		return;
// 	}

// 	for (int i = 0; i < array->m_size; i++)
// 	{
// 		if (myCompare (array->pAddr[i], data))
// 		{
// 			//if the deleting data is found, then i is its position
// 			removeByPos_DynamicArray(array, i);
// 			break;
// 		}
// 	}
// }

// //destroy array
// void destroy_DynamicArray(struct dynamicArray * array)
// {
// 	if(array == NULL)
// 	{
// 		return;
// 	}

// 	if(array->pAddr != NULL)
// 	{
// 		free(array->pAddr);
// 		array->pAddr = NULL;
// 	}
	
// 	free(array);
// 	array = NULL;
// }








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

int myComparePerson(void * data1, void * data2)
{
	struct Person * p1 = data1;
	struct Person * p2 = data2;

	return strcmp(p1->name, p2->name) == 0 && p1->age == p2->age;
}

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
	
	printf("Capacity before insertion: %d, Size before insertion: %d \n", array->m_capacity, array->m_size); 
	printf("-----------------------------------------------------------------------\n");
	
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
	
	//test remove by position
	removeByPos_DynamicArray(array, 2);
	printf("_________________________________\n");
	foreach_DynamicArray(array, myPrintPerson);
	printf("Capacity after removal: %d Size after removal %d\n", array->m_capacity, array->m_size); 
	
	//test remove by value
	struct Person p = { "Nel", 79 };
	removeByValue_DynamicArray(array, &p, myComparePerson);
	printf("_________________________________\n");
	foreach_DynamicArray(array, myPrintPerson);
	printf("Capacity after removal: %d Size after removal %d\n", array->m_capacity, array->m_size); 

	//destroy array
	destroy_DynamicArray(array);
	array = NULL;

	getchar();
	return EXIT_SUCCESS;
}
