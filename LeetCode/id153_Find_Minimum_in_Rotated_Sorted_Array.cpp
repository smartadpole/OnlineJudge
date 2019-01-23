//////////////////////////////////////////////////////////////////////
///  @file     id153_Find_Minimum_in_Rotated_Sorted_Array.cpp
///  @brief    binary search -- leetcode 153: Find Minimum in Rotated Sorted Array
///  Details.
///
///  @author   smartadpole
///  @version  1.0.0.0
///  @date     2019.01.23
///
///  修订说明: 初始版本
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <iostream>
#include <vector>
#include <sys/time.h> //test
using namespace std;
#define DEBUG_SMART

void Rotate(const int* arrInput, const unsigned int length, const unsigned int pivot, int* arrOutput)
{
    for(unsigned int i = 0; i != length; ++i)
    {
        arrOutput[i] = arrInput[(i + pivot) % length];
    }
}

void GetSequence(const int length, int* arrOutput)
{
    for (int i = 0; i != length; ++i)
    {
        *arrOutput++ = i;
    }
}

int findMinCpp(vector<int>& nums)
{
    int numsSize = nums.size();
    if (1 == numsSize
            || nums[0] < nums[numsSize - 1])
    {
        return nums[0];
    }

    int low = 0, high = numsSize-1;

    while(low <= high)
    {
        int mid = low + ((high - low)>>1);

        if (nums[low] > nums[high])
        {
            if (nums[mid] < nums[low])  // right sub array
            {
                high = mid;
            }
            else    // left sub array
            {
                low = mid + 1;
            }
        }
        else    // ascending order
        {
            return nums[low];
        }
    }

    return nums[high];
}

int findMin(const int* nums, const int numsSize)
{
    if (1 == numsSize
            || nums[0] < nums[numsSize - 1])
    {
        return nums[0];
    }

    int low = 0, high = numsSize-1;

    while(low <= high)
    {
        int mid = low + ((high - low)>>1);

        if (nums[low] > nums[high])
        {
            if (nums[mid] < nums[low])  // right sub array
            {
                high = mid;
            }
            else    // left sub array
            {
                low = mid + 1;
            }
        }
        else    // ascending order
        {
            return nums[low];
        }
    }

    return nums[high];
}


/*
 test result
element number:             10	20	30	50	80	100	150	200	300	400	500	800	1000	2000	3000	4000	5000	10000
iterator number:            20	40	60	100	160	200	300	400	600	800	1000	1600	2000	4000	6000	8000	10000	20000
c search use time(ms):		0.00	0.00	0.00	0.00	0.00	0.01	0.01	0.00	0.01	0.01	0.02	0.03	0.04	0.09	0.19	0.26	0.32	0.79
cpp search use time(ms):	0.00	0.00	0.00	0.00	0.00	0.00	0.01	0.00	0.01	0.01	0.02	0.04	0.05	0.08	0.13	0.20	0.29	0.58
c per use time(ms):         0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00
cpp per use time(ms):		0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.00
speed ratio:                1.00	-nan	1.00	inf	1.00	0.50	0.64	0.75	1.08	1.08	1.22	1.62	1.22	0.85	0.70	0.79	0.89	0.74

conclusion:
核心代码一样，速度却不同，C++ 更快速；
*/

void TestTimeC(void (*generate)(int,int*))
{

    const int LENGTH[] = {10, 20, 30, 50, 80, 100, 150, 200, 300, 400, 500, 800, 1000, 2000, 3000, 4000, 5000, 10000};

    const int size = sizeof(LENGTH) / sizeof(int);

    printf("element number:\t\t");
    for (int l = 0; l != size; ++l)
    {
       printf("%d\t", LENGTH[l]);
    }
    printf("\n");
    printf("iterator number:\t\t");
    for (int l = 0; l != size; ++l)
    {
       printf("%d\t", LENGTH[l]+LENGTH[l]);
    }


    vector<float> timeCList, timeCppList;
    float timeC = 0, timeCpp = 0;

    for (int l = 0; l != size; ++l)
    {
        vector<int> arrTestOrg(LENGTH[l], 0);
        generate(LENGTH[l], &arrTestOrg[0]);

        //test
        struct timeval start, end;
        gettimeofday(&start, nullptr);
        const int arrLength = arrTestOrg.size();
        gettimeofday(&end, nullptr);
//        time += (1000000*(end.tv_sec-start.tv_sec) + end.tv_usec-start.tv_usec) * 1.0 / 1000;

        for(int i = 0; i != arrLength; ++i)
        {
            vector<int> arrTest(arrLength, 0);
            Rotate(&arrTestOrg[0], arrLength, i, &arrTest[0]);

            int value = -1;

            //test
            gettimeofday(&start, nullptr);
            value = findMin(&arrTest[0], arrLength);
            gettimeofday(&end, nullptr);
            timeC += (1000000*(end.tv_sec-start.tv_sec) + end.tv_usec-start.tv_usec) * 1.0 / 1000;

            //test
            gettimeofday(&start, nullptr);
            value = findMinCpp(arrTest);
            gettimeofday(&end, nullptr);
            timeCpp += (1000000*(end.tv_sec-start.tv_sec) + end.tv_usec-start.tv_usec) * 1.0 / 1000;
        }

        timeCList.push_back(timeC);
        timeCppList.push_back(timeCpp);
        timeC = 0;
        timeCpp = 0;
    }

    printf("\nc search use time(ms):\t\t");
    for (auto& t : timeCList)
    {
        printf("%.2f\t", t);
    }
    printf("\ncpp search use time(ms):\t");
    for (auto& t : timeCppList)
    {
        printf("%.2f\t", t);
    }

    printf("\nc per use time(ms):\t\t");
    for (int i = 0; i != size; ++i)
    {
        printf("%.2f\t", timeCList[i]/(LENGTH[i]<<1));
    }

    printf("\ncpp per use time(ms):\t\t");
    for (int i = 0; i != size; ++i)
    {
        printf("%.2f\t", timeCppList[i]/(LENGTH[i]<<1));
    }

    printf("\nspeed ratio:\t\t\t");
    for (int i = 0; i != size; ++i)
    {
        printf("%.2f\t", timeCppList[i]/timeCList[i]);
    }

}

// make solution, print array and search result
void Design(void (*generate)(int,int*), const int length)
{
    int arrTestOrg[length];

    generate(length, arrTestOrg);

    printf("(value, index)\n\n");
    for(unsigned int i = 0; i != length; ++i)
    {
        int arrTest[length];
        Rotate(arrTestOrg, length, i, arrTest);

        printf("array\t");
        for(unsigned int j = 0; j != length; ++j)
        {
            printf("%d,", arrTest[j]);
        }

        int value = findMin(arrTest, length);
        printf("\tmin:%d", value);
        printf("\n\n");
    }
}

int main(int argc, char *argv[])
{
//    printf("test sequence\n");
//    Design(GetSequence, 10);
//    Design(GetSequence, 4);
//    printf("test duplication\n");
    TestTimeC(GetSequence);
    printf("\n");
}
