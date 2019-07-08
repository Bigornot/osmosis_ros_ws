
#include <osmosis_control/graph.hpp>



Node::Node(double x, double y)
{
	point.x = x;
	point.y = y;
}

bool compare_astar (string first, string second,
map<string,double>& f, map<string,double>& g)
{
	if ( f[first] < f[second] ) return true;
	else if ( f[first] == f[second] ) return ( g[first] > g[second] );
	else return false;
}

double Graph::distance(const Node* a, const Node* b)
{
	auto & p = a->point;
	auto & q = b->point;
	return distance(p, q);
}

double Graph::distance(const geometry_msgs::Point p, const geometry_msgs::Point q)
{
	return sqrt( pow(p.x - q.x, 2) + pow(p.y - q.y, 2) );
}

void Graph::addNode(const string& name, Node* n)
{
	nodes[name]= n;
	n->name = name;
}

void Graph::addEdge(const string& a, const string& b, double weight)
{
	auto n = nodes[a];
	auto m = nodes[b];
	n->neighbors.push_back({m, weight});
	m->neighbors.push_back({n, weight});
}

Node* Graph::getNode(const string& i)
{
	return nodes[i];
}

Node* Graph::getNode(const geometry_msgs::Point& p)
{
	for (auto& kv: nodes)
	{
		auto n = kv.second;
		if ( (n->point.x == p.x) && (n->point.y == p.y) )
			return n;
	}
	return nullptr;
}

Node* Graph::getClosestNode(const geometry_msgs::Point& p)
{
	Node* N;
	double D = numeric_limits<double>::max();
	for (auto& kv: nodes)
	{
		auto n = kv.second;
		double d = distance(p, n->point);
		if ( d < D )
		{
			N = n;
			D = d;
		}
	}
	return N;
}

vector<Node*> Graph::compute_plan(const Node* start, const Node* goal)
{
	using namespace placeholders;

	map<string, double> g;
	map<string, double> f;
	map<string, string> parent;
	
	string sn = start->name;
	string fn = goal->name;
	
	// Init grid
	for (auto i : nodes)
	{
		if (i.first == sn)
		{
			g[i.first] = 0;
			f[i.first] = distance(start, goal);
			parent[i.first] = i.first;
		}
		else
		{
			g[i.first] = numeric_limits<double>::max();
			f[i.first] = g[i.first];
		}
	}

	vector<Node*> plan;

	list<string> openset;
	openset.push_back(sn);

	while (!openset.empty())
	{
		string k = *openset.begin();
		//cout << "k: " << k << endl;
		openset.pop_front();
		if (k == fn)
		{
			// reconstruct path
			while (parent[k] != k)
			{
				auto p = getNode(k);
				plan.push_back(p);
				k = parent[k];
			}
			reverse(plan.begin(), plan.end());
			return plan;
		}
		for (auto& e: getNode(k)->neighbors)
		{
			//cout << "k': " << *(e.target) << endl;
			double g_ = g[k] + e.weight;
			string t = e.target->name;
			if (g_ < g[t])
			{
				g[t] = g_;
				f[t] = g[t] + distance(getNode(t), goal);
				parent[t] = k;
				openset.push_back(t);
			}
		}
		auto sort = bind(&compare_astar, _1, _2, f, g);
		openset.sort(sort);
	}

	return plan;
}
