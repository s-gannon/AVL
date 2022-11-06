#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdio>
#include <cstdlib>

using namespace std;

class Node {
private:
	string name;
	string gator_id;
	Node* left;
	Node* right;
	Node* parent;
public:
	Node(string _name, string _gator_id) {
		name = _name;
		gator_id = _gator_id;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}
	~Node() {
		if(left == nullptr)
			delete left;
		if(right == nullptr)
			delete right;
		if(parent == nullptr)
			delete parent;
	}
	//mutators
	void set_name(string _name) { name = _name; }
	void set_left_link(Node* _left) { left = _left; }
	void set_right_link(Node* _right) { right = _right; }
	void set_parent_link(Node* _parent) { parent = _parent; }
	void set_gator_id(string _gator_id) { gator_id = _gator_id; }
	//accessors
	string get_name() { return name; }
	string get_gator_id() { return gator_id; }
	Node* get_left_link() { return left; }
	Node* get_right_link() { return right; }
	Node* get_parent_link() { return parent; }
};

class AVL {
private:
	Node* root;

	Node* left_rotate(Node* node){
		Node* par = node;
		Node* child = node->get_right_link();

		child->set_left_link(par);
		par->set_right_link(nullptr);
		par->set_parent_link(child);
		child->set_parent_link(nullptr);
		
		return child;
	}

	Node* right_rotate(Node* node){
		Node* par = node;
		Node* child = node->get_left_link();

		child->set_right_link(par);
		par->set_left_link(nullptr);
		par->set_parent_link(child);
		child->set_parent_link(nullptr);
		
		return child;
	}

	void balance(){
		int left_height = get_max_height(root->get_left_link(), 0);
		int right_height = get_max_height(root->get_right_link(), 0);
		if(abs(left_height - right_height) > 1){
			int parent_height = get_max_height(root, 0);
			int child_height;

			child_height = (left_height > right_height ? left_height : right_height);

			int height_sum = parent_height + child_height;
			switch(height_sum){
				case 3:		//left left
					{
						root = right_rotate(root);
					}
				case -3:	//right right
					{
						root = left_rotate(root);
					}
				case 1:		//left right
					{
						root->set_left_link(left_rotate(root->get_left_link()));
						root = right_rotate(root);
						break;
					}
				case -1:	//right left
					{
						root->set_right_link(right_rotate(root->get_right_link()));
						root = left_rotate(root);
						break;
					}
				default:
					cout << "unsuccessful" << endl;
					return;
					break;
			}
		}
	}

