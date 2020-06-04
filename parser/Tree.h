#pragma once
#include <string>
#include <list>


class Tree {
public:
	static class Node {
	private:
		int id;
		std::string name;
		std::string value;
		std::list<Node*>* childNodes;

	public:
		Node(const std::string& name, const std::string& value, const int id);
		Node(const std::string& name, std::list<Tree::Node*>* childNodes, const int id);
		~Node();
		const std::string& getName() const noexcept;
		const std::string& getValue() const noexcept;
		int getId() const noexcept;
		bool hasChildNodes() const noexcept;
		std::list<Node*>* getChildNodes() const noexcept;
		void addChildNode(Node* node);
		void output(std::ostream& os, int parentId) const;

	};
	explicit Tree(Node* n);
	~Tree();
	static void output(std::ostream& os, Tree::Node* node, int parentId);
	int size() const;
	void output(std::ostream& os) const;
	Node* getRoot() const;

private:
	int* size(Node* node, int* counter) const;
	Node* root;

};

std::ostream& operator<<(std::ostream& os, const Tree& tree);