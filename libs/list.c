#include "/home/codeleaded/System/Static/Library/AlxCallStack.h"
#include "/home/codeleaded/System/Static/Library/AlxExternFunctions.h"
#include "/home/codeleaded/System/Static/Library/LuaLikeDefines.h"

Number Implementation_IntOf(Scope* s,Token* a){
    Number n = NUMBER_PARSE_ERROR;
    if(a->tt==TOKEN_STRING){
        Variable* a_var = Scope_FindVariable(s,a->str);
        if(a_var && a_var->data){
            n = *(Number*)Variable_Data(a_var);
        }else{
            printf("[Int_Number]: 1. Arg: Variable %s doesn't exist!\n",a->str);
        }
    }else if(a->tt==TOKEN_NUMBER){
        n = a->v_i64;
    }
    return n;
}
Boolean Implementation_BooleanOf(Scope* s,Token* a){
    Boolean n = 0;
    
    if(a->tt==TOKEN_STRING){
        Variable* a_var = Scope_FindVariable(s,a->str);
        if(a_var){
            n = *(Boolean*)Variable_Data(a_var);
        }else{
            printf("[Int_Boolean]: 1. Arg: Variable %s doesn't exist!\n",a->str);
        }
    }else if(a->tt==TOKEN_BOOL){
        n = a->v_b1;
    }
    return n;
}
Double Implementation_FloatOf(Scope* s,Token* a){
    Double n = DOUBLE_PARSE_ERROR;
    
    if(a->tt==TOKEN_STRING){
        Variable* a_var = Scope_FindVariable(s,a->str);
        if(a_var){
            n = *(Double*)Variable_Data(a_var);
        }else{
            printf("[Int_Double]: 1. Arg: Variable %s doesn't exist!\n",a->str);
        }
    }else if(a->tt==TOKEN_FLOAT){
        n = a->v_f64;
    }
    return n;
}
CStr Implementation_StrOf(Scope* s,Token* a){
    CStr n = NULL;
    
    if(a->tt==TOKEN_STRING){
        Variable* a_var = Scope_FindVariable(s,a->str);
        if(a_var){
            n = *(CStr*)Variable_Data(a_var);
        }else{
            printf("[Int_CStr]: 1. Arg: Variable %s doesn't exist!\n",a->str);
        }
    }else if(a->tt==TOKEN_CONSTSTRING_DOUBLE){
        n = a->str;
    }
    return n;
}


typedef VariableMap Listtype;// Vector<Variable>

void Listtype_Destroyer(Variable* v){
    //printf("Listtype: Destroyer!\n");
    VariableMap_Free(Variable_Data(v));
}
void Listtype_Cpyer(Variable* src,Variable* dst){
    printf("Listtype: Cpyer!\n");
    Listtype* src_str = (Listtype*)Variable_Data(src);
    Listtype* dst_str = (Listtype*)Variable_Data(dst);
    *dst_str = VariableMap_Cpy(src_str);
}

Token Listtype_Listtype_Handler_Ass(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("ASS: %s = %s\n",a->str,b->str);

    Variable* b_var;
    if(b->tt==TOKEN_STRING){
        b_var = Scope_FindVariable(s,b->str);
        if(!b_var){
            printf("[Listtype_Ass]: 1. Arg: Variable %s doesn't exist!\n",a->str);
            return Token_Null();
        }
    }else{
        printf("[Listtype_Ass]: 1. Arg: %s is not a Listtype type!\n",a->str);
        return Token_Null();
    }
    
    if(a->tt==TOKEN_STRING){
        Variable* a_var = Scope_FindVariable(s,a->str);
        if(!a_var){
            Scope_BuildVariableRange(s,a->str,"list",s->range-1);
            a_var = Scope_FindVariable(s,a->str);
            if(a_var->data) free(a_var->data);
            a_var->data = NULL;
        }

        Variable_Set(a_var,b_var);
    }else{
        printf("[Listtype_Ass]: 1. Arg: %s is not a variable type!\n",a->str);
        return Token_Null();
    }

    return Token_Null();
}

