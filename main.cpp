#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>

using namespace std;

class Node {
private:
	string name;
	int gator_id;
	Node* left;
	Node* right;
	Node* parent;
public:
	Node(string _name, int _gator_id) {
		name = _name;
		gator_id = _gator_id;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}
	~Node() {
		delete left;
		delete right;
	}
	//mutators
	void set_left_link(Node* _left) { left = _left; }
	void set_right_link(Node* _right) { right = _right; }
	void set_parent_link(Node* _parent) { parent = _parent; }
	//accessors
	string get_name() { return name; }
	int get_gator_id() { return gator_id; }
	Node* get_left_link() { return left; }
	Node* get_right_link() { return right; }
	Node* get_parent_link() { return parent; }
};

class AVL {
private:
	Node* root;

	void insert(Node* node, string _name, int _gator_id) {	//come back to this
		if (root == nullptr) {
			root = node;
			return;
		}
		if (node->get_gator_id() < _gator_id) {	//go down the left
			if (node->get_left_link() == nullptr) {
				static Node* new_node = new Node(_name, _gator_id);
				node->get_left_link()->set_parent_link(node);
				node->set_left_link(new_node);
			}
			else {
				insert(node->get_left_link(), _name, _gator_id);
				return;
			}
		}
		else {	//go down the right
			if (node->get_right_link() == nullptr) {
				static Node* new_node = new Node(_name, _gator_id);
				node->get_right_link()->set_parent_link(node);
				node->set_right_link(new_node);
			}
			else {
				insert(node->get_right_link(), _name, _gator_id);
				return;
			}
		}
		//balance
		while(node != root){
			int left_height = get_max_height(node->get_left_link(),0);
			int right_height = get_max_height(node->get_right_link(),0);
			if(abs(left_height - right_height) > 1){
				int parent_height = get_max_height(node, 0);
				int child_height;
				Node* child;

				if(left_height == -1){
					child = node->get_left_link();
					child_height = left_height;
				}
				else{
					child = node->get_right_link();
					child_height = right_height;
				}

				switch(parent_height + child_height){
					case 3:		//left left
						Node* grandparent = node->get_parent_link();
						node->get_left_link()->set_right_link(node);
						node->get_left_link()->set_parent_link(grandparent);
						if(node == grandparent.get_left_link())
							grandparent->set_left_link(node->get_left_link());
						else
							grandparent->set_right_link(node->get_left_link());
						node->set_parent_link(node->get_left_link());
						node->set_left_link(nullptr);
						break;
					case -3:	//right right
						Node* grandparent = node->get_parent_link();
						node->get_right_link()->set_left_link(node);
						node->get_right_link()->set_parent_link(grandparent);
						if(node == grandparent.get_left_link())
							grandparent->set_left_link(node->get_right_link());
						else
							grandparent->set_right_link(node->get_right_link());
						node->set_parent_link(node->get_right_link());
						node->set_right_link(nullptr);
						break;
					case 1:		//left right
						break;
					case -1:	//right left
						break;
					default:
						cout << "unsuccessful" << endl;
						return;
						break;
				}
			}

			node = node->get_parent_link();
		}
		cout << "successful" << endl;
	}
	int get_max_height(Node* node, int height) {
		if(node == nullptr){
			return -1;
		}
		else if (node->get_left_link() == nullptr && node->get_right_link() == nullptr) {
			return height;
		}
		else if (node->get_left_link() != nullptr && node->get_right_link() != nullptr) {
			return 	max(get_max_height(node->get_left_link(), ++height),
				get_max_height(node->get_right_link(), ++height));
		}
		else if (node->get_left_link() != nullptr) {
			return get_max_height(node->get_left_link(), ++height);
		}
		else if (node->get_right_link() != nullptr) {
			return get_max_height(node->get_right_link(), ++height);
		}
	}
	void print_pre_order(Node* node, vector<int>& current) {
		if (node == nullptr)
			return;
		current.push_back(node->get_gator_id());
		print_pre_order(node->get_left_link(), current);
		print_pre_order(node->get_right_link(), current);
	}
	void print_in_order(Node* node, vector<int>& current) {
		if (node == nullptr)
			return;
		print_in_order(node->get_left_link(), current);
		current.push_back(node->get_gator_id());
		print_in_order(node->get_right_link(), current);
	}
	void print_post_order(Node* node, vector<int>& current) {
		if (node == nullptr)
			return;
		print_in_order(node->get_left_link(), current);
		print_in_order(node->get_right_link(), current);
		current.push_back(node->get_gator_id());
	}
	void search_name(Node* node, string name, vector<string> &sName) {
		if (node == nullptr){
			cout << "unsuccessful" << endl;
			return;
		}
		if (name.equals(node->get_name())){
			sName.push_back(node->get_gator_id());
		}
		searchName(node->get_left_link(), name, current);
		searchName(node->get_right_link(), name,  current);
	}
	void search_id(Node* node, string _gator_id){
		if (root == nullptr) {
			cout << "unsuccessful" << endl;
			return;
			//print unsecessful
		}
		if (node->get_gator_id() == _gator_id){
			cout << node->get_name() << endl;
			return;
		}
		if (node->get_gator_id() < _gator_id) {	//go down the left
			if (node->get_left_link() == nullptr)
				return;	//return this node
			else {
				search(node->get_left_link(), _gator_id);
				return;
			}
		}
		else {	//go down the right
			if (node->get_right_link() == nullptr)
				return;	//return this node
			else {
				search(node->get_right_link(), _gator_id);
				return;
			}
		}
	}
public:
	AVL() {
		root = nullptr;
	}
	~AVL() {
		delete root;
	}
	void insert(string _name, string _gator_id) {
		insert(root, _name, _gator_id);
	}
	void print_pre_order() {
		vector<int> print_vec;
		print_pre_order(root, &print_vec);
		for (int i = 0; i < print_vec.size(); i++) {
			if (i == print_vec.size() - 1)
				cout << print_vec[i];
			else
				cout << print_vec[i] << ",";
		}
	}
	void print_in_order() {
		vector<int> print_vec;
		print_in_order(root, &print_vec);
		for (int i = 0; i < print_vec.size(); i++) {
			if (i == print_vec.size() - 1)
				cout << print_vec[i];
			else
				cout << print_vec[i] << ",";
		}
	}
	void print_post_order() {
		vector<int> print_vec;
		print_post_order(root, &print_vec);
		for (int i = 0; i < print_vec.size(); i++) {
			if (i == print_vec.size() - 1)
				cout << print_vec[i];
			else
				cout << print_vec[i] << ",";
		}
	}
	void search_id(string _gator_id){
		search_id(root, _gator_id);
	}
	void search_name(string name){
		vector<int> print_vec;
		search_name(root, name, &print_vec);
		for(auto i : print_vec)
			cout << i << endl;
	}
	void printLevelCount(){
		if (node == nullptr) {
			cout << "0" << endl;
			return;
		}
		int levelCount;
		levelCount = get_max_height(root, 1);
		cout << levelCount << endl;
	}
};

int main() {
	bool cont_prog = true;
	string user_input;

	do {
		string next_word;
		size_t word_pos = 0;

		getline(cin, user_input);

		istringstream user_input_stream(user_input);

		while (user_input_stream) {
			string command;
			user_input_stream >> command;

			if (user_input_stream) {
				if (command == "insert") {

				}
				else if (command == "remove") {

				}
				else if (command == "search") {

				}
			}
		}

		cont_prog = false;
	} while (cont_prog);

	return 0;
}


//TO DO:
//balance
// remove id
// remove inOrder N
// main
//
