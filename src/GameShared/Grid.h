#ifndef _GRID_H_
#define _GRID_H_

#include "Sys.h"
#include "Logger.h"
#include "Entry.h"

#define NINE_GRID_NUM 9

//
template <typename T>
class Grid
{
public:
	~Grid()
	{
	
	}

	bool Init();
	void Clear();

	void AddObject(T *);
	void RemoveObject(T *);
	T *HaveObject(uint64_t uid);
public:
	std::map<uint64_t, T *>  m_units;
	uint64_t sceneId;
};

template <typename T>
bool Grid<T>::Init()
{

	return true;
}

template <typename T>
void Grid<T>::Clear()
{

	return ;
}

template <typename T>
void Grid<T>::AddObject(T *ptr)
{
	m_units[ptr->Uid()] = ptr;
	ptr->SetGrid(this);

	return ;
}

template <typename T>
void Grid<T>::RemoveObject(T *ptr)
{
	typename std::map<uint64_t, T *>::iterator itr = m_units.find(ptr->Uid());
	if (itr != m_units.end())
	{
		itr->second->SetGrid(NULL);
		m_units.erase(itr);
	}

	return ;
}

template <typename T>
T *Grid<T>::HaveObject(uint64_t uid)
{
	typename std::map<uint64_t, T *>::iterator itr = m_units.find(uid);
	if (itr != m_units.end())
	{
		return itr->second;
	}

	return NULL;
}

//GridVec2Strategy
struct GridVec2Info
{
	int64_t m_xMin;
	int64_t m_yMin;
	int64_t m_xMax;
	int64_t m_yMax;
	uint64_t m_size;
};

template <typename T>
class GridVec2Strategy
{
public:
	GridVec2Strategy()
		:m_x(64), m_y(64), m_size(64)
	{
		m_xIndex = m_x / m_size + 1;
		m_yIndex = m_y / m_size + 1;

		m_vecGrids.resize(m_xIndex * m_yIndex);
	}
	~GridVec2Strategy()
	{
	}

	bool Init(void *);
	void Update();

public:
	inline int64_t X() { return m_x; }
	inline int64_t Y() { return m_y; }
	inline uint64_t Size() { return m_size; }	inline uint64_t YIndex() { return m_yIndex; }

	Grid<T> *GetGrid(T *object);
	Grid<T> *GetGrid(double x, double y, double z);
	bool GetNineGrid(T *object, Grid<T> **);
	bool GetNineGrid(double x, double y, double z, Grid<T> **);

	void DoExec(T *object, double rand, CEntryCallback<T> *exec);
	void DoExec(double x, double y, double z, double rand, CEntryCallback<T> *exec);

	void UpdateScene(uint64_t id, void *);

private:
	std::vector< Grid<T> > m_vecGrids;
	int64_t m_x;
	int64_t m_y;
	int64_t m_xDif;
	int64_t m_yDif;
	uint64_t m_size;
	uint64_t m_xIndex;
	uint64_t m_yIndex;
};

template <typename T>
bool GridVec2Strategy<T>::Init(void *ptr)
{
	GridVec2Info *pos = (GridVec2Info *)ptr;
	m_x = pos->m_xMax - pos->m_xMin;
	m_y = pos->m_xMax - pos->m_yMin;
	m_xDif = pos->m_xMin - 0;
	m_yDif = pos->m_yMin - 0;
	m_size = pos->m_size;
	if (!m_size)
		m_size = 64;

	m_xIndex = m_x / m_size + 1;
	m_yIndex = m_y / m_size + 1;

	m_vecGrids.resize(m_xIndex * m_yIndex);

	return true;
}

template <typename T>
void GridVec2Strategy<T>::Update()
{


	return;
}

template <typename T>
Grid<T> *GridVec2Strategy<T>::GetGrid(T *object)
{
	return GetGrid(object->x, object->y, 0);
}

