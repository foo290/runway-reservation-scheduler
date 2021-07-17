#include <iostream>
#include <cmath>
#include <queue>

using namespace std;

namespace bst {
    class Node {
    public:
        float data;
        int subtreeSize;
        Node *left;
        Node *right;
        Node *parent;
    };

    class BST {
    private:
        Node *root = nullptr;
        float kMin = 0.0;
        bool deleted = false;


        static Node *getNode(float data) {
            Node *node = new Node();
            node->data = data;
            node->subtreeSize = 1;
            node->right = nullptr;
            node->left = nullptr;
            node->parent = nullptr;
            return node;
        }

        Node *insert(Node *rootNode, Node *dataNode) {
            if (rootNode == nullptr) {
                rootNode = dataNode;
                return rootNode;
            }
            if (kMinCheck(rootNode->data, dataNode->data)) {
                if (rootNode->data < dataNode->data) {
                    Node *newRoot = insert(rootNode->right, dataNode);
                    if (newRoot != nullptr) {
                        rootNode->subtreeSize += 1;
                        rootNode->right = newRoot;
                        return rootNode;
                    } else return nullptr;
                } else {
                    Node *newRoot = insert(rootNode->left, dataNode);
                    if (newRoot != nullptr) {
                        rootNode->subtreeSize += 1;
                        rootNode->left = newRoot;
                        return rootNode;
                    } else return nullptr;
                }
            } else {
                return nullptr;
            }
        }

        static Node *search(Node *rootNode, Node *targetNode) {
            if (rootNode == nullptr) return rootNode;
            if (rootNode->data == targetNode->data) return rootNode;
            if (rootNode->data > targetNode->data) return search(rootNode->left, targetNode);
            else return search(rootNode->right, targetNode);
        }

        Node *deleteNode(Node *rootNode, float data) {
            if (rootNode == nullptr) {
                return rootNode;
            } else if (rootNode->data > data) {
                rootNode->left = deleteNode(rootNode->left, data);
            } else if (rootNode->data < data) {
                rootNode->right = deleteNode(rootNode->right, data);
            } else {
                // case - 1
                if (rootNode->left == nullptr && rootNode->right == nullptr) {
                    delete rootNode;
                    deleted = true;
                    rootNode = nullptr;
                }
                    // case - 2
                else if (rootNode->left == nullptr) {
                    Node *right = rootNode->right;
                    delete rootNode;
                    rootNode = right;
                    deleted = true;
                }
                    // case - 3
                else if (rootNode->right == nullptr) {
                    Node *left = rootNode->left;
                    delete rootNode;
                    rootNode = left;
                    deleted = true;
                } else {
                    Node *temp = findMinNode(rootNode->right);
                    rootNode->data = temp->data;
                    Node *modifiedRoot = deleteNode(rootNode->right, temp->data);
                    rootNode->right = modifiedRoot;
                }
            }
            if (rootNode != nullptr && deleted) rootNode->subtreeSize -= 1;
            return rootNode;
        }

    public:

        explicit BST(float interval) {
            kMin = interval;
        }

        Node *searchData(float data) {
            return search(root, getNode(data));
        }

        static Node *findMinNode(Node *root) {
            Node *current = root;
            while (current->left != nullptr) {
                current = root->left;
            }
            return current;
        }

        Node *deleteData(float data, bool resetDelete = true) {
            Node *afterDelete = deleteNode(root, data);
            if (resetDelete) deleted = false;
            return afterDelete;
        }

        bool getDeleteCounter() const {
            return deleted;
        }

        void resetDeleteCounter() {
            deleted = false;
        }

        bool kMinCheck(float lastTime, float arrivalTime) const {
            return kMin < fabsf(lastTime - arrivalTime);
        }

        Node *getRoot() {
            return root;
        }

        bool insertData(float data) {
            Node *modifiedRoot = insert(root, getNode(data));
            if (modifiedRoot != nullptr) {
                root = modifiedRoot;
                return true;
            }
            return false;
        }

        void printLevelOrder(Node* rootNode){
            if (rootNode == nullptr) return;
            queue<Node*> discovery_queue;
            discovery_queue.push(rootNode);

            while (!discovery_queue.empty()){
                Node* frontNode = discovery_queue.front();
                cout<<frontNode->data<<" ";
                discovery_queue.pop();
                if (frontNode->left) discovery_queue.push(frontNode->left);
                if (frontNode->right) discovery_queue.push(frontNode->right);
            }
        }

        void printInOrder(Node *rootNode) {
            if (rootNode == nullptr) return;
            printInOrder(rootNode->left);
            cout << rootNode->data << " ";
            printInOrder(rootNode->right);
        }

        void printPreOrder(Node *rootNode) {
            if (rootNode == nullptr) return;
            cout << rootNode->data << " ";
            printPreOrder(rootNode->left);
            printPreOrder(rootNode->right);
        }

        void printPostOrder(Node *rootNode) {
            if (rootNode == nullptr) return;
            printPostOrder(rootNode->left);
            printPostOrder(rootNode->right);
            cout << rootNode->data << " ";
        }
    };

}


class ReservationScheduler : public bst::BST {
private:

    template<typename T>
    void log(T prefix, T msg, bool raw = false) {
        if (raw) {
            cout << "[" << prefix << "]" << " : " << msg;
            return;
        }
        cout << "[" << prefix << "]" << " : " << msg << endl;
    }

public:
    explicit ReservationScheduler(float interval) : bst::BST(interval) {}

    bool requestLanding(float arrivalTime) {
        if (insertData(arrivalTime)) {
            log("Success", "Landing is successfully scheduled at : ", true);
            cout << arrivalTime << endl;
            return true;
        } else {
            log("BUSY", "Runway is busy at the given time : ", true);
            cout << arrivalTime << endl;
            return false;
        }
    }

    int getScheduledLandings(float uptoTime) {
        bst::Node *node = searchData(uptoTime);
        if (node != nullptr) {
            log("Scheduled", "The number of landings scheduled are : ", true);
            cout << node->subtreeSize << endl;
        } else {
            log("ERROR", "This time is not scheduled");
        }
        return 0;
    }

    void landingComplete(float data) {
        deleteData(data, false);
        if (getDeleteCounter()) {
            log("COMPLETE", "Landing removed from scheduled landings for time : ", true);
            cout << data << endl;
        } else {
            log("ERROR", "There are no landings scheduled for time : ", true);
            cout << data << endl;
        }
        resetDeleteCounter();
    }
};


int main() {
    float kTime = 3.0;
    ReservationScheduler reservationScheduler = ReservationScheduler(kTime);

    int choice = 0;
    float lTime = 0.0;

    while (true){
        cout<< "\nChoose :\n"
               "1: to schedule a landing.\n"
               "2: to get number of landings scheduled\n"
               "3: to delete a scheduled landing, marking as complete\n"
               "4: to print level order\n"
               "5: to print pre order\n"
               "6: to print In order\n"
               "7: to print post order\n"
               "0: to quit"<<endl;
        cout<<"\nChoice > ";cin >> choice;
        switch (choice) {
            case 0:
                return 0;
            case 1:
                cout<<"Insert the time you would like to schedule a landing for : "; cin >>lTime;
                if (lTime <= 0) cout<<"Time must be greater than 0 and integer";
                else reservationScheduler.requestLanding(lTime);
                break;
            case 2:
                cout<<"Insert the time you would like to get all number of landing for : "; cin >>lTime;
                if (lTime <= 0) cout<<"Time must be greater than 0 and integer";
                else reservationScheduler.getScheduledLandings(lTime);
                break;
            case 3:
                cout<<"Insert the time you would like to delete : "; cin >>lTime;
                if (lTime <= 0) cout<<"Time must be greater than 0 and integer";
                else reservationScheduler.landingComplete(lTime);
                break;
            case 4:
                cout<<"Level order : ";
                reservationScheduler.printLevelOrder(reservationScheduler.getRoot());
                break;
            case 5:
                cout<<"Pre order : ";
                reservationScheduler.printPreOrder(reservationScheduler.getRoot());
                break;
            case 6:
                cout<<"In order : ";
                reservationScheduler.printInOrder(reservationScheduler.getRoot());
                break;
            case 7:
                cout<<"Post order : ";
                reservationScheduler.printPostOrder(reservationScheduler.getRoot());
                break;

            default:
                cout<<"Sorry the input was not valid"<<endl;
                break;
        }
    }
}

