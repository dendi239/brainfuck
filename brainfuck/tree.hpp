#pragma once

#include <memory>
#include <vector>

#include "io.hpp"
#include "marker.hpp"
#include "memory.hpp"
#include "program.hpp"

namespace brainfuck::tree {

using ::std::unique_ptr;
using ::std::vector;

class Node {
public:
  virtual ~Node() = default;

  virtual bool tick(Memory *memory, IO *io) = 0;
  virtual void reset() {}

  virtual void print(string pref = {}) {}
};

class FlipRunNode : public Node {
public:
  virtual bool tick(Memory *memory, IO *io) override {
    run_ = !run_;
    return run_;
  }

  virtual void reset() override {}

private:
  bool run_ = false;
};

class Add : public FlipRunNode {
public:
  Add(int diff) : diff_(diff) {}

  virtual bool tick(Memory *memory, IO *io) override {
    if (!FlipRunNode::tick(memory, io)) {
      return false;
    }
    memory->add(diff_);
    return true;
  }

  virtual void print(string pref) override {
    ::std::cerr << pref << "-+"[diff_ > 0];
    if (abs(diff_) != 1) {
      ::std::cerr << abs(diff_);
    }
    ::std::cerr << "\n";
  }

private:
  int diff_ = 0;
};

class Shift : public FlipRunNode {
public:
  Shift(int diff) : diff_(diff) {}

  virtual bool tick(Memory *memory, IO *io) override {
    if (!FlipRunNode::tick(memory, io)) {
      return false;
    }
    memory->shift(diff_);
    return true;
  }

  virtual void print(string pref) override {
    ::std::cerr << pref << "<>"[diff_ > 0];
    if (abs(diff_) != 1) {
      ::std::cerr << abs(diff_);
    }
    ::std::cerr << "\n";
  }

private:
  int diff_;
};

class Read : public FlipRunNode {
public:
  virtual bool tick(Memory *memory, IO *io) override {
    if (!FlipRunNode::tick(memory, io)) {
      return false;
    }

    memory->set(io->getchar());
    return true;
  }

  virtual void print(string pref) override { ::std::cerr << pref << ",\n"; }
};

class Write : public FlipRunNode {
public:
  virtual bool tick(Memory *memory, IO *io) override {
    if (!FlipRunNode::tick(memory, io)) {
      return false;
    }

    io->putchar(memory->get());
    return true;
  }

  virtual void print(string pref) override { ::std::cerr << pref << ".\n"; }
};

class Cycle : public Node {
public:
  Cycle(vector<unique_ptr<Node>> nodes = {}) : nodes_{std::move(nodes)} {}

  virtual void append(Node *node) { nodes_.emplace_back(node); }

  const vector<unique_ptr<Node>> &get_nodes() const { return nodes_; }

  vector<unique_ptr<Node>> release_nodes() { return std::move(nodes_); }

  virtual bool tick(Memory *memory, IO *io) override {
    while (true) {
      if (is_start_ && !memory->get()) {
        return false;
      }

      is_start_ = false;
      if (nodes_[inode_]->tick(memory, io)) {
        return true;
      }

      ++inode_;
      if (inode_ >= nodes_.size()) {
        is_start_ = true;
        inode_ = 0;
      }
    }
  }

  virtual void reset() override {
    is_start_ = true;
    inode_ = 0;

    for (auto &node : nodes_) {
      node->reset();
    }
  }

  virtual void print(string pref) override {
    ::std::cerr << pref << "[\n";
    for (auto &node : nodes_) {
      node->print(pref + "\t");
    }
    ::std::cerr << pref << "]\n";
  }

private:
  bool is_start_ = true;
  size_t inode_ = 0;
  vector<unique_ptr<Node>> nodes_;
};

class ArifmeticCycle : public FlipRunNode {
public:
  ArifmeticCycle(::std::map<int, int> diffs) : diffs_{std::move(diffs)} {}

  virtual bool tick(Memory *memory, IO *io) override {
    if (!FlipRunNode::tick(memory, io)) {
      return false;
    }

    int now = 0, steps = memory->get();
    for (auto [dx, dy] : diffs_) {
      memory->shift(dx - now);
      memory->add(dy * steps);
      now = dx;
    }
    memory->shift(-now);
    memory->set(0);

    return true;
  }

  virtual void print(string pref) override {
    ::std::cerr << pref << "[...]" << ::std::endl;
  }

private:
  ::std::map<int, int> diffs_;
};

int get_add(Node *node);
int get_shift(Node *node);

optional<unique_ptr<Node>> build_arifmetic(Cycle *cycle);
vector<unique_ptr<Node>> eliminate_cycles(vector<unique_ptr<Node>> nodes);
vector<unique_ptr<Node>> compress(vector<unique_ptr<Node>> nodes);
vector<unique_ptr<Node>> build_tree(Program *program);

class Interpretator {
public:
  Interpretator(Memory *memory, IO *io, Program *program)
  : memory_(memory), io_(io)
  {
    nodes_ = build_tree(program);
  }

  bool tick() {
    while (true) {
      if (inode_ >= nodes_.size()) {
        return false;
      }

      if (nodes_[inode_]->tick(memory_, io_)) {
        // ::std::cerr << "run node: " << nodes_[inode_].get() << "\n";
        return true;
      }

      ++inode_;
    }
  }

private:
  size_t inode_ = 0;
  vector<unique_ptr<Node>> nodes_;

  Memory *memory_;
  IO *io_;
};

} // namespace brainfuck::tree
