#include<bits/stdc++.h>
 
typedef int LL;  //Attention!!
using namespace std;
 
#define fillchar(a, x) memset(a, x, sizeof(a))
#define MP make_pair
#define PB push_back
#define endl '\n'
 
const int M = 1000000007;
 
typedef complex<double> base;
 
//polynomials are taken as a0 + a1x + a2x^2...
void fft (vector<base> & a, bool invert) 
{
	int n = (int) a.size();
	if (n == 1)  return;
 
	vector<base> a0 (n/2),  a1 (n/2);
	for (int i=0, j=0; i<n; i+=2, ++j) 
	{
		a0[j] = a[i];
		a1[j] = a[i+1];
	}
	
	fft (a0, invert);
	fft (a1, invert);
 
	double ang = 2*M_PI/n * (invert ? -1 : 1);
	base w (1),  wn (cos(ang), sin(ang));
for (int i=0; i<n/2; ++i) 
	{
		a[i] = a0[i] + w * a1[i];
		a[i+n/2] = a0[i] - w * a1[i];
		if (invert)
			a[i] /= 2,  a[i+n/2] /= 2;  //while doing inverse why is this happening.....
		w *= wn;
	}
}
 
 
 
void multiply (const vector<int> & a, const vector<int> & b, vector<int> & res) 
{
	vector<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
	size_t n = 1;
	while (n < max (a.size(), b.size()))  n <<= 1;
	n <<= 1;
	fa.resize (n),  fb.resize (n);
 
	fft (fa, false),  fft (fb, false);
	for (size_t i=0; i<n; ++i)
		fa[i] *= fb[i];
	fft (fa, true);
 
	res.resize (n);
	for (size_t i=0; i<n; ++i)
		res[i] = int (fa[i].real() + 0.5);
}
 
int main()
{
ios_base::sync_with_stdio(0); cout.precision(15);cout.setf(ios::fixed);
LL n,i,j,m;
 
cin>>n;
 
string a,b;
 
 
for(i=0;i<n;i++)
{
cin>>a>>b;
vector <LL> u,v,res;
 
for(j=a.size()-1;j>=0;j--) u.PB(a[j]-'0');
for(j=b.size()-1;j>=0;j--) v.PB(b[j]-'0');
 
multiply(u,v,res);
 
for(j=0;j<res.size()-1;j++)
	{
	if(res[j]>=10)
		{
		res[j+1] += (res[j]/10);	
		res[j] %= 10;	
		}	
	}
 
//for(j=0;j<res.size();j++)  cout<<res[j]<<endl;
 
j = res.size()-1;
 
while(j>=0 && res[j]==0) j--;
 
if(j==-1) cout<<'0';
 
for(;j>=0;j--)
	cout<<res[j];
cout<<endl;
 
}
 
 
}
 
 