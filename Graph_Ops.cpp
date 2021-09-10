#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <utility>
#include <set>
using namespace std ;


typedef pair<int,int> edge ;
typedef pair<int,int> dist ;


int min(int a, int b){

	if(a<=b){
		return a;
	}
	else{
		return b ;
	}

}


void create_adjacency_list(vector<int> *graph, int n){

	for(int i=1 ; i<=n ; i++){
		for(int j=1 ; j<=n ; j++){
			int a ;
			cin >> a ;
			if(a==1 && i!=j){
				graph[i].push_back(j) ;
			}
		}
	}

}


void create_adjacency_weighted_list(vector<edge> *graph, int n){

	for(int i=1 ; i<=n ; i++){
		for(int j=1 ; j<=n ; j++){
			int a ;
			cin >> a ;
			if(a!=999999 && i!=j){
				graph[i].push_back(make_pair(j,a)) ;
			}
		}
	}

}


void delete_graph(vector<int> *graph, int n){

	for(int i=0 ; i<=n; i++){
		for(int j=0 ; j<graph[i].size() ; j++){
			graph[i].erase(graph[i].begin()) ;
		}
	}

}


void delete_weighted_graph(vector<edge> *graph, int n){

	for(int i=0 ; i<=n; i++){
		for(int j=0 ; j<graph[i].size() ; j++){
			graph[i].erase(graph[i].begin()) ;
		}
	}

}


void breadth_first_search(vector<int> *graph, int n, int d, int s){

	if(n==0){
		cout << -1 ;
	}
	queue<int> bfs_queue ;
	int black_nodes[n+1] ;
	int dist[n+1][2] ;
	int prev_nodes[n+1] ;
	for(int i=0 ; i<=n ; i++){
		prev_nodes[i] = 0 ;
	}
	for(int i=0 ; i<=n ; i++){
		dist[i][0] = 0 ;
		dist[i][1] = 0 ;
	}
	for(int i=0 ; i<=n ; i++){
		black_nodes[i] = 0 ;
	}
	int tree_edges=0, forward_edges=0, back_edges=0, cross_edges=0 ;
	bfs_queue.push(s) ;
	black_nodes[s]=1 ;
	prev_nodes[s]=-1 ;
	dist[s][0]=0 ;
	dist[0][1]++ ;
	while(!bfs_queue.empty()){
		int node = bfs_queue.front() ;
		bfs_queue.pop() ;
		for(auto i=graph[node].begin() ; i!=graph[node].end() ; ++i){
			if(black_nodes[*i]==0){
				bfs_queue.push(*i) ;
				black_nodes[*i] = 1 ;
				dist[*i][0] = dist[node][0] + 1 ;
				dist[dist[*i][0]][1]++ ;
				prev_nodes[*i] = node ;
				tree_edges++ ;
			}
			else{
				if(d==0){
					if(prev_nodes[node]!=(*i)){
						cross_edges++ ;
					}
				}
				else{
					int temp = node ;
					int flag = 0 ;
					while(temp!=-1){
						if(prev_nodes[temp]==(*i)){
							flag=1 ;
							break ;
						}
						else{
							temp=prev_nodes[temp] ;
						}
					}
					if(flag==0){
						cross_edges++ ;
					}
					else{
						back_edges++ ;
					}
				}
			}
		}
	}
	for(int j=1 ; j<=n ; j++){
		if(j==1){
			cout << dist[j][1] ;
		}
		else{
			cout << " " << dist[j][1] ;
		}
		if(dist[j][1]==0){
			break ;
		}
	}
	if(d==0){
		cross_edges = cross_edges/2 ;
		cout << " " << tree_edges << " " << cross_edges ;
	}
	else{
		cout << " " << tree_edges << " " << back_edges << " " << forward_edges << " " << cross_edges ;
	}

}


