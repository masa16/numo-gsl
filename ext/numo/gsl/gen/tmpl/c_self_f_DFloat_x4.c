static void
iter_<%=c_func%>(na_loop_t *const lp)
{
    size_t   i;
    char    *p1, *p2, *p3, *p4;
    ssize_t  s1, s2, s3, s4;
    double   x1, x2, x3, x4;
    <%=struct%> *w = (<%=struct%>*)(lp->opt_ptr);
    <% c_args = get(:postpose) ? "x1,x2,x3,x4,w" : "w,x1,x2,x3,x4" %>

    INIT_COUNTER(lp, i);
    INIT_PTR(lp, 0, p1, s1);
    INIT_PTR(lp, 1, p2, s2);
    INIT_PTR(lp, 2, p3, s3);
    INIT_PTR(lp, 3, p4, s4);

    for (; i--;) {
        GET_DATA_STRIDE(p1,s1,double,x1);
        GET_DATA_STRIDE(p2,s2,double,x2);
        GET_DATA_STRIDE(p3,s3,double,x3);
        GET_DATA_STRIDE(p4,s4,double,x4);
        <%=func_name%>(<%=c_args%>);
    }
}

/*
  @overload <%=name%>(<%=args[1..4].map{|a| a[1]}.join(",")%>)
  @param  [DFloat]   <%=args[1][1]%>
  @param  [DFloat]   <%=args[2][1]%>
  @param  [DFloat]   <%=args[3][1]%>
  @param  [DFloat]   <%=args[4][1]%>
  @return [<%=class_name%>]  self

  <%= description %>
*/
static VALUE
<%=c_func(4)%>(VALUE self, VALUE v1, VALUE v2, VALUE v3, VALUE v4)
{
    <%=struct%> *w;
    ndfunc_arg_in_t ain[4] = {{cDF,0},{cDF,0},{cDF,0},{cDF,0}};
    ndfunc_t ndf = {iter_<%=c_func%>, STRIDE_LOOP, 4,0, ain,0};

    TypedData_Get_Struct(self, <%=struct%>, &<%=data_type_var%>, w);

    na_ndloop3(&ndf, w, 4, v1, v2, v3, v4);
    return self;
}
