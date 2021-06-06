#include <iostream>
#include <math.h>
template <class T>
class DynamicArray{
private:
    //поля
    T* m_DATA;
    int m_size;
    int m_capacity;
public:
    //создание
    DynamicArray(){//конструктор по умолчанию
        m_DATA = NULL;
        m_size = 0;
        m_capacity = 0;
    }


    void Delete(){
        delete[] this->m_DATA;
    }
    DynamicArray(int size){//конструктор с числом элементов
        m_size = size;
        m_capacity = size;
        m_DATA = new T[size];
    }

    DynamicArray(T* items,int count){//копировать элементы
        if(items == nullptr){
            m_DATA = nullptr;
            m_size = 0;
            m_capacity = 0;
        }
        else{
            m_size = count;			//из переданного массива
            m_capacity = count;
            m_DATA = new T[count];
            for (int i = 0; i < count; ++i)
            {
                m_DATA[i] = items[i];
            }
        }
    }

    DynamicArray(const DynamicArray<T> &dynamicArray){//копирующий конструктор
        if(&dynamicArray == nullptr){
            m_DATA = nullptr;
            m_size = 0;
            m_capacity = 0;
        }
        else{
            m_size = dynamicArray.m_size;
            m_capacity = m_size;
            m_DATA = new T[m_size];
            for (int i = 0; i < dynamicArray.m_size; ++i)
            {
                m_DATA[i] = dynamicArray.m_DATA[i];
            }
        }
    }

    //операции
    void Resize(int newSize){//перераспределение памяти
        if(newSize > m_capacity){
            int new_capacity = std::max(2 * m_size, newSize);
            T* new_DATA = new T[new_capacity];
            for (int i = 0; i < m_size; ++i)
            {
                new_DATA[i] = m_DATA[i];
            }
            delete[] m_DATA;
            m_DATA = new_DATA;
            m_capacity = new_capacity;
        }
        m_size = newSize;
    }

    T Get(int index){
        if(index < 0 || index >= m_capacity)
            throw "\nGet Message : Index Out Of Range\n";
        //std::cout << "\nGet index = " << index << "\n";
        return m_DATA[index];
    }

    void Set(int index,T value){//задать элемент по индексу
        if(index < 0 || index > m_capacity)
            throw "\nSet Message : Index Out Of Range\n";
        //std::cout << "\nSet DATA = " << value << " index = "<< index <<"\n";
        m_DATA[index] = value;

    }

    int GetSize() const{//получить размер массива
        return m_size;
    }

    void Append(T val){//добавление элемента в конец массива
        //std::cout << "\nAppend DATA = " << val;
        Resize(m_size + 1);//выделение доп памяти при необходимости
        m_DATA[m_size - 1] = val;
    }

    void Prepend(T val){//добавление элемента в начало массива
        //std::cout << "\nPrepend DATA = " << val << "\n";
        Resize(m_size + 1);//выделение доп памяти при необходимости
        for (int i = m_size - 2; i >= 0; --i)
        {
            m_DATA[i + 1] = m_DATA[i];
        }
        m_DATA[0] = val;
    }

    T & operator [] (int i){//перегрузка оператора "[]" для удобства вывода
        return m_DATA[i];
    }

    void Print(){
        if(m_size > 0 && m_DATA != nullptr){
            std::cout << std::endl;
            for (int i = 0; i < m_size; ++i) {
                std::cout << m_DATA[i] << "\t";
            }
            std::cout << std::endl;
        }
        else{
            std::cout << "\nObject is empty!\n";
        }
    }
};


template <typename T>
std::ostream & operator << (std::ostream & out, DynamicArray<T> a){//перегрузка оператора << для вывода
    for(int i = 0; i < a.GetSize();++i){
        out << a[i] << " ";
    }
    return out;
}
//==================================================================================================================//
template<typename T>
T sqr(T value){
    return value * value;
}

template<typename T>
bool is_more_than_10(T value){
    if(value >= 10)
        return true;
    return false;
}

template<typename T>
T sum(T first,T second){
    return first + second;
}

