#include "Controller.h"
#include <cmath>
#include "Exceptions.h"
#include <random>

namespace simulator {

	void Controller::SetSample(Sample &sample) {
			this->_sample = sample;
	}

	void Controller::ControlRotation(Vector3d rotSpeed) {
			if (this->_obj == NULL)
				throw UnregisteredObjectException();

			MatrixXd rotSpeedMatrix = rotSpeed;
			MatrixXd predictionMatrix = this->_neuralNetwork.Predict(rotSpeedMatrix);
			int numberOfWheels = this->_obj->GetNumOfWheels();
			vector<double> currentEnergy = _obj->GetWheelsEnergies();
			for (int i = 0; i < numberOfWheels; i++) {
				_obj->EnergyToReactionWheel(i, predictionMatrix(i, 0) - currentEnergy[i] * (this->_obj->GetWheelSpeed(i) > 0 ? -1: 1));
			}	
	}

		void Controller::Train(string path) {
			Generate(RANGESTART, RANGEEND, NUMBEROFSAMPLES);
			this->_neuralNetwork.SetHiddenLayers(NUMBEROFHIDDENLAYERS, HIDDENLAYERSLENGTH, this->_obj->GetNumOfWheels());
			this->_neuralNetwork.SetLearningRate(LEARNINGRATE);
			this->_neuralNetwork.Train(this->_sample, BATCHSIZE, EPOCH);
			this->_neuralNetwork.Save(path);
	}

	void Controller::LoadNetwork(string fileName) {
		this->_neuralNetwork.SetHiddenLayers(NUMBEROFHIDDENLAYERS, HIDDENLAYERSLENGTH, this->_obj->GetNumOfWheels());
		this->_neuralNetwork.SetLearningRate(LEARNINGRATE);
		this->_neuralNetwork.LoadParameters(fileName);
	}

	void Controller::Generate(double rangeStart, double rangeEnd, int numberOfSamples) {
			if (this->_obj == NULL)
				throw UnregisteredObjectException();

			vector<double> firstNeuronInput;
			int wheelSize = _obj->GetNumOfWheels();
			int numberOfRanges = 5 * log10(numberOfSamples);
			double step = (double)(rangeEnd - rangeStart) / numberOfRanges;
			for (int i = 0, currentSize = 0; i < numberOfRanges; i++) {
				int numberOfPointsInThisRange = (i == numberOfRanges - 1) ? numberOfSamples / numberOfRanges + numberOfSamples % numberOfRanges : numberOfSamples / numberOfRanges;
				for (int j = 0; j < numberOfPointsInThisRange; j++, currentSize++) {
					firstNeuronInput.push_back(rangeStart + (rand() / (RAND_MAX + 1.0) *(rangeStart + step - rangeStart)));
				}
				rangeStart += step;
			}
			vector<vector<double>> vectorMatrix;
			for (int i = 0; i < wheelSize; i++) {
				vector<double> NeuronInput(firstNeuronInput);
				vectorMatrix.push_back(NeuronInput);
			}

			for (int size = firstNeuronInput.size(); 0 < size; size--) {
				Satellite sattelite = *(_obj);

				VectorXd inputVector(wheelSize);
				for (int i = 0; i < wheelSize; i++) {
					int randIndex = rand() % size;
					sattelite.EnergyToReactionWheel(i, vectorMatrix.at(i).at(randIndex));
					inputVector(i) = vectorMatrix.at(i).at(randIndex);
					vectorMatrix.at(i).erase(vectorMatrix.at(i).begin() + randIndex);
				}
				sattelite.Rotate(1.0);

				this->_sample.AddEnergy(inputVector); //power

				Vector3d rotationVector = sattelite.GetRotationSpeeds();

				VectorXd excpectedOutput = this->_sample.ConvertVector3dToXd(rotationVector);

				this->_sample.AddRotSpeed(excpectedOutput);

			}

	}
		
}
