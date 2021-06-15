#include <iostream>
#include <vector>

using namespace std;

// This code emplements operations with max heap 
 
void InsertToHeap(vector<int>& heap_array, int key){
    // O(log2(n)) - reducing index by 2 every step
    size_t i = heap_array.size();
    heap_array.emplace_back(key);
    // Finding parent node for inserted key.
    // Heap is a complete binary tree represented as array.
    // So the parent index of current element if element has even index is: (index / 2) - 1
    // else index / 2. 
    size_t parent_index = i % 2 == 0 ? (i / 2) - 1 : i / 2;
    
    // Finding element, which bigger than inserted key.
    // If condition of loop is true, we assign to position of current index of 
    // inserted element i found element (parent element) if this element
    // smaller than inserted key. Then we assign to i value of parent index
    // and recalculate parent_index.
    while(i > 0 && key > heap_array[parent_index]){
        heap_array[i] = heap_array[parent_index];
        i = parent_index;
        parent_index = i % 2 == 0 ? (i / 2) - 1 : i / 2;
    }
    // i after while loop is position in which should be assign inserted key 
    heap_array[i] = key;
}

int DeleteFromHeap(vector<int>& heap_array){
    // Deletion from heap is O(log2(n)) order
    size_t heap_size = heap_array.size();
    if(heap_size == 0){
        return -1;
    }
    int deleted_element = heap_array[0];
    heap_array[0] = heap_array[heap_size - 1];
    heap_array.pop_back();

    int parent_index = 0;
    // set for default value index of left child of root
    int child_index = 2 * parent_index + 1;

    while(child_index < heap_size - 1){
        if(child_index + 1 < heap_size && heap_array[child_index] < heap_array[child_index + 1]){
            child_index++;
        }

        if(heap_array[parent_index] < heap_array[child_index]){
            swap(heap_array[parent_index], heap_array[child_index]);
            // go to child root
            parent_index = child_index;
            child_index = 2 * parent_index + 1;
        }
        else{
            break;
        }
    }
    return deleted_element;
}

// Heapify C++ dynamic array - this operation has O(n). This function
// faster than creation of heap with using InsertToHeap (order O(nlog2(n)))
void Heapify(vector<int>& heap_array){
    // Detected first element which has child (not leaf node)
    // Index of this element: i = (size of heap_array / 2) - 1
    size_t heap_size = heap_array.size();
    if(heap_size < 2){
        return;
    }
    for(int parent_index  = (heap_size / 2) - 1; parent_index >= 0; parent_index--){
        int child_index = 2 * parent_index + 1; // left child of parent node

        while(child_index < heap_size - 1)
        {
            // Check if right node bigger than left node
            if(child_index + 1 < heap_size && heap_array[child_index] < heap_array[child_index + 1])
            {
                child_index++;
            }

            if(heap_array[child_index] > heap_array[parent_index]){
                swap(heap_array[child_index], heap_array[parent_index]);
                // change parent_index with child_index
                parent_index = child_index;
                // calculate new child_index
                child_index = 2 * parent_index + 1;
            }
            else{
                // Value on the right place in heap_array
                break;
            }
        }
    }
}



 
int main() {
    vector<int> heap = {10, 20, 50, 15, 17, 30, 40};
    Heapify(heap);
    cout << "After heapify: ";
    for(auto& element : heap){
        cout << element << " ";
    }
    cout << endl;
    vector<int> sorted;
    for(auto& element : heap){
        sorted.emplace_back(DeleteFromHeap(heap));
    }
    cout << "Heap sort: ";
    for(auto& element : sorted){
        cout << element << " ";
    }
    cout << endl;

    // Heap can be used as priority queue, because from heap operation delete
    // deleted max element (or min if min heap used).

    return 0;
}