template<typename T>
class Node{
public:
    Node* pNext;
    Node* pPrev;
    T DATA;
    Node(T DATA = T(),Node* pPrev = nullptr,Node* pNext = nullptr){
        this->DATA = DATA;
        this->pPrev = pPrev;
        this->pNext = pNext;
    }
};

template<typename T>
class LinkedList{
public:



    ~LinkedList(){
        clear();
    }


    LinkedList(){
        Size = 0;
        HEAD = nullptr;
    }

    //считывание значений из переданного массива
    LinkedList(T* items,int count){
        if(items == nullptr){
            Size = 0;
            HEAD = nullptr;
        }
        else{
            Size = 0;
            this->HEAD = nullptr;
            this->TAIL = nullptr;
            for (int i = 0; i < count; ++i) {
                Append(items[i]);
            }
        }
    }


    LinkedList(const LinkedList<T>& list){
        Size = 0;
        this->HEAD = nullptr;//для корректного отрабатывания Append
        Node<T>* current = list.HEAD;
        for (int i = 0; i < list.Size; ++i) {//заменил Size на GetLength()
            this->Append(current->DATA);
            current = current->pNext;
        }
        //std::cout << "CopyConstructor done . . .\n";
    }


    LinkedList<T>* Concat(LinkedList<T>* list){//разобраться,что происходит с длиной(разобрался и переделал,ошибка была в том,что не было обновления TAIL у текущего объекта)
        //вызывающий объединяю с переданным в качестве параметра
        //при этом тот,что передан в качестве параметра,остается в памяти как отдельный
        //однако вызывающий воспринимает его как свою часть
        this->TAIL->pNext = list->HEAD;
        list->HEAD->pPrev = this->TAIL;
        this->TAIL = list->TAIL;
        Size+=list->Size;

        return this;
    }


    T Get(int index){
        if(index < 0 || index >= Size)
            throw "\nGet Message : Index Out Of Range\n";

        Node<T>* current;

        if(index < Size/2){
            current = HEAD;
            for (int i = 0; i < index; ++i) {
                current = current->pNext;
            }
        }else{
            current = TAIL;
            for (int i = 0; i < Size-index-1; ++i) {
                current = current->pPrev;
            }
        }
        return current->DATA;

    }


    T GetFirst() {
        if(Size == 0)
            throw "\nGetFirst Message : Index Out Of Range\n";
        //std::cout<<"\nGetFirst:\n";
        return Get(0);
    }


    T GetLast(){
        if(Size == 0)
            throw "\nGetLast Message : Index Out Of Range\n";
        //std::cout<<"\nGetLast:\n";
        return Get(Size - 1);
    }


    LinkedList<T>* GetSubLinkedList(int startIndex,int endIndex){
        if(startIndex < 0 || endIndex < 0 || startIndex >= Size || endIndex >=Size)
            throw "\nGetSubLinkedList Message : Index Out Of Range\n";
        //std::cout<<"\nGetSubLinkedList\n";
        Node<T>* current = this->HEAD;
        for (int i = 0; i < startIndex; ++i) {
            current = current->pNext;
        }
        T* items;
        items = (T*)malloc(sizeof(T*)*(endIndex - startIndex + 1));
        for (int i = 0; i < endIndex - startIndex + 1; ++i) {
            items[i] = current->DATA;
            current = current->pNext;
        }

        LinkedList<T>* result = new LinkedList<T>(items,endIndex - startIndex + 1);
        return result;

    }


    void PrintFromEnd(){//печать с конца списка
        //std::cout << std::endl;
        Node<T>* tmp = this->TAIL;
        if(Size == 1)
            std::cout << TAIL->DATA << " ";
        else{
            while(tmp != nullptr){
                std::cout << tmp->DATA <<" ";
                tmp = tmp->pPrev;
            }
        }
        std::cout << std::endl;
    }


    void PrintFromBegin(){//печать с начала списка
        if(HEAD != nullptr){
            //std::cout << std::endl;
            Node<T>* tmp = this->HEAD;
            if(Size == 1)
                std::cout << HEAD->DATA << " ";
            else{
                while(tmp != nullptr){
                    std::cout << tmp->DATA <<" ";//std::endl;
                    tmp = tmp->pNext;
                }
            }
            std::cout << std::endl;
        }
    }



