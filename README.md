# Chess Game Documentation
This is a simple implementation of a chess game in C++. The game is played on the console and the board is printed after each move. The game supports all the basic rules of chess including castling, pawn promotion, and en passant.

Classes
The game is implemented using several classes to represent the chess pieces and the board.

Piece
This is the base class for all the chess pieces. It has two data members: name which is a character representing the piece, and isWhite which is a boolean indicating whether the piece is white or not. It also has a pure virtual function getLegalMoves which returns a vector of legal moves for the piece.

Pawn, King, Queen, Rook, Bishop, Knight
These are derived classes from the Piece class. They implement the getLegalMoves function to return the legal moves for each piece according to the rules of chess.

Board
This class represents the chess board. It has a 2D array of Piece pointers representing the board. It also has a boolean isWhiteTurn to keep track of whose turn it is. The class has several member functions to initialize the board, get the legal moves for a piece, move a piece, and print the board.

Functions
isKingInCheck
This is a helper function that checks if the king of a given color is in check. It does this by simulating the moves of all the pieces of the opposite color and checking if any of them can capture the king.

printBoard
This function prints the current state of the board. It also highlights the possible moves for a piece when a piece is selected.

Main Function
The main function is where the game loop is implemented. It prompts the user to enter a move, validates the move, makes the move if it’s valid, and then prints the new state of the board. The game continues until a player is checkmated or a player resigns.

How to Play
To play the game, compile and run the program. You will be prompted to enter a move. A move is entered as the initial of the piece followed by the starting and ending coordinates of the move. For example, to move a pawn from e2 to e4, you would enter e2 e4. To resign, you can enter resign.

Please note that this game does not support castling, pawn promotion, or en passant. Also, it does not check for checkmate or stalemate, so the game continues until a player resigns.

Enjoy the game!
