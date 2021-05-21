#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int getRand(int l, int r)
{
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
  
#define int long long 
#define pb push_back
#define S second
#define F first
#define f(i,n) for(int i=0;i<n;i++)
#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define vi vector<int>
#define pii pair<int,int>
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update> 
#define precise(x) fixed << setprecision(x) 

const int MOD = 1e9+7;

int mod_pow(int a,int b,int M = MOD)
{
    int res = 1;
    
    while(b)
    {
        if(b&1) res=(res*a)%M;
        a=(a*a)%M;
        b>>=1;
    }
    
    return res;
}


void solve()
{
    int n,m;
    cin >> n >> m;
    
    int a[n];
    f(i,n) cin >> a[i];
    
    sort(a,a+n);
    
    vi pref(n,0);
    
    f(i,n) pref[i] = a[i];
    f(i,n-1) pref[i+1]+=pref[i];
    
    int res = (n*m);
    
    //make each value as a[i] 
    f(i,n)
    {
        int cur = a[i];
        int prv = cur;
        
        if(cur <= (m+1)/2) prv = 1;
        else prv = cur - m/2;
            
        int nex = cur;
        
        if(cur >= (m+1)/2) nex = m;
        else nex = cur + (m/2);
        
        int temp = 0;
        int idp = lower_bound(a,a+n,prv) - a;
        int cntp = i - idp + 1;
        int sump = pref[i];
        if(idp > 0) sump-=pref[idp-1];
        temp+=(a[i]*cntp) - sump;
        
        int idn = upper_bound(a,a+n,nex) - a - 1;
        int cntn = idn - i + 1;
        int sumn = pref[idn];
        if(i > 0) sumn -= pref[i-1];
        temp+=sumn - (cntn*a[i]);
        
        int nleft = n - i - cntn;
        int nsumleft = pref[n-1] - sumn;
        if(i > 0) nsumleft -= pref[i-1];
        temp+= (nleft*m) - nsumleft + (nleft*a[i]);
        
        int pleft = i + 1 - cntp;
        int psumleft = pref[i] - sump;
        temp+= psumleft + (pleft*(m - a[i]));
        
        res = min(res,temp);
    }
    
    cout << res << '\n';
}

signed main()
{
    fast;
    
    int t = 1;
    
    cin >> t;
    
    for(int i=1;i<=t;i++)
    {
    cout <<"Case #" << i<<": ";   
    solve();
    }
}