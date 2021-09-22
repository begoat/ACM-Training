#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,p,k,head[160],rd[160],dp[160][160],siz[160],ans=0x3f3f3f;
struct edge {int to,next;} ed[330];
void adde(int u,int v){ed[++k].to=v;ed[k].next=head[u];head[u]=k;}

void dfs1(int u,int fa)
{
	siz[u]++;
	for(int i=head[u];i;i=ed[i].next)
	{
		int v=ed[i].to;
		if(v==fa) continue;
		dfs1(v,u);
		siz[u]+=siz[v];
	}
	dp[u][siz[u]]=1;//����е�����������ֻ���е��븸�ڵ������
	dp[u][0]=0;//����
}

void dfs2(int u,int fa)
{
	for(int i=head[u];i;i=ed[i].next)
	{
		int v=ed[i].to;
		if(v==fa) continue;
		dfs2(v,u);
		for(int j=siz[u]-1;j;j--)//���ж���
		for(int k=0;k<=j ;k++)//�ҵĶ����ж���
		dp[u][j]=min(dp[u][j],dp[u][j-k]+dp[v][k]);
		//����j���ڵ��е����ٱ���=min ����j-k���ڵ�����ٱ���+�ҵĶ�����k���ڵ�����ٱ���
	}
	if(siz[u]-p>=0)//����ô��ڵ�
	ans=min(ans,dp[u][siz[u]-p]+bool(fa));
	//min �е�siz[u]-p���ڵ�(ʣP���ڵ�)�����ٱ���+�ֿ����븸�׵ı�
}

int main()
{
	scanf("%d%d",&n,&p);
	memset(dp,0x3f3f3f,sizeof(dp));//��ʼ��Ϊ���ֵ
	for(int i=1;i<=n-1;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		adde(u,v);adde(v,u);
	}
	dfs1(1,1);//��siz���� & ��ʼ��
	dp[1][siz[1]]=0;//���ڵ㲻��Ҫ�븸�ڵ�ֿ�  ��û�и��ס�������
	dfs2(1,0);//����dp
	printf("%d",ans);
	return 0;
}