template <typename T>
Grid<T> *GridVec2Strategy<T>::GetGrid(double x, double y, double z)
{
	uint64_t xindex = (uint64_t)(x - m_xDif) / m_size;
	uint64_t yindex = (uint64_t)(y - m_yDif) / m_size;
	uint64_t at = xindex + yindex * m_xIndex;

	if (at >= (uint64_t)m_vecGrids.size())
	{
		return NULL;
	}

	return &m_vecGrids[at];
}

template <typename T>
bool GridVec2Strategy<T>::GetNineGrid(T *object, Grid<T> **grids)
{
	memset(grids, 0, sizeof(Grid<T> *) * NINE_GRID_NUM);

	if (!object->GetGrid())
		return true;

	uint64_t xindex = (uint64_t)(object->x - m_xDif) / m_size;
	uint64_t yindex = (uint64_t)(object->y - m_yDif) / m_size;

	if (xindex > m_xIndex)
		xindex = m_xIndex;

	if (yindex > m_yIndex)
		yindex = m_yIndex;

	uint64_t xb = 0;
	if (xindex > 1)
		xb = xindex - 1;

	uint64_t xe = m_xIndex;
	if (xindex + 2 < m_xIndex)
		xe = xindex + 2;

	uint64_t yb = 0;
	if (yindex > 1)
		yb = yindex - 1;

	uint64_t ye = m_yIndex;
	if (yindex + 2 < m_yIndex)
		ye = yindex + 2;

	uint32_t index = 0;
	for (uint64_t j = yb; j < ye; ++j)
	{
		for (uint64_t i = xb; i < xe; ++i)
		{
			if (index < NINE_GRID_NUM)
				grids[index++] = &m_vecGrids[i + j * m_xIndex];
			else
				return true;
		}
	}

	return true;
}

template <typename T>
bool GridVec2Strategy<T>::GetNineGrid(double x, double y, double z, Grid<T> **grids)
{
	memset(grids, 0, sizeof(Grid<T> *) * NINE_GRID_NUM);

	uint64_t xindex = (uint64_t)(x - m_xDif) / m_size;
	uint64_t yindex = (uint64_t)(y - m_yDif) / m_size;

	if (xindex > m_xIndex)
		xindex = m_xIndex;

	if (yindex > m_yIndex)
		yindex = m_yIndex;

	uint64_t xb = 0;
	if (xindex > 1)
		xb = xindex - 1;

	uint64_t xe = m_xIndex;
	if (xindex + 2 < m_xIndex)
		xe = xindex + 2;

	uint64_t yb = 0;
	if (yindex > 1)
		yb = yindex - 1;

	uint64_t ye = m_yIndex;
	if (yindex + 2 < m_yIndex)
		ye = yindex + 2;

	uint32_t index = 0;
	for (uint64_t j = yb; j < ye; ++j)
	{
		for (uint64_t i = xb; i < xe; ++i)
		{
			if (index < NINE_GRID_NUM)
				grids[index++] = &m_vecGrids[i + j * m_xIndex];
			else
				return true;
		}
	}
	
	return true;
}

template <typename T>
void GridVec2Strategy<T>::DoExec(T *object, double rand, CEntryCallback<T> *exec)
{
	if (!object->GetGrid())
		return;

	int64_t beginx = (int64_t)(object->x - m_xDif - rand) / (int64_t)m_size;
	if (beginx < 0)
		beginx = 0;

	int64_t endx = (int64_t)(object->x - m_xDif + rand) / (int64_t)m_size + 1;
	if (endx > (int64_t)m_xIndex)
		endx = (int64_t)m_xIndex;
	else if (endx < 0)
		endx = 0;

	int64_t beginy = (int64_t)(object->y - m_yDif - rand) / (int64_t)m_size;
	if (beginy < 0)
		beginy = 0;

	int64_t endy = (int64_t)(object->y - m_yDif + rand) / (int64_t)m_size + 1;
	if (endy >(int64_t)m_yIndex)
		endy = (int64_t)m_yIndex;
	else if (endy < 0)
		endy = 0;

	for (int64_t y = beginy; y < endy; ++y)
	{
		for (int64_t x = beginx; x < endx; ++x)
		{
			uint64_t at = x + y * m_xIndex;
			for (typename std::map<uint64_t, T *>::iterator itr = m_vecGrids[at].m_units.begin(); itr != m_vecGrids[at].m_units.end(); ++itr)
			{
				if (!exec->exec(itr->second))
					return;
			}
		}
	}

	return;
}

