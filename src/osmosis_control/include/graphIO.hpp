#include <fstream>
//#include <json/json.h>
#include <jsoncpp/json/json.h>
//#include <json/json.h>
//#include <json/reader.h>
//#include <json/value.h>

#include <graph.hpp>


    std::ostream& operator<< (std::ostream& out, const Edge& e) {
      out << "-[" << e.weight << "]-> " << e.target->name;
      return out;
    }

    std::ostream& operator<< (std::ostream& out, const Node& n) {
      out << n.name;
      for (auto e: n.neighbors) out << e << std::endl;
      return out;
    }

    std::ostream& operator<< (std::ostream& out, const Graph& g) {
      for (auto n: g.nodes)
        out << *n.second << std::endl;
      return out;
    }

Graph parse(const std::string& filename) {
  std::ifstream ifs(filename);
  Json::Value root;
  ifs >> root;

  Graph g;

  for (auto & n: root["nodes"])
    g.addNode(n["id"].asString(),
      new Node(n["x"].asDouble(), n["y"].asDouble()));

  for (auto & e: root["edges"]) {
    auto * src = g.getNode(e[(uint)0].asString());
    auto * tgt = g.getNode(e[1].asString());
    g.addEdge(src->name, tgt->name, Graph::distance(src, tgt));
  }
  return g;
}
