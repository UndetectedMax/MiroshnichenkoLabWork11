#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include "libpq-fe.h"
int main(int argc, char **argv)
{
        const char *conninfo;
        PGconn *conn;
        PGresult *res;
        PGnotify *notify;
        char db_name[] = "miroshnichenko_maksim";
        char user_name[] = "miroshnichenko_maksim";
        conn = PQsetdbLogin(NULL, NULL, NULL, NULL, db_name, user_name, NULL);
        if (PQstatus(conn) != CONNECTION_OK)
        {
                fprintf(stderr, "Connection to database failed: %s",
                                        PQerrorMessage(conn));
                PQfinish(conn);
                exit(1);
        }
        res = PQexec(conn, "NOTIFY miroshnichenko, 'Hello, process of miroshnichenko'");
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
                fprintf(stderr, "NOTIFY Command failed: %s", PQerrorMessage(conn));
                PQclear(res);
                PQfinish(conn);
                exit(1);
        }
        PQclear(res);
        PQfinish(conn);
        return 0;
}
