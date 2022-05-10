#include <iostream>

using namespace std;

template<class T1, class T2>
struct duo {
    T1 data1;
    T2 data2;

    duo(T1 data1, T2 data2) : data1(data1), data2(data2) {};

    friend ostream& operator<<(ostream& out, duo& pair) {
        out << "[" << pair.data1 << " ; " << pair.data2 << "]";
        return out;
    }

    friend istream& operator>>(istream& in, duo& pair) {
        in >> pair.data1;
        in >> pair.data2;
        return in;
    }

    friend bool operator==(duo& p1, duo& p2) {
        return p1.data1 == p2.data1 && p1.data2 == p2.data2;
    }
};

template<class T>
class gleipnir {
private:
    struct item {
        T data;
        item* prev_item;
        item* next_item;

        item(T data, item* prev_item = nullptr, item* next_item = nullptr) :
            data(data), prev_item(prev_item), next_item(next_item) {};


    };

    item* m_head;
    item* m_tail;
    unsigned long int m_size;

    void remove_solo();

    gleipnir(item*);

    gleipnir(gleipnir<T>*);

public:
    void push_back(T data);

    void push_front(T data);

    void insert(T data, int position);

    T* get();

    T* find(int position);

    void remove_back();

    void remove_front();

    void remove(int position);

    bool find(T* data);

    duo<gleipnir, gleipnir> split(int position);

    int size();

    bool empty();

    gleipnir();

    gleipnir(const gleipnir<T>& list);

    ~gleipnir();

    friend ostream& operator<<(ostream& out, const gleipnir& list) {
        item* cur_item = list.m_head;
        if (cur_item != nullptr) {
            while (cur_item != list.m_tail && cur_item != nullptr) {
                out << cur_item->data << " ";
                cur_item = cur_item->next_item;
            }
            if (list.m_tail != nullptr)
                out << list.m_tail->data;
        }
        else {
            out << "list is empty!";
        }
        return out;
    }
};

template<class T>
gleipnir<T>::gleipnir() : m_head(nullptr), m_tail(m_head), m_size(0) {};

template<class T>
gleipnir<T>::gleipnir(const gleipnir<T>& list) : m_head(list.m_head), m_tail(list.m_tail), m_size(list.m_size) {};

template<class T>
gleipnir<T>::gleipnir(item* item) :m_size(1) {
    gleipnir<T>::item* cur_item = m_head = item;
    while (cur_item->next_item != nullptr) {
        cur_item = cur_item->next_item;
        m_size++;
    }
    m_tail = cur_item;
}

template<class T>
gleipnir<T>::gleipnir(gleipnir<T>* list) : m_head(list->m_head), m_tail(list->m_tail), m_size(list->m_size) {};

template<class T>
gleipnir<T>::~gleipnir() {
    item* save_item = m_head;
    while (save_item != m_tail && save_item != nullptr) {
        save_item = m_head->next_item;
        /*m_head = nullptr;*/
        m_head = save_item;
    }
}

template<class T>
void gleipnir<T>::push_back(T data) {
    item* new_item = new item(data);
    if (m_head == nullptr) {
        m_head = m_tail = new_item;
    }
    else {
        new_item->prev_item = m_tail;
        m_tail->next_item = new_item;
        m_tail = new_item;
    }
    m_size++;
};

template<class T>
void gleipnir<T>::push_front(T data) {
    item* new_item = new item(data);
    if (m_head == nullptr) {
        m_head = m_tail = new_item;
    }
    else {
        new_item->next_item = m_head;
        m_head->prev_item = new_item;
        m_head = new_item;
    }
    m_size++;
}

template<class T>
void gleipnir<T>::insert(T data, int position) {
    if (position <= m_size - 1) {
        if (position == 0) push_front(data);
        else if (position == m_size) push_back(data);
        else {
            item* cur_item = m_head;
            for (int i = 0; i < position; i++) {
                cur_item = cur_item->next_item;
            }
            item* new_item = new item(data);
            cur_item->prev_item->next_item = new_item;
            new_item->prev_item = cur_item->prev_item;
            new_item->next_item = cur_item;
            cur_item->prev_item = new_item;
        }
        m_size++;
    }
}

template<class T>
int gleipnir<T>::size() { return m_size; }

template<class T>
void gleipnir<T>::remove_solo() {
    delete m_head;
    m_head = m_tail = nullptr;
    m_size--;
}

template<class T>
void gleipnir<T>::remove_back() {
    if (m_size > 1) {
        m_tail = m_tail->prev_item;
        delete m_tail->next_item;
        m_size--;
    }
    else if (m_size == 1)
        remove_solo();
}

template<class T>
void gleipnir<T>::remove_front() {
    if (m_size > 1) {
        m_head = m_head->next_item;
        delete m_head->prev_item;
    }
    else if (m_size == 1)
        remove_solo();
    m_size--;
}

template<class T>
void gleipnir<T>::remove(int position) {
    if (position <= m_size - 1) {
        if (position == 0) remove_front();
        if (position == m_size - 1) remove_back();
        else {
            item* cur_item = m_head;
            for (int i = 0; i < position; i++) {
                cur_item = cur_item->next_item;
            }
            cur_item->prev_item->next_item = cur_item->next_item;
            cur_item->next_item->prev_item = cur_item->prev_item;
            delete cur_item;
        }
        m_size--;
    }
}

