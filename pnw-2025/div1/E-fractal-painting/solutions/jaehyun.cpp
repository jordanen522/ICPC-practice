#include<iostream>
using namespace std;
using ll = long long;
int main()
{
    int T; scanf("%d", &T);
    while(T--)
    {
        ll x0, y0, x1, y1, x2, y2;
        cin>>x0>>y0>>x1>>y1>>x2>>y2;
        ll alen2 = x0*x0+y0*y0;
        ll blen2 = (x1-x0)*(x1-x0)+(y1-y0)*(y1-y0);
        ll clen2 = (x2-x0)*(x2-x0)+(y2-y0)*(y2-y0);
        if(blen2>alen2 || clen2>alen2) cout<<"NO\n";  // diverging segment lengths
        else if(alen2==blen2 && x1==2*x0 && y1==2*y0) cout<<"NO\n";  // same length, same direction --> diverges
        else if(alen2==clen2 && x2==2*x0 && y2==2*y0) cout<<"NO\n";  // same length, same direction --> diverges
        else if(blen2<alen2 || clen2<alen2) cout<<"YES\n"; // at least one segment is strictly convergent
        else cout<<"NO\n"; // segment lengths don't change but point to different directions:
        // can always find a point further from the origin by "walking along a circle then switching to a different circle"
    }
    return 0;
}
