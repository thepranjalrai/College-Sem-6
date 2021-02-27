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

long comparison_counter = 0;

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

    static void merge(int* arr, int min_index, int mid_index, int max_index)
    {
        int left_size = mid_index - min_index + 1;
        int right_size = max_index - mid_index;

        int left_half[left_size], right_half[right_size];

        for (int i = 0; i < left_size; i++)
            left_half[i] = arr[min_index + i];
        for (int i = 0; i < right_size; i++)
            right_half[i] = arr[mid_index + 1 + i];

        int left_index = 0, right_index = 0, main_index = min_index;

        //count this loop
        while (left_index < left_size && right_index < right_size) {
            if (left_half[left_index] <= right_half[right_index]) {
                arr[main_index] = left_half[left_index];
                left_index++;
            }
            else {
                arr[main_index] = right_half[right_index];
                right_index++;
            }
            main_index++;
            comparison_counter++;
        }

        while (left_index < left_size) {
            arr[main_index] = left_half[left_index];
            left_index++;
            main_index++;
        }

        while (right_index < right_size) {
            arr[main_index] = right_half[right_index];
            right_index++;
            main_index++;
        }
    }

static void merge_sort(int* arr,int l,int r){
	if(l>=r){
		return;
	}
	int m =l+ (r-l)/2;
	merge_sort(arr,l,m);
	merge_sort(arr,m+1,r);
	merge(arr,l,m,r);
}
    //Utility Functions
    static void _print(string title, int *arr, int arr_size)           //To print given array
    {
        cout << '\n' << title << '\n';
        
        for(int i=0; i<arr_size; i++)
            cout << arr[i] << "  ";

        cout << '\n';
    }
};

void analyse_sorted_unsorted(int* arr, int size, int iterations)
{
    cout << "\nElements : ";// << size << endl << endl;
    print_number(size, " \n\n");
    cout << setfill(filler) << setw(cell_size-10) << "Iteration";
    cout << setfill(filler) << setw(cell_size) << "Unsorted Pass";
    cout << setfill(filler) << setw(cell_size-5) << "Comparisons";
    cout << setfill(filler) << setw(cell_size) << "Sorted Pass ";
    cout << setfill(filler) << setw(cell_size-5) << "Comparisons";
    cout << "\n";

    arrays array_manager;

    long a_times_sum = 0, b_times_sum = 0;

    for(int i = 0; i < iterations; i++)
    {
        fill_elements(arr, size);   //New random elements are put into the array

        int* copy1  = (int*) malloc(size * sizeof(int));    //Array is made into a copy for debugging purposes
        copy(arr, arr+size, copy1);

        cout << setw(cell_size-11) << i << "]";
        //array_manager._print("Original Array : ", arr, size);

        auto start = high_resolution_clock::now();					//Start timing
            //array_manager._print("Unsorted Array : ", copy1, size);
            array_manager.merge_sort(copy1, 0, size-1);
            //array_manager._print("Sorted : ", copy1, size);
        auto stop = high_resolution_clock::now();					//Stop timing
        auto duration_first = duration_cast<nanoseconds>(stop - start);

        print_number(duration_first.count(), " (ns)");
        print_number(comparison_counter);
        a_times_sum += duration_first.count();
        comparison_counter = 0;

        start = high_resolution_clock::now();					//Start timing
            //array_manager._print("Sorted Array : ", copy1, size);
            array_manager.merge_sort(copy1, 0, size-1);
            //array_manager._print("Sorted : ", copy1, size);
        stop = high_resolution_clock::now();					//Stop timing
        auto duration_second = duration_cast<nanoseconds>(stop - start);

        print_number(duration_second.count(), " (ns)");
        print_number(comparison_counter, "\n");
        b_times_sum += duration_second.count();
        comparison_counter = 0;
    }

    cout << endl;
    cout << setfill(filler) << setw(cell_size-10) << "Avg Time";
    print_number(a_times_sum/iterations, " (ns)");
    print_number(b_times_sum/iterations, " (ns)\n");
}

int main()
{    
    cout << "EXECUTING\n";

    const int size1 = 50000;
    int* arr1 = (int*) malloc(size1 * sizeof(int));
    
    const int size2 = 100000;
    int* arr2 = (int*) malloc(size2 * sizeof(int));

    /*
    fill_elements(arr1, size1);
    arrays::_print("Unsorted", arr1, size1);
    arrays::merge_sort(arr1, 0, size1-1);
    arrays::_print("Sorted", arr1, size1);
    */

    cout << "_______________________________________________\n\n";
    cout << "Sorted and Unsorted Pass of Merge Sort\n";
    analyse_sorted_unsorted(arr1, size1, 5);
    analyse_sorted_unsorted(arr2, size2, 5);

    return 0;
}