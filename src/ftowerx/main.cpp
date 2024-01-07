void runTOHGame(size_t size);

int main() {
    std::cout << "q: Exit, Esc: Cancel Move, Arrow Keys: Moving Disks. Enter number of disk: ";
    size_t size{};
    std::cin >> size;
    runTOHGame(size);
}
