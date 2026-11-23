#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
// usage: gen <type> <n> <m> <a> <b> <corner> [tag]
// types:
//  rand     : each cell blocked with prob a/1000
//  free     : all free
//  thick    : random monotone path dilated by random radius in [0,a] (per segment of length ~b), other cells free w.p. noise 1/1000*? (noise fixed 0)
//  thickn   : like thick, other cells blocked w.p. 1-(... ) -> outside cells free w.p. b/1000, radius a
//  paths    : union of a random monotone paths (bias b/1000 toward going down), rest blocked
//  ring     : border of the grid free, interior blocked w.p. 1-a/1000 (interior free w.p. a/1000)
//  ladder   : free band of width a around the main "diagonal" line, with blocked holes w.p. b/1000
// corner: bit0 -> block (1,1), bit1 -> block (n,m), bit2 -> force both corners free (applied first)
int n,m;
vector<string> g;
vector<pair<int,int>> randPath(int bias){ // bias in [0,1000]: prob of down when both possible
    vector<pair<int,int>> p;int i=0,j=0;p.push_back({0,0});
    while(i<n-1||j<m-1){
        bool down;
        if(i==n-1)down=false;else if(j==m-1)down=true;else down=rnd.next(1000)<bias;
        if(down)i++;else j++;p.push_back({i,j});
    }
    return p;
}
int main(int argc,char*argv[]){
    registerGen(argc,argv,1);
    string type=argv[1];n=atoi(argv[2]);m=atoi(argv[3]);int a=atoi(argv[4]),b=atoi(argv[5]),corner=atoi(argv[6]);
    g.assign(n,string(m,'.'));
    auto bal=[&](){ // bias so that random path ends roughly on the anti-corner proportionally
        return (int)(1000.0*n/(n+m));
    };
    if(type=="rand"){
        for(auto&s:g)for(auto&c:s)c=rnd.next(1000)<a?'*':'.';
    }else if(type=="free"){
    }else if(type=="thick"||type=="thickn"){
        int noise=type=="thickn"?b:0;
        for(auto&s:g)for(auto&c:s)c=rnd.next(1000)<noise?'.':'*';
        auto p=randPath(bal());
        int seg=type=="thick"?max(1,b):max(1,(n+m)/20),r=rnd.next(0,a);
        for(size_t t=0;t<p.size();t++){
            if(t%seg==0)r=rnd.next(0,a);
            auto [i,j]=p[t];
            for(int x=max(0,i-r);x<=min(n-1,i+r);x++)for(int y=max(0,j-r);y<=min(m-1,j+r);y++)g[x][y]='.';
        }
    }else if(type=="paths"){
        for(auto&s:g)for(auto&c:s)c='*';
        for(int k=0;k<a;k++){
            int bias=b>0?b:bal();
            if(b<0)bias=rnd.next(100,900);
            for(auto [i,j]:randPath(bias))g[i][j]='.';
        }
    }else if(type=="ring"){
        for(int i=0;i<n;i++)for(int j=0;j<m;j++)
            if(!(i==0||j==0||i==n-1||j==m-1))g[i][j]=rnd.next(1000)<a?'.':'*';
    }else if(type=="ladder"){
        for(int i=0;i<n;i++)for(int j=0;j<m;j++){
            double ci=(double)j*(n-1)/max(1,m-1);
            g[i][j]=(fabs(i-ci)<=a&&rnd.next(1000)>=b)?'.':'*';
        }
    }else{
        quitf(_fail,"unknown type");
    }
    if(corner&4)g[0][0]=g[n-1][m-1]='.';
    if(corner&1)g[0][0]='*';
    if(corner&2)g[n-1][m-1]='*';
    printf("%d %d\n",n,m);
    for(auto&s:g)printf("%s\n",s.c_str());
}