Token Listtype_Int_Handler_Asd(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("ASD: %s += %s\n",a->str,b->str);

    Number cn = Implementation_IntOf(s,b);
    
    if(a->tt==TOKEN_STRING){
        Variable* a_var = Scope_FindVariable(s,a->str);
        if(a_var){
            if(!Variable_Data(a_var) || !CStr_Cmp(a_var->typename,"list")){
                printf("[Listtype_Acs]: 1. Arg: %s is not a list type!\n",a->str);
                return Token_Null();
            }else if(cn!=NUMBER_PARSE_ERROR){
                VariableMap* members = Variable_Data(a_var);
                VariableMap_PPush(members,(Variable[]){ Variable_Make("NL","int",(Number[]){ cn },sizeof(Number),-1,NULL,NULL) });
            }else{
                printf("[Listtype_Asd]: 2. Arg: %s is not a int!\n",b->str);
                return Token_Null();
            }
        }else{
            printf("[Listtype_Asd]: 1. Arg: %s is not a variable!\n",a->str);
            return Token_Null();
        }
    }else{
        printf("[Listtype_Asd]: 1. Arg: %s is not a variable type!\n",a->str);
        return Token_Null();
    }

    return Token_Null();
}
Token Listtype_Str_Handler_Asd(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("ASD: %s += %s\n",a->str,b->str);

    CStr cs = Implementation_StrOf(s,b);
    
    if(a->tt==TOKEN_STRING){
        Variable* a_var = Scope_FindVariable(s,a->str);
        if(a_var){
            if(!Variable_Data(a_var) || !CStr_Cmp(a_var->typename,"list")){
                printf("[Listtype_Acs]: 1. Arg: %s is not a list type!\n",a->str);
                return Token_Null();
            }else if(cs!=NULL){
                VariableMap* members = Variable_Data(a_var);
                VariableMap_PPush(members,(Variable[]){ 
                    Variable_Make("NL","str",(CStr[]){ CStr_Cpy(cs) },sizeof(CStr),-1,Scope_DestroyerOfType(s,"str"),Scope_CpyerOfType(s,"str"))
                });
            }else{
                printf("[Listtype_Asd]: 2. Arg: %s is not a str!\n",b->str);
                return Token_Null();
            }
        }else{
            printf("[Listtype_Asd]: 1. Arg: %s is not a variable!\n",a->str);
            return Token_Null();
        }
    }else{
        printf("[Listtype_Asd]: 1. Arg: %s is not a variable type!\n",a->str);
        return Token_Null();
    }

    return Token_Null();
}
Token Listtype_Boolean_Handler_Asd(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("ASD: %s += %s\n",a->str,b->str);

    Boolean cb = Implementation_BooleanOf(s,b);
    
    if(a->tt==TOKEN_STRING){
        Variable* a_var = Scope_FindVariable(s,a->str);
        if(a_var){
            if(!Variable_Data(a_var) || !CStr_Cmp(a_var->typename,"list")){
                printf("[Listtype_Acs]: 1. Arg: %s is not a list type!\n",a->str);
                return Token_Null();
            }else if(cb){
                VariableMap* members = Variable_Data(a_var);
                VariableMap_PPush(members,(Variable[]){ Variable_Make("NL","Boolean",(Boolean[]){ cb },sizeof(Boolean),-1,NULL,NULL) });
            }else{
                printf("[Listtype_Asd]: 2. Arg: %s is not a Boolean!\n",b->str);
                return Token_Null();
            }
        }else{
            printf("[Listtype_Asd]: 1. Arg: %s is not a variable!\n",a->str);
            return Token_Null();
        }
    }else{
        printf("[Listtype_Asd]: 1. Arg: %s is not a variable type!\n",a->str);
        return Token_Null();
    }

    return Token_Null();
}
Token Listtype_Float_Handler_Asd(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("ASD: %s += %s\n",a->str,b->str);

    Double cf = Implementation_FloatOf(s,b);
    
    if(a->tt==TOKEN_STRING){
        Variable* a_var = Scope_FindVariable(s,a->str);
        if(a_var){
            if(!Variable_Data(a_var) || !CStr_Cmp(a_var->typename,"list")){
                printf("[Listtype_Acs]: 1. Arg: %s is not a list type!\n",a->str);
                return Token_Null();
            }else if(cf!=DOUBLE_PARSE_ERROR){
                VariableMap* members = Variable_Data(a_var);
                VariableMap_PPush(members,(Variable[]){ Variable_Make("NL","float",(Double[]){ cf },sizeof(Double),-1,NULL,NULL) });
            }else{
                printf("[Listtype_Asd]: 2. Arg: %s is not a float!\n",b->str);
                return Token_Null();
            }
        }else{
            printf("[Listtype_Asd]: 1. Arg: %s is not a variable!\n",a->str);
            return Token_Null();
        }
    }else{
        printf("[Listtype_Asd]: 1. Arg: %s is not a variable type!\n",a->str);
        return Token_Null();
    }

    return Token_Null();
}
Token Listtype_Obj_Handler_Asd(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("ASD: %s += %s\n",a->str,b->str);
    
    if(a->tt==TOKEN_STRING){
        Variable* a_var = Scope_FindVariable(s,a->str);
        if(a_var){
            if(!Variable_Data(a_var) || !CStr_Cmp(a_var->typename,"list")){
                printf("[Listtype_Acs]: 1. Arg: %s is not a list type!\n",a->str);
                return Token_Null();
            }else if(b->tt==TOKEN_STRING){
                VariableMap* members = Variable_Data(a_var);
                Variable* b_var = Scope_FindVariable(s,b->str);
                if(b_var){
                    if(!Variable_Data(b_var)){
                        printf("[Listtype_Asd]: 2. Arg: %s is not inited!\n",b->str);
                        return Token_Null();
                    }else if(CStr_Cmp(b_var->typename,"obj")){
                        void (*Cpyer)(Variable*,Variable*) = Scope_CpyerOfType(s,b_var->typename);
                        
                        Variable var = Variable_Make("NL",b_var->typename,NULL,sizeof(CStr),-1,Scope_DestroyerOfType(s,b_var->typename),Scope_CpyerOfType(s,b_var->typename));
                        Cpyer(b_var,&var);

                        VariableMap_PPush(members,&var);
                    }else{
                        printf("[Listtype_Asd]: 2. Arg: %s is from a not defined type!\n",b->str);
                        return Token_Null();
                    }
                }else{
                    printf("[Listtype_Asd]: 2. Arg: %s is not a variable!\n",b->str);
                    return Token_Null();
                }
            }else{
                printf("[Listtype_Asd]: 2. Arg: %s is not a obj!\n",a->str);
                return Token_Null();
            }
        }else{
            printf("[Listtype_Asd]: 1. Arg: %s is not a variable!\n",a->str);
            return Token_Null();
        }
    }else{
        printf("[Listtype_Asd]: 1. Arg: %s is not a variable type!\n",a->str);
        return Token_Null();
    }

    return Token_Null();
}
Token Listtype_Listtype_Handler_Asd(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("ASD: %s += %s\n",a->str,b->str);
    
    if(a->tt==TOKEN_STRING){
        Variable* a_var = Scope_FindVariable(s,a->str);
        if(a_var){
            if(!Variable_Data(a_var) || !CStr_Cmp(a_var->typename,"list")){
                printf("[Listtype_Acs]: 1. Arg: %s is not a list type!\n",a->str);
                return Token_Null();
            }else if(b->tt==TOKEN_STRING){
                VariableMap* members = Variable_Data(a_var);
                Variable* b_var = Scope_FindVariable(s,b->str);
                if(b_var){
                    if(!Variable_Data(b_var)){
                        printf("[Listtype_Asd]: 2. Arg: %s is not inited!\n",b->str);
                        return Token_Null();
                    }else if(CStr_Cmp(b_var->typename,"list")){
                        void (*Cpyer)(Variable*,Variable*) = Scope_CpyerOfType(s,b_var->typename);
                        
                        Variable var = Variable_Make("NL",b_var->typename,NULL,sizeof(CStr),-1,Scope_DestroyerOfType(s,b_var->typename),Scope_CpyerOfType(s,b_var->typename));
                        Cpyer(b_var,&var);

                        VariableMap_PPush(members,&var);
                    }else{
                        printf("[Listtype_Asd]: 2. Arg: %s is from a not defined type!\n",b->str);
                        return Token_Null();
                    }
                }else{
                    printf("[Listtype_Asd]: 2. Arg: %s is not a variable!\n",b->str);
                    return Token_Null();
                }
            }else{
                printf("[Listtype_Asd]: 2. Arg: %s is not a obj!\n",a->str);
                return Token_Null();
            }
        }else{
            printf("[Listtype_Asd]: 1. Arg: %s is not a variable!\n",a->str);
            return Token_Null();
        }
    }else{
        printf("[Listtype_Asd]: 1. Arg: %s is not a variable type!\n",a->str);
        return Token_Null();
    }

    return Token_Null();
}

