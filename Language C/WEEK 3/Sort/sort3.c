#include <cs50.h>
#include <stdio.h>

// Function declaration
void sort_array(int values[], int size);

int main(void)
{
    int values[8] = {7, 2, 5, 1, 3, 6, 4, 0};

    // Function Recall
    sort_array(values, 8);

    for (int i = 0; i < 8; i++)
    {
        printf("%i ", values[i]);
    }

    printf("\n");
}

// Function definition
void sort_array(int values[], int size)
{
    for (int i = 0; i < size; i++)
    {
        int min = i;

        for (int j = i + 1; j < size; j++)
        {
            if (values[j] < values[min])
            {
                min = j;
            }
        }

        int temp = values[i];
        values[i] = values[min];
        values[min] = temp;
    }
}
