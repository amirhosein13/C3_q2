#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m;vector<string> g;vector<int> fr,to,cnt;
// returns -1 if no path, else number of single-cell cuts
ll cuts(){
    for(int i=0;i<n;i++)for(int j=0;j<m;j++){int c=i*m+j;fr[c]=g[i][j]=='.'&&((!i&&!j)||(i&&fr[c-m])||(j&&fr[c-1]));}
    for(int i=n-1;i>=0;i--)for(int j=m-1;j>=0;j--){int c=i*m+j;to[c]=g[i][j]=='.'&&((i==n-1&&j==m-1)||(i+1<n&&to[c+m])||(j+1<m&&to[c+1]));}
    if(!to[0])return -1;
    fill(cnt.begin(),cnt.end(),0);
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(fr[i*m+j]&&to[i*m+j])cnt[i+j]++;
    ll k=0;for(int x:cnt)k+=x==1;return k;
}
int main(){
    cin>>n>>m;g.resize(n);for(auto&s:g)cin>>s;
    fr.resize(n*m);to.resize(n*m);cnt.resize(n+m);
    ll F=0;for(auto&s:g)for(char c:s)F+=c=='.';
    if(cuts()<0){cout<<F*(F-1)/2<<"\n";return 0;}
    ll tot=0;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(g[i][j]=='.'){
        g[i][j]='*';ll k=cuts();g[i][j]='.';
        tot+=k<0?F-1:k;
    }
    cout<<tot/2<<"\n";
}
