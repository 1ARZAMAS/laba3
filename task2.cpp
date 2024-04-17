#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

using namespace std;

int getRandomNumber(int min, int max) {  // Функция для генерации случайного числа в заданном диапазоне
    return rand() % (max - min + 1) + min;
}

// Решето Эратосфена
void Eratosfen(vector<int>& Prost500) {

    for (int i = 2; i < 500; i++) { //закидываем все числа от 2 до 500
        Prost500.push_back(i);
    }

    for (int i = 0; i <= sqrt(Prost500.size()); i++) { //смотрим от начального числа до корня из него
        int j = i + 1;
        while (j < Prost500.size()) {
            if (Prost500[j] % Prost500[i] == 0) {
                for (int k = j; k < Prost500.size() - 1; k++) {  //если чисто непростое
                    Prost500[k] = Prost500[k + 1];               //затираем сдвигом
                }
                Prost500.pop_back();                             //и удаляем последнюю пустую позицию
            }
            else {
                j++;                                        //если простое, идем дальше
            }
        }
    }
}



// Функция для возведения в степень по модулю
int modPow(int a, int q, int n) {
    int result = 1;
    while (q > 0) {
        if (q % 2 == 1) {
            result = (result * a) % n;
        }
        a = (a * a) % n;
        q /= 2;
    }
    return result;
}

bool TestMiller(int n, int s, int q, int t) {
    // Проверяем базовые случаи
    if (n == 2) return true;
    if (n < 2 || n % 2 == 0) return false;


    for (int i = 0; i < t; i++) {
        // Генерируем случайное число a в диапазоне от 2 до n-2
        int a = getRandomNumber(2, n - 2);

        // Проверяем первое условие
        if (modPow(a, q, n) == 1) {
            return true;
        }

        // Проверяем второе условие
        for (int i = 0; i < s; i++) {
            if (modPow(a, pow(2, i) * q, n) == n - 1) {
                return true;
            }
        }

        return false;
    }
}

// Функция для нахождения НОД
int NOD(int a, int b) {
    if (b == 0) return a;
    return NOD(b, a % b);
}

// Функция для проверки условия
bool TestPoklingtona(int n, int q, int t) {
    if (n == 2) return true;

    int n_minus_1 = n - 1;
    for (int i = 0; i < t; i++) {

        int a = getRandomNumber(1, n - 1);

        // Проверяем a^(n-1) mod n
        int res = modPow(a, n_minus_1, n);
        if (res != 1) return false;

        // Проверяем (a^((n-1)/q)) mod n
        int q_part = n_minus_1 / q;
        int result = modPow(a, q_part, n);
        result = (result) % n;
        if (result < 0) result += n;

        return NOD(result, n) == 1;
    }
}

int St(int a, int b) {
    int result = 1;
    for (int i = 0; i < b; i++) {
        result *= a;
    }
    return result;
}

bool GOST(int t, int q1) {
    int p = 0;

    while (true) {

        int N1 = ceil(St(2, t - 1) / q1);
        int N2 = ceil(St(2, t - 1) / (q1));

        double N = N1 + N2;
        if (static_cast<int>(round(N)) % 2 != 0) {
            N++;
        }

        for (int u = 0; St(2, t) >= (N + u) * q1 + 1; u += 2) {
            p = (N + u) * q1 + 1;
            if ((St(2, p - 1) % p == 1) && (St(2, N + u) % p != 1)) {
                return true;
            }
        }
    }
    return false;
}

// Функция для проверки числа на простоту вероятностным тестом с заданной вероятностью ошибки
bool probabilisticTest(int n, double errorProbability) {
    if (n <= 1 || n == 4) {
        return false;
    }
    if (n <= 3) {
        return true;
    }

    int k = static_cast<int>(log2(n)); // Определение количества итераций для заданной вероятности ошибки
    for (int i = 0; i < k; i++) {
        int a = 2 + rand() % (n - 3); // Генерация случайного числа a в диапазоне от 2 до n-2
        int x = modPow(a, n - 1, n);
        if (x != 1) {
            return false;
        }
    }
    return true;
}

bool TestVeroyatnost(bool Result, int n, int k) {
    if (Result) {
        bool probabilisticTestResult = probabilisticTest(n, 0.1);
        if (probabilisticTestResult && k < 5) {
            return false;
        }
    }
    return true;
}

void InPut(int n, bool testResult, int k) {
    if (testResult && k < 5) {
        cout << n << " \t" << "+" << "  \t" << k << endl;
    }
    else {
        cout << n << " \t" << "-" << "  \t" << k << endl;
    }
}


int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(0));

    vector<int> Prost500;
    Eratosfen(Prost500);

    int t1 = 10;
    int k1;
    int k = 0;
    int t = 4;
    int q1 = 3;
    bool millerResult;
    bool poklingtonResult;

    cout << "Число\tВероятностный тест\tk" << endl;

    
    for (int i = 0; i < 10; i++) {
        int n = getRandomNumber(2, 500 - 2);
        int q = n - 1;
        int s = 0;

        while (q % 2 == 0 && q != 0) {
            q /= 2;
            s++;
        }

        millerResult = TestMiller(n, s, q, t1);
       // TestVeroyatnost(millerResult, n, k); // Обновляем счетчик отвергнутых чисел

        poklingtonResult = TestPoklingtona(n, q, t1);
        //TestVeroyatnost(poklingtonResult, k, n); // Обновляем счетчик отвергнутых чисел

        

        if (!millerResult || !poklingtonResult) {
            k++;
            i--;
            continue;
        }
        TestVeroyatnost(millerResult, n, k); // Обновляем счетчик отвергнутых чисел
       
        bool gostResult = GOST(t, q1);
        
        InPut(n, TestVeroyatnost, k);
        
        if (millerResult && poklingtonResult) {
            k = 0;
        }


    }
    return 0;
}