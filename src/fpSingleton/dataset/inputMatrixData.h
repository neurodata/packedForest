#ifndef inputMatrixData_h
#define inputMatrixData_h
#include <vector>
#include <iostream>
#include "inputData.h"
#include <string>


namespace fp {

	template <typename T, typename Q>
		class inputMatrixData : public inputData<T,Q>
	{
		private:
			const std::vector<std::vector<T> >& inputXData;
			const std::vector<Q>& inputYData;
			int numClasses;
		public:
			inputMatrixData( std::vector<std::vector<T> >& Xmat, std::vector<Q>& Yvec):inputXData(Xmat),inputYData(Yvec),numClasses(-1){
				//inputXData = Xmat;
			//	inputYData = Yvec;
				countAndCheckClasses();
			}

			~inputMatrixData(){
				//TODO destroy X and Y
			}

			inline Q returnClassOfObservation(const int &observationNum){
				return inputYData[observationNum];
			}

			inline T returnFeatureValue(const int &featureNum, const int &observationNum){
				return inputXData[featureNum][observationNum];
			}

			inline void prefetchFeatureValue(const int &featureNum, const int &observationNum){
				__builtin_prefetch(&inputXData[featureNum][observationNum], 0, 2);
			}

			inline int returnNumFeatures(){
				return inputXData.size();
			}

			inline int returnNumObservations(){
				return inputYData.size();
			}

			inline int returnNumClasses(){
				return numClasses;
			}


			inline void countAndCheckClasses(){
				std::vector<short> classRoll;
				for(auto i : inputYData){
					if(i > numClasses){
						numClasses=i+1;
						classRoll.resize(numClasses,0);
					}
					classRoll[i]=1;
				}

				for(auto i : classRoll){
					if(i != 1){
						throw std::runtime_error("Not all classes represented in input." );
					}
				}
			}


			void printDataStats(){
				std::cout << "there are " << returnNumFeatures() << " features.\n";
				std::cout << "there are " << returnNumObservations() << " observations.\n";
			}

			void printXValues(){
				for(int i = 0; i < returnNumFeatures(); i++){
					for(int j = 0; j < returnNumObservations(); j++){
						std::cout << returnFeatureValue(i,j) << " ";
					}
					std::cout << "\n";
				}
			}

			void printYValues(){
				for(int j = 0; j < returnNumObservations(); j++){
					std::cout << returnClassOfObservation(j) << " ";
				}
				std::cout << "\n";
			}
	};

} //namespace fp
#endif //inputMatrixData_h
