#include "NetworkGraph.h"

#include <utility>

namespace evosim {

Node &NetworkGraph::add_node(std::unique_ptr<Node> p_node) {
  m_nodes.push_back(std::move(p_node));
  return *m_nodes.back();
}

Node *NetworkGraph::get_node_by_id(Object::ID p_id) {
  for (auto &node : m_nodes) {
    if (node && node->get_id() == p_id) {
      return node.get();
    }
  }

  return nullptr;
}

std::vector<std::unique_ptr<Node>> &NetworkGraph::get_nodes() {
  return m_nodes;
}

const std::vector<std::unique_ptr<Node>> &NetworkGraph::get_nodes() const {
  return m_nodes;
}

std::vector<Connection> &NetworkGraph::get_connections() {
  return m_connections;
}

const std::vector<Connection> &NetworkGraph::get_connections() const {
  return m_connections;
}

} // namespace evosim
