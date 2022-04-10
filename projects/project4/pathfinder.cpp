#include <iostream>
#include "deque.hpp"
#include "image.cpp"
#include <vector>
#include <cstdlib>

//this is used to store the values of the current square being visited
struct Square {
  intmax_t row; //row of current square
  intmax_t col; //column of current sqaure
  bool **visited; //creates a 2d array of bool values for
  //all the possible square indexes

  Square(intmax_t width, intmax_t height){
    //creates an array of boolean pointers of length width
    visited = new bool*[width];

    for (intmax_t i = 0; i < width; i++){
      //this for loop fills each index i in visited with a
      //boolean array of length height, effectively creating a
      //2d array of dimensions, width by height
      visited[i] = new bool[height];
    }

    //this just initiates all values in visited to false
    for (intmax_t j = 0; j < width; j++){
      for (intmax_t k = 0; k < height; k++){
        visited[j][k] = false;
      }
    }//end nested initiation loops
  }//end square

//this sets the current square as visited
  void setVisit(){
    visited[row][col] = true;
  }

  //returns whether or not the current square has been visited
  bool checkVisit(){
    return visited[row][col];
  }
};

//this function is a breadth first search algorithm that we use to find
//the shortest path out of the maze, takes a deque and image input, 
// the intmax_t variables passed by reference will end up storing
//the row and column of the end point
bool breadthFirstSearch(Deque<intmax_t> &, Image<Pixel> &, intmax_t &, intmax_t &);

//this function checks the next pixels from the current one
//to determine if it can be travelled to or if it is an endpoint
//the two intmax_t variables are for the coordinates
//and the image is for the maze picture
bool checkNextPosition(Image<Pixel> &, intmax_t, intmax_t);

int main(int argc, char *argv[])
{
  // get input/output file names from command line arguments
  if (argc != 3) {
    std::cout << "Usage: compare"
              << "<first_input_filename> <second_output_filename>\n"
              << std::endl;
    return EXIT_FAILURE;
  }

  Deque<intmax_t> frontier; //creates our empty deque
  Image<Pixel> input = readFromFile(argv[1]); //stores first argument as a png file
  
  //stores rgb values
  uint8_t redVal;
  uint8_t greenVal;
  uint8_t blueVal;
  uint8_t alphaVal;
  Pixel colorVal;

  //keeps track if we've found the start point yet
  bool foundRedPixel = false;

  for (intmax_t i = 0; i < input.width(); i++){
    for (intmax_t j = 0; j < input.height(); j++){
      //here we store the raw color value of each pixel
      //at index i,j
      redVal = input(i,j).red;
      greenVal = input(i,j).green;
      blueVal = input(i,j).blue;
      alphaVal = input(i,j).alpha;
      colorVal = {redVal, greenVal, blueVal, alphaVal};

      //check pixel color against one that is already predefined
      if ((colorVal != BLACK) && (colorVal != WHITE) && (colorVal != RED)){
        std::cout << "ERROR! Invalid pixel color." << std::endl;
        return EXIT_FAILURE;
      }

      //check for if we found red start pixel
      if (colorVal == RED){
        if (foundRedPixel == false){
          //so this if is saying we found the red pixel and
          //we hadn't found another one already
          //in that case we update the foundRedPixel
          //and by pushing i and j into the deque, we set that coord
          //pair as the first one
          foundRedPixel = true;
          frontier.pushBack(i);
          frontier.pushBack(j);
        }
        else{
          //if we found one already we have to output an error
          std::cout<<"ERROR! found more than one red pixel"<<std::endl;
          return EXIT_FAILURE;
        }
      }//end check red pixel


    }//close i (col) loop
  }//close j (row) loop
  
  //if we scan the whole image and cant find a start then we
  //output another error message
  if (foundRedPixel == false){
    std::cout<< "ERROR! couldn;t find a red starting pixel"<<std::endl;
    return EXIT_FAILURE;
  }
  
  intmax_t row, col; //these will store the exit coordinates
  bool foundExit = breadthFirstSearch(frontier, input, row, col);

  //plugs exit coord into maze
  if (foundExit){
    std::cout << "maze exited!!"<<std::endl;
    input(row,col).red = 0;
    input(row, col).green = 255;
    input(row, col).blue = 0;
    input(row, col).alpha = 255;
  }
  else{
    //for if we can;t find an exit
    std::cout<<"could't find an exit :("<<std::endl;
  }

  //creates output file using input file
  writeToFile(input, argv[2]);
  return EXIT_SUCCESS;
}//end main function


