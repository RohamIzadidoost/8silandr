const ll maxn = 2e5 + 10;
ll z[maxn];
//  Pattern matching : maximum character matching of start at index i to prefix
//  text && pattern -----> s = pattern + '$' + text
// z[i] = number of match prifix start index i

void z_function(string s)
{
    ll left = 0, right = 0;
    for(int i = 1; i < s.size(); i++)
        if(i <= right && z[i - left] < right - i + 1)
            z[i] = z[i - left];
        else
        {
            if(i <= right)
                left = i;
            else
                left = right = i;
            while(right < s.size() && s[right] == s[right - left])
                right++;
            z[i] = right - left;
            right--;
        }
}