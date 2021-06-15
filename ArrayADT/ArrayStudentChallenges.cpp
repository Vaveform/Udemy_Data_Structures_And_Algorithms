#include <iostream>
#include <vector>

using namespace std;

// Finding one missing element in sorted array like: k, k+1, k+2 ... n, where k is int 
void FindingMissingElement(int sorted_array[], const size_t size){
    int diff = sorted_array[0];
    for(int i = 1; i < size; i++){
        if(sorted_array[i] - i != diff){
            cout << "Missing element: " << i + diff << endl;
            break;
        }
    }
}

// Finding several missing elements in sorted array like: k, k+1, k+2 ... n
void FindingMissingElements(int sorted_array[], const size_t size){
    int diff = sorted_array[0];
    for(int i = 1; i < size; i++){
        if(diff != sorted_array[i] - i){
            // if diff not equal to sorted_array[i] - i
            // diff can be only smaller than sorted_array[i] - i, because array sorted
            while(diff < sorted_array[i] - i){
                cout << "Missing element: " << i + diff << endl;
                diff++;
            }
        }
    }
}

// Structure to keep min and max value
struct MinMax{
    int min_value;
    int max_value;
};

// Finding min and max by one scan
MinMax FindMinMax(int array[], const size_t size){
    MinMax result;
    result.min_value = array[0];
    result.max_value = array[0];
    for(int i = 1; i < size; i++ ){
        if(array[i] < result.min_value){
            result.min_value = array[i];
        }
        else if(array[i] > result.max_value){
            result.max_value = array[i];
        }
    }
    return result;
}

// Finding missing elements in unsorted array - O(n) using hash table
void FindMissingElementsUnsorted(int array[], const size_t size){
    MinMax minmax = FindMinMax(array, size);
    // allocate in heap hash table(array)
    int* hash_table = new int[minmax.max_value + 1]();
    // n - times
    for(int i = 0; i < size; i++){
        hash_table[array[i]]++;
    }
    // n - times
    for(int i = minmax.min_value; i < minmax.max_value + 1; i++){
        if(hash_table[i] == 0){
            cout << "Missing element: " << i << endl;
        }
    }
    // Summary complexity: n + n = 2n => O(2n) = O(n)
    // Summary memory complexity: O(q), where q - max value of input array

    // deleting dynamically created (on heap array)
    delete[] hash_table;
}


// Finding duplicates in sorted array and printing number of duplicates
void FindDuplicatesInSorted(int sorted_array[], const size_t size){
    // example: 3 6 8 8 10 12 15 15 15 20
    // Order of complexity: O(n) - in nested while loop to i assign result j iteration
    for(int i = 0; i < size - 1; i++){
        if(sorted_array[i] == sorted_array[i + 1]){
            int j = i + 1;
            while(sorted_array[i] == sorted_array[j]) j++;
            cout << "Value " << sorted_array[i] << " has " << j - i - 1 << " duplicates" << endl;
            // j - 1 because on next step of for loop i will be incremented
            i = j - 1;
        }
    }

}

void FindDuplicatesInSortedHashing(int sorted_array[], const int size){
    // array is sorted:
    int min = sorted_array[0];
    int max = sorted_array[size-1];
    int* hash_table = new int[max + 1]();
    // n - complexity
    for(int i = 0; i < size; i++){
        hash_table[sorted_array[i]]++;
    }
    // n - complexity
    for(int i = min; i < max + 1; i++){
        if(hash_table[i] > 1){
            cout << "Value " << i << " has " << hash_table[i] - 1 << " duplicates" << endl;
        }
    }
    // Time complexity O(2n) => O(n)
    delete[] hash_table;
}

void FindDuplicatesInUnsorted(int array[], const int size){
    // Bad complexity -> O(n^2)
    for(int i = 0; i < size - 1; i++){
        int count = 1;
        if(array[i] != -1){
            for(int j = i + 1; j < size; j++){
                if(array[i] == array[j]){
                    count++;
                    array[j] = -1;
                }
            }
            if(count > 1){
                cout << "Value " << array[i] << " has " << count - 1 << " duplicates" << endl;
            }
        }
    }
}

