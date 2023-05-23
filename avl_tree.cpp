#include <iostream>
#include<algorithm>
using namespace std;

template<class T>
struct node {
	public:
		T data;
		node<T>* left;
		node<T>* right;
		int height;
		node(const T& val){
			this->data = val;
			left = NULL;
			right = NULL;
			height = 1;
		};
};

template <class T> class avlTree  {
	public:
		node<T>* root = NULL;
		
	      int height(node<T> * head){
            if(head==NULL) return 0;
            return head->height;
        }
		
		node<T>* insert(node<T>* head , T data_){
			node<T>* data = new node<T>(data_);
			if(head == NULL){
				head = data;
				return head;
			}else{
				if(head->data < data->data){
					head->right = insert(head->right , data->data);
					head->height = 1 + max(height(head->left), height(head->right));
          			int bal = height(head->left) - height(head->right);					
					if(bal < -1){
						if(data->data > head->right->data){
							head = singleleftrotate(head);
						}else{
							head = doubleleftrotation(head);
						}
					}
				}else if(head->data > data->data){
				 	head->left = insert(head->left , data->data);
					head->height = 1 + max(height(head->left), height(head->right));
          			int bal = height(head->left) - height(head->right);
          			
					if(bal > 1){
						if(data->data < head->left->data){
							head = singlerightrotate(head);
						}else{
							head = doublerightnoation(head);
						}
					}					
				}
			}
			            return head;
		}
		
		node<T>* search(node<T>* root , T x){
			if(root == NULL){
				return NULL;
			}else{
				if(x > root->data){
					search(root->right , x);
				}else if(x < root->data){
					search(root->left , x);
				}else{
					return root;
				}
			}
		}
		
		node<T>* remove(node<T>* root,T x){
			if(root == NULL){
				return NULL;
			}if(x < root->data){
				root->left = remove(root->left , x);
			}else if(x > root->data){
				root->right = remove(root->right ,x);
			}else{
				node<T>* temp = root->right;
				if(root->right == NULL){
					node<T>* left = root->left;
					delete(root);
					root = left;
				}else if(root->left == NULL){
					node<T>* right = root->right;
					delete(root);
					root = right;
				}else{
					node<T>* key = temp;
					while(key->left != NULL){
						key = key->left;
					}
					root->data = key->data;
					root->right = remove(root->right , key->data);
				}
			}
			if(root == NULL){
				return NULL;
			}
			root->height = 1 + max(height(root->left), height(root->right));
			int bal = height(root->left) - height(root->right);
			if(bal > 1){
				node<T>* check = root->left;
                if(height(check->left) >= height(check->right)){
                    return singlerightrotate(root);
                }else{
                    return doublerightnoation(root);
                }
				}else if(bal < -1){
					node<T>* check = root->right;
               if(height(check->left) <= height(check->right)){
                    return singleleftrotate(root);
                }else{
                    return doubleleftrotation(root);
                }                	
				}
				return root;
			}
			
		
		node<T>* singleleftrotate(node<T>* root){
			node<T>* u = root->right;
			root->right = u->left;
			u->left = root;
            root->height = 1+max(height(root->left), height(root->right));
            u->height = 1+max(height(u->left), height(u->right));			
			return u;
		}
		
		node<T>* singlerightrotate(node<T>* root){
			node<T>* u = root->left;
			root->left = u->right;
			u->right = root;
            root->height = 1+max(height(root->left), height(root->right));
            u->height = 1+max(height(u->left), height(u->right));
			return u;
		}		

		node<T>* doublerightnoation(node<T>* root){
			root->left = singleleftrotate(root->left);
			return singlerightrotate(root); 
		}
		
		node<T>* doubleleftrotation(node<T>* root){
			root->right = singlerightrotate(root->right);
			return singleleftrotate(root);
		}
		
	void inorder(node<T>* t)
    {
        if(t == NULL)
            return;
        inorder(t->left);
        cout << t->data  <<"\n";
        inorder(t->right);
    }
};


int main() { 

	avlTree<int> *t = new avlTree<int>();
    t->root = t->insert(t->root,20);
    t->root = t->insert(t->root,25);
    t->root = t->insert(t->root,15);
    t->root = t->insert(t->root,10);
    t->root=t->insert(t->root,30);
    t->root=t->insert(t->root,5);
    t->root=t->insert(t->root,35);
    t->root=t->insert(t->root,67);
    t->root=t->insert(t->root,43);
    t->root=t->insert(t->root,21);
    t->root=t->insert(t->root,89);
    t->root=t->insert(t->root,38);
    t->root=t->insert(t->root,69);
    t->root=t->insert(t->root,63);
	t->root=t->remove(t->root,63);
	t->root=t->remove(t->root,67);
	t->root=t->remove(t->root,89);	
	t->root=t->remove(t->root,69);
	t->inorder(t->root);
 return 0;
}
