#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
#include <typeinfo>
using namespace std;

/* Graph definition region*/
template <class T>
class Vertex{
	private:
		shared_ptr<T> vertex;
	public:
		Vertex() {this(nullptr);}
		Vertex(shared_ptr<T> _vertex): vertex(_vertex){}
		shared_ptr<T> getVertex(){
			return vertex;
		}
		void setVertex(shared_ptr<T> _vertex){
			vertex = _vertex;
		}
};

template <class T>
class Edge{
	private:
		shared_ptr<Vertex<T>> srcNode;
		shared_ptr<Vertex<T>> destNode;
		long long int cost;
	public:
		Edge(shared_ptr<Vertex<T>> _srcNode, shared_ptr<Vertex<T>> _destNode, long long int _cost): srcNode(_srcNode), destNode(_destNode), cost(_cost){
		}
		shared_ptr<Vertex<T>> getSrcVertex(){
			return srcNode;
		}
		shared_ptr<Vertex<T>> getDestVertex(){
			return destNode;
		}
		long long int getCost(){
			return cost;
		}
		void changeSrcVertex(shared_ptr<Vertex<T>> _vertex){
			srcNode = _vertex;
		}
		void changeDestVertex(shared_ptr<Vertex<T>> _vertex){
			destNode = _vertex;
		}
		void modifyCost(long long int _cost){
			cost = _cost;
		}
};

template <class T>
class VertexEdges{
	public:
		shared_ptr<Vertex<T>> vertex;
		shared_ptr<vector<shared_ptr<Edge<T>>>> edges;
		VertexEdges(shared_ptr<Vertex<T>> _vertex): vertex(_vertex){
			edges = make_shared<vector<shared_ptr<Edge<T>>>>();
		}
		void add(shared_ptr<Edge<T>> _edge){
			edges->push_back(_edge);
		}
};

template <class T>
class Graph{
	private:
		int noVertices;
	public:
		unique_ptr<vector<shared_ptr<VertexEdges<T>>>> vertices;
		Graph(){
 			vertices = make_unique<vector<shared_ptr<VertexEdges<T>>>>();
		}
		void add(shared_ptr<VertexEdges<T>> _vertexEdge){
			vertices->push_back(_vertexEdge);
		}
};

/* Algorithms */
class SimpleDijkstra{
	public:	
		int value;
		bool visited;
		SimpleDijkstra(int _value): value(_value){ visited = false;}
		void display(){
				cout << value << endl;
		}
};
Graph<SimpleDijkstra> *g;

template <typename T>
shared_ptr<VertexEdges<T>> getVertexEdgeFromEdge(shared_ptr<Edge<T>> _edge){
	for(auto it = g->vertices->begin(); it != g->vertices->end(); ++it){
		if((*it)->vertex == _edge->getDestVertex()) return (*it);
	}
	return nullptr;
}

template <typename T>
void depthFirst(shared_ptr<VertexEdges<T>> _vertexEdges){
	if(_vertexEdges != nullptr){
		//if(_vertexEdges->vertex == nullptr) cout << "NULL REFERENCE" <<endl;
		//cout << "Vertex " << _vertexEdges->vertex->getVertex()->visited << ", " << _vertexEdges->vertex->getVertex()->value << endl;
		for(auto it = _vertexEdges->edges->begin(); it != _vertexEdges->edges->end() && !(*it)->getDestVertex()->getVertex()->visited; ++it){
			(*it)->getDestVertex()->getVertex()->display();
			depthFirst(getVertexEdgeFromEdge(*it));
		}
		_vertexEdges->vertex->getVertex()->visited = true;
	}
}

shared_ptr<VertexEdges<SimpleDijkstra>> makeGraph(){
	g = new Graph<SimpleDijkstra>();
    shared_ptr<Vertex<SimpleDijkstra>> v1 = make_shared<Vertex<SimpleDijkstra>>(make_shared<SimpleDijkstra>(1));
    shared_ptr<Vertex<SimpleDijkstra>> v2 = make_shared<Vertex<SimpleDijkstra>>(make_shared<SimpleDijkstra>(2));
    shared_ptr<Vertex<SimpleDijkstra>> v3 = make_shared<Vertex<SimpleDijkstra>>(make_shared<SimpleDijkstra>(3));
    shared_ptr<Vertex<SimpleDijkstra>> v4 = make_shared<Vertex<SimpleDijkstra>>(make_shared<SimpleDijkstra>(4));
    shared_ptr<Edge<SimpleDijkstra>> e1 = make_shared<Edge<SimpleDijkstra>>(v1, v2, 5);
    shared_ptr<Edge<SimpleDijkstra>> e2 = make_shared<Edge<SimpleDijkstra>>(v2, v3, 8);
    shared_ptr<Edge<SimpleDijkstra>> e3 = make_shared<Edge<SimpleDijkstra>>(v1, v3, 10);
    shared_ptr<Edge<SimpleDijkstra>> e4 = make_shared<Edge<SimpleDijkstra>>(v1, v4, 6);
    shared_ptr<Edge<SimpleDijkstra>> e5 = make_shared<Edge<SimpleDijkstra>>(v2, v4, 3);
    shared_ptr<Edge<SimpleDijkstra>> e6 = make_shared<Edge<SimpleDijkstra>>(v3, v4, 5);
    shared_ptr<VertexEdges<SimpleDijkstra>> ve1 = make_shared<VertexEdges<SimpleDijkstra>>(v1);
    ve1->add(e1);
    ve1->add(e3);
    ve1->add(e4);
    shared_ptr<VertexEdges<SimpleDijkstra>> ve2 = make_shared<VertexEdges<SimpleDijkstra>>(v2);
    ve1->add(e2);
    ve1->add(e5);
    shared_ptr<VertexEdges<SimpleDijkstra>> ve3 = make_shared<VertexEdges<SimpleDijkstra>>(v3);
    ve1->add(e6);
    shared_ptr<VertexEdges<SimpleDijkstra>> ve4 = make_shared<VertexEdges<SimpleDijkstra>>(v4);
	g->add(ve1);
	g->add(ve2);
	g->add(ve3);
	g->add(ve4);
	return ve1;
}

int main() {  
	//cout << "Program Started" << endl;
	shared_ptr<VertexEdges<SimpleDijkstra>> ve1 = makeGraph();
	ve1->vertex->getVertex()->display();
	depthFirst(ve1);
	int a;
	cin >> a;
	//cout << "Program Completed" << endl;
    return 0;
}

