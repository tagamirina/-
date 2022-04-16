#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <chrono>

void gen_graph() ;
bool include(std::deque<int>& q, int n) ;
void depth_first_search(int start, int goal) ;
void breadth_first_search(int start, int goal) ;

const int MAX_V  = 1000 ;
std::vector<int> graph[MAX_V] ;
int parent[MAX_V] ;
int parent2[MAX_V] ;

int main(void){

    gen_graph() ;

    int start, goal ;
    start = 1 ;
    goal = 7 ;

    std::chrono::system_clock::time_point Start, Middle1, Middle2, End ;
    Start = std::chrono::system_clock::now() ;
    depth_first_search(start, goal) ;
    Middle1 = std::chrono::system_clock::now() ;
    const double time1 = std::chrono::duration_cast<std::chrono::milliseconds>( Middle1 - Start ).count() ;
    
    int n ;
    n = goal ;

    printf("%d", n ) ;
    while( n != start ){
        n = parent[n] ;
        printf(" <- %d", n ) ;
    }
    printf("\n") ;
    printf("time %lf[ms]\n\n", time1) ;
    
    n = goal ;
    
    Middle2 = std::chrono::system_clock::now() ;
    breadth_first_search(start, goal) ;
    End = std::chrono::system_clock::now() ;
    const double time2 = std::chrono::duration_cast<std::chrono::milliseconds>( End - Middle2 ).count() ;

    printf("%d", n ) ;
    while( n != start ){
        n = parent2[n] ;
        printf(" <- %d", n ) ;
    }
    printf("\n") ;
    printf("time %lf[ms]\n\n", time2) ;

    return 0 ;
}

void gen_graph(){ 
    // Initial values of child nodes
    printf("Initialization\n\n") ;
    graph[1] = std::vector<int>{ 2, 3, 4 } ;
    graph[2] = std::vector<int>{ 5, 6 } ;
    graph[3] = std::vector<int>{ 2, 4, 7 } ;
    graph[4] = std::vector<int>{ 7 } ;
    graph[5] = std::vector<int>{ 6 } ;
    graph[6] = std::vector<int>{ 3, 7 } ;
}

bool include(std::deque<int>& q, int n){
    return q.end() != std::find(q.begin(), q.end(), n);
}

void depth_first_search(int start, int goal){

    // Array element <int "start">. Declaration of the double-ended queue "open".
    // Declaration of the double-ended queue "closed".
    printf("Depth first search\n") ;
    std::deque<int> open({ start }), closed ;
    for(int i = 0;i < open.size();i++ ){
        std::cout << open[i] << std::endl ;
    }

    while( !open.empty() ){

        int n ;
        n = open.front() ;
        open.pop_front() ;
        if( n == goal ) return ;

        closed.push_back(n) ;

        std::vector<int> L ;
        L = graph[n] ;

        // Replace elements in reverse order
        std::reverse( L.begin(), L.end() ) ;

        for( int m : L ){
            if( !include(open, m) && !include(closed, m) ){
                parent[m]= n ;
                printf("m : %d, parent[%d] : %d\n", m, m, parent[m] ) ;
                open.push_front( m ) ;
            }
        }
    }
}

void breadth_first_search(int start, int goal){
    
    printf("Breadth first search\n") ;
    std::deque<int> open({ start }), closed ;

    while( !open.empty() ){
        int n ;
        n = open.front() ;
        open.pop_front() ;
        if( n == goal ) return ;

        closed.push_back( n ) ;

        for( int m : graph[n] ) {
            if( !include( open, m ) && !include( closed, m )){
                parent2[m] = n ;
                open.push_back( m ) ;
            }
        }
    }
}
