#ifndef UTILS_HPP_
#define UTILS_HPP_
#include <cstring>
#include <sstream>
namespace Utils{
	template<class T>
	static std::string toString(const T source) {
		std::stringstream ss;
		ss << source;
		return ss.str();
	}
}
#endif /* UTILS_HPP_ */
