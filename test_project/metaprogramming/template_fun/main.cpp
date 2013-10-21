#include "stdcpp.hpp"

class callback
{
public:
    void do_register();
    virtual bool Invoke() = 0;
private:
};

template<class T, class F>
class callback0 : public callback
{
public:
    //typedef int T::*f() fun;
    callback0(T* t, F f)
    {
       this->t = t;
       this->fn = f;
    }
    void do_register();
    virtual bool Invoke()
    {
        //t->*fn();
        return true;
    }
private:
    T* t;
    F fn;
};

template<class T, class F, class P1>
class callback1 : public callback
{
public:
    callback1(T t, F f, P1 p1)
    {
       /*
        this->t = t;
        this->fn = f;
        this->p1 = p1;
        */
    }

    void do_register();
    virtual bool Invoke()
    {
        //t->fn(p1);
        return true;
    }
private:
    T t;
    F fn;
    P1 p1;
};

struct MSG
{

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
    bool register_msg(uint32_t msg, T t, F f)
    {
        callback* new_back = new callback0<T, F>(&t, f);
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
        //g_mgr->register_msg(2, this, this->fun2);       
        //the same name but diff param ???
    }

    bool fun()
    {
        cout<<"usecase::fun()"<<endl;
    }

    bool fun2(uint32_t param)
    {
        cout<<"usecase::fun(uint32_t) param:"<<param<<endl;
    }

private:
};

template<class T, class F>
class Caller
{
public:
    Caller(T t, F f)
    {
        this->t = t;
        this->f = f;
    }

    void Invoke()
    {
        t->*f();
    }
private:        
    T *t;
    F f;
};

int main()
{
    usecase case1;
    //Caller caller<usecase*, void usecase::*fun()>(&case1, &usecase::fun);
    //caller.Invoke();
	return 0;
}
