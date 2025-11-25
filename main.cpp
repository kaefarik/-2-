#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class dynamicArray
{
private:
    int *arr;
    int size;

public:
    dynamicArray(int size)
    {
        this->arr = new int[size];
        this->size = size;
    }

    dynamicArray(const dynamicArray &other)
    {
        this->arr = new int[other.size];
        this->size = other.size;

        for (int i = 0; i < other.size; i++) {
            this->arr[i] = other.arr[i];
        }
    }

    virtual void printArray()
    {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    bool setValue(int index, int value)
    {
        if (index < 0 || index >= size) {
            cout << "неверный индекс" << endl;
            return false;
        }
        if (value < -100 || value > 100) {
            cout << "значение не принадлежит [-100; 100]" << endl;
            return false;
        }
        arr[index] = value;
        return true;
    }

    int getValue(int index)
    {
        if (index < 0 || index >= size) {
            cout << "неверный индекс";
            return -101;
        }
        return arr[index];
    }

    int getSize() { return this->size; }

    void push_back(int value)
    {
        if (value < -100 || value > 100)
            return;
        int *newArray = new int[size + 1];
        for (int i = 0; i < size; i++) {
            newArray[i] = arr[i];
        }
        newArray[size] = value;
        size++;
        delete[] arr;
        arr = newArray;
    }

    dynamicArray add(const dynamicArray &other)
    {
        int max_size = this->size;
        if (this->size < other.size) {
            max_size = other.size;
        }

        dynamicArray result(max_size);

        for (int i = 0; i < max_size; i++) {
            int value = 0;

            if (i < this->size) {
                value += this->arr[i];
            }
            if (i < other.size) {
                value += other.arr[i];
            }

            result.arr[i] = value;
        }
        return result;
    }

    dynamicArray subtract(const dynamicArray &other)
    {
        int max_size = this->size;
        if (this->size < other.size) {
            max_size = other.size;
        }

        dynamicArray result(max_size);

        for (int i = 0; i < max_size; i++) {
            int value = 0;

            if (i < this->size) {
                value += this->arr[i];
            }
            if (i < other.size) {
                value -= other.arr[i];
            }

            result.arr[i] = value;
        }
        return result;
    }

    ~dynamicArray() { delete[] arr; }
};

class inheritedArray : public dynamicArray
{
private:
    void insertionSort(int temp[], int size)
    {
        for (int i = 1; i < size; i++) {
            int x = temp[i];
            int j = i;
            while (j > 0 && temp[j - 1] > x) {
                temp[j] = temp[j - 1];
                j--;
            }
            temp[j] = x;
        }
    }

public:
    inheritedArray(int size)
        : dynamicArray(size)
    {}

    double average_value()
    {
        int size = getSize();
        double result = 0;
        for (int i = 0; i < size; i++) {
            result += getValue(i);
        }
        result /= size;
        return result;
    }

    double median_value()
    {
        int size = getSize();
        int *temp = new int[size];

        for (int i = 0; i < size; i++) {
            temp[i] = getValue(i);
        }

        insertionSort(temp, size);

        double result;
        if (size % 2 == 0) {
            result = temp[size / 2 - 1] + temp[size / 2];
            result /= 2;
        } else {
            result = temp[size / 2];
        }
        delete[] temp;
        return result;
    }
    void min_value()
    {
        int size = getSize();
        int *temp = new int[size];

        for (int i = 0; i < size; i++) {
            temp[i] = getValue(i);
        }

        insertionSort(temp, size);

        int result = temp[0];

        delete[] temp;
        cout << result << endl;
    }
    void max_value()
    {
        int size = getSize();
        int *temp = new int[size];

        for (int i = 0; i < size; i++) {
            temp[i] = getValue(i);
        }

        insertionSort(temp, size);

        int result = temp[size - 1];

        delete[] temp;
        cout << result << endl;
    }
};

class ArrTxt : public dynamicArray
{
public:
    ArrTxt(int size)
        : dynamicArray(size)
    {}
    void printArray() override
    {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::string filename = std::ctime(&time);
        filename.pop_back();
        filename.append(".txt");

        for (int i = 0; i < filename.length(); i++) {
            if (filename[i] == ' ') {
                filename[i] = '_';
            }
            if (filename[i] == ':') {
                filename[i] = '-';
            }
        }

        std::ofstream file;
        file.open(filename);
        if (file.is_open()) {
            cout << "Файл создан: " << filename << endl;
            int size = getSize();

            for (int i = 0; i < size; i++) {
                file << getValue(i) << ' ';
            }
        } else {
            cout << "Ошибка: не удалось создать файл " << filename << endl;
        }

        file.close();
    }
};

class ArrCSV : public dynamicArray
{
public:
    ArrCSV(int size)
        : dynamicArray(size)
    {}
    void printArray() override
    {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::string filename = std::ctime(&time);
        filename.pop_back();
        filename.append(".csv");

        for (int i = 0; i < filename.length(); i++) {
            if (filename[i] == ' ') {
                filename[i] = '_';
            }
            if (filename[i] == ':') {
                filename[i] = '-';
            }
        }

        std::ofstream file;
        file.open(filename);
        if (file.is_open()) {
            cout << "Файл создан: " << filename << endl;
            int size = getSize();

            for (int i = 0; i < size; i++) {
                file << getValue(i) << ' ';
            }
        } else {
            cout << "Ошибка: не удалось создать файл " << filename << endl;
        }

        file.close();
    }
};

int main()
{
    dynamicArray a(3);
    a.setValue(0, 1);
    a.setValue(1, 5);
    a.setValue(2, 10);
    cout << "a.getValue(1) " << a.getValue(1) << endl;
    cout << "a.getValue(1000) ";
    cout << a.getValue(1000) << endl;
    cout << "arr a: ";
    a.printArray();

    dynamicArray b = a;
    cout << "arr b: ";
    b.printArray();

    dynamicArray c(5);
    c.setValue(0, 1);
    c.setValue(1, 2);
    c.setValue(2, 3);
    c.setValue(3, 4);
    c.setValue(4, 5);

    a.push_back(11);
    cout << "arr a: ";
    a.printArray();

    cout << "arr c: ";
    c.printArray();

    dynamicArray d = a.add(c);
    cout << "arr d: ";
    d.printArray();

    dynamicArray e = a.subtract(c);
    cout << "arr e: ";
    e.printArray();

    int size = 5;
    inheritedArray arr2(size);

    arr2.setValue(0, 2);
    arr2.setValue(1, 4);
    arr2.setValue(2, 100);
    arr2.setValue(3, 1);
    arr2.setValue(4, 3);
    cout << "arr2: ";
    arr2.printArray();
    cout << arr2.average_value() << endl;
    cout << arr2.median_value() << endl;
    arr2.min_value();
    arr2.max_value();

    size = 20;
    ArrTxt txt(size);
    for (int i = 0; i < size; i++) {
        txt.setValue(i, i + 1);
    }
    txt.printArray();
    size = 10;
    ArrCSV csv(size);
    for (int i = 0; i < size; i++) {
        csv.setValue(i, i + 1);
    }
    csv.printArray();
}
