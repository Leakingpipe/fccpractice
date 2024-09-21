#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


//Store the dynamic array in the structure
struct dynamicArray
{
	void ** pAddr;
	
	int m_capacity;
	
	int m_size;
};

//initialize the dynamic array
struct dynamicArray * init_DynamicArray(int capacity);

//insertion
void insert_DynamicArray(struct dynamicArray * array, int pos, void * data);
 
//iterate the array 
void foreach_DynamicArray(struct dynamicArray * array, void(*myPrint)(void*));

//RemoveByPosition
void removeByPos_DynamicArray(struct dynamicArray * array, int pos);

//remove by value
void removeByValue_DynamicArray(struct dynamicArray * array, void * data, int (* myCompare)(void *, void *));

//destroy array
void destroy_DynamicArray(struct dynamicArray * array);
