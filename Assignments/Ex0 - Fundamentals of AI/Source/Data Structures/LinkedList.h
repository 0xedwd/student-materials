

// LinkedList class should go in the "ufl_cap4053::fundamentals" namespace!
namespace ufl_cap4053
{
    namespace fundamentals
    {

        template <typename T>
        class LinkedList
        {
        private:
            struct Node
            {
                T data;
                Node *next, *prev;

                Node(const T &d, Node *n = nullptr, Node *p = nullptr) : data(d), next(n), prev(p) {}
            };

            Node *head;
            Node *tail;
            int size;

        public:
            /*****************************************************************************************/
            /*****************************************************************************************/
            /*                                      ITERATOR CLASS                                   */
            /*****************************************************************************************/
            /*****************************************************************************************/
            class Iterator
            {
            public:
                Node *current;
                Iterator(Node *curr) : current(curr) {}

                // returns the element the iterator is pointing to
                T operator*() const { return current->data; }

                // moves the iterator to the next element
                Iterator &operator++()
                {
                    if (current != nullptr)
                        current = current->next;

                    return *this;
                }

                // returns true if the iterator is pointing to the same element as the other iterator
                bool operator==(const Iterator &other) { return current == other.current; }

                // returns true if the iterator is not pointing to the same element as the other iterator
                bool operator!=(const Iterator &other) { return current != other.current; }
            };

            LinkedList<T>() : head(nullptr), tail(nullptr), size(0) {}
            ~LinkedList<T>() { clear(); }

            /*****************************************************************************************/
            /*****************************************************************************************/
            /*                                      ITERATORS                                        */
            /*****************************************************************************************/
            /*****************************************************************************************/
            // return iterator pointing to the beginning of the list
            Iterator begin() const { return Iterator(head); }

            // return iterator pointing to the end of the list
            Iterator end() const { return Iterator(tail->next); }

            /*****************************************************************************************/
            /*****************************************************************************************/
            /*                                      BOOLEANS                                         */
            /*****************************************************************************************/
            /*****************************************************************************************/

            // return true if the list is empty
            bool isEmpty() const { return size == 0; }
            // returns true if the list contains node->data == element

            bool contains(const T &element) const
            {
                Node *node = head;
                while (node != nullptr)
                {
                    if (node->data == element)
                        return true;
                    node = node->next;
                }
                return false;
            }

            /*****************************************************************************************/
            /*****************************************************************************************/
            /*                                      GETTERS                                          */
            /*****************************************************************************************/
            /*****************************************************************************************/

            // returns the number of elements in the list
            int getSize() const { return size; }

            // returns the first element in the list
            T getFront() const { return head->data; }

            // returns the last element in the list
            T getBack() const { return tail->data; }

            /*****************************************************************************************/
            /*****************************************************************************************/
            /*                                      QUEUE                                            */
            /*****************************************************************************************/
            /*****************************************************************************************/

            // adds an element to the end of the list
            void enqueue(const T &element)
            {
                Node *node = new Node(element);
                if (isEmpty())
                {
                    head = tail = node;
                }
                else
                {
                    tail->next = node;
                    node->prev = tail;
                    tail = node;
                }

                size++;
            }

            // removes the first element in the list
            void dequeue()
            {
                if (isEmpty())
                    return;

                Node *temp = head;
                if (head == tail)
                {
                    head = tail = nullptr;
                }
                else
                {
                    head = head->next;
                    head->prev = nullptr;
                }

                delete temp;
                size--;
            }

            /*****************************************************************************************/
            /*****************************************************************************************/
            /*                                      DELETERS                                         */
            /*****************************************************************************************/
            /*****************************************************************************************/

            // removes last element in the list
            void pop()
            {
                if (isEmpty())
                    return;

                if (size == 1)
                {
                    delete head;
                    head = tail = nullptr;
                }
                else
                {
                    Node *node = head;
                    while (node->next != tail)
                        node = node->next;

                    delete tail;
                    tail = node;
                    tail->next = nullptr;
                }

                size--;
            }

            // removes all elements from the list
            void clear()
            {
                while (!isEmpty())
                    pop();
            }

            // removes the first element in the list that has node->data == element
            void remove(T element)
            {
                if (isEmpty())
                    return;

                if (head->data == element)
                {
                    dequeue();
                    return;
                }
                else if (tail->data == element)
                {
                    pop();
                    return;
                }

                Node *node = head;
                while (node->next != nullptr)
                {
                    if (node->next->data == element)
                    {
                        Node *temp = node->next;
                        node->next = node->next->next;
                        node->next->prev = node;
                        delete temp;
                        size--;
                        return;
                    }
                    node = node->next;
                }
            }
        };
    }
} // namespace ufl_cap4053::fundamentals
