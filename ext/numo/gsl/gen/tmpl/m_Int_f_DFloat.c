static void
iter_<%=c_func%>(na_loop_t *const lp)
{
    size_t   i;
    char    *p1, *p2;
    ssize_t  s1, s2;
    double   x;
    int      y;

    INIT_COUNTER(lp, i);
    INIT_PTR(lp, 0, p1, s1);
    INIT_PTR(lp, 1, p2, s2);

    for (; i--; ) {
        GET_DATA_STRIDE(p1,s1,double,x);
        y = <%=func_name%>(x);
        SET_DATA_STRIDE(p2,s2,int,y);
    }
}

/*
  @overload <%=name%>(<%=args[0][1]%>)
  @param  [DFloat]   <%=args[0][1]%>
  @return [Int]      result

  <%= description %>
*/
static VALUE
<%=c_func(1)%>(VALUE mod, VALUE v0)
{
    ndfunc_arg_in_t ain[1] = {{cDF,0}};
    ndfunc_arg_out_t aout[1] = {{cI,0}};
    ndfunc_t ndf = {iter_<%=c_func%>, STRIDE_LOOP|NDF_EXTRACT, 1,1, ain,aout};

    return na_ndloop(&ndf, 1, v0);
}
