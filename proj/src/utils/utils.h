/**
 * @brief This file contains 2 simple utilitary functions
 * 
 */
#define FRAME_RATE 60
#define PLAYER_V 200
#define CAT_V 30
#define SELECT_RADIUS 70


/**
 * @brief Generates a random number between lower_bound and upper_bound
 * 
 * @param lower_bound lower bound
 * @param upper_bound upper bound
 * @return generated number
 */
int randomNumer(int lower_bound, int upper_bound);
/**
 * @brief Converts an angle in degrees to radians
 * 
 * @param angleInDegrees angle in degrees
 * @return angle in radians 
 */
double degToRad(double angleInDegrees);
/**
 * @brief Converts an angle in radians to an angle in degrees
 * 
 * @param angleInRad angle in radians
 * @return angle in degrees
 */
double radToDeg(double angleInRad);
