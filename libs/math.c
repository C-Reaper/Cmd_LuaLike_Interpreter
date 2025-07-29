#include "/home/codeleaded/System/Static/Library/AlxCallStack.h"
#include "/home/codeleaded/System/Static/Library/AlxExternFunctions.h"
#include "/home/codeleaded/System/Static/Library/LuaLikeDefines.h"

Variable math_min(Scope* sc,CStr name,Variable* args){
    Variable* a = &args[0];
    Variable* b = &args[1];
    
    Number out = I64_Min(*(Number*)a->data,*(Number*)b->data);
    Variable ret = Variable_Make("OUT","int",(Number[]){ out },sizeof(Number),0,NULL,NULL);
    return ret;
}
Variable math_max(Scope* sc,CStr name,Variable* args){
    Variable* a = &args[0];
    Variable* b = &args[1];
    
    Number out = I64_Max(*(Number*)a->data,*(Number*)b->data);
    Variable ret = Variable_Make("OUT","int",(Number[]){ out },sizeof(Number),0,NULL,NULL);
    return ret;
}
Variable math_parseInt(Scope* sc,CStr name,Variable* args){
    Variable* a = &args[0];
    
    Number out = Number_Parse(*(CStr*)a->data);
    Variable ret = Variable_Make("OUT","int",(Number[]){ out },sizeof(Number),0,NULL,NULL);
    return ret;
}
Variable math_parseFloat(Scope* sc,CStr name,Variable* args){
    Variable* a = &args[0];
    
    Double out = Double_Parse(*(CStr*)a->data,1);
    Variable ret = Variable_Make("OUT","float",(Double[]){ out },sizeof(Double),0,NULL,NULL);
    return ret;
}

void Ex_Packer(ExternFunctionMap* Extern_Functions,Vector* funcs,Scope* s){//Vector<CStr>
    ExternFunctionMap_PushContained_C(Extern_Functions,funcs,(ExternFunction[]){
        ExternFunction_New("min",NULL,(Member[]){ 
            Member_New(NULL,"a"),
            Member_New(NULL,"b"),
            MEMBER_END
        },(void*)math_min),
        ExternFunction_New("max",NULL,(Member[]){ 
            Member_New(NULL,"a"),
            Member_New(NULL,"b"),
            MEMBER_END
        },(void*)math_max),
        ExternFunction_New("parseInt",NULL,(Member[]){ 
            Member_New(NULL,"a"),
            MEMBER_END
        },(void*)math_parseInt),
        ExternFunction_New("parseFloat",NULL,(Member[]){ 
            Member_New(NULL,"a"),
            MEMBER_END
        },(void*)math_parseFloat),
        ExternFunction_Null()
    });
}
