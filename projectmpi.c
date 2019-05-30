#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
int desc(int arr[],int i,int k,int m)
{
        if(m==-1)
            return 0;
        int temp=arr[i+m+1];
        int l=desc(arr,i,k,m-1);
        // printf("%i",l);
        int low,high;
        if(temp<arr[0])
        {
            low=-1;
        }
        else
        {
            high=i-l;
            low=0;
            do
            {
                int med=(low+high)/2;
                if(temp>arr[med])
                {
                    low=med;
                }
                else
                {
                    high=med;
                }
            }while(low<high-1);
            while(temp>=arr[low+1])
            {
                low++;
            }
        }
        k=k-l-m;
        i=i-l;
        while(i>low)
        {
            arr[k]=arr[i];
            i--;
            k--;
            l++;
        }  
        arr[k]=temp;
        return l;
}
int asc(int arr[],int i,int k,int m)
{
     
        if(m==-1)
        {
            return 0;
        }
        int temp=arr[k-m];
        int l=asc(arr,i,k,m-1);
        int low,high;
        if(temp<arr[0])
        {
            low=-1;
        }
        else
        {
            high=i-l;
            low=0;
            do
            {
                int med=(low+high)/2;
                if(temp>arr[med])
                {
                    low=med;
                }
                else
                {
                    high=med;
                }
            }while(low<high-1);
            while(temp>=arr[low+1])
            {
                low++;
            }
        }
        k=k-l-m;
        i=i-l;
        while(i>low)
        {
            arr[k]=arr[i];
            i--;
            k--;
            l++;
        }  
        arr[k]=temp;
    return l;
}

void useme(int arr[],int n)
{
    int i=0;
    int m,k;
    while(i<n-1)
    {
        if(arr[i]>arr[i+1])
        {
            k=i+1;
            while(arr[k]>arr[k+1] && k<n-1)
            {
                k++;
            }
            if(k!=i+1)
            {
                m=k-i-1;
                desc(arr,i,k,m);
                i=k;
            }
            else
            {
                while(arr[k]<=arr[k+1] && k<n-1 && arr[k+1]<arr[i])
                {
                    k++;
                }
                m=k-i-1;
                asc(arr,i,k,m);
                i=k;
            }
        }
        else
            i++;
    }
}
int main(int argc,char* argv[])
{
    double start,end;
    int size,rank;
    int n=atoi(argv[1]);
    char names[50][5];
    char users[50000][100];
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int esize=n/size;
    int* subarray=malloc(esize*sizeof(int));
    int i=0;
    int counts[n];
    if(rank==0)
    {
        for(int o=0;o<n;o++)
            scanf("%s",names[o]);
        FILE* file=fopen("usernames.csv","r");
        char str[100];
        while(fgets(str,100,file)!=NULL)
        {
            strcpy(users[i++],str);
        }
        for(int j=0;j<n;j++)
            counts[j]=0;
        start=MPI_Wtime();
    }
    MPI_Bcast(&i,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Bcast(&users[0][0],i*100,MPI_CHAR,0,MPI_COMM_WORLD);
    MPI_Bcast(&names[0][0],n*100,MPI_CHAR,0,MPI_COMM_WORLD);
    MPI_Bcast(counts,n,MPI_INT,0,MPI_COMM_WORLD);
        for(int j=(rank)*i/size;j<(rank+1)*i/size;j++)
        {
            for(int k=0;k<n;k++)
            {
                if(strstr(users[j],names[k])!=NULL)
                {          
                       counts[k]+=1;
                }
            }
        }
        int counts1[n],counts2[n],counts3[n];
        MPI_Reduce(counts,counts1,n,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
        // MPI_Reduce(counts,counts1,n,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
        if(rank==0)
        {
            for(int j=0;j<n;j++)
            {
                counts2[j]=counts1[j];
                counts3[j]=counts1[j];
            }
        }
    MPI_Scatter(counts2,esize,MPI_INT,subarray,esize,MPI_INT,0,MPI_COMM_WORLD);
    useme(subarray,esize-1);
    int* sorted=NULL;
    if(rank==0)
    {
        sorted=malloc(n*sizeof(int));
    }
    MPI_Gather(subarray,esize,MPI_INT,sorted,esize,MPI_INT,0,MPI_COMM_WORLD);
    if(rank==0)
    {
        useme(sorted,n);
        printf("The name of the week:");
        
            for(int j=0;j<n;j++)
            {
                if(sorted[n/2]==counts3[j])
                {
                    printf("%s\n",names[j]);
                }
            }
            end=MPI_Wtime();
            printf("Time: %f",end-start);
    }
    
    MPI_Finalize();
}