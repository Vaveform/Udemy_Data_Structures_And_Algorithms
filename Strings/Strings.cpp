#include <iostream>
#include <string>

using namespace std;

// Using C++ because i didn't spent time to write swap function
// for swap. This functions working with set of char and generate 
// all permutations of this set. Set of symbols 
// is an array which has unique elements


// Hash function to generate index for array
// in which index - ASCII code of every symbol
int hash_function_ASCII_chars(char* symbol){
    if(*symbol >= 65 && *symbol <= 90){
        return *symbol - 65;
    }
    if(*symbol >= 97 && *symbol <= 122){
        return *symbol - 71;
    }
    return -1;
}


int decode_hash_ASCII(int ASCII_code){
    if(ASCII_code >= 0 && ASCII_code <= 25){
        return ASCII_code + 65;
    }
    if(ASCII_code >= 26 && ASCII_code <= 51){
        return ASCII_code + 71;
    }
    return 0;
}

// Finding duplicates symbols in string.
// Ideas of this function can be apply 
// for numeric arrays. In this function using bit shifting
// masking and merging. Instead of hashing using unsigned long long (64 bits array)-
// this value represents hash table
void BitwiseDuplicateChecking(char* str){
    unsigned long long hash = 0, tmp_hash = 0;
    int hash_code = 0;
    for(int i = 0; str[i] != '\0'; i++){
        tmp_hash = 1; // 00000000000000000000000001 - every time initialize
        hash_code = hash_function_ASCII_chars(&str[i]);
        //cout << "hash_code " << hash_code  << endl;
        if(hash_code == -1){
            printf("Symbol %c not a letter", str[i]);
        }
        else{
            // switch one bit to the place like in hash table
            tmp_hash = tmp_hash << hash_code;
            // check if the bit located in the value by using masking - bitwise logical AND
            // if value will be 0 - symbol did not appear earlier
            // else - symbol duplicate

            // warning! First time compucting logical comparitions, bitwise shifting and ariphmetical
            // and then bitwise OR and AND
            // cout << (tmp_hash & hash) << endl;
            if((tmp_hash & hash) > 0){
                printf("Duplicate of %c found in position %d\n", str[i], i);
            }
            else{
                // Saving result to the variable using merging - bitwise logical OR
                hash = hash | tmp_hash;
            }
        }
    }
}


void FindingDuplicatesUsingHashing(char* str){
    // O(n) difficulty
    const int size_hash_table = 52;
    int* hash_table = new int[52]();
    int hash_code = 0;
    for(int i = 0; str[i] != '\0'; i++)
    {
        hash_code = hash_function_ASCII_chars(&str[i]);
        //cout << hash_code << endl;
        if(hash_code == -1)
        {
            printf("symbol %c not a letter\n", str[i]);
        }
        else{
            hash_table[hash_code] += 1;
        }
    }
    
    for(int i = 0; i < size_hash_table; i++)
    {
        //cout << hash_table[i] << endl;
        if(hash_table[i] > 1){
            printf("%c has %d duplicates\n", decode_hash_ASCII(i), hash_table[i] - 1);
        }
    }
    //cout << hash_table[0] << endl;
    delete[] hash_table;
}


void ReverseStringInPlace(char* str)
{
    int i = 0, j = 0;
    for(; str[j] != '\0'; j++){}
    j--;
    while(i < j){
        swap(str[i], str[j]);
        i++;
        j--;
    }
}


void ReverseStringCopy(char* str, char* result_buffer)
{
    int i = 0, j = 0;
    for(; str[j] != '\0'; j++){}
    j--;
    for(; j >= 0; j--, i++){
        result_buffer[i] = str[j];
    }
    result_buffer[i] = '\0';
}

int StringsIsEqual(char* left_str, char* right_str){
    int i = 0, j = 0;
    for(; left_str[i] != '\0' && right_str[j] != '\0'; i++, j++){
        if(left_str[i] != right_str[j]){
            break;
        }
    }
    if(left_str[i] == right_str[j]) {
        return 1;
    }
    else if(left_str[i] < right_str[j]){
        return 2;
    }
    else{
        return 0;
    }
}

