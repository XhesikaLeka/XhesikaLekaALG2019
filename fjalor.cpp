#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
using namespace std;
  

struct node
{
	string vlere;
	struct node *pas;
};

struct node_peme_bin
{
	string vlere;
	struct node_peme_bin * majtas;
	struct node_peme_bin * djathtas;
};


class fjalor_liste 
{
	private:
		node *head;
		string skedari;
	public:
		fjalor_liste()
		{
			this->head=NULL;
		}

		node* create_node(string vlera)
		{
			node * n = new node;
			n->vlere=vlera;
			n->pas=NULL;
			return n;
		}
		
		void set_url(string skedari)
		{
			this->skedari= skedari;
		}
		
		bool radha(string nyja, string fjala)
		{
			return nyja<fjala;
		}
		
		bool te_barabarta(string nyja, string fjala)
		{
			return nyja==fjala;
		}
		
		void afisho()
		{
			node * tmp = this->head;
			while(tmp!=NULL)
			{
				cout<<tmp->vlere<<endl;
				tmp=tmp->pas;
			}
		}
		
		void shto_ne_liste(string fjala)
		{
			if(this->head==NULL)
			{
				this->head=new node;
				head->vlere=fjala;
				head->pas= NULL;
				return;
			}
			
			node * n = this->create_node(fjala);
			node * tmp = this->head;
			if(!radha(head->vlere,fjala))
			{
				if(!te_barabarta(head->vlere,fjala))
				{
					n->pas=this->head;
					this->head=n;
					return;
				}
			}
			while(tmp->pas!=NULL&&radha(tmp->pas->vlere,fjala))
				tmp=tmp->pas;
			if(tmp->pas==NULL)
				tmp->pas = n;
			else
			{
				if(!te_barabarta(tmp->pas->vlere,fjala))
				{
					n->pas = tmp->pas;
					tmp->pas = n;
				}
			}
		}
		void lexo()
		{
			string fjala;
			ifstream in;
			in.open( this->skedari.c_str() );
				if (!in) 
				{
				    cerr << "Gabim ne hapjen e skedarit: "<<skedari;
				    exit(1);
				}
				while(!in.eof()&&in >> fjala)
					shto_ne_liste(fjala);
			in.close();
		}
};
class fjalor_peme_bin
{
	private:
		node_peme_bin *head;
		string skedari;
	public:
		fjalor_peme_bin()
		{
			this->head=NULL;
		}
		
		node_peme_bin* create_node(string vlera)
		{
			node_peme_bin * n = new node_peme_bin;
			n->vlere=vlera;
			n->majtas=NULL;
			n->djathtas=NULL;
			return n;
		}
		
		void set_url(string skedari)
		{
			this->skedari= skedari;
		}
		
		bool radha(string nyja, string fjala)
		{
			return nyja<fjala;
		}
		
		bool te_barabarta(string nyja, string fjala)
		{
			return nyja==fjala;
		}
		
		void afisho(node_peme_bin *p)
		{
			if(p!=NULL)
			{
				afisho(p->majtas);
				cout<<p->vlere<<endl;
				afisho(p->djathtas);
			}
		}
		void afisho()
		{
			this->afisho(this->head);
		}
		
		node_peme_bin * shto_ne_peme(node_peme_bin *p,string fjala)
		{
			if(p==NULL)
				return create_node(fjala);

			if(radha(p->vlere,fjala))
				p->djathtas = shto_ne_peme(p->djathtas, fjala);
			else if(!te_barabarta(p->vlere, fjala))
				p->majtas = shto_ne_peme(p->majtas, fjala);
			return p;
		}
		void lexo()
		{
			string fjala;
			ifstream in;
			in.open( this->skedari.c_str() );
				if (!in) 
				{
				    cerr << "Gabim ne hapjen e skedarit: "<<skedari;
				    exit(1);
				}
				while(!in.eof()&&in >> fjala)
					this->head = shto_ne_peme(this->head,fjala);
					
			in.close();
		}
};
// void test()

