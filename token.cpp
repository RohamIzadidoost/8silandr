
vector<string> token(string& s, string& del)
{
    vector<string> ans; 
    int start = 0, last = 0;
    while ((last = s.find_first_of(del, start)) != string::npos) 
	{
        if (last != start) 
            ans.pb(s.substr(start, last - start));
        start = last + 1;                  
    }
    if (start != s.length()) 
        ans.pb(s.substr(start));
    return ans;
}

int main()
{
    string inp = "Hello,World;This|is.GeeksForGeeks pam";
    string del = ",;.| ";
    vector<string> ans = token(inp, del);
}