Token Listtype_Int_Handler_Asu(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("ASU: %s -= %s\n",a->str,b->str);

    Number cn = Implementation_IntOf(s,b);
    CStr cs = Implementation_StrOf(s,b);
    
    if(a->tt==TOKEN_STRING){
        Variable* a_var = Scope_FindVariable(s,a->str);
        if(a_var){
            if(!Variable_Data(a_var) || !CStr_Cmp(a_var->typename,"list")){
                printf("[Listtype_Acs]: 1. Arg: %s is not a list type!\n",a->str);
                return Token_Null();
            }else if(cn!=NUMBER_PARSE_ERROR){
                VariableMap* members = Variable_Data(a_var);
                if(cn>=0 && cn<members->size){
                    Variable* var = (Variable*)PVector_Get(members,cn);
                    Variable_Free(var);
                    PVector_Remove(members,cn);
                }else{
                    printf("[Listtype_Asu]: index %ld out of bounds!\n",cn);
                    return Token_Null();
                }
            }
        }else{
            printf("[Listtype_Asu]: 1. Arg: %s is not a variable!\n",a->str);
            return Token_Null();
        }
    }else{
        printf("[Listtype_Asu]: 1. Arg: %s is not a variable type!\n",a->str);
        return Token_Null();
    }

    return Token_Null();
}
Token Listtype_Str_Handler_Asu(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("ASU: %s -= %s\n",a->str,b->str);

    CStr cs = Implementation_StrOf(s,b);
    
    if(a->tt==TOKEN_STRING){
        Variable* a_var = Scope_FindVariable(s,a->str);
        if(a_var){
            if(!Variable_Data(a_var) || !CStr_Cmp(a_var->typename,"list")){
                printf("[Listtype_Acs]: 1. Arg: %s is not a list type!\n",a->str);
                return Token_Null();
            }else if(cs!=NULL){
                VariableMap* members = Variable_Data(a_var);
                VariableMap_Remove(members,cs);
            }else{
                printf("[Listtype_Asu]: 2. Arg: %s is not a str!\n",b->str);
                return Token_Null();
            }
        }else{
            printf("[Listtype_Asu]: 1. Arg: %s is not a variable!\n",a->str);
            return Token_Null();
        }
    }else{
        printf("[Listtype_Asu]: 1. Arg: %s is not a variable type!\n",a->str);
        return Token_Null();
    }

    return Token_Null();
}

