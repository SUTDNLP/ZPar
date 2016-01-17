/*
 * based on ldc tokenization rule
 *
 * author: jiangming liu
 *
 *
 */
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fstream>
using namespace std;

class Node {
	
public:
    char c;
	Node* next;
	Node(){
		c = ' ';
		next = NULL;
	};
	Node(char _c){
		c = _c;
		next = NULL;
	}
	~Node(){};
};

void init_List(Node *h, const string &a){
	Node *p = h;
	for(int i = 0; i < a.size(); i ++){
		Node *current = new Node(a[i]);
		p->next = current;
		p = current;
	}
}
void clean_List(Node *h){
	Node *p;
	while(h){
		p = h->next;
		delete h;
		h = p;
	}
}
Node* insert(Node *p, Node *node){
	Node *pnext = p->next;
	p->next = node;
	p = p->next;
	if(pnext){
		p->next = pnext;
	}
	return p;
}
void del(Node *p){
	if(p->next){
		Node *pnext = p->next;
		Node *pnextnext = pnext->next;
		p->next = pnextnext;
		delete pnext;
	}
}
void p1(Node *h){
	Node *p = h;
	Node *pn = p->next;
	if(pn != NULL && pn->c == '\"'){
//		cout<<"p1"<<endl;
		Node *node;
		node = new Node('`');
		p = insert(p,node);		
		node = new Node('`');
		p = insert(p,node);
		node = new Node(' ');
		p = insert(p,node);

		del(p);
	}
}
void p2(Node *h){
	Node *p = h;
	while(p){
		Node *pn = p->next;
		if(pn == NULL || (pn->c != '(' &&
		   pn->c != '[' &&
		   pn->c != ' ' &&
		   pn->c != '{' &&
		   pn->c != '<')){
			p = p->next;
			continue;
		}
		Node *pnn = pn->next;
		if(pnn == NULL || pnn->c != '\"'){
			p = p->next;
			continue;
		}
//		cout<<"p2"<<endl;
		Node *node;
		node = new Node(' ');
		pn = insert(pn,node);
		node = new Node('`');
		pn = insert(pn,node);
		node = new Node('`');
		pn = insert(pn,node);
		node = new Node(' ');
		pn = insert(pn,node);
		
		del(pn);
		p = pn;
	}
}
void p3(Node *h){
	Node *p = h;
	while(p){
		Node *pn = p->next;
		if(pn == NULL || pn->c != '.') {
			p = p->next;
			continue;
		}
		Node *pnn = pn->next;
		if(pnn == NULL || pnn->c != '.') {
			p = p->next;
			continue;
		}
		Node *pnnn = pnn->next;
		if(pnnn == NULL || pnnn->c != '.') {
			p = p->next;
			continue;
		}
//		cout<<"p3"<<endl;
		Node *node;
		node = new Node(' ');
		p = insert(p,node);
		node = new Node(' ');
		pnnn = insert(pnnn,node);
		p = pnnn;
	}
}
void p4(Node *h){
	Node *p = h;
	while(p){
		Node *pn = p->next;
		if(pn == NULL || (
			pn->c != ',' &&
			pn->c != ';' &&
			pn->c != ':' &&
			pn->c != '@' &&
			pn->c != '#' &&
			pn->c != '$' &&
			pn->c != '%' &&
			pn->c != '&')){
			p = p->next;
			continue;
		}
//		cout<<"p4"<<endl;
		Node *node;
		node = new Node(' ');
		p = insert(p,node);
		node = new Node(' ');
		pn = insert(pn,node);
		p = pn;
	}
}
void p5(Node *h){
	Node *p = h;
	while(p){
		Node *pn = p->next;
		if(pn == NULL || pn->c == '.'){
			p = p->next;
			continue;
		}
		Node *pnn = pn->next;
		if(pnn == NULL || pnn->c != '.'){
			p = p->next;
			continue;
		}
		Node *pnnn = pnn->next;
		if(pnnn == NULL){
//			cout<<"p5_1 "<<p->c<<endl;
			Node *node;
			node = new Node(' ');
			pn = insert(pn,node);
			node = new Node(' ');
			pnn = insert(pnn,node);
			break;
		}
		Node *p1 = pnnn;
		while(p1){
			if(p1->c != ']' &&
			   p1->c != ')' &&
			   p1->c != '}' &&
			   p1->c != '>' &&
			   p1->c != '\"'&&
			   p1->c != '\'')
				break;
			p1 = p1->next;
		}
		Node *p2 = p1;
		while(p2){
			if(p2->c != ' ' && p2->c != '\t')
				break;
			p2 = p2->next;
		}
		if(p2){
			p = p->next;
			continue;
		}
//		cout<<"p5_3"<<endl;
		Node* node;
		node = new Node(' ');
		pn = insert(pn, node);
		node = new Node(' ');
		p1->c = ' ';
		clean_List(p1->next);
		p1->next = NULL;
		break;
	}
}
void p6(Node *h){
	Node *p = h;
	while(p){
		Node *pn = p->next;
		if(pn == NULL || (pn->c != '?' && pn->c != '!')){
			p = p->next;
			continue;
		}
//		cout<<"p6"<<endl;
		Node *node = new Node(' ');
		p = insert(p,node);
		node = new Node(' ');
		pn = insert(pn,node);
		p = pn;
	}
}
void p7(Node *h){
	Node *p = h;
	while(p){
		Node *pn = p->next;
		if(pn == NULL || 
			(pn->c != ']' &&
			 pn->c != '[' &&
			 pn->c != '(' &&
			 pn->c != ')' &&
			 pn->c != '{' &&
			 pn->c != '}' &&
			 pn->c != '<' &&
			 pn->c != '>')){
			p = p->next;
			continue;
		}
//		cout<<"p7"<<endl;
		Node *node = new Node(' ');
		p = insert(p,node);
		node = new Node(' ');
		pn = insert(pn,node);
		p = pn;
	}
}
void p8(Node *h){
	Node *p = h;
	while(p){
		Node *pn = p->next;
		if(pn == NULL || pn->c != '-'){
			p = p->next;
			continue;
		}
		Node *pnn = pn->next;
		if(pnn == NULL || pnn->c != '-'){
			p = p->next;
			continue;
		}
//		cout<<"p8"<<endl;
		Node *node = new Node(' ');
		p = insert(p,node);
		node = new Node(' ');
		pnn = insert(pnn,node);
		p = pnn;
	}
}
void p9(Node *h){
	Node *p = h;
	Node *node = new Node(' ');
	p = insert(p,node);
	while(p->next){
		p = p->next;
	}
	node = new Node(' ');
	p = insert(p, node);
}
void p10(Node *h){
	Node *p = h;
	while(p){
		Node *pn = p->next;
		if(pn == NULL || pn->c != '\"'){
			p = p->next;
			continue;
		}
//		cout<<"p10"<<endl;
		Node *node;
		node = new Node(' ');
		p = insert(p,node);
		node = new Node('\'');
		p = insert(p,node);
		node = new Node('\'');
		p = insert(p,node);
		node = new Node(' ');
		p = insert(p,node);

		del(p);
	}
}
void p11(Node *h){
	Node *p = h;
	while(p){
		Node *pn = p->next;
		if(pn == NULL || pn->c == '\''){
			p = p->next;
			continue;
		}
		Node *pnn = pn->next;
		if(pnn == NULL || pnn->c != '\''){
			p = p->next;
			continue;
		}
		Node *pnnn = pnn->next;
		if(pnnn == NULL || pnnn->c != ' '){
			p = p->next;
			continue;
		}
//		cout<<"p11"<<endl;
		Node *node = new Node(' ');
		pn = insert(pn,node);
		p = pnnn;
	}
}
void p12(Node *h){
	Node *p = h;
	while(p){
		Node *pn = p->next;
		if(pn == NULL || pn->c != '\''){
			p = p->next;
			continue;
		}
		Node *pnn = pn->next;
		if(pnn == NULL || (
		   pnn->c != 's' &&
		   pnn->c != 'S' &&
		   pnn->c != 'm' &&
		   pnn->c != 'M' &&
		   pnn->c != 'd' &&
		   pnn->c != 'D')){
			p = p->next;
			continue;
		}
		Node *pnnn = pnn->next;
		if(pnnn == NULL || pnnn->c != ' '){
			p = p->next;
			continue;
		}
//		cout<<"p12 "<<p->c<<endl;
		Node *node = new Node(' ');
		p = insert(p,node);
		p = pnnn;
	}
}
void p13(Node *h, char *c){
	Node *p = h;
	while(p){
		Node *pn = p->next;
		if(pn == NULL || pn->c != c[0]){
			p = p->next;
			continue;
		}
		Node *pnn = pn->next;
		if(pnn == NULL || pnn->c != c[1]){
			p = p->next;
			continue;
		}
		Node *pnnn = pnn->next;
		if(pnnn == NULL || pnnn->c != c[2]){
			p = p->next;
			continue;
		}
		Node *pnnnn = pnnn->next;
		if(pnnnn == NULL || pnnnn->c != ' '){
			p = p->next;
			continue;
		}
//		cout<<"p13"<<endl;
		Node *node = new Node(' ');
		p = insert(p,node);
		p = pnnnn;
	}
}
void p14(Node *h, char *c, int l, int s){
	Node *p = h;
	Node *pn[15];
	while(p){
		int i;
		for(i = 0; i < l; i ++){
			if( i == 0) pn[i] = p->next;
			else pn[i] = pn[i-1]->next;

			if(pn[i] == NULL || pn[i]->c != c[i]){
				break;
			}
		}
		if(i != l) {
			p = p->next;
			continue;
		}
//		cout<<"p14"<<endl;
		Node *node = new Node(' ');
		pn[s] = insert(pn[s],node);
		p = pn[l-1];
	}
}
void p15(Node *h){
	Node *p = h;
	while(p->next){
		if((p->next)->c == ' ') del(p);
		else break;
	}
//	cout<<"p15"<<endl;
	while(p){
		if(p->c == ' '){
			while(p->next){
				if((p->next)->c == ' ') del(p);
				else break;
			}
		}
		p = p->next;
	}
}
int main(int argc, char** argv){
	string a;
	Node* h;
	char c[20];
	istream *in;
	if(argc >= 2) in = new ifstream(argv[1]);
	else in = &std::cin;

	ostream *out;
	if(argc >= 3) out = new ofstream(argv[2]);
	else out = &std::cout;

	while(getline(*in,a)){
		h = new Node();
		init_List(h,a);
		p1(h);
		p2(h);
		p3(h);
		p4(h);
		p5(h);
		p6(h);
		p7(h);
		p8(h);
		p9(h);
		p10(h);
		p11(h);
		p12(h);
		memcpy(c,"'ll",3); p13(h,c);
		memcpy(c,"'re",3); p13(h,c);
		memcpy(c,"'ve",3); p13(h,c);
		memcpy(c,"n't",3); p13(h,c);
		memcpy(c,"'LL",3); p13(h,c);
		memcpy(c,"'RE",3); p13(h,c);
		memcpy(c,"'VE",3); p13(h,c);
		memcpy(c,"N'T",3); p13(h,c);

		memcpy(c," cannot ",8); p14(h,c,8,3);
		memcpy(c," Cannot ",8); p14(h,c,8,3);
		memcpy(c," d'ye ",6); p14(h,c,6,2);
		memcpy(c," D'ye ",6); p14(h,c,6,2);
		memcpy(c," gimme ",7); p14(h,c,7,3);
		memcpy(c," Gimme ",7); p14(h,c,7,3);
		memcpy(c," gonna ",7); p14(h,c,7,3);
		memcpy(c," Gonna ",7); p14(h,c,7,3);
		memcpy(c," gotta ",7); p14(h,c,7,3);
		memcpy(c," Gotta ",7); p14(h,c,7,3);
		memcpy(c," lemme ",7); p14(h,c,7,3);
		memcpy(c," Lemme ",7); p14(h,c,7,3);
		memcpy(c," more'n ",8); p14(h,c,8,4);
		memcpy(c," More'n ",8); p14(h,c,8,4);
		memcpy(c," 'tis ",6); p14(h,c,6,2);
		memcpy(c," 'Tis ",6); p14(h,c,6,2);
		memcpy(c," 'twas ",7); p14(h,c,7,2);
		memcpy(c," 'Twas ",7); p14(h,c,7,2);
		memcpy(c," wanna ",7); p14(h,c,7,3);
		memcpy(c," Wanna ",7); p14(h,c,7,3);

		p15(h);
//		cout<<"ok"<<endl;
		Node *p = h->next;
		while(p){
			if(p->c == '(') (*out)<<"-LRB-";
			else if(p->c == ')') (*out)<<"-RRB-";
			else if(p->c == '[') (*out)<<"-LSB-";
			else if(p->c == ']') (*out)<<"-RSB-";
			else if(p->c == '{') (*out)<<"-LCB-";
			else if(p->c == '}') (*out)<<"-RCB-";
			else (*out)<<p->c;
			p = p->next;
		}
		(*out)<<endl;
		clean_List(h);
	}
	return 0;
}
