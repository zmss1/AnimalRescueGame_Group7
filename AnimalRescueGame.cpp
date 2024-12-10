#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

// Class to represent an Animal
class Animal {
public:
    string name;
    string species;
    int rescuePriority;

    Animal(string name, string species, int priority) {
        this->name = name;
        this->species = species;
        this->rescuePriority = priority;
    }

    void print() {
        cout << name << " (" << species << ") - Priority: " << rescuePriority << " ";
        // Display species emoji based on the species
        if (species == "dog") {
            cout << "🐶\n";
        } else if (species == "cat") {
            cout << "🐱\n";
        } else if (species == "rabbit") {
            cout << "🐰\n";
        } else {
            cout << "Species not recognized\n";
        }
    }
};

// Binary Search Tree Node
class BSTNode {
public:
    Animal* animal;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Animal* animal) {
        this->animal = animal;
        left = right = nullptr;
    }
};

// Binary Search Tree (BST) for storing animals in sorted order by name
class BinarySearchTree {
private:
    BSTNode* root;

    void insert(BSTNode*& node, Animal* animal) {
        if (node == nullptr) {
            node = new BSTNode(animal);
        } else if (animal->name < node->animal->name) {
            insert(node->left, animal);
        } else {
            insert(node->right, animal);
        }
    }

    BSTNode* search(BSTNode* node, const string& name) {
        if (node == nullptr || node->animal->name == name) {
            return node;
        } else if (name < node->animal->name) {
            return search(node->left, name);
        } else {
            return search(node->right, name);
        }
    }

    void inOrderTraversal(BSTNode* node, vector<Animal*>& animals) {
        if (node != nullptr) {
            inOrderTraversal(node->left, animals);
            animals.push_back(node->animal);
            inOrderTraversal(node->right, animals);
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(Animal* animal) {
        insert(root, animal);
    }

    BSTNode* search(const string& name) {
        return search(root, name);
    }

    vector<Animal*> inOrderTraversal() {
        vector<Animal*> animals;
        inOrderTraversal(root, animals);
        return animals;
    }
};

// Max Heap for prioritizing rescue
class MaxHeap {
private:
    vector<Animal*> heap;

    void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heap[index]->rescuePriority > heap[parentIndex]->rescuePriority) {
                swap(heap[index], heap[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int leftChild, rightChild, largest;
        while (index < heap.size()) {
            leftChild = 2 * index + 1;
            rightChild = 2 * index + 2;
            largest = index;

            if (leftChild < heap.size() && heap[leftChild]->rescuePriority > heap[largest]->rescuePriority) {
                largest = leftChild;
            }

            if (rightChild < heap.size() && heap[rightChild]->rescuePriority > heap[largest]->rescuePriority) {
                largest = rightChild;
            }

            if (largest != index) {
                swap(heap[index], heap[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

public:
    void insert(Animal* animal) {
        heap.push_back(animal);
        heapifyUp(heap.size() - 1);
    }

    Animal* removeMax() {
        if (heap.empty()) return nullptr;
        Animal* maxAnimal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return maxAnimal;
    }

    Animal* peekMax() {
        return heap.empty() ? nullptr : heap[0];
    }
};

// Game Simulation
void animalRescueGame() {
    BinarySearchTree bst;
    MaxHeap maxHeap;

    cout << "\n=======================|🐾 Animal Rescue Game 🐾|=======================\n";
    cout << "\n🦸 Welcome to Animal Rescue Adventure - A Tale of Priority and Care! 🦸\n";

    while (true) {
        cout << "\n";
        cout << "Choose an action:";
        cout << "[ 1 ] 🐾 Rescue a new animal\n";
        cout << "[ 2 ] 🕵️‍♀️ Search for an animal\n";
        cout << "[ 3 ] 📋 View all rescued animals (BST)\n";
        cout << "[ 4 ] 🏡 Adopt an animal (remove from BST) \n";
        cout << "[ 5 ] 🐾 View top priority animal (Heap)\n";
        cout << "[ 6 ] ❤️‍🩹 Adopt a priority animal (remove from Heap)\n";
        cout << "[ 7 ] ❌ Exit\n";
        cout << "Choose an option (1-7): ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            string name, species;
            int priority;
            cout << "✯ Enter animal's name: ";
            cin >> name;
            cout << "✯ Enter species (dog 🐶, cat 🐱, rabbit 🐰): ";
            cin >> species;
            cout << "✯ Enter rescue priority (1-10, 10 being most urgent): ";
            cin >> priority;

            Animal* animal = new Animal(name, species, priority);
            bst.insert(animal);
            maxHeap.insert(animal);
            cout << name << " has been rescued!❤️🎉\n";

        } else if (choice == 2) {
            string name;
            cout << "✯ Enter the name of the animal to search: ";
            cin >> name;

            BSTNode* result = bst.search(name);
            if (result) {
                cout << "Found " << result->animal->name << " in the rescue system!🐾🎉\n";
            } else {
                cout << "No animal found with the name " << name << " 💔\n";
            }

        } else if (choice == 3) {
            vector<Animal*> animals = bst.inOrderTraversal();
            cout << "\n📋 All rescued animals:\n";
            for (Animal* animal : animals) {
                animal->print();
            }

        } else if (choice == 4) {
            string name;
            cout << "✯ Enter the name of the animal to adopt: ";
            cin >> name;

            BSTNode* result = bst.search(name);
            if (result) {
                cout << result->animal->name << " has been adopted! Thank you for giving them a loving home! 🏡💞\n";
            } else {
                cout << "No animal found with the name " << name << " 💔\n";
            }

        } else if (choice == 5) {
            Animal* maxAnimal = maxHeap.peekMax();
            if (maxAnimal) {
                cout << "The top priority animal is:  ";
                maxAnimal->print();
            } else {
                cout << "No animals in the priority queue.💔\n";
            }

        } else if (choice == 6) {
            Animal* adoptedAnimal = maxHeap.removeMax();
            if (adoptedAnimal) {
                cout << adoptedAnimal->name << " has been adopted due to priority!💖🎉\n";
            } else {
                cout << "No animals in the priority queue. 🐾💔\n";
            }

        } else if (choice == 7) {
            cout << "✨🐾 Thank you for playing the Animal Rescue Game!  Have a pawsome day! 🐾✨\n";
            break;

        } else {
            cout << "⚠️ Invalid choice. Please try again.\n";
        }
    }
}

// Main function to start the game
int main() {
    animalRescueGame();
    return 0;
}
