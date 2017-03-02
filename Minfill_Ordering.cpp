#include <algorithm> 
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <queue>
#include <limits>
#include <algorithm> 
#include <stdlib.h>
#include <utility> // pair
#include <sys/time.h>
#include <signal.h>
#define DEBUG 0
using namespace std;
class Set{

	public :

	static set<int> intersect (set<int> s1,set<int> s2)
	{
		set<int> s3,smallSet,largeSet;
		set<int>::iterator sit;
		
		if (s1.size()<s2.size())
		   {
			   smallSet=s1;
			   largeSet=s2;
		   }
		   else
		   {
			   smallSet=s2;
			   largeSet=s1;
		   }
		for (sit=smallSet.begin(); sit!=smallSet.end(); ++sit)  
		     if(largeSet.find(*sit)!=largeSet.end()) 
		        s3.insert(*sit);
		 
		 return s3;  
		
	}
	static set<int> setMinus(set<int> setA,set<int> setB){
		set<int> returnSet;
		set<int>::iterator it1,it2,	t1=setB.begin(), t2=setB.end();
		for(it1 = setA.begin(), it2 = setA.end() ; it1!=it2 ; it1++){
			if(setB.find(*it1)==setB.end()){
				returnSet.insert(*it1);
			}		
		}
		return returnSet;
	}
        static int isSubset (set<int> s1,set<int> s2)
    {
	if(s1.size() > s2.size()) return -1;
	
	unsigned int cnt=0;
	
	set<int> :: iterator sit;
	for(sit=s1.begin();sit!=s1.end();sit++)
	{
		if(s2.find(*sit)==s2.end())
		return -1;      //s1 is not subset
		else cnt++;
	}
	if(s1.size()==s2.size())
	{
	  if(s1.size()==cnt) return 0; //both sets equal
	  else return 1; //s1 is proper subset
	}  
	else return 1; //s1 is proper subset
     }
	static void printSet(set <int> s){
		set<int>::iterator it,end;
		cout<< "NB set: " ;
		for(it = s.begin(), end = s.end() ; it != end ; it++){
			cout<< *it << " ";
		}
		cout << endl;
	}
};
class Graph
{
	public:
		unsigned int n;
		unsigned int m;
		
		unsigned int max_clique_size;
		std::map<int, set <int>  > retMapOfSet;
		vector <int> *adjList;
        set <int>  nodes;
        set < set <int> > returnSoS;
        bool cycle_found;
        std::map<int, int> vertexColour;
	int no_of_components;
        Graph()
        {
		}
        Graph(int n , vector <int> * a,set <int>  nodes)
        {	
			
			this->n = n;
			this->nodes=nodes;
			max_clique_size=1;	
			adjList = new vector <int> [n+1];
            cycle_found=false;
			for(int i=1; i <= n; i++)
                         {
                         
                          adjList[i]=a[i];
                         }
		}
		void printAdjList(){
			
			for(unsigned int i=1; i <= n; i++){
				 cout  <<i << "\t#";
				for( std::vector<int>::iterator it=adjList[i].begin(), end =adjList[i].end(); it!=end; it++){
					 cout << " "<< *it;
				}
				cout << endl;
                                 
			}
                        
                  }
		
		Graph complete_clique(Graph g,set<int> k,set<pair<int,int> >& fill_edges)
       {
	     set<int> :: iterator sit1,sit2;
	     for(sit1=k.begin();sit1!=k.end();sit1++)
	         for(sit2=sit1;sit2!=k.end();sit2++)
	         if(*sit1!=*sit2) 
	         {
					 std::vector<int>::iterator tmp_it1;
			         tmp_it1 = find (g.adjList[*sit1].begin(), g.adjList[*sit1].end(),  *sit2);
			         
			         if( tmp_it1==g.adjList[*sit1].end() )
			         {
				     g.adjList[*sit1].push_back(*sit2);
				     g.adjList[*sit2].push_back(*sit1);
				     if(DEBUG) cout<<"Edge Added"<<*sit1<<" "<<*sit2<<"\n";
				     pair<int,int> curr_edge=make_pair(*sit1,*sit2);
				     fill_edges.insert(curr_edge);
			         }
			}
	     return g;
       }
       
       
		
