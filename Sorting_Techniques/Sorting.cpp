#include <iostream>

using namespace std;



// In C++ can use using Item = int;
using Item = int;
//typedef int Item;

// Definition of node for linked list
struct Node{

	Item val;
	Node* next;
	Node(const Item& _val, Node* _next = nullptr){
		val = _val;
		next = _next;
	}
};

// Adding dynamic allocated node to link list
void AddElementToList(Node** ptr, const Item& new_element){
	if(*ptr == nullptr){
		*ptr = new Node(new_element);
		return;
	}
	Node* begin = *ptr;
	while(begin->next != nullptr){
		begin = begin->next;
	}
	begin->next = new Node(new_element);
}

void PrintList(Node* ptr){
	while(ptr != nullptr){
		cout << ptr->val << " ";
		ptr = ptr->next;
	}
	cout << endl;
}

// Deleting first node (front) of link list
void PopFrontOfList(Node** ptr){
	if(*ptr == nullptr){
		return;
	}
	Node* to_delete = *ptr;
	*ptr = (*ptr)->next;
	delete to_delete;
}



// Second parametr - free node with next value nullptr
// Attention! We assume list sorted in ascending order.
void InsertNodeToSortedList(Node** ptr, Node* to_insert){
	// Empty node to insertion
	if(to_insert == nullptr){
		return;
	}
	// Empty list - simply insert new node;
	if(*ptr == nullptr){
		*ptr = to_insert;
		return;
	}
	Node* p = nullptr;
	Node* q = *ptr;
	// if array sorted in descending order we should use >
	while(q != nullptr && q->val < to_insert->val){
		p = q;
		q = q->next;
	}
	// if we insert node to end of sorted list
	if(q == nullptr){
		p->next = to_insert;
	}
	// if we insert node to begin of sorted list
	else if(p == nullptr){
		*ptr = to_insert;
	       to_insert->next = q;	
	}
	// other case when position to insert between two nodes
	else{
		p->next = to_insert;
		to_insert->next = q;
	}


}

void InsertValToSortedList(Node** ptr, const Item& value){
	InsertNodeToSortedList(ptr, new Node(value));
}

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

// Algorithm for sorting list
void InsertionSortList(Node** ptr){
	if(ptr == nullptr){
		return ;
	}
	// No nodes
	if(*ptr == nullptr){
		return ;
	}
	// One element list already sorted
	if((*ptr)->next == nullptr){
		return;
	}
	// Using two pointers for sorting.
	// p - using for insertion through the next field of 
	// Node struct 
	Node* p = *ptr;
	Node* q = p->next;
	while(q != nullptr){
		p->next = nullptr;
		Node* list_begining = q->next;
		q->next = nullptr;
		// One node list is already sorted.
		// Inserting element to sorted list(left part of list)
		InsertNodeToSortedList(ptr, q);
		if(p->next != nullptr){
			p = p->next;
		}
		// glue together sorted part of list and unsorted
		p->next = list_begining;
		q = p->next;
	}
}

// Find max element of array with size
Item FindMax(Item arr[], size_t size){
	Item max_val = arr[0];
	for(size_t i = 1; i < size; ++i){
		if(max_val < arr[i]){
			max_val = arr[i];
		}
	}
	return max_val;

}


// Counting number of digits
int FindNumberOfDigits(Item value){
	int result = 1;
	long long unsigned delim = 10;
	while(value / delim != 0){
		delim *= 10;
		++result;
	}
	return result;
}

// Radix Sort for array - only for values bigger or equal 0
// This sorting techniques doesn't adoptive
void RadixSort(Item arr[], size_t size)
{
	int digits = FindNumberOfDigits(FindMax(arr, size));
 	// Creating array of lists (array of buckets).
	// Size of array number of digits of max value in array + 1
	Node** buckets = new Node*[digits + 1];
	int mod = 10, delim = 1;
	
	// We should pass all digits
	for(int i = 0; i < digits; ++i){
		// Insert to buckets by first, second ... n digit of element.
		// Current digit - index of bucket in which should be inserted current value
		for(int j = 0; j < size; ++j){
			AddElementToList(&buckets[ (arr[j] % mod) / delim ], arr[j]);
		}
		// Gettings elements from buckets(link lists) and inserting them
		// to source array (after every nested while loop bucket becoming empty)
		int k = 0;
		for(int j = 0; j <= digits; ++j){
			while(buckets[j]){
				arr[k++] = buckets[j]->val;
				// Deleting value from list
				PopFrontOfList(&buckets[j]);
			}
		}
		// Getting next digit
		mod*= 10;
		delim*= 10;
	}
	delete[] buckets;

	
}


// Counting sort for array - for values bigger or equal 0
void CountSort(Item arr[], size_t size){
	int max = FindMax(arr, size);
	int* buffer = new int[max + 1];
	for(int i = 0; i <= max; i++){
		buffer[i] = 0;
	}

	for(size_t i = 0; i < size; ++i){
		buffer[arr[i]]+= 1;
	}
	int k = 0;
	for(int i = 0; i <= max; ++i){
		while(buffer[i] != 0){
			--buffer[i];
			arr[k++] = i;
		}
	}
	delete[] buffer;
}

// BinBucket sort for array - for values bigger or equal 0
void BinBucketSort(Item arr[], size_t size){
	int max = FindMax(arr, size);
	Node** buckets = new Node*[max + 1];
	
	// Filling buckets
	for(int i = 0; i < size; ++i){
		AddElementToList(&buckets[arr[i]], arr[i]);
	}
	int k = 0;
	for(int i = 0; i <= max; ++i){
		while(buckets[i]){
			arr[k++] = buckets[i]->val;
			PopFrontOfList(&buckets[i]);
		}
	}
	delete[] buckets;
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

	Node* list = nullptr;
	AddElementToList(&list, 5);
	AddElementToList(&list, 3);
	AddElementToList(&list, -12);
	PrintList(list);
	while(list != nullptr){
		cout << list->val << endl;
		PopFrontOfList(&list);
	}
	AddElementToList(&list, 1);
	InsertNodeToSortedList(&list, new Node(0));
	PrintList(list);
	AddElementToList(&list, 6);
	AddElementToList(&list, 8);
	AddElementToList(&list, 12);
	PrintList(list);
	InsertValToSortedList(&list, -10);
	InsertValToSortedList(&list, 7);
	InsertValToSortedList(&list, 25);
	PrintList(list);
	while(list != nullptr)
		PopFrontOfList(&list);
	AddElementToList(&list, 24);
	AddElementToList(&list, 12);
	AddElementToList(&list, -10);
	AddElementToList(&list, 50);
	AddElementToList(&list, -90);
	AddElementToList(&list, 5);
	cout << "Insertion sort for linked list below: " << endl;
	PrintList(list);
	InsertionSortList(&list);
	cout << "After sorted algorithm: " << endl;
	PrintList(list);


	Item arr3[6] = {13425, 342, 543, 654, 2345, 32};
	cout << "Array before radix sort: " << endl;
	PrintArr(arr3, 6);
	RadixSort(arr3, 6);
	cout << "Array after radix sort: " << endl;
	PrintArr(arr3, 6);
	Item arr4[7] = {12, 4, 1, 4, 5, 4, 0};
	Item arr5[7] = {12, 4, 1, 4, 5, 4, 0};
	BinBucketSort(arr5, 7);
	PrintArr(arr5, 7);
	CountSort(arr4, 7);
	PrintArr(arr4, 7);
	return 0;
}