Token Listtype_Str_Handler_Asm(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("ASM: %s *= %s\n",a->str,b->str);

    CStr cs = Implementation_StrOf(s,b);
    
    if(a->tt==TOKEN_STRING){
        Variable* a_var = Scope_FindVariable(s,a->str);
        if(a_var){
            if(!Variable_Data(a_var) || !CStr_Cmp(a_var->typename,"list")){
                printf("[Listtype_Acs]: 1. Arg: %s is not a list type!\n",a->str);
                return Token_Null();
            }else if(cs!=NULL){
                VariableMap* members = Variable_Data(a_var);
                VariableMap_PPush(members,(Variable[]){ 
                    Variable_Make(cs,"str",(CStr[]){ "" },
                    sizeof(CStr),-1,Scope_DestroyerOfType(s,"str"),Scope_CpyerOfType(s,"str"))
                });
            }else{
                printf("[Listtype_Asd]: 2. Arg: %s is not a str!\n",b->str);
                return Token_Null();
            }
        }else{
            printf("[Listtype_Asd]: 1. Arg: %s is not a variable!\n",a->str);
            return Token_Null();
        }
    }else{
        printf("[Listtype_Asd]: 1. Arg: %s is not a variable type!\n",a->str);
        return Token_Null();
    }

    return Token_Null();
}

