
import functools

@functools.total_ordering
class Node:
    def __init__(self, value, prev=None, next=None):
        self.value = value
        self.prev = prev
        self.next = next

    def __eq__(self, other):
        return self.value == other.value

    def __lt__(self, other):
        return self.value < other.values

class BidirectionalList:
    def __init__(self):
        self.head = None
        self.tail = None
        self.count = 0

    def add_in_tail(self, value):
        if self.head is None:
            temp = Node(value)
            self.head = temp
            self.tail = temp
        else:
            temp = Node(value, self.tail)
            self.tail.next = temp
            self.tail = temp
        self.count += 1


    def add_in_head(self, value):
        if self.head is None:
            temp = Node(value)
            self.head = temp
            self.tail = temp
        else:
            temp = Node(value, None, self.head)
            self.head = temp
        self.count += 1

    def clear(self):
        self.head = None
        self.tail = None
        self.count = 0


    def remove_by_index(self, index):
        if index >= self.count:
            raise ValueError()

        temp = self[index]

        if temp.next is None:
            self.tail = self.tail.prev
            self.tail.next = None

        elif temp.prev is None:
            self.head = self.head.next

        else:
            prev = temp.prev
            next = temp.next
            prev.next = next
            next.prev = prev

        self.count -= 1


    def __getitem__(self, index):
        temp = self.head
        while index != 0:
            temp = temp.next;
            index -= 1
        return temp

    def __iter__(self):
        temp = self.head
        while temp is not None:
            yield temp.value
            temp = temp.next

    def __len__(self):
        return self.count

def main():
    my_list = BidirectionalList()
    while True:
        print("1) Добавить в начало ")
        print("2) Добавить в конец ")
        print("3) Удалить по индексу ")
        print("4) Очистить список ")
        print("5) Вывести содержимое ")
        print("0) Выйти ")

        select = input("Введите команду ")
        if select == "1":
            my_list.add_in_head(input("Введите строку: "))
        elif select == "2":
            my_list.add_in_tail(input("Введите строку: "))
        elif select == "3":
            try:
                index = int(input("Введите индекс: "))
                my_list.remove_by_index(index)
            except:
                pass
        elif select == "4":
            my_list.clear()
        elif select == "5":
            print('[', end = "")
            for item in my_list:
                print(item, end = ' ')
            print(']', end = "\n")
        elif select == "0":
            break
        else:
            print("Ошибка ввода")

if __name__ == "__main__":
    main()
