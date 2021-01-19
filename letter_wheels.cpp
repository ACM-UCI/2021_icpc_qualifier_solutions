#include <bits/stdc++.h>

int wheels[3][5000];
int N = 0;

std::vector<bool> compareWheels(int a, int b) {
    std::vector<bool> to_return(N);
    for (int offset = 0; offset < N; ++offset) {
        bool valid = true;
        for (int i = 0; i < N; ++i) {
            if (wheels[a][i] & wheels[b][(offset+i)%N]) {
                valid = false;
                break;
            }
        }
        if (valid) {
            to_return[offset] = true;
        }
    }
    return to_return;
}

int main() {

    std::string s1,s2,s3; std::cin >> s1 >> s2 >> s3;
    N = s1.length();

    for (int i = 0; i < N; ++i)
        wheels[0][i] = (1 << (s1[i]-'A'));

    for (int i = 0; i < N; ++i)
        wheels[1][i] = (1 << (s2[i]-'A'));

    for (int i = 0; i < N; ++i)
        wheels[2][i] = (1 << (s3[i]-'A'));


    int answer = -1;

    std::vector<bool> w01 = compareWheels(0,1);
    std::vector<bool> w12 = compareWheels(1,2);
    std::vector<bool> w02 = compareWheels(0,2);

    for (int i = 0; i < N; ++i) {
        if (w01[i]) {
            for (int j = 0; j < N; ++j) {
                if (w12[j] && w02[(i+j)%N]) {
                    int k = (i+j)%N;
                    int a = std::min(i, N-i) + std::min(j, N-j);
                    int b = std::min(i, N-i) + std::min(k, N-k);
                    int c = std::min(j, N-j) + std::min(k, N-k);
                    
                    int best = std::min({a,b,c});
                    answer = (answer < 0 ? best : std::min(answer, best));
                }
            }
        }
    }
    

    std::cout << answer << std::endl;

    return 0;
}

