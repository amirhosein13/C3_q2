#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m;vector<string> g;
bool path(){
    vector<vector<char>> r(n,vector<char>(m,0));
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(g[i][j]=='.')r[i][j]=(!i&&!j)||(i&&r[i-1][j])||(j&&r[i][j-1]);
    return r[n-1][m-1];
}
int main(){
    cin>>n>>m;g.resize(n);for(auto&s:g)cin>>s;
    vector<pair<int,int>> f;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(g[i][j]=='.')f.push_back({i,j});
    ll ans=0;
    for(size_t a=0;a<f.size();a++)for(size_t b=a+1;b<f.size();b++){
        g[f[a].first][f[a].second]='*';g[f[b].first][f[b].second]='*';
        if(!path())ans++;
        g[f[a].first][f[a].second]='.';g[f[b].first][f[b].second]='.';
    }
    cout<<ans<<"\n";
}
