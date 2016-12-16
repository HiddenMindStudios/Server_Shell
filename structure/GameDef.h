#pragma once
#include "stdafx.h"
#include <vector>
#define INVENTORY_ITEM_MAX 255
const int MAPID_COUNT = 1;

enum GridTileType{
	GRID_OPEN = 0,
	GRID_BLOCK,
	GRID_DMG,
	GRID_HEAL
};

struct MapBounding{
	const int width;
	const int height;
	int** grid;
	MapBounding(int w, int h) :width(w), height(h){
		grid[width][height];
	}
};

struct MapData{
	int id;
	std::string name;
	//Asset load (MapBounding, etc.)
	MapData(int i, std::string n) : id(i), name(n){};
};

struct Item{
	int id;
	int cost;
	int count;
	bool stackable;
};

typedef std::vector<Item> vItem;

class Inventory{
	int itemMax;
	vItem items;
	int itemCount;
public:
	Inventory(){
		itemMax = 0;
		items = vItem();
		itemCount = 0;
	};
	Inventory(int max){
		if (max <= INVENTORY_ITEM_MAX)
			itemMax = max;
		else
			itemMax = 0;
		items = vItem();
		itemCount = 0;
	};
	Inventory(Inventory& inv){
		itemMax = inv.itemMax;
		itemCount = inv.itemCount;
		items = inv.items;
	}
	inline int getItemCount(){ return itemCount; };
	inline int getItemMax(){ return itemMax; };
	bool setItemMax(int max){
		if (max <= INVENTORY_ITEM_MAX){
			itemMax = max;
			return true;
		}
		return false;
	}
	bool addItem(Item it, int iCount){
		bool bItem = hasItem(it.id);
		bool bStack = it.stackable;
		//item is stackable, dont have it, itemCount == max; item isn't stackable, itemCount+iCount > max
		if ((bStack && !bItem && itemCount == itemMax) || (!bStack && itemCount + iCount > itemMax))
			return false;
		//Have item and is stackable
		else if (bItem && bStack){
			for (vItem::iterator t = items.begin(); t != items.end(); ++t){
				if (t->id == it.id){
					t->count += iCount;
					return true;
				}
			}
		}
		//Isn't stackable and itemCount + iCount less than or equal to max
		else if (!bStack){
			for (int i = 0; i < iCount; ++i){
				items.push_back(it);
			}
			return true;
		}
		//Don't have item and is stackable and itemCount+1 <= max
		else if (!bItem && bStack){
			it.count = iCount;
			itemCount++;
			items.push_back(it);
			return true;
		}
		return false;
	};
	bool hasItem(int id){
		for (vItem::iterator t = items.begin(); t != items.end(); ++t){
			if (t->id == id)
				return true;
		}
		return false;
	};
	bool removeItem(int id, int c){
		for (vItem::iterator t = items.begin(); t != items.end(); ++t){
			if (t->id == id){
				int count = t->count;
				if (count == c){
					items.erase(t);
					itemCount--;
					return true;
				}
				else if (count < c){
					t->count -= c;
					return true;
				}
				else if (count > c){
					return false;
				}
			}
		}
	}
};