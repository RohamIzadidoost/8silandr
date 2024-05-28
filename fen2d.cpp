map<pair<int,int>,int>tree;
int MAXX = 1e5 + 5, MAXY = 1e5+5;

void update( int x, int y, int val )
{
    while( x <= MAXX )
    {
        int now = y;
        while( now <= MAXY )
        {
            tree[{x,now}] += val;
            now += now&(-now);
        }
        x += x&(-x);
    }
}

int get( int x, int y )
{
    int ans = 0;
    while( x > 0 )
    {
        int now = y;
        while( now > 0 )
        {
            if( tree.find({x,now}) != tree.end() )
                ans += tree[{x,now}];
            now -= now&(-now);
        }
        x -= x&(-x);
    }
    return ans;
}
