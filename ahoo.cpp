//Aho 
void AddTrie(){
    int v=0;
    for (char ch:S){
        if (!C[v][ch-'a']) C[v][ch-'a']=++ts;
        v=C[v][ch-'a'];
    }
    ted[v]++;
}
void BuildAho(){
    for (int i=0; i<SGM; i++) if (C[0][i]) Q[R++]=C[0][i];
    while (L<R){
        int v=Q[L++];
        ted[v]++;
        for (int i=0; i<SGM; i++){
            if (!C[v][i]) C[v][i]=C[F[v]][i];
            else{
                F[C[v][i]]=C[F[v]][i];
                Q[R++]=C[v][i];
            }
        }
    }
}//
for(int i = 1 ; i <= ts  ; i++ ) adj[f[i]].pb(i) ;
