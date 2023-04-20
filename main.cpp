#include <iostream>
#include <vector>
#include <complex>

using namespace std;
using cd = complex<double>;

#define PI acos(-1)

void fft(vector<cd> & a, bool inverse) {
    int n = a.size();
    if (n == 1){
        return;
    }

    vector<cd> evens(n / 2), odds(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        evens[i] = a[2*i];
        odds[i] = a[2*i+1];
    }
    fft(evens, inverse);
    fft(odds, inverse);

    double ang = 2 * PI / n * (inverse ? -1 : 1);
    cd w(1), unity(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = evens[i] + w * odds[i];
        a[i + n/2] = evens[i] - w * odds[i];
        if (inverse) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= unity;
    }
}
vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) {
        n <<= 1;
    }
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++){
        fa[i] *= fb[i];
    }
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++){
        result[i] = round(fa[i].real());
    }
    return result;
}

int main(){
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a, b;
    for(int i = 0; i < n+1; i++){
        int t;
        std::cin >> t;
        a.push_back(t);
    }
    for(int i = 0; i < m+1; i++){
        int t;
        std::cin >> t;
        b.push_back(t);
    }
    std::vector<int> res = multiply(a, b);
    bool start = true;
    int ct = 0;
    for(int i : res){
        if(!start && i != 0){
            start = true;
        }
        if(!start){
            continue;
        }
        std::cout << i << " ";
        ct++;
        if(ct == m+n+1){
            break;
        }
    }
    std::cout << "\n";
}
