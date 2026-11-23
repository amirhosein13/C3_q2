#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m;vector<string> g;vector<char> fr,to,u;vector<int> cnt;
bool calc(){
    for(int i=0;i<n;i++)for(int j=0;j<m;j++){int c=i*m+j;fr[c]=g[i][j]=='.'&&((!i&&!j)||(i&&fr[c-m])||(j&&fr[c-1]));}
    for(int i=n-1;i>=0;i--)for(int j=m-1;j>=0;j--){int c=i*m+j;to[c]=g[i][j]=='.'&&((i==n-1&&j==m-1)||(i+1<n&&to[c+m])||(j+1<m&&to[c+1]));}
    if(!to[0])return 0;
    fill(cnt.begin(),cnt.end(),0);
    for(int i=0;i<n;i++)for(int j=0;j<m;j++){int c=i*m+j;u[c]=fr[c]&&to[c];if(u[c])cnt[i+j]++;}
    return 1;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;g.resize(n);for(auto&s:g)cin>>s;
    fr.resize(n*m);to.resize(n*m);u.resize(n*m);cnt.resize(n+m);
    ll F=0;for(auto&s:g)for(char c:s)F+=c=='.';
    if(!calc()){cout<<F*(F-1)/2<<"\n";return 0;}
    vector<int> c0=cnt;ll k=0;for(int x:c0)k+=x==1;
    ll ans=F*(F-1)/2-(F-k)*(F-k-1)/2;
    vector<pair<int,int>> L;{int i=0,j=0;L.push_back({0,0});while(i<n-1||j<m-1){if(i+1<n&&u[(i+1)*m+j])i++;else j++;L.push_back({i,j});}}
    for(auto [i,j]:L){
        if(c0[i+j]==1)continue;
        g[i][j]='*';calc();g[i][j]='.';
        for(int d=0;d<n+m-1;d++)if(cnt[d]==1&&c0[d]>1)ans++;
    }
    cout<<ans<<"\n";
}
