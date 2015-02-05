#include "MyDistribution.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include <cmath>
#include <gsl/gsl_cdf.h>

using namespace DNest3;

MyDistribution::MyDistribution(double x_min, double x_max,
				double y_min, double y_max)
:x_min(x_min)
,x_max(x_max)
,y_min(y_min)
,y_max(y_max)
,x_range(x_max - x_min)
,y_range(y_max - y_min)
{

}

void MyDistribution::fromPrior()
{
	mu = exp(tan(M_PI*(0.97*randomU() - 0.485)));
}

double MyDistribution::perturb_parameters()
{
	double logH = 0.;

	mu = log(mu);
	mu = (atan(mu)/M_PI + 0.485)/0.97;
	mu += randh();
	wrap(mu, 0., 1.);
	mu = tan(M_PI*(0.97*mu - 0.485));
	mu = exp(mu);

	return logH;
}

// vec[0] = x
// vec[1] = y
// vec[2] = flux

double MyDistribution::log_pdf(const std::vector<double>& vec) const
{
	double logp = 0.;

	if(vec[0] < x_min || vec[0] > x_max ||
		vec[1] < y_min || vec[1] > y_max ||
		vec[2] < 0)
		return -1E300;

	logp += -log(mu) - vec[2]/mu;

	return logp;
}

void MyDistribution::from_uniform(std::vector<double>& vec) const
{
	vec[0] = x_min + x_range*vec[0];
	vec[1] = y_min + y_range*vec[1];
	vec[2] = -mu*log(1. - vec[2]);
}

void MyDistribution::to_uniform(std::vector<double>& vec) const
{
	vec[0] = (vec[0] - x_min)/x_range;
	vec[1] = (vec[1] - y_min)/y_range;
	vec[2] = 1. - exp(-vec[2]/mu);
}

void MyDistribution::print(std::ostream& out) const
{
	out<<mu<<' ';
}