    void Append(T DATA){
        if(HEAD == nullptr){//если только один элемент,то заполняем HEAD
            HEAD = new Node<T>(DATA);
            this->TAIL = HEAD;

        }else{//если больше,то добавляем и присваиваем TAIL этот элемент
            Node<T>* current = this->HEAD;//временная переменная
            Node<T>* tmp;
            while(current->pNext != nullptr){
                tmp = current;
                current = current->pNext;
                current->pPrev = tmp;
            }

            this->TAIL = new Node<T>(DATA,current,current->pNext);//вставка между current и nullptr
            current->pNext = TAIL;
        }
        Size++;
    }


    void Prepend(T DATA) {
        if(HEAD == nullptr){
            HEAD = new Node<T>(DATA);
            this->TAIL = HEAD;
        }
        else{
            Node<T>* one_more = new Node<T>(DATA,HEAD->pPrev,HEAD);//создание нового узла(следующий - HEAD,предыдущего нет)
            HEAD->pPrev = one_more;
            this->HEAD = one_more;
            Node<T>* current = HEAD;
            while(current->pNext != nullptr){
                current = current->pNext;
            }
            this->TAIL = current;
        }
        Size++;
    }


    void pop_front() {
        if(Size == 1){
            delete [] TAIL;
            Size--;
        }
        else{
            Node<T>* tmp = HEAD;//запоминаем ссылку,по которой находится текущий HEAD
            HEAD = HEAD->pNext;//сдвиг HEAD к концу на один элемент
            HEAD->pPrev = nullptr;//"обнуление" указателя на предыдущий элемент
            delete [] tmp;//удаление старого HEAD
            Size--;
        }

    }


    void pop_back(){
        Node<T>* tmp = TAIL;
        TAIL = TAIL->pPrev;
        TAIL->pNext = nullptr;
        delete [] tmp;
        Size--;
    }

    //усовершенствован для двусвязного списка
    void InsertAt(T DATA, int index) {
        if(index < 0 || index >= Size)
            throw "\nInsertAt Message : Index Out Of Range\n";
        Node<T>* previous;
        Node<T>* new_elem;
        Node<T>* tmp;
        //std::cout << "\nInsertAt DATA = " << DATA << " index = " << index << "\n";
        if(index <= Size/2){//идём сначала
            if(index == 0)
                Prepend(DATA);
            previous = HEAD;
            for (int i = 0; i < index - 1; ++i) {
                previous = previous->pNext;
            }
        }
        else{//идём с конца

            previous = TAIL;
            for (int i = 0; i < Size - index; ++i) {
                previous = previous->pPrev;
            }
        }
        tmp = previous->pNext;//запоминаем адрес следующего узла
        new_elem = new Node<T>(DATA,previous,previous->pNext);//создаем новый узел
        previous->pNext = new_elem;//обновляем указатель на следующий узел у предыдущего
        tmp->pPrev = new_elem;//обновляем указатель на предыдущий узел у следующего

        Size++;
    }

    //усовершенствован для двусвязного списка
    void removeAt(int index) {
        if(index < 0 || index >= Size)
            throw "removeAt Message : Index Out Of Range\n";
        //std::cout << "\nremoveAt index = " << index << "\n";
        if(index == 0)
            pop_front();
        else{
            if(index == Size - 1)
                pop_back();
            else{
                Node<T>* previous;
                Node<T>* toDelete;
                if(index <= Size/2){
                    previous = HEAD;
                    for (int i = 0; i < index - 1; ++i) {
                        previous = previous->pNext;
                    }
                }
                else{
                    previous = TAIL;
                    for (int i = 0; i < Size - index; ++i) {
                        previous = previous->pPrev;
                    }
                }

                toDelete = previous->pNext;//запоминаем ссылку на удаляемый узел
                previous->pNext = toDelete->pNext;//изменяем поле следующего узла у идущего перед удаляемым
                toDelete->pNext->pPrev = previous;//изменяем поле предыдущего узла у идущего после удаляемого

                delete[] toDelete;//очистка памяти по ссылке удаляемого узла
            }
            Size--;
        }
    }
    void ChangeValue(int index,T value){//изменяет по заданному индексу значение на value
        Node<T>* curr = HEAD;
        for (int i = 0; i < index; ++i) {//i + 1 < index вместо i < index - 1 для того,чтобы избежать переполнения числа
            curr = curr->pNext;
        }
        curr->DATA = value;
    }
    //очистка памяти
    void clear(){
        while(Size){
            pop_front();
        }
    }

