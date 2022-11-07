#include <cstddef>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdio>
#include <cstdlib>

using namespace std;

inline int max(int a, int b){
	return (a > b ? a : b);
}

class Node{
public:
	int height;
	string name, gator_id;
	Node* left;
	Node* right;

	Node(string _name, string _gator_id){
		height = 1;
		name = _name;
		gator_id = _gator_id;
		left = nullptr;
		right = nullptr;
	}
	~Node(){
		delete left;
		delete right;
	}
};

class AVL {
private:
	Node* root;
	int height(Node* node){
		return (node == nullptr ? 0 : node->height);
	}
	int get_bal_fact(Node* node){
		return (node == nullptr ? 0 : height(node->left) - height(node->right));
	}
	Node* left_rotate(Node* node){
		Node* par = node->right;
		Node* child = par->left;

		par->left = node;
		node->right = child;
		node->height = max(height(node->left), height(node->right)) + 1;
		par->height = max(height(par->left), height(par->right)) + 1;

		return par;
	}
	Node* right_rotate(Node *node){
		Node* par = node->left;
		Node* child = par->right;
		par->right = node;
		node->left = child;
		node->height = max(height(node->left), height(node->right)) + 1;
		par->height = max(height(par->left), height(par->right)) + 1;
		
		return par;
	}
	Node* insert(Node* node, string _name, string _gator_id){
		if(node == nullptr){
			return new Node(_name, _gator_id);
		}
		if(_gator_id < root->gator_id){
			node->left = insert(node->left, _name, _gator_id);
		}
		else if(_gator_id > root->gator_id){
			node->right = insert(node->right, _name, _gator_id);
		}
		//balancing goes on down here
		node->height = max(height(node->left), height(node->right)) + 1;
		
		int par_bal_fact = get_bal_fact(node);
		int child_bal_fact;
		if(get_bal_fact(node->left) > get_bal_fact(node->right)){
			child_bal_fact = get_bal_fact(node->left);
		}
		else{
			child_bal_fact = get_bal_fact(node->right);
		}

		if(par_bal_fact == 2){
			if(child_bal_fact == 1){
				return right_rotate(node);
			}
			else if(child_bal_fact == -1){
				node->left = left_rotate(node->left);
				return right_rotate(node);
			}
		}
		else if(par_bal_fact == -2){
			if(child_bal_fact == -1){
				return left_rotate(node);
			}
			else if(child_bal_fact == 1){
				node->right = right_rotate(node->right);
				return left_rotate(node);
			}
		}
		return node;
	}
	Node* smallest_node(Node* node){
		Node* current = node;
		while(current->left != nullptr){
			current = current->left;
		}
		return current;
	}
	Node* remove_id(Node* node, string _gator_id){
		if(node == nullptr){
			return node;
		}
		if(_gator_id < node->gator_id){
			node->left = remove_id(node->left, _gator_id);
		}
		else if(_gator_id > node->gator_id){
			node->right = remove_id(node->right, _gator_id);
		}
		else{
			if((node->left == nullptr) || (node->right == nullptr)){
				Node* temp = node->left ? node->left : node->right;

				if(temp == nullptr){
					temp = node;
					node = nullptr;
				}
				else{
					*node = *temp;
				}
				free(temp);
			}
			else{
				Node* temp = smallest_node(node->right);
				node->gator_id = temp->gator_id;
				node->name = temp->name;
				node->right = remove_id(node->right, temp->gator_id);
			}
		}

		if(node == nullptr){
			return node;
		}

		return node;
	}
	string search_id(Node* node, string _gator_id){
		if(node == nullptr){
			return "";
		}
		if(node->gator_id.compare(_gator_id) == 0){
			return node->name;
		}
		else if(_gator_id < node->gator_id){
			return search_id(node->left, _gator_id);
		}
		else if(_gator_id > node->gator_id){
			return search_id(node->right, _gator_id);
		}
		return "";
	}
	void search_name(Node* node, string _name, vector<string>& ids){
		if (node == nullptr){
			return;
		}
		search_name(node->left, _name, ids);
		if (_name.compare(node->name) == 0){
			ids.push_back(node->gator_id);
		}
		search_name(node->right, _name, ids);
	}
	void get_ids_in_order(Node* node, vector<string>& ids) {
		if (node == nullptr)
			return;
		get_ids_in_order(node->left, ids);
		ids.push_back(node->gator_id);
		get_ids_in_order(node->right, ids);
	}
	void get_names_in_order(Node* node, vector<string>& names) {
		if (node == nullptr)
			return;
		get_names_in_order(node->left, names);
		names.push_back(node->name);
		get_names_in_order(node->right, names);
	}
	void get_names_post_order(Node* node, vector<string>& names) {
		if (node == nullptr)
			return;
		get_names_post_order(node->left, names);
		get_names_post_order(node->right, names);
		names.push_back(node->name);
	}
	void get_names_pre_order(Node* node, vector<string>& names) {
		if (node == nullptr)
			return;
		names.push_back(node->name);
		get_names_pre_order(node->left, names);
		get_names_pre_order(node->right, names);
	}
public:
	AVL(){
		root = nullptr;
	}
	~AVL(){
		delete root;
	}
	Node* getRoot(){return root;}
	void search_id(string _gator_id){
		string res = search_id(root, _gator_id);
		if(res.compare("") == 0){
			cout << "unsuccessful" << endl;
		}
		else{
			cout << res << endl;
		}
	}
	void search_name(string _name){
		vector<string> ids;
		search_name(root, _name, ids);
		if(ids.size() == 0){
			cout << "unsuccessful" << endl;
		}
		else{
			for(auto id : ids){
				cout << id << endl;
			}
		}
	}
	void insert(string _name, string _gator_id){
		if(search_id(root, _gator_id).compare("") == 0){
			root = insert(root, _name, _gator_id);
			cout << "successful" << endl;
		}
		else{
			cout << "unsuccessful" << endl;
		}
	}
	void remove_id(string _gator_id){
		if(search_id(root, _gator_id).compare("") != 0){
			root = remove_id(root, _gator_id);
			cout << "successful" << endl;
		}
		else{
			cout << "unsuccessful" << endl;
		}
	}
	void remove_in_order(int num){
		vector<string> ids;
		get_ids_in_order(root, ids);
		if(ids.size() <= num + 1){
			root = remove_id(root, ids[num]);
			cout << "successful" << endl;
		}
		else{
			cout << "unsuccessful" << endl;
		}
	}
	void print_level_count(){
		cout << height(root) << endl;
	}
	void print_in_order(){
		vector<string> names;
		get_names_in_order(root, names);
		for(size_t i = 0; i < names.size(); i++){
			if(i == names.size() - 1){
				cout << names[i];
			}
			else{
				cout << names[i] << ", ";
			}
		}
		cout << endl;
	}
	void print_pre_order(){
		vector<string> names;
		get_names_pre_order(root, names);
		for(size_t i = 0; i < names.size(); i++){
			if(i == names.size() - 1){
				cout << names[i];
			}
			else{
				cout << names[i] << ", ";
			}
		}
		cout << endl;
	}
	void print_post_order(){
		vector<string> names;
		get_names_post_order(root, names);
		for(size_t i = 0; i < names.size(); i++){
			if(i == names.size() - 1){
				cout << names[i];
			}
			else{
				cout << names[i] << ", ";
			}
		}
		cout << endl;
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

			bool valid_name = true;

			for(auto chr : name.substr(1, name.size()-2)){
				if((chr < 0x41 || (chr > 0x5A && chr < 0x61)) || ((chr > 0x5A && chr < 0x61) || chr > 0x7A)){
					valid_name = false;
				}
			}
			if(id.size() != 8){
				cout << "unsuccessful" << endl;
			}

			if(valid_name){
				avl.insert(name.substr(1, name.size()-2), id);
			}
			else{
				cout << "unsuccessful" << endl;
			}
		}
		else if (start == "remove") {
			string arg;

			command_parts >> arg;

			if(arg.size() == 8){	//remove id (string)
				avl.remove_id(arg);
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