void depth_first_search(vector<int> *graph, int n, int d, int s){

	if(n==0){
		cout << "-1" ;
		return ;
	}
	stack<int> dfs_stack ;
	int black_nodes[n+1] ;
	int times[n+1][2] ;
	for(int i=0 ; i<=n ; i++){
		black_nodes[i] = 0 ;
	}
	for(int i=0 ; i<=n ; i++){
		times[i][0] = 0 ;
		times[i][1] = 0 ;
	}
	int tree_edges=-1, forward_edges=0, back_edges=0, cross_edges=0, timestep=1 ;
	dfs_stack.push(s) ;
	while(!dfs_stack.empty()){
		int node = dfs_stack.top() ;
		dfs_stack.pop() ;
		if(black_nodes[node]==0){
			black_nodes[node]=1 ;
			dfs_stack.push(node) ;
			times[node][0]=timestep ;
			timestep++ ;
			for(auto i=graph[node].rbegin() ; i!=graph[node].rend() ; i++){
				if(black_nodes[*i]==0){
					dfs_stack.push(*i) ;
				}
				else{
					if(times[*i][1]==0){
						back_edges++ ;
					}
					else{
						if(d==1){
							cross_edges++ ;
						}
					}
				}
			}
		}
		else{
			if(times[node][1]==0){
				times[node][1]=timestep ;
				timestep++ ;
				tree_edges++ ;
			}
			else{
				if(d==1){
					forward_edges++ ;
				}
			}
		}
	}
	for(int j=1 ; j<=n ; j++){
		if(black_nodes[j]==0){
			forward_edges-- ;
			dfs_stack.push(j) ;
			while(!dfs_stack.empty()){
				int node = dfs_stack.top() ;
				dfs_stack.pop() ;
				if(black_nodes[node]==0){
					black_nodes[node]=1 ;
					dfs_stack.push(node) ;
					times[node][0]=timestep ;
					timestep++ ;
					for(auto i=graph[node].rbegin() ; i!=graph[node].rend() ; i++){
						if(black_nodes[*i]==0){
							dfs_stack.push(*i) ;
						}
						else{
							if(times[*i][1]==0 && times[*i][0]<times[node][0]){
								back_edges++ ;
							}
							else{
								if(d==1){
									cross_edges++ ;
								}
							}
						}
					}
				}
				else{
					if(times[node][1]==0){
						times[node][1]=timestep ;
						timestep++ ;
						tree_edges++ ;
					}
					else{
						if(d==1){
							forward_edges++ ;
						}
					}
				}
			}
		}
	}
	cout << times[s][1] ;
	if(d==0){
		back_edges = back_edges - tree_edges ;
		cout << " " << tree_edges << " " << back_edges ;
	}
	else{
		cout << " " << tree_edges << " " << back_edges << " " << forward_edges << " " << cross_edges ;
	}

}


void topological_sort(vector<int> *graph, int n){

	if(n==0){
		cout << "-1" ;
		return ;
	}
	vector<int> final_array ;
	int in_degree[n+1][2] ;
	for(int i=0 ; i<=n ; i++){
		in_degree[i][0]=0 ;
		in_degree[i][1]=0 ;
	}
	for(int i=1 ; i<=n ; i++){
		for(auto j=graph[i].begin() ; j!=graph[i].end() ; ++j){
			in_degree[*j][0]++ ;
		}
	}
	queue<int> top_queue ;
	int break_condition=0, itr=0 ;
	while(break_condition!=n){
		int j=0 ;
		for(int i=1 ; i<=n ; i++){
			if(in_degree[i][0]==0 && in_degree[i][1]==0){
				top_queue.push(i) ;
				in_degree[i][1]=1 ;
				break_condition++ ;
				j++ ;
			}
		}
		if(j==0){
			cout << "-1" ;
			return ;
		}
		for(int k=0 ; k<j ; k++){
			int node=top_queue.front() ;
			top_queue.pop() ;
			final_array.push_back(node) ;
			for(auto i=graph[node].begin() ; i!=graph[node].end() ; ++i){
				in_degree[*i][0]-- ;
			}
		}
	}
	for(auto i=final_array.begin() ; i!=final_array.end() ; ++i){
		if(itr==0){
			cout << *i ;
			itr++ ;
		}
		else{
			cout << " " << *i ;
		}
	}

}


void dijkstra(vector<edge> *graph, int n, int d, int s){

	if(n==0){
		cout << "-1" ;
		return ;
	}
	set<dist> dist_holder ;
	set<dist>::iterator smallest_itr ; 
	int completed[n+1][2] ;
	for(int i=1 ; i<=n ; i++){
		if(i==s){
			dist_holder.insert(make_pair(0,i)) ;
			completed[i][0]=0 ;
			completed[i][1]=0 ;
		}
		else{
			dist_holder.insert(make_pair(999999,i)) ;
			completed[i][0]=0 ;
			completed[i][1]=999999 ;
		}
	}
	for(int i=1 ; i<=n ; i++){
		smallest_itr = dist_holder.begin() ;
		int x=smallest_itr->first, y=smallest_itr->second ;
		if(x==999999){
			break ;
		}
		completed[y][0]=1 ;
		for(auto j=graph[y].begin() ; j!=graph[y].end() ; ++j){
			int a=j->first, w=j->second ;
			if(w<0){
				cout << "-1" ;
				return ;
			}
			if(completed[a][0]==0 && x+w<completed[a][1]){
				dist_holder.erase({completed[a][1],a}) ;
				completed[a][1]=x+w ;
				dist_holder.insert(make_pair(completed[a][1],a)) ;
			}
		}
		dist_holder.erase({x,y}) ;
	}
	for(int i=1 ; i<=n ; i++){
		if(i==1){
			cout << completed[i][1] ;
		}
		else{
			cout << " " << completed[i][1] ;
		}
	}

}