    //усовершенствован для двусвязного списка
    T& operator[](const int index) {//перегрузка оператора []
        //для нахождения элемента с номером index
        int counter;
        Node<T> *current;
        if (index <= Size / 2) {//идём с начала
            counter = 0;
            current = this->HEAD;
            while (current != nullptr) {
                if (counter == index) {
                    return current->DATA;
                }
                current = current->pNext;
                counter++;
            }
        } else {//идём с конца
            counter = Size - 1;
            current = this->TAIL;
            while (current != nullptr) {
                if (counter == index) {
                    return current->DATA;
                }
                current = current->pPrev;
                counter--;
            }
        }
    }
private:
    int Size;
    Node<T>* HEAD;
    Node<T>* TAIL;
};

//==================================================================================================================//


template<typename T>
class Sequence{
public:
    virtual Sequence<T>* GetSubsequence(int startIndex,int endIndex) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* list) = 0;

    virtual T GetFirst() = 0;
    virtual T GetLast() = 0;
    virtual T Get(int index) = 0;
    virtual int GetLength() = 0;

    virtual void Append(T item) = 0;
    virtual void Prepend(T item) = 0;
    virtual void InsertAt(T item,int index) = 0;

    virtual void Print() = 0;
};
//==================================================================================================================//
template<typename T>
class ArraySequence : public Sequence<T>{
public:
    ArraySequence(){
        DynamicArray<T>* tmp = new DynamicArray<T>();
        DATA = *tmp;
    }

    ArraySequence(T* item,int count){

        DynamicArray<T>* tmp = new DynamicArray<T>(item,count);
        DATA = *tmp;

    }

    ArraySequence(ArraySequence<T>& array){//копиконструктор для параметра ArraySequence

        DynamicArray<T>* tmp = new DynamicArray<T>(array.DATA);//конструктор копирует соответствующее поле
        DATA = *tmp;
    }

    ArraySequence(LinkedList<T>& list){//копиконструктор для параметра LinkedList
        T* items;
        items = (T*)malloc(sizeof(T)*(list.GetLength()));
        for (int i = 0; i < list.GetLength(); ++i) {
            items[i] = list.Get(i);
        }

        DynamicArray<T>* tmp = new DynamicArray<T>(items,list.GetLength());
        DATA = *tmp;
    }
    int GetLength(){
        return DATA.GetSize();
    }
    T Get(int index){
        return DATA.Get(index);
    }
    T GetFirst(){
        return DATA.Get(0);
    }
    T GetLast(){
        return DATA.Get(DATA.GetSize()-1);
    }

    void Append(T item){
        DATA.Append(item);
    }
    void Prepend(T item){
        DATA.Prepend(item);
    }
    void InsertAt(T item,int index){//void Set(int index,T value)
        if(index >= DATA.GetSize() || index < 0)
            throw "\nInsertAt Message : Index Out Of Range";
        DATA.Resize(DATA.GetSize()+1);
        for (int i = DATA.GetSize()-2; i >= index ; --i) {
            DATA.Set(i+1,DATA.Get(i));
        }
        DATA.Set(index,item);
    }
    void Print(){
        DATA.Print();
    }

    ArraySequence<T>* GetSubsequence(int startIndex,int endIndex){
        T* items = (T*)malloc(sizeof(T)*(endIndex-startIndex));
        for (int i = startIndex; i < endIndex; ++i) {
            items[i-startIndex] = DATA.Get(i);
        }
        ArraySequence<T>* result = new ArraySequence<T>(items,endIndex-startIndex);
        return result;
    }

