#include "grid.h"

Grid::Grid(int cellsX_, int cellsY_, int cellsZ_, Vector3D cellSize_) {
  std::cout << "Making new grid." << std::endl;
  cellsX = cellsX_;
  cellsY = cellsY_;
  cellsZ = cellsZ_;
  cellSize = cellSize_;
  //std::list< std::list< std::list< Cell > > >::iterator itx = cells.begin();
  //std::list< std::list< Cell > >::iterator ity = itx->begin();
  //std::list< Cell >::iterator itz = ity->begin();

  for (int x = 0; x < cellsX; x++) {

    std::vector< std::vector< Cell* > > ycol;
    for (int y = 0; y < cellsY; y++) {

      std::vector< Cell* > zcol;
      for (int z = 0; z < cellsY; z++) {
	Cell* cell = new Cell(Vector3D((double)x * cellSize.x,
				      (double)y * cellSize.y,
				      (double)z * cellSize.z),
			     cellSize);
	zcol.push_back(cell);
      }
      ycol.push_back(zcol);
    }
    cells.push_back(ycol);
  }
}

void Grid::addParticle(Vector3D pos, Vector3D vel, Species species) {
  int xi = std::floor(pos.x/cellSize.x);
  int yi = std::floor(pos.y/cellSize.y);
  int zi = std::floor(pos.z/cellSize.z);
  std::cout << xi << yi << zi << std::endl;

  cells[xi][yi][zi]->addParticle(pos, vel, species);
}

Cell* Grid::getCell(int ix, int iy, int iz) {
  return cells[ix][iy][iz];
}

void Grid::computeDensity() {
  for (int xi = 0; xi < cellsX; xi++) {
    for (int yi = 0; yi < cellsY; yi++) {
      for (int zi = 0; zi < cellsY; zi++) {
	Cube den = cells[xi][yi][zi]->getDensity();
      }
    }
  }
}
