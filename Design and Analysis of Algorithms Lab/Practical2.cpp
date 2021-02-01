#include <iostream>
#include <string>
#include <chrono>
#include <math.h>
#include <iomanip>
#include <stdlib.h>
#include <algorithm>
#include <climits>

#define cell_size 25
#define filler ' '

using namespace std;
using namespace chrono;

void swap(int *a, int *b)
{
    int dummy = *a;
    *a = *b;
    *b = dummy;
}

void fill_elements(int* array, int size)	//Function to randomly initialize sample arrays
{
	float k = 2;

	srand(time(NULL));
	for (int i = 0; i < size; i++)
	{
		array[i] = abs(rand() % (3 * size) + (size/k));
		k = int(sqrt(array[i])*3.14);
	}
}

void print_number(long num, string terminator = "")  //To print numbers formatted by commas
{
    string s = std::to_string(num);
    int n = s.length() - 3;
    while (n > 0) {
        s.insert(n, ",");
        n -= 3;
    }
    cout << setw(cell_size-5) << s << terminator;
}

class arrays
{
public:
    
    //Address Oriented implementation (My implementation)
    int* findMOM(int** addresses, int size) //Returns the memory address of Median of Medians of given array
    {
        const int split = 5;                //Subset size per iteration i.e. array[45] = 9 subarrays
                                            
        if (size <= split)                  //Insertion sort and return median
        {
            for (int i = 0; i < size; i++)
                for (int j = i+1; j < size; j++)
                    if (*addresses[j] < *addresses[i])
                    {
                        int* dummy = addresses[i];
                        addresses[i] = addresses[j];
                        addresses[j] = dummy;
                    }
            return (addresses[size/2]);
        }

        int* shortlist[size/split];         //to store median of each subset
        int* subset[split];                 //to store one subset at a time
        for(int i = 0; i < size; i+=split)
        {
            int subset_size = (size-i >= split? split : size-i);
            //2833 ahmd howrah
            for(int j = 0; j < split; j++)  //Extract from original array into subset
                subset[j] = addresses[i+j];

            shortlist[i/split] = findMOM(subset, subset_size);  //Put Medians of subset into shortlist
        }

        return findMOM(shortlist, size/split);  //Recur to find median of the (shortlisted) medians
    }

    void quick_sort(int* arr, int low, int high)    //Entire original array, low:high are slice indices wrt original array
    {
        if(low < high)
        {
            int* addresses[high-low+1]; //Map the partition(array) elements with their respective addresses
            for(int i=0; i< high-low+1; i++) addresses[i] = &arr[low+i];

            int pivot_index = findMOM(addresses, high-low+1) - arr; //Pivot index is w.r.t. original array

            swap(arr[pivot_index], arr[high]);  //Swap pivot with the last element in partition(array)

            int pivot = arr[high];
            int i = low - 1; // Index of smaller element  

            for (int j = low; j <= high - 1; j++)               //Throw elements around pivot
                if (arr[j] < pivot) swap(&arr[++i], &arr[j]);  

            swap(&arr[i + 1], &arr[high]);                      //Place pivot
            
            int m (i + 1);                                      //Pivot index
            quick_sort(arr, low, m - 1);                        //Recur left of pivot
            quick_sort(arr, m + 1, high);                       //Recur right of pivot
        }
    }
    
    //Basic Implementation  (My implementation)
    int partition(int* arr, int low, int high)  
    {  
        int pivot = arr[high]; // pivot  
        int i = (low - 1); // Index of smaller element  
    
        for (int j = low; j <= high - 1; j++)   
            if (arr[j] < pivot)  
                swap(&arr[++i], &arr[j]);  
        
        swap(&arr[i + 1], &arr[high]);  
        return (i + 1);  
    }  
    
    void basic_quick_sort(int* arr, int low, int high)  
    {  
        if (low < high)  
        {  
            int m = partition(arr, low, high);  
    
            // Separately sort elements before  
            // partition and after partition  
            basic_quick_sort(arr, low, m - 1);  
            basic_quick_sort(arr, m + 1, high);  
        }  
    }  

    //Search for MoM based implementation (Taken from geeksforgeeks.com)
    int partition(int arr[], int l, int r, int x)       // It searches for x in array, and partitions the array around x.
    {
        // Search for x in array and move it to end
        int i;
        for (i=l; i<r; i++)
            if (arr[i] == x)
            break;
        swap(&arr[i], &arr[r]);
    
        // Standard partition algorithm
        i = l;
        for (int j = l; j <= r - 1; j++)
        {
            if (arr[j] <= x)
            {
                swap(&arr[i], &arr[j]);
                i++;
            }
        }
        swap(&arr[i], &arr[r]);
        return i;
    }
    
    int findMedian(int arr[], int n)                    // A simple function to find median of arr[] For array size of 5
    {
        sort(arr, arr+n); // Sort the array
        return arr[n/2]; // Return middle element
    }
    
