#pragma once
#include <string>
#include <list>

class Tree {
public:
	static class Node {
	private:
		int id;
		Node* parent;
		std::string name;
		std::string value;
		std::list<Node*>* childNodes;
		Node(const std::string& name, const std::string& value, int id, Node* parent = nullptr);
		Node(const std::string& name, int id, Node* parent = nullptr);
		void swap(Node& s);

	public:
		Node(const Node& node);
		Node& operator=(const Node& s);
		Node& operator=(Node&& node);
		Node(Node&& s);
		~Node();
		const std::string& getName() const noexcept;
		void setName(const std::string& name);
		const std::string& getValue() const noexcept;
		void setValue(const std::string& value);
		int getId() const noexcept;
		Node* getParent() const;
		void setParent(Node* parent);
		std::list<Node*>* getChildNodes() const noexcept;
		bool hasChildNodes() const noexcept;
		void appendChild(Node* node);
		bool isDummy() const;

		friend Tree;
	};
	explicit Tree(Node* n);
	Tree(const Tree& tree);
	Tree(Tree&& tree);
	Tree& operator=(const Tree& s);
	Tree& operator=(Tree&& tree);
	~Tree();
	Node* getRoot() const;
	static void output(std::ostream& os, Tree::Node* node);
	void output(std::ostream& os) const;
	static int size(Node* node);
	int size() const;
	static Node* makeNode(const std::string& name, const std::string& value);
	static Node* makeNode(const std::string& name);
	static Node* makeDummy();

private:
	Node* root;
	static int generateNodeId();

};

std::ostream& operator<<(std::ostream& os, const Tree& tree);
std::ostream& operator<<(std::ostream& os, const Tree::Node& node);