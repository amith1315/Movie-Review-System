#include "Controller.h"
#include "Model.h"
#include "View.h"

void Controller::run() {
    Model model;
    View view;
	if (!model.openDatabase("movie.db")) {
	    view.showError("Failed to open database.");
	    return;
	}

	model.initializeDatabase();
	model.insertSampleMovies();

	std::string username;
	int choice;

	do {
	    view.showMenu();
	    choice = view.getChoice();

	    switch (choice) {
		case 1: { // Register
		    std::string newUsername = view.getUsername();
		    std::string newPassword = view.getPassword();
		    model.registerUser(newUsername, newPassword);
		    view.showMessage("User registered successfully!");
		    break;
		}

		case 2: { // Login
		    std::string inputUsername = view.getUsername();
		    std::string inputPassword = view.getPassword();
		    if (model.loginUser(inputUsername, inputPassword)) {
		        username = inputUsername;
		        view.showMessage("Login successful!");
		    } else {
		        view.showError("Invalid credentials.");
		    }
		    break;
		}

		case 3: { // View Movies
		    view.showMovies(model.getMovies());
		    break;
		}

		case 4: { // Add Review
		    if (!username.empty()) {
		        int movie_id = view.getMovieId(model.getMovies());
		        int rating = view.getRating();
		        std::string review = view.getReview();
		        model.addReview(username, movie_id, rating, review);
		        double newRating = model.getAverageRating(movie_id);
		        model.updateMovieRating(movie_id, newRating);
		        view.showMessage("Review added successfully! New rating: " + std::to_string(newRating));
		    } else {
		        view.showError("Please login first.");
		    }
		    break;
		}

		case 5: { // View Reviews
		    view.showReviews(model.getReviews(view.getMovieId(model.getMovies())));
		    break;
		}

		case 6: { // Exit
		    view.showMessage("Exiting...");
		    model.closeDatabase();
		    return;
		}

		default: {
		    view.showError("Invalid choice.");
		}
	    }
	} while (true);
}

