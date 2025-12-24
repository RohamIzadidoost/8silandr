// Make a vec of <l, r> and run this sort on it. Also after that move the in_l and in_r towards the sorted l, r.
bool cmp(int a, int b) {
	int l1 = l[a], r1 = r[a];
	int l2 = l[b], r2 = r[b];
	if(l1 / sq != l2 / sq) {
		return (l1 / sq) < (l2 / sq);
	}
	l1 /= sq;
	if(l1 % 2) return r2 < r1;
	return r1 < r2;
}
