#include "Tree.h"
#include <string>
#include <fstream>
#include <streambuf>

using namespace std;

Tree::Node::Node(const std::string& name, const std::string& value, const int id) : 
	name(name), 
	value(value), 
	id(id), 
	childNodes(nullptr) 
{}

Tree::Node::Node(const std::string& name, list<Tree::Node*>* childNodes, const int id) : 
	name(name), 
	childNodes(childNodes), 
	id(id) 
{}

Tree::Node::~Node() {
	if (childNodes != nullptr) {
		for (list<Node*>::const_iterator it = childNodes->begin(); it != childNodes->end(); ++it)
		{
			delete *it;
		}
		childNodes->clear();
	}
	delete childNodes;
}
const std::string& Tree::Node::getName() const noexcept {
	return name;
}
const std::string& Tree::Node::getValue() const noexcept {
	return value;
}

int Tree::Node::getId() const noexcept {
	return id;
}

bool Tree::Node::hasChildNodes() const noexcept {
	if (childNodes == nullptr) return false;
	return true;
}

list<Tree::Node*>* Tree::Node::getChildNodes() const noexcept {
	return childNodes;
}

void Tree::Node::addChildNode(Node* node) {
	if (!hasChildNodes()) childNodes = new list<Node*>();
	childNodes->push_back(node);
}

void Tree::Node::output(std::ostream& os, int parentId) const {
	os << "id: " << getId() << ", parent node: ";
	if (parentId == -1) os << "none";
	else os << parentId;
	os << ", name: " << getName();

	if (!hasChildNodes()) {
		os << ", value: " << getValue() << endl;
		return;
	}
	else {
		os << ", child nodes: ";
		list<Tree::Node*>::iterator it;
		for (it = childNodes->begin(); it != childNodes->end();) {
			os << " " << (*it)->getId();
			if (++it != childNodes->end()) os << ", ";
			else os << endl;
		}
	}

}

Tree::Tree(Node* n) : 
	root(n) 
{}

Tree::~Tree() {
	delete root;
}

void Tree::output(std::ostream& os, Tree::Node* node, int parentId) {
	if (!node->hasChildNodes()) {
		node->output(os, parentId);
		return;
	}
	else {
		node->output(os, parentId);
		for (list<Tree::Node*>::iterator it = node->getChildNodes()->begin(); it != node->getChildNodes()->end(); it++) {
			output(os, *it, node->getId());

		}
	}
}

int* Tree::size(Node* node, int* counter) const {
	if (!node->hasChildNodes()) {
		(*counter)++;
		return counter;
	}
	else {
		(*counter)++;
		for (list<Tree::Node*>::iterator it = node->getChildNodes()->begin(); it != node->getChildNodes()->end(); it++) {
			size(*it, counter);
		}
	}
}

int Tree::size() const {
	int* counter = new int(0);
	size(root, counter);
	int counterValue = *counter;
	delete counter;
	return counterValue;
}

void Tree::output(std::ostream& os) const {
	Tree::output(os, root, -1);
}

Tree::Node* Tree::getRoot() const {
	return root;
}

std::ostream& operator<<(std::ostream& os, const Tree& tree) {
	tree.output(os);
	return os;
}