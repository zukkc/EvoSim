#include "NetworkGraph.h"

#include "nodes/AddNode.h"
#include "nodes/InputNode.h"
#include "nodes/MultiplyNode.h"
#include "nodes/OutputNode.h"

#include <stdexcept>
#include <utility>

namespace evosim {

Node &NetworkGraph::create_node(NodeType p_type) {
  switch (p_type) {
  case NodeType::Input:
    return add_node(std::make_unique<InputNode>());
  case NodeType::Output:
    return add_node(std::make_unique<OutputNode>());
  case NodeType::Add:
    return add_node(std::make_unique<AddNode>());
  case NodeType::Multiply:
    return add_node(std::make_unique<MultiplyNode>());
  }

  throw std::invalid_argument("Unknown node type");
}

Node &NetworkGraph::add_node(std::unique_ptr<Node> p_node) {
  if (!p_node) {
    throw std::invalid_argument("Cannot add a null node");
  }

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
