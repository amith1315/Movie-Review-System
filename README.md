# 🎬 Movie Rating System

Welcome to the Movie Rating System – a console-based application built using C++ that allows users to register, log in, view movies, add reviews, and view ratings.

This project follows the Model–View–Controller (MVC) architecture and is built as part of a capstone project to demonstrate clean architecture, design principles, and object-oriented programming in C++.

---

##  Features

- User Registration & Login
- View list of movies (stored in SQLite database)
- Add movie reviews with rating (1–5) and comments
- Automatic average rating calculation per movie
- Error handling for invalid inputs and login failures
- Modular MVC architecture
- Easily extendable and maintainable design

---

##  Tech Stack

- C++17
- SQLite3 (for database storage)
- CMake (for build management)
- Standard Template Library (STL)

---

## Design Patterns Used

- Model-View-Controller (MVC)
- Singleton (for database access or config if implemented)
- Strategy 

---

##  Architecture (MVC)

- Model → Handles database, business logic, and data manipulation.
- View → Handles all user interaction and input/output.
- Controller → Coordinates between model and view, handles flow.

Build Instructions

# git clone https://github.com/Aakriti-2334/movie-rating-system
# cd MovieRatingSystem
# mkdir -p build
# cd build
# cmake ..
# make
# ./MovieRatingSystem

OR

# g++ -std=c++17 -Iinclude src/main.cpp src/controller/Controller.cpp src/model/Model.cpp src/view/View.cpp -lsqlite3 -o MovieRatingSystem
# ./MovieRatingSystem

Sample Usage

----- Movie Rating System -----
1. Register
2. Login
3. View Movies
4. Add Review
5. View Reviews
6. Exit
Enter your choice:

