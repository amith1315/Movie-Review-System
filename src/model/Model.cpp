#include "Model.h"
#include <iostream>
#include <sstream>

Model::Model() : db(nullptr) {}

Model::~Model() {
    closeDatabase();
}

bool Model::openDatabase(const std::string &filename) {
    return sqlite3_open(filename.c_str(), &db) == SQLITE_OK;
}

void Model::closeDatabase() {
    if (db) sqlite3_close(db);
}

void Model::initializeDatabase() {
    const char *createUsers = "CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT);";
    const char *createMovies = "CREATE TABLE IF NOT EXISTS movies (id INTEGER PRIMARY KEY, title TEXT, genre TEXT, year INTEGER, rating REAL);";
    const char *createReviews = "CREATE TABLE IF NOT EXISTS reviews (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT, movie_id INTEGER, rating INTEGER, review TEXT);";

    char *errMsg = nullptr;
    sqlite3_exec(db, createUsers, nullptr, nullptr, &errMsg);
    sqlite3_exec(db, createMovies, nullptr, nullptr, &errMsg);
    sqlite3_exec(db, createReviews, nullptr, nullptr, &errMsg);
}

void Model::insertSampleMovies() {
    std::vector<std::string> movies = {
        "INSERT OR IGNORE INTO movies VALUES (1, 'Inception', 'Sci-Fi', 2010, 0.0);",
        "INSERT OR IGNORE INTO movies VALUES (2, 'Titanic', 'Romance', 1997, 0.0);"
    };
    for (const auto &query : movies)
        sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);
}

bool Model::registerUser(const std::string &username, const std::string &password) {
    std::string sql = "INSERT INTO users (username, password) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    bool success = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return success;
}

bool Model::loginUser(const std::string &username, const std::string &password) {
    std::string sql = "SELECT * FROM users WHERE username = ? AND password = ?;";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    bool found = sqlite3_step(stmt) == SQLITE_ROW;
    sqlite3_finalize(stmt);
    return found;
}

std::vector<Movie> Model::getMovies() {
    std::vector<Movie> movies;
    const char *sql = "SELECT * FROM movies;";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Movie m;
        m.id = sqlite3_column_int(stmt, 0);
        m.title = (const char*)sqlite3_column_text(stmt, 1);
        m.genre = (const char*)sqlite3_column_text(stmt, 2);
        m.year = sqlite3_column_int(stmt, 3);
        m.rating = sqlite3_column_double(stmt, 4);
        movies.push_back(m);
    }
    sqlite3_finalize(stmt);
    return movies;
}

bool Model::addReview(const std::string &username, int movie_id, int rating, const std::string &review) {
    std::string sql = "INSERT INTO reviews (username, movie_id, rating, review) VALUES (?, ?, ?, ?);";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, movie_id);
    sqlite3_bind_int(stmt, 3, rating);
    sqlite3_bind_text(stmt, 4, review.c_str(), -1, SQLITE_STATIC);
    bool success = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return success;
}

std::vector<Review> Model::getReviews(int movie_id) {
    std::vector<Review> reviews;
    std::string sql = "SELECT username, rating, review FROM reviews WHERE movie_id = ?;";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, movie_id);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Review r;
        r.username = (const char*)sqlite3_column_text(stmt, 0);
        r.rating = sqlite3_column_int(stmt, 1);
        r.text = (const char*)sqlite3_column_text(stmt, 2);
        reviews.push_back(r);
    }
    sqlite3_finalize(stmt);
    return reviews;
}

double Model::getAverageRating(int movie_id) {
    std::string sql = "SELECT AVG(rating) FROM reviews WHERE movie_id = ?;";
    sqlite3_stmt *stmt;
    double avg = 0.0;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, movie_id);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            avg = sqlite3_column_double(stmt, 0);
        }
    }
    sqlite3_finalize(stmt);
    return avg;
}

void Model::updateMovieRating(int movie_id, double avgRating) {
    std::string sql = "UPDATE movies SET rating = ? WHERE id = ?;";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_double(stmt, 1, avgRating);
    sqlite3_bind_int(stmt, 2, movie_id);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}
