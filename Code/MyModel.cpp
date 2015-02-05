#include "MyModel.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include "Data.h"
#include <cmath>

using namespace std;
using namespace DNest3;

MyModel::MyModel()
:objects(3, 100, false, MyDistribution(-1., 1., -1., 1.))
{

}

void MyModel::fromPrior()
{
	objects.fromPrior();
}

double MyModel::perturb()
{
	double logH = 0.;

	logH += objects.perturb();

	return logH;
}

double MyModel::logLikelihood() const
{
	const vector<double>& u = Data::get_instance().get_u();
	const vector<double>& v = Data::get_instance().get_v();
	const vector<double>& intensity = Data::get_instance().get_intensity();
	const vector<double>& sigma = Data::get_instance().get_sigma();

	double logL = 0.;

	return logL;
}

void MyModel::print(std::ostream& out) const
{
	objects.print(out); out<<' ';
}

string MyModel::description() const
{
	return string("objects");
}