template <typename T>
void GridVec2Strategy<T>::DoExec(double x, double y, double z, double rand, CEntryCallback<T> *exec)
{
	int64_t beginx = (int64_t)(x - m_xDif - rand) / (int64_t)m_size;
	if (beginx < 0)
		beginx = 0;

	int64_t endx = (int64_t)(x - m_xDif + rand) / (int64_t)m_size + 1;
	if (endx >(int64_t)m_xIndex)
		endx = (int64_t)m_xIndex;
	else if (endx < 0)
		endx = 0;

	int64_t beginy = (int64_t)(y - m_yDif - rand) / (int64_t)m_size;
	if (beginy < 0)
		beginy = 0;

	int64_t endy = (int64_t)(y - m_yDif + rand) / (int64_t)m_size + 1;
	if (endy >(int64_t)m_yIndex)
		endy = (int64_t)m_yIndex;
	else if (endy < 0)
		endy = 0;

	for (int64_t y = beginy; y < endy; ++y)
	{
		for (int64_t x = beginx; x < endx; ++x)
		{
			uint64_t at = x + y * m_xIndex;
			for (typename std::map<uint64_t, T *>::iterator itr = m_vecGrids[at].m_units.begin(); itr != m_vecGrids[at].m_units.end(); ++itr)
			{
				if (!exec->exec(itr->second))
					return;
			}
		}
	}

	return;
}

template <typename T>
void GridVec2Strategy<T>::UpdateScene(uint64_t id, void *info)
{
	GridVec2Info *pos = (GridVec2Info *)info;
	int64_t beginx = (int64_t)(pos->m_xMin - m_xDif) / (int64_t)m_size;
	if (beginx < 0)
		beginx = 0;
	int64_t endx = (int64_t)(pos->m_xMax - m_xDif) / (int64_t)m_size + 1;
	if (endx > (int64_t)m_xIndex)
		endx = (int64_t)m_xIndex;
	else if (endx < 0)
		endx = 0;

	int64_t beginy = (int64_t)(pos->m_yMin - m_yDif) / (int64_t)m_size;
	if (beginy < 0)
		beginy = 0;

	int64_t endy = (int64_t)(pos->m_yMax - m_yDif) / (int64_t)m_size + 1;
	if (endy > (int64_t)m_yIndex)
		endy = (int64_t)m_yIndex;
	else if (endy < 0)
		endy = 0;

	for (int64_t y = beginy; y < endy; ++y)
	{
		for (int64_t x = beginx; x < endx; ++x)
		{
			uint64_t at = x + y * m_xIndex;
			m_vecGrids[at].sceneId = id;
		}
	}

	return;
}

//GridVec3Strategy
struct GridVec3Info
{
	int64_t m_xMin;
	int64_t m_yMin;
	int64_t m_zMin;
	int64_t m_xMax;
	int64_t m_yMax;
	int64_t m_zMax;
	uint64_t m_size;
	uint64_t m_highSize;
};

template <typename T>
class GridVec3Strategy
{
public:
	GridVec3Strategy()
		:m_x(64), m_y(64), m_z(64), m_size(64), m_highSize(64)
	{
		m_xIndex = m_x / m_size + 1;
		m_yIndex = m_y / m_size + 1;
		m_zIndex = m_z / m_highSize + 1;

		m_vecGrids.resize(m_xIndex * m_yIndex * m_zIndex);
	}
	~GridVec3Strategy()
	{
	}

	bool Init(void *);
	void Update();

public:
	inline int64_t X() { return m_x; }
	inline int64_t Y() { return m_y; }
	inline int64_t Z() { return m_z; }
	inline uint64_t XSize() { return m_size; }
	inline uint64_t HighSize() { return m_highSize; }

	Grid<T> *GetGrid(T *object);
	Grid<T> *GetGrid(double x, double y, double z);

