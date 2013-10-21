#include "stdcpp.hpp"

struct MSG
{

};

class callback
{
public:
    void do_register();
    virtual bool Invoke() = 0;
private:
};

template<class T>
class callback0 : public callback
{
public:
    typedef bool (T::*tFunction)();
    callback0(T* t, tFunction f)
    {
       this->t = t;
       fn = f;
    }
    void do_register();
    virtual bool Invoke()
    {
        (t->*fn)();
        return true;
    }
private:
    T* t;
    tFunction fn;
};

template<class T, class P1>
class callback1 : public callback
{
public:
    typedef bool (T::*tFunction)(P1);
    callback1(T* t, tFunction f, P1& p1) : p1(p1)
    {
       this->t = t;
       fn = f;
       //this->p1 = p1;
    }
    void do_register();
    virtual bool Invoke()
    {
        (t->*fn)(p1);
        return true;
    }
private:
    T* t;
    tFunction fn;
    P1& p1;
};


class RegisterMgr
{
private:
    typedef std::map<uint32_t, callback*>  MSG_MAP;
public:
    ~RegisterMgr()
    {
        
    }

    template<class T, class F>
    bool register_msg(uint32_t msg, T* t, F f)
    {
        callback* new_back = new callback0<T>(t, f);
        ms_map[msg] = new_back;
        return true; 
    }

    template<class T, class F, class P1>
    bool register_msg(uint32_t msg, T* t, F f, P1& p1)
    {
        callback* new_back = new callback1<T, P1>(t, f, p1);
        ms_map[msg] = new_back;
        return true; 
    }

    bool on_handle_msg(uint32_t msg, MSG param1, MSG param2)
    {
        MSG_MAP::iterator it = ms_map.find(msg);
        if (it != ms_map.end()) {
           return it->second->Invoke();
        }
    }

private:
    MSG_MAP ms_map;  
};

RegisterMgr g_mgr;

class usecase
{
public:
    bool Init()
    {
        g_mgr.register_msg(1, this, &usecase::fun);       
        g_mgr.register_msg(2, this, &usecase::fun2, m_data);       
        //the same name but diff param ???
    }

    bool fun()
    {
        cout<<"usecase::fun()"<<endl;
    }

    bool fun2(int param)
    {
        cout<<"usecase::fun(uint32_t) param:"<<param<<endl;
    }

    void set_data(int v) { m_data = v; }

private:
    int m_data;
};

int main()
{
    usecase case1;
    case1.Init();
    MSG m1;
    MSG m2;
    g_mgr.on_handle_msg(1, m1, m2);
    case1.set_data(1);
    g_mgr.on_handle_msg(2, m1, m2);
    case1.set_data(2);
    g_mgr.on_handle_msg(2, m1, m2);

	return 0;
}
