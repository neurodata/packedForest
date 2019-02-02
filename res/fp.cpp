#include <iostream>
#include <Rcpp.h> 
#include "forestPackingRConversion.h"

using namespace Rcpp;


RCPP_MODULE(RForest){
	class_<RForest<double> >("RForest")

		.constructor()

		.method("setParameterString", &RForest<double>::setParameterString)
		.method("setParameterInt", &RForest<double>::setParameterInt)
		.method("setParameterDouble", &RForest<double>::setParameterDouble)
		.method("growForestGivenX", &RForest<double>::growForestGivenX)
		.method("growForestCSV", &RForest<double>::growForestCSV)
		.method("printParameters", &RForest<double>::printParameters)
		.method("printForestType", &RForest<double>::printForestType)
		.method("testAccuracy", &RForest<double>::testAccuracy)
		.method("predict", &RForest<double>::predict)
		;
}

