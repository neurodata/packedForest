#ifndef inputMatrixDataRowMajor_h
#define inputMatrixDataRowMajor_h
#include "inputMatrixData.h"
#include <iostream>
#include <string>
#include <vector>

namespace fp
{

template <typename T, typename Q>
class inputMatrixDataRowMajor : public inputMatrixData<T, Q>
{
  public:
    inline T returnFeatureValue(const int &featureNum,
                                const int &observationNum)
    {
        return inputXData[observationNum * numFeatures + featureNum];
    }

    inline void prefetchFeatureValue(const int &featureNum,
                                     const int &observationNum)
    {
        __builtin_prefetch(&inputXData[observationNum * numFeatures + featureNum],
                           0, 2);
    }
};
} // namespace fp
#endif // inputMatrixDataRowMajor_h