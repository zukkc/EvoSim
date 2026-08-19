#pragma once

#include "Connection.h"
#include "Node.h"
#include "NodeType.h"

#include <memory>
#include <vector>

namespace evosim {

class NetworkGraph {
public:
  Node &create_node(NodeType p_type);
  Node &add_node(std::unique_ptr<Node> p_node);
  Node *get_node_by_id(Object::ID p_id);

  std::vector<std::unique_ptr<Node>> &get_nodes();
  const std::vector<std::unique_ptr<Node>> &get_nodes() const;

  std::vector<Connection> &get_connections();
  const std::vector<Connection> &get_connections() const;

private:
  std::vector<std::unique_ptr<Node>> m_nodes;
  std::vector<Connection> m_connections;
};

} // namespace evosim
