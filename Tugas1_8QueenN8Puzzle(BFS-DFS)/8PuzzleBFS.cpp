#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <deque>
#include <stack>
using namespace std;

class State{ 
public:
	// int a[9] {1,2,3,8,6,4,7,5,0};
	int a[9] {2,8,3,1,6,4,7,0,5};
	
	//printout kondisi puzzle
	void print(){
		for(int i=0; i<9; i++){
			if (i>0 && i%3==0) cout <<endl;
			cout << a[i] << "\t";
		}
		cout << endl << "__________________" << endl;
	}
	
	int found(int i){
		for(int j=0; j<i; j++){
			if (a[i]==a[j]) return 1;
		}
		return 0;
	}
	
	//untuk mencari node yang bisa digerakkan
	int findzero(){
		for (int i=0; i<9; i++){
			if (a[i]==0) return i;
		}
	}
	
	//menukar elemen
	State exch(int i, int j){
		State b;
		for (int k=0; k<9; k++)
			b.a[k]=a[k];
		int t=b.a[i];
		b.a[i]=b.a[j];
		b.a[j]=t;
		return b;
	}

	int equal(State s){
		for(int i=0; i<9; i++){
			if (a[i]!=s.a[i]) return 0;
		}
		return 1;
	}
	
	//puzzle yang tersusun dengan benar
	// 1	2	3			_>>	  _>>	 _v
	// 8	0	4			X	  0	 	 _v
	// 7	6	5			^_	  <<_	<<_
	int goal(){
		int g[9] = {1,2,3,8,0,4,7,6,5};
		for (int i=0; i<9; i++){
			if (a[i]!=g[i]) return 0; 
		}
		return 1;
	}
	
};

class Node{
public:
	State s;
	Node *father;
	int action, Step, depth;
	
	//buat kondisi awal
	Node(){
		State s();
		father=NULL;
		action=-1;
		Step=1;
		depth=0;
	}
	
	//ekspansi
	Node(State _s, Node *_father, int _action, int _depth){
		s=_s;
		father=_father;
		action=_action;
		depth=_depth;
	}

	Node copy(){
		Node b;
		for (int i=0; i<9; i++)
			b.s.a[i]=s.a[i];		
		b.father=father;
		b.action=action;
		b.depth=depth;
		
		return b;
	}
	
	void print(){
		cout << "Step: \t" << depth << endl;
	}
	
	//step ekspansi geser
	void expand(deque<Node> *deque){
		//temukan node untuk digeser
		int p = s.findzero();
		//moveup	(0)
		if ((p!=0 && p!=1 && p!=2) && action!=1){
			Node n(s.exch(p,p-3), this, 0, depth+1);
			(*deque).push_back(n);
		}
		//movedown 	(1)
		if ((p!=6 && p!=7 && p!=8) && action!=0){
			Node n(s.exch(p,p+3), this, 1, depth+1);
			(*deque).push_back(n);
		}
		//moveright (2)
		if ((p!=2 && p!=5 && p!=8) && action!=3){
			Node n(s.exch(p,p+1), this, 2, depth+1);
			(*deque).push_back(n);
		}
		//moveleft 	(3)
		if ((p!=0 && p!=3 && p!=6) && action!=2){
			Node n(s.exch(p,p-1), this, 3, depth+1);
			(*deque).push_back(n);
		}
	}
	
	//cek node yang diekspansi
	int expanded(deque<State> *deque){
		int max=(*deque).size()>depth?depth:(*deque).size();
		for (int i=0; i<max; i++){
			if ( s.equal( (*deque)[i] ) ){
				return 1;
			}
		}
		return 0;
	}

		
	int bfs(){
		deque<Node> toexpand;
		deque<State> expanded;
		
		toexpand.push_back(*this);
		while ( !toexpand.empty() ){
			if ( toexpand.front().s.goal()==1 ){ 
				cout << "BFS" << endl;
				cout << "Bisa diselesaikan" << endl;
				toexpand.front().print();
				Step = toexpand.front().Step;
				toexpand.clear();
				return Step;
			}
			else{
				if ( !(toexpand.front().expanded(&expanded)) ){
					toexpand.front().expand(&toexpand);
					expanded.push_front( toexpand.front().s );
					toexpand[1].Step=toexpand[0].Step+1;
				}
				toexpand.pop_front();
			}
		}
		if ( toexpand.empty() ) cout << endl << "Tidak bisa diselesaikan" << endl;
		return 0;
	}
	
};

	
int main(int argc, char *argv[]){
	int num=1;
	int i=0;	
		
        Node n;
		n.s.print();
		n.bfs();
		cout<<endl;
		return 0;
}