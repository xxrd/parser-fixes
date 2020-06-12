#include "Tree.h"
#include <string>
#include <fstream>
#include <streambuf>

using namespace std;

Tree::Node::Node(const std::string& name, const std::string& value, int id, Node* parent) :
	id(id),
	parent(parent),
	name(name), 
	value(value), 
	childNodes(nullptr)
{}

Tree::Node::Node(const std::string& name, int id, Node* parent) :
	id(id),
	parent(parent),
	name(name),
	childNodes(nullptr)
{}

Tree::Node::Node(const Node& node) {
	id = node.id;
	name = node.name;
	value = node.value;
	parent = nullptr;

	if (node.childNodes != nullptr) {
		childNodes = new list<Node*>();
		for (list<Node*>::const_iterator it = node.childNodes->begin(); it != node.childNodes->end(); ++it)
		{
			Node* n = new Node(**it);
			n->setParent(this);
			childNodes->push_back(n);
		}
	}
	else {
		childNodes = nullptr;
	}
}

Tree::Node& Tree::Node::operator=(Node const& node) {
	if (this != &node) {
		id = node.id;
		name = node.name;
		value = node.value;
		parent = nullptr;

		if (node.childNodes != nullptr) {
			for (list<Node*>::const_iterator it = childNodes->begin(); it != childNodes->end(); ++it)
			{
				delete *it;
			}
			childNodes->clear();
			delete childNodes;

			childNodes = new list<Node*>();
			for (list<Node*>::const_iterator it = node.childNodes->begin(); it != node.childNodes->end(); ++it)
			{
				Node* n = new Node(**it);
				n->setParent(this);
				childNodes->push_back(n);
			}
		}
		else {
			childNodes = nullptr;
		}
	}
	return *this;
}

Tree::Node::Node(Node&& node) {
	swap(node);
}

Tree::Node& Tree::Node::operator=(Node&& node) {
	swap(node);
	return *this;
}

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

void Tree::Node::swap(Node& node) {
	std::swap(id, node.id);
	std::swap(name, node.name);
	std::swap(value, node.value);
	parent = node.parent;
	node.parent = nullptr;
	childNodes = node.childNodes;
	node.childNodes = nullptr;
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

void Tree::Node::appendChild(Node* node) {
	if (!hasChildNodes()) childNodes = new list<Node*>();
	node->setParent(this);
	childNodes->push_back(node);
}

void Tree::Node::setName(const std::string& name) {
	this->name = name;
}

void Tree::Node::setValue(const std::string& value) {
	this->value = value;
}

bool Tree::Node::isDummy() const {
	if (getId() == -1) return true;
	return false;
}

void Tree::Node::setParent(Node* parent) {
	this->parent = parent;
}

Tree::Node* Tree::Node::getParent() const {
	return parent;
}

Tree::Tree(Node* n) : 
	root(n) 
{}

Tree::Tree(const Tree& tree) {
	root = new Node(*tree.root);
}

Tree& Tree::operator=(Tree const& tree) {
	if (this != &tree) {
		delete root;
		root = new Node(*tree.root);
	}
	return *this;
}

Tree& Tree::operator=(Tree&& tree) {
	root = tree.root;
	tree.root = nullptr;
	return *this;
}

Tree::Tree(Tree&& tree) {
	root = tree.root;
	tree.root = nullptr;
}

Tree::~Tree() {
	delete root;
}

void Tree::output(std::ostream& os, Tree::Node* node) {
	if (!node->hasChildNodes()) {
		os << *node;
		return;
	}
	else {
		os << *node;
		for (list<Tree::Node*>::iterator it = node->getChildNodes()->begin(); it != node->getChildNodes()->end(); it++) {
			output(os, *it);
		}
	}
}

void Tree::output(std::ostream& os) const {
	if (root->isDummy()) return;
	Tree::output(os, root);
}

int Tree::size(Node* node) {
	static int counter = 0;

	if (!node->hasChildNodes()) {
		return ++counter;
	}
	else {
		++counter;
		for (list<Tree::Node*>::iterator it = node->getChildNodes()->begin(); it != node->getChildNodes()->end(); it++) {
			size(*it);
		}
	}
	return counter;
}

int Tree::size() const {
	if (root->isDummy()) return 0;
	return size(root);
}

Tree::Node* Tree::getRoot() const {
	return root;
}

Tree::Node* Tree::makeNode(const std::string& name, const std::string& value) {
	return new Node(name, value, generateNodeId());
}

Tree::Node* Tree::makeNode(const std::string& name) {
	return new Node(name, generateNodeId());
}

Tree::Node* Tree::makeDummy() {
	return new Tree::Node("", "", -1);
}

int Tree::generateNodeId() {
	static int lastGeneratedNodeId = 0;
	return lastGeneratedNodeId++;
}

std::ostream& operator<<(std::ostream& os, const Tree::Node& node) {
	os << "Id: " << node.getId();
	os << ", parent node: ";

	if (node.getParent() == nullptr)
		os << "none";
	else
		os << node.getParent()->getId();

	os << ", name: " << node.getName();

	if (!node.hasChildNodes()) {
		os << ", value: " << node.getValue() << ";" << endl;
		return os;
	}
	else {
		os << ", child nodes:";
		list<Tree::Node*>::iterator it;
		for (it = node.getChildNodes()->begin(); it != node.getChildNodes()->end();) {
			os << " " << (*it)->getId();
			if (++it != node.getChildNodes()->end())
				os << ",";
			else
				os << ";" << endl;
		}
	}

	return os;
}

std::ostream& operator<<(std::ostream& os, const Tree& tree) {
	tree.output(os);
	return os;
}