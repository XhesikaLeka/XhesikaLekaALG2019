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

struct node_hash
{
	int celes;
	string vlere;
	struct node_hash *pas;
};


class fjalor_liste 
{
	private:
		node *koka;
		string skedari;
	public:
		fjalor_liste()
		{
			this->koka=NULL;
		}

		node* krijo_node(string vlera)
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
			node * tmp = this->koka;
			while(tmp!=NULL)
			{
				cout<<tmp->vlere<<endl;
				tmp=tmp->pas;
			}
		}
		
		void shto_ne_liste(string fjala)
		{
			if(this->koka==NULL)
			{
				this->koka=new node;
				koka->vlere=fjala;
				koka->pas= NULL;
				return;
			}
			
			node * n = this->krijo_node(fjala);
			node * tmp = this->koka;
			if(!radha(koka->vlere,fjala))
			{
				if(!te_barabarta(koka->vlere,fjala))
				{
					n->pas=this->koka;
					this->koka=n;
					return;
				}
			}
			if(!te_barabarta(koka->vlere,fjala))
			{
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
		node_peme_bin *koka;
		string skedari;
	public:
		fjalor_peme_bin()
		{
			this->koka=NULL;
		}
		
		node_peme_bin* krijo_node(string vlera)
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
			this->afisho(this->koka);
		}
		
		node_peme_bin * shto_ne_peme(node_peme_bin *p,string fjala)
		{
			if(p==NULL)
				return krijo_node(fjala);

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
					this->koka = shto_ne_peme(this->koka,fjala);
					
			in.close();
		}
};
class fjalor_hash_map 
{
	private:
		node_hash * hash[26];
		string skedari;
	public:
		fjalor_hash_map()
		{
			for(int i=0;i<26;i++)
			{
				this->hash[i] = NULL;
			}
		}
		node_hash* krijo_node(string vlera)
		{
			node_hash * n = new node_hash;
			n->celes=gjej_celes(vlera);
			n->vlere=vlera;
			n->pas=NULL;
			return n;
		}
		
		void set_url(string skedari)
		{
			this->skedari= skedari;
		}
		
		int gjej_celes(string fjala)
		{
			return toupper(fjala.at(0))-65;
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
			for(int i=0;i<26;i++)
			{
				node_hash * tmp = this->hash[i];
				while(tmp!=NULL)
				{
					cout<<tmp->vlere<<endl;
					tmp=tmp->pas;
				}
			}
		}
		
