#include "tree.hpp"

namespace brainfuck::tree {

int get_shift(Node *node) {
  marker::Memory memory;
  marker::IO io;

  node->tick(&memory, &io);
  node->reset();

  return memory.index;
}

int get_add(Node *node) {
  marker::Memory memory;
  marker::IO io;

  node->tick(&memory, &io);
  node->reset();

  return memory.diffs[0];
}

vector<unique_ptr<Node>> build_tree(Program *program) {
  vector<unique_ptr<Node>> nodes;
  vector<Cycle *> stack;

  auto append = [&](Node *node) {
    if (stack.empty()) {
      nodes.emplace_back(node);
    } else {
      stack.back()->append(node);
    }
  };

  for (auto command = program->read_command(); command;
       command = program->read_command()) {
    switch (*command) {
    case '[': {
      auto cycle = new Cycle();
      append(cycle);
      stack.push_back(cycle);
      break;
    }

    case ']': {
      stack.pop_back();
      break;
    }

    case '+': {
      append(new Add{+1});
      break;
    }

    case '-': {
      append(new Add{-1});
      break;
    }

    case '>': {
      append(new Shift{+1});
      break;
    }

    case '<': {
      append(new Shift{-1});
      break;
    }

    case ',': {
      append(new Read{});
      break;
    }

    case '.': {
      append(new Write{});
      break;
    }
    }
  }

  nodes = compress(std::move(nodes));
  nodes = eliminate_cycles(std::move(nodes));

  return nodes;
}

vector<unique_ptr<Node>> compress(vector<unique_ptr<Node>> nodes) {
  vector<unique_ptr<Node>> ans;
  for (auto &node : nodes) {
    if (auto cycle = dynamic_cast<Cycle *>(node.get()); cycle) {
      ans.emplace_back(new Cycle{compress(cycle->release_nodes())});
      continue;
    }

    if (!ans.empty()) {
      if (auto last_add = dynamic_cast<Add *>(ans.back().get()); last_add) {
        if (auto now_add = dynamic_cast<Add *>(node.get()); now_add) {
          auto combined = new Add{get_add(last_add) + get_add(now_add)};
          ans.pop_back();
          ans.emplace_back(combined);
          continue;
        }
      }
      if (auto last_shift = dynamic_cast<Shift *>(ans.back().get());
          last_shift) {
        if (auto now_shift = dynamic_cast<Shift *>(node.get()); now_shift) {
          auto combined =
              new Shift{get_shift(last_shift) + get_shift(now_shift)};
          ans.pop_back();
          ans.emplace_back(combined);
          continue;
        }
      }
    }

    ans.emplace_back(std::move(node));
  }

  return ans;
}

vector<unique_ptr<Node>> eliminate_cycles(vector<unique_ptr<Node>> nodes) {
  vector<unique_ptr<Node>> ans;
  for (auto &node : nodes) {
    if (auto cycle = dynamic_cast<Cycle *>(node.get()); cycle) {
      auto arifmetic = build_arifmetic(cycle);
      if (arifmetic) {
        ans.push_back(std::move(*arifmetic));
      } else {
        ans.emplace_back(new Cycle{eliminate_cycles(cycle->release_nodes())});
      }
      continue;
    }
    ans.push_back(std::move(node));
  }
  return ans;
}
optional<unique_ptr<Node>> build_arifmetic(Cycle *cycle) {
  for (auto &node : cycle->get_nodes()) {
    if (auto add = dynamic_cast<Add *>(node.get()); add) {
      continue;
    }
    if (auto shift = dynamic_cast<Shift *>(node.get()); shift) {
      continue;
    }

    return nullopt;
  }

  marker::IO io;
  marker::Memory memory;

  for (auto &node : cycle->get_nodes()) {
    node->tick(&memory, &io);
  }

  if (io.used || memory.index != 0 || memory.diffs[0] != -1) {
    return nullopt;
  }

  return optional<unique_ptr<Node>>(
      ::std::make_unique<ArifmeticCycle>(std::move(memory.diffs)));
}

} // namespace brainfuck::tree
