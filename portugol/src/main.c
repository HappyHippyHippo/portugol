#include <stdio.h>

#include "pt/pt.h"

void test1 (void)
{
    pt.runmode.set(PT_RUNMODE_DEBUG);

    pt_data_t val1 = pt.data.alloc_by_type(PT_DATATYPE_TEXT);
    pt_data_t val2 = pt.data.alloc_by_type(PT_DATATYPE_TEXT);
    pt_data_t result = pt.data.alloc_by_type(PT_DATATYPE_TEXT);

    if (!val1.data || !val2.data || !result.data)
    {
        printf("unable to allocate the data\n");
        exit(-1);
    }

    // getting methods accelerators
    pt_data_method_t assign;
    pt_data_method_t add;
    {
        pt_data_type_t params [] = { 0 };
        assign = pt.data.get_method(val1, PT_LANG_ASSIGN, params);
    }
    {
        pt_data_type_t params [] = { PT_DATATYPE_TEXT, 0 };
        add = pt.data.get_method(val1, PT_LANG_ADD, params);
    }

    // execute methods
    {
        pt_data_t text = { "Happy", pt.data.pool.get_by_type(PT_DATATYPE_TEXT) };
        void * args [] = { NULL };
        pt.data.method_ex(text, assign, args, & val1.data );
    }
    {
        pt_data_t text = { "HippyHippo", pt.data.pool.get_by_type(PT_DATATYPE_TEXT) };
        void * args [] = { NULL };
        pt.data.method_ex(text, assign, args, & val2.data );
    }
    {
        void * args [] = { val2.data, NULL };
        pt.data.method_ex(val1, add, args, & result.data );
    }

    printf("val1   : %s\n", (char *) val1.data);
    printf("val2   : %s\n", (char *) val2.data);
    printf("result : %s\n", (char *) result.data);

    pt.data.free(& result);
    pt.data.free(& val2);
    pt.data.free(& val1);
}

void ** cb (void * src, void ** args, void ** dest)
{
    return dest;
}

int main (int argc, char ** argv)
{
    pt_data_t val1   = pt.data.alloc_by_type(PT_DATATYPE_INTEGER32);
    pt_data_t val2   = pt.data.alloc_by_type(PT_DATATYPE_INTEGER32);
    pt_data_t result = pt.data.alloc_by_type(PT_DATATYPE_INTEGER32);

    if (!val1.data || !val2.data || !result.data)
    {
        printf("unable to allocate the data\n");
        exit(-1);
    }

    {
        pt_data_type_t params [] = { PT_DATATYPE_INTEGER32, 0 };
        pt.data.strategy.add_method(pt.data.pool.get_by_type(PT_DATATYPE_INTEGER32),
                                    PT_DATATYPE_INTEGER32,
                                    " foo",
                                    params,
                                    cb);
    }
    {
        pt_data_type_t params [] = { PT_DATATYPE_INTEGER8, PT_DATATYPE_INTEGER32, 0 };
        pt.data.strategy.add_method(pt.data.pool.get_by_type(PT_DATATYPE_INTEGER32),
                                    PT_DATATYPE_INTEGER32,
                                    " foo",
                                    params,
                                    cb);
    }
    {
        pt_data_type_t params [] = { PT_DATATYPE_INTEGER32, PT_DATATYPE_INTEGER32, 0 };
        pt.data.strategy.add_method(pt.data.pool.get_by_type(PT_DATATYPE_INTEGER32),
                                    PT_DATATYPE_INTEGER32,
                                    " foo",
                                    params,
                                    cb);
    }

    {
        pt_data_type_t params [] = { PT_DATATYPE_INTEGER32, PT_DATATYPE_INTEGER32, 0 };
        pt.data.get_method(val1, " foo", params);
    }
    {
        pt_data_type_t params [] = { PT_DATATYPE_BIT8, PT_DATATYPE_INTEGER32, 0 };
        pt.data.get_method(val1, " foo", params);
    }
    {
        pt_data_type_t params [] = { PT_DATATYPE_BIT8, 0 };
        pt.data.get_method(val1, " foo", params);
    }

    pt.data.free(& result);
    pt.data.free(& val2);
    pt.data.free(& val1);

    return 0;
}
