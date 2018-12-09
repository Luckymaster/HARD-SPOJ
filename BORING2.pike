array(int) pre = allocate(1000002);

void init()
{  
   pre[1]=1;
   int x=1,l=1;
  for(int i=2;i<=1000001;i++)
   {
     l=l*i;
     pre[i]=l;
     if(x==1500) {l=1;x=0;}x+=1;
     }
}

int modInverse(int a, int n) {
int i = n, v = 0, d = 1;
 while (a>0){
  int t = i/a, x = a;
  a = i % x;
  i = x;
  x = d;
  d = v - t*x;
  v = x;
 }
 v %= n;
 if (v<0) v = (v+n)%n;
 return v;
}
int factMOD1(int n, int MOD)
{ 
   
    int res=1,pes;
    for(int i=1;i<MOD-n;i=i+1500)
    {
      res=res*pre[i]%MOD;
    }
    res = modInverse(res,MOD);
    if(n%2==0) res = -1*res+MOD;
    return res;
}
int factMOD(int n, int MOD)
{ 
   
    int res=1,pes;
    for(int i=1;i<MOD-n;i=i+1500)
    {
      res=res*pre[i]%MOD;
    }
    int x,y;
    res=res*pre[MOD-n-1]%MOD;
    res = modInverse(res,MOD);
    if(n%2==0) res = -1*res+MOD;
    return res;
}

int main()
{
  int n,p,ans,d,v=0,tc;
  init();
  string line;
  line = Stdio.stdin->gets();
  sscanf(line, "%d",tc);
  for(int cs=1;cs<=tc;cs++)
  {
       line = Stdio.stdin->gets();
       sscanf(line, "%d%d",  n,p);
       if(n>=p)write(sprintf("%d\n",v));
       else if((p-n)%1500==2)
       {
          ans = factMOD1(n,p);
          write(sprintf("%d\n",ans));
       }
       else if(n==(p-1)) write(sprintf("%d\n",n));
       else{
       ans = factMOD(n,p);
       write(sprintf("%d\n",ans));}
  }
}