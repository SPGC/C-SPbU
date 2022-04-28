#ifndef NODE
#define NODE

class Node
{
private:
    Node* child0;
    Node* child1;
    int amount;
    unsigned char value;
    bool isLeaf;
    int code;
    int codeLength;
public:
    Node(Node *, Node *);
    Node(unsigned char, int);
    ~Node();
    Node * getChild0() const;
    Node * getChild1() const;
    int getAmount() const;
    unsigned char getValue() const;
    bool getIsLeaf() const;
    int getCode() const;
    int getCodeLength() const;
    void increaseAmount();
    void setCodeLength(int);
    void setCode(int);
    void setChild1(Node *);
    void setChild0(Node *);
};

bool operator<(const Node& n1, const Node& n2);
#endif