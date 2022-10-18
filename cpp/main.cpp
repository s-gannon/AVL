#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

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
		delete left;
		delete right;
	}
	//mutators
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

	void insert(Node* node, string _name, string _gator_id) {	//come back to this
		if (root == nullptr) {
			root = node;
			cout << "successful" << endl;
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
			if (node->get_right_link() == nullptr) {	//successful addition
				static Node* new_node = new Node(_name, _gator_id);
				node->get_right_link()->set_parent_link(node);
				node->set_right_link(new_node);
			}
			else {
				insert(node->get_right_link(), _name, _gator_id);
				return;
			}
		}
		//balancing portion
		/*while(node != root){
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

				int height_sum = parent_height + child_height;
				switch(height_sum){
					case 3:		//left left
						{
							Node* grandparent = node->get_parent_link();
							node->get_left_link()->set_right_link(node);
							node->get_left_link()->set_parent_link(grandparent);
							if(node == grandparent->get_left_link())
								grandparent->set_left_link(node->get_left_link());
							else
								grandparent->set_right_link(node->get_left_link());
							node->set_parent_link(node->get_left_link());
							node->set_left_link(nullptr);
							break;
						}
					case -3:	//right right
						{
							Node* grandparent = node->get_parent_link();
							node->get_right_link()->set_left_link(node);
							node->get_right_link()->set_parent_link(grandparent);
							if(node == grandparent->get_left_link())
								grandparent->set_left_link(node->get_right_link());
							else
								grandparent->set_right_link(node->get_right_link());
							node->set_parent_link(node->get_right_link());
							node->set_right_link(nullptr);
							break;
						}
					case 1:		//left right
						{

							break;
						}
					case -1:	//right left
						{

							break;
						}
					default:
						cout << "unsuccessful" << endl;
						return;
						break;
				}
			}

			node = node->get_parent_link();
		} */
		cout << "successful" << endl;
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
			//error out if we get here
			return -1;
		}
	}
	void print_pre_order(Node* node, vector<string>& current) {
		if (node == nullptr)
			return;
		current.push_back(node->get_gator_id());
		print_pre_order(node->get_left_link(), current);
		print_pre_order(node->get_right_link(), current);
	}
	void print_in_order(Node* node, vector<string>& current) {
		if (node == nullptr)
			return;
		print_in_order(node->get_left_link(), current);
		current.push_back(node->get_gator_id());
		print_in_order(node->get_right_link(), current);
	}
	void print_post_order(Node* node, vector<string>& current) {
		if (node == nullptr)
			return;
		print_in_order(node->get_left_link(), current);
		print_in_order(node->get_right_link(), current);
		current.push_back(node->get_gator_id());
	}
	void search_name(Node* node, string name, vector<string>& current) {
		if (node == nullptr){
			cout << "unsuccessful" << endl;
			return;
		}
		if (!name.compare(node->get_name())){	//if comparison returns 0, invert that and make it true because the two are equal
			current.push_back(node->get_gator_id());
		}
		search_name(node->get_left_link(), name, current);
		search_name(node->get_right_link(), name,  current);
	}
	Node* search_id(Node* node, string _gator_id){
		if (root == nullptr) {
			return nullptr;
		}
		if (stoi(node->get_gator_id()) == stoi(_gator_id)){
			return node;	//found it! return the ptr
		}
		if (stoi(node->get_gator_id()) < stoi(_gator_id)) {	//go down the left
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
	Node* find_max_key(Node* node){
		while(node->get_right_link() != nullptr){
			node = node->get_right_link();
		}
		return node;
	}
	void remove_id(Node* node, string _gator_id){
		if(root == nullptr){
			cout << "unsuccessful" << endl;
			return;
		}

		if(_gator_id < node->get_gator_id()){
			remove_id(node->get_left_link(), _gator_id);
			return;
		}
		else if(_gator_id > node->get_gator_id()){
			remove_id(node->get_right_link(), _gator_id);
			return;
		}
		else{
			if(node->get_left_link() == nullptr && node->get_left_link() == nullptr){
				delete node;
				node = nullptr;
			}
			else if(node->get_left_link() != nullptr && node->get_right_link() != nullptr){
				Node* predecessor = find_max_key(node->get_left_link());

				node->set_gator_id(predecessor->get_gator_id());
				remove_id(node->get_left_link(), predecessor->get_gator_id());
				return;
			}
			else{
				Node* current = node;	//store mem addr of node we want to delete

				if(node->get_left_link() != nullptr){	//if we have a left branch
					node = node->get_left_link();		//set node to the left branch
				}
				else{
					node = node->get_right_link();		//else, set to right branch
				}

				delete current;		//delete the original node at the mem addr
			}
		}
		cout << "successful" << endl;
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
		vector<string> print_vec;
		print_pre_order(root, print_vec);
		for (size_t i = 0; i < print_vec.size(); i++) {
			if (i == print_vec.size() - 1)
				cout << print_vec[i];
			else
				cout << print_vec[i] << ",";
		}
	}
	void print_in_order() {
		vector<string> print_vec;
		print_in_order(root, print_vec);
		for (size_t i = 0; i < print_vec.size(); i++) {
			if (i == print_vec.size() - 1)
				cout << print_vec[i];
			else
				cout << print_vec[i] << ",";
		}
	}
	void print_post_order() {
		vector<string> print_vec;
		print_post_order(root, print_vec);
		for (size_t i = 0; i < print_vec.size(); i++) {
			if (i == print_vec.size() - 1)
				cout << print_vec[i];
			else
				cout << print_vec[i] << ",";
		}
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
		for(auto i : print_vec)
			cout << i << endl;
	}
	void print_level_count(){
		if (root == nullptr) {
			cout << "0" << endl;
			return;
		}
		int level_count;
		level_count = get_max_height(root, 1);
		cout << level_count << endl;
	}
	void remove_id(string _gator_id){
		remove_id(root, _gator_id);
	}
	void remove_in_order(int num){
		vector<string> id_vec;
		print_in_order(root, id_vec);
		remove_id(root, id_vec[num]);
	}
};

int main() {
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
	}
	avl.print_in_order();

	return 0;
}


//TO DO:
//balance
// remove id
// remove inOrder N
// main
//
