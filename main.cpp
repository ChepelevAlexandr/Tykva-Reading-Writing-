#include <iostream>
#include <chrono>
#include <thread>

const size_t PAGE_SIZE = 4096; // Размер страницы 4 KiB
const size_t DELAY_PAGES = 1000; // Задержка через каждые DELAY_PAGES страниц
const size_t MEMORY_SIZE_FACTOR = 1000; // Увеличенный множитель размера памяти

volatile char* memory; // Глобальная переменная для чтения/записи

void read_memory(size_t memory_size) {
    for (size_t i = 0; i < memory_size; i += PAGE_SIZE) {
        // Чтение из памяти
        volatile char value = memory[i];

        if (i % (DELAY_PAGES * PAGE_SIZE) == 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Задержка
        }
    }
}

void write_memory(size_t memory_size) {
    for (size_t i = 0; i < memory_size; i += PAGE_SIZE) {
        // Запись в память
        memory[i] = 'x';

        if (i % (DELAY_PAGES * PAGE_SIZE) == 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Задержка
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " [read|write]" << std::endl;
        return 1;
    }

    size_t memory_size = MEMORY_SIZE_FACTOR * 1024 * 1024; // Размер памяти в МБ

    memory = new volatile char[memory_size]; // Выделение памяти

    if (std::string(argv[1]) == "read") {
        std::cout << "Reading memory..." << std::endl;
        read_memory(memory_size);
    }
    else if (std::string(argv[1]) == "write") {
        std::cout << "Writing to memory..." << std::endl;
        write_memory(memory_size);
    }
    else {
        std::cerr << "Unknown command: " << argv[1] << std::endl;
        delete[] memory;
        return 1;
    }

    delete[] memory; // Освобождение памяти
    return 0;
}
