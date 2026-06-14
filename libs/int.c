#include "/home/codeleaded/System/Static/Library/AlxCallStack.h"
#include "/home/codeleaded/System/Static/Library/AlxExternFunctions.h"
#include "/home/codeleaded/System/Static/Library/LuaLikeDefines.h"
//#include "/home/codeleaded/Hecke/C/Cmd_Scripter/src/LuaLike.h"

Number Implementation_IntOf(Scope* s,Token* a){
    Number n = NUMBER_PARSE_ERROR;
    if(a->tt==TOKEN_STRING){
        Variable* a_var = Scope_FindVariable(s,a->str);
        if(a_var && a_var->data){
            n = *(Number*)Variable_Data(a_var);
        }else{
            s->Error(s,"[Int_Number]: 1. Arg: Variable %s doesn't exist!\n",a->str);
        }
    }else if(a->tt==TOKEN_NUMBER){
        n = a->v_i64;
    }else if(a->tt==TOKEN_FLOAT){
        n = (Number)a->v_f64;
    }else{
        s->Error(s,"[Int_Number]: 1. Arg: %s is not a int type!\n",a->str);
    }
    return n;
}

Token Int_Int_Handler_Ass(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);
    
    printf("(int,int) ASS: ");
    Token_Print_V(a);
    printf(" = ");
    Token_Print_V(b);
    printf("\n");

    Number n2 = Implementation_IntOf(s,b);
    
    if(a->tt==TOKEN_STRING){
        Variable* a_var = Scope_FindVariable(s,a->str);
        if(a_var){
            Variable_PrepairFor(a_var,sizeof(Number),"int",NULL,NULL);
            Variable_SetTo(a_var,(Number[]){ n2 });
        }else{
            Scope_BuildInitVariableRange(s,a->str,"int",s->range-1,(Number[]){ n2 });
        }
    }else{
        s->Error(s,"[Int_Ass]: 1. Arg: %s is not a variable type!\n",a->str);
    }

    return Token_New_I64(TOKEN_NUMBER,n2);
}
Token Int_Int_Handler_Add(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("(int,int) ADD: ");
    Token_Print_V(a);
    printf(" + ");
    Token_Print_V(b);
    printf("\n");

    Number n1 = Implementation_IntOf(s,a);
    Number n2 = Implementation_IntOf(s,b);
    Number res = n1 + n2;
    return Token_New_I64(TOKEN_NUMBER,res);
}
Token Int_Int_Handler_Sub(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("(int,int) SUB: ");
    Token_Print_V(a);
    printf(" - ");
    Token_Print_V(b);
    printf("\n");

    Number n1 = Implementation_IntOf(s,a);
    Number n2 = Implementation_IntOf(s,b);
    Number res = n1 - n2;
    return Token_New_I64(TOKEN_NUMBER,res);
}
Token Int_Int_Handler_Mul(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

     printf("(int,int) MUL: ");
    Token_Print_V(a);
    printf(" * ");
    Token_Print_V(b);
    printf("\n");

    Number n1 = Implementation_IntOf(s,a);
    Number n2 = Implementation_IntOf(s,b);
    Number res = n1 * n2;
    return Token_New_I64(TOKEN_NUMBER,res);
}
Token Int_Int_Handler_Div(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("(int,int) DIV: ");
    Token_Print_V(a);
    printf(" / ");
    Token_Print_V(b);
    printf("\n");

    Number n1 = Implementation_IntOf(s,a);
    Number n2 = Implementation_IntOf(s,b);

    Number res = 0;
    if(n2!=0)
        res = n1 / n2;
    else{
        s->Error(s,"[Environment]: Error: DIV by Zero\n");
    }

    return Token_New_I64(TOKEN_NUMBER,res);
}
Token Int_Int_Handler_Neg(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);

    printf("(int) NEG: -");
    Token_Print_V(a);
    printf("\n");

    Number n1 = Implementation_IntOf(s,a);
    Number res = -n1;
    return Token_New_I64(TOKEN_NUMBER,res);
}
Token Int_Int_Handler_Equ(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("(int,int) EQU: ");
    Token_Print_V(a);
    printf(" == ");
    Token_Print_V(b);
    printf("\n");

    Number n1 = Implementation_IntOf(s,a);
    Number n2 = Implementation_IntOf(s,b);
    Boolean res = n1 == n2;
    return Token_New_B1(TOKEN_BOOL,res);
}
Token Int_Int_Handler_Les(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("(int,int) LES: ");
    Token_Print_V(a);
    printf(" < ");
    Token_Print_V(b);
    printf("\n");

    Number n1 = Implementation_IntOf(s,a);
    Number n2 = Implementation_IntOf(s,b);
    Boolean res = n1 < n2;
    return Token_New_B1(TOKEN_BOOL,res);
}
Token Int_Int_Handler_Grt(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("(int,int) GRT: ");
    Token_Print_V(a);
    printf(" > ");
    Token_Print_V(b);
    printf("\n");

    Number n1 = Implementation_IntOf(s,a);
    Number n2 = Implementation_IntOf(s,b);
    Boolean res = n1 > n2;
    return Token_New_B1(TOKEN_BOOL,res);
}
Token Int_Int_Handler_Leq(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("(int,int) LEQ: ");
    Token_Print_V(a);
    printf(" <= ");
    Token_Print_V(b);
    printf("\n");

    Number n1 = Implementation_IntOf(s,a);
    Number n2 = Implementation_IntOf(s,b);
    Boolean res = n1 <= n2;
    return Token_New_B1(TOKEN_BOOL,res);
}
Token Int_Int_Handler_Grq(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("(int,int) GRQ: ");
    Token_Print_V(a);
    printf(" >= ");
    Token_Print_V(b);
    printf("\n");

    Number n1 = Implementation_IntOf(s,a);
    Number n2 = Implementation_IntOf(s,b);
    Boolean res = n1 >= n2;
    return Token_New_B1(TOKEN_BOOL,res);
}
Token Int_Handler_Cast(Scope* s,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);

    //printf("(int) CAST: ()");
    //Token_Print_V(a);
    //printf("\n");

    Number res = Implementation_IntOf(s,a);
    char* resstr = Number_Get(res);
    return Token_Move(TOKEN_CONSTSTRING_DOUBLE,resstr);
}

