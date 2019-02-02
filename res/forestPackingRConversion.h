#ifndef forestConv_h
#define forestConv_h

#include "packedForest/src/packedForest.h"
#include <stdexcept>
#include <Rcpp.h> 
#include <string>
#include <iostream>
#include <vector>
//#include <Rinternals.h>

//using namespace fp;
using namespace Rcpp;

template <typename T>
class RForest{

	protected:

	public:
		RForest(){
			std::cout << "created RForest\n";	
		}

		fp::fpForest<T> forest;


		inline void setParameterString(const std::string& parameterName, const std::string& parameterValue){
			forest.setParameter(parameterName, parameterValue);
		}


		inline void setParameterInt(const std::string& parameterName, int parameterValue){
			forest.setParameter(parameterName, parameterValue);
		}


		inline void setParameterDouble(const std::string& parameterName, double parameterValue){
			forest.setParameter(parameterName, parameterValue);
		}


		inline void growForestCSV(){
			forest.growForest();
		}


		inline void growForestGivenX(const void* mat, const void* yvec){
			double* x = (double*)mat + 5;
			int* y = (int*)yvec+10;

			int numObs = ((int*)yvec)[8];
			int numFeatures = ((int*)mat)[8]/numObs;

			
			for(int i = 0; i < numObs*numFeatures; ++i){
				std::cout << x[i] << " ";
			}

			for(int i = 0; i < numObs; ++i){
				std::cout << y[i] << " ";
			}
			
			forest.growForest(x,y,numObs,numFeatures);
		}


		inline void printParameters(){
			forest.printParameters();
		}


		inline void printForestType(){
			forest.printForestType();
		}


		inline double testAccuracy(){
			return forest.testAccuracy();
		}


		inline Rcpp::NumericVector predict(const NumericMatrix mat){
			int numObservations = mat.nrow();
			int numFeatures = mat.ncol();

			std::vector<double> currObs(numFeatures);
			Rcpp::NumericVector predictions(numObservations);

			for(int i = 0; i < numObservations; i++){
				for(int j = 0; j < numFeatures; j++){
					currObs[j] = mat(i,j);
				}
				predictions[i] = forest.predict(currObs);
			}
			return predictions;
		}
};

#endif //forestConv_h