		 pair <Graph , set<pair<int,int> > >  find_simplicial_order(int ordering[])
		{
			Graph chordal_graph(n,adjList,nodes);
			pair <bool , vector <int> > op;
			set<pair<int,int> > fill_edges;
		do
		{
			for( int i=n-3;i>=0;i--)
			{   
				if(DEBUG) cout<<"Current vertex "<<ordering[i]<<"\n";
				set<int> higher_adj_nodes;
				for(unsigned int j=i+1;j<n;j++)
				{
				   //cout<<"ordering[j] "<<ordering[j]<<"\n";
				   if(find(chordal_graph.adjList[ordering[i]].begin(),chordal_graph.adjList[ordering[i]].end(),
					ordering[j])!=chordal_graph.adjList[ordering[i]].end())
				      higher_adj_nodes.insert(ordering[j]);
			    }
				//cout<<"higher_adj_nodes.size() "<<higher_adj_nodes.size()<<"\n";
				if(higher_adj_nodes.size()>1)
				   {
				     //if(higher_adj_nodes.size()>max_clique_size)  max_clique_size=higher_adj_nodes.size();   				     
				     chordal_graph= complete_clique(chordal_graph,higher_adj_nodes,fill_edges); 
				     //chordal_graph.max_clique_size=chordal_graph.find_max_clique_size(ordering,i,higher_adj_nodes);  
			       }
			       //if(higher_adj_nodes.size()==1 && chordal_graph.max_clique_size <2) chordal_graph.max_clique_size=2;
				if(DEBUG) cout<<"max_clique_size "<<chordal_graph.max_clique_size<<"\n";
				
			}
			op=chordal_graph.isChordal();
	   }while(!op.first);
	   pair <Graph , set<pair<int,int> > >  retPair;
	   //vector<int> vec=op.second;
	   retPair = make_pair (chordal_graph,fill_edges);
			return retPair;
		}
		
