
template <typename T>
class basic_atom :  noncopyable
{
private:
	T n;
	typedef mutex mutex_t;
	mutex_t mu;
public:
	basic_atom(T x = T()) : n(x) {}
	T operator++ ()
	{
		mutex_t::scoped_lock lock(mu);
		return ++n;
	}
	
	operator T() { return n; }
};

typedef basic_atom<int> atom_int;
	
