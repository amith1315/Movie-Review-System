#include "View.h"
#include <iostream>
#include <termios.h>
#include <unistd.h>

// Helper function to mask password input
std::string getHiddenPassword() {
    std::string password;
    char ch;
    struct termios oldt, newt;

    // Turn off echoing
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    std::cout << "Password: ";
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (ch == 127 || ch == 8) { // handle backspace
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b";
            }
        } else {
            password += ch;
            std::cout << '*';
        }
    }

    std::cout << std::endl;

    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return password;
}

void View::showMenu() {
    std::cout << "\n1. Register\n2. Login\n3. View Movies\n4. Add Review\n5. View Reviews\n6. Exit\nChoice: ";
}

int View::getChoice() {
    int choice;
    std::cin >> choice;
    std::cin.ignore();
    return choice;
}

std::string View::getUsername() {
    std::string name;
    std::cout << "Username: ";
    std::getline(std::cin, name);
    return name;
}

std::string View::getPassword() {
    return getHiddenPassword();
}

void View::showMessage(const std::string &msg) {
    std::cout << msg << std::endl;
}

void View::showError(const std::string &msg) {
    std::cerr << "Error: " << msg << std::endl;
}

void View::showMovies(const std::vector<Movie> &movies) {
    for (const auto &m : movies)
        std::cout << m.id << ". " << m.title << " (" << m.genre << ", " << m.year << ") - Rating: " << m.rating << "\n";
}

int View::getMovieId(const std::vector<Movie> &movies) {
    int id;
    std::cout << "Enter movie ID: ";
    std::cin >> id;
    std::cin.ignore();
    return id;
}

int View::getRating() {
    int r;
    std::cout << "Enter rating (1–5): ";
    std::cin >> r;
    std::cin.ignore();
    return r;
}

std::string View::getReview() {
    std::string review;
    std::cout << "Enter review: ";
    std::getline(std::cin, review);
    return review;
}

void View::showReviews(const std::vector<Review> &reviews) {
    for (const auto &r : reviews)
        std::cout << r.username << " rated " << r.rating << "/5: " << r.text << "\n";
}