Token Listtype_Int_Handler_Subs(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("SUBS: %s[%s]\n",a->str,b->str);

    Number n2 = Implementation_IntOf(s,b);
    
    CStr name = NULL;
    if(a->tt==TOKEN_STRING){
        Variable* a_var = Scope_FindVariable(s,a->str);
        if(a_var){
            if(!Variable_Data(a_var) || !CStr_Cmp(a_var->typename,"list")){
                printf("[Listtype_Subs]: 1. Arg: %s is not a list type!\n",a->str);
                return Token_Null();
            }else{
                VariableMap* members = Variable_Data(a_var);
                if(n2>=0 && n2<members->size){
                    Variable* member = (Variable*)PVector_Get(members,n2);

                    String strbuilder = String_Make(".LISTSUBS");
                
                    Variable* temp = Scope_FindVariableLike(s,".LISTSUBS*",'*');

                    if(temp){
                        CStr retnumberstr = temp->name + 9;// CStr_Size(".LISTSUBS") -> 9
                        CStr strdepth = Number_Get(Number_Parse(retnumberstr) + 1);
                        String_Append(&strbuilder,strdepth); 
                        name = String_CStr(&strbuilder);
                        String_Free(&strbuilder);
                        CStr_Free(&strdepth);
                    }else{
                        name = CStr_Cpy(".LISTSUBS0");
                    }

                    Scope_BuildRefVariableRange(s,name,member->typename,s->range+1,member);
                }else{
                    printf("[Listtype_Subs]: in list %s index %ld is out of bounds!\n",a_var->name,n2);
                    return Token_Null();
                }
            }
        }else{
            printf("[Listtype_Subs]: 1. Arg: %s is not a variable!\n",a->str);
            return Token_Null();
        }
    }else{
        printf("[Listtype_Subs]: 1. Arg: %s is not a variable type!\n",a->str);
        return Token_Null();
    }

    return Token_Move(TOKEN_STRING,name);
}
Token Listtype_Str_Handler_Subs(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("SUBS: %s[%s]\n",a->str,b->str);

    CStr n2 = Implementation_StrOf(s,b);
    
    CStr name = NULL;
    if(a->tt==TOKEN_STRING){
        Variable* a_var = Scope_FindVariable(s,a->str);
        if(a_var){
            if(!Variable_Data(a_var) || !CStr_Cmp(a_var->typename,"list")){
                printf("[Listtype_Subs]: 1. Arg: %s is not a list type!\n",a->str);
                return Token_Null();
            }else{
                VariableMap* members = Variable_Data(a_var);
                Variable* member = VariableMap_Find(members,n2);
                if(member){
                    String strbuilder = String_Make(".LISTSUBS");
                
                    Variable* temp = Scope_FindVariableLike(s,".LISTSUBS*",'*');

                    if(temp){
                        CStr retnumberstr = temp->name + 9;// CStr_Size(".LISTSUBS") -> 9
                        CStr strdepth = Number_Get(Number_Parse(retnumberstr) + 1);
                        String_Append(&strbuilder,strdepth); 
                        name = String_CStr(&strbuilder);
                        String_Free(&strbuilder);
                        CStr_Free(&strdepth);
                    }else{
                        name = CStr_Cpy(".LISTSUBS0");
                    }

                    Scope_BuildRefVariableRange(s,name,member->typename,s->range+1,member);
                }else{
                    printf("[Listtype_Subs]: in list %s field \"%s\" doesn't exist!\n",a_var->name,n2);
                    return Token_Null();
                }
            }
        }else{
            printf("[Listtype_Subs]: 1. Arg: %s is not a variable!\n",a->str);
            return Token_Null();
        }
    }else{
        printf("[Listtype_Subs]: 1. Arg: %s is not a variable type!\n",a->str);
        return Token_Null();
    }

    return Token_Move(TOKEN_STRING,name);
}
Token Listtype_Handler_Cast(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);

    //printf("CAST: %s\n",a->str);

    Variable* a_var;
    if(a->tt==TOKEN_STRING){
        a_var = Scope_FindVariable(s,a->str);
        if(!a_var){
            printf("[Listtype_Ass]: 1. Arg: Variable %s doesn't exist!\n",a->str);
            return Token_Null();
        }
    }else{
        printf("[Listtype_Ass]: 1. Arg: %s is not a Listtype type!\n",a->str);
        return Token_Null();
    }

    Listtype* list = (Listtype*)Variable_Data(a_var);

    String builder = String_Make("{ ");
    for(int i = 0;i<list->size;i++){
        Variable* v = (Variable*)PVector_Get(list,i);
        CStr num = Number_Get(i);
        String_Append(&builder,num);
        CStr_Free(&num);
        String_Append(&builder," \"");
        String_Append(&builder,v->name);
        String_Append(&builder,"\":");
        String_Append(&builder,v->typename);
        
        String_Append(&builder," = ");

        CStr content = Scope_VariableContentStr(s,v);
        if(content){
            String_Append(&builder,content);
            CStr_Free(&content);
        }else{
            String_Append(&builder,"None");
        }
        
        if(i<list->size-1) String_Append(&builder,", ");
    }
    String_Append(&builder," }");
    char* resstr = String_CStr(&builder);
    String_Free(&builder);
    return Token_Move(TOKEN_CONSTSTRING_DOUBLE,resstr);
}
Token Listtype_Handler_Destroy(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);

    printf("DESTROY: %s\n",a->str);

    Variable* a_var = Scope_FindVariable(s,a->str);
    if(a_var){
        a_var->destroy(a_var);
    }
    
    return Token_Null();
}

