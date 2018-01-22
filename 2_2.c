#include <stdio.h>

int main()
{
    //input number of elements
    int n=0;    
    printf("Please enter number of elements:");
    scanf("%d",&n);

    //input the elements
    int numList[n];
    printf("\nEnter %d integers:",n);    
    for(int i=0;i<n;i++)
    scanf("%d",&numList[i]);

    //sorting the elements
    printf("\nsorting the elements:\n");
    int t;
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-1-i;j++)
        {
            if(numList[j]>numList[j+1])
			{
				t=numList[j];
				numList[j]=numList[j+1];
				numList[j+1]=t;
			}

            //displaying the process
            for(int i=0;i<n;i++)
            printf("%d\t",numList[i]);
            printf("\n");
        }
    }

    //output the sorted elements
    printf("\nSorted list in ascending order:\n");
    for(int i=0;i<n;i++)
    printf("%d\t",numList[i]);
    printf("\n");

    return 0;
}