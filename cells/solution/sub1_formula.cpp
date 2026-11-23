#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ll n,m;cin>>n>>m;string s;bool fr=1;
    for(int i=0;i<n;i++){cin>>s;for(char c:s)fr&=c=='.';}
    if(!fr){puts("0");return 0;}
    ll F=n*m;auto C=[](ll x){return x*(x-1)/2;};
    ll ans;
    if(n==1||m==1)ans=C(F);
    else if(n==2||m==2){ll k=max(n,m);ans=C(F)-C(F-2)+k*(k-1)/2;}
    else ans=C(F)-C(F-2)+2;
    cout<<ans<<"\n";
}
