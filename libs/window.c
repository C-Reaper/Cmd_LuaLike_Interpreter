#include "/home/codeleaded/System/Static/Library/AlxCallStack.h"
#include "/home/codeleaded/System/Static/Library/AlxExternFunctions.h"
#include "/home/codeleaded/System/Static/Library/AlxEnviroment.h"
#include "/home/codeleaded/System/Static/Library/LuaLikeDefines.h"
//#include "/home/codeleaded/Hecke/C/Cmd_Scripter/src/LuaLike.h"

#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/Pointer.h"


typedef SharedPointer WindowPtr;

void Window_Destroyer(Variable* v){
    printf("Window: Destroyer -> %s!\n",v->name);
    
    SharedPointer* ptr = (SharedPointer*)v->data;
    char ret = SharedPointer_Free(ptr);
    //if(ret) printf("FULL KILL\n");
    //else    printf("SMALL KILL\n");
}
void Window_Cpyer(Variable* src,Variable* dst){
    printf("Window: Cpyer!\n");
    
    SharedPointer* ptr1 = (SharedPointer*)src->data;
    SharedPointer* ptr2 = (SharedPointer*)dst->data;
    *ptr2 = SharedPointer_Share(ptr1);
}

CStr Window_BuildAcs(Scope* s,WindowPtr* wptr,CStr type,void* data,CStr name,CStr field){
    if(CStr_Cmp(name,field)){
        CStr name = Enviroment_Variablename_Next((Enviroment*)s,LUALIKE_STACK,sizeof(LUALIKE_STACK) - 1);
        Scope_BuildRefDataVariableRange(s,name,type,s->range,data);
        return name;
    }
    return NULL;
}

#define RETURNIF(s,wptr,ret,type,data,name,field)\
ret = Window_BuildAcs(s,wptr,type,data,name,field);\
if(ret) return Token_Move(TOKEN_STRING,ret);

Token Window_Window_Handler_Ass(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("ASS: %s = %s\n",a->str,b->str);

    Variable* b_var;
    if(b->tt==TOKEN_STRING){
        b_var = Scope_FindVariable(s,b->str);
        if(!b_var){
            printf("[Window_Ass]: 1. Arg: Variable %s doesn't exist!\n",a->str);
            return Token_Null();
        }
    }else{
        printf("[Window_Ass]: 1. Arg: %s is not a Window type!\n",a->str);
        return Token_Null();
    }
    
    if(a->tt==TOKEN_STRING){
        Variable* a_var = Scope_FindVariable(s,a->str);
        if(!a_var){
            Scope_BuildVariableRange(s,a->str,"window",s->range-1);
            a_var = Scope_FindVariable(s,a->str);
            if(a_var->data) free(a_var->data);
            a_var->data = NULL;
        }

        Variable_Set(a_var,b_var);
    }else{
        printf("[Window_Ass]: 1. Arg: %s is not a variable type!\n",a->str);
        return Token_Null();
    }

    return Token_Null();
}
Token Window_Any_Handler_Acs(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("[Window]: Acs -> %s.%s\n",a->str,b->str);
    
    CStr name = NULL;
    if(a->tt==TOKEN_STRING){
        Variable* a_var = Scope_FindVariable(s,a->str);
        if(a_var){
            if(!Variable_Data(a_var)){
                printf("[Obj_Acs]: 1. Arg: %s is not a init obj type!\n",a->str);
                return Token_Null();
            }else{
                WindowPtr* wptr = (WindowPtr*)Variable_Data(a_var);
                AlxWindow* alxw = (AlxWindow*)wptr->Memory;

                CStr name = NULL;
                RETURNIF(s,wptr,name,"str",&alxw->Name,b->str,"name")
                RETURNIF(s,wptr,name,"small",&alxw->Width,b->str,"width")
                RETURNIF(s,wptr,name,"small",&alxw->Height,b->str,"height")
                RETURNIF(s,wptr,name,"small",&alxw->Running,b->str,"running")
            }
        }else{
            printf("[Obj_Ass]: 1. Arg: %s is not a variable!\n",a->str);
            return Token_Null();
        }
    }else{
        printf("[Obj_Ass]: 1. Arg: %s is not a variable type!\n",a->str);
        return Token_Null();
    }

    return Token_Null();
}
Token Window_Handler_Cast(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);

    //printf("CAST: %s\n",a->str);

    Variable* a_var;
    if(a->tt==TOKEN_STRING){
        a_var = Scope_FindVariable(s,a->str);
        if(!a_var){
            printf("[Window_Ass]: 1. Arg: Variable %s doesn't exist!\n",a->str);
            return Token_Null();
        }
    }else{
        printf("[Window_Ass]: 1. Arg: %s is not a Window type!\n",a->str);
        return Token_Null();
    }

    AlxWindow* window = (AlxWindow*)Variable_Data(a_var);

    String builder = String_Make("{ ");
    
    String_Append(&builder,window->Name);
    String_AppendNumber(&builder,window->Width);
    String_AppendNumber(&builder,window->Height);

    String_Append(&builder," }");
    char* resstr = String_CStr(&builder);
    String_Free(&builder);
    return Token_Move(TOKEN_CONSTSTRING_DOUBLE,resstr);
}
Token Window_Handler_Destroy(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);

    printf("DESTROY: %s\n",a->str);

    Variable* a_var = Scope_FindVariable(s,a->str);
    if(a_var){
        a_var->destroy(a_var);
    }
    
    return Token_Null();
}

