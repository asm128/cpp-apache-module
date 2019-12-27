#include <httpd.h>
#include <http_protocol.h>
#include <http_config.h>

// handler del modulo
int myapmodHandler(request_rec *reqrec)
{
    // test handler
    if (! reqrec->handler || strcmp(reqrec->handler, "example"))
        return DECLINED;

    // test metodo http
    if (reqrec->method_number != M_GET)
        return HTTP_METHOD_NOT_ALLOWED;

    // html output
    ap_set_content_type(reqrec, "text/html;charset=ascii");
    ap_rputs("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\">\n", 
                        reqrec);
    ap_rputs("<html>",  reqrec);
    ap_rputs("<head>",  reqrec);
    ap_rputs("<title>It Works!</title>", reqrec);
    ap_rputs("</head>", reqrec);
    ap_rputs("<body>",  reqrec);
    ap_rputs("<h1>C++ Apache Module</h1>", 
                        reqrec);
    ap_rputs("</body>", reqrec);
    ap_rputs("</html>", reqrec);

    // salgo con OK
    return OK;
}

// register hooks del modulo
void myapmodHooks(apr_pool_t *pool)
{
    // set hook handler
    ap_hook_handler(myapmodHandler, NULL, NULL, APR_HOOK_LAST);
}

// estructura global del modulo
module AP_MODULE_DECLARE_DATA example = {
    STANDARD20_MODULE_STUFF,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    myapmodHooks
};