    ArraySequence<T>* Concat(Sequence<T>* list){
        if(list->GetLength() != 0){
            T* items = (T*)malloc(sizeof(T)*(DATA.GetSize()+list->GetLength()));
            for (int i = 0; i < DATA.GetSize(); ++i) {
                items[i] = DATA.Get(i);
            }
            for (int i = 0; i < list->GetLength(); ++i) {
                items[i+DATA.GetSize()] = list->Get(i);
            }
            ArraySequence<T>* result = new ArraySequence<T>(items,DATA.GetSize()+list->GetLength());

            return result;
        }else{
            ArraySequence<T>* result = new ArraySequence<T>(*this);
            return result;
        }

    }
private:
    DynamicArray<T> DATA;
};
//==================================================================================================================//
template<typename T>
class LinkedListSequence : public Sequence<T>{
public://информация о размере хранится в поле DATA
    LinkedListSequence(){//конструктор по умолчанию
        LinkedList<T>* tmp = new LinkedList<T>();
        DATA = *tmp;
    }
    LinkedListSequence(T* items,int count){//конструктор по массиву
        LinkedList<T>* tmp = new LinkedList<T>(items,count);
        DATA = *tmp;

    }

    //переопределение не охватывает соответствующую функцию из LinkedList,
    // так как требуется общность первого параметра,вследствие чего нет возможности получить данные
    LinkedListSequence<T>* Concat(Sequence<T>* list){
        for (int i = 0; i < list->GetLength(); ++i) {//добавляю в DATA все элементы из list,её Size увеличивается
            DATA.Append(list->Get(i));
        }
        T* items;
        items = (T*)malloc(sizeof(T*)*(DATA.GetLength()+list->GetLength()));
        for (int i = 0; i < DATA.GetLength(); ++i) {//записываю все элементы из DATA  в массив
            items[i] = DATA.Get(i);
        }

        LinkedListSequence<T>* result = new LinkedListSequence<T>(items,DATA.GetLength());//создание нового экземпляра
        return result;
    }

    LinkedListSequence(const LinkedList<T>& list){//конструктор по объекту
        LinkedList<T>* tmp = new LinkedList<T>(list);
        std::cout<< "Constructor by object . . .\n";
        DATA = *tmp;
    }
    LinkedListSequence<T>* GetSubsequence(int startIndex,int endIndex){//вернуть Sequence<T>*
        LinkedList<T>* tmp = DATA.GetSubLinkedList(startIndex,endIndex);//создаем экземляр с указанными индексами
        T* items;
        items = (T*)malloc(sizeof(T*)*(endIndex-startIndex));
        for (int i = 0; i < endIndex-startIndex; ++i) {
            items[i] = tmp->Get(i);
        }

        LinkedListSequence<T>* result = new LinkedListSequence<T>(items,endIndex-startIndex);

        return result;
    }
    int GetLength(){
        return DATA.GetLength();
    }
    T GetFirst(){
        DATA.GetFirst();
    }
    T GetLast(){
        DATA.GetLast();
    }
    T Get(int index){
        DATA.Get(index);
    }

    void Append(T item){
        DATA.Append(item);
    }
    void Prepend(T item){
        DATA.Prepend(item);
    }
    void InsertAt(T item,int index){
        DATA.InsertAt(item,index);
    }
    void removeAt(int index){
        DATA.removeAt(index);
    }
    void Print(){
        DATA.PrintFromBegin();
    }
private:
    LinkedList<T> DATA;
};
//==================================================================================================================//
template<typename T>
class TriangularMatrix{
private:
    DynamicArray<DynamicArray<T>> data;//здесь хранятся все значения матрицы
    int m;//размерность матрицы
public:
    TriangularMatrix(){
        m = 0;
    }

    TriangularMatrix(TriangularMatrix<T>* example){//копирующий конструктор
        m = example->GetSize();
        data.Resize(m);

        for (int i = 0; i < m; ++i) {
            data[i].Resize(i+1);
            for (int j = 0; j < i + 1; ++j) {
                data[i].Set(j,example->Get(i,j));
            }
        }
    }

