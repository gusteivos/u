#include "uvminstr.h"

const uvm_instruction_t first_uvm_instruction = UVM_INSTRUCTION_NOOP;

const uvm_instruction_t last_uvm_instruction = UVM_INSTRUCTION_SZOUTSTK;

const char *uvm_instruction2str[] =
{

    [UVM_INSTRUCTION_NOOP] = "noop",
    [UVM_INSTRUCTION_HALT] = "halt",

    [UVM_INSTRUCTION_UVMID ] = "uvmid" ,
    [UVM_INSTRUCTION_UVMSTS] = "uvmsts",
    [UVM_INSTRUCTION_CTXID ] = "ctxid" ,
    [UVM_INSTRUCTION_CTXSTS] = "ctxsts",

    [UVM_INSTRUCTION_GESTKB] = "gestkb",
    [UVM_INSTRUCTION_GESTKP] = "gestkp",
    [UVM_INSTRUCTION_SESTKB] = "sestkb",
    [UVM_INSTRUCTION_SESTKP] = "sestkp",

    [UVM_INSTRUCTION_GEIMA] = "geima",
    [UVM_INSTRUCTION_SEIMA] = "seima",
    [UVM_INSTRUCTION_CLIMA] = "clima",

    [UVM_INSTRUCTION_MEM] = "mem",
    [UVM_INSTRUCTION_GRO] = "gro",
    [UVM_INSTRUCTION_SWP] = "swp",

    [UVM_INSTRUCTION_BYPUSH] = "bypush",
    [UVM_INSTRUCTION_BYDROP] = "bydrop",
    [UVM_INSTRUCTION_BYDUP ] = "bydup" ,
    [UVM_INSTRUCTION_BYREV ] = "byrev" ,

    [UVM_INSTRUCTION_BYADD ] = "byadd" ,
    [UVM_INSTRUCTION_BYSUB ] = "bysub" ,
    [UVM_INSTRUCTION_BYMUL ] = "bymul" ,
    [UVM_INSTRUCTION_BYDIV ] = "bydiv" ,
    [UVM_INSTRUCTION_BYMOD ] = "bymod" ,
    [UVM_INSTRUCTION_BYADDS] = "byadds",
    [UVM_INSTRUCTION_BYSUBS] = "bysubs",
    [UVM_INSTRUCTION_BYMULS] = "bymuls",
    [UVM_INSTRUCTION_BYDIVS] = "bydivs",
    [UVM_INSTRUCTION_BYMODS] = "bymods",
    [UVM_INSTRUCTION_BYASL ] = "byasl" ,
    [UVM_INSTRUCTION_BYASR ] = "byasr" ,
    [UVM_INSTRUCTION_BYAND ] = "byand" ,
    [UVM_INSTRUCTION_BYOR  ] = "byor"  ,
    [UVM_INSTRUCTION_BYXOR ] = "byxor" ,
    [UVM_INSTRUCTION_BYNOT ] = "bynot" ,
    [UVM_INSTRUCTION_BYLSL ] = "bylsl" ,
    [UVM_INSTRUCTION_BYLSR ] = "bylsr" ,
    [UVM_INSTRUCTION_BYRL  ] = "byrl"  ,
    [UVM_INSTRUCTION_BYRR  ] = "byrr"  ,
    [UVM_INSTRUCTION_BYEQ  ] = "byeq"  ,
    [UVM_INSTRUCTION_BYGT  ] = "bygt"  ,
    [UVM_INSTRUCTION_BYLT  ] = "bylt"  ,
    [UVM_INSTRUCTION_BYGTS ] = "bygts" ,
    [UVM_INSTRUCTION_BYLTS ] = "bylts" ,

    [UVM_INSTRUCTION_SHPUSH] = "shpush",
    [UVM_INSTRUCTION_SHDROP] = "shdrop",
    [UVM_INSTRUCTION_SHDUP ] = "shdup" ,
    [UVM_INSTRUCTION_SHREV ] = "shrev" ,

    [UVM_INSTRUCTION_SHADD ] = "shadd" ,
    [UVM_INSTRUCTION_SHSUB ] = "shsub" ,
    [UVM_INSTRUCTION_SHMUL ] = "shmul" ,
    [UVM_INSTRUCTION_SHDIV ] = "shdiv" ,
    [UVM_INSTRUCTION_SHMOD ] = "shmod" ,
    [UVM_INSTRUCTION_SHADDS] = "shadds",
    [UVM_INSTRUCTION_SHSUBS] = "shsubs",
    [UVM_INSTRUCTION_SHMULS] = "shmuls",
    [UVM_INSTRUCTION_SHDIVS] = "shdivs",
    [UVM_INSTRUCTION_SHMODS] = "shmods",
    [UVM_INSTRUCTION_SHASL ] = "shasl" ,
    [UVM_INSTRUCTION_SHASR ] = "shasr" ,
    [UVM_INSTRUCTION_SHAND ] = "shand" ,
    [UVM_INSTRUCTION_SHOR  ] = "shor"  ,
    [UVM_INSTRUCTION_SHXOR ] = "shxor" ,
    [UVM_INSTRUCTION_SHNOT ] = "shnot" ,
    [UVM_INSTRUCTION_SHLSL ] = "shlsl" ,
    [UVM_INSTRUCTION_SHLSR ] = "shlsr" ,
    [UVM_INSTRUCTION_SHRL  ] = "shrl"  ,
    [UVM_INSTRUCTION_SHRR  ] = "shrr"  ,
    [UVM_INSTRUCTION_SHEQ  ] = "sheq"  ,
    [UVM_INSTRUCTION_SHGT  ] = "shgt"  ,
    [UVM_INSTRUCTION_SHLT  ] = "shlt"  ,
    [UVM_INSTRUCTION_SHGTS ] = "shgts" ,
    [UVM_INSTRUCTION_SHLTS ] = "shlts" ,

    [UVM_INSTRUCTION_INPUSH] = "inpush",
    [UVM_INSTRUCTION_INDROP] = "indrop",
    [UVM_INSTRUCTION_INDUP ] = "indup" ,
    [UVM_INSTRUCTION_INREV ] = "inrev" ,

    [UVM_INSTRUCTION_INADD ] = "inadd" ,
    [UVM_INSTRUCTION_INSUB ] = "insub" ,
    [UVM_INSTRUCTION_INMUL ] = "inmul" ,
    [UVM_INSTRUCTION_INDIV ] = "indiv" ,
    [UVM_INSTRUCTION_INMOD ] = "inmod" ,
    [UVM_INSTRUCTION_INADDS] = "inadds",
    [UVM_INSTRUCTION_INSUBS] = "insubs",
    [UVM_INSTRUCTION_INMULS] = "inmuls",
    [UVM_INSTRUCTION_INDIVS] = "indivs",
    [UVM_INSTRUCTION_INMODS] = "inmods",
    [UVM_INSTRUCTION_INASL ] = "inasl" ,
    [UVM_INSTRUCTION_INASR ] = "inasr" ,
    [UVM_INSTRUCTION_INAND ] = "inand" ,
    [UVM_INSTRUCTION_INOR  ] = "inor"  ,
    [UVM_INSTRUCTION_INXOR ] = "inxor" ,
    [UVM_INSTRUCTION_INNOT ] = "innot" ,
    [UVM_INSTRUCTION_INLSL ] = "inlsl" ,
    [UVM_INSTRUCTION_INLSR ] = "inlsr" ,
    [UVM_INSTRUCTION_INRL  ] = "inrl"  ,
    [UVM_INSTRUCTION_INRR  ] = "inrr"  ,
    [UVM_INSTRUCTION_INEQ  ] = "ineq"  ,
    [UVM_INSTRUCTION_INGT  ] = "ingt"  ,
    [UVM_INSTRUCTION_INLT  ] = "inlt"  ,
    [UVM_INSTRUCTION_INGTS ] = "ingts" ,
    [UVM_INSTRUCTION_INLTS ] = "inlts" ,

    [UVM_INSTRUCTION_SZPUSH] = "szpush",
    [UVM_INSTRUCTION_SZDROP] = "szdrop",
    [UVM_INSTRUCTION_SZDUP ] = "szdup" ,
    [UVM_INSTRUCTION_SZREV ] = "szrev" ,

    [UVM_INSTRUCTION_SZADD ] = "szadd" ,
    [UVM_INSTRUCTION_SZSUB ] = "szsub" ,
    [UVM_INSTRUCTION_SZMUL ] = "szmul" ,
    [UVM_INSTRUCTION_SZDIV ] = "szdiv" ,
    [UVM_INSTRUCTION_SZMOD ] = "szmod" ,
    [UVM_INSTRUCTION_SZADDS] = "szadds",
    [UVM_INSTRUCTION_SZSUBS] = "szsubs",
    [UVM_INSTRUCTION_SZMULS] = "szmuls",
    [UVM_INSTRUCTION_SZDIVS] = "szdivs",
    [UVM_INSTRUCTION_SZMODS] = "szmods",
    [UVM_INSTRUCTION_SZASL ] = "szasl" ,
    [UVM_INSTRUCTION_SZASR ] = "szasr" ,
    [UVM_INSTRUCTION_SZAND ] = "szand" ,
    [UVM_INSTRUCTION_SZOR  ] = "szor"  ,
    [UVM_INSTRUCTION_SZXOR ] = "szxor" ,
    [UVM_INSTRUCTION_SZNOT ] = "sznot" ,
    [UVM_INSTRUCTION_SZLSL ] = "szlsl" ,
    [UVM_INSTRUCTION_SZLSR ] = "szlsr" ,
    [UVM_INSTRUCTION_SZRL  ] = "szrl"  ,
    [UVM_INSTRUCTION_SZRR  ] = "szrr"  ,
    [UVM_INSTRUCTION_SZEQ  ] = "szeq"  ,
    [UVM_INSTRUCTION_SZGT  ] = "szgt"  ,
    [UVM_INSTRUCTION_SZLT  ] = "szlt"  ,
    [UVM_INSTRUCTION_SZGTS ] = "szgts" ,
    [UVM_INSTRUCTION_SZLTS ] = "szlts" ,

    [UVM_INSTRUCTION_BYSTOREIMM] = "bystoreimm",
    [UVM_INSTRUCTION_BYSTORESTK] = "bystorestk",
    [UVM_INSTRUCTION_BYFETCHIMM] = "byfetchimm",
    [UVM_INSTRUCTION_BYFETCHSTK] = "byfetchstk",

    [UVM_INSTRUCTION_SHSTOREIMM] = "shstoreimm",
    [UVM_INSTRUCTION_SHSTORESTK] = "shstorestk",
    [UVM_INSTRUCTION_SHFETCHIMM] = "shfetchimm",
    [UVM_INSTRUCTION_SHFETCHSTK] = "shfetchstk",

    [UVM_INSTRUCTION_INSTOREIMM] = "instoreimm",
    [UVM_INSTRUCTION_INSTORESTK] = "instorestk",
    [UVM_INSTRUCTION_INFETCHIMM] = "infetchimm",
    [UVM_INSTRUCTION_INFETCHSTK] = "infetchstk",

    [UVM_INSTRUCTION_SZSTOREIMM] = "szstoreimm",
    [UVM_INSTRUCTION_SZSTORESTK] = "szstorestk",
    [UVM_INSTRUCTION_SZFETCHIMM] = "szfetchimm",
    [UVM_INSTRUCTION_SZFETCHSTK] = "szfetchstk",

    [UVM_INSTRUCTION_JMPIMM  ] = "jmpimm"  ,
    [UVM_INSTRUCTION_JMPSTK  ] = "jmpstk"  ,
    [UVM_INSTRUCTION_JMPZIMM ] = "jmpzimm" ,
    [UVM_INSTRUCTION_JMPZSTK ] = "jmpzstk" ,
    [UVM_INSTRUCTION_JMPNZIMM] = "jmpnzimm",
    [UVM_INSTRUCTION_JMPNZSTK] = "jmpnzstk",

    [UVM_INSTRUCTION_CALIMM] = "calimm",
    [UVM_INSTRUCTION_CALSTK] = "calstk",
    [UVM_INSTRUCTION_RET]    = "ret"   ,

    [UVM_INSTRUCTION_BYIN] = "byin",
    [UVM_INSTRUCTION_SHIN] = "shin",
    [UVM_INSTRUCTION_ININ] = "inin",
    [UVM_INSTRUCTION_SZIN] = "szin",

    [UVM_INSTRUCTION_BYOUTIMM] = "byoutimm",
    [UVM_INSTRUCTION_BYOUTSTK] = "byoutstk",
    [UVM_INSTRUCTION_SHOUTIMM] = "shoutimm",
    [UVM_INSTRUCTION_SHOUTSTK] = "shoutstk",
    [UVM_INSTRUCTION_INOUTIMM] = "inoutimm",
    [UVM_INSTRUCTION_INOUTSTK] = "inoutstk",
    [UVM_INSTRUCTION_SZOUTIMM] = "szoutimm",
    [UVM_INSTRUCTION_SZOUTSTK] = "szoutstk"

};

const char *uvm_instruction2string(uvm_instruction_t instruction)
{

    if (instruction < first_uvm_instruction || instruction > last_uvm_instruction)
    {

        return NULL;

    }

    return uvm_instruction2str[instruction];

}
