#ifndef _MyDistribution_
#define _MyDistribution_

#include <Distributions/Distribution.h>

// Basically 2D MassInf
class MyDistribution:public Distribution
{
	private:
		// Limits
		double x_min, x_max, x_range;
		double y_min, y_max, y_range;

		double mu;

		double perturb_parameters();

	public:
		MyDistribution(double x_min, double x_max,
				double y_min, double y_max);

		void fromPrior();

		double log_pdf(const std::vector<double>& vec) const;
		void from_uniform(std::vector<double>& vec) const;
		void to_uniform(std::vector<double>& vec) const;

		void print(std::ostream& out) const;
		static const int weight_parameter = 1;

};

#endif

