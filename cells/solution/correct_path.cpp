#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m;
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    vector<string> g(n);for(auto&s:g)cin>>s;
    vector<vector<char>> fr(n,vector<char>(m)),to=fr,u=fr,rr=fr;
    ll F=0;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(g[i][j]=='.'){F++;fr[i][j]=(!i&&!j)||(i&&fr[i-1][j])||(j&&fr[i][j-1]);}
    for(int i=n-1;i>=0;i--)for(int j=m-1;j>=0;j--)if(g[i][j]=='.')to[i][j]=(i==n-1&&j==m-1)||(i+1<n&&to[i+1][j])||(j+1<m&&to[i][j+1]);
    if(!to[0][0]){cout<<F*(F-1)/2<<"\n";return 0;}
    int D=n+m-1;vector<int> cnt(D);
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(fr[i][j]&&to[i][j])u[i][j]=1,cnt[i+j]++;
    ll k=0;for(int x:cnt)k+=x==1;
    ll ans=F*(F-1)/2-(F-k)*(F-k-1)/2;
    vector<pair<int,int>> L,R;
    {int i=0,j=0;L.push_back({0,0});while(i+j<D-1){if(i+1<n&&u[i+1][j])i++;else j++;L.push_back({i,j});}}
    {int i=0,j=0;R.push_back({0,0});while(i+j<D-1){if(j+1<m&&u[i][j+1])j++;else i++;R.push_back({i,j});}}
    for(auto [i,j]:R)if(cnt[i+j]>1)rr[i][j]=1;
    for(auto [i,j]:L){
        if(cnt[i+j]==1)continue;
        int r=i-1,c=j+1;while(!u[r][c])r--,c++;
        ll s=rr[r][c];
        int a=r,b=c;
        while(a||b){if(b&&u[a][b-1])b--;else a--;s+=rr[a][b];}
        a=r,b=c;
        while(a<n-1||b<m-1){if(a+1<n&&u[a+1][b])a++;else b++;s+=rr[a][b];}
        ans+=s;
    }
    cout<<ans<<"\n";
}
