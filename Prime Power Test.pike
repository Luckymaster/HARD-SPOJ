int i = 0;
int mida = 0,ab=0;
int chk = 0,b = 0;


int pow_i(int m, int i){
	int x=1,y=m;
	while(i){
		if(i&1) x = x*y;
		y =  y*y;
		i>>=1;
	}
	return x;
}

int pow_mod(int m, int i,int mod){
	int x=1,y=m%mod;
	while(i){
		if(i&1) x = x*y%mod;
		y =  y*y%mod;
		i>>=1;
	}
	return x;
}
int is_prime(int n){
	array(int) prime ;
	prime = ({2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 47, 53, 59, 61, 67, 71, 79, 83, 89, 97, 101, 103, 107, 109, 113});
    int idx =  search( prime, n);
    if( n < 113 && n == prime[idx] ){
        return 1;
    }
    if(n < 2047) prime = ({2, 3});
    if(n < 1373653)prime = ({2, 3});
    if(n < 9080191)prime = ({31, 73});
    if(n < 25326001)prime = ({2, 3, 5});
    if(n < 3215031751)prime = ({2, 3, 5, 7});
    if(n < 4759123141)prime = ({2, 7, 61});
    if(n < 1122004669633)prime = ({2, 13, 23, 1662803});
    if(n < 2152302898747)prime = ({2, 3, 5, 7, 11});
    if(n < 3474749660383)prime = ({2, 3, 5, 7, 11, 13});
    if(n < 341550071728321)prime = ({2, 3, 5, 7, 11, 13, 17});
    if(n < 3825123056546413051)prime = ({2, 3, 5, 7, 11, 13, 17, 19, 23});
    if(n < 18446744073709551616)prime = ({2, 3, 5, 7, 11, 13, 17, 19, 23, 29});
    if(n < 318665857834031151167461)prime = ({2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31});
    if(n < 3317044064679887385961981)prime = ({2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37});
    else prime = ({2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 47, 53, 59, 61, 67, 71});
    int d = n - 1;
    int s = 0;
    while(d % 2 == 0){
    	d >>= 1;
    	s += 1;
    }
    for (int repeat=0 ; repeat < sizeof(prime); repeat++){
        int a = prime[repeat];
        if(!mr_pass(a, s, d, n)){
            return 0;
        }
    }
    return 1;
}

bool mr_pass(int a, int s, int d, int n){
    int a_to_power = pow_mod(a, d, n);
    if(a_to_power == 1)
        return true;
    for(int i = 0; i< s - 1; i++){
        if(a_to_power == n - 1)
            return true;
        a_to_power = (a_to_power * a_to_power) % n;
    }
    return a_to_power == n - 1;
}

int log2(int n){
	int aux = 0;
	int t = 1;
	while(t<=n){
		t<<=1;
		aux++;
	}
	return aux;
}
void is_power(int n){
    int lgn = 1 + log2(n);
    //write(sprintf("%d\n",lgn));
    for(b=lgn;b>=1;b--){
    	int lowa = 1;
        int higha = 1 << (lgn / b + 1);
        while(lowa < higha - 1){
        	mida = (lowa + higha) >> 1;
            ab = pow(mida,b);
            if(ab > n) higha = mida;else
            if(ab < n) lowa  = mida;else
            {chk = 1; return;}
        }
    }
}

int main() {
	string line;
	int tc;
	line = Stdio.stdin->gets();
	sscanf(line, "%d",tc);
	for(int i=1;i<=tc;i++){
		line = Stdio.stdin->gets();
		int n;
		sscanf(line, "%d",n);
		is_power(n);
		if(chk == 1 && is_prime(mida))
		write(sprintf("%d %d\n",mida,b));
		else write("Invalid order\n");
	}
}
