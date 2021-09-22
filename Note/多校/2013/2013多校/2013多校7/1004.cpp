/* **********************************************
Author      : kuangbin
Created Time: 2013/8/13 15:10:49
File Name   : F:\2013ACM��ϰ\2013��У7\1004.cpp
*********************************************** */

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>


using namespace std;

const int MAXN = 50010;
int a[MAXN]; //��i����
int end[MAXN];//end[i]��ʾ��i����...һֱ���ӵ���n������kȡģ���ֵ

int len[MAXN];//��i�����ĳ���

int b[2][220]; //�������飬Ԥ�����Ե�i������β�ģ��������ӳɵĶ�kȡģ�õ�ֵ�ĸ���

int getlen(int n)//�õ�n�ж���λ
{
	int ret = 0;
	while(n)
	{
		ret++;
		n/=10;
	}
	return ret;
}
int Ten[10];//10^i  Ԥ��������Ԥ�����˺ܴ�10^i�ģ��������һԤ��������ͳ�ʱ,T_T



int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,k;
	while(scanf("%d%d",&n,&k) == 2)
	{
		for(int i = 1;i <= n;i++)
		{
		    scanf("%d",&a[i]);
			len[i] = getlen(a[i]);
		}
		Ten[0] = 1;
		for(int i = 1;i < 5;i++)
			Ten[i] = Ten[i-1]*10%k;
		int now = 0;
		memset(b,0,sizeof(b));
		b[now][a[1]%k] = 1;
		long long ans = 0;
		ans += b[now][0];
		for(int i = 2;i <= n;i++)
		{
			memset(b[now^1],0,sizeof(b[now^1]));
			b[now^1][a[i]%k] = 1;
			for(int j = 0;j < k;j++)
			{
				if(b[now][j] == 0)continue;
				int ttt = j*Ten[len[i]]%k+a[i];
				ttt%=k;
				b[now^1][ttt] += b[now][j];
			}
			now^=1;
			ans += b[now][0];

		}
		//ǰ���ۼӵĽ����û��a[n]��a[1]���ӵġ�
		//�������a[n]��a[1]���ӵļ���
		end[n] = a[n]%k;
		int tmp = len[n];
		int SSSS = Ten[len[n]];
		for(int i = n-1;i>= 1;i--)
		{
			end[i] = a[i]*SSSS%k + end[i+1];
			end[i]%=k;
			tmp += len[i];
			SSSS = SSSS*Ten[len[i]]%k;
		}
		tmp = len[1];
		SSSS = Ten[len[1]];
		int tt = a[1]%k;
		for(int i = 1;i < n;i++)
		{
			b[now][end[i]]--;
			for(int j = 0;j < k;j++)
			{
				int ppp = (j*SSSS%k+tt)%k;
				if(ppp == 0)ans += b[now][j];
			}
			tt = tt*Ten[len[i+1]]+a[i+1];
			tt%=k;
			tmp+=len[i+1];
			SSSS = SSSS*Ten[len[i+1]]%k;
		}
		printf("%I64d\n",ans);//T_T һ��Ҫlong long,����ò���Ǹպó�int~~

	}
    return 0;
}