    TriangularMatrix(int size){//конструктор с вводом элементов с консоли

        m = size;
        data.Resize(m);

        for (int i = 0; i < m; ++i) {
            data[i].Resize(i+1);
            std::cout << "Enter " << i + 1 << " values for " << i <<" matrix string\n";
            for (int j = 0; j < i + 1; ++j) {
                T value;
                if(std::cin >> value)
                    data[i].Set(j,value);
                else{
                    std::cout << "Invalid value ! ! !\n";
                    m = 0;
                    return;
                }
            }
        }
    }

    //методы для получения и записи характеристик матрицы
    int GetSize(){
        return m;
    }
    T Get(int i,int j) {
        return data[i].Get(j);
    }
    void Set(int i,int j,T value){
        data[i].Set(j,value);
    }

    TriangularMatrix<T>* Sum(TriangularMatrix<T>* example){//сумма матрицы,переданной в качестве параметра,и данной матрицы
        if(m == example->GetSize()){
            TriangularMatrix<T>* result = new TriangularMatrix<T>(example);//создание результирующей матрицы как копии переданной в качестве параметра
            //для последующего сложения с той матрицей,у которой этот метод вызван
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < i + 1; ++j) {
                    result->Set(i,j,data[i].Get(j) + result->Get(i,j));
                }
            }
            return result;
        }else{
            return nullptr;
        }
    }

    void multiplication_of_a_triangular_matrix_by_a_scalar(T scalar){//умножение данной матрицы на скаляр
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < i + 1; ++j) {
                this->Set(i,j,this->Get(i,j) * scalar);
            }
        }
    }

    T calculating_the_norm_of_a_matrix(){//вычисление нормы данной матрицы
        if(this != nullptr && m != 0){
            T result = this->Get(0,0);//в качестве начального значения результата берем элемент с индексами i = 0 и j = 0
            for (int i = 0; i < m; ++i) {
                T tmp = 0;
                for (int j = 0; j < i + 1; ++j) {
                    tmp += this->Get(i,j);
                }
                if(tmp >= result)
                    result = tmp;
            }
            return result;
        }else{
            std::cout << "Error of calculations ! ! !\n";
            return -1;//возвращаем -1 так как нужно вернуть какое то число
        }

    }

    void Print(){
        if(this != nullptr && m != 0){
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < i + 1; ++j) {
                    std::cout << data[i].Get(j) << " ";
                }
                std::cout << std::endl;
            }
        }else{
            std::cout << "Can't print ! ! !\n";
        }
    }

};
template<typename T>
class Stack{
private:
    LinkedList<T>* DATA;
    int size;
public:
    Stack(){//конструктор по умолчанию
        DATA = nullptr;
        size = 0;
    }
    Stack(LinkedList<T>* items, int count){
        DATA = items;
        size = count;
    }
    Stack(T* items, int count){//конструктор по массиву элементов
        DATA = new LinkedList<T>(items, count);
        size = count;
    }

    int GetSize(){//получение размера стека
        return size;
    }

    T Get(int index){//получение элемента по индексу
        return DATA->Get(index);
    }

    void Append(T value){//добавление элемента в конец стека
        DATA->Append(value);
    }

    void Print(){
        if(this != nullptr && DATA != nullptr && size != 0)
            DATA->PrintFromEnd();//у стека нет возможности идти с начала(тк все операции происходят на последних элементах)
    }

    //map, where, reduce
    void Map(T(*func)(T)){//возведение в квадрат
        for (int i = 0 ; i < size ; i++) {
            DATA->ChangeValue(i,func(DATA->Get(i)));
            //изменяем значение по данному индексу
        }
    }

    Stack<T>* Where(bool(*func)(T)){
        int count = 0;
        for (int i = 0; i < size; ++i) {
            if(!func(DATA->Get(i))){
                count++;
            }
        }
        if(count > 0){
            T* items = new T[count];
            int index = 0;
            for (int i = 0; i < size; ++i) {
                if(!func(DATA->Get(i))){
                    items[index] = DATA->Get(i);
                    index++;
                }
            }
            Stack<T>* result = new Stack<T>(items, count);
            return result;
        }else{
            std::cout << "There are no elements which bigger than 10 !\n";
            return nullptr;
        }

    }

