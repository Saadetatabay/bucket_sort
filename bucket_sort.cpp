#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
/**
 * Bucket Sort Algoritmas�
 * @param arr: Siralanacak float vektör
 * @param n:   Oluşturulacak kova sayısı
 */
void bucketSort(vector<float>& arr, int n)
{
    // Hata Kontrolü: Boş dizi veya kova sayisi geçersizliği için eklendi
    if (arr.empty() || n <= 0)
        return;

    // 1. ADIM: Dizideki minimum ve maksimum de�erleri bulma
    float minVal = arr[0];
    float maxVal = arr[0];

    for (size_t i = 1; i < arr.size(); i++)
    {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    // range: Tüm dizi araliğini temsil eder
    float range = maxVal - minVal;

    // range=0 ise tüm elemanlar eşittir, bölme hatasi oluşmaması için
    if (range == 0)
        return;

    // 2. ADIM: n tane boş kova oluşturma
    vector<vector<float>> buckets(n);

    // 3. ADIM: Elemanlari uygun kovalara yerleştirme 
    for (size_t i = 0; i < arr.size(); i++)
    {
        // Normalizasyon Formülü:
        // bucketIndex = (x - minVal) * (n-1) / range
        // Bu formül her elemani [0, n-1] aralığına eşler.
        // minVal her zaman kova[0]'a, maxVal kova[n-1]'e gider.
        int bucketIndex = (int)((arr[i] - minVal) * (n - 1) / range);

        // Güvenlik kontrolü
        if (bucketIndex >= n) bucketIndex = n - 1;  // Üst sınır
        if (bucketIndex < 0)  bucketIndex = 0;      // Alt sınır

        buckets[bucketIndex].push_back(arr[i]);
    }

    // 4. ADIM: Her kovayı sıralama ve ana diziye geri yazma
    int index = 0;  
    for (int i = 0; i < n; i++)
    {
        /**
         * Kova içi sıralama için std::sort kullanılmıştır.
         * std::sort, IntroSort implementasyonu sayesinde kova gibi küçük
         * dizilerde otomatik olarak Insertion Sort'a geçer.
         */
        if (!buckets[i].empty()) {
            sort(buckets[i].begin(), buckets[i].end());
            for (float val : buckets[i])
                arr[index++] = val;
        }
    }
}

int main() {
    // örnek veri seti: Dağınık ondalıklı sayılar
    vector<float> data = {15.5, 1.2, 55.8, 110.0, 10.0, 42.7, 88.3};
    int kovaSayisi = 5;

    cout << "Siralamadan Once: ";
    for (float x : data) cout << x << " ";
    cout << endl;

    bucketSort(data, kovaSayisi);

    cout << "Siralamadan Sonra (Bucket Sort): ";
    for (float x : data) cout << x << " ";
    cout << endl;

    return 0;
}
