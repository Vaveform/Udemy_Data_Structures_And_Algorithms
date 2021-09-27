#include <iostream>

using namespace std;

typedef int Item;



// Definition of node for linked list
struct Node{

	Item val;
	Node* next;
	Node(Item _val, Node* _next = nullptr){
		val = _val;
		next = _next;
	}
};

void PrintArr(Item* ptr, size_t size){
	for(size_t i = 0; i < size; ++i){
		cout << ptr[i] << " ";
	}
	cout << endl;
}


// C-style implementation of bubble sort
void BubbleSort(Item* ptr, size_t size){
	// First loop - number of passes for
	// for pushing bubbles (max element from 0 to size - i - 1 (-1 for swapping
	// with next element))
	for(size_t i = 0; i < size; i++){
		// Flag for adaptivity bubble sorting algorithm
		// If we did not make swap (on any i) - array sorted - we should stop sorting
		bool arr_is_sorted = true;
		for(size_t j = 0; j < size - i - 1; j++){
			// On the i = 0 we pushing max element to the last index;
			// On the i = 1 we pushing max element between 0 to size - 2 index elements
			// on the index size - 2 and so on. 
			if(ptr[j] > ptr[j + 1]){  // Comparing should be strictly bigger
				arr_is_sorted = false;
				swap(ptr[j], ptr[j + 1]);
			}
		}
		if(arr_is_sorted){
			break;
		}
	}
}


// C-style implementaion of insertion sort
void InsertionSort(Item* ptr, size_t size){
	// First element - sorted array -> begin from i = 1
	for(size_t i = 1; i < size; i++ ){
		// Every time when we start inserting element - we insert to sorted array.
		Item value_to_insert = ptr[i];
		// Finding last element, which bigger then value to insert
		// (or value should be insert to begin) and shift all elements
		// by one position to right
		int j = i - 1;
		// j > -1 - because value may be smaller than all before him
		while(j > -1 && ptr[j] > value_to_insert){
			// shifting
			ptr[j + 1] = ptr[j];
			// going to begin with j
			--j;
		}
		// j stopped on -1 or on element which equal or smaller than value to inserted
		ptr[j + 1] = value_to_insert; 
	}
}



int main(){
	int arr1[10] = {8, 1, 8, -4, 1, 10, 20, 6, 3, 15};
	cout << "Before bubble sort: " << endl;
	PrintArr(arr1, 10);
	BubbleSort(arr1, 10);
	cout << "After bubble sort: " << endl;
	PrintArr(arr1, 10);
	int arr2[10] = {8, 1, 8, -4, 1, 10, 20, 6, 3, 15};
	cout << "Before bubble sort: " << endl;
	PrintArr(arr2, 10);
	BubbleSort(arr2, 10);
	cout << "After bubble sort: " << endl;
	PrintArr(arr2, 10);
	return 0;
}
