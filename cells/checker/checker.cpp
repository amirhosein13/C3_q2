#include "testlib.h"
using namespace std;
// The answer is unique: whitespace-insensitive token comparison.
int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    int k=0;
    while(!ans.seekEof()){
        string a=ans.readToken();
        if(ouf.seekEof())quitf(_wa,"expected %s, found EOF",a.c_str());
        string b=ouf.readToken();k++;
        if(a!=b)quitf(_wa,"token %d differs: expected %s, found %s",k,a.c_str(),b.c_str());
    }
    if(!ouf.seekEof())quitf(_wa,"extra tokens in output");
    quitf(_ok,"%d token(s)",k);
}
