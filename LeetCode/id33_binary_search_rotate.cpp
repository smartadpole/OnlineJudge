//////////////////////////////////////////////////////////////////////
///  @file     id33_binary_search_rotate.cpp
///  @brief    binary search -- leetcode 33: Search in Rotated Sorted Array
///  Details.
///
///  @author   smartadpole
///  @version  1.0.0.0
///  @date     2019.01.22
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

// 4 ms（196 测试数据）
int SearchCpp(vector<int>& nums, int target)
{
    int numsSize = nums.size();
    int low = 0, high = numsSize-1, mid = -1;
    while(low <= high)
    {
        mid = low + ((high - low) >> 1);
        if (nums[mid] < target)
        {
            if (nums[mid] < nums[low] && target > nums[numsSize-1]) // right sub array
            {
                high = mid -1;
            }
            else
            {
                low = mid + 1;
            }
        }
        else if (nums[mid] > target)
        {
            if (nums[mid] > nums[numsSize-1] && nums[numsSize-1] >= target) // left sub array
            {
                low = mid + 1;
            }
            else
            {
                high = mid -1;
            }
        }
        else
        {
            return mid;
        }
    }
    return -1;
}

// 0 ms（196 测试数据）
int Search(const int* nums, const int numsSize, const int target)
{
    int low = 0, high = numsSize-1, mid = -1;
    while(low <= high)
    {
        mid = low + ((high - low) >> 1);
        if (nums[mid] < target)
        {
            if (nums[mid] < nums[low] && target > nums[numsSize-1]) // right sub array
            {
                high = mid -1;
            }
            else
            {
                low = mid + 1;
            }
        }
        else if (nums[mid] > target)
        {
            if (nums[mid] > nums[numsSize-1] && nums[numsSize-1] >= target) // left sub array
            {
                low = mid + 1;
            }
            else
            {
                high = mid -1;
            }
        }
        else
        {
            return mid;
        }
    }
    return -1;
}

/*
 test result

iterator number:            10      20      30      50      80      100     150     200     300     400     500     800     1000	2000	3000	4000	5000	10000
c search use time(ms):		0.00	0.02	0.04	0.14	0.36	0.56	1.42	2.81	6.82	12.64	19.82	54.46	86.34	352.99	797.56	1403.84	2242.37	9372.29
cpp search use time(ms):	0.01	0.09	0.16	0.36	0.90	1.81	4.02	8.28	18.54	38.10	69.70	154.47	288.08	831.37	2047.58	4227.48	7722.19	28637.23
c per use time(ms):         0.00	0.00	0.00	0.00	0.00	0.01	0.01	0.01	0.02	0.03	0.04	0.07	0.09	0.18	0.27	0.35	0.45	0.94
cpp per use time(ms):		0.00	0.00	0.01	0.01	0.01	0.02	0.03	0.04	0.06	0.10	0.14	0.19	0.29	0.42	0.68	1.06	1.54	2.86
speed ratio:                2.50	5.41	3.85	2.61	2.50	3.25	2.83	2.94	2.72	3.01	3.52	2.84	3.34	2.36	2.57	3.01	3.44	3.06
*/

void TestTimeC()
{

    const int LENGTH[] = {10, 20, 30, 50, 80, 100, 150, 200, 300, 400, 500, 800, 1000, 2000};//, 3000, 4000, 5000, 10000};

    const int size = sizeof(LENGTH) / sizeof(int);

    printf("iterator number:\t\t");
    for (int l = 0; l != size; ++l)
    {
       printf("%d\t", LENGTH[l]);
    }


    vector<float> timeCList, timeCppList;
    float timeC = 0, timeCpp = 0;

    for (int l = 0; l != size; ++l)
    {
        vector<int> arrTestOrg(LENGTH[l], 0);
        GetSequence(LENGTH[l], &arrTestOrg[0]);

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

            int index = -1, target = -1;
            for(int j = 0; j != arrLength; ++j)
            {
                target = arrTest[j];

                //test
                gettimeofday(&start, nullptr);
                index = Search(&arrTest[0], arrLength, target);
                gettimeofday(&end, nullptr);
                timeC += (1000000*(end.tv_sec-start.tv_sec) + end.tv_usec-start.tv_usec) * 1.0 / 1000;

                gettimeofday(&start, nullptr);
                index = SearchCpp(arrTest, target);
                gettimeofday(&end, nullptr);
                timeCpp += (1000000*(end.tv_sec-start.tv_sec) + end.tv_usec-start.tv_usec) * 1.0 / 1000;

            }
        }

        timeCList.push_back(timeC);
        timeCppList.push_back(timeCpp);
        timeC = 0;
        timeC = 0;
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
        printf("%.2f\t", timeCList[i]/LENGTH[i]);
    }

    printf("\ncpp per use time(ms):\t\t");
    for (int i = 0; i != size; ++i)
    {
        printf("%.2f\t", timeCppList[i]/LENGTH[i]);
    }

    printf("\nspeed ratio:\t\t\t");
    for (int i = 0; i != size; ++i)
    {
        printf("%.2f\t", timeCppList[i]/timeCList[i]);
    }

}