void Ex_Packer(ExternFunctionMap* Extern_Functions,Vector* funcs,Scope* s){//Vector<CStr>
    TypeMap_PushContained(&s->types,funcs,
        Type_New("int",8,OperatorInterationMap_Make((OperatorInterater[]){
            OperatorInterater_Make((CStr[]){ NULL },OperatorDefineMap_Make((OperatorDefiner[]){
                OperatorDefiner_New(TOKEN_LUALIKE_NEG,(Token(*)(void*,Token*,Vector*))Int_Int_Handler_Neg),
                OperatorDefiner_New(TOKEN_CAST,(Token(*)(void*,Token*,Vector*))Int_Handler_Cast),
                OperatorDefiner_New(TOKEN_INIT,NULL),
                OperatorDefiner_New(TOKEN_DESTROY,NULL),
                OPERATORDEFINER_END
            })),
            OperatorInterater_Make((CStr[]){ "int",NULL },OperatorDefineMap_Make((OperatorDefiner[]){
                OperatorDefiner_New(TOKEN_LUALIKE_ASS,(Token(*)(void*,Token*,Vector*))Int_Int_Handler_Ass),
                OperatorDefiner_New(TOKEN_LUALIKE_ADD,(Token(*)(void*,Token*,Vector*))Int_Int_Handler_Add),
                OperatorDefiner_New(TOKEN_LUALIKE_SUB,(Token(*)(void*,Token*,Vector*))Int_Int_Handler_Sub),
                OperatorDefiner_New(TOKEN_LUALIKE_MUL,(Token(*)(void*,Token*,Vector*))Int_Int_Handler_Mul),
                OperatorDefiner_New(TOKEN_LUALIKE_DIV,(Token(*)(void*,Token*,Vector*))Int_Int_Handler_Div),
                OperatorDefiner_New(TOKEN_LUALIKE_EQU,(Token(*)(void*,Token*,Vector*))Int_Int_Handler_Equ),
                OperatorDefiner_New(TOKEN_LUALIKE_LES,(Token(*)(void*,Token*,Vector*))Int_Int_Handler_Les),
                OperatorDefiner_New(TOKEN_LUALIKE_GRT,(Token(*)(void*,Token*,Vector*))Int_Int_Handler_Grt),
                OperatorDefiner_New(TOKEN_LUALIKE_LEQ,(Token(*)(void*,Token*,Vector*))Int_Int_Handler_Leq),
                OperatorDefiner_New(TOKEN_LUALIKE_GRQ,(Token(*)(void*,Token*,Vector*))Int_Int_Handler_Grq),
                OPERATORDEFINER_END
            })),
            OPERATORINTERATER_END
        }),NULL,NULL)
    );
}