		void shto_ne_hash(string fjala)
		{
			
			int i = gjej_celes(fjala);
			node_hash * n = this->krijo_node(fjala);
			if(this->hash[i]==NULL)
			{
				this->hash[i]=n;
				return;
			}
			
			if(!radha(this->hash[i]->vlere,fjala))
			{
				if(!te_barabarta(this->hash[i]->vlere,fjala))
				{
					n->pas=this->hash[i];
					this->hash[i]=n;
					return;
				}
			}
			if(!te_barabarta(this->hash[i]->vlere,fjala))
			{

				node_hash * tmp = this->hash[i];
				
				while(tmp->pas!=NULL&&radha(tmp->pas->vlere,fjala))
				{
					tmp=tmp->pas;
				}
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
				{
					shto_ne_hash(fjala);
				}
			in.close();
		}
};

int main()
{
	clock_t fillimi,fundi;
	double elapsed_secs;
	fjalor_liste F;
	fillimi = clock();
	
	F.set_url("C:/Users/Xhesika/Desktop/algoritmike/fjalet100.txt");
	F.lexo();
//	F.afisho();
	
	fundi = clock();
  	elapsed_secs = double(fundi - fillimi)/ CLOCKS_PER_SEC;
  	cout<<endl<<"FJALOR LISTE: Time of execution: "<<elapsed_secs<<" seconds. [100 fjale]"<<endl;
  	
  	fillimi = clock();
  	
	F.set_url("C:/Users/Xhesika/Desktop/algoritmike/fjalet1000.txt");
	F.lexo();
//	F.afisho();
	
	fundi = clock();
  	elapsed_secs = double(fundi - fillimi)/ CLOCKS_PER_SEC;
  	cout<<endl<<"FJALOR LISTE: Time of execution: "<<elapsed_secs<<" seconds. [1000 fjale]"<<endl;
  	
  	fillimi = clock();
  	
	F.set_url("C:/Users/Xhesika/Desktop/algoritmike/fjalet100000.txt");
	F.lexo();
//	F.afisho();
	
	fundi = clock();
  	elapsed_secs = double(fundi - fillimi)/ CLOCKS_PER_SEC;
  	cout<<endl<<"FJALOR LISTE: Time of execution: "<<elapsed_secs<<" seconds. [100000 fjale]"<<endl;
//  	
//  	merr shume kohe
////  fillimi = clock();
//
////	F.set_url("C:/Users/Xhesika/Desktop/algoritmike/fjalet1000000.txt");
////	F.lexo();
////	F.afisho();
////	
////	fundi = clock();
////  	elapsed_secs = double(fundi - fillimi)/ CLOCKS_PER_SEC;
////  	cout<<endl<<"FJALOR LISTE: Time of execution: "<<elapsed_secs<<" seconds. [1000000 fjale]"<<endl;
//  	
//  	
//  	fjalor_peme_bin FPB;
//  	
//  	fillimi = clock();
//
//
//	FPB.set_url("C:/Users/Xhesika/Desktop/algoritmike/fjalet100.txt");
//	FPB.lexo();
////	FPB.afisho();
//	
//	fundi = clock();
//  	elapsed_secs = double(fundi - fillimi)/ CLOCKS_PER_SEC;
//  	cout<<endl<<"FJALOR PEME BINARE: Time of execution: "<<elapsed_secs<<" seconds. [100 fjale]"<<endl;
//  	
//  	fillimi = clock();
//  	
//
//	FPB.set_url("C:/Users/Xhesika/Desktop/algoritmike/fjalet1000.txt");
//	FPB.lexo();
////	FPB.afisho();
//	
//	fundi = clock();
//  	elapsed_secs = double(fundi - fillimi)/ CLOCKS_PER_SEC;
//  	cout<<endl<<"FJALOR PEME BINARE: Time of execution: "<<elapsed_secs<<" seconds. [1000 fjale]"<<endl;
//  	
//  	
//  	fillimi = clock();
//  	
//
//	FPB.set_url("C:/Users/Xhesika/Desktop/algoritmike/fjalet100000.txt");
//	FPB.lexo();
////	FPB.afisho();
//	
//	fundi = clock();
//  	elapsed_secs = double(fundi - fillimi)/ CLOCKS_PER_SEC;
//  	cout<<endl<<"FJALOR PEME BINARE: Time of execution: "<<elapsed_secs<<" seconds. [100000 fjale]"<<endl;
//  	
//  	
//  	fillimi = clock();
//  	
//
//	FPB.set_url("C:/Users/Xhesika/Desktop/algoritmike/fjalet1000000.txt");
//	FPB.lexo();
////	FPB.afisho();
//	
//	fundi = clock();
//  	elapsed_secs = double(fundi - fillimi)/ CLOCKS_PER_SEC;
//  	cout<<endl<<"FJALOR PEME BINARE: Time of execution: "<<elapsed_secs<<" seconds. [1000000 fjale]"<<endl;


	fjalor_hash_map FHM;
	fillimi = clock();
  	

	FHM.set_url("C:/Users/Xhesika/Desktop/algoritmike/fjalet100.txt");
	FHM.lexo();
//	FHM.afisho();
	
	fundi = clock();
  	elapsed_secs = double(fundi - fillimi)/ CLOCKS_PER_SEC;
  	cout<<endl<<"FJALOR HASH MAP: Time of execution: "<<elapsed_secs<<" seconds. [100 fjale]"<<endl;
  	
  		fillimi = clock();
  	

	FHM.set_url("C:/Users/Xhesika/Desktop/algoritmike/fjalet1000.txt");
	FHM.lexo();
//	FHM.afisho();
	
	fundi = clock();
  	elapsed_secs = double(fundi - fillimi)/ CLOCKS_PER_SEC;
  	cout<<endl<<"FJALOR HASH MAP: Time of execution: "<<elapsed_secs<<" seconds. [1000 fjale]"<<endl;
  	
  	
  		fillimi = clock();
  	

	FHM.set_url("C:/Users/Xhesika/Desktop/algoritmike/fjalet100000.txt");
	FHM.lexo();
//	FHM.afisho();
	
	fundi = clock();
  	elapsed_secs = double(fundi - fillimi)/ CLOCKS_PER_SEC;
  	cout<<endl<<"FJALOR HASH MAP: Time of execution: "<<elapsed_secs<<" seconds. [100000 fjale]"<<endl;
  	
	return 0;
}
