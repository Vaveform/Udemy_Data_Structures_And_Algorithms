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


// Good algorithm for sorting list - merge sort
// We have two opeartions: Split list by 2 lists and merge two sorted lists
void SplitList(Node* head, Node** second_part){
	// We have two static variables:
	// i - current position in list
	// list_i - size of list 
	static int i = 0;
	static int list_s = 0;
	if(head == nullptr)
		return;
	// Incrementing every variable
	++list_s;
	++i;
	// Making recursive call
	SplitList(head->next, second_part);
	// This part making after base case of recursion
	// with previous parametrs of call.
	if(i == list_s / 2){
		// Setting second_part - pointer to second part
		// of list
		*second_part = head->next;
		// Slicing first part
		head->next = nullptr;
		// Setting list_s for other calls
		list_s = 0;
	}
	--i;
}

// Merging two lists
Node* mergeTwoLists(Node* l1, Node* l2){
	if(l1 == nullptr || l2 == nullptr){
            if(l1 == nullptr && l2 != nullptr){
                return l2;
            }
            else if(l1 != nullptr && l2 == nullptr){ return l1;}
            else{
                return l1;
            }
        }
        Node* begin = nullptr;
        Node* tmp = nullptr;
        int i = 0;
        while(l1 != nullptr && l2 != nullptr){
            if(l1->val <= l2->val){
                if(i == 0){
                    begin = l1;
                    tmp = begin;
                    l1 = l1->next;
                }
                else{
                    tmp->next = l1;
                    tmp = tmp->next;
                    l1 = l1->next;
                }
            }
            else{
                if(i == 0){
                    begin = l2;
                    tmp = begin;
                    l2 = l2->next;
                }
                else{
                    tmp->next = l2;
                    tmp = tmp->next;
                    l2 = l2->next;
                }
            }
            i++;
       	}
        if(l1 != nullptr){
            tmp->next = l1;
        }
        else{
            tmp->next = l2;
        }
        return begin;
}
// Good algorithm for sorting lists
// On leetcode - beats 97.53 percents of people by time 
Node* MergeSortList(Node* head){
	if(head != nullptr && head->next != nullptr)
	{
		// For storing second part of list
		Node* second_part = nullptr;
		// Head - pointer to first part of list
		SplitList(head, &second_part);
		return mergeTwoLists(MergeSortList(head), MergeSortList(second_part));
	}
	else{
		// Base case - simply returning Node
		return head;
	}
}

// Insertion sort algorithm for sorting list
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

// Selection sort for array (Complexity O(n^2))
void SelectionSort(Item arr[], size_t size)
{
	for(int i = 0; i < size - 1; ++i)
	{
		int k = i;
		for(int j = i; j < size; ++j)
		{
			// Finding min/max for pushing to buttom
			if(arr[j] < arr[k] ){
				k = j;
			}
		}
		swap(arr[k], arr[i]);
	}
}


// For central element of diapason of array 
// returning index of this element, after placing
// all elements to right side which bigger than this element
// and placing all elements which smaller than this element
int partition(Item arr[], int begin, int end){
    int i = begin, j = end - 1;
    int pivot = begin + (j + 1 - i) / 2;
    while(i < j){
	// Finding elements for swapping i -> arr <- j
        while(i < end && arr[i] <= arr[pivot]) ++i;
        while(j >= begin && arr[j] > arr[pivot]) --j;
	if(i < j){
        	swap(arr[i], arr[j]);
		// Pivot should be shifted and swapped
		if(pivot == j) {
			// Changing index for pivot
			// we shift pivot element!
			swap(i, j);
			pivot = j;
		}
	}
    }
    swap(arr[j],  arr[pivot]);
    return j;
}


void quicksort(Item arr[], int begin, int end)
{
	if(end - begin > 0){
		int par_ptr = partition(arr, begin, end);
		// Index par_ptr - last index element for array and using
		// in procedure of quicksort
		quicksort(arr, begin, par_ptr);
		quicksort(arr, par_ptr + 1, end);
	}
}