	void DoExec(T *object, double rand, CEntryCallback<T> *exec);
	void DoExec(double x, double y, double z, double rand, CEntryCallback<T> *exec);

private:
	std::vector< Grid<T> > m_vecGrids;
	int64_t m_x;
	int64_t m_y;
	int64_t m_z;
	int64_t m_xDif;
	int64_t m_yDif;
	int64_t m_zDif;
	uint64_t m_size;
	uint64_t m_highSize;
	uint64_t m_xIndex;
	uint64_t m_yIndex;
	uint64_t m_zIndex;
};

template <typename T>
bool GridVec3Strategy<T>::Init(void *ptr)
{
	GridVec3Info *pos = (GridVec3Info *)ptr;
	m_x = pos->m_xMax - pos->m_xMin;
	m_y = pos->m_xMax - pos->m_yMin;
	m_z = pos->m_xMax - pos->m_zMin;
	m_xDif = pos->m_xMin - 0;
	m_yDif = pos->m_yMin - 0;
	m_zDif = pos->m_zMin - 0;
	m_size = pos->m_size;
	if (!m_size)
		m_size = 64;
	m_highSize = pos->m_highSize;
	if (!m_highSize)
		m_highSize = 64;

	m_xIndex = m_x / m_size + 1;
	m_yIndex = m_y / m_size + 1;
	m_zIndex = m_z / m_highSize + 1;

	m_vecGrids.resize(m_xIndex * m_yIndex * m_zIndex);

	return true;
}

template <typename T>
void GridVec3Strategy<T>::Update()
{


	return;
}

template <typename T>
Grid<T> *GridVec3Strategy<T>::GetGrid(T *object)
{
	return GetGrid(object->x, object->y, object->z);
}

template <typename T>
Grid<T> *GridVec3Strategy<T>::GetGrid(double x, double y, double z)
{
	uint64_t xindex = (uint64_t)(x - m_xDif) / m_size;
	uint64_t yindex = (uint64_t)(y - m_yDif) / m_size;
	uint64_t zindex = (uint64_t)(z - m_zDif) / m_highSize;
	uint64_t at = xindex + yindex * m_xIndex + zindex * m_yIndex * m_xIndex;

	if (at >= (uint64_t)m_vecGrids.size())
	{
		return NULL;
	}

	return &m_vecGrids[at];
}

template <typename T>
void GridVec3Strategy<T>::DoExec(T *object, double rand, CEntryCallback<T> *exec)
{
	if (!object->GetGrid())
		return;

	int64_t beginx = (int64_t)(object->x - m_xDif - rand) / (int64_t)m_size;
	if (beginx < 0)
		beginx = 0;

	int64_t endx = (int64_t)(object->x - m_xDif + rand) / (int64_t)m_size + 1;
	if (endx >(int64_t)m_xIndex)
		endx = (int64_t)m_xIndex;
	else if (endx < 0)
		endx = 0;

	int64_t beginy = (int64_t)(object->y - m_yDif - rand) / (int64_t)m_size;
	if (beginy < 0)
		beginy = 0;

	int64_t endy = (int64_t)(object->y - m_yDif + rand) / (int64_t)m_size + 1;
	if (endy >(int64_t)m_yIndex)
		endy = (int64_t)m_yIndex;
	else if (endy < 0)
		endy = 0;

	int64_t beginz = (int64_t)(object->z - m_zDif - rand) / (int64_t)m_highSize;
	if (beginz < 0)
		beginz = 0;

	int64_t endz = (int64_t)(object->z - m_zDif + rand) / (int64_t)m_highSize + 1;
	if (endz >(int64_t)m_zIndex)
		endz = (int64_t)m_zIndex;
	else if (endz < 0)
		endz = 0;

	for (int64_t z = beginz; z < endz; ++z)
	{
		for (int64_t y = beginy; y < endy; ++y)
		{
			for (int64_t x = beginx; x < endx; ++x)
			{
				uint64_t at = x + y * m_xIndex + z * m_yIndex * m_xIndex;
				for (typename std::map<uint64_t, T *>::iterator itr = m_vecGrids[at].m_units.begin(); itr != m_vecGrids[at].m_units.end(); ++itr)
				{
					if (!exec->exec(itr->second))
						return;
				}
			}
		}
	}

	return;
}


