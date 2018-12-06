#include <iostream>
#include <vector>

using namespace std;

int n;

struct node{

	int sum, greater, begin, end, lazy, on;

	vector<node> sons;

	node(int begin_=1, int end_=n){
	    sum=0;
	    greater=0;
	    lazy=0;
        begin=begin_, end=end_;
		on=0;
	}
	void flush(){

	  if(sons.empty()&&begin<end){
            int mid=(begin+end)>>1;
			sons.push_back(node(begin,mid));
			sons.push_back(node(mid+1,end));
		}

		if(on){

			if(end>begin){

				sons[0].lazy=sons[1].lazy=lazy;
				sons[0].on=sons[1].on=on;
			}

			sum=greater=(end-begin+1)*lazy;
		}
		lazy=on=0;
	}

	int query(int h){
	    flush();
	    if(greater<h)
            return n;

		if(begin==end){

			if(greater>h) return begin-1;
			return begin;
		}
		sons[0].flush();
		if(sons[0].greater>h) return sons[0].query(h);
		return sons[1].query(h-sons[0].sum);
	}

	void update(int a, int b, int d){
	    flush();
		if(a>end or b<begin) return;

		if(a<=begin and b>=end){

			lazy=d;
			on=1;
			flush();
			return;
		}
		sons[0].update(a,b,d);
		sons[1].update(a,b,d);

		sum=sons[0].sum+sons[1].sum;
		greater=max(sons[0].greater,sons[0].sum+sons[1].greater);
	}

	void print(){

		if(sons.size()) sons[0].print(), sons[1].print();
	}
};

int main(){

	ios_base::sync_with_stdio(false), cin.tie();

	cin >> n;

	node segtree;

	char op;

	while(cin>>op and op!='E'){

		if(op=='Q'){

			int h;
			cin >> h;

			cout << segtree.query(h) << '\n';
		}

		if(op=='I'){

			int a, b, d;
			cin >> a >> b >> d;

			segtree.update(a,b,d);
		}
	}

	return 0;
}
