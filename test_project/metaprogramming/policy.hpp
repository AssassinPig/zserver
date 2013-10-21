template <typename T>
class AccumulationTraits;

template <>
class AccumulationTraits<char>
{
public:
	typedef int AccT;
	static AccT zero() {
		return 0;
	}
};

template <>
class AccumulationTraits<int>
{
public:
	typedef long AccT;
	static AccT zero() {
		return 0;
	}
};

class SumPolicy
{
public:
	template <typename T1, typename T2> 
	static void accumulate(T1& total, T2 const& value) {
		total += value;
	}
};

class MultiPolicy
{
public:
	template <typename T1, typename T2>
	static void accumulate(T1& total, T2 const& value) {
		total *= value;
	}
};

template <typename T, 
		typename Policy = SumPolicy,
		typename Traits = AccumulationTraits<T> >
class Accum 
{
public: 
	typedef typename Traits::AccT AccT;
	static AccT accum(T const *beg, T const *end) {
		AccT total = Traits::zero();
		while(beg != end) {
			Policy::accumulate(total, *beg);
			++beg;
		}
		
		return total;
	}
}; 
