#ifndef ISO8583_CONFIG_H
#define ISO8583_CONFIG_H

#include "iso8583.h"

static tsField sIsoDef[] = {
    {TYP_BCD, LEN_FIXED,    4   },/*field00*/
    {TYP_BIT, LEN_FIXED,    8   },/*field01*/
    {TYP_BCD, LEN_LLVAR,    19  },/*field02*/
    {TYP_BCD, LEN_FIXED,    6   },/*field03*/
    {TYP_BCD, LEN_FIXED,    12  },/*field04*/
    {TYP_BCD, LEN_FIXED,    12  },/*field05*/
    {TYP_BCD, LEN_FIXED,    12  },/*field06*/
    {TYP_BCD, LEN_FIXED,    10  },/*field07*/
    {TYP_BCD, LEN_FIXED,    8   },/*field08*/
    {TYP_BCD, LEN_FIXED,    8   },/*field09*/
    {TYP_BCD, LEN_FIXED,    8   },/*field10*/
    {TYP_BCD, LEN_FIXED,    6   },/*field11*/
    {TYP_BCD, LEN_FIXED,    6   },/*field12*/
    {TYP_BCD, LEN_FIXED,    4   },/*field13*/
    {TYP_BCD, LEN_FIXED,    4   },/*field14*/
    {TYP_BCD, LEN_FIXED,    4   },/*field15*/
    {TYP_BCD, LEN_FIXED,    4   },/*field16*/
    {TYP_BCD, LEN_FIXED,    4   },/*field17*/
    {TYP_BCD, LEN_FIXED,    4   },/*field18*/
    {TYP_BCD, LEN_FIXED,    3   },/*field19*/
    {TYP_BCD, LEN_FIXED,    3   },/*field20*/
    {TYP_BCD, LEN_FIXED,    3   },/*field21*/
    {TYP_BCD, LEN_FIXED,    3   },/*field22*/
    {TYP_BCD, LEN_FIXED,    4   },/*field23*/
    {TYP_BCD, LEN_FIXED,    3   },/*field24*/
    {TYP_BCD, LEN_FIXED,    2   },/*field25*/
    {TYP_BCD, LEN_FIXED,    2   },/*field26*/
    {TYP_BCD, LEN_FIXED,    1   },/*field27*/
    {TYP_ASC, LEN_FIXED,    9   },/*field28*/
    {TYP_ASC, LEN_FIXED,    9   },/*field29*/
    {TYP_ASC, LEN_FIXED,    9   },/*field30*/
    {TYP_ASC, LEN_LLVAR,    9   },/*field31*/
    {TYP_BCD, LEN_LLVAR,    99  },/*field32*/
    {TYP_BCD, LEN_LLVAR,    11  },/*field33*/
    {TYP_ASC, LEN_LLVAR,    28  },/*field34*/
    {TYP_BCD, LEN_LLVAR,    37  },/*field35*/
    {TYP_ASC, LEN_LLLVAR,   104 },/*field36*/
    {TYP_ASC, LEN_FIXED,    12  },/*field37*/
    {TYP_ASC, LEN_FIXED,    6   },/*field38*/
    {TYP_ASC, LEN_FIXED,    2   },/*field39*/
    {TYP_BCD, LEN_FIXED,    3   },/*field40*/
    {TYP_ASC, LEN_FIXED,    8   },/*field41*/
    {TYP_ASC, LEN_FIXED,    15  },/*field42*/
    {TYP_ASC, LEN_FIXED,    40  },/*field43*/
    {TYP_ASC, LEN_LLVAR,    25  },/*field44*/
    {TYP_ASC, LEN_LLVAR,    76  },/*field45*/
    {TYP_ASC, LEN_LLLVAR,   999 },/*field46*/
    {TYP_ASC, LEN_LLLVAR,   999 },/*field47*/
    {TYP_BCD, LEN_LLLVAR,   999 },/*field48*/
    {TYP_ASC, LEN_FIXED,    3   },/*field49*/
    {TYP_ASC, LEN_FIXED,    3   },/*field50*/
    {TYP_ASC, LEN_FIXED,    3   },/*field51*/
    {TYP_BIN, LEN_FIXED,    8   },/*field52*/
    {TYP_BCD, LEN_FIXED,    16  },/*field53*/
    {TYP_ASC, LEN_LLLVAR,   999 },/*field54*/
    {TYP_BIN, LEN_LLLVAR,   999 },/*field55*/
    {TYP_ASC, LEN_LLLVAR,   999 },/*field56*/
    {TYP_ASC, LEN_LLLVAR,   999 },/*field57*/
    {TYP_ASC, LEN_LLLVAR,   999 },/*field58*/
    {TYP_ASC, LEN_LLLVAR,   999 },/*field59*/
    {TYP_BCD, LEN_LLLVAR,   999 },/*field60*/
    {TYP_BCD, LEN_LLLVAR,   999 },/*field61*/
    {TYP_ASC, LEN_LLLVAR,   999 },/*field62*/
    {TYP_ASC, LEN_LLLVAR,   999 },/*field63*/
    {TYP_BIN, LEN_FIXED,    8   } /*field64*/
};

#endif // ISO8583_CONFIG_H
