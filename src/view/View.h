#ifndef VIEW_H
#define VIEW_H

#include "Model.h"
#include <string>
#include <vector>

class View {
public:
    void showMenu();
    int getChoice();
    std::string getUsername();
    std::string getPassword();
    void showMessage(const std::string &msg);
    void showError(const std::string &msg);
    void showMovies(const std::vector<Movie> &movies);
    int getMovieId(const std::vector<Movie> &movies);
    int getRating();
    std::string getReview();
    void showReviews(const std::vector<Review> &reviews);
};

#endif
