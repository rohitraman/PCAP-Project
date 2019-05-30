#include<stdio.h>
#include <time.h>
#include <string.h>


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
        //printf("k==%i",k);
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

int main()
{
    int n;
    char users[50000][100];
    char arr[6][50];
    int o=0;
    int i=0;
    for(int j=0;j<6;j++)
    {
        scanf("%s",arr[j]);
    }
    
    FILE* file=fopen("usernames.csv","r");
    char str[100];
    int counts[6],counts1[6];
    for(int p=0;p<6;p++)
        counts[p]=0;
    clock_t start=clock();

    while(fgets(str,100,file)!=NULL)
    {
        strcpy(users[i++],str);
    }
    printf("%i   ",i);
    for(int j=0;j<i;j++)
        {
            for(int k=0;k<6;k++)
            {
                if(strstr(users[j],arr[k])!=NULL)
                {          
                       counts[k]+=1;
                }
            }
        }
    for(int k=0;k<6;k++)
    {
        counts1[k]=counts[k];
    }
    useme(counts,6);
    
    for(int k=0;k<6;k++)
    {
        if(counts[3]==counts1[k])
        {
            printf("The name of the week is:%s",arr[k]);
        }
    }
    clock_t end=clock();
    printf("\nTime taken:%f seconds",(float)(end-start)/CLOCKS_PER_SEC);
}