Variable Listtype_Make(Scope* sc,CStr name,Variable* args){
    Variable ret = Variable_Make(
        "Listtype","list",(VariableMap[]){ VariableMap_New() },
        sizeof(VariableMap),sc->range - 1,
        Scope_DestroyerOfType(sc,"list"),
        Scope_CpyerOfType(sc,"list")
    );
    return ret;
}
Variable Listtype_ToStr(Scope* sc,CStr name,Variable* args){
    Variable* a_var = &args[0];
    
    if(!Variable_Data(a_var)){
        printf("[Listtype]: ToStr -> %s is not a var!\n",a_var->name);
    }else{
        Listtype* lptr = (Listtype*)Variable_Data(a_var);
        TokenMap tm = TokenMap_Make((Token[]){
            Token_By(TOKEN_STRING,a_var->name),
            Token_Null()
        });
        Token tstr = Listtype_Handler_Cast(sc,(Token[]){ Token_Move(TOKEN_CAST,NULL) },&tm);
        TokenMap_Free(&tm);

        Variable v = Variable_Make(
            "ToStr","str",(CStr[]){ tstr.str },
            sizeof(CStr),sc->range - 1,
            Scope_DestroyerOfType(sc,"str"),
            Scope_CpyerOfType(sc,"str")
        );
        tstr.str = NULL;
        Token_Free(&tstr);
        return v;
    }

    return Variable_Null();
}
Variable Listtype_Contains(Scope* sc,CStr name,Variable* args){
    Variable* a_var = &args[0];
    Variable* e_var = &args[1];
    
    if(!Variable_Data(a_var)){
        printf("[Listtype]: ToStr -> %s is not a var!\n",a_var->name);
    }else{
        Listtype* members = (Listtype*)Variable_Data(a_var);
        CStr e_str = *(CStr*)Variable_Data(a_var);
        Variable* member = VariableMap_Find(members,e_str);
        
        if(member){
            return Variable_Make(
                "Contains","bool",(Boolean[]){ 1 },
                sizeof(Boolean),sc->range - 1,
                Scope_DestroyerOfType(sc,"bool"),
                Scope_CpyerOfType(sc,"bool")
            );
        }
    }

    return Variable_Make(
        "Contains","bool",(Boolean[]){ 0 },
        sizeof(Boolean),sc->range - 1,
        Scope_DestroyerOfType(sc,"bool"),
        Scope_CpyerOfType(sc,"bool")
    );
}

