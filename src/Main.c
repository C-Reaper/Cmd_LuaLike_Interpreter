#include "/home/codeleaded/System/Static/Library/LuaLike.h"

/*
typedef struct Human {
    CStr name;
    int x;
    int y;
} Human;

Human Human_New(CStr name,int x,int y){
    Human h;
    if(name)    h.name = CStr_Cpy(name);
    else        h.name = NULL;
    h.x = 0;
    h.y = 0;
    return h;
}
Human Human_Cpy(Human* h){
    Human ret;
    ret.name = CStr_Cpy(h->name);
    ret.x = h->x;
    ret.y = h->y;
    return ret;
}
Human Human_Null(){
    Human h;
    h.name = NULL;
    h.x = 0;
    h.y = 0;
    return h;
}
CStr Human_CStr(Human* h){
    String builder = String_Format("{ name = %s,x = %d,y = %d }",h->name,h->x,h->y);
    CStr resstr = String_CStr(&builder);
    String_Free(&builder);
    return resstr;
}
void Human_Free(Human* h){
    if(h->name) free(h->name);
    h->name = NULL;
}

void Human_Destroyer(Variable* v){
    printf("Human: Destroyer!\n");
    Human_Free(Variable_Data(v));
}
void Human_Cpyer(Variable* src,Variable* dst){
    printf("Human: Cpyer!\n");
    Human* src_str = (Human*)Variable_Data(src);
    Human* dst_str = (Human*)Variable_Data(dst);
    *dst_str = Human_Cpy(src_str);
}

Token Human_Human_Handler_Ass(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("ASS: %s = %s\n",a->str,b->str);

    Variable* b_var;
    if(b->tt==TOKEN_STRING){
        b_var = Scope_FindVariable(s,b->str);
        if(!b_var){
            printf("[Human_Ass]: 1. Arg: Variable %s doesn't exist!\n",a->str);
            return Token_Null();
        }
    }else{
        printf("[Human_Ass]: 1. Arg: %s is not a Human type!\n",a->str);
        return Token_Null();
    }
    
    if(a->tt==TOKEN_STRING){
        Variable* a_var = Scope_FindVariable(s,a->str);
        if(!a_var){
            Scope_BuildVariableRange(s,a->str,"human",s->range-1);
            a_var = Scope_FindVariable(s,a->str);
            if(a_var->data) free(a_var->data);
            a_var->data = NULL;
        }

        Variable_Set(a_var,b_var);
    }else{
        printf("[Human_Ass]: 1. Arg: %s is not a variable type!\n",a->str);
        return Token_Null();
    }

    return Token_Null();
}
Token Human_Handler_Cast(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);

    //printf("CAST: %s\n",a->str);

    Variable* a_var;
    if(a->tt==TOKEN_STRING){
        a_var = Scope_FindVariable(s,a->str);
        if(!a_var){
            printf("[Human_Ass]: 1. Arg: Variable %s doesn't exist!\n",a->str);
            return Token_Null();
        }
    }else{
        printf("[Human_Ass]: 1. Arg: %s is not a Human type!\n",a->str);
        return Token_Null();
    }

    Human* h = (Human*)Variable_Data(a_var);
    CStr resstr = Human_CStr(h);
    return Token_Move(TOKEN_CONSTSTRING_DOUBLE,resstr);
}

Variable Human_human(Enviroment* ev,CStr name,Variable* args){
    Variable ret = Variable_Make(
        "HUMAN","human",
        (Human[]){ Human_New("DUMMY",0,0) },
        sizeof(Human),ev->sc.range-1,
        Scope_DestroyerOfType(&ev->sc,"human"),
        Scope_CpyerOfType(&ev->sc,"human")
    );
    return ret;
}
*/

int main(int argc,char** argv){
    if(argc<=1){
        printf("Missing File .ll!\n");
        return 1;
    }

    LuaLike ll = LuaLike_New(argv[1],"./bin");

    //LuaLike_CreateType_Std(&ll,"human",sizeof(Human),Human_Handler_Cast,Human_Human_Handler_Ass,Human_Destroyer,Human_Cpyer);
    //LuaLike_CreateFunc_Std(&ll,"C","humannew",NULL,(Member[]){ MEMBER_END },(void*)Human_human);
    
    //Variable a = Variable_Make("a","int",(Number[]){ 7 },sizeof(Number),0,NULL,NULL);
    //Variable b = Variable_Make("b","int",(Number[]){ 8 },sizeof(Number),0,NULL,NULL);
    
    //CStr name = "Hello World\n";
    //char sname[13];
    //memcpy(sname,name,13);
    //Variable c = Variable_RefData("c","str",(CStr[]){ sname },sizeof(CStr),0,NULL,NULL);
    //Variable d = Variable_Make("d","human",(Human[]){ Human_New("John",1,2) },sizeof(Human),0,Human_Destroyer,Human_Cpyer);
    
    //LuaLike_Print(&ll);

    Variable ret = LuaLike_Function(&ll,"main",(Variable[]){ 
        VARIABLE_END
    });
    LuaLike_PrintVariable(&ll,&ret);
    Variable_Free(&ret);

    //Variable_Free(&d);
    //Variable_Free(&c);
    
    //Variable_Free(&b);
    //Variable_Free(&a);
    
    LuaLike_Free(&ll);
    
    return 0;
}