// mid - begin of the second sorted subarray
// l - begin of the first sorted subarray
// h - end of the second sorted subarray (last element index plus 1)
// mid - end of the first sorted subarray
void mergeArrDiapasons(Item arr[], int l, int mid, int h){
	// Using extra space (O(n), n - number of elements of input arr)
	// Time complexity - O(n)
	if(h - l <= 1)
		return;
	Item* temp = new Item[h - l];
	int first = l;
	int second = mid;
	int k = 0;
	// Example: 1 2 3 4 |3| 4 5 6 7
	while(first < mid && second < h){
		// Assign to k-index element min element 
		// of first / second element
		if(arr[first] < arr[second]){
			temp[k++] = arr[first++];
		}
		else{
			temp[k++] = arr[second++];
		}
	}
	for(; first < mid; first++){
		temp[k++] = arr[first];
	}
	for(; second < h; second++){
		temp[k++] = arr[second];
	}
	// Now temp array is sorted -> copy to input array
	int begin = l;
	for(int i = 0; i < h - l; ++i){
		arr[begin++] = temp[i];
	}
	delete[] temp;
}




void IterativeMergeSort(Item arr[], size_t size){
	int p = 2, i = 0;
	for(p = 2; p < size; p*=2){
		for(i = 0; i < size; i+=p){
			// case when p step (2^n) + i smaller then array end
			if(i + p <=  size)
				mergeArrDiapasons(arr, i, (i + (i + p)) / 2, i + p);
			// Merging part of array which is not fit to step 
			// (step + 1 bigger than size) - this case very bad for merging
			else{
				mergeArrDiapasons(arr, i, (i + size) / 2, size);
			}
		}
	}
	mergeArrDiapasons(arr, 0, p/2 , size);
}


void RecursiveMergeSort(Item arr[], int begin, int end){
	if(end - begin <= 1)
		return;
	if(end - begin == 2)
		mergeArrDiapasons(arr, begin, begin + (end - begin) / 2, end);
	// For mergeArrDiapasons selected indexes of end 
	// First recursive call has end : begin + (end - begin) / 2
	// it is number equal to the index of last element  + 1
	RecursiveMergeSort(arr, begin, begin + (end - begin) / 2);
	// Second recursive call start with the begin equal to the end of the first
	// recursive call because for first recursive call mergeArrDiapasons will
	// be interpret end as the index of last index element + 1 (element with index
	// begin + (end - begin) / 2 - not element wich will be using for merging in first
	// recursive call)
	RecursiveMergeSort(arr, begin + ((end - begin) / 2) , end);
	mergeArrDiapasons(arr, begin, begin + ((end - begin) / 2), end);
}

void ShellSortArr(Item arr[], size_t size, int delim)
{
	for(int j = size / delim; j >= 1; j /= delim)
	{
		// Starting insertion sort, but we 
		// decremented/incremented by j -
		// we sorted only elements which have gap
		// between and start from index zero
		for(int i = 0; i < size; i+= j){
			int k = i - j;
			Item value_to_insert = arr[i];
			// Shifting elements for insertion
			while(k > -1 && arr[k] > value_to_insert){
				arr[k + j] = arr[k];
				k -= j;
			}
			arr[k + j] = value_to_insert;
		}
	}
}

// I will write Shell Sort for Link List!!!

