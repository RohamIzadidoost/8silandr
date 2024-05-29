Bitset:
bitset<4> b3{"0011"};
b3.set(position_t(1), true);
b3[2] = true;

Custom Sorted Set:
struct AbsoluteValueComparator { 
    bool operator()(int a, int b) const
    { 
        return abs(a) < abs(b); 
    } 
};
set<int, AbsoluteValueComparator> mySet; 

lower_bound on vector:
ll pos = lower_bound(Rs.begin() , Rs.end() , value) - Rs.begin() ; 

Compress:
sort(all(v))
v.erase(unique(all(v)) , v.end())

