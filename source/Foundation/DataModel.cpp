#include <Nephilim/Foundation/DataModel.h>

NEPHILIM_NS_BEGIN

/// Construct a invalid model index
ModelIndex::ModelIndex()
: row(-1)
, column(-1)
{

}

/// Get the parent model index, if applicable
ModelIndex ModelIndex::parent()
{
	return ModelIndex();
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/// Get the data in a given cell
Variant DataModel::data(int row, int col)
{
	return Variant::Invalid;
}

/// Get the number of rows
int DataModel::rows()
{
	return 0;
}

NEPHILIM_NS_END