#include <cassert>
#include <iostream>

class Node {//узел, записываем данные и указатель на след функции

    public:
    int data;
    Node *next;//указатель на след узел
    explicit Node(int d) {//конструктор, для записывания значений в этот узел
        data = d;
        next = nullptr;
    }
};

class List {
private:
   Node* head;// указатель на узел наш

public:
    [[nodiscard]] Node * getHead() const {//возвращает указатель на наш первый узел(node-возвращаемый тип данных для того чтоб создать функцию принт)
       return head;
   }

private:
   int size;
public:
    ~List() = default;//дектруктор, очистить память

    List() : head {nullptr}, size{0} {}// ставит наши значения 0

    List(const List& a) : head(nullptr), size(0) {// копирует наш лист
        Node * last = nullptr;
        for(Node * n = a.head; n != nullptr; n = n->next)
        {
            Node * item = new Node(n->data);//данные нашего n записываем в указатель item
            if(!head)
            {
                head = item;//Если список был пуст, то мы указываем, что новый элемент (item) становится первым элементом списка
            }
            else
            {
                last->next = item;
            }
            last = item;
            ++size;
        }
    }

    List(List&& a) noexcept : size(a.size), head(a.head) {
       a.head = nullptr;//Мы просто перенаправляем указатель на данные из старого списка в новый и обнуляем старый указатель, чтобы не было ошибок.
   }

   explicit List(size_t n) : head(nullptr), size(n) {//конструктор который имеет один параметр

        Node* current = nullptr;

        for (size_t i = 0; i < n; i++) {
            Node* item = new Node(0);//создаем item

            if (!head) {
                head = item;
                current = head;
            } else {
                current->next = item;
                current = current->next;
            }
        }

    }

    List(const int a[], size_t n): head(nullptr), size(0) {//констурктор принимает 2 параметра- массив и длина
        for (size_t i = 0; i < n; ++i) {
            Node* newNode = new Node(a[i]);
            if (!head) {
                head = newNode;
            } else {
                Node* current = head;
                while (current->next) {
                    current = current->next;// ищем конец листа
                }
                current->next = newNode;//когда мы его нашли мы записываем новый элемент в конец и увеличиваем длину
            }
            ++size;
        }
   }

    void clear() {//очищаем наши данные
        while (head->next != nullptr) {//пока не устанется одного узла в списке мы удаляем все узлы
            Node * temp = head;// указатель на начало списка
            head = head->next;// делаем второй узел началом списка
            delete temp;//и первый узел удаляется

        }
        head = nullptr;
        size = 0;
    }

     int  at(int ind) {// функция для нахождения узла на определенном индексе

        if (ind < 0) {// если индекс меньше 0
            ind += size;// прибавляем наш размер списка
        }
        Node* current = head;
        if (ind < 0) {// если у нас индекс остался отрицательным
            return current->data;// значит мы возвращаем данные начало списка
        } else if (ind >= size) {// если у нас индекс больше 0, то мы возвращаем данные с конца списка

            for(int i = 0; i < size && current->next != nullptr; i++) {
                current = current->next;
            }

        }else {
            for (int i = 0; i < ind; i++) {//если наш индекс в промужке то мы переходим к этому элменту индекса и возвращем его
                current = current->next;
            }
        }

        return current->data;
    }

     void resize(size_t n) {//меняем размер( если меньше оставляем сколько нужно элементов остальное удаляем)
        if (n < size) {
            Node* temp = head;
            for (size_t i = 0; i < n - 1 && temp != nullptr; i++) {
                temp = temp->next;// ищем конец нового списка
            }
            if (temp != nullptr) {
                Node* del = temp->next;
                temp->next = nullptr;
                while (del != nullptr) {
                    Node* nextNode = del->next;
                    delete del;
                    del = nextNode;
                }
            }
        } else if (n > size) {//( а если больше то записываем в конец нули сколько нам надо )

            Node* temp = head;
            while (temp && temp->next != nullptr) {
                temp = temp->next;
            }

            for (size_t i = size; i < n; i++) {
                Node* newNode = new Node(0);
                if (temp) {
                    temp->next = newNode;
                } else {
                    head = newNode;
                }
                temp = newNode;
            }
        }
        size = n;

    }

    void assign(size_t count, int value) {//( эта функция делает наш лист по размеру каким мы хотим и делает элементы там одинаковые какие мы хотим )
        if (count > size) {
            Node* current = head;

            for (size_t i = 0; i < size && current != nullptr; ++i) {
                current->data = value;
                current = current->next;
            }

            for (size_t i = size; i < count; ++i) {
                Node* newNode = new Node(value);
                if (current) {
                    current->next = newNode;
                } else {
                    head = newNode;
                }
                current = newNode;
            }
        } else if (count < size) {
            Node* current = head;

            for (size_t i = 0; i < count; ++i) {
                current->data = value;
                current = current->next;
            }

            while (current != nullptr) {
                Node* del = current;
                current = current->next;
                delete del;
            }
        } else {
            Node* current = head;
            for (size_t i = 0; i < size && current != nullptr; ++i) {
                current->data = value;
                current = current->next;
            }
        }

        size = count;
    }

     size_t length() {
        return size;
    }

    bool empty() {
        return size == 0;
    }

     void swap(List& a) {
        std::swap(a.size, size);
        std::swap(a.head, head);
    }
};

void print(const List& a) {
    if (a.getHead() == nullptr) {
        return;
    }
    Node* current = a.getHead();
    while (current) {
        std::cout << current->data <<" ";
        current = current->next;
    }
}

int main()
{
     int array[] = {1, 4, 7, 3};

     List a(array, 4);
     assert(4 == a.length());
     assert(1 == a.at(0));
     assert(4 == a.at(1));
     assert(3 == a.at(10));
     print(a);

     List b(a);
     b.clear();
    assert(b.empty());
     List c;
    assert(c.empty());
     c.assign(3, 7);
     assert(3 == c.length());
     List d(5);
     assert(5 == d.length());
     d.resize(10);
     b.swap(d);
     assert(10 == b.length());
    assert(d.empty());
}