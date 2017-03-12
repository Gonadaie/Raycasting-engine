#include "Map.h"
#include <iostream>
#include <fstream>
#include "constants.h"
#include <math.h>
#include "trigo_functions.h"

using namespace std;

Map::Map(){
  renderingRect = {0, 0, 4, 4};
}

Map::~Map(){
  for(unsigned int i = 0; i < width; ++i){
    delete cells[i];
    cells[i] = NULL;
  }
  delete[] cells;
  cells = NULL;
}

bool Map::loadMap(char* path){
  ifstream file;
  file.open(path, ios::in);
  if(file == NULL){
    cerr << "Error : Could not load " << path << endl;
    return false;
  }
  else{

    file >> width;
    file >> height;
    unsigned int cellSize;
    file >> cellSize;

    //initialize each row
    cells = new unsigned int*[width];

    //initialize each column
    for(unsigned int i = 0; i < width; ++i){
        cells[i] = new unsigned int[height];
    }

    for(unsigned int i = 0; i < height; ++i){
      for(unsigned int j = 0; j < width; ++j){
        file >> cells[j][i];
      }
    }
    cout << path << " has been loaded" << endl;
    file.close();
    return true;
  }
}

void Map::render(SDL_Renderer* renderer, SDL_Rect* miniMap, Entity* player){
  //SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  //SDL_RenderFillRect(renderer, miniMap);

  SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);

  for(unsigned int i = 0; i < width; ++i){
    for(unsigned int j = 0; j < height; ++j){
      if(cells[i][j] == 1001){
        renderingRect = {miniMap->x + i*PIXELSIZE, miniMap->y + j*PIXELSIZE, PIXELSIZE, PIXELSIZE};
        SDL_RenderFillRect(renderer, &renderingRect);
      }
    }
  }
  SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);
  renderingRect = {(int)(miniMap->x + player->getXX()), (int)(miniMap->y + player->getYY()), PIXELSIZE, PIXELSIZE};
  SDL_RenderFillRect(renderer, &renderingRect);
  renderingRect = {(int)((miniMap->x + player->getXX())+PIXELSIZE*cos(-player->getAngle()*3.14f/180)), (int)((miniMap->y + player->getYY())+PIXELSIZE*sin(-player->getAngle()*3.14f/180)), PIXELSIZE, PIXELSIZE};
  SDL_RenderFillRect(renderer, &renderingRect);
}

int Map::getCellAt(int x, int y){
  //cerr << x << " : " << y << endl;
  if(0 <= x && x < width && 0 <= y && y < height)
    return cells[x][y];
  else
    return -1;
}

bool Map::isFacingWall(float ox, float oy, bool right, bool up, bool vertical){

  if(vertical){
    if(right){
      if(up)
        return getCellAt(ox, oy) == 1001;
      else
        return getCellAt(ox, oy) == 1001;
    }
    else{
      if(up)
        return getCellAt(ox-1, oy) == 1001;
      else
        return getCellAt(ox-1, oy) == 1001;
    }
  }
  else{
    if(right){
      if(up)
        return getCellAt(ox, oy-1) == 1001;
      else
        return getCellAt(ox, oy) == 1001;
    }
    else{
      if(up)
        return getCellAt(ox, oy-1) == 1001;
      else
        return getCellAt(ox, oy) == 1001;
    }
  }
}


float Map::findDistance(float ox, float oy, float angle){
  float cell[2] = {ox, oy};
  angle = -angle;
  float distX = cos(angle*PI/180)*0.01f;
  float distY = sin(angle*PI/180)*0.01f;
  while(getCellAt((unsigned int)cell[0], (unsigned int)cell[1]) != 1001){

    cell[0] += distX;
    cell[1] += distY;
    if((int)cell[0] >= width || (int)cell[0] < 0 || (int)cell[1] >= height || (int)cell[1] < 0)
      return -1;
  }

  return sqrt((cell[0]-ox)*(cell[0]-ox) + (cell[1]-oy)*(cell[1]-oy));
}

