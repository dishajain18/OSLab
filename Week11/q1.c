#include <stdio.h>
#include <stdlib.h>
int n,m;

int display(int Allocation[][m],int Need[][m],int  Available[m] )
{
	printf("\nAllocation Matrix: ");
	for(int i=0;i<n;i++)
	{
	  printf("\nP%d",i);
	  for(int j=0;j<m;j++)
	   printf(" %d",Allocation[i][j]);
	}

	printf("\nNeed Matrix: ");
	for(int i=0;i<n;i++)
	{
	  printf("\nP%d",i);
	  for(int j=0;j<m;j++)
	   printf(" %d",Need[i][j]);
	}

	printf("\nAvailable:");
	for(int j=0;j<m;j++)
	   printf(" %d",Available[j]);
	printf("\n");
}

int isSafe(int Allocation[][m],int Need[][m],int  Available[m] )
{
	int Work[m],Finish[n];
	for(int i=0;i<m;i++)
		{
			Work[i]=Available[i];
		}
	for (int i = 0; i < n; i++) {
        Finish[i] = 0; // All processes are initially unfinished
    }

	int safeseq[n];
	int pos=0;
	int safe;
	while(pos<n)
	{
	  safe=0;
      for(int i=0;i<n;i++)
      {
          if(Finish[i])
	        continue;

	      else
	      {
	      	int j=0;
	      	while(Need[i][j]<=Work[j]&&j<m)
	      	  j++;
	      	if (j<m)
	      		continue;
	   
	      }
    
      	   safe = 1 ; //found safe process
	       for(int j=0;j<m;j++)
      	     Work[j]+=Allocation[i][j];
      	   Finish[i]=1;
           safeseq[pos++]=i;
	   }

	   if(!safe)
	   	{
	   		printf("\nSystem is not safe\n");
	   		return 0;
	   	}

    }
      
    printf("\nSystem is safe\n");
    printf("Safe sequence:");
    for(int i=0;i<n;i++)
    	printf(" %d",safeseq[i]);
    printf("\n");
    return 1;
	
}

void resource_request(int p,int Allocation[][m],int Need[][m],int  Available[m],int Request[m])
{
	for(int j=0;j<m;j++)
		if(Need[p][j]<Request[j])
		{
			printf("Request Denied, exceeding Need\n");
			return;
		}
	for(int j=0;j<m;j++)
		if(Available[j]<Request[j])
		{
			printf("Try Again Later, Not enough Resources\n");
			return;
		}

	for(int j=0;j<m;j++)
	{
		Available[j]-=Request[j];
		Allocation[p][j]+=Request[j];
		Need[p][j]-=Request[j];
	}


	if(isSafe(Allocation,Need,Available))
	{
		printf("Request Granted\n");
		display(Allocation,Need,Available);
	}

	else
	{
		printf("Request Denied\n");
		for(int j=0;j<m;j++)
		{
			Available[j]+=Request[j];
			Allocation[p][j]-=Request[j];
			Need[p][j]+=Request[j];
		}
		display(Allocation,Need,Available);
	}


}

int main()
{
    printf("No. of Processes? ");
    scanf("%d", &n);
    printf("No. of Resource Types? ");
    scanf("%d", &m);

    int Allocation[n][m], Max[n][m], Need[n][m];
    int Available[m];

    // Input Allocation Matrix
    printf("Allocation Matrix: \n");
    for (int i = 0; i < n; i++) {
        printf("P%d ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &Allocation[i][j]);
        }
    }

    // Input Max Matrix
    printf("Max Matrix: \n");
    for (int i = 0; i < n; i++) {
        printf("P%d ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &Max[i][j]);
        }
    }

    // Input Available resources
    printf("Available: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &Available[i]);
    }

    // Calculate and display Need Matrix
    printf("Need Matrix: \n");
    for (int i = 0; i < n; i++) {
        printf("P%d ", i);
        for (int j = 0; j < m; j++) {
            Need[i][j] = Max[i][j] - Allocation[i][j];
            printf("%d  ", Need[i][j]);
        }
        printf("\n");
    }

    isSafe(Allocation,Need,Available);

    while(1)
    {
    	printf("\n\nEnter Requesting process (-1 to exit): ");
    	int p;
    	scanf("%d",&p);
    	if(p<0||p>=n)
    		break;
    	printf("Enter request: ");
    	int Request[m];
    	for(int j=0;j<m;j++)
    	{
    		scanf("%d",&Request[j]);
    		printf("%d\n",Request[j]);
    	}
    	resource_request(p,Allocation,Need,Available,Request);
    }

    return 0;

}