#include <iostream>

using namespace std;

class Error {};
Error visitingEmptyList; 

// error instances

// a data structure used to dispose polynomials, integrate several functions

class Poly {
private:
    struct node {
        int coeff;
        int power;
        unsigned int index;
        node* next;
    };
    node* head;
    bool isEmpty() const;
    void copyAll(node* source);
        // REQUIRES: source non empty

    void removeAll();
    node* highestLessThan(int power) const;
        // return the term with the highest order smaller than the entry
        // if there is no term corresponds, return nullptr.
    node* highestTerm() const;
        // EFFECTS: return the term of highest power.
public:
    Poly();
    Poly(const Poly& source);
    void insertFront(int coeff, int power);
        // MODIFIES: this
        // EFFECTS: insert (coeff,power) at the front of list
    int order() const;
        // REQUIRES: is not empty
        // EFFECTS: return the order of this polynomial. (Highest power in the polynomial)
    void mergeTerms();
        // EFFECTS: merge the terms of same orders.
    void sort(); 
        // REQUIRES: there is no term with the same power
        // sort the polynomial linked list by the power: 0,1,2... in this order
    void insertInOrder(int coeff, int power);
        // REQUIRES: the list is already in order (increasing power)
        // MODIFIES: this
        // EFFECTS: insert the term (coeff, power) into the polynomial in the position
        // it should belongs to.
    void print();
    void removeByIndex(unsigned int index);
        // remove the index-th node
        // if that does not exist, do nothing
    unsigned int length();
    Poly& operator=(const Poly& source);
    friend Poly operator+(const Poly& lhs, const Poly& rhs);
    friend Poly operator*(const Poly& lhs, const Poly& rhs);
    Poly& operator+=(const Poly& rhs);
    Poly& operator*=(const Poly& rhs);
    ~Poly();
};

Poly operator+(const Poly& lhs, const Poly& rhs) {
    Poly ans;
    Poly::node* curr = lhs.head;
    while (curr != nullptr) {
        ans.insertFront(curr->coeff, curr->power);
        curr = curr->next;
    }
    curr = rhs.head;
    while (curr != nullptr) {
        ans.insertFront(curr->coeff, curr->power);
        curr = curr->next;
    }
    ans.sort();
    ans.mergeTerms();
    return ans;
}

Poly operator*(const Poly& lhs, const Poly& rhs) {
    Poly ans;
    if (lhs.isEmpty() || rhs.isEmpty())
        throw visitingEmptyList;
    Poly::node* curr1 = lhs.head;
    Poly::node* curr2 = rhs.head;
    while (curr1 != nullptr) {
        curr2 = rhs.head;
        while (curr2 != nullptr) {
            ans.insertFront(curr2->coeff*curr1->coeff, curr2->power+curr1->power);
            curr2 = curr2->next;
        }
        curr1 = curr1->next;
    }
    ans.sort();
    ans.mergeTerms();
    return ans;
}

Poly::Poly() : head(nullptr) {
}

bool Poly::isEmpty() const {
    return (head == nullptr);
}

void Poly::removeAll() {
    while(!isEmpty()) {
        node* victim = head;
        head = head->next;
        delete victim;
    }
}

void Poly::copyAll(node *source) {
    if (source == nullptr) {
        head = nullptr;
    } else {
        if (source->next != nullptr)
            copyAll(source->next);
        insertFront(source->coeff, source->power);
    }
}

Poly::Poly(const Poly& source) : head(nullptr) {
    copyAll(source.head);
}

void Poly::insertFront(int coeff, int power) {
    node *curr = new node;
    curr->coeff = coeff;
    curr->power = power;
    if (head != nullptr)
        curr->index = head->index + 1;
    else
        curr->index = 0;
    curr->next = head;
    head = curr;   
}

int Poly::order() const {
    if (isEmpty()) {
        throw visitingEmptyList;
    }
    int order = head->power;
    node* curr = head;
    while (curr->next != nullptr) {
        curr = curr->next;
        if (curr->power > order)
            order = curr->power;
    }
    return order;
}

Poly::node* Poly::highestLessThan(int power) const {
    node* ans = nullptr;
    node* curr = head;
    while (curr != nullptr) {
        if (curr->power <= power) {
            ans = curr;
            break;
        }
    }
    if (ans == nullptr) return ans; // not found
    else { // curr has the power smaller than the entry
        int max = curr->power;
        while (curr->next != nullptr) {
            curr = curr->next;
            if (curr->power > max && curr->power <= power) {
                max = curr->power;
                ans = curr;
            }
        }
        return ans;
    }
}

Poly::node* Poly::highestTerm() const {
    int order1 = order();
    return highestLessThan(order1);
}



void Poly::removeByIndex(unsigned int i) {
    node* curr = head;
    node* prev = nullptr;
    bool start = false;
    while (curr != nullptr) {
        if (curr->index == i) {
            if (prev == nullptr) {
                head = curr->next;
                delete curr;
                curr = nullptr;
                break;
            } else {
                prev->next = curr->next;
                delete curr;
                curr = nullptr;
                node* curr_ = head;
                while (curr_ != nullptr && curr_->index >= prev->index) {
                    curr_->index--;
                    curr_ = curr_->next;
                } // keep the index invariant
                break;
            }
        }
        curr = curr->next;
        if (!start) {
            start = true;
            prev = head;
        } else 
            prev = prev->next;
    }
}

unsigned int Poly::length() {
    unsigned int counter = 0;
    node* curr = head;
    while (curr != nullptr) {
        counter++;
        curr = curr->next;
    }
    return counter;
}



void Poly::sort() {
    Poly* newPoly = new Poly;
    unsigned int len = length();
    for (unsigned int counter = 0; counter < len; counter++) {
        node* highest = highestTerm();
        unsigned int index = highest->index;
        newPoly->insertFront(highest->coeff, highest->power);
        removeByIndex(index);
    }
    removeAll();
    copyAll(newPoly->head);
}


void Poly::mergeTerms() {
    if (isEmpty() || head->next == nullptr)
        return; // 0 term or 1 term will have no terms to merge.
    unsigned int i = 0;
    node* curr = head;
    while (curr != nullptr) {
        node* curr_ = curr->next;
        while (curr_ != nullptr) {
            if (curr_->power == curr->power) {
                curr->coeff += curr_->coeff;
                node* tmp = curr_->next;
                removeByIndex(curr_->index);
                curr_ = tmp;
            } else {
                curr_ = curr_->next;
            }
        }
        curr = curr->next;
    }
}


void Poly::print() {
    node* curr = head;
    while (curr != nullptr) {
        cout << curr->coeff << "x^" << curr->power;
        if (curr->next != nullptr) {
            cout << " + ";
        } else {
            cout << endl;
        }
        curr = curr->next;
    }
}



Poly& Poly::operator=(const Poly& source) {
    if (this != &source)
        removeAll();
    copyAll(source.head);
    return *this;
}

Poly::~Poly() {
    removeAll();
}


int main() {
    Poly poly;
    poly.insertFront(2,1);
    poly.insertFront(3,2);
    poly.insertFront(1,3);
    poly.insertFront(4,4);
    Poly poly1, poly2(poly);
    poly1.insertFront(2,3);
    poly1.insertFront(4,2);
    poly.print(); poly1.print();
    poly2 = poly1 * poly;
    poly2.print();
    return 0;
}