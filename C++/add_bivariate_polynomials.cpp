#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int coeff, px, py;
    Node *next;

    Node(int c, int x, int y) : coeff(c), px(x), py(y), next(nullptr) {}
};

class Polynomial {
private:
    Node *head;

    // Helper function to push a term into the polynomial list
    void push(int coeff, int px, int py) {
        // Create a new node
        Node *newNode = new Node(coeff, px, py);
        
        // If the list is empty or the new term should be placed at the head
        if (!head || (head->px < px || (head->px == px && head->py < py))) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node *current = head;
        while (current->next && (current->next->px > px || (current->next->px == px && current->next->py > py))) {
            current = current->next;
        }

        // Insert newNode in the sorted order
        newNode->next = current->next;
        current->next = newNode;
    }

public:
    Polynomial() : head(nullptr) {}

    // Function to add a term to the polynomial
    void addTerm(int coeff, int px, int py) {
        push(coeff, px, py);
    }

    // Function to add two polynomials
    Polynomial add(Polynomial &other) {
        Polynomial result;
        Node *currA = this->head;
        Node *currB = other.head;

        while (currA || currB) {
            if (!currA) {
                result.push(currB->coeff, currB->px, currB->py);
                currB = currB->next;
            } else if (!currB) {
                result.push(currA->coeff, currA->px, currA->py);
                currA = currA->next;
            } else if (currA->px == currB->px && currA->py == currB->py) {
                int newCoeff = currA->coeff + currB->coeff;
                if (newCoeff != 0) {
                    result.push(newCoeff, currA->px, currA->py);
                }
                currA = currA->next;
                currB = currB->next;
            } else if (currA->px > currB->px || (currA->px == currB->px && currA->py > currB->py)) {
                result.push(currA->coeff, currA->px, currA->py);
                currA = currA->next;
            } else {
                result.push(currB->coeff, currB->px, currB->py);
                currB = currB->next;
            }
        }
        return result;
    }

    // Function to display the polynomial
    void display() {
        Node *temp = head;
        while (temp) {
            cout << temp->coeff << " " << temp->px << " " << temp->py << "\n";
            temp = temp->next;
        }
    }

    // Function to count non-zero terms
    int countNonZeroTerms() {
        int count = 0;
        Node *temp = head;
        while (temp) {
            if (temp->coeff != 0) count++;
            temp = temp->next;
        }
        return count;
    }
};

int main() {
    int m, n;
    cin >> m >> n;

    if (m > 10 || n > 10) {
        cout << "Number of terms exceeds the MAXSIZE limit\n";
        return 0;
    }

    Polynomial polyA, polyB;

    for (int i = 0; i < m; ++i) {
        int coeff, px, py;
        cin >> coeff >> px >> py;
        polyA.addTerm(coeff, px, py);
    }

    for (int i = 0; i < n; ++i) {
        int coeff, px, py;
        cin >> coeff >> px >> py;
        polyB.addTerm(coeff, px, py);
    }

    Polynomial result = polyA.add(polyB);
    cout << result.countNonZeroTerms() << "\n";
    result.display();

    return 0;
}
