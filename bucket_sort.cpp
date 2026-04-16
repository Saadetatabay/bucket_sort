#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void bucketSort(vector<float>& arr, int n)
{
    if (arr.empty())
        return ;

    // n tane boş kova oluşturuyoruz
    vector<vector<float>> buckets(n);
    float minVal = arr[0];
    float maxVal = arr[0];
    
    for (int i = 0; i< arr.size();i++)
    {
        if (arr[i] < minVal)
            minVal = arr[i];
        if (arr[i] > maxVal)
            maxVal = arr[i];
    }

    float range = maxVal - minVal;

    // eğer tüm değerler birbirine eşitse sıralıdır diyip return yapıyoruz
    if (range == 0)
        return ;

    int bucketIndex;
    for (int i = 0; i< arr.size();i++)
    {
        bucketIndex = (int)((arr[i] - minVal) * (n - 1) / (maxVal - minVal));
        buckets[bucketIndex].push_back(arr[i]);
    }
    
    int index = 0;
    for (int i = 0; i< n; i++)
    {
        // her kovayı kendi içince sıralıyoruz
        sort(buckets[i].begin(), buckets[i].end());
        for (int j = 0; j < buckets[i].size(); j++)
        {
            arr[index++] = buckets[i][j];
        }
    }

}