#ifndef inputMatrixDataColMajor_h
#define inputMatrixDataColMajor_h
#include "inputMatrixData.h"
#include <iostream>
#include <string>
#include <vector>

namespace fp
{

template <typename T, typename Q>
class inputMatrixDataColMajor : public inputMatrixData<T, Q>
{
  public:
	inline T returnFeatureValue(const int &featureNum,
								const int &observationNum)
	{
		return inputXData[numObs * featureNum + observationNum];
	}

	inline void prefetchFeatureValue(const int &featureNum,
									 const int &observationNum)
	{
		__builtin_prefetch(&inputXData[numObs * featureNum + observationNum], 0, 2);
	}
};

} // namespace fp
#endif // inputMatrixDataColMajor_h
