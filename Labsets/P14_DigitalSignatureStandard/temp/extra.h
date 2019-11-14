typeL mod(typeL m, typeL n)	//m%n
{
	return (m%n>=0)?m%n:mod(n-m,n);
}

typeL inverse(typeL num, typeL n)
{
    	typeL i,p[100],q[100],t,r=num,d=n;
    	i=0;
    	if(d%r==0) return 1;
    	do
    	{
        	t=d;
        	q[i]=d/r;
        	d=r;
        	r=t%r;
        	if(i==0 || i==1) p[i]=i;
        	else p[i]=mod( (p[i-2]-p[i-1]*q[i-2]) , n);
        	i++;
    	}
    	while(r!=0);
    	p[i]=mod( (p[i-2]-p[i-1]*q[i-2]) , n);
    	return p[i];
}