int main(){
	//int arr1[10] = {8, 1, 8, -4, 1, 10, 20, 6, 3, 15};
	//cout << "Before bubble sort: " << endl;
	//PrintArr(arr1, 10);
	//BubbleSort(arr1, 10);
	//cout << "After bubble sort: " << endl;
	//PrintArr(arr1, 10);
	//int arr2[10] = {8, 1, 8, -4, 1, 10, 20, 6, 3, 15};
	//cout << "Before bubble sort: " << endl;
	//PrintArr(arr2, 10);
	//BubbleSort(arr2, 10);
	//cout << "After bubble sort: " << endl;
	//PrintArr(arr2, 10);

	//Node* list = nullptr;
	//AddElementToList(&list, 5);
	//AddElementToList(&list, 3);
	//AddElementToList(&list, -12);
	//PrintList(list);
	//while(list != nullptr){
	//	cout << list->val << endl;
	//	PopFrontOfList(&list);
	//}
	//AddElementToList(&list, 1);
	//InsertNodeToSortedList(&list, new Node(0));
	//PrintList(list);
	//AddElementToList(&list, 6);
	//AddElementToList(&list, 8);
	//AddElementToList(&list, 12);
	//PrintList(list);
	//InsertValToSortedList(&list, -10);
	//InsertValToSortedList(&list, 7);
	//InsertValToSortedList(&list, 25);
	//PrintList(list);
	//while(list != nullptr)
	//	PopFrontOfList(&list);
	//AddElementToList(&list, 24);
	//AddElementToList(&list, 12);
	//AddElementToList(&list, -10);
	//AddElementToList(&list, 50);
	//AddElementToList(&list, -90);
	//AddElementToList(&list, 5);
	//cout << "Insertion sort for linked list below: " << endl;
	//PrintList(list);
	//InsertionSortList(&list);
	//cout << "After sorted algorithm: " << endl;
	//PrintList(list);


	//Item arr3[6] = {13425, 342, 543, 654, 2345, 32};
	//cout << "Array before radix sort: " << endl;
	//PrintArr(arr3, 6);
	//RadixSort(arr3, 6);
	//cout << "Array after radix sort: " << endl;
	//PrintArr(arr3, 6);
	//Item arr4[7] = {12, 4, 1, 4, 5, 4, 0};
	//Item arr5[7] = {12, 4, 1, 4, 5, 4, 0};
	//BinBucketSort(arr5, 7);
	//PrintArr(arr5, 7);
	//CountSort(arr4, 7);
	//PrintArr(arr4, 7);

	//Item arr6[7] = {43, 1, 54, 3, 7, 18, -15};
	//cout << "Array before selection sort: " << endl;
	//PrintArr(arr6, 7);
	//SelectionSort(arr6, 7);
	//cout << "Array after selection sort: " << endl;
	//PrintArr(arr6, 7);
	Item arr7[11] = {0, 50, -70, 60, -90, 10, 10, 10, 20, 0,  40};
	
	//PrintArr(arr6, 11);
	//quicksort(arr7, 0, 11);
	//PrintArr(arr7, 11);

	Item arr8[9] = {4, 1, 5, 0, 0, 0, -1, -1, 2};
	
	//mergeArrDiapasons(arr8, 0, 1, 2);
	//PrintArr(arr8, 10);
	//mergeArrDiapasons(arr8, 2, 3, 4);
	//PrintArr(arr8, 10);
	//mergeArrDiapasons(arr8, 4, 5, 6);
	//PrintArr(arr8, 10);
	//mergeArrDiapasons(arr8, 6, 7, 8);
	PrintArr(arr7, 11);
	ShellSortArr(arr7, 11, 2);
	PrintArr(arr7, 11);


	PrintArr(arr8, 9);
	ShellSortArr(arr8, 9, 2);
	PrintArr(arr8, 9);
	//Node* list2 = nullptr;
	//AddElementToList(&list2, 24);
	//AddElementToList(&list2, 12);
	//AddElementToList(&list2, -10);
	//AddElementToList(&list2, 50);
	//AddElementToList(&list2, -90);
	//AddElementToList(&list2, 5);
	//cout << "List before merge sorting: " << endl;
	//PrintList(list2);
	//cout << "List after merge sorting: " << endl;
	//PrintList(MergeSortList(list2));
	return 0;
}
