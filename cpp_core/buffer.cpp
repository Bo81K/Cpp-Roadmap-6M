#include <iostream>
#include <cstddef>
#include <fstream>
#include <string>

class Buffer {
public:
    Buffer(size_t size);

    ~Buffer();

    void set(size_t index, int value);
    int get(size_t index) const;
    size_t size() const;
    void print() const;
    Buffer(const Buffer& other);
    Buffer& operator = (const Buffer& other);

    bool saveToFile(const std::string &filename) const;
    bool loadFromFile(const std::string &filename);

private:
    int* data_;
    size_t size_;
};

Buffer::Buffer(size_t size)
{
    size_ = size;
    data_ = new int[size_];

    for(size_t i = 0; i < size_; ++i){
        data_[i] = 0;
    }

}

Buffer::~Buffer()
{
    delete[] data_;
    std::cout << "Destructor called! Memory freed.\n"; 
}

Buffer::Buffer(const Buffer& other)
{
    std::cout << ">>> Сработал МОЙ конструктор копирования! <<<\n";
    size_ = other.size_;

    data_ = new int[size_];

    for(size_t i = 0; i < size_; ++i){
        data_[i] = other.data_[i];
    }
}

Buffer& Buffer::operator=(const Buffer& other) 
{
    if (this == &other) {
        return *this;
    }
    
    delete[]data_;

    size_ = other.size_;
    
    data_ = new int[size_];
    
    for(size_t i = 0; i < size_; ++i){
        data_[i] = other.data_[i];
    }
    
    return *this;
}

void Buffer::set(size_t index, int value) 
{
    if (index < size_) {
        data_[index] = value;
    }
}

int Buffer::get(size_t index) const 
{
    if (index < size_) {
        return data_[index];
    }
    return -1;
}

size_t Buffer::size() const
{
    return size_;
}

void Buffer::print() const
{
    std::cout<< "Buffer [";
    for (size_t i = 0; i < size_; ++i){
        std::cout << data_[i] << (i + 1 < size_ ? ", ": "");
    }
    
    std::cout<< "]\n";
}

bool Buffer::saveToFile(const std::string &filename) const
{
    std::ofstream out(filename, std::ios::binary); // запись
    if (!out.is_open())
    {
        std::cout << "Error: cannot open file for writting\n";
        return false;
    }

    out.write(reinterpret_cast<const char *>(&size_), sizeof(size_));

    // Откуда: сам массив (приведённый к указателю на байты)
    // Сколько: количество элементов * размер одного элемента (int)
    out.write(reinterpret_cast<const char *>(data_), size_ * sizeof(int));

    out.close();
    return true;
}

bool Buffer::loadFromFile(const std::string &filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open())
    {
        std::cout << "Error: cannot open file for reading\n";
        return false;
    }

    size_t newSize;
    in.read(reinterpret_cast<char *>(&newSize), sizeof(newSize));

    delete[] data_;

    size_ = newSize;
    data_ = new int[size_];

    in.read(reinterpret_cast<char *>(data_), size_ * sizeof(int));

    in.close();
    return true;
}

// Проверка
void testFunction() 
{
    std::cout << "Entering testFunction...\n";
    Buffer myBuf(5); // Здесь вызывается конструктор
    
    myBuf.set(0, 10);
    myBuf.set(1, 20);
    myBuf.print();
    
    std::cout << "Exiting testFunction...\n";
    // Здесь myBuf умирает, и АВТОМАТИЧЕСКИ вызывается деструктор!
}

int main() 
{
    testFunction();
    std::cout << "Back in main. Buffer is already destroyed.\n";
    
    std::cout << "\n=== Testing copy ===\n";
    Buffer buf1(3);
    buf1.set(0, 100);
    buf1.set(1, 200);
    buf1.set(2, 300);
    
    std::cout << "buf1: ";
    buf1.print();
    
    Buffer buf2 = buf1;  // Копирование!
    
    std::cout << "buf2 (copy of buf1): ";
    buf2.print();
    
    buf2.set(0, 999);  // Изменяем buf2
    
    std::cout << "After changing buf2:\n";
    std::cout << "buf1: ";
    buf1.print();
    std::cout << "buf2: ";
    buf2.print();

    std::cout << "\n=== Testing File I/O ===\n";
    Buffer fileBuf(3);
    fileBuf.set(0, 77);
    fileBuf.set(1, 88);
    fileBuf.set(2, 99);

    fileBuf.saveToFile("test_buffer.bin");

    Buffer emptyBuf(1);
    emptyBuf.loadFromFile("test_buffer.bin");

    std::cout << "Loaded from file: ";
    emptyBuf.print();

    return 0;
}