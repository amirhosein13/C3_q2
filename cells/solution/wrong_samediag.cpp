#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int n,m;cin>>n>>m;vector<string> g(n);for(auto&s:g)cin>>s;
    vector<vector<char>> fr(n,vector<char>(m)),to=fr;
    ll F=0;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(g[i][j]=='.'){F++;fr[i][j]=(!i&&!j)||(i&&fr[i-1][j])||(j&&fr[i][j-1]);}
    for(int i=n-1;i>=0;i--)for(int j=m-1;j>=0;j--)if(g[i][j]=='.')to[i][j]=(i==n-1&&j==m-1)||(i+1<n&&to[i+1][j])||(j+1<m&&to[i][j+1]);
    if(!to[0][0]){cout<<F*(F-1)/2<<"\n";return 0;}
    vector<int> cnt(n+m);
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(fr[i][j]&&to[i][j])cnt[i+j]++;
    ll k=0,two=0;for(int x:cnt)k+=x==1,two+=x==2;
    cout<<F*(F-1)/2-(F-k)*(F-k-1)/2+two<<"\n";
}
