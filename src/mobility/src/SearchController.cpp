#include "SearchController.h"

SearchController::SearchController() {
  rng = new random_numbers::RandomNumberGenerator();
}

/**
 * This code implements a basic random walk search.
 */
geometry_msgs::Pose2D SearchController::search(geometry_msgs::Pose2D currentLocation, float myAngle, float myLength) {
  geometry_msgs::Pose2D goalLocation;

  //select new heading from Gaussian distribution around current heading
  goalLocation.theta = 
  myAngle;

  //select new position 50 cm from current location
  goalLocation.x = currentLocation.x + (myLength * cos(goalLocation.theta));
  goalLocation.y = currentLocation.y + (myLength * sin(goalLocation.theta));

  return goalLocation;
}

/**
 * Continues search pattern after interruption. For example, avoiding the
 * center or collisions.
 */
geometry_msgs::Pose2D SearchController::continueInterruptedSearch(geometry_msgs::Pose2D currentLocation, geometry_msgs::Pose2D oldGoalLocation, int myObstacle) {
  geometry_msgs::Pose2D newGoalLocation;
  

	/* myObstacle decides whether this function is being called by targetHandler or obstacleHandler 
	 * targetHandler = 1
	 * obstacleHandler = 2
	 */
  //remainingGoalDist avoids magic numbers by calculating the dist
  double remainingGoalDist = hypot(oldGoalLocation.x - currentLocation.x, oldGoalLocation.y - currentLocation.y);

  //this of course assumes random walk continuation. Change for diffrent search methods.
  newGoalLocation.theta = oldGoalLocation.theta;
  newGoalLocation.x = currentLocation.x + (1 * cos(newGoalLocation.theta)); //(remainingGoalDist * cos(oldGoalLocation.theta));
  newGoalLocation.y = currentLocation.y + (1 * sin(newGoalLocation.theta)); //(remainingGoalDist * sin(oldGoalLocation.theta));

  return newGoalLocation;
}
