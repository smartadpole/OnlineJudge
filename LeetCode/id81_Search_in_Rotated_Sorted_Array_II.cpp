//////////////////////////////////////////////////////////////////////
///  @file     id81_binary_search_rotate2.cpp
///  @brief    binary search -- leetcode 81: Search in Rotated Sorted Array II
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

void GetDuplication(const int length, int* arrOutput)
{
    for (int i = 0; i != length; ++i)
    {
        *arrOutput++ = ((i>>8)<<8) + 1;
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

        if (target == nums[mid])
        {
            return true;
        }
        else if (nums[mid] == nums[low])
        {
            ++low;
            continue;
        }

        if (nums[mid] < target)
        {
            if (nums[mid] < nums[low]   // right sub array
                    && target > nums[high])
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
            if (nums[mid] > nums[high]   // left sub array
                    && nums[high] >= target)
            {
                low = mid + 1;
            }
            else
            {
                high = mid -1;
            }
        }
    }
    return false;
}

// 0 ms（196 测试数据）
int Search(const int* nums, const int numsSize, const int target)
{
    int low = 0, high = numsSize-1, mid = -1;
    while(low <= high)
    {
        mid = low + ((high - low) >> 1);

        if (target == nums[mid])
        {
            return true;
        }
        else if (nums[mid] == nums[low])
        {
            ++low;
            continue;
        }
//        else if (nums[mid] == nums[high])  // work as <else if (nums[mid] == nums[low])>
//        {
//            --high;
//            continue;
//        }

        if (nums[mid] < target)
        {
            if (nums[mid] < nums[low]   // right sub array
                    && target > nums[high])
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
            if (nums[mid] > nums[high]   // left sub array
                    && nums[high] >= target)
            {
                low = mid + 1;
            }
            else
            {
                high = mid -1;
            }
        }
    }
    return false;
}

/*
 test result

GetDuplication - 16 倍数，真假各半:
element number:             10	20	30	50	80	100	150	200	300	400	500	800	1000	2000	3000	4000	5000	10000
iterator number:            20	40	60	100	160	200	300	400	600	800	1000	1600	2000	4000	6000	8000	10000	20000
c search use time(ms):		0.01	0.02	0.05	0.12	0.36	0.51	1.23	2.35	5.37	10.76	14.44	40.30	59.81	262.01	581.37	1039.111593.09	6795.52
cpp search use time(ms):	0.00	0.02	0.06	0.12	0.37	0.54	1.35	2.46	6.07	9.42	14.63	40.22	60.58	264.02	588.14	1052.291621.88	6916.27
c per use time(ms):         0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.01	0.01	0.01	0.01	0.03	0.03	0.07	0.10	0.13	0.16	0.34
cpp per use time(ms):		0.00	0.00	0.00	0.00	0.00	0.00	0.00	0.01	0.01	0.01	0.01	0.03	0.03	0.07	0.10	0.13	0.16	0.35
speed ratio:                0.50	1.60	1.22	0.98	1.04	1.05	1.10	1.05	1.13	0.87	1.01	1.00	1.01	1.01	1.01	1.01	1.02	1.02

GetDuplication - 256 倍数，真假各半:
element number:             10	20	30	50	80	100	150	200	300	400	500	800	1000	2000	3000	4000	5000	10000
iterator number:            20	40	60	100	160	200	300	400	600	800	1000	1600	2000	4000	6000	8000	10000	20000
c search use time(ms):		0.01	0.02	0.06	0.12	0.72	1.05	4.30	9.53	13.57	27.27	50.54	79.93	186.64	659.71	1297.74	2133.653134.91	12305.63
cpp search use time(ms):	0.01	0.03	0.06	0.14	0.79	1.09	4.27	9.42	13.74	27.29	51.23	79.40	184.52	663.96	1304.73	2149.063155.78	12374.82
c per use time(ms):         0.00	0.00	0.00	0.00	0.00	0.01	0.01	0.02	0.02	0.03	0.05	0.05	0.09	0.16	0.22	0.27	0.31	0.62
cpp per use time(ms):		0.00	0.00	0.00	0.00	0.00	0.01	0.01	0.02	0.02	0.03	0.05	0.05	0.09	0.17	0.22	0.27	0.32	0.62
speed ratio:                1.00	1.52	1.05	1.14	1.10	1.04	0.99	0.99	1.01	1.00	1.01	0.99	0.99	1.01	1.01	1.01	1.01	1.01

conclusion:
c,c++ 速度无差别；
target 不在搜索库中时，耗时更长；
随着左侧边界重复元素逐渐增多，搜索也逐渐趋近于线性；
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

            int index = -1, target = -1;
            const int searchLength = arrLength << 1;
            for(int j = 0; j != searchLength; ++j)
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
        printf("\n");

        int index = -1, target = -1;
        for(unsigned int j = 0; j != length+3; ++j)
        {
            target = j;
            printf("(%d,", target);

            index = Search(arrTest, length, target);
            printf("%d)\t", index);
        }
        printf("\n\n");
    }
}

int main(int argc, char *argv[])
{
//    printf("test sequence\n");
//    Design(GetSequence, 10);
//    Design(GetSequence, 17);
//    printf("test duplication\n");
//    Design(GetDuplication, 17);
//    printf("\n");
    TestTimeC(GetDuplication);
    printf("\n");
}


/*
 //--------------error method 1：没改逻辑，[1,3,1,1,1],3,没有考虑到大批元素重复，且左右两分的情况
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
            return true;
        }
    }
    return false;
}
//---------思路卡壳，想不到如何处理中间只有很短的子序列单增，而其左右两侧都是重复的数；主要是思路局限在二分了；
//---------突破：题目打破了两侧数组单调递增的特性
// 1. 若重复元素出现在两个子序列内部也没什么，
// 2. 就怕同时出现在左序列起、右序列止；因为此时判断 mid 落在左序列还是右序列出现困难；例如 [1,3,1,1,1]；
// 解决：将情形 2 转化为 情形 1 即可——只处理单侧；
// 当前值与边界值相等时，该边界处的哨兵向另一侧单步移动，直至当前子序列单增，此时重复元素只出现在单侧，即情形 1；
//---------初版
int Search(const int* nums, const int numsSize, const int target)
{
    int low = 0, high = numsSize-1, mid = -1;
    while(low <= high)
    {
        mid = low + ((high - low) >> 1);

        if (target == nums[mid])
        {
            return true;
        }
        else if (nums[mid] == nums[low])
        {
            ++low;
            continue;
        }

        if (nums[mid] < target)
        {
            if (nums[mid] < nums[low]   // right sub array
                    && target > nums[high])
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
            if (nums[mid] > nums[high]   // left sub array
                    && nums[high] >= target)
            {
                low = mid + 1;
            }
            else
            {
                high = mid -1;
            }
        }
    }
    return false;
}
 * */

