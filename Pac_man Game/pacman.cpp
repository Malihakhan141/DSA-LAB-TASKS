#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <queue>
#include <stack>
#include <set>
using namespace std;

const int WIDTH = 30;
const int HEIGHT = 15;

char maze[HEIGHT][WIDTH];
int foodCount = 0;

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

struct Position {
    int x, y;
};

Position player = {1, 1};
Position enemy1 = {WIDTH - 2, 1};
Position enemy2 = {WIDTH - 2, HEIGHT - 2};
Position chaser = {1, HEIGHT - 2};

bool gameOver = false;
int collisionType = 0;

void gotoXY(int x, int y) {
    COORD pos = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(console, pos);
}

bool isValid(int x, int y) {
    return x > 0 && x < WIDTH - 1 && y > 0 && y < HEIGHT - 1;
}

void setupMaze() {
    foodCount = 0;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || j == 0 || i == HEIGHT - 1 || j == WIDTH - 1)
                maze[i][j] = '#';
            else if ((i % 4 == 0 && j % 3 != 0) || (j % 6 == 0 && i % 5 != 0))
                maze[i][j] = '#';
            else {
                maze[i][j] = '.';
                foodCount++;
            }
        }
    }

    maze[player.y][player.x] = 'P';
    maze[enemy1.y][enemy1.x] = 'E';
    maze[enemy2.y][enemy2.x] = 'E';
    maze[chaser.y][chaser.x] = 'E';
    foodCount -= 4;
}

void drawMaze() {
    gotoXY(0, 0);
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            cout << maze[i][j];
        }
        cout << endl;
    }
    cout << "🍒 Food left: " << foodCount << "      ";
}

void movePlayer(int key) {
    int newX = player.x;
    int newY = player.y;

    switch (key) {
        case 72: newY--; break;
        case 80: newY++; break;
        case 75: newX--; break;
        case 77: newX++; break;
        default: return;
    }

    if (isValid(newX, newY) && maze[newY][newX] != '#') {
        if (maze[newY][newX] == '.')
            foodCount--;

        maze[player.y][player.x] = ' ';
        player.x = newX;
        player.y = newY;
        maze[player.y][player.x] = 'P';
    }
}

// Checks collision BEFORE enemy steps
bool tryMoveEnemy(Position &enemy, int nx, int ny, int type) {
    if (!isValid(nx, ny) || maze[ny][nx] == '#' || maze[ny][nx] == 'E') return false;

    if (nx == player.x && ny == player.y) {
        gameOver = true;
        collisionType = type;
        return true;
    }

    maze[enemy.y][enemy.x] = ' ';
    enemy.x = nx;
    enemy.y = ny;
    maze[enemy.y][enemy.x] = 'E';
    return true;
}

void moveRandom(Position &enemy, int type) {
    int dir = rand() % 4;
    int nx = enemy.x + dx[dir];
    int ny = enemy.y + dy[dir];
    tryMoveEnemy(enemy, nx, ny, type);
}

void moveChaser(Position &chaser, int type) {
    int bestDist = INT_MAX;
    int bestX = chaser.x, bestY = chaser.y;

    for (int i = 0; i < 4; i++) {
        int nx = chaser.x + dx[i];
        int ny = chaser.y + dy[i];
        int dist = abs(player.x - nx) + abs(player.y - ny);

        if (isValid(nx, ny) && maze[ny][nx] != '#' && maze[ny][nx] != 'E' && dist < bestDist) {
            bestDist = dist;
            bestX = nx;
            bestY = ny;
        }
    }

    tryMoveEnemy(chaser, bestX, bestY, type);
}

// Singly Linked List Node
struct Node {
    Position pos;
    Node* next;
};

Node* head = NULL;

// Function to insert at end of singly linked list
void insertAtEnd(Position pos) {
    Node* newNode = new Node{ pos, NULL };
    if (!head) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
}

// Function to display singly linked list
void displayList() {
    Node* temp = head;
    while (temp) {
        cout << "(" << temp->pos.x << ", " << temp->pos.y << ") -> ";
        temp = temp->next;
    }
    cout << "NULL\n";
}

