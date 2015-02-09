#ifndef NephilimFoundationDataModel_h__
#define NephilimFoundationDataModel_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Variant.h>

#include <stdint.h>

NEPHILIM_NS_BEGIN

/**
	\class ModelIndex
	\brief Refers to a cell of data in the data model
*/
class ModelIndex
{
public:

	/// Row index of this cell
	int row;

	/// Column index of this cell
	int column;


public:

	/// Construct a invalid model index
	ModelIndex();

	/// Get the parent model index, if applicable
	ModelIndex parent();
};

/**
	\class DataModel
	\brief Abstract dataset interface through which widgets fetch data from
*/
class NEPHILIM_API DataModel
{
public:


	/// Get the data in a given cell
	virtual Variant data(int row, int col);

	/// Get the number of rows
	virtual int rows();
};

NEPHILIM_NS_END
#endif // NephilimFoundationDataModel_h__