    int kthSmallest(int arr[], int l, int r, int k)     // Returns k'th smallest element in array in worst case linear time.
    {
        // If k is smaller than number of elements in array
        if (k > 0 && k <= r - l + 1)
        {
            int n = r-l+1; // Number of elements in arr[l..r]
    
            // Divide arr[] in groups of size 5, calculate median of every group and store it in median[] array.
            int i, median[(n+4)/5]; // There will be floor((n+4)/5) groups;
            for (i=0; i<n/5; i++)
                median[i] = findMedian(arr+l+i*5, 5);
            if (i*5 < n) //For last group with less than 5 elements
            {
                median[i] = findMedian(arr+l+i*5, n%5);
                i++;
            }
    
            // Find median of all medians using recursive call if more than 1 median
            int medOfMed = (i == 1)? median[i-1]:
                                    kthSmallest(median, 0, i-1, i/2);
    
            // Partition the array around a random element and get position of pivot element in sorted array
            int pos = partition(arr, l, r, medOfMed);
    
            // If position is same as k
            if (pos-l == k-1)
                return arr[pos];
            if (pos-l > k-1) // If position is more, recur for left
                return kthSmallest(arr, l, pos-1, k);
    
            // Else recur for right subarray
            return kthSmallest(arr, pos+1, r, k-pos+l-1);
        }
    
        // If k is more than number of elements in array
        return INT_MAX;
    }
    
    void mom_quick_sort(int arr[], int l, int h)
    {
        if (l < h)
        {
            // Find size of current subarray
            int n = h-l+1;
            // Find median of arr[]
            int med = kthSmallest(arr, l, h, n/2);
    
            // Partition the array around median
            int p = partition(arr, l, h, med);
    
            // Recur for left and right of partition
            mom_quick_sort(arr, l, p - 1);
            mom_quick_sort(arr, p + 1, h);
        }
    }

    //Utility Functions
    void print(string title, int** addresses, int size)         //To print array by given address list
    {
        cout << '\n' << title << '\n';
        
        for(int i=0; i<size; i++)
            cout << *addresses[i] << "  ";

        cout << '\n';
    }
    
    void _print(string title, int *arr, int arr_size)           //To print given array
    {
        cout << '\n' << title << '\n';
        
        for(int i=0; i<arr_size; i++)
            cout << arr[i] << "  ";

        cout << '\n';
    }
};

void analyse(int* arr, int size, int iterations)
{
    cout << "\n\nElements : " << size << endl << endl;
    cout << setfill(filler) << setw(cell_size-10) << "Iteration";
    cout << setfill(filler) << setw(cell_size) << "My MoM + QS";
    cout << setfill(filler) << setw(cell_size) << "Mom + QS of GFG";
    cout << setfill(filler) << setw(cell_size) << "Basic QS";
    cout << "\n";

    arrays array_manager;

    long a_times_sum = 0, b_times_sum = 0, c_times_sum = 0;

    for(int i = 0; i < iterations; i++)
    {
        fill_elements(arr, size);

        int* copy1  = (int*) malloc(size * sizeof(int));    //Making copies for each methods
        int* copy2  = (int*) malloc(size * sizeof(int));    //because some operations may be in-place
        int* copy3  = (int*) malloc(size * sizeof(int));
        copy(arr, arr+size, copy1);
        copy(arr, arr+size, copy2);
        copy(arr, arr+size, copy3);

        cout << setw(cell_size-11) << i << "]";
        //array_manager._print("Original Array : ", arr, size);

        auto start = high_resolution_clock::now();					//Start timing
            //array_manager._print("Copy1 Array : ", arr, size);
            array_manager.quick_sort(copy1, 0, size-1);
            //array_manager._print("Sorted : ", copy1, size);
        auto stop = high_resolution_clock::now();					//Stop timing
        auto duration_first = duration_cast<nanoseconds>(stop - start);

        print_number(duration_first.count(), " (ns)");
        a_times_sum += duration_first.count();

        start = high_resolution_clock::now();					//Start timing
            //array_manager._print("Copy2 Array : ", arr, size);
            array_manager.mom_quick_sort(copy2, 0, size-1);
            //array_manager._print("Sorted : ", copy2, size);
        stop = high_resolution_clock::now();					//Stop timing
        auto duration_second = duration_cast<nanoseconds>(stop - start);

        print_number(duration_second.count(), " (ns)");
        b_times_sum += duration_second.count();
        
        start = high_resolution_clock::now();					//Start timing
            //array_manager._print("Copy2 Array : ", arr, size);
            array_manager.basic_quick_sort(copy2, 0, size-1);
            //array_manager._print("Sorted : ", copy2, size);
        stop = high_resolution_clock::now();					//Stop timing
        auto duration_third = duration_cast<nanoseconds>(stop - start);

        print_number(duration_third.count(), " (ns)\n");
        c_times_sum += duration_third.count();
    }

    cout << endl;
    cout << setfill(filler) << setw(cell_size-10) << "Avg Time";
    print_number(a_times_sum/iterations, " (ns)");
    print_number(b_times_sum/iterations, " (ns)");
    print_number(c_times_sum/iterations, " (ns)");
}

int main()
{    
    cout << "EXECUTING";

    const int size1 = 50000;
    int* arr1 = (int*) malloc(size1 * sizeof(int));
    
    const int size2 = 100000;
    int* arr2 = (int*) malloc(size2 * sizeof(int));

    analyse(arr1, size1, 5);
    analyse(arr2, size2, 5);

    return 0;
}