	void insert(Node* node, string _name, string _gator_id) {
		if (root == nullptr) {
			root = new Node(_name, _gator_id);
			cout << "successful" << endl;
			return;
		}
		if (_gator_id < node->get_gator_id()) {	//go down the left
			if (node->get_left_link() == nullptr) {	//should go in left and nothing in left pointer
				Node* new_node = new Node(_name, _gator_id);
				node->set_left_link(new_node);
				new_node->set_parent_link(node);

				cout << "successful" << endl;
				return;
			}
			else {
				insert(node->get_left_link(), _name, _gator_id);
				return;
			}
		}
		else if(_gator_id > node->get_gator_id()) {	//go down the right
			if (node->get_right_link() == nullptr) {	//successful addition
				Node* new_node = new Node(_name, _gator_id);
				node->set_right_link(new_node);
				node->get_right_link()->set_parent_link(node);
				cout << "successful" << endl;
				return;
			}
			else {
				insert(node->get_right_link(), _name, _gator_id);
				return;
			}
		}
		else{
			cout << "unsuccessful" << endl;
			return;
		}
		return;
	}
	int get_max_height(Node* node, int height) {
		if(node == nullptr){
			return -1;
		}
		else if (node->get_left_link() == nullptr && node->get_right_link() == nullptr) {
			return height;
		}
		else if (node->get_left_link() != nullptr && node->get_right_link() != nullptr) {
			++height;
			return 	max(get_max_height(node->get_left_link(), height),
				get_max_height(node->get_right_link(), height));
		}
		else if (node->get_left_link() != nullptr) {
			++height;
			return get_max_height(node->get_left_link(), height);
		}
		else if (node->get_right_link() != nullptr) {
			++height;
			return get_max_height(node->get_right_link(), height);
		}
		else{
			fprintf(stderr, "[ERROR] Unexpected error in get_max_height.\n");
			return -1;
		}
	}
	void print_pre_order(Node* node, vector<string>& current) {
		if (node == nullptr)
			return;
		current.push_back(node->get_name());
		print_pre_order(node->get_left_link(), current);
		print_pre_order(node->get_right_link(), current);
	}
	void print_in_order(Node* node, vector<string>& current) {
		if (node == nullptr)
			return;
		print_in_order(node->get_left_link(), current);
		current.push_back(node->get_name());
		print_in_order(node->get_right_link(), current);
	}
	void print_in_order_id(Node* node, vector<string>& current) {
		if (node == nullptr)
			return;
		print_in_order(node->get_left_link(), current);
		current.push_back(node->get_gator_id());
		print_in_order(node->get_right_link(), current);
	}
	void print_post_order(Node* node, vector<string>& current) {
		if (node == nullptr)
			return;
		print_post_order(node->get_left_link(), current);
		print_post_order(node->get_right_link(), current);
		current.push_back(node->get_name());
	}
	void search_name(Node* node, string name, vector<string>& current) {
		if (node == nullptr){
			return;
		}
		search_name(node->get_left_link(), name, current);
		if (!name.compare(node->get_name())){	//if comparison returns 0, invert that and make it true because the two are equal
			current.push_back(node->get_gator_id());
		}
		search_name(node->get_right_link(), name,  current);
	}
	Node* search_id(Node* node, string _gator_id){
		if (root == nullptr) {
			return nullptr;
		}
		if (!(node->get_gator_id().compare(_gator_id))){
			return node;	//found it! return the ptr
		}
		if (_gator_id < node->get_gator_id()) {	//go down the left
			if (node->get_left_link() == nullptr)
				return nullptr;	//there's no more left, so it's not here
			else {
				return search_id(node->get_left_link(), _gator_id);	//there's more left
			}
		}
		else {	//go down the right
			if (node->get_right_link() == nullptr)
				return nullptr;
			else {
				return search_id(node->get_right_link(), _gator_id);
			}
		}
	}
	Node* in_order_successor(Node* node){
		Node* min = node;
		Node* point = node;
		while (point->get_left_link() != nullptr){
			min = point->get_left_link();
			point = point->get_left_link();
		}
		return min;
	}
	Node* remove_id(Node* node, string _gator_id){
		if(root == nullptr){
			return nullptr;
		}
		if(_gator_id < node->get_gator_id()){
			node->set_left_link(remove_id(node->get_left_link(), _gator_id));
		}
		else if(_gator_id > node->get_gator_id()){
			node->set_right_link(remove_id(node->get_right_link(), _gator_id));
		}
		else{
			if(node->get_left_link() == nullptr){
				return node->get_right_link();
			}
			else if(node->get_right_link() == nullptr){
				return node->get_left_link();
			}
			Node* successor = in_order_successor(node->get_right_link());
			node->set_gator_id(successor->get_gator_id());
			node->set_name(successor->get_name());
			node->set_right_link(remove_id(node->get_right_link(),successor->get_gator_id()));
		}

		return node;
	}
public:
	AVL() {
		root = nullptr;
	}
	~AVL() {
		if(root == nullptr)
			delete root;
	}
	void insert(string _name, string _gator_id) {
		insert(root, _name, _gator_id);
		// balance();
	}
	void print_pre_order() {
		vector<string> print_vec;
		print_pre_order(root, print_vec);
		for (size_t i = 0; i < print_vec.size(); i++) {
			if (i == print_vec.size() - 1)
				cout << print_vec[i];
			else
				cout << print_vec[i] << ", ";
		}
		cout << endl;
	}
	void print_in_order() {
		vector<string> print_vec;
		print_in_order(root, print_vec);
		for (size_t i = 0; i < print_vec.size(); i++) {
			if (i == print_vec.size() - 1)
				cout << print_vec[i];
			else
				cout << print_vec[i] << ", ";
		}
		cout << endl;
	}
	void print_post_order() {
		vector<string> print_vec;
		print_post_order(root, print_vec);
		for (size_t i = 0; i < print_vec.size(); i++) {
			if (i == print_vec.size() - 1)
				cout << print_vec[i];
			else
				cout << print_vec[i] << ", ";
		}
		cout << endl;
	}
	void search_id(string _gator_id){
		Node* found = search_id(root, _gator_id);
		if(found == nullptr){
			cout << "unsuccessful" << endl;
		}
		else{
			cout << found->get_name() << endl;
		}
	}
	void search_name(string name){
		vector<string> print_vec;
		search_name(root, name, print_vec);
		if(print_vec.size() == 0){
			cout << "unsuccessful" << endl;
		}
		for(auto i : print_vec)
			cout << i << endl;
	}
	void print_level_count(){
		if (root == nullptr) {
			cout << "0" << endl;
			return;
		}
		int level_count;
		level_count = get_max_height(root, 0);
		cout << level_count << endl;
	}
	void remove_id(string _gator_id){
		// root = remove_id(root, _gator_id);
		// if(root == nullptr){
		// 	cout << "unsuccessful" << endl;
		// }
		// else{
		// 	cout << "successful" << endl;
		// }
	}
	void remove_in_order(int num){
	// 	vector<string> id_vec;
	// 	print_in_order_id(root, id_vec);
	// 	remove_id(id_vec[num]);
	}
};

int main(void) {
	AVL avl;
	string num_str;
	vector<string> commands;

	cin >> num_str;

	//how many commands to run
	for(int i = 0; i <= stoi(num_str); i++){
		string arg;
		getline(cin, arg);
		commands.push_back(arg);
	}

	commands.erase(commands.begin());	//get rid of leading empty string in vec

	// for(auto i : commands)
	// 	cout << i << endl;

	for(auto command : commands){
		istringstream command_parts(command);
		string start;

		command_parts >> start;
		if (start == "insert") {
			string name;
			string id;

			command_parts >> name;
			command_parts >> id;

			avl.insert(name.substr(1, name.size()-2), id);
		}
		else if (start == "remove") {
			string arg;

			command_parts >> arg;

			if(arg.size() == 8){	//remove id (string)
				avl.remove_id(arg);
			}
			else{	//remove in order (int)
				avl.remove_in_order(stoi(arg));
			}
		}
		else if (start == "search") {
			string arg;

			command_parts >> arg;

			if (arg[0] == '"') {	//looking for a name
				avl.search_name(arg.substr(1, arg.size()-2));
			}
			else{	//looking for an ID
				avl.search_id(arg);
			}
		}
		else if (start == "printLevelCount") {
			avl.print_level_count();
		}
		else if (start == "printInorder") {
			avl.print_in_order();
		}
		else if (start == "printPreorder") {
			avl.print_pre_order();
		}
		else if (start == "printPostorder") {
			avl.print_post_order();
		}
		else if (start == "removeInorder") {
			string arg;

			command_parts >> arg;
			
			avl.remove_in_order(stoi(arg));
		}
	}
	//avl.print_in_order();
	return 0;
}


//TO DO:
// balance
// remove id
// remove inOrder N
// main
//
