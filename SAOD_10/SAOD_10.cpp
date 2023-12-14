#include <iostream>
#include <algorithm>

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
};

// Функция для создания нового узла
Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->height = 1; // Начальная высота нового узла равна 1
    return newNode;
}

// Функция для получения высоты поддерева
int getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

// Функция для вычисления баланса узла
int getBalance(Node* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Функция для правого поворота поддерева
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T = x->right;

    // Проворачивание
    x->right = y;
    y->left = T;

    // Обновление высоты узлов
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Функция для левого поворота поддерева
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T = y->left;

    // Проворачивание
    y->left = x;
    x->right = T;

    // Обновление высоты узлов
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Функция для вставки узла в AVL-дерево
Node* insertNode(Node* node, int data) {
    // Шаг 1: Обычная вставка узла
    if (node == nullptr)
        return createNode(data);

    if (data < node->data)
        node->left = insertNode(node->left, data);
    else if (data > node->data)
        node->right = insertNode(node->right, data);
    else // Игнорирование дубликатов
        return node;

    // Шаг 2: Обновление высоты текущего узла
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    // Шаг 3: Получение баланса узла
    int balance = getBalance(node);

    // Шаг 4: Балансировка узла, если он несбалансирован
    // Левый случай
    if (balance > 1 && data < node->left->data)
        return rotateRight(node);

    // Правый случай
    if (balance < -1 && data > node->right->data)
        return rotateLeft(node);

    // Лево-правый случай
    if (balance > 1 && data > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Право-левый случай
    if (balance < -1 && data < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    // Возврат указателя на узел (без изменений)
    return node;
}

// Функция для вывода дерева в соответствии с предложенным форматом
void printTree(Node* root, int space) {
    constexpr int COUNT = 5; // Количество пробелов между узлами

    if (root == nullptr)
        return;

    space += COUNT;

    printTree(root->right, space);

    std::cout << std::endl;
    for (int i = COUNT; i < space; ++i)
        std::cout << " ";
    std::cout << root->data << "\n";

    printTree(root->left, space);
}

// Функция для вывода узлов в порядке возрастания
void inOrderTraversal(Node* root) {
    if (root == nullptr)
        return;

    inOrderTraversal(root->left);
    std::cout << root->data << " ";
    inOrderTraversal(root->right);
}

// Тестирование программы
int main() {

    system("chcp 1251");
    Node* root = nullptr;

    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);
    root = insertNode(root, 50);
    root = insertNode(root, 25);

    std::cout << "Сбалансированное AVL-дерево: ";
    inOrderTraversal(root);

    std::cout << "\n\nВывод дерева:\n";
    printTree(root, 0);

    return 0;
}
