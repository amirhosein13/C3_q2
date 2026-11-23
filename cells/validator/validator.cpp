#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
// usage: validator [--sub allfree|n15|n50|n300]
int main(int argc,char*argv[]){
    registerValidation(argc,argv);
    string sub="";
    for(int i=1;i+1<argc;i++)if(string(argv[i])=="--sub")sub=argv[i+1];
    int lim=3000;
    if(sub=="n15")lim=15;else if(sub=="n50")lim=50;else if(sub=="n300")lim=300;
    else if(sub!=""&&sub!="allfree")quitf(_fail,"unknown subtask %s",sub.c_str());
    int n=inf.readInt(1,lim,"n");inf.readSpace();
    int m=inf.readInt(1,lim,"m");inf.readEoln();
    for(int i=0;i<n;i++){
        string pat=sub=="allfree"?"[.]{"+to_string(m)+"}":"[.*]{"+to_string(m)+"}";
        inf.readToken(pat,"row");
        inf.readEoln();
    }
    inf.readEof();
}
