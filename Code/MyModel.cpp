#include "MyModel.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include "Data.h"
#include <cmath>

using namespace std;
using namespace DNest3;

MyModel::MyModel()
:objects(3, 100, false, MyDistribution(-10., 10., -10., 10.))
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

	const vector< vector<double> >& components = objects.get_components();

	double logL = 0.;

	double mock, real, imag;
	for(size_t i=0; i<u.size(); i++)
	{
		// Sum over components
		real = 0.;
		imag = 0.;
		for(size_t j=0; j<components.size(); j++)
		{
			real +=  components[j][2]*cos(2.*M_PI*(u[i]*components[j][0] + v[i]*components[j][1]));
			imag += -components[j][2]*sin(2.*M_PI*(u[i]*components[j][0] + v[i]*components[j][1]));
		}
		real /= 2.*M_PI;
		imag /= 2.*M_PI;
		mock = real*real + imag*imag;
		logL += //-0.5*log(2.*M_PI) - log(sigma[i])
			-0.5*pow((intensity[i] - mock)/sigma[i], 2);
	}

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

