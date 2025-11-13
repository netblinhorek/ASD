#include <iostream>
#include <stdexcept>

class DSU {
	int* _parent, * _rank;
	size_t _size;
public:
	DSU(size_t size);
	~DSU();
	void union_set(int x, int y);
	int find(int x);
	int find_recurtion(int x);

};

DSU::DSU(size_t size) : _size(size)  {
if(size==0){
	throw std::logic_error("The size cannot be equal to 0");
}
_parent = new int[size];
_rank = new int[size];
for (size_t i = 0; i < size; ++i) {
	_parent[i] = static_cast<int>(i);
	_rank[i] = 0;
}
}
DSU::~DSU(){
	delete[] _parent;
	delete[] _rank; 
}

void DSU::union_set(int x, int y) {
	if (x >= _size || y >= _size || x < 0 || y < 0) {
		throw std::logic_error("Going beyond borders");
	}

	int parent_x = find(x);
	int parent_y = find(y);

	if (_rank[parent_x] < _rank[parent_y]) {
		_parent[parent_x] = parent_y;
	}
	else if (_rank[parent_x] > _rank[parent_y]) {
		_parent[parent_y] = parent_x;
	}
	else {
		_parent[parent_y] = parent_x;
		_rank[parent_x]++;
	}
}
int DSU::find(int x) {
	if (x >= _size || x < 0) {
		throw std::logic_error("Going beyond borders");
	}
	while (x != _parent[x]) {
		x = _parent[x];
	}
	return x;
}
int DSU::find_recurtion(int x) {
	if (_parent[x] == x) {
		return x;
	}
	return x = find(_parent[x]);

}