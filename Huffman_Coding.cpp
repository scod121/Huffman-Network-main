// Huffman Coding

#include<bits/stdc++.h>
using namespace std;
int count_index=1;

class Node {
public:
	char* symbol;
	int frequency;
	Node* next;
	Node* left;
	Node* right;
};

void FrontBackSplit(Node* source, Node** frontRef, Node** backRef){ 
	Node* fast; 
	Node* slow; 
	slow = source; 
	fast = source->next; 
	while (fast != NULL) { 
		fast = fast->next; 
		if (fast != NULL) { 
			slow = slow->next; 
			fast = fast->next; 
		} 
	} 
	*frontRef = source; 
	*backRef = slow->next; 
	slow->next = NULL; 
}

Node* SortedMerge(Node* a, Node* b){ 
	Node* result = NULL; 
	if (a == NULL) 
		return (b); 
	else if (b == NULL) 
		return (a); 
	if (a->frequency <= b->frequency) { 
		result = a; 
		result->next = SortedMerge(a->next, b); 
	} 
	else { 
		result = b; 
		result->next = SortedMerge(a, b->next); 
	} 
	return (result); 
}

void MergeSort(Node** head){ 
	Node* ptr = *head; 
	Node* a; 
	Node* b; 
	if ((ptr == NULL) || (ptr->next == NULL)) { 
		return; 
	} 
	FrontBackSplit(ptr, &a, &b); 
	MergeSort(&a); 
	MergeSort(&b); 
	*head = SortedMerge(a, b); 
}  

Node* insert(Node* head, int key, char* c){ 
    Node* temp = new Node; 
    Node* ptr; 
    temp->frequency = key; 
    temp->next = NULL; 
    temp->left = NULL;
    temp->right = NULL;
    temp->symbol = (char *)malloc(10*sizeof(char));
    for(int i=0;i<strlen(c);i++){
    	temp->symbol[i] = c[i];
    }
    if (head == NULL) head = temp; 
    else{ 
        ptr = head; 
        while (ptr->next != NULL) 
            ptr = ptr->next; 
        ptr->next = temp; 
    } 
    return(head);
}

void part_1(int x[], int y[]){
	int i=0;
	for(char c='a';c<='z';c++){
		cout<<c<<"="<<x[i]<<" "<<",";
		i++;
	}
	cout<<endl;
	i=0;
	for(int j=0;j<10;j++){
		cout<<j<<"="<<y[i]<<" "<<",";
		i++;
	}
	cout<<endl;
}

void assignN(char ** symbol){
	string buffer = to_string(count_index++);
	(*symbol)[0]='N';
	for (int i = 0; i < buffer.size(); ++i){
		// cout<<buffer[i]<<endl;
		(*symbol)[i+1] = buffer[i];
	}
}

bool isalphabet(char x){
	return x<='z' && x>='a';
}

bool lessThan(Node** a, Node** b){
	if((*a)->frequency!=(*b)->frequency) return (*a)->frequency<(*b)->frequency;
	if(a==NULL)return false;
	if(b==NULL)return true;
	char firsta = (*a)->symbol[0];
	char firstb = (*b)->symbol[0];
	if(firsta=='N' && firstb=='N'){
		int lenone = strlen((*a)->symbol);
		int lentwo = strlen((*b)->symbol);
		if(lenone==lentwo){
			for (int i = 0; i < lenone; ++i)
				if((*a)->symbol[i]!=(*b)->symbol[i]){
					return (*a)->symbol[i] < (*b)->symbol[i];
				}
		}else{
			return lenone < lentwo;
		}
	}else{
		if(firsta=='N')return true;
		if(firstb=='N')return false;
		if(isalphabet(firsta) && isalphabet(firstb)) return firsta < firstb;
		if(!isalphabet(firsta) && !isalphabet(firstb)) return firsta < firstb;
		if(isalphabet(firsta) && !isalphabet(firstb)) return true;
		if(!isalphabet(firsta) && isalphabet(firstb)) return false;
	}
	return true;
}