			void DFS()
{
	std::set<int>::iterator it,end;
	
	for (it=nodes.begin(),end=nodes.end();it!=end;it++)
			vertexColour[*it]=0;
		if(DEBUG) cout<<"DFS Starts"<<endl;	
		unsigned int i=0;
		std::map<int, int>::iterator iter;
    for (it=nodes.begin(),end=nodes.end();it!=end;it++)	
    {
         iter=vertexColour.find(*it);
         if(DEBUG) cout<<"vertex"<<*it<<" vcolor "<<iter->second<<endl;
         if( iter->second==0)
         {
             i=i+1;
             if(DEBUG) cout<<"Component  "<<i<<endl;
             DFS_VISIT(*it,i);
	}
	no_of_components=i; 
    }
                          
}
void DFS_VISIT(int v,unsigned int setno)
{
	std::vector<int>::iterator it,end;
	std::map<int, set<int> >::iterator iter;
	set<int> currComponent;
	if(DEBUG) cout<<v<<endl;
	if(DEBUG) cout<<"Map size="<<retMapOfSet.size()<<"  setno="<<setno<<endl;
	if (retMapOfSet.size()==setno)
	{
		iter=retMapOfSet.find(setno);
		currComponent=iter->second;
	}
		currComponent.insert(v);
		if(DEBUG) cout<<"currComponent size="<<currComponent.size()<<endl;
		retMapOfSet[setno]=currComponent;
	
	vertexColour.erase(v);
	vertexColour[v]=1;
	//cout<<"Vertex Color changed:"<<v<<"  "<<vertexColour[v]<<"\n";	
	std::map<int, int>::iterator i;
	for (it=adjList[v].begin(),end=adjList[v].end();it!=end;it++)
                                  {
                                  	i=vertexColour.find(*it);
                                  	if(i->second==2)
									{
									 //cout<<"Cycle Detected: "<<v<<"  "<<i->first<<"\n"	;	
									 cycle_found=true;
								    }
                                  	if(i->second==0)
									  DFS_VISIT(*it,setno); 
									
								  }
	vertexColour.erase(v);
	vertexColour[v]=2;	
	//cout<<"Vertex Color changed:"<<v<<"  "<<vertexColour[v]<<"\n";					  
}	



vector<int> lex_bfs()
{
	if(DEBUG) cout<<"inside lex_bfs\n";
	vector<set<int> > Q;
	//int node_2_Q[n];
	Q.push_back(nodes);
	int setno=0;
	/*for(unsigned int j=0;j<n;j++)
	node_2_Q[j]=setno;*/
	
	map<int,int> sigma,siginv;
	std::vector<int>::iterator it,end;
	
	for(int i=n;i>0;i--)
	{
		if(DEBUG) cout<<"i="<<i<<"\n";
		while(Q.back().size()==0) Q.pop_back();
		set<int> curr_set=Q.back();
		int v=*(curr_set.begin());
		if(DEBUG) cout<<"v="<<v<<"\n";
		//(*(Q.end())).erase(curr_set.begin());
		curr_set.erase(v);
		Q.pop_back();
		Q.push_back(curr_set);
		sigma[i]=v;
		siginv[v]=i;
		if(DEBUG) cout<<"Debug 1\n";
		set<int> curr_adj_ver;
		for (it=adjList[v].begin(),end=adjList[v].end();it!=end;it++)
		{
			if(DEBUG) cout<<"adj v="<<*it<<"\n";
			if(siginv.find(*it)==siginv.end())
				curr_adj_ver.insert(*it);
		}
		unsigned int no_adj_vertices=curr_adj_ver.size();
		 if(DEBUG) cout<<"no_adj_vertices="<<no_adj_vertices<<"\n";
		vector<set<int> > Q1;
		vector<set<int> > ::iterator Q_iter;
		Q1.assign(Q.begin(),Q.end());
		 if(DEBUG) cout<<"Q1.size()="<<Q1.size()<<"\n";
		 Q_iter=Q.begin();
		 int k=0;
		for(unsigned int j=0;j<Q1.size() && no_adj_vertices>0;j++)
		{
			 if(DEBUG) cout<<"j="<<j<<"\n";
			set<int> s=Set::intersect(Q1.at(j),curr_adj_ver);
			if(s.size()!=0)
			{				
				if(k+j+1==Q.size())	 Q.push_back(s);
				else
				{
				//Q_iter++;
					
			    Q.insert(Q.begin()+k+j+1,s);
			    	
				//Q_iter--;
					
			    }		
				setno++;
				set<int> ::iterator iter;
				for(iter=s.begin();iter!=s.end();iter++)
				{
				   //node_2_Q[*iter]=setno;
				   Q.at(j+k).erase(*iter);
				   no_adj_vertices--;
			   }
			   k++;
			}
			//else Q_iter++;
		}
	}
	vector<int> ordering;
	for(unsigned int i=1;i<=n;i++)
	ordering.push_back(sigma.at(i));
	
	return ordering;
}

pair <bool , vector <int> > isChordal()
{
	if(DEBUG) cout<<"inside isChordal\n";
	vector<int> vec=lex_bfs();
	if(DEBUG) 
	{
	for(unsigned int k=0;k<n;k++)
	cout<<vec.at(k)<<"\n";
    }
	map<int,vector<int> > A;
	map<int,int> siginv;
	for(unsigned int i=1;i<=n;i++)
	siginv[vec.at(i-1)]=i;
    std::vector<int>::iterator it,end;
    pair <bool , vector <int> >  retPair;
	for(unsigned int i=0;i<n-1;i++)
	{
		int v=vec.at(i);
		set<int> X;
		for (it=adjList[v].begin(),end=adjList[v].end();it!=end;it++)
		if(siginv[v]<siginv[*it])
		X.insert(*it);
		set<int> :: iterator sit;
		if(X.size()!=0)
		{
			
			int min=numeric_limits<int>::max();
			int u;
			for(sit=X.begin();sit!=X.end();sit++)
			{
				if(siginv[*sit]<min)
				{
				min=siginv[*sit];
				u=*sit;
			    }
			}
			X.erase(u);
			if(A.find(u)==A.end())
				A[u].assign(X.begin(),X.end());
			else
			    A[u].insert(A[u].begin(),X.begin(),X.end());
		}
		
		set<int> s1,s2,s3;
		s1.insert(A[v].begin(),A[v].end());
		s2.insert(adjList[v].begin(),adjList[v].end());
		for(sit=s1.begin();sit!=s1.end();sit++)
		   if(s2.find(*sit)==s2.end())
		   s3.insert(*sit);
		if(s3.size()!=0)
		{if(DEBUG) cout<<"GRaph Not yet Chordal\n";
			retPair = make_pair (false,vec);
			return retPair;}
	}
	if(DEBUG) cout<<"Graph is now Chordal\n";
	retPair = make_pair (true,vec);
	return retPair;
}
	
};


