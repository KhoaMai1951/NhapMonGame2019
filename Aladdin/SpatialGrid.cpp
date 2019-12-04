#include "SpatialGrid.h"
#include <sstream>
#include <fstream>
SpatialGrid* SpatialGrid::instance = nullptr;

SpatialGrid* SpatialGrid::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new SpatialGrid();
    }
	return instance;
};

void SpatialGrid::Clear()
{
	map<string, vector<CGameObject*>>::iterator it;
	for (it = Grid.begin(); it != Grid.end(); ++it)
		it->second.clear();
	Grid.clear();
};

void SpatialGrid::SetCell(int cell_size)
{
	Clear();
	CellSize = cell_size;
};


//Lấy vị trí index x, y của các Cell chứa object
void SpatialGrid::Index(CGameObject* object, float& x1, float& y1, float& x2, float& y2)
{
	object->GetBoundingBox(x1, y1, x2, y2);
	RECT temp = ViewPort::getInstance()->InvertY(x1, y1, x2, y2, object->width, object->height);
	/*x1 = floor(x1 / CellSize);
	y1 = floor(y1 / CellSize);
	x2 = ceil(x2 / CellSize);
	y2 = ceil(y2 / CellSize);*/
	
	x1 = floor(temp.left / CellSize);
	y1 = floor(temp.top / CellSize);
	x2 = ceil(temp.right / CellSize);
	y2 = ceil(temp.bottom / CellSize);
};

//Insert 1 vật thể vào các Cell có chứa vật thể đó
void SpatialGrid::Insert(CGameObject* object, string FileName)
{
	float x1, y1, x2, y2;
	float i, j;
	Index(object, x1, y1, x2, y2);
	stringstream ss;
	for (i = x1; i < x2; ++i)
		for (j = y1; j < y2; ++j)
		{
			//add object to grid
			Grid[IndexMakeKey(ss, i, j)].push_back(object);
			//write object's   position in grid to text file
			std::ofstream outfile;
			outfile.open(FileName, std::ios_base::app); // append instead of overwrite
			outfile << i << " " << j << " " << object->id << "\n";
		}
			
}

/* lấy danh sách các vật thể thuộc tọa độ của lưới
( dùng cho nhân vật chính của game, để lấy danh sách các vật thể còn lại thuộc
các Cell có chứa nhân vật chính, để xét va chạm của lưới */

set<CGameObject*> SpatialGrid::Get(float x1, float y1, float x2, float y2)
{
	currentKeys.clear();
	// Determine which grid cell it's in.

	x1 = floor(x1 / CellSize);
	y1 = floor(y1 / CellSize);
	x2 = ceil(x2 / CellSize);
	y2 = ceil(y2 / CellSize);
	

	
	set<CGameObject*> result;
	stringstream ss;
	string key;


	for (float i = x1; i < x2; i++)
		for (float j = y1; j < y2; j++)
		{
			key = IndexMakeKey(ss, i, j);
			currentKeys.push_back(key);
			vector<CGameObject*> v_cell = Grid[key];
			result.insert(v_cell.begin(), v_cell.end());
		}
	
	return result;
};

set<CGameObject*> SpatialGrid::GetGridForCollision(float x1, float y1, float x2, float y2)
{
    // Determine which grid cell it's in.

    x1 = floor(x1 / CellSize);
    y1 = floor(y1 / CellSize);
    x2 = ceil(x2 / CellSize);
    y2 = ceil(y2 / CellSize);


    set<CGameObject*> result;
    stringstream ss;
    string key;


    for (float i = x1; i < x2; i++)
        for (float j = y1; j < y2; j++)
        {
            key = IndexMakeKey(ss, i, j);
            vector<CGameObject*> v_cell = Grid[key];
            result.insert(v_cell.begin(), v_cell.end());
        }

    return result;
};

//Add grid from file
void SpatialGrid::AddGridFromFile(vector<LPGAMEOBJECT> objects, string FileName)
{
	std::ifstream infile(FileName);
	//check if file exists, then add grid from text file
	if (infile.good())
	{
		float cell_x, cell_y;
		int object_id;
		stringstream ss;

		while (infile >> cell_x >> cell_y >> object_id)
		{
			Grid[IndexMakeKey(ss, cell_x, cell_y)].push_back(objects[object_id]);
		}
	}
	//if file not exists, insert grid normally and then create new text file
	else
	{
		for (unsigned i = 1; i < objects.size(); i++)
			Insert(objects[i], FileName);
	}
}

void SpatialGrid::DeleteFromGrid(int id)
{
	for (int i = 0; i < currentKeys.size(); i++)
	{

		for (int j = 0; j < Grid[currentKeys[i]].size(); j++)
		{
			if (j == Grid[currentKeys[i]].size() - 1 && i == currentKeys.size()-1)
			{
				int a = 0;
			}
			if (Grid[currentKeys[i]][j]->id == id)
			{
				Grid[currentKeys[i]].erase(Grid[currentKeys[i]].begin() + j);
				break;
			}
		}
	}
}


//Tạo key thứ tự Cell
string SpatialGrid::IndexMakeKey(stringstream& ss, float& x, float& y)
{
	ss.str(std::string());
	ss << x << "_" << y;
	return ss.str();
};