Variable Window_Make(Scope* sc,CStr name,Variable* args){
    Variable* v_name = &args[0];
    Variable* v_width = &args[1];
    Variable* v_height = &args[2];
    
    CStr tname = *(CStr*)v_name->data;
    Number width = *(Number*)v_width->data;
    Number height = *(Number*)v_height->data;
    
    AlxWindow* pw = (AlxWindow*)malloc(sizeof(AlxWindow));
    *pw = AlxWindow_New(tname,width,height,1,1,NULL,NULL,NULL);
    WindowPtr ptr = SharedPointer_Make(pw,(void*)AlxWindow_OnlyExit);

    Variable ret = Variable_Make(
        "Windowtype","window",
        &ptr,
        sizeof(WindowPtr),
        sc->range-1,
        Scope_DestroyerOfType(sc,"window"),
        Scope_CpyerOfType(sc,"window")
    );
    return ret;
}
Variable Window_Init(Scope* sc,CStr name,Variable* args){
    Variable* a_var = &args[0];
    printf("CALL INIT\n");
    
    if(!Variable_Data(a_var)){
        printf("[Window]: Update -> %s is not init!\n",a_var->name);
    }else{
        WindowPtr* wptr = (WindowPtr*)Variable_Data(a_var);
        AlxWindow* alxw = (AlxWindow*)wptr->Memory;
        AlxWindow_GameInit(alxw);
    }

    return Variable_Null();
}
Variable Window_Update(Scope* sc,CStr name,Variable* args){
    Variable* a_var = &args[0];
    
    if(!Variable_Data(a_var)){
        printf("[Window]: Update -> %s is not init!\n",a_var->name);
    }else{
        WindowPtr* wptr = (WindowPtr*)Variable_Data(a_var);
        AlxWindow* alxw = (AlxWindow*)wptr->Memory;
        AlxWindow_GameUpdate(alxw);
    }

    return Variable_Null();
}
Variable Window_Render(Scope* sc,CStr name,Variable* args){
    Variable* a_var = &args[0];
    
    if(!Variable_Data(a_var)){
        printf("[Window]: Render -> %s is not init!\n",a_var->name);
    }else{
        WindowPtr* wptr = (WindowPtr*)Variable_Data(a_var);
        AlxWindow* alxw = (AlxWindow*)wptr->Memory;
        AlxWindow_Render(alxw);
    }

    return Variable_Null();
}

void Ex_Packer(ExternFunctionMap* Extern_Functions,Vector* funcs,Scope* s){//Vector<CStr>
    TypeMap_PushContained(&s->types,funcs,
        Type_New("window",sizeof(AlxWindow),OperatorInterationMap_Make((OperatorInterater[]){
            OperatorInterater_Make((CStr[]){ NULL },OperatorDefineMap_Make((OperatorDefiner[]){
                OperatorDefiner_New(TOKEN_CAST,Window_Handler_Cast),
                OperatorDefiner_New(TOKEN_INIT,NULL),
                OperatorDefiner_New(TOKEN_DESTROY,NULL),
                OPERATORDEFINER_END
            })),
            OperatorInterater_Make((CStr[]){ "window",NULL },OperatorDefineMap_Make((OperatorDefiner[]){
                OperatorDefiner_New(TOKEN_LUALIKE_ASS,Window_Window_Handler_Ass),
                OPERATORDEFINER_END
            })),
            OperatorInterater_Make((CStr[]){ OPERATORINTERATER_DONTCARE,NULL },OperatorDefineMap_Make((OperatorDefiner[]){
                OperatorDefiner_New(TOKEN_LUALIKE_ACS,Window_Any_Handler_Acs),
                OPERATORDEFINER_END
            })),
            OPERATORINTERATER_END
        }),Window_Destroyer,Window_Cpyer)
    );

    ExternFunctionMap_PushContained(Extern_Functions,funcs,ExternFunction_New("new",NULL,(Member[]){ 
        Member_New("str","name"),
        Member_New("int","width"),
        Member_New("int","height"),
        MEMBER_END
    },(void*)Window_Make));
    ExternFunctionMap_PushContained(Extern_Functions,funcs,ExternFunction_New("init",NULL,(Member[]){ 
        Member_New("window","w"),
        MEMBER_END
    },(void*)Window_Init));
    ExternFunctionMap_PushContained(Extern_Functions,funcs,ExternFunction_New("update",NULL,(Member[]){ 
        Member_New("window","w"),
        MEMBER_END
    },(void*)Window_Update));
    ExternFunctionMap_PushContained(Extern_Functions,funcs,ExternFunction_New("render",NULL,(Member[]){ 
        Member_New("window","w"),
        MEMBER_END
    },(void*)Window_Render));
}