    T Reduce(T(*func)(T,T)){
        T sum = 0;
        for (int i = 0; i < size; ++i) {
            sum = func(sum, DATA->Get(i));
            //передаем в функцию суммирования
            //два аргумента - старое значение sum и значение текущего элемента
            //в результате получается сумма всех элементов стека
        }
        return sum;
    }

    Stack<T>* Concat(Stack<T>* example){
        T* items = new T[size + example->GetSize()];//поэлементно копируем в этот массив элементы из обоих стеков
        for (int i = 0; i < size; ++i) {
            items[i] = DATA->Get(i);
        }
        for (int i = 0; i < example->GetSize(); ++i) {
            items[size + i] = example->Get(i);
        }

        Stack<T>* result = new Stack<T>(items, size + example->GetSize());
        return result;
    }

    //извлечение подпоследовательности из стека
    Stack<T>* GetSubsequenceFromStack(int start, int end){
        Stack<T>* result = new Stack<T>(DATA->GetSubLinkedList(start,end),end - start + 1);
        return result;
    }
};
int main(){
    int flag;
    std::cout << "Testing a stack or a triangular matrix ? (1 - stack , 2 - triangular matrix)\n";
    std::cin >> flag;
    if(flag == 1){
        //==============================================================//
        int n;
        std::cout <<"Enter size of stack : \n";
        std::cin >> n;
        std::cout <<"Enter " << n <<" elements of stack : \n";
        int* tmp1 = new int[n];
        for (int i = 0; i < n; ++i) {
            int elem;
            std::cin >> elem;
            tmp1[i] = elem;
        }
        Stack<int>* first = new Stack<int>(tmp1, n);
        first->Print();//элементы печатаются с конца, так как все операции стека должны происходить и начинаться на последнем элементе

        std::cout <<"Enter size of stack : \n";
        std::cin >> n;
        std::cout <<"Enter " << n <<" elements of vector : \n";
        int* tmp2 = new int[n];
        for (int i = 0; i < n; ++i) {
            int elem;
            std::cin >> elem;
            tmp2[i] = elem;
        }
        Stack<int>* second = new Stack<int>(tmp2, n);
        second->Print();

        int begin, end;
        std::cout << "Enter the start and end indices to get a subsequence on the first stack :\n";
        std::cin >> begin >> end;
        try{//демонстрация работы метода получения подпоследовательности из стека,в случае некорректных индексов выбрасывается исключение
            Stack<int>* sub = first->GetSubsequenceFromStack(begin,end);
            sub->Print();
        }catch (const char* msg){
            std::cout << msg << std::endl;
        }
        std::cout << "The result of concatenating the first and second stacks :\n";
        Stack<int>* concat = first->Concat(second);//демонстрация работы функции конкатенации
        concat->Print();
        std::cout << "The first stack after squaring it's elements :\n";
        first->Map(sqr);//возведение всех элементов в квадрат
        first->Print();

        std::cout << "Concatenation result after removing all elements, greater than 10 :\n";
        Stack<int>* for_where = concat->Where(is_more_than_10);
        for_where->Print();

        std::cout << "Sum of all elements in the first stack : " << first->Reduce(sum) << std::endl;
        //==============================================================//

    } else{
        if(flag == 2){
            int m;
            std::cout << "Enter size of first matrix :\n";
            std::cin >> m;
            TriangularMatrix<int>* test1 = new TriangularMatrix<int>(m);
            test1->Print();
            std::cout << "Enter size of second matrix :\n";
            std::cin >> m;
            TriangularMatrix<int>* test2 = new TriangularMatrix<int>(m);
            test2->Print();

            TriangularMatrix<int>* sum = test1->Sum(test2);
            sum->Print();

            std::cout << "Enter scalar for multiplication on a first matrix :\n";
            int scalar;
            std::cin >> scalar;
            test1->multiplication_of_a_triangular_matrix_by_a_scalar(scalar);
            test1->Print();

            std::cout << "The norm of first matrix : " << test1->calculating_the_norm_of_a_matrix() << std::endl;//вычисление нормы для матрицы test1
        }
    }

    return 0;
}