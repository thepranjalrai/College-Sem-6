#include <iostream>
#include <string>
#include <chrono>
#include <math.h>
#include <iomanip>
#include <stdlib.h>

using namespace std;
using namespace chrono;

int recursion_depth = 0;

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
		array[i] = abs(rand() % (3 * size) + (size / k));
		k = int(sqrt(array[i])*3.14);
	}
}

class arrays
{
public:
    int* findMOM(int** addresses, int size)
    {
        const int split = 5;

        if (size <= split)
        {
            for (int i = 0; i < size; i++)
                for (int j = i+1; j < size; j++)
                    if (*addresses[j] < *addresses[i])
                    {
                        int* dummy = addresses[i];
                        addresses[i] = addresses[j];
                        addresses[j] = dummy;
                    }
            
            //for(int i=0; i<size; i++) cout << setw(4) << *addresses[i];
            //cout << "\t";
            //print(">>GroundSort", addresses, size);
            return (addresses[size/2]);
        }

        int* shortlist[size/split];
        int* subset[split];
        for(int i = 0; i < size; i+=split)
        {
            int subset_size = (size-i >= split? split : size-i);
            
            //2833 ahmd howrah

            //cout << "\n" << i << "\tsubset_size = " << subset_size <<endl;
            for(int j = 0; j < split; j++)
                subset[j] = addresses[i+j];

            //print("Subset", subset, subset_size);
            shortlist[i/split] = findMOM(subset, subset_size);
            //cout << "shortlist_idx : " << i/split << " = " << shortlist[i/split] << endl;
        }

        //for(int i = 0; i < size/split; i++) cout << setw(4) << shortlist[i];
        //print("Shortlist", shortlist, size/split);


        return findMOM(shortlist, size/split);
        //for(int i=0; i<size; i++) cout << setw(4) << array[i];
    }

    void quick_sort(int* arr, int low, int high)    //Entire original array, low:high are slice indices wrt original array
    {
        if(low < high)
        {
            recursion_depth++;
            char filler = '\t';
            
            //cout <<"\n\n";
            //cout << setfill(filler) << setw(recursion_depth) << "Recursion Depth = " << recursion_depth << endl;
            //cout << setfill(filler) << setw(recursion_depth) << "Low : High = " << low << " : " << high << endl;
            
            int** addresses = (int**) malloc (high-low+1 * sizeof(int*));

            for(int i=0; i< high-low+1; i++)
            {
                addresses[i] = &arr[low+i];
                //cout << setfill(filler) << setw(recursion_depth) << "" << addresses[i] << "\t" << *addresses[i] << "\t" << arr[i] << endl;
            }

            int partition_index = findMOM(addresses, high-low+1) - arr; //Partition index is w.r.t. original array
            
            //cout << setfill(filler) << setw(recursion_depth) << "" << endl << partition_index + arr << "\tarr[" << partition_index << "] = " << arr[partition_index] << "\n";

            int dummy = arr[partition_index];
            arr[partition_index] = arr[high];
            arr[high] = dummy;

            int pivot = arr[high];
            int i = low - 1; // Index of smaller element  

            //print("............\nPass..", array_1, size_1);

            for (int j = low; j <= high - 1; j++)  
            {
                //cout << "arr[" << j << "] = " << arr[j] << " | Pivot = " << pivot;
                if (arr[j] < pivot)  
                {  
                    i++; 
                    swap(&arr[i], &arr[j]);
                    //cout << "\tSwapped..";
                }
                //print("\n > ", array_1, size_1);
            }  
            swap(&arr[i + 1], &arr[high]);  
            int m (i + 1);

            free(addresses);

            quick_sort(arr, low, m - 1);  
            quick_sort(arr, m + 1, high); 
            recursion_depth--;
        }
    }

    void print(string title, int** addresses, int size)
    {
        cout << '\n' << title << '\n';
        
        for(int i=0; i<size; i++)
        {
            cout << *addresses[i] << "  ";
        }

        cout << '\n';
    }

    void _print(string title, int *arr, int arr_size)
    {
        cout << '\n' << title << '\n';
        
        for(int i=0; i<arr_size; i++)
        {
            cout << arr[i] << "  ";
        }

        cout << '\n';
    }
};

int main()
{
    arrays array_manager;
    
    cout << "EXECUTING\n\n";
    cout << "Enter Array Size : ";
    int size;
    cin >> size;

    int* arr = (int*) malloc(size * sizeof(int));
    int** addresses = (int**) malloc (size * sizeof(int*));

    fill_elements(arr, size);
    for(int i=0; i<size; i++)
    {
        addresses[i] = &arr[i];
        //cout << addresses[i] << "\t" << *addresses[i] << "\t" << arr[i] << endl;
    }

    array_manager.print("Original Array : ", addresses, size);
    array_manager.quick_sort(arr, 0, size-1);
    array_manager.print("Sorted Array : ", addresses, size);
    //int* momLoc = array_manager.findMOM(addresses, size);
    //cout << "\n\nMomLOC : " << momLoc << "  =  " << *momLoc << endl;

    //int momidx = array_manager.findMOM(arr, size, true);
    //cout << "\n\n" << momidx << '\t' << array_manager.recursion_depth;
    //for(int i=0; i<size; i++) cout << arr[i] << endl;

    return 0;
}