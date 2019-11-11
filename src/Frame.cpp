#include "Frame.hpp"
#include "VM.hpp"
#include "Core.hpp"
#include "PyFunction.hpp"

// 这个方法仅限于模块使用.
Frame::Frame(CodeObject *codes)
{
    m_Locals    = new Map<PyObject*,PyObject*>();
    m_Globals   = m_Locals; // 非函数上下文 全局和局部等价
    m_Stack     = new ArrayList<PyObject*>(codes->m_StackSize);
    m_LoopStack = new ArrayList<Block*>();
    m_Consts    = codes->m_Consts;
    m_Names     = codes->m_Names;
    m_Codes     = codes;
    m_Pc        = 0;
    m_Caller    = nullptr;
}

Frame::Frame(PyFunction *func, ArrayList<PyObject*> *args, int opArg)
{
    m_Stack     = new ArrayList<PyObject*>();
    m_LoopStack = new ArrayList<Block*>();
    m_Locals    = new Map<PyObject*,PyObject*>();
    m_Globals   = func->globals();

    // 如果存在默认参数 则先设置默认参数
    m_FastLocals = new ArrayList<PyObject*>();
    if(func->default_args())
    {
        int defaultArgCnt = func->default_args()->size();
        int realArgCnt    = opArg;
        while (defaultArgCnt--) // 默认参数只支持从后往前
        {
            m_FastLocals->set(-- realArgCnt, func->default_args()->get(defaultArgCnt));
        }
    }
    if(args)
    {
        for(auto i = 0; i < args->size(); i++)
        {
            m_FastLocals->set(i, args->get(i));
        }
    }
    
    m_Codes     = func->m_FuncCode;
    m_Consts    = m_Codes->m_Consts;
    m_Names     = m_Codes->m_Names;
    m_Pc        = 0;
    m_Caller    = nullptr;
}

Frame::Frame(){}

Frame::~Frame()
{
    delete m_Stack;
    delete m_LoopStack;
    delete m_Locals;
    // delete m_Globals; need delete ?
    m_Locals = nullptr;
    m_Stack = nullptr;
    m_LoopStack = nullptr;
    m_Consts = nullptr;
    m_Names = nullptr;
    m_Codes = nullptr; // ? code is need to delete ?
    m_Pc = 0;
}

bool Frame::has_more_codes()
{
    return m_Pc < m_Codes->m_ByteCodes->length();
}

uint8_t Frame::get_op_code()
{
    return m_Codes->m_ByteCodes->value()[m_Pc++];
}

uint32_t Frame::get_op_arg()
{
    int lowBit =  m_Codes->m_ByteCodes->value()[m_Pc++] & 0xff;
    int highBit = m_Codes->m_ByteCodes->value()[m_Pc++] & 0xff;
    return highBit << 8 | lowBit; // opArg只占2个字节的.
}
