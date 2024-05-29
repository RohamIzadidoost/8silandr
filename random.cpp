mt19937 Rnd;
int Rand(int l, int r)
{
    return (Rnd() % (r - l + 1) + l);
}
Rnd.seed(time(0));