int main()
{
	clock_t fillimi,perfundimi;
	double elapsed_secs;
	fillimi = clock();
	fjalor_liste F;
	F.set_url("C:/Users/Xhesika/Desktop/algoritmike/fjalet100.txt");
	F.lexo();
//	F.afisho();
	
	perfundimi = clock();
  	elapsed_secs = double(perfundimi - fillimi)/ CLOCKS_PER_SEC;
  	cout<<endl<<"FJALOR LISTE: Time of execution: "<<elapsed_secs<<" seconds. [100 fjale]"<<endl;
  	
  	fillimi = clock();
	fjalor_liste F1;
	F1.set_url("C:/Users/Xhesika/Desktop/algoritmike/fjalet1000.txt");
	F1.lexo();
//	F1.afisho();
	
	perfundimi = clock();
  	elapsed_secs = double(perfundimi - fillimi)/ CLOCKS_PER_SEC;
  	cout<<endl<<"FJALOR LISTE: Time of execution: "<<elapsed_secs<<" seconds. [1000 fjale]"<<endl;
  	
  	fillimi = clock();
	fjalor_liste F2;
	F2.set_url("C:/Users/Xhesika/Desktop/algoritmike/fjalet100000.txt");
	F2.lexo();
//	F2.afisho();
	
	perfundimi = clock();
  	elapsed_secs = double(perfundimi - fillimi)/ CLOCKS_PER_SEC;
  	cout<<endl<<"FJALOR LISTE: Time of execution: "<<elapsed_secs<<" seconds. [100000 fjale]"<<endl;
  	
  	//kerkon shume kohe
//  fillimi = clock();
//	fjalor_liste F3;
//	F3.set_url("C:/Users/Xhesika/Desktop/algoritmike/fjalet1000000.txt");
//	F3.lexo();
//	F3.afisho();
//	
//	perfundimi = clock();
//  	elapsed_secs = double(perfundimi - fillimi)/ CLOCKS_PER_SEC;
//  	cout<<endl<<"FJALOR LISTE: Time of execution: "<<elapsed_secs<<" seconds. [1000000 fjale]"<<endl;
  	
  	fillimi = clock();
	fjalor_peme_bin FPB;

	FPB.set_url("C:/Users/Xhesika/Desktop/algoritmike/fjalet100.txt");
	FPB.lexo();
//	FPB.afisho();
	
	perfundimi = clock();
  	elapsed_secs = double(perfundimi - fillimi)/ CLOCKS_PER_SEC;
  	cout<<endl<<"FJALOR PEME BINARE: Time of execution: "<<elapsed_secs<<" seconds. [100 fjale]"<<endl;
  	
  	fillimi = clock();
	fjalor_peme_bin FPB1;

	FPB1.set_url("C:/Users/Xhesika/Desktop/algoritmike/fjalet1000.txt");
	FPB1.lexo();
//	FPB1.afisho();
	
	perfundimi = clock();
  	elapsed_secs = double(perfundimi - fillimi)/ CLOCKS_PER_SEC;
  	cout<<endl<<"FJALOR PEME BINARE: Time of execution: "<<elapsed_secs<<" seconds. [1000 fjale]"<<endl;
  	
  	
  	fillimi = clock();
	fjalor_peme_bin FPB2;

	FPB2.set_url("C:/Users/Xhesika/Desktop/algoritmike/fjalet100000.txt");
	FPB2.lexo();
//	FPB2.afisho();
	
	perfundimi = clock();
  	elapsed_secs = double(perfundimi - fillimi)/ CLOCKS_PER_SEC;
  	cout<<endl<<"FJALOR PEME BINARE: Time of execution: "<<elapsed_secs<<" seconds. [100000 fjale]"<<endl;
  	
  	
  	fillimi = clock();
	fjalor_peme_bin FPB3;

	FPB3.set_url("C:/Users/Xhesika/Desktop/algoritmike/fjalet1000000.txt");
	FPB3.lexo();
//	FPB3.afisho();
	
	perfundimi = clock();
  	elapsed_secs = double(perfundimi - fillimi)/ CLOCKS_PER_SEC;
  	cout<<endl<<"FJALOR PEME BINARE: Time of execution: "<<elapsed_secs<<" seconds. [1000000 fjale]"<<endl;

  	
	return 0;
}
