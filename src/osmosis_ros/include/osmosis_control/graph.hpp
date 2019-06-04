/*
 * Copyright 2018 LAAS-CNRS
 *
 * This file is part of the OSMOSIS project.
 *
 * Osmosis is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * Osmosis is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef OSMOSIS_GRAPH_HPP
#define OSMOSIS_GRAPH_HPP

#include <map>
#include <algorithm>
#include <geometry_msgs/Point.h>



    struct Node;

    struct Edge {
      Node* target;
      double weight;
    };

    struct Node {
      std::string name;
      geometry_msgs::Point point;
      std::vector<Edge> neighbors;
      Node(double x, double y);
    };

    struct Graph {
      friend std::ostream& operator<< (std::ostream&, const Graph& g);

      void addNode(const std::string& name, Node* n);
      void addEdge(const std::string& a, const std::string& b,
        double weight = 0);
      Node* getNode(const std::string& name);
      Node* getNode(const geometry_msgs::Point& p);
      Node* getClosestNode(const geometry_msgs::Point& p);
      inline int size() { return nodes.size(); };
      std::vector<Node*> compute_plan(const Node* start, const Node* goal);
      static double distance(const Node* a, const Node* b);
      static double distance(const geometry_msgs::Point a, const geometry_msgs::Point b);
      inline void clear() { this->nodes.clear(); };

      Graph& operator=(const Graph& g) {
        this->copy(g);
        return *this;
      };
      Graph() {};
      Graph(const Graph& g) {
        this->copy(g);
      };



    private:

      std::map<std::string, Node*> nodes;

      struct DeepCopyMapPointer {
        typedef std::map<std::string, Node*> map_type;
        typedef map_type::value_type value_type;
        value_type operator()( const value_type & other ) const {
          return value_type(other.first, new Node(*other.second) );
        }
      };
      void copy(const Graph &other) {
        std::transform(other.nodes.begin(), other.nodes.end(),
          std::inserter(nodes, nodes.end() ), DeepCopyMapPointer() );
      }
    };

    Graph parse(const std::string& filename);

    std::ostream& operator<< (std::ostream&, const Edge& e);
    std::ostream& operator<< (std::ostream&, const Node& n);
    std::ostream& operator<< (std::ostream&, const Graph& g);



#endif
