#include <bits/stdc++.h>
using namespace std;
typedef int ll;
int n,m;
int main(){
    if(scanf("%d %d",&n,&m)!=2)return 0;
    vector<string> g(n);
    static char buf[3005];
    for(int i=0;i<n;i++){if(scanf("%s",buf)!=1)return 0;g[i]=buf;}
    auto id=[&](int i,int j){return i*m+j;};
    vector<char> fr(n*m,0),to(n*m,0),u(n*m,0),rr(n*m,0);
    ll F=0;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++){
        if(g[i][j]!='.')continue; F++;
        fr[id(i,j)]=(i==0&&j==0)||(i&&fr[id(i-1,j)])||(j&&fr[id(i,j-1)]);
    }
    for(int i=n-1;i>=0;i--)for(int j=m-1;j>=0;j--){
        if(g[i][j]!='.')continue;
        to[id(i,j)]=(i==n-1&&j==m-1)||(i+1<n&&to[id(i+1,j)])||(j+1<m&&to[id(i,j+1)]);
    }
    if(!to[0]){printf("%d\n",F*(F-1)/2);return 0;}
    int D=n+m-1;
    vector<int> cnt(D,0);
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(fr[id(i,j)]&&to[id(i,j)])u[id(i,j)]=1,cnt[i+j]++;
    ll k=0;for(int d=0;d<D;d++)k+=cnt[d]==1;
    ll ans=F*(F-1)/2-(F-k)*(F-k-1)/2;
    vector<pair<int,int>> L,R;
    {int i=0,j=0;L.push_back({0,0});while(i+j<D-1){if(i+1<n&&u[id(i+1,j)])i++;else j++;L.push_back({i,j});}}
    {int i=0,j=0;R.push_back({0,0});while(i+j<D-1){if(j+1<m&&u[id(i,j+1)])j++;else i++;R.push_back({i,j});}}
    for(auto [i,j]:R)if(cnt[i+j]>1)rr[id(i,j)]=1;
    vector<int> fw(n*m,0),bw(n*m,0);
    for(int i=n-1;i>=0;i--)for(int j=m-1;j>=0;j--){
        int c=id(i,j);if(!u[c])continue;
        int nx=-1;
        if(i+1<n&&u[id(i+1,j)])nx=id(i+1,j);else if(j+1<m&&u[id(i,j+1)])nx=id(i,j+1);
        fw[c]=rr[c]+(nx>=0?fw[nx]:0);
    }
    for(int i=0;i<n;i++)for(int j=0;j<m;j++){
        int c=id(i,j);if(!u[c])continue;
        int pv=-1;
        if(j&&u[id(i,j-1)])pv=id(i,j-1);else if(i&&u[id(i-1,j)])pv=id(i-1,j);
        bw[c]=rr[c]+(pv>=0?bw[pv]:0);
    }
    for(auto [i,j]:L){
        if(cnt[i+j]==1)continue;
        int r=i-1,c=j+1;
        while(!u[id(r,c)])r--,c++;
        int x=id(r,c);
        ans+=fw[x]+bw[x]-rr[x];
    }
    printf("%d\n",ans);
}
