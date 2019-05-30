#include<stdio.h>

void desc(int arr[],int i,int k,int m)
{
        int stack[25],stack1[25];
        int j=0,o=0,y,u;
        stack[j++]=m;
        int t=m;
        for(int p=0;;p++)
        {
            if(m==-1)
                break;
            stack[j++]=m-1;
            m=m-1;
        }   
        for(int p=k;p>=i+1;p--)
        {
            stack1[o++]=arr[p];
        }

        for(int p=0;p<o;p++)
        {
            printf("%i ",stack1[p]);
        }

        y=k;
        u=i;
        int l;
        while(j>0 && o>0)
        {
            m=stack[--j];
            if(m==-1)
            {
                l=0;
                continue;
            }
            int temp=stack1[--o];
            int low,high;
            if(temp<arr[0])
            {
                low=-1;
            }
            else
            {
                high=u-l;
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
            k=y-l-m;
            i=u-l;
            while(i>low)
            {
                arr[k]=arr[i];
                i--;
                k--;
                l++;
            }  
            arr[k]=temp;
    }
}

void asc(int arr[],int i,int k,int m)
{
        int stack[25],stack1[25];
        int j=0,o=0,y=0,u=0;
        stack[j++]=m;
        int t=m;
        for(int p=0;;p++)
        {
            if(m==-1)
                break;
            stack[j++]=m-1;
            m=m-1;
        }   
        for(int p=i+1;p<=k;p++)
        {
            stack1[o++]=arr[p];
        }
        for(int p=0;p<o;p++)
        {
            printf("%i ",stack1[p]);
        }
        y=k;
        u=i;
        int l;
        while(j>0 && o>0)
        {
            m=stack[--j];
            if(m==-1)
            {
                l=0;
                continue;
            }
            int temp=stack1[--o];
            int low,high;
            if(temp<arr[0])
            {
                low=-1;
            }
            else
            {
                high=u-l;
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
            k=y-l-m;
            i=u-l;
            while(i>low)
            {
                arr[k]=arr[i];
                i--;
                k--;
                l++;
            }  
            arr[k]=temp;
    }
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
    printf("Enter no of elements:");
    int n;
    scanf("%i",&n);
    int arr[n];
    for(int i=0;i<n;i++)
        scanf("%i",&arr[i]);
    useme(arr,n);
    for(int i=0;i<n;i++)
        printf(" %i ",arr[i]);
    printf("\n");
}