// make solution, print array and search result
void Design()
{
    const int LENGTH = 13;
    int arrTestOrg[LENGTH];

    GetSequence(LENGTH, arrTestOrg);

    const int arrLength = sizeof (arrTestOrg)/sizeof (int);

    printf("(value, index)\n\n");
    for(unsigned int i = 0; i != arrLength; ++i)
    {
        static int arrTest[arrLength];
        Rotate(arrTestOrg, arrLength, i, arrTest);

        printf("array\t");
        for(unsigned int j = 0; j != arrLength; ++j)
        {
            printf("%d,", arrTest[j]);
        }
        printf("\n");

        int index = -1, target = -1;
        for(unsigned int j = 0; j != arrLength; ++j)
        {
            target = arrTest[j];
            printf("(%d,", target);

            index = Search(arrTest, arrLength, target);
            printf("%d)\t", index);
        }
        printf("\n\n");
    }
}

int main(int argc, char *argv[])
{
    Design();
    printf("\n");
    TestTimeC();
    printf("\n");
}


/*
 //--------------error method 1：子序判断不对
int Search(const int* nums, const int numsSize, const int target)
{
    int low = 0, high = numsSize-1, mid = -1;
    while(low <= high)
    {
        mid = low + ((high - low) >> 1);
        if (nums[mid] < target)
        {
            low = mid + 1;
        }
        else if (nums[mid] > target)
        {
            if (nums[mid] < nums[numsSize-1])
            {
                high = mid -1;
            }
            else
            {
                low = mid + 1;
            }
        }
        else
        {
            return mid;
        }
    }
    return -1;
}
//---------error method 2：只处理了大于的两界问题，没处理小于的情况
int Search(const int* nums, const int numsSize, const int target)
{
    int low = 0, high = numsSize-1, mid = -1;
    while(low <= high)
    {
        mid = low + ((high - low) >> 1);
        if (nums[mid] < target)
        {
            low = mid + 1;
        }
        else if (nums[mid] > target)
        {
            if (nums[numsSize-1] > target
                    && nums[mid] > nums[numsSize-1])
            {
                low = mid + 1;
            }
            else if (nums[numsSize-1] == target)
            {
                return numsSize-1;
            }
            else
            {
                high = mid -1;
            }
        }
        else
        {
            return mid;
        }
    }
    return -1;
}
//---------error method 3：小于的情况处理不下去了
// 判断点落在左侧还是右侧很简单
//-----------error method 4:目标落在右侧的情况处理得不好
int Search(const int* nums, const int numsSize, const int target)
{
    int low = 0, high = numsSize-1, mid = -1;
    while(low <= high)
    {
        mid = low + ((high - low) >> 1);
        if (nums[mid] < target)
        {
            if (nums[mid] < nums[low]
                    && nums[mid] < nums[high]) // right sub array
            {
                high = mid -1;
            }
            else
            {
                low = mid + 1;
            }
        }
        else if (nums[mid] > target)
        {
            // right sub array
            if (nums[numsSize-1] > target
                    && nums[mid] > nums[numsSize-1])
            {
                low = mid + 1;
            }
            else if (nums[numsSize-1] == target)
            {
                return numsSize-1;
            }
            else
            {
                high = mid -1;
            }
        }
        else
        {
            return mid;
        }
    }
    return -1;
}
//----------初版
int Search(const int* nums, const int numsSize, const int target)
{
    int low = 0, high = numsSize-1, mid = -1;
    while(low <= high)
    {
        mid = low + ((high - low) >> 1);
        if (nums[mid] < target)
        {
            if (nums[mid] < nums[low]
                    && nums[mid] < nums[high] && target > nums[numsSize-1]) // right sub array
            {
                high = mid -1;
            }
            else
            {
                low = mid + 1;
            }
        }
        else if (nums[mid] > target)
        {
            // right sub array
            if (nums[numsSize-1] > target
                    && nums[mid] > nums[numsSize-1])
            {
                low = mid + 1;
            }
            else if (nums[numsSize-1] == target)
            {
                return numsSize-1;
            }
            else
            {
                high = mid -1;
            }
        }
        else
        {
            return mid;
        }
    }
    return -1;
}
//------------edition 2:使判断条件更清晰——速度没变化
int Search(const int* nums, const int numsSize, const int target)
{
    int low = 0, high = numsSize-1, mid = -1;
    while(low <= high)
    {
        mid = low + ((high - low) >> 1);
        if (nums[mid] < target)
        {
            if (nums[mid] < nums[low] && target > nums[numsSize-1]) // right sub array
            {
                high = mid -1;
            }
            else
            {
                low = mid + 1;
            }
        }
        else if (nums[mid] > target)
        {
            if (nums[mid] > nums[numsSize-1] && nums[numsSize-1] >= target) // left sub array
            {
                low = mid + 1;
            }
            else
            {
                high = mid -1;
            }
        }
        else
        {
            return mid;
        }
    }
    return -1;
}
 * */
