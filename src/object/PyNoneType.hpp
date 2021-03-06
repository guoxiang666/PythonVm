#ifndef PY_NONE_TYPE_HPP
#define PY_NONE_TYPE_HPP

#include "Klass.hpp"
#include "PyObject.hpp"

#include <memory>
#include <mutex>

class NoneTypeKlass : public Klass {
public:
    static NoneTypeKlass* get_instance();
    void InitKlass() override;
    void print(PyObject *x) override;
    PyObject* toBool(PyObject *x) override;
private:
    NoneTypeKlass();
    static std::unique_ptr<NoneTypeKlass> m_Instance;
    static std::mutex m_Mutex;
};

// Single Instance in the python vm.
struct PyNoneType : public PyObject {

    PyNoneType(){
        set_klass(NoneTypeKlass::get_instance());
    }
    
};

#endif