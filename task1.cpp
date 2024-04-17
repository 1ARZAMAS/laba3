#include <iostream> 
#include <cmath> 
#include <iomanip> 
#include <fstream> 
 
using namespace std; 
 
double firstFragm(double x){ 
    double res = - sqrt(-x*x - 4*x)+2;
    if (abs(res) < 0.000001) { 
        res = 0.0; 
    } 
    return res; 
} 
 
double secondFragm(double x){ 
    double res = 0.0; 
    return res; 
} 
 
double thirdFragm(double x){ 
    double res = -x;
    return res; 
} 
 
double fourthFragm(double x){ 
    double res = sqrt(-x*x + 6*x - 5)-1;
    if (abs(res) < 0.000001) { 
        res = 0.0; 
    } 
    return res; 
} 
 
int main () { 
    double xStart = -5.0; 
    double xEnd = 6.0; 
    double dx = 0.5; 
 
    ofstream outfile("test.txt"); 
    if (!outfile.is_open()) { 
        cout << "При открытии файла произошла ошибка" << endl; 
        return 1; 
    } 
    outfile << setw(10)  << "x" << setw(10) << "y" << endl;
    for (double x = xStart; x <= xEnd ; x += dx){ 
        if (abs(x) < 0.000001) { 
        x = 0.0; 
        } 
        
        if (x >= -5.0 && x < -4.0) { 
            outfile << setw(10)  << x << setw(10) << "2" << endl; 
        } 
        if (x >= -4.0 && x < -2.0) { 
            outfile << setw(10)  << x << setw(10) << firstFragm(x) << endl; 
        } 
        if (x >= -2.0 && x <= 0.0){ 
            outfile << setw(10)  << x << setw(10) << secondFragm(x) << endl; 
        } 
        if (x > 0.0 && x < 3.0){ 
            outfile << setw(10)  << x << setw(10) << thirdFragm(x) << endl; 
        } 
        if (x >= 3.0 && x <= 5.0){ 
            outfile << setw(10)  << x << setw(10) << fourthFragm(x) << endl; 
        } 
        if (x > 5.0 && x <= 6.0) { 
            outfile << setw(10)  << x << setw(10) << "-1" << endl; 
        }
    } 
}