void FindDuplicatesInUnsortedHashing(int array[], const int size)
{
    // FindMinMax - O(n) - n complexity
    MinMax minmax = FindMinMax(array, size);
    int* hash_table = new int[minmax.max_value + 1]();
    // Filling hash_table - n complexity
    for(int i = 0; i < size; i++){
        hash_table[array[i]]++;
    }
    for(int i = minmax.min_value; i < minmax.max_value + 1; i++){
        if(hash_table[i] > 1){
            cout << "Value " << i << " has " << hash_table[i] - 1 << " duplicates" << endl;
        }
    }
    delete[] hash_table;
}

// This function find sets of two elements sum of which gives result equal to k
void FindPairSumKInUnsorted(int array[], const int size, int k){
    // two nestes for loop - O(n^2) complexity
    for(int i = 0; i < size - 1; i++){
        for(int j = i + 1; j < size; j++){
            if(array[j] + array[i] == k){
                cout << "A[" << i << "] + A[" << j << "]=" << array[i] << "+" << array[j] << "=" << k << endl;
            }
        }
    }
}

// Find sets of two elements sum of which gives result equal to k
void FindPairSumKInUnsortedHashing(int array[], const int size, int k){
    // Complexity = O(2n) = O(n)
    // Space = O(q), where q - max element
    MinMax minmax = FindMinMax(array, size);
    int* hash_table = new int[minmax.max_value + 1]();
    for(int i = 0; i < size; i++){
        // Check if diff is located in hash_table
        if(k - array[i] > 0 && hash_table[k - array[i]] > 0){
            cout << array[i] << " + " << k - array[i] << " = " << k << endl; 
        }
        // Marked detected value
        hash_table[array[i]]++;
    }
    delete[] hash_table;
}

void FindPairSumKInSorted(int sorted_array[], const int size, int k){
   // Complexity = O(n)
   int i = 0, j = size - 1;
   // While loop working when left pointer (i) smaller than right pointer (j)
   while(i < j){
       // If value in index i and value in index j give sum equal to k
       // increment small index and decrement big index
       if(sorted_array[i] + sorted_array[j] == k){
           cout << "A[" << i << "] + A[" << j << "]=" << sorted_array[i] << "+" << sorted_array[j] << "=" << k << endl;
           i++;
           j--;
       }
       // If sum of values smaller than k, we should decrease sum
       // by taken bigger value (increment small index)
       else if(sorted_array[i] + sorted_array[j] < k){
           i++;
       }
       // If sum bigger than k, we should increase sum
       // by taken smaller value (decrement big index)
       else{
           j--;
       }
   }
}

int main(){
    const size_t size1 = 10;
    int arr1[size1] = {6,7,8,9,10,11,12,13,14,16};
    FindingMissingElement(arr1, size1);

    const size_t size2 = 8;
    int arr2[size2] = {1,5,6,7,16,17,18,20};
    FindingMissingElements(arr2, size2);

    const size_t size3 = 6;
    int arr3[size3] = {4, 1, 5, 12, 6, 10};
    MinMax minmax = FindMinMax(arr3, size3);
    cout << "Min value: " << minmax.min_value << endl;
    cout << "Max value: " << minmax.max_value << endl;

    FindMissingElementsUnsorted(arr3, size3);

    const size_t size4 = 10;
    int arr4[size4] = {3, 6, 8, 8, 10, 12, 15, 15, 15, 20};
    FindDuplicatesInSorted(arr4, size4);
    FindDuplicatesInSortedHashing(arr4, size4);

    const size_t size5 = 10;
    int arr5[size5] = {8, 3, 6, 4, 6, 5, 6, 8, 2, 7};
    int arr6[size5] = {8, 3, 6, 4, 6, 5, 6, 8, 2, 7};
    FindDuplicatesInUnsorted(arr5, size5);
    FindDuplicatesInUnsortedHashing(arr6, size5);
    
    const size_t size6 = 10;
    // Unsorted
    int arr7[size6] = {6, 3, 8, 10, 16, 7, 5, 2, 9, 14};
    // Sorted
    int arr8[size6] = {1, 3, 4, 5, 6, 8, 9, 10, 12, 14};
    
    FindPairSumKInUnsorted(arr7, size6, 10);
    FindPairSumKInUnsortedHashing(arr7, size6, 10);
    FindPairSumKInSorted(arr8, size6, 10);


    return 0;
}