void bellman_ford(vector<edge> *graph, int n, int d, int s){

	if(n==0){
		cout << "-1" ;
		return ;
	}
	int dist_array[n+1] ;
	for(int i=0 ; i<=n ; i++){
		if(i==s){
			dist_array[i]=0 ;
		}
		else{
			dist_array[i]=999999 ;
		}
	}
	int total_checks=0, total_relaxes=0 ;
	for(int i=1 ; i<=n ; i++){
		int relaxes_this_cycle=0 ;
		for(int u=1 ; u<=n ; u++){
			for(auto k=graph[u].begin() ; k!=graph[u].end() ; ++k){
				int v=k->first, w=k->second ;
				if(dist_array[u]==999999 && u<v){
					total_checks++ ;
					continue ;
				}
				if(d==0 && w<0){
					cout << "-1" ;
					return ;
				}
				if(u>v){
					continue ;
				}
				if(dist_array[u]+w<dist_array[v]){
					dist_array[v]=dist_array[u]+w ;
					total_relaxes++ ;
					relaxes_this_cycle++ ;
				}
				total_checks++ ;
			}
		}
		for(int u=n ; u>=1 ; u--){
			for(auto k=graph[u].rbegin() ; k!=graph[u].rend() ; k++){
				int v=k->first, w=k->second ;
				if(dist_array[u]==999999 && u>v){
					total_checks++ ;
					continue ;
				}
				if(d==0 && w<0){
					cout << "-1" ;
					return ;
				}
				if(u<v){
					continue ;
				}
				if(dist_array[u]+w<dist_array[v]){
					dist_array[v]=dist_array[u]+w ;
					total_relaxes++ ;
					relaxes_this_cycle++ ;
				}
				total_checks++ ;
			}
		}
		if(relaxes_this_cycle==0){
			break ;
		}
		if(relaxes_this_cycle>0 && i==n){
			cout << "-1" ;
			return ;
		}
	}
	for(int i=1 ; i<=n ; i++){
		if(i==1){
			cout << dist_array[i] ;
		}
		else{
			cout << " " << dist_array[i] ;
		}
	}
	cout << " " << total_checks << " " << total_relaxes ;

}


void graph_ops(){

	int query ;
	cin >> query ;

	if(query==3){

		int n ;
		cin >> n ;
		vector<int> *graph = new vector<int>[n+1] ;
		create_adjacency_list(graph,n) ;
		topological_sort(graph,n) ;
		delete_graph(graph,n) ;

	}
	else{

		int n, d, s ;
		cin >> n >> d >> s ;

		switch(query){

			case 1 :
			{
				vector<int> *graph = new vector<int>[n+1] ;
				create_adjacency_list(graph,n) ;
				breadth_first_search(graph,n,d,s) ;
				delete_graph(graph,n) ;
				break ;
			}
			case 2 :
			{
				vector<int> *graph = new vector<int>[n+1] ;
				create_adjacency_list(graph,n) ;
				depth_first_search(graph,n,d,s) ;
				delete_graph(graph,n) ;
				break ;
			}
			case 4 :
			{
				vector<edge> *graph = new vector<edge>[n+1] ;
				create_adjacency_weighted_list(graph,n) ;
				dijkstra(graph,n,d,s) ;
				delete_weighted_graph(graph,n) ;
				break ;
			}
			case 5 :
			{
				vector<edge> *graph = new vector<edge>[n+1] ;
				create_adjacency_weighted_list(graph,n) ;
				bellman_ford(graph,n,d,s) ;
				delete_weighted_graph(graph,n) ;
				break ;
			}
			default :
			{
				cout << "-1" ;
				break ;
			}

		}

	}

}


int main(){

	int t ;
	cin >> t ;

	while(t>0){

		graph_ops() ;

		if(t!=1){
			cout << endl ;
		}

		t-- ;

	}

	return 0 ;

}



/*



Testcases that work for my code (all my own) :

5
4
9 1 1
0 4 999999 8 999999 999999 999999 8 6
4 0 8 999999 999999 999999 999999 11 999999
10 8 0 7 999999 4 999999 999999 2 
999999 999999 7 0 9 14 999999 6 999999
4 999999 3 9 0 10 999999 999999 999999
999999 999999 4 14 10 0 2 999999 999999
999999 999999 999999 999999 999999 2 0 1 6
8 11 999999 999999 7 999999 1 0 7
999999 999999 2 999999 999999 999999 6 7 0
3
6
0 0 0 0 1 0
1 0 0 0 0 0
0 1 0 0 0 1
0 1 0 0 0 0
1 1 0 0 0 1
1 0 1 0 0 0
2
10 1 1
0 1 1 0 0 0 0 0 0 0
0 0 1 1 0 0 0 0 0 0
0 0 0 1 0 0 0 0 0 0
0 0 0 0 1 1 0 0 0 0
1 0 0 0 0 1 0 0 0 0
1 0 0 0 1 0 1 1 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 1 1
0 0 0 0 0 0 1 0 0 0
0 0 0 0 0 0 1 0 0 0
1
10 1 1
0 1 1 0 0 0 0 0 0 0
0 0 1 1 0 0 0 0 0 0
0 0 0 1 0 0 0 0 0 0
0 0 0 0 1 1 0 0 0 0
1 0 0 0 0 1 0 0 0 0
1 0 0 0 1 0 1 1 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 1 1
0 0 0 0 0 0 1 0 0 0
0 0 0 0 0 0 1 0 0 0
5
4 1 2
0 -1 2 999999
999999 0 4 999999
999999 999999 0 -2
999999 3 999999 0


Output :

0 4 8 8 15 11 9 8 6
-1
20 9 3 3 2
2 1 2 2 2 0 9 2 0 6
999999 0 4 2 10 2



*/