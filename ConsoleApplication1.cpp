

#include <iostream>
#include <mutex>
#include <thread>

class Data {
private:
    int scalarData;
    std::mutex mtx;

public:
    Data(int data) : scalarData(data) {}

    int getScalarData() {
        return scalarData;
    }

    void setScalarData(int data) {
        scalarData = data;
    }

    std::mutex& getMutex() {
        return mtx;
    }
};
void swap1(Data& data1, Data& data2) {
    std::lock(data1.getMutex(), data2.getMutex());
    std::lock_guard<std::mutex> lock1(data1.getMutex(), std::adopt_lock);
    std::lock_guard<std::mutex> lock2(data2.getMutex(), std::adopt_lock);

  
    int temp = data1.getScalarData();
    data1.setScalarData(data2.getScalarData());
    data2.setScalarData(temp);
}


void swap2(Data& data1, Data& data2) {
    std::scoped_lock lock(data1.getMutex(), data2.getMutex());

   
    int temp = data1.getScalarData();
    data1.setScalarData(data2.getScalarData());
    data2.setScalarData(temp);
}


void swap3(Data& data1, Data& data2) {
    std::unique_lock<std::mutex> lock1(data1.getMutex(), std::defer_lock);
    std::unique_lock<std::mutex> lock2(data2.getMutex(), std::defer_lock);
    std::lock(lock1, lock2);

    
    int temp = data1.getScalarData();
    data1.setScalarData(data2.getScalarData());
    data2.setScalarData(temp);
}

int main() {
    Data data1(10);
    Data data2(20);
    std::cout << "Data 1 before swap: " << data1.getScalarData() << std::endl;
    std::cout << "Data 2 before swap: " << data2.getScalarData() << std::endl;
   
    swap1(data1, data2);
    std::cout << "Data 1 after swap: " << data1.getScalarData() << std::endl;
    std::cout << "Data 2 after swap: " << data2.getScalarData() << std::endl;

    swap2(data1, data2);
    std::cout << "Data 1 after swap: " << data1.getScalarData() << std::endl;
    std::cout << "Data 2 after swap: " << data2.getScalarData() << std::endl;

    swap3(data1, data2);
    std::cout << "Data 1 after swap: " << data1.getScalarData() << std::endl;
    std::cout << "Data 2 after swap: " << data2.getScalarData() << std::endl;

    return 0;
}
