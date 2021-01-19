MOD = 10**9 + 7

T = int(input().rstrip())

for _ in range(T):
    R,C = map(int,input().rstrip().split())

    ans = 18 * (6**(R-1)) * (6**(C-1)) * (2**((R-1)*(C-1)))
    print(ans%MOD)