int IsPalindrome(char* str){
    int length = sizeof(str);
    char* buffer = new char[length];
    ReverseStringCopy(str, buffer);
    int res = StringsIsEqual(str, buffer);
    delete[] buffer;
    return res;
}

// Check if two string are anagrams (same set of chars in string but other order)
// If two words are anagrams return 1 else 0
int IsAnagramsWithHashing(char* left, char* right){
    // Create a hash table of ASCII (for upper case and lower case)
    // upper cases in ASCII from 65 to 90
    // lower cases in ASCII from 97 to 122
    int* hash_table = new int[52]();
    int hash_code = 0;
    // O(n) - filling hash table
    for(int i = 0; left[i] != '\0'; i++){
        hash_code = hash_function_ASCII_chars(&left[i]);
        if(hash_code == -1){
            printf("symbol %c not a letter\n", left[i]);
        }
        else{
            hash_table[hash_code] += 1;
        }
    }
    // O(n) - going by right word
    for(int i = 0; right[i] != '\0'; i++){
        hash_code = hash_function_ASCII_chars(&right[i]);     
        if(hash_code == -1){
            printf("symbol %c not a letter\n", right[i]);
        }
        else{
            hash_table[hash_code] -= 1;
            if(hash_table[hash_code] < 0){
                delete[] hash_table;
                return 0;
            }
        }
    }
    // Difficulty of these function is O(2*n) => O(n)
    delete[] hash_table;
    return 1;
}

// Backtracking + recursion = brutforce all combinations


// Char_set_permutation1 - simple version and make smaller number of calls.
// l - index of begin char_set and h - index of end char_set(inclusive)
// in this function parametr str should be like a array
// access to symbol char* in swap throw signal Segmentation fault
void Char_set_permutation1(char* str, int l, int h){
    if(l == h){
        printf("%s\n", str);
    }
    else{
        for(int i = l; i <= h; i++){
            swap(str[l], str[i]);
            Char_set_permutation1(str, l+1, h);
            swap(str[l], str[i]);
        }
    }
}


// Chars_permutation - version with static variables - experimental
// This function shows how to work with backtracking
// and how to use recustion and loops to build state space tree
// k - index, from which algorithm start working
// str - pointer to a char_set
// res_buffer - pointer to buffer in which will be store combinations
// hash - hash table which need to store what elements of set was used
void Chars_permutation(char* str, char* res_buffer, int* hash, int k){
    // res_buffer - to save result (combination)
    // hash - hash table to save which symbols from set was used
    if(str[k] == '\0'){
        res_buffer[k] = '\0';
        printf("%s\n", res_buffer);
    }
    else{
        for(int i = 0; str[i] != '\0'; i++){
            // Symbol from set not used earlier - check
            if(hash[i] == 0){
                // running in calling time - storing chars from 
                // set to the res_buffer
                res_buffer[k] = str[i];
                hash[i] = 1;
                Chars_permutation(str, res_buffer, hash, k+1);
                // running in returning time - when call stack
                // start clean up
                hash[i] = 0;
            }
        }
    }
}


void Char_set_permutation2(char* str, int k){
    int size_of_set = sizeof(str);
    char* res_buffer = new char[size_of_set];
    int* hash = new int[size_of_set];
    Chars_permutation(str, res_buffer, hash, k);
    delete [] res_buffer;
    delete [] hash;
}

int main(){
    char char_set[] = "ABC";
    printf("First method to generate all permutations(two swap) of char set %s\n", char_set);
    Char_set_permutation1(char_set, 0, 2);
    printf("Second method to generate all permutations of char set %s\n", char_set);
    Char_set_permutation2(char_set, 0);

    char left_string[] = "decimal";
    char right_string[] = "medical";
    char right_string2[] = "madam";
    printf("%s and %s are anagrams? %d\n", left_string, right_string, IsAnagramsWithHashing(left_string, right_string));
    
    printf("%s and %s are anagrams? %d\n", left_string, right_string2, IsAnagramsWithHashing(left_string, right_string2));
    BitwiseDuplicateChecking(right_string2);
    FindingDuplicatesUsingHashing(right_string2);
    ReverseStringInPlace(left_string);
    printf("%s\n", left_string);
    printf("%s is palindrome(True if 1)? %d\n",right_string, IsPalindrome(right_string));
    return 0;
}
