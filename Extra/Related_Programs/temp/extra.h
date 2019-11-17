typeL mod(long m, typeL n)	//m%n
{
	return (m>=0)?m%n:mod(m+n,n);
}

typeL inverse(typeL num, typeL n)
{
	typeL i=0, p[1000],q[1000],t, r=num, d=n;
	if(d%r==0) return 1;
	do
	{
		t=d;
		q[i]=d/r;	
		d=r;
		r=t%r;
		if(i==0 || i==1) p[i]=i;
		else p[i]=mod(p[i-2]-p[i-1]*q[i-2],n);
		//cout<<t<<" = "<<q[i]<<"("<<d<<") + "<<r<<"\tP"<<i<<" = "<<p[i]<<endl;
		i++;	
	
	} 
	while(r!=0);
	p[i]=mod( (p[i-2]-p[i-1]*q[i-2]) , n);
    	return p[i];
}