void Insert_in_sorted_list(Node** head, Node* new_node){ 
    Node* current; 
    if (*head == NULL || (*head)->frequency >= new_node->frequency) { 
        new_node->next = *head; 
        *head = new_node; 
    } 
    else{ 
        current = *head; 
        while (current->next != NULL && lessThan(&current->next, &new_node)){ 
            current = current->next; 
        } 
        new_node->next = current->next; 
        current->next = new_node; 
    } 
}

void merge2nodes(Node** head){
	if((*head)->next == NULL) return;
	Node* ptr = *head;
	Node* a = ptr;
	ptr = ptr->next;
	Node* b = ptr;
	*head = ptr->next;
	ptr->next = NULL;
	Node* temp;
	temp = (Node *)malloc(sizeof(Node));
	temp->frequency = a->frequency + b->frequency;
	temp->symbol = (char *)malloc(10*sizeof(char));
	assignN(&temp->symbol);
	temp->left = a;
	temp->right = b;
	Insert_in_sorted_list(head, temp);
	merge2nodes(head);
}

string search(Node* head, char c, string s, int i){
	if(head == NULL) return "";
	if(head->symbol[0] == c) return s;
	string x = search(head->left, c, s+"0", i+1);
	string y = search(head->right, c, s+"1", i+1);
	if(x!="")return x;
	if(y!="")return y;
	return "";
}

void pre_order(Node* head){
	if(head != NULL){
		cout << head->symbol << '(' << head->frequency<<") ";
		pre_order(head->left);
		pre_order(head->right);
	}
}

int main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n;
    cin>>n;
    int x[26],y[10];
    for (int i = 0; i < 26; ++i){
    	x[i]=0;
    }
    for (int i = 0; i < 10; ++i){
    	y[i]=0;
    }
    for(int i=0;i<n;i++){
    	char arr[50];
    	cin>>arr;
    	for(int j=0;j<strlen(arr);j++){
    		if(arr[j]=='0' || arr[j]=='1' || arr[j]=='2' || arr[j]=='3' || arr[j]=='4' || arr[j]=='5' || arr[j]=='6' || arr[j]=='7' || arr[j]=='8' || arr[j]=='9'){
    			y[arr[j]-'0']++;
    		}
    		else x[arr[j]-'a']++;
    	}
    }
    part_1(x, y);
    Node* head = NULL;
    int j=0;
    for (char i = 'a'; i <= 'z'; ++i){
    	char* ptr = (char *)malloc(10*sizeof(char));
    	ptr[0]=i;
    	head = insert(head, x[j], ptr);
    	j++;
    }
    j=0;
    for (char i = '0'; i <= '9'; ++i){
    	char* ptr = (char *)malloc(10*sizeof(char));
    	ptr[0]=i;
    	head = insert(head, y[j], ptr);
    	j++;
    }
    MergeSort(&head);
    Node* ppt = head;
    while(ppt!=NULL){
    	cout<<ppt->frequency<<" ";
    	ppt = ppt->next;
    }
    merge2nodes(&head);
    cout<<endl;
    char** arr1;
    char** arr2;
    arr1 = (char **)malloc(26*sizeof(char *));
    for (int i = 0; i < 26; ++i){
    	arr1[i] = (char *)malloc(100*sizeof(char));
    }
    arr2 = (char **)malloc(10*sizeof(char *));
    for (int i = 0; i < 10; ++i){
    	arr2[i] = (char *)malloc(100*sizeof(char));
    }
    pre_order(head);
    cout<<"Huffman Codes :"<<endl;
    for (int i = 0; i < 26; ++i)
    {
    	cout<< char('a'+i) << ": "; 
    	cout << search(head, 'a'+i, "", 0);
    	cout<<endl;
    }
    for (int i = 0; i < 10; ++i)
    {
    	cout<< char('0'+i) << ": "; 
    	cout << search(head, '0'+i, "", 0);
    	cout<<endl;
    }
    return 0;
}