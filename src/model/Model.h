#ifndef MODEL_H
#define MODEL_H

#include <sqlite3.h>
#include <string>
#include <vector>

struct Movie {
    int id;
    std::string title;
    std::string genre;
    int year;
    double rating;
};

struct Review {
    std::string username;
    int rating;
    std::string text;
};

class Model {
private:
    sqlite3* db;
public:
    Model();
    ~Model();
    bool openDatabase(const std::string &filename);
    void closeDatabase();
    void initializeDatabase();
    void insertSampleMovies();
    bool registerUser(const std::string &username, const std::string &password);
    bool loginUser(const std::string &username, const std::string &password);
    std::vector<Movie> getMovies();
    bool addReview(const std::string &username, int movie_id, int rating, const std::string &review);
    std::vector<Review> getReviews(int movie_id);
    double getAverageRating(int movie_id);
    void updateMovieRating(int movie_id, double avgRating);
};

#endif
