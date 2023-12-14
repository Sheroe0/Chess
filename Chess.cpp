#include <iostream>
#include <vector>
#include <cctype>

class Piece {
public:
    char name;
    bool isWhite;
    Piece(char name, bool isWhite) : name(name), isWhite(isWhite) {}
    virtual std::vector<std::pair<int, int>> getLegalMoves(int x, int y, Piece* board[8][8]) = 0;
};

class Pawn : public Piece {
public:
    Pawn(char name, bool isWhite) : Piece(name, isWhite) {}
    std::vector<std::pair<int, int>> getLegalMoves(int x, int y, Piece* board[8][8]) override {
        std::vector<std::pair<int, int>> moves;
        int direction = isWhite ? -1 : 1;
        // Проверяем, не выходит ли следующая клетка за пределы доски и не занята ли она
        if (x + direction >= 0 && x + direction < 8 && !board[x + direction][y]) {
            moves.push_back({ x + direction, y });
            // Проверяем, может ли пешка сделать двойной ход вперед
            if ((x == 6 && isWhite) || (x == 1 && !isWhite) && !board[x + 2 * direction][y]) {
                moves.push_back({ x + 2 * direction, y });
            }
        }
        // Проверяем, можно ли бить влево
        if (x + direction >= 0 && x + direction < 8 && y > 0 && board[x + direction][y - 1] && board[x + direction][y - 1]->isWhite != this->isWhite) {
            moves.push_back({ x + direction, y - 1 });
        }
        // Проверяем, можно ли бить вправо
        if (x + direction >= 0 && x + direction < 8 && y < 7 && board[x + direction][y + 1] && board[x + direction][y + 1]->isWhite != this->isWhite) {
            moves.push_back({ x + direction, y + 1 });
        }
        return moves;
    }
};

class King : public Piece {
public:
    King(char name, bool isWhite) : Piece(name, isWhite) {}
    std::vector<std::pair<int, int>> getLegalMoves(int x, int y, Piece* board[8][8]) override {
        std::vector<std::pair<int, int>> moves;
        // Все возможные направления для короля
        int directions[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
        for (auto& direction : directions) {
            int newX = x + direction[0];
            int newY = y + direction[1];
            // Проверяем, не выходит ли клетка за пределы доски
            if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
                // Проверяем, не занята ли клетка фигурой того же цвета
                if (!board[newX][newY] || board[newX][newY]->isWhite != this->isWhite) {
                    moves.push_back({ newX, newY });
                }
            }
        }
        return moves;
    }
};

class Queen : public Piece {
public:
    Queen(char name, bool isWhite) : Piece(name, isWhite) {}
    std::vector<std::pair<int, int>> getLegalMoves(int x, int y, Piece* board[8][8]) override {
        std::vector<std::pair<int, int>> moves;
        // Все возможные направления для ферзя
        int directions[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
        for (auto& direction : directions) {
            for (int i = 1; i < 8; ++i) {
                int newX = x + i * direction[0];
                int newY = y + i * direction[1];
                // Проверяем, не выходит ли клетка за пределы доски
                if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
                    // Проверяем, не занята ли клетка фигурой того же цвета
                    if (!board[newX][newY] || board[newX][newY]->isWhite != this->isWhite) {
                        moves.push_back({ newX, newY });
                    }
                    // Если клетка занята, прерываем цикл
                    if (board[newX][newY]) {
                        break;
                    }
                }
                else {
                    break;
                }
            }
        }
        return moves;
    }

};

class Rook : public Piece {
public:
    Rook(char name, bool isWhite) : Piece(name, isWhite) {}
    std::vector<std::pair<int, int>> getLegalMoves(int x, int y, Piece* board[8][8]) override {
        std::vector<std::pair<int, int>> moves;
        // Все возможные направления для ладьи
        int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
        for (auto& direction : directions) {
            for (int i = 1; i < 8; ++i) {
                int newX = x + i * direction[0];
                int newY = y + i * direction[1];
                // Проверяем, не выходит ли клетка за пределы доски
                if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
                    // Проверяем, не занята ли клетка фигурой того же цвета
                    if (!board[newX][newY] || board[newX][newY]->isWhite != this->isWhite) {
                        moves.push_back({ newX, newY });
                    }
                    // Если клетка занята, прерываем цикл
                    if (board[newX][newY]) {
                        break;
                    }
                }
                else {
                    break;
                }
            }
        }
        return moves;
    }

};

class Bishop : public Piece {
public:
    Bishop(char name, bool isWhite) : Piece(name, isWhite) {}
    std::vector<std::pair<int, int>> getLegalMoves(int x, int y, Piece* board[8][8]) override {
        std::vector<std::pair<int, int>> moves;
        // Все возможные направления для слона
        int directions[4][2] = { {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };
        for (auto& direction : directions) {
            for (int i = 1; i < 8; ++i) {
                int newX = x + i * direction[0];
                int newY = y + i * direction[1];
                // Проверяем, не выходит ли клетка за пределы доски
                if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
                    // Проверяем, не занята ли клетка фигурой того же цвета
                    if (!board[newX][newY] || board[newX][newY]->isWhite != this->isWhite) {
                        moves.push_back({ newX, newY });
                    }
                    // Если клетка занята, прерываем цикл
                    if (board[newX][newY]) {
                        break;
                    }
                }
                else {
                    break;
                }
            }
        }
        return moves;
    }

};

