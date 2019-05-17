int phi(int n) {
    int result = n;
    for (int i = 2; i * i <= n; i++) {
        if(n % i == 0) {
            while(n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if(n > 1)
        result -= result / n;
    return result;
}

void computeTotient(){
  phi[1] = 1;
  for (int i = 2; i < MAXN; i++) {
    phi[i] += i - 1;
    for (int j = i + i; j < MAXN; j+=i) {
      phi[j] -= phi[i];
    }
  }
}