// Doubly Linked List Node
struct DNode {
    Position pos;
    DNode* next;
    DNode* prev;
};

DNode* dHead = NULL;

// Function to insert at end of doubly linked list
void insertEnemyMovement(Position pos) {
    DNode* newNode = new DNode{ pos, NULL, NULL };
    if (!dHead) {
        dHead = newNode;
    } else {
        DNode* temp = dHead;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
        newNode->prev = temp;
    }
}

// Circular Linked List Node
struct CNode {
    string event;
    CNode* next;
};

CNode* cHead = NULL;

// Function to insert into circular linked list
void insertCircular(string e) {
    CNode* newNode = new CNode{ e, NULL };
    if (!cHead) {
        cHead = newNode;
        cHead->next = cHead;
    } else {
        CNode* temp = cHead;
        while (temp->next != cHead) temp = temp->next;
        temp->next = newNode;
        newNode->next = cHead;
    }
}

// Function to display circular linked list
void displayCircular() {
    if (!cHead) return;
    CNode* temp = cHead;
    do {
        cout << temp->event << " -> ";
        temp = temp->next;
    } while (temp != cHead);
    cout << "...\n";
}

// Stack implementation using array
Position stackArr[100];
int top = -1;

void push(Position p) {
    if (top < 99) stackArr[++top] = p;
}

Position pop() {
    if (top >= 0) return stackArr[top--];
    return { -1, -1 };
}

// Queue implementation using array
Position queueArr[100];
int front = 0, rear = 0;

void enqueue(Position p) {
    queueArr[rear++] = p;
}

Position dequeue() {
    if (front < rear) return queueArr[front++];
    return { -1, -1 };
}

// Binary Search Tree Node
struct BSTNode {
    int score;
    BSTNode* left, *right;
};

BSTNode* insertBST(BSTNode* root, int val) {
    if (!root) return new BSTNode{ val, NULL, NULL };
    if (val < root->score) root->left = insertBST(root->left, val);
    else root->right = insertBST(root->right, val);
    return root;
}

void inorder(BSTNode* root) {
    if (root) {
        inorder(root->left);
        cout << root->score << " ";
        inorder(root->right);
    }
}

// BFS for maze traversal
bool visited[HEIGHT][WIDTH];

void bfs(Position start) {
    queue<Position> q;
    q.push(start);
    visited[start.y][start.x] = true;

    while (!q.empty()) {
        Position curr = q.front(); q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];
            if (isValid(nx, ny) && !visited[ny][nx] && maze[ny][nx] != '#') {
                visited[ny][nx] = true;
                q.push({ nx, ny });
            }
        }
    }
}

// DFS for maze traversal
void dfs(Position curr) {
    visited[curr.y][curr.x] = true;
    for (int i = 0; i < 4; i++) {
        int nx = curr.x + dx[i];
        int ny = curr.y + dy[i];
        if (isValid(nx, ny) && !visited[ny][nx] && maze[ny][nx]
!= '#') {
            dfs({ nx, ny });
        }
    }
}

void displayEndMessage() {
    gotoXY(0, HEIGHT + 2);
    if (foodCount == 0) {
        cout << "\n🎉 You Win! Final Score: 0";
    } else {
        switch (collisionType) {
            case 1: cout << "\n💥 Game Over! Caught by Enemy 1"; break;
            case 2: cout << "\n💥 Game Over! Caught by Enemy 2"; break;
            case 3: cout << "\n💥 Game Over! Caught by Chaser"; break;
        }
        cout << "\nFinal Score: " << foodCount;
    }
}

int main() {
    srand(time(0));
    setupMaze();

    while (!gameOver && foodCount > 0) {
        if (_kbhit()) {
            int key = _getch();
            movePlayer(key);
        }

        moveRandom(enemy1, 1);
        moveRandom(enemy2, 2);
        moveChaser(chaser, 3);

        drawMaze();
        Sleep(120);
    }

    drawMaze();
    displayEndMessage();
    gotoXY(0, HEIGHT + 5);
    return 0;
}

