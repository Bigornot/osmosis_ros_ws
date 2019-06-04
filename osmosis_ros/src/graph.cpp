#include <list>
#include <functional>
#include <limits>
#include <cmath>
#include <algorithm>

#include <osmosis_control/graph.hpp>



Node::Node(double x, double y) {
  this->point.x = x;
  this->point.y = y;
}

bool compare_astar (std::string first, std::string second,
  std::map<std::string,double>& f, std::map<std::string,double>& g)
{
	if ( f[first] < f[second] ) return true;
	else if ( f[first] == f[second] ) return ( g[first] > g[second] );
	else return false;
}

double Graph::distance(const Node* a, const Node* b) {
  auto & p = a->point;
  auto & q = b->point;
  return distance(p, q);
}

double Graph::distance(const geometry_msgs::Point p, const geometry_msgs::Point q) {
  return sqrt( std::pow(p.x - q.x, 2) + std::pow(p.y - q.y, 2) );
}

void Graph::addNode(const std::string& name, Node* n) {
  nodes[name]= n;
  n->name = name;
}

void Graph::addEdge(const std::string& a, const std::string& b, double weight) {
  auto n = nodes[a];
  auto m = nodes[b];
  n->neighbors.push_back({m, weight});
  m->neighbors.push_back({n, weight});
}

Node* Graph::getNode(const std::string& i) {
  return nodes[i];
}

Node* Graph::getNode(const geometry_msgs::Point& p) {
  for (auto& kv: nodes) {
    auto n = kv.second;
    if ( (n->point.x == p.x) && (n->point.y == p.y) )
      return n;
  }
  return nullptr;
}

Node* Graph::getClosestNode(const geometry_msgs::Point& p) {
  Node* N;
  double D = std::numeric_limits<double>::max();
  for (auto& kv: nodes) {
    auto n = kv.second;
    double d = distance(p, n->point);
    if ( d < D ) {
      N = n;
      D = d;
    }
  }
  return N;
}

std::vector<Node*> Graph::compute_plan(const Node* start, const Node* goal)
{
  using namespace std::placeholders;

  std::map<std::string, double> g;
  std::map<std::string, double> f;
  std::map<std::string, std::string> parent;

  std::string sn = start->name;
  std::string fn = goal->name;

	// Init grid
	for (auto i : nodes) {
		if (i.first == sn) {
			g[i.first] = 0;
			f[i.first] = distance(start, goal);
			parent[i.first] = i.first;
		}
		else {
			g[i.first] = std::numeric_limits<double>::max();
			f[i.first] = g[i.first];
		}
	}

  std::vector<Node*> plan;

	std::list<std::string> openset;
	openset.push_back(sn);

	while (!openset.empty()) {
		std::string k = *openset.begin();
    //std::cout << "k: " << k << std::endl;
		openset.pop_front();
		if (k == fn) {
			// reconstruct path
			while (parent[k] != k) {
				auto p = getNode(k);
        plan.push_back(p);
				k = parent[k];
			}
			reverse(plan.begin(), plan.end());
      return plan;
		}
		for (auto& e: getNode(k)->neighbors) {
      //std::cout << "k': " << *(e.target) << std::endl;
			double g_ = g[k] + e.weight;
      std::string t = e.target->name;
			if (g_ < g[t]) {
				g[t] = g_;
				f[t] = g[t] + distance(getNode(t), goal);
				parent[t] = k;
				openset.push_back(t);
			}
		}
    auto sort = std::bind(&compare_astar, _1, _2, f, g);
		openset.sort(sort);
	}

  return plan;
}
