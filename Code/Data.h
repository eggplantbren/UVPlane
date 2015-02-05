#ifndef _Data_
#define _Data_

#include <vector>

class Data
{
	private:
		std::vector<double> u, v, intensity, sigma;

	public:
		Data();
		void load(const char* filename);

		// Getters
		const std::vector<double>& get_u() const { return u; }
		const std::vector<double>& get_v() const { return v; }
		const std::vector<double>& get_intensity() const { return intensity; }
		const std::vector<double>& get_sigma() const { return sigma; }

	// Singleton
	private:
		static Data instance;
	public:
		static Data& get_instance() { return instance; }
};

#endif

