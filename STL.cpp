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

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace __gnu_pbds;
typedef cc_hash_table<ll, ll, hash<ll>> ht;


#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace __gnu_pbds;
typedef cc_hash_table<
    ll, ll, hash<ll>, equal_to<ll>, direct_mask_range_hashing<ll>,
    hash_standard_resize_policy<hash_exponential_size_policy<>, hash_load_check_resize_trigger<true>, true>>
    ht;
 
