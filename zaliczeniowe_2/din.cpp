#include <bits/stdc++.h>
using namespace std;
using uid = uniform_int_distribution<int>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define X first
#define Y second
#define N 1000007

int n, m;
int j, k, l;
char c;

struct Node {
    int lazy, size, priority;
    Node *l, *r;
    char left_nucleotide, right_nucleotide, nucleotide;
    int left_range, mid_range, right_range, max_range;

    Node* attach(Node *left, Node *right) {

        this->l = left;
        this->r = right;

        this->size = 1;
        this->left_nucleotide = this->nucleotide;
        this->right_nucleotide = this->nucleotide;
        this->max_range = 1;
        this->left_range = 1;
        this->mid_range = 1;
        this->right_range = 1;

        if (l != nullptr) {
            this->l->push();
            size += l->size;
            this->left_nucleotide = l->left_nucleotide;
            this->left_range = l->left_range;
            this->max_range = max(this->max_range, l->max_range);
        }
        if (r != nullptr) {
            this->r->push();
            size += r->size;
            this->right_nucleotide = r->right_nucleotide;
            this->right_range = r->right_range;
            this->max_range = max(this->max_range, r->max_range);
        }

        bool LM_equals = (l != nullptr && l->right_nucleotide == this->nucleotide);
        bool MR_equals = (r != nullptr && this->nucleotide == r->left_nucleotide);
        bool L_mono = (l != nullptr && l->max_range == l->size);
        bool R_mono = (r != nullptr && r->max_range == r->size);


        if (l != nullptr && r != nullptr) {
            if (LM_equals) {
                this->mid_range += l->right_range;
                if (L_mono) {
                    this->left_range++;
                    if (MR_equals) {
                        this->left_range += r->left_range;
                    }
                }
            }
            if (MR_equals) {
                this->mid_range += r->left_range;
                if (R_mono) {
                    this->right_range++;
                    if (LM_equals) {
                        this->right_range += l->right_range;
                    }
                }
            }
        }
        else if (l != nullptr) {
            if (LM_equals) {
                this->mid_range += l->right_range;
                this->right_range += l->right_range;
                if (L_mono) {
                    this->left_range++;
                }
            }
        }
        else if (r != nullptr) {
            if (MR_equals) {
                this->mid_range += r->left_range;
                this->left_range += r->left_range;
                if (R_mono) {
                    this->right_range++;
                }
            }
        }

        this->max_range = max({this->left_range, this->max_range, this->right_range, this->mid_range});

        return this;
    }

    Node* push () {
        if (lazy) {
            lazy = 0;

            swap(left_range, right_range);
            swap(left_nucleotide, right_nucleotide);
            swap(l, r);

            if (l != nullptr) {
                l->lazy ^= 1;
            }
            if (r != nullptr) {
                r->lazy ^= 1;
            }
        }
        return this;
    }
};

Node* merge(Node *a, Node *b) {
    if (a == nullptr) {
        return b;
    }
    if (b == nullptr) {
        return a;
    }

    a->push();
    b->push();

    if (a->priority > b->priority) {
        return a->attach(a->l, merge(a->r, b));
    }
    return b->attach(merge(a, b->l), b->r);
}

// count nodes will be in the first member of returned pair
pair<Node*, Node*> split(Node* node, int count) {
    if (count == 0) {
        return { nullptr, node };
    }

    node->push();
    int l_size = (node->l == nullptr) ? 0 : node->l->size;

    if (count <= l_size) {
        auto post_split = split(node->l, count);
        return { post_split.X, node->attach(post_split.Y, node->r) };
    }

    auto post_split = split(node->r, count - l_size - 1);
    return { node->attach(node->l, post_split.X), post_split.Y };
}

struct Treap {
    Node *root;
    char DNA[N];
    int priorities[N];

    Node* build(int x, int y) {
        if (y < x) {
            return nullptr;
        }

        int max_priority_ID = x;
        for (int i = x + 1; i <= y; i++) {
            if (priorities[i] > priorities[max_priority_ID]) {
                max_priority_ID = i;
            }
        }

        Node *node = new Node();

        node->nucleotide = DNA[max_priority_ID];
        node->priority = priorities[max_priority_ID];

        return node->attach(build(x, max_priority_ID - 1), build(max_priority_ID + 1, y));
    }

    void init() {
        for (int i = 1; i <= n; i++) {
            cin >> DNA[i];
            priorities[i] = uid(INT_MIN, INT_MAX)(rng);
        }
        root = build(1, n);
    }

    void reverse () {
        cin >> j >> k;
        auto left_rev = split(root, j - 1);
        auto rev_right = split(left_rev.Y, k - j + 1);
        rev_right.X->lazy ^= 1;
        root = merge(left_rev.X, merge(rev_right.X, rev_right.Y));
    }

    void move () {
        cin >> j >> k >> l;
        auto left_move = split(root, j - 1);
        auto move_right = split(left_move.Y, k - j + 1);
        auto w = merge(left_move.X, move_right.Y);
        auto wLeft_wRight = split(w, l - 1);
        root = merge(wLeft_wRight.X, merge(move_right.X, wLeft_wRight.Y));
    }

    void query () {
        cin >> j >> k;
        auto left_query = split(root, j -  1);
        auto query_right = split(left_query.Y, k - j + 1);
        cout << query_right.X->max_range << "\n";
        root = merge(left_query.X, merge(query_right.X, query_right.Y));
    }

};

Treap T;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;

    T.init();

    for (int i = 0; i < m; i++) {
        cin >> c;
        c == 'O' ? T.reverse() : c == 'P' ? T.move() : T.query();
    }

    return 0;
}