float Map::findNearestWall(float ox, float oy, float& ix, float& iy, float angle){
  //Variables
  float vPointX = ox;
  float vPointY = oy;
  float vDistanceX, vDistanceY;

  float hPointX = ox;
  float hPointY = oy;
  float hDistanceX, hDistanceY;

  float verticalDistanceFound = -1;
  float horizontalDistanceFound = -1;

  //If not 0 < angle < 360 then correct the angle value
  updateAngle(angle);
  float initialAngle = angle;
  bool up = (angle >= 0 && angle < 180);
  bool right = !(angle >= 90 && angle < 270);

  if(up){
    if(!right)
      angle -= 90;
  }
  else{
    if(!right)
      angle -= 180;
    else
      angle -= 270;
  }

  updateAngle(angle);
  //Conversion from degrees to radians --> cos() sin() tan() take an angle in radians
  angle = degreesToRadians(angle);

  //float distanceCorrection = getDistanceCorrection(angle, right, up);

  // --- Find nearest intersections --- //

  //Vertical
  if(right){
    vPointX = trunc(ox) + 1;
    vDistanceX = vPointX - ox;
    if(up){
      vDistanceY = vDistanceX * tan(angle);
      vPointY = oy - vDistanceY;
      vDistanceY = tan(angle);
    }
    else{
      vDistanceY = vDistanceX / tan(angle);
      vPointY = oy + vDistanceY;
      vDistanceY = 1 / tan(angle);
    }
  }
  else{
    vPointX = trunc(ox);
    vDistanceX = ox - vPointX;
    if(up){
      vDistanceY = vDistanceX / tan(angle);
      vPointY = oy - vDistanceY;
      vDistanceY = 1 / tan(angle);
    }
    else{
      vDistanceY = vDistanceX * tan(angle);
      vPointY = oy + vDistanceY;
      vDistanceY = tan(angle);
    }
  }

  //Horizontal
  if(up){
    hPointY = trunc(oy);
    hDistanceY = oy - hPointY;
    if(right){
      hDistanceX = hDistanceY / tan(angle);
      hPointX = ox + hDistanceX;
      hDistanceX = 1 / tan(angle);
    }
    else{
      hDistanceX = hDistanceY * tan(angle);
      hPointX = ox - hDistanceX;
      hDistanceX = tan(angle);
    }
  }
  else{
    hPointY = trunc(oy) + 1;
    hDistanceY = hPointY - oy;
    if(right){
      hDistanceX = hDistanceY * tan(angle);
      hPointX = ox + hDistanceX;
      hDistanceX = tan(angle);
    }
    else{
      hDistanceX = hDistanceY / tan(angle);
      hPointX = ox - hDistanceX;
      hDistanceX = 1 / tan(angle);
    }
  }

  //cerr << "vPointX : " << vPointX << " vPointY : " << vPointY << endl;

  while(!isFacingWall(vPointX, vPointY, right, up, true)){
    //cerr << "vx : " << vPointX << " vy : " << vPointY << endl;
    //cerr << "vDistX : " << vDistanceX << " vDistY : " << vDistanceY << endl;
    //Vertical
    if(right){
      ++vPointX;
      if(up)
        vPointY -= vDistanceY;
      else
        vPointY += vDistanceY;
    }
    else{
      --vPointX;
      if(up)
        vPointY -= vDistanceY;
      else
        vPointY += vDistanceY;
    }
    if(vPointX < 0 || vPointX >= width || vPointY < 0 || vPointY >= height)
      break;
  }

  while(!isFacingWall(hPointX, hPointY, right, up, false)){
    //Horizontal
    if(up){
      --hPointY;
      if(right)
        hPointX += hDistanceX;
      else
        hPointX -= hDistanceX;
    }
    else{
      ++hPointY;
      if(right)
        hPointX += hDistanceX;
      else
        hPointX -= hDistanceX;
    }
    if(hPointX < 0 || hPointX >= width || hPointY < 0 || hPointY >= height)
      break;
  }

  if(isFacingWall(vPointX, vPointY, right, up, true))
    verticalDistanceFound = distanceBetween(ox, oy, vPointX, vPointY);
  if(isFacingWall(hPointX, hPointY, right, up, false))
    horizontalDistanceFound = distanceBetween(ox, oy, hPointX, hPointY);

  if(verticalDistanceFound != -1 && horizontalDistanceFound != -1){
    verticalDistanceFound = distanceBetween(ox, oy, vPointX, vPointY);
    horizontalDistanceFound = distanceBetween(ox, oy, hPointX, hPointY);
    if(min(verticalDistanceFound, horizontalDistanceFound) == verticalDistanceFound){
      ix = vPointX;
      iy = vPointY;
      return verticalDistanceFound;
    }
    else{
      ix = hPointX;
      iy = hPointY;
      return horizontalDistanceFound;
    }
  }
  else{
    if(verticalDistanceFound != -1 && horizontalDistanceFound == -1){
      ix = vPointX;
      iy = vPointY;
      return verticalDistanceFound;
    }
    if(verticalDistanceFound == -1 && horizontalDistanceFound != -1){
      ix = hPointX;
      iy = hPointY;
      return horizontalDistanceFound;
    }
  }
  return -1;

}
