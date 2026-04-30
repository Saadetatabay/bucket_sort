#include <iostream>
#include <algorithm> // std::sort (IntroSort) kullanımı için
#include <vector>

using namespace std;

/**
 * Bucket Sort Algoritması
 * @param arr: Sıralanacak float vektörü
 * @param n: Oluşturulacak kova sayısı
 * Gerekçe: Veriler aralığa homojen dağıldığında O(n+k) performans sağlar.
 */
void bucketSort(vector<float>& arr, int n)
{
    // Hata Kontrolü: Boş dizi veya kova sayısı geçersizliği
    if (arr.empty() || n <= 0)
        return;

    // 1. ADIM: Dizideki minimum ve maksimum değerleri bulma
    float minVal = arr[0];
    float maxVal = arr[0];
    
    for (size_t i = 1; i < arr.size(); i++)
    {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    float range = maxVal - minVal;

    // Eğer tüm değerler aynıysa dizi zaten sıralıdır
    if (range == 0)
        return;

    // 2. ADIM: n tane boş kova oluşturma
    vector<vector<float>> buckets(n);

    // 3. ADIM: Elemanları uygun kovalara yerleştirme (Normalizasyon)
    for (size_t i = 0; i < arr.size(); i++)
    {
        // Hassas hesaplama: maxVal değerinin indis sınırını (n) aşmasını engelliyoruz
        int bucketIndex = (int)((arr[i] - minVal) * (n - 1) / range);
        
        // Güvenlik kontrolü (Floating point hatalarına karşı koruma)
        if (bucketIndex >= n) bucketIndex = n - 1;
        if (bucketIndex < 0) bucketIndex = 0;
        
        buckets[bucketIndex].push_back(arr[i]);
    }
    
    // 4. ADIM: Her kovayı sıralama ve ana diziye geri yazma
    int index = 0;
    for (int i = 0; i < n; i++)
    {
        /** 
         * Kova içi sıralamada std::sort (IntroSort) kullanılmıştır.
         * IntroSort, verinin durumuna göre en verimli sıralamayı garanti eder.
         */
        if (!buckets[i].empty()) {
            sort(buckets[i].begin(), buckets[i].end());
            for (float val : buckets[i])
            {
                arr[index++] = val;
            }
        }
    }
}

int main() {
    // Örnek veri seti: Dağınık ondalıklı sayılar
    vector<float> data = {15.5, 1.2, 55.8, 110.0, 10.0, 42.7, 88.3};
    int kovaSayisi = 5;

    cout << "Siralamadan Once: ";
    for (float x : data) cout << x << " ";
    cout << endl;

    // Bucket Sort fonksiyonunun çağrılması
    bucketSort(data, kovaSayisi);

    cout << "Siralamadan Sonra (Bucket Sort): ";
    for (float x : data) cout << x << " ";
    cout << endl;

    return 0;
}