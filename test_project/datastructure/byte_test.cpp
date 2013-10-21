#include "stdcpp.hpp"

bool test_fn(uint32_t n) { return false; }
bool (*byte_relloc_fn)(uint32_t) = &test_fn;

template<class T = uint8_t>
class byte_t
{
public: 
    byte_t(int n = 100, bool read_only = false)
    {
        m_t = NULL; 
        m_t = new T[n]; 
        m_capacity = n;	
        m_read = m_write = 0;
        m_read_only = read_only;
    }
    
    ~byte_t()
    {
        m_read = m_write = 0;
        if (m_t) {
            delete [] m_t;
            m_t = NULL;
        }
    }

    bool relloc_room()
    {
        bool ret = false;
        /*
         if (byte_relloc_fn) {
            ret true; 
        }    
        */

        return ret;
    }

    template<class Type> 
    const byte_t& write(Type t)
    {
        uint32_t data_size = sizeof(Type);
        while (full() || !can_write(data_size)) {
            relloc_room();
        }

        memcpy(m_t+m_write, &t, data_size);
        
        return *this;    
    }

    template<class Type>
    uint32_t read(Type& t)
    {
        uint32_t data_size = sizeof(Type);
        if (empty() 
            || !can_read(data_size)
            ) {
            return 0;
        }

        memcpy(&t, m_t + m_read, data_size);

        return data_size;
    }

    bool full() 
    {
        return m_write == m_capacity - 1  ? true : false;
    }

    bool empty()
    {
        return m_read == m_write ? true : false;
    }

    bool can_write(uint32_t data_size)
    {
        return (m_capacity - 1 - m_write) > data_size ? true : false;
    }

    bool can_read(uint32_t data_size)
    {
        return (m_write - m_read) > data_size ? true : false;
    }

private:
	T* m_t;
	uint32_t m_capacity;
	uint32_t m_read;
	uint32_t m_write;
	bool m_read_only;
};

enum {
	max_capacity = 3,
};

int main()
{
    byte_t<> data;
    /*
    byte_relloc_fn(9);
    byte_relloc_fn = NULL;
    byte_relloc_fn = &test_fn;
    */
	return 0;
}
