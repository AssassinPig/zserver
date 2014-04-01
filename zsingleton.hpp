#ifndef _ZSINGLETON_H__ 
#define _ZSINGLETON_H__

template<class T>
class ZSingleton
{
    public:
        static T* GetInstance() 
        {
            assert(ms_instance);
            return ms_instance;
        }

    private:
        ZSingleton();
        ZSingleton(const ZSingleton&);        
        const ZSingleton& operator = (const ZSingleton&);

    protected:
        static T* ms_instance;
};

#endif //_ZSINGLETON_H__
