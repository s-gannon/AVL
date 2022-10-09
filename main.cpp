#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

class Node{
private:
	string name;
	int gator_id;
	Node* left;
	Node* right;
	Node* parent;
public:
	Node(string _name, int _gator_id){
		name = _name;
		gator_id = _gator_id;
		left = NULL;
		right = NULL;
		parent = NULL;
	}
	// Node(string _name, int _gator_id, Node* _left, Node* _right){
	// 	name = _name;
	// 	height = 0;
	// 	gator_id = _gator_id;
	// 	left = _left;
	// 	left->set_height(height + 1);
	// 	right = _right;
	// 	right->set_height(height + 1);
	// }
	// Node(string _name, int _gator_id, int _height, Node* _left, Node* _right){
	// 	name = _name;
	// 	height = _height;
	// 	gator_id = _gator_id;
	// 	left = _left;
	// 	left->set_height(height + 1);
	// 	right = _right;
	// 	right->set_height(height + 1);
	// }

	~Node(){
		delete left;
		delete right;
	}
	//mutators
	void set_height(int _height){ height = _height; }
	void set_left_link(Node* _left){ left = _left; }
	void set_right_link(Node* _right){ right = _right; }
	void set_parent_link(Node* _parent){ parent = _parent; }
	//accessors
	string get_name(){ return name; }
	int get_height(){ return height; }
	int get_gator_id(){ return gator_id; }
	Node* get_left_link(){ return left; }
	Node* get_right_link(){ return right; }
	Node* get_parent_link(){ return parent; }
};

class AVL{
private:
	Node* root;

	void insert(Node* node, string _name, int _gator_id){	//come back to this
		if(root != NULL){
			root = node;
			return;
		}
		if(node->get_gator_id() < _gator_id){	//go down the left
			if(node->get_left_link() == NULL){
				static Node* new_node = new Node(_name, _gator_id);
				node->set_left_link(new_node);
				return;
			}
			else{
				insert(node->get_left_link(), _name, _gator_id);
				return;
			}
		}
		else{	//go down the right
			if(node->get_right_link() == NULL){
				static Node* new_node = new Node(_name, _gator_id);
				node->set_right_link(new_node);
				return;
			}
			else{
				insert(node->get_right_link(), _name, _gator_id);
				return;
			}
		}
	}
	int get_max_height(Node* node, int height){
		if(node->get_left_link() == NULL && node->get_right_link() == NULL){
			return height;
		}
		else if(node->get_left_link() != NULL && node->get_right_link() != NULL){
			return 	max(get_max_height(node->get_left_link(), ++height),
						get_max_height(node->get_right_link(), ++height));
		}
		else if(node->get_left_link() != NULL){
			return get_max_height(node->get_left_link(), ++height);
		}
		else if(node->get_right_link() != NULL){
			return get_max_height(node->get_right_link(), ++height);
		}
	}
	void balance(Node* node, int height){
		int left_height = get_max_height(node->get_left_link(), ++height);
		int right_height = get_max_height(node->get_right_link(), ++height);
		if(abs(right_height - left_height) < 2){
			return;
		}
		else if(){
			//???
		}
		else{
			if(right_height > left_height){
				balance(node->get_right_link());
			}
			else{
				balance(node->get_left_link());
			}
		}
	}
	void print_pre_order(Node* node, vector<int> &current){
		if(node == NULL)
			return;
		current.push_back(node->get_gator_id());
		print_pre_order(node->get_left_link(), ++depth);
		print_pre_order(node->get_right_link(), ++depth);
	}
	void print_in_order(Node* node, vector<int> &current){
		if(node == NULL)
			return;
		print_in_order(node->get_left_link(), &current);
		current.push_back(node->get_gator_id());
		print_in_order(node->get_right_link(), &current);
	}
	void print_post_order(Node* node, vector<int> &current){
		if(node == NULL)
			return;
		print_in_order(node->get_left_link(), &current);
		print_in_order(node->get_right_link(), &current);
		current.push_back(node->get_gator_id());
	}
public:
	AVL(){
		root = NULL;
	}
	~AVL(){
		delete root;
	}
	void insert(string _name, int _gator_id){
		insert(root, _name, _gator_id);
		balance(root);
	}
	void print_pre_order(){
		vector<int> print_vec;
		print_pre_order(root, &print_vec);
		for(int i = 0; i < print_vec.size(); i++){
			if(i == print_vec.size() - 1)
				cout << print_vec[i];
			else
				cout << print_vec[i] << ",";
		}
	}
	void print_in_order(){
		vector<int> print_vec;
		print_in_order(root, &print_vec);
		for(int i = 0; i < print_vec.size(); i++){
			if(i == print_vec.size() - 1)
				cout << print_vec[i];
			else
				cout << print_vec[i] << ",";
		}
	}
	void print_post_order(){
		vector<int> print_vec;
		print_post_order(root, &print_vec);
		for(int i = 0; i < print_vec.size(); i++){
			if(i == print_vec.size() - 1)
				cout << print_vec[i];
			else
				cout << print_vec[i] << ",";
		}
	}
	void balance(){

	}
};

int main(){
	bool cont_prog = true;
	string user_input;

	do{
		string next_word;
		size_t word_pos = 0;

		getline(cin, user_input);

		istringstream user_input_stream(user_input);

		while(user_input_stream){
			string command;
			user_input_stream >> command;

			if(user_input_stream){
				if(command == "insert"){

				}
				else if(command == "remove"){

				}
				else if(command == "search"){

				}
			}
		}

		cont_prog = false;
	} while(cont_prog);

	return 0;
}