class Knight : public Piece {
public:
    Knight(char name, bool isWhite) : Piece(name, isWhite) {}
    std::vector<std::pair<int, int>> getLegalMoves(int x, int y, Piece* board[8][8]) override {
        std::vector<std::pair<int, int>> moves;
        // Все возможные ходы коня
        std::vector<std::pair<int, int>> knightMoves = { {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1} };
        for (const auto& move : knightMoves) {
            int newX = x + move.first;
            int newY = y + move.second;
            // Проверяем, не выходит ли клетка за пределы доски
            if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
                // Проверяем, не занята ли клетка фигурой того же цвета
                if (!board[newX][newY] || board[newX][newY]->isWhite != this->isWhite) {
                    moves.push_back({ newX, newY });
                }
            }
        }
        return moves;
    }
};

bool isKingInCheck(Piece* board[8][8], bool isWhite) {
    // Найти позицию короля
    int kingX, kingY;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board[i][j];
            if (piece && piece->isWhite == isWhite && piece->name == 'K') {
                kingX = i;
                kingY = j;
                break;
            }
        }
    }

    // Проверить, может ли какая-либо фигура противника атаковать короля
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board[i][j];
            if (piece && piece->isWhite != isWhite) {
                std::vector<std::pair<int, int>> legalMoves = piece->getLegalMoves(i, j, board);
                if (std::find(legalMoves.begin(), legalMoves.end(), std::make_pair(kingX, kingY)) != legalMoves.end()) {
                    return true;
                }
            }
        }
    }

    return false;
}

class Board {
private:
    Piece* board[8][8];
    bool isWhiteTurn = true; // Переменная для отслеживания очередности ходов
public:
    Piece* (*getBoard())[8] { return board; }
    bool getIsWhiteTurn() { return isWhiteTurn; }
    Board() {
        // Инициализируйте доску
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                board[i][j] = nullptr;
            }
        }

        // Инициализация пешек
        for (int i = 0; i < 8; ++i) {
            board[1][i] = new Pawn('P', false);
            board[6][i] = new Pawn('P', true);
        }

        // Инициализация фигур
        std::string pieces = "RNBQKBNR";
        for (int i = 0; i < 8; ++i) {
            switch (pieces[i]) {
            case 'R':
                board[0][i] = new Rook(pieces[i], false);
                board[7][i] = new Rook(pieces[i], true);
                break;
            case 'N':
                board[0][i] = new Knight(pieces[i], false);
                board[7][i] = new Knight(pieces[i], true);
                break;
            case 'B':
                board[0][i] = new Bishop(pieces[i], false);
                board[7][i] = new Bishop(pieces[i], true);
                break;
            case 'Q':
                board[0][i] = new Queen(pieces[i], false);
                board[7][i] = new Queen(pieces[i], true);
                break;
            case 'K':
                board[0][i] = new King(pieces[i], false);
                board[7][i] = new King(pieces[i], true);
                break;
            }
        }

    }

    std::vector<std::pair<int, int>> getLegalMoves(int x, int y) {
        if (board[x][y] == nullptr) {
            return {};
        }
        return board[x][y]->getLegalMoves(x, y, board);
    }

    Piece* getPiece(int x, int y) {
        return board[x][y];
    }

    bool movePiece(int oldX, int oldY, int newX, int newY) {
        Piece* piece = board[oldX][oldY];
        if (piece == nullptr || piece->isWhite != isWhiteTurn) { 
            return false; // Нет фигуры для перемещения или не тот ход
        }
        std::vector<std::pair<int, int>> legalMoves = piece->getLegalMoves(oldX, oldY, board);
        if (std::find(legalMoves.begin(), legalMoves.end(), std::make_pair(newX, newY)) == legalMoves.end()) {
            return false; // Ход недопустим
        }
        // Создайте копию доски и сделайте ход на копии
        Piece* tempBoard[8][8];
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                tempBoard[i][j] = board[i][j];
            }
        }
        tempBoard[newX][newY] = tempBoard[oldX][oldY];
        tempBoard[oldX][oldY] = nullptr;
        // Проверьте, будет ли король в шаху после хода
        if (isKingInCheck(tempBoard, piece->isWhite)) {
            return false; // Если король в шаху, ход недопустим
        }
        // Если ход допустим, сделайте его на реальной доске
        delete board[newX][newY]; // Удаляем фигуру, которая стоит на новой позиции
        board[newX][newY] = piece; // Перемещаем фигуру
        board[oldX][oldY] = nullptr; // Очищаем старую позицию
        isWhiteTurn = !isWhiteTurn; // Передаем ход другой стороне
        return true;
    }

};


