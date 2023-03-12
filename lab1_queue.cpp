#include <iostream>
#include <cassert>
#include <sstream>

struct Node
{
    Node(int data)
    : val(data), next(nullptr)
    {
    }
    int val;
    Node *next;
};

class Queue
{
public:
    Queue()
    : head(nullptr), tail(nullptr)
    {
    }
    
    ~Queue()
    {
        while (!IsEmpty())
            Dequeue();
    }
    
    void Enqueue(int data)
    {
        Node *node = new Node(data);
        if (IsEmpty())
        {
            head = tail = node;
            return;
        }
        tail->next = node;
        tail = node;
    }
    
    int Dequeue()
    {
        if (IsEmpty())
            return -1;
        
        int tmpData = head->val;
        Node *tmpNode = head;
        
        head = head->next;
        if (head == nullptr)
        {
            tail = nullptr;
        }
        
        delete tmpNode;
        return tmpData;
    }
    
    bool IsEmpty()
    {
        return head == nullptr && tail == nullptr;
    }
private:
    Node *head;
    Node *tail;
};

void testLogic()
{
    Queue queue;
    int sampleCount = 100;
    
    assert(queue.IsEmpty());
    
    for (int i = 0; i < sampleCount; i++)
        queue.Enqueue(i);
    
    assert(!queue.IsEmpty());
    
    for (int i = 0; i < sampleCount; i++)
    {
        assert(i == queue.Dequeue());
    }
    
    assert(queue.IsEmpty());
}

void run(std::istream &input, std::ostream &output)
{
    Queue queue;
    
    int n = 0;
    input >> n;
    
    for (int i = 0; i < n; i++)
    {
        int op = 0, val = 0;
        input >> op >> val;
        switch (op)
        {
            case 2:
            {
                // dequeue
                int tmpVal = queue.Dequeue();
                if (tmpVal != val)
                {
                    output << "NO\n";
                    return;
                }
                break;
            }
            case 3:
            {
                // enqueue
                queue.Enqueue(val);
                break;
            }
        }
    }
    output << "YES\n";
}

void testQueue()
{
    {
        std::stringstream input, output;
        input << "3\n";
        input << "3 10\n";
        input << "3 20\n";
        input << "2 10\n";
        run(input, output);
        assert(output.str() == "YES\n");
    }
    {
        std::stringstream input, output;
        input << "3\n";
        input << "3 10\n";
        input << "3 20\n";
        input << "2 1\n";
        run(input, output);
        assert(output.str() == "NO\n");
    }
}

int main(int argc, const char * argv[]) {
    //testLogic();
    run(std::cin, std::cout);
    //testQueue();
    return 0;
}