int main()
{
	int total_nodes, total_edges;
	int n,m;
	
	string lineStr ;
	string node1, node2;
	//signal(SIGTERM, handleSignal);
	//signal(SIGINT, handleSignal);
	unordered_map<string,vector<string> > input;
	
	while(getline(std::cin, lineStr)){		
	// To ignore comments
		if(lineStr[0]=='#')
			continue;			
			
		istringstream edges(lineStr);
		edges >> node1;
		edges >> node2;
		
		if(DEBUG) cout << node1 << " " << node2 << endl;
		vector<string> v1,v2;
		if (input.find(node1)!=input.end())
			v1=input[node1];
		v1.push_back(node2);
		input[node1]=v1;

		if (input.find(node2)!=input.end())
			v2=input[node2];
		v2.push_back(node1);
		input[node2]=v2;		
	}
	n=input.size();
	unordered_map<string,int> m1;
	unordered_map<int,string> m2;

	int i=1;
	unordered_map<string,vector<string> > ::iterator miter;
	for(miter=input.begin();miter!=input.end();miter++)
		{
		string curr_v=miter->first;
		m1[curr_v]=i;
		m2[i]=curr_v;
		i++;
		}
	vector<int> adjList[n+1];
	
	if(DEBUG)
	{
	cout<<"m1\n";
	unordered_map<string,int> ::iterator m1_it;
	
	for(m1_it=m1.begin();m1_it!=m1.end();m1_it++)
		cout<<(m1_it->first)<<" is now "<<(m1_it->second)<<endl;
	
	}
		
	for(miter=input.begin();miter!=input.end();miter++)
	{
		string curr_v=miter->first;
		int curr_intv=m1[curr_v];
		vector<string> curr_adj=miter->second;
		vector<int> curr_int_adj;
		vector<string> ::iterator vit;
		for(vit=curr_adj.begin();vit!=curr_adj.end();vit++)
			curr_int_adj.push_back(m1[*vit]);
		adjList[curr_intv]=curr_int_adj	;	
	}	
	set<int> input_nodes;
	for(int i=1;i<=n;i++) input_nodes.insert(i);
	
	Graph g(n,adjList,input_nodes);
	if(DEBUG) 
	{
	cout<<"Adjacency List\n";
	g.printAdjList();
	}
	g.DFS();
	//If graph is tree, no fill edge is required
	if(!g.cycle_found) return 0;
	int ordering[n];
	pair <Graph , set<pair<int,int> > > tw_simplicial_order_pair;
	set<pair<int,int> > optimal_fill_edges;
	unsigned int minfillsize=numeric_limits<int>::max();
	for(int i=0;i<n;i++) ordering[i]=i+1;
	for (int i=0;i<5000;i++)
	{
		if(DEBUG) 
		{
		cout<<"Ordering"<<endl;
		for(int i=0;i<n;i++)
	    	cout<<ordering[i]<<" ";
	    	cout<<"\n";	
	    	}
		tw_simplicial_order_pair=g.find_simplicial_order(ordering);
				
		if(tw_simplicial_order_pair.second.size()<minfillsize) 
		{
		minfillsize=tw_simplicial_order_pair.second.size();
		optimal_fill_edges=tw_simplicial_order_pair.second;	
		}
		int num1=rand()%n;
		int num2;
		while(1)
		{
			num2=rand()%n;
			if(num1!=num2) break;
		}
		int temp=ordering[num1];
		ordering[num1]=ordering[num2];
		ordering[num2]=temp;
				
	}
	if(DEBUG)
	cout<<"Number of edges="<<optimal_fill_edges.size()<<endl;
	set<pair<int,int> > ::iterator spit;
		for(spit=optimal_fill_edges.begin();spit!=optimal_fill_edges.end();spit++)
		{
			pair<int,int> curr_fedge=*spit;
			cout<<m2[curr_fedge.first]<<" "<<m2[curr_fedge.second]<<endl;
		}

	return 0;
}