template<class T>
duo<gleipnir<T>, gleipnir<T>> gleipnir<T>::split(int position) {
    if (m_size == 2 && position == 0) {
        gleipnir<T> list1, list2;
        list1.push_back(m_head->data);
        list2.push_back(m_tail->data);
        return duo<gleipnir<T>, gleipnir<T>>(list1, list2);
    }
    else if (-1 < position < m_size - 1) {
        item* cur_item = m_head;
        gleipnir<T> list1, list2;
        for (int i = 0; i <= position; i++) {
            list1.push_back(cur_item->data);
            cur_item = cur_item->next_item;
        }
        while (cur_item != nullptr) {
            list2.push_back(cur_item->data);
            cur_item = cur_item->next_item;
        }
        return duo<gleipnir<T>, gleipnir<T>>(list1, list2);
    }
    else {
        return duo<gleipnir<T>, gleipnir<T>>(gleipnir<T>(), gleipnir<T>());
    }
}

template<class T>
bool gleipnir<T>::empty() {
    return (m_head == m_tail == nullptr);
}

template<class T>
bool gleipnir<T>::find(T* data) {
    item* cur_item = m_head;
    while (cur_item != nullptr) {
        if (cur_item->data == *data) return true;
        cur_item = cur_item->next_item;
    }
    return false;
}

template<class T>
T* gleipnir<T>::get() {
    return &m_head->data;
}

template<class T>
T* gleipnir<T>::find(int position) {

    if (-1 < position < m_size) {
        item* cur_item = m_head;
        for (int i = 0; i < position; i++) {
            cur_item = cur_item->next_item;
        }
        return &cur_item->data;
    }

    return nullptr;
}

gleipnir<duo<char, int>> list_count_symbols(string str) {
    gleipnir<duo<char, int>> list;
    while (!str.empty()) {
        char symbol = str[0];
        str.erase(0, 1);
        int count = 1;
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == symbol) {
                str.erase(i, 1);
                i = 0;
                count++;
            }
        }
        list.push_back(duo<char, int>(symbol, count));
    }
    return list;
}

int count_symbols(string str, char symbol) {
    int count = 0;
    for (char i : str)
        if (i == symbol) count++;
    return count;
}

template<class T>
struct tree {
    struct node {
        gleipnir<T> list;
        node* left;
        node* right;

        node(gleipnir<T> list) : list(list), left(nullptr), right(nullptr) {};

        node(gleipnir<T>* list) : list(*list), left(nullptr), right(nullptr) {};
    };

    node root;

    tree(gleipnir<T> list) : root(list) {};


    char find_element(string* s) {
        node* cur_node = &root;
        string s2 = *s;
        while (cur_node->left || cur_node->right) {
            if (s2[0] == '0') {
                s->erase(0, 1);
                s2.erase(0, 1);
                cur_node = cur_node->left;
            }
            else {
                s->erase(0, 1);
                s2.erase(0, 1);
                cur_node = cur_node->right;
            }
        }
        duo<char, int>* p = cur_node->list.get();
        return p->data1;
    }

    string find(T* e) {
        string s = "";
        node* cur_node = &root;
        while (cur_node != nullptr && cur_node->left && cur_node->right) {
            if (cur_node->left->list.find(e)) {
                s += '0';
                cur_node = cur_node->left;
            }
            else {
                s += "1";
                cur_node = cur_node->right;
            }
        }
        return s;
    }

    int center_of_list(node* n) {
        if (n->list.size() == 2)
            return 0;
        else if (n->list.size() % 2 == 0)
            return ceil(n->list.size() / 2) - 1;
        else
            return ceil(n->list.size() / 2);
    }

    void init_tree(node* n) {
        int center = center_of_list(n);
        duo<gleipnir<duo<char, int>>, gleipnir<duo<char, int>>> duo = n->list.split(
            center);

        n->left = new node(duo.data1);
        n->right = new node(duo.data2);
        if (n->list.size() != 2) {
            if (n->left->list.size() != 1)
                init_tree(n->left);
            if (n->right->list.size() != 1)
                init_tree(n->right);
        }

    };
};

string print_alphabet(string s, tree<duo<char, int>>* tree) {
    gleipnir<duo<char, int>> l = list_count_symbols(s);
    string out = "";
    string c;
    for (int i = 0; i < l.size(); i++) {
        cout << l.find(i)->data1;
        out += l.find(i)->data1;
        c = tree->find(new duo<char, int>(s[i], count_symbols(s, s[i])));
        cout << " " << c << endl;
        out += c;
    }
    return out;
}

duo<string, tree<duo<char, int>>> encode(string str) {
    gleipnir<duo<char, int>> list = list_count_symbols(str);
    tree<duo<char, int>> tree(list);
    tree.init_tree(&tree.root);
    string code = "";

    for (int i = 0; i < str.length(); i++) {
        string c = "";
        c = tree.find(new duo<char, int>(str[i], count_symbols(str, str[i])));
        code += c;
    }
    duo<string, ::tree<duo<char, int>>> duo(code, tree);
    return duo;
}

string uncode(string str, tree<duo<char, int>>* tree) {
    string s = str;
    string uncoded_str = "";
    while (!s.empty()) {
        uncoded_str += tree->find_element(&s);
    }
    return uncoded_str;
}


int main() {

    string str = "Never gonna give you up. Never gonna let you cry.";
    gleipnir<duo<char, int>> list = list_count_symbols(str);

    cout << "Input string: " << str << endl;
    string encode_str = encode(str).data1;
    tree<duo<char, int>> key = encode(str).data2;
    cout << "\nencode: " << encode_str << endl;

    cout << "uncode: " << uncode(encode_str, &key) << endl;

    cout << "Alphabet:\n";
    print_alphabet(str, &key);
   
    return 0;
}