template <typename T>
void GridVec3Strategy<T>::DoExec(double x, double y, double z, double rand, CEntryCallback<T> *exec)
{
	int64_t beginx = (int64_t)(x - m_xDif - rand) / (int64_t)m_size;
	if (beginx < 0)
		beginx = 0;

	int64_t endx = (int64_t)(x - m_xDif + rand) / (int64_t)m_size + 1;
	if (endx >(int64_t)m_xIndex)
		endx = (int64_t)m_xIndex;
	else if (endx < 0)
		endx = 0;

	int64_t beginy = (int64_t)(y - m_yDif - rand) / (int64_t)m_size;
	if (beginy < 0)
		beginy = 0;

	int64_t endy = (int64_t)(y - m_yDif + rand) / (int64_t)m_size + 1;
	if (endy >(int64_t)m_yIndex)
		endy = (int64_t)m_yIndex;
	else if (endy < 0)
		endy = 0;

	int64_t beginz = (int64_t)(z - m_zDif - rand) / (int64_t)m_highSize;
	if (beginz < 0)
		beginz = 0;

	int64_t endz = (int64_t)(z - m_zDif + rand) / (int64_t)m_highSize + 1;
	if (endz >(int64_t)m_zIndex)
		endz = (int64_t)m_zIndex;
	else if (endz < 0)
		endz = 0;

	for (int64_t z = beginz; z < endz; ++z)
	{
		for (int64_t y = beginy; y < endy; ++y)
		{
			for (int64_t x = beginx; x < endx; ++x)
			{
				uint64_t at = x + y * m_xIndex + z * m_yIndex * m_xIndex;
				for (typename std::map<uint64_t, T *>::iterator itr = m_vecGrids[at].m_units.begin(); itr != m_vecGrids[at].m_units.end(); ++itr)
				{
					if (!exec->exec(itr->second))
						return;
				}
			}
		}
	}

	return;
}

//GridManager
template < typename T, typename S = GridVec2Strategy<T> >
class GridManager
{
public:
	GridManager()
	{
		
	}

	bool Init(void *);
	void Clear();
	void Update();

public:
	Grid<T> *GetGrid(T *);
	Grid<T> *GetGrid(double x, double y, double z);
	bool GetNineGrid(T *object, Grid<T> **);
	bool GetNineGrid(double x, double y, double z, Grid<T> **);
	S &GetStrategy();
	void UpdateScene(uint64_t id, void *);

private:

	S m_gridStrategy;
};

template <typename T, typename S>
bool GridManager<T, S>::Init(void *ptr)
{
	return m_gridStrategy.Init(ptr);
}

template <typename T, typename S>
void GridManager<T, S>::Clear()
{


	return;
}

template <typename T, typename S>
void GridManager<T, S>::Update()
{
	

	return m_gridStrategy.Update();
}

template <typename T, typename S>
Grid<T> * GridManager<T, S>::GetGrid(T *object)
{
	return m_gridStrategy.GetGrid(object);
}

template <typename T, typename S>
Grid<T> *GridManager<T, S>::GetGrid(double x, double y, double z)
{
	return m_gridStrategy.GetGrid(x, y, z);
}

template <typename T, typename S>
bool GridManager<T, S>::GetNineGrid(T *object, Grid<T> **grids)
{
	return m_gridStrategy.GetNineGrid(object, grids);
}

template <typename T, typename S>
bool GridManager<T, S>::GetNineGrid(double x, double y, double z, Grid<T> **grids)
{
	return m_gridStrategy.GetNineGrid(x, y, z, grids);
}

template <typename T, typename S>
S &GridManager<T, S>::GetStrategy()
{
	return m_gridStrategy;
}

template <typename T, typename S>
void GridManager<T, S>::UpdateScene(uint64_t id, void *info)
{
	return m_gridStrategy.UpdateScene(id, info);
}

#endif