void Ex_Packer(ExternFunctionMap* Extern_Functions,Vector* funcs,Scope* s){//Vector<CStr>
    TypeMap_PushContained(&s->types,funcs,
        Type_New("list",sizeof(Listtype),OperatorInterationMap_Make((OperatorInterater[]){
            OperatorInterater_Make((CStr[]){ NULL },OperatorDefineMap_Make((OperatorDefiner[]){
                OperatorDefiner_New(TOKEN_CAST,(Token(*)(void*,Token*,Vector*))Listtype_Handler_Cast),
                OperatorDefiner_New(TOKEN_INIT,NULL),
                OperatorDefiner_New(TOKEN_DESTROY,NULL),
                OPERATORDEFINER_END
            })),
            OperatorInterater_Make((CStr[]){ "list",NULL },OperatorDefineMap_Make((OperatorDefiner[]){
                OperatorDefiner_New(TOKEN_LUALIKE_ASS,(Token(*)(void*,Token*,Vector*))Listtype_Listtype_Handler_Ass),
                OperatorDefiner_New(TOKEN_LUALIKE_ASD,(Token(*)(void*,Token*,Vector*))Listtype_Listtype_Handler_Asd),
                OPERATORDEFINER_END
            })),
            OperatorInterater_Make((CStr[]){ "int",NULL },OperatorDefineMap_Make((OperatorDefiner[]){
                OperatorDefiner_New(TOKEN_LUALIKE_SUBS,(Token(*)(void*,Token*,Vector*))Listtype_Int_Handler_Subs),
                OperatorDefiner_New(TOKEN_LUALIKE_ASD,(Token(*)(void*,Token*,Vector*))Listtype_Int_Handler_Asd),
                OperatorDefiner_New(TOKEN_LUALIKE_ASU,(Token(*)(void*,Token*,Vector*))Listtype_Int_Handler_Asu),
                OPERATORDEFINER_END
            })),
            OperatorInterater_Make((CStr[]){ "str",NULL },OperatorDefineMap_Make((OperatorDefiner[]){
                OperatorDefiner_New(TOKEN_LUALIKE_SUBS,(Token(*)(void*,Token*,Vector*))Listtype_Str_Handler_Subs),
                OperatorDefiner_New(TOKEN_LUALIKE_ASD,(Token(*)(void*,Token*,Vector*))Listtype_Str_Handler_Asd),
                OperatorDefiner_New(TOKEN_LUALIKE_ASU,(Token(*)(void*,Token*,Vector*))Listtype_Str_Handler_Asu),
                OperatorDefiner_New(TOKEN_LUALIKE_ASM,(Token(*)(void*,Token*,Vector*))Listtype_Str_Handler_Asm),
                OPERATORDEFINER_END
            })),
            OperatorInterater_Make((CStr[]){ "Boolean",NULL },OperatorDefineMap_Make((OperatorDefiner[]){
                OperatorDefiner_New(TOKEN_LUALIKE_ASD,(Token(*)(void*,Token*,Vector*))Listtype_Boolean_Handler_Asd),
                OPERATORDEFINER_END
            })),
            OperatorInterater_Make((CStr[]){ "float",NULL },OperatorDefineMap_Make((OperatorDefiner[]){
                OperatorDefiner_New(TOKEN_LUALIKE_ASD,(Token(*)(void*,Token*,Vector*))Listtype_Float_Handler_Asd),
                OPERATORDEFINER_END
            })),
            OperatorInterater_Make((CStr[]){ "obj",NULL },OperatorDefineMap_Make((OperatorDefiner[]){
                OperatorDefiner_New(TOKEN_LUALIKE_ASD,(Token(*)(void*,Token*,Vector*))Listtype_Obj_Handler_Asd),
                OPERATORDEFINER_END
            })),
            OPERATORINTERATER_END
        }),Listtype_Destroyer,Listtype_Cpyer)
    );

    ExternFunctionMap_PushContained(Extern_Functions,funcs,ExternFunction_New("new",NULL,(Member[]){ 
        MEMBER_END 
    },(void*)Listtype_Make));
    ExternFunctionMap_PushContained(Extern_Functions,funcs,ExternFunction_New("tostr",NULL,(Member[]){ 
        Member_New("list","l"),
        MEMBER_END
    },(void*)Listtype_ToStr));
    ExternFunctionMap_PushContained(Extern_Functions,funcs,ExternFunction_New("contains","bool",(Member[]){ 
        Member_New("list","l"),
        Member_New(NULL,"e"),
        MEMBER_END
    },(void*)Listtype_Contains));
}
