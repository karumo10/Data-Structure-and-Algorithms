void Permutation(int a[],int m,int n){
    if(m==n){
        cout<<a[0];
        for(int i=1;i<n;i++){
            cout<<" "<<a[i];
        }
        cout<<endl;
    }
    else {
        for(int i=m;i<n;i++){
            int temp=a[m];
            a[m]=a[i];
            a[i]=temp;
            Permutation(a,m+1,n);
            temp=a[m];
            a[m]=a[i];
            a[i]=temp;
        }
    }
}