bool breadthFirstSearch(Deque<intmax_t> &frontier, Image<Pixel> &img, intmax_t &r, intmax_t &c){
  //this is holds whether or not the the position is valid
  bool validPosition;

  //creates a structure to hold info about current position in maze
  Square currentPos(img.width(), img.height());

  while (!frontier.isEmpty()){
    //so the frontier deque is holding the coordinate pairs of the picture
    //and here we are popping them out and into the square struct
    currentPos.row = frontier.front();
    frontier.popFront();
    currentPos.col = frontier.front();
    frontier.popFront();

    //this checks if the current coordinate pair
    //has been visited and proceeds accordingly
    bool visit = currentPos.checkVisit();
    if (visit){
      continue;
    }

    //if we make it here now we have to mark these coords as visited
    currentPos.setVisit();

    //check the row below our current one
    validPosition = checkNextPosition(img, currentPos.row - 1, currentPos.col);
    //if the square in the row right below our current space
    //is valid then we continue into this statement
    if (validPosition){
      //this is checking to see if the row below our current pos
      //is the bottom edge of the picture and we can update r and c
      if (currentPos.row-1==0){
        r = currentPos.row-1;
        c = currentPos.col;
        return true;
      }

      //if not we push this coord pair to the back of the deque
      frontier.pushBack(currentPos.row -1);
      frontier.pushBack(currentPos.col);
    }//end below row if

    //checks next row up
    validPosition = checkNextPosition(img, currentPos.row + 1, currentPos.col);
    if (validPosition){
      //checks if we found a valid exit at the top of the maze
      if (currentPos.row + 1 == img.height() - 1){
        r = currentPos.row + 1;
        c = currentPos.col;
        return true;
      }
      //if it isn't an exit then we push the coord pair to
      //the pack of the deque
      frontier.pushBack(currentPos.row+1);
      frontier.pushBack(currentPos.col);
    }//end above row check

    //checks previous (left) column
    validPosition = checkNextPosition(img, currentPos.col, currentPos.col - 1);
    if (validPosition){
      //again check for edge exit
      if (currentPos.col - 1 == 0){
        r = currentPos.row;
        c = currentPos.col - 1;
        return true;
      }
      //if not exit again push back
      frontier.pushBack(currentPos.row);
      frontier.pushBack(currentPos.col - 1);
    }//end left column check

    //final check this time the right column
    validPosition = checkNextPosition(img, currentPos.col, currentPos.col + 1);
    if (validPosition){
      //check for right edge exit
      if (currentPos.col + 1 == img.width() - 1){
        r = currentPos.row;
        c = currentPos.col + 1;
        return true;
      }
      frontier.pushBack(currentPos.row);
      frontier.pushBack(currentPos.col + 1);
    }//end right column check
  }//end while loop
  
  //if we get here we have either hit a dead end of there is no
  //exit
  return false;
}

bool checkNextPosition(Image<Pixel> &img, intmax_t r, intmax_t c){
  //checks validity of row and column
  if (r < 0 || r >= img.height() || c < 0 || c >= img.width()){
    return false;
  }

  //now we store the color of the pixel
  Pixel indexColor = {img(r,c).red, img(r,c).green, img(r,c).blue, img(r,c).alpha};

  //if the pixel at row,col is black its a wall so we return false
  if (indexColor == BLACK){
    return false;
  }

  //otherwise it passes and is valid
  return true;

}//end check next position