void printBoard(Board& board, std::vector<std::pair<int, int>> legalMoves = {}) {
    std::string letters = "ABCDEFGH";
    std::cout << "  ";
    for (char letter : letters) {
        std::cout << " " << letter << " ";
    }
    std::cout << std::endl;
    int start = board.getIsWhiteTurn() ? 0 : 7;
    int end = board.getIsWhiteTurn() ? 8 : -1;
    int step = board.getIsWhiteTurn() ? 1 : -1;
    for (int i = start; i != end; i += step) {
        std::cout << 8 - i << " ";
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board.getPiece(i, j); // Получаем фигуру на доске
            bool isLegalMove = std::find(legalMoves.begin(), legalMoves.end(), std::make_pair(i, j)) != legalMoves.end();
            if (piece) {
                // Если клетка занята вражеской фигурой, которую можно съесть, выводим её фиолетовым цветом
                if (piece && isLegalMove) {
                    std::cout << "\033[35m " << piece->name << " \033[0m";
                }
                else {
                    if (piece->isWhite) {
                        std::cout << "\033[34m " << piece->name << " \033[0m"; // Белые фигуры выводятся синим цветом
                    }
                    else {
                        std::cout << "\033[31m " << piece->name << " \033[0m"; // Черные фигуры выводятся красным цветом
                    }
                }
            }
            else if (isLegalMove) {
                std::cout << "\033[32m " << "+" << " \033[0m"; // Возможные ходы выводятся зелёным цветом
            }
            else {
                std::cout << " " << "+" << " ";
            }

        }
        std::cout << " " << 8 - i << std::endl;
    }
    std::cout << "  ";
    for (char letter : letters) {
        std::cout << " " << letter << " ";
    }
    std::cout << std::endl;
}



int main() {
    setlocale(LC_ALL, "Russian");
    Board board;
    std::string input;
    while (true) {
        printBoard(board); // Выводим доску до хода
        std::cout << "Ход " << (board.getIsWhiteTurn() ? "белых" : "черных") << ". Введите позицию фигуры или 'сдаться' для сдачи: ";
        std::cin >> input;
        if (input == "сдаться") {
            std::cout << (board.getIsWhiteTurn() ? "Черные" : "Белые") << " выиграли!" << std::endl;
            break;
        }
        // Конвертируем ввод пользователя в uppercase
        for (auto& c : input) {
            c = toupper(c);
        }
        // Меняем местами символы ввода если первым ввели цифру
        if (isdigit(input[0])) {
            std::swap(input[0], input[1]);
        }
        // Проверка ввода на валидность
        if (input.size() != 2 || input[0] < 'A' || input[0] > 'H' || input[1] < '1' || input[1] > '8') {
            std::cout << "Неверный ввод. Попробуйте еще раз." << std::endl;
            continue;
        }
        int x = 8 - (input[1] - '0'); // Переводим номера строк в индексы массива
        int y = input[0] - 'A'; // Переводим буквы в индексы массива
        Piece* piece = board.getPiece(x, y); // Получаем фигуру на доске
        if (piece == nullptr) {
            std::cout << "Вы выбрали пустую клетку. Попробуйте еще раз." << std::endl;
            continue;
        }
        if (piece->isWhite != board.getIsWhiteTurn()) {
            std::cout << "Вы выбрали вражескую фигуру. Попробуйте еще раз." << std::endl;
            continue;
        }
        auto moves = board.getLegalMoves(x, y);
        for (const auto& move : moves) {
            std::cout << "Возможный ход: " << static_cast<char>('A' + move.second) << 8 - move.first << std::endl;
        }
        printBoard(board, moves); // Выводим доску с подсвеченными возможными ходами


        // Запрашиваем у пользователя координаты для хода
        std::cout << "Введите координаты для хода или 'cancel' для отмены: ";
        std::cin >> input;
        if (input == "cancel") {
            continue;
        }
        // Конвертируем ввод пользователя в uppercase
        for (auto& c : input) {
            c = toupper(c);
        }
        // Меняем местами символы ввода если первым ввели цифру
        if (isdigit(input[0])) {
            std::swap(input[0], input[1]);
        }
        // Проверка ввода на валидность
        if (input.size() != 2 || input[0] < 'A' || input[0] > 'H' || input[1] < '1' || input[1] > '8') {
            std::cout << "Неверный ввод. Попробуйте еще раз." << std::endl;
            continue;
        }
        int newX = 8 - (input[1] - '0'); // Переводим номера строк в индексы массива
        int newY = input[0] - 'A'; // Переводим буквы в индексы массива

        // Проверяем, является ли выбранный ход допустимым
        if (std::find(moves.begin(), moves.end(), std::make_pair(newX, newY)) != moves.end()) {
            // Если да, то делаем ход и обновляем доску
            if (board.movePiece(x, y, newX, newY)) {
                std::cout << "Ход сделан: " << input << std::endl;
                // Проверяем, находится ли король под шахом
                if (isKingInCheck(board.getBoard(), !board.getPiece(newX, newY)->isWhite)) {
                    std::cout << "Шах!" << std::endl;
                }
            }
            else {
                std::cout << "Ход не удался. Попробуйте еще раз." << std::endl;
            }
        }
        else {
            std::cout << "Недопустимый ход. Попробуйте еще раз." << std::endl;
        }
